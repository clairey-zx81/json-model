# WIP
# TODO fix json path for all/any/one?! [1,2...]
# TODO check for possibly undefined defs by tracking defs and uses
# TODO define a Compiler class?
# TODO check for some obviously empty types?

import enum
import json
import re  # re2?
import logging
import urllib

# logging.basicConfig()
log = logging.getLogger("compiler")
log.setLevel(level=logging.INFO)
# log.setLevel(level=logging.DEBUG)

from typing import Callable

import json_model.utils as utils
import json_model.url_cache as url_cache
from json_model.utils import ModelError, ModelType, CheckFun, KeyCheckFun, UnknownModel, ModelDefs, one, distinct_values

# debug helpers
_debug: bool = True

def _trace(*args) -> bool:
    """Convenient expression debug tracer."""
    if _debug:
        log.debug(f"trace{args}")
    return True

def _show_index(checks: list[bool], val):
    bads = [ str(i) for i, b in enumerate(checks) if b == val ]
    # log.warning(f"checks={checks} bads={bads}")
    assert bads
    return "[" + ",".join(bads) + "]"


class CompileModel:

    def __init__(self, model, loose_int: bool = False, signed_int: bool = False):

        # is 2.0 an int?
        self._loose_int = loose_int
        # use -1/0/1 for any int, positive and strictly positive
        self._signed_int = signed_int

        # get options for meta-data
        if isinstance(model, dict) and "#" in model:
            meta = model["#"]
            if isinstance(meta, dict) and "options" in meta:
                options = meta["options"]
                if isinstance(options, (list, tuple)):
                    if "loose-int" in options:
                        self._loose_int = True
                    if "signed-int" in options:
                        self._signed_int = True
                    # TODO other options?

        self._LENGTH_LAMBDAS = {
            "eq": self._lambda_eq,
            "ne": self._lambda_ne,
            "le": self._lambda_le,
            "lt": self._lambda_lt,
            "ge": self._lambda_ge,
            "gt": self._lambda_gt,
        }

        # predefs
        self._defs = ModelDefs(self._raw_compile)
        self._defs.set("ANY", lambda _v, _p: True, "accept anything")
        self._defs.set("NONE", lambda _v, p: self._no(p, "none"), "refuse everything")
        self._defs.set("REGEX", lambda v, p: utils.is_regex(v) or self._no(p, "invalid regex"), "valid regular expression")
        # these are permissive for now
        self._defs.set("URI", lambda s, p: isinstance(s, str) or self._no(p, "invalid uri"))
        self._defs.set("URI-REFERENCE", lambda s, p: isinstance(s, str) or self._no(p, "invalid uri-reference"))
        # some predefined numeric types (strict)
        self._defs.set("I32", lambda v, p: isinstance(v, int) and -2**31 <= v and v <= (2**31 - 1) or self._no(p, "invalid I32"))
        self._defs.set("U32", lambda v, p: isinstance(v, int) and 0 <= v and v <= (2**32 - 1) or self._no(p, "invalid U32"))
        self._defs.set("I64", lambda v, p: isinstance(v, int) and -2**63 <= v and v <= (2**63 - 1) or self._no(p, "invalid I64"))
        self._defs.set("U64", lambda v, p: isinstance(v, int) and 0 <= v and v <= (2**64 - 1) or self._no(p, "invalid U64"))
        self._defs.set("F64", lambda v, p: isinstance(v, float) or self._no(p, "invalid F64"))

        # url cache
        self._urls = set()
        self._cache = url_cache.jsonURLCache()

        # actually compile the model
        self._fun = self._raw_compile(model)
        self._reasons = []

    def _no(self, path: str, msg: str, reset=False):
        """On error, record where and why it failed."""
        if reset:
            self._reasons = []
        self._reasons.append((path, msg))
        return False

    def _yes(self, reset=False):
        if reset:
            self._reasons = []
        return True

    def __call__(self, value: any) -> bool:
        """Call the checker on a value."""
        self._reasons = []
        try:
            return self._fun(value, "$")
        except Exception as e:
            # exceptions should not occur
            if _debug:
                log.error(e, exc_info=True)
            return False

    # stupid work around loop value capture
    def _lambda_eq(self, val):
        return lambda v, p: v == val or self._no(p, f"eq {val} failed")

    def _lambda_ne(self, val):
        return lambda v, p: v != val or self._no(p, f"ne {val} failed")

    def _lambda_le(self, val):
        return lambda v, p: v <= val or self._no(p, f"le {val} failed")

    def _lambda_lt(self, val):
        return lambda v, p: v < val or self._no(p, f"lt {val} failed")

    def _lambda_ge(self, val):
        return lambda v, p: v >= val or self._no(p, f"ge {val} failed")

    def _lambda_gt(self, val):
        return lambda v, p: v > val or self._no(p, f"gt {val} failed")

    # def _lambda_mo(self, val):
    #     # type check needed to avoid accepting bool
    #     return lambda v, p: type(v) in (int, float) and v % val == 0 or self._no(p, f"mo {val} failed")

    def _distinct(self):
        return lambda v, p: distinct_values(v) or self._no(p, "distinct failed")

    def _is_vartuple(self, model: ModelType) -> bool:
        """Is this model a variable-length tuple.

        I.e. a list in a constrained type.

        FIXME: for now only direct models are managed.
        """
        if not isinstance(model, dict) or "@" not in model:
            return False
        return isinstance(model["@"], (list, tuple))

    def _vartuple_check(self, model: list[ModelType], length=True) -> CheckFun:
        """Check a variable-length tuple.

        The last model is implicitly expanded for tail values.
        It length is true, check for size as well.

        FIXME: for now only direct models are managed.
        """
        if not isinstance(model, (list, tuple)):
            raise ModelError(f"unexpected vartuple model: {m} ({type(m)})")

        nmodels = len(model)
        if nmodels == 0:
            # empty list/tuple
            return lambda v, p: isinstance(v, (list, tuple)) and len(v) == 0 or \
                no(p, "expecting empty list")
        # else: we have a non empty list of models

        checks = [ self._raw_compile(m) for m in model ]
        last = checks[-1]

        def check_vartuple(v, p) -> bool:
            if not isinstance(v, (list, tuple)):
                return self._no(p, "expecting an array")
            if length and len(v) != nmodels:
                return self._no(p, f"expecting {nmodels} items")
            for i in range(len(v)):
                check = checks[i] if i < nmodels else last
                if not check(v[i], f"{p}[{i}]"):
                    return False
            return True

        return check_vartuple

    def _list_check(self, model: ModelType) -> CheckFun:
        """Check an array (list) and its contents."""
        item = self._raw_compile(model)
        def check_list(v, p) -> bool:
            if not isinstance(v, (list, tuple)):
                return self._no(p, "expecting an array")
            # return all(map(lambda i, e: item(e, f"{p}[{i}]"), enumerate(v)))
            item_checks = []
            for i, e in enumerate(v):
                item_checks.append(item(e, f"{p}[{i}]"))
            return all(item_checks) or self._no(p + _show_index(item_checks, False), "not all items checked")
        return check_list

    def _tuple_check(self, model: ModelType) -> CheckFun:
        """Check an array (tuple) and its contents."""
        if not isinstance(model, (list, tuple)):
            raise ModelError(f"unexpected tuple model: {m} ({type(m)})")

        nmodels = len(model)
        items = [ self._raw_compile(m) for m in model ]

        def check_tuple(v, p) -> bool:
            if not isinstance(v, (list, tuple)):
                return self._no(p, f"expecting an array")
            if len(v) != nmodels:
                return self._no(p, "bad array length")
            return all([ items[i](v[i], f"{p}[{i}]") for i in range(nmodels) ])

        return check_tuple

    def _keyname_val_compile(self, name: str, model: ModelType) -> KeyCheckFun:
        """Check object named property and its associated value."""
        val_check = self._raw_compile(model)
        # NOTE if $name is not defined it should coldly fail
        return lambda k, v, p: val_check(v, p) if self._defs[name](k, p) else None

    def _keyreg_val_compile(self, reg: str, model: ModelType) -> KeyCheckFun:
        """Check object named property and its associated value."""
        val_check = self._raw_compile(model)
        re_check = re.compile(reg).search
        return lambda k, v, p: val_check(v, p) if re_check(k) else None

    def _dict_check(self, model: ModelType) -> CheckFun:
        """Check a standard object."""

        assert isinstance(model, dict)

        # detect multiply defined properties
        properties: set(str) = set()

        must, may, refs, regs, ots = utils.split_object(model)

        # key/value checks functions
        mandatory = { key: self._raw_compile(val) for key, val in must.items() }
        optional = { key: self._raw_compile(val) for key, val in may.items() }

        # other optional properties have key-value check functions
        key_checks: dict[str, KeyCheckFun] = {}
        for key, val in refs.items():
            key_checks[key] = self._keyname_val_compile(key, val)
        for key, val in regs.items():
            key_checks[key] = self._keyreg_val_compile(key, val)

        if "" in ots:
            fun = self._raw_compile(ots[""])
            others = lambda k, v, p: isinstance(k, str) and fun(v, p) or self._no(f"{p}", f"bad property {k}")
        else:
            # reject unexpected properties
            others = lambda k, _v, p: self._no(f"{p}", f"unexpected property {k}")

        # function for the actual checking
        # captures mandatory, optional, key_checks, others
        def check_dict(v: any, p: str) -> bool:

            if not isinstance(v, dict):
                return False

            must_see = len(mandatory)

            # check v keys
            for key, val in v.items():
                if key in mandatory:
                    must_see -= 1
                    if not mandatory[key](val, f"{p}.{key}"):
                        return self._no(f"{p}.{key}", "bad mandatory value")
                elif key in optional:
                    if not optional[key](val, f"{p}.{key}"):
                        return self._no(f"{p}.{key}", "bad optional value")
                else:
                    # else key checks, which return None if unchecked
                    checked = False
                    for k, kc in key_checks.items():
                        res = kc(key, val, p)
                        if res is not None:
                            if not res:
                                return self._no(f"{p}.{kc}", f"bad key value for {k}")
                            checked = True
                            # keep on checking all others for determinism?
                            # break
                    # else try catch-all
                    if not checked and not others(key, val, f"{p}.{key}"):
                        return self._no(f"{p}.{key}", "unexpected other property")

            # all mandatory are accounted for?
            if must_see != 0:
                missing = set(mandatory.keys()).difference(v.keys())
                return self._no(p, f"missing mandatory key: {' '.join(sorted(missing))}")

            return True

        return check_dict

    def _ultimate_type(self, model: ModelType) -> type:
        """Get the utimate type by following definitions."""
        tmodel = type(model)
        if tmodel in (type(None), bool, int, float, list, tuple):
            return tmodel
        elif tmodel is str:
            if model == "" or model[0] != "$":
                return tmodel
            else:  # follow definition if possible
                m = self._defs.model(model[1:])
                return self._ultimate_type(m) if m != UnknownModel else m
        elif tmodel is dict:
            if "@" in model:
                return self._ultimate_type(model["@"])
            elif "|" in model:
                assert isinstance(model["|"], (list, tuple))
                types = set(self._ultimate_type(i) for i in model["|"])
                if len(types) == 1:
                    return types.pop()
                else:
                    return UnknownModel
            else:
                return tmodel

    def _ultimate_model(self, model: ModelType, constrained=True) -> ModelType:
        tmodel = type(model)
        if tmodel in (type(None), bool, int, float, list, tuple):
            return model
        elif tmodel is str:
            if model == "" or model[0] not in ("$", "="):
                return model
            elif model[0] == "=":
                return model
            else:  # follow definition if possible
                m = self._defs.model(model[1:])
                return self._ultimate_model(m) if m != UnknownModel else m
        elif tmodel is dict:
            if "@" in model:
                return self._ultimate_model(model["@"]) if constrained else UnknownModel
            elif "|" in model:
                return UnknownModel
            else:
                return model

    def _constant(self, model: ModelType):
        """Tell an ultimate model value has a constant."""
        # FIXME should it detect @ eq?
        v = self. _ultimate_model(model)
        if v == UnknownModel:
            return None
        tv = type(v)
        if tv == str:
            if v == "":
                return None
            elif v == "=null":
                return None
            elif re.search(r"^=\d+$", v):
                return int(v[1:])
            elif re.search(r"^=(true|false)$", v):
                return bool(v[1:])
            # TODO float?
            elif v[0] == "_":
                return v[1:]
            else:
                return v
        else:
            return None

    def _disjunction(self, model: ModelType) -> CheckFun|None:
        """Return the disjonctive property and its values."""
        assert isinstance(model, dict) and "|" in model
        # first filter out
        utype = self._ultimate_type(model)
        if utype != dict:
            log.debug(f"ultimate type not a dict: {utype}")
            return None
        # get models
        models = [self._ultimate_model(m) for m in model["|"]]
        # should not happen, just in case
        if len(models) < 2:
            log.debug(f"not enough models for a disjunction")
            return None
        # we may have some doubts yet (eg | in |)
        if any(filter(lambda m: type(m) != dict, models)):
            log.debug(f"some models are not objects")
            return None
        # only objects: collect their direct mandatory properties
        all_props: list[set[str]] = [
            set(k for k in m.keys() if k and k[0] not in ("$", "?"))
            for m in models
        ]
        # get cleaned props and their constant values
        all_const_props: list[dict[str, any]] = []
        for props, model in zip(all_props, models):
            consts: dict[str, any] = {}
            for prop in props:
                val = self._constant(model[prop])
                key = prop[1:] if prop[0] == "_" else prop
                if val is not None:
                    consts[key] = val
            all_const_props.append(consts)
        # tag candidates must:
        # - appear in all alternate models
        candidates: set[str] = set(all_const_props[0].keys())
        for props in all_const_props[1:]:
            candidates.intersection_update(props.keys())
        if not candidates:
            log.debug(f"no property with constant values")
            return None
        # - have the same type
        candidates_typed: set[str] = set()
        for prop in candidates:
            if len(set(type(consts[prop]) for consts in all_const_props)) == 1:
                candidates_typed.add(prop)
        if not candidates_typed:
            log.debug(f"no proprety with same type constants")
            return None
        # - have distinct constant values
        candidates_distinct: set[str] = set()
        for prop in candidates_typed:
            if len(set(consts[prop] for consts in all_const_props)) == len(all_const_props):
                candidates_distinct.add(prop)
        if not candidates_distinct:
            log.debug("no property with distinct values")
            return None
        if len(candidates_distinct) > 1:
            log.warning(f"several disjunctive properties: {candidates_distinct}")
        # one tag with one type and only constants found!
        tag_name = candidates_distinct.pop()
        tag_type = self._ultimate_type(all_const_props[0][tag_name])
        assert tag_type in (bool, int, float, str)

        # map tag values to value check
        TAG_CHECKS = {
            consts[tag_name]: self._raw_compile(model)
            for consts, model in zip(all_const_props, models)
        }

        # actual check function
        def disjunct_check(v, p):
            # is there a tag?
            if not isinstance(v, dict) or not tag_name in v:
                return self._no(p, f"missing tag {tag_name}")
            tag = v[tag_name]
            if not type(tag) == tag_type:
                return self._no(f"{p}.{tag_name}", f"bad tag type")
            return TAG_CHECKS.get(tag, lambda _, p: self._no(p, f"unexpected tag {tag_name} value {tag}"))(v, p)

        return disjunct_check

    def _obj_constraints(self, constraint: dict[str, any], ttype: type):
        """Check a constrained type constraints."""
        checks_val, checks_nb = [], []
        has_len = ttype in (str, list, tuple, dict)
        item_filter = None
        for kc, vc in constraint.items():

            if not isinstance(kc, str):
                raise ModelError(f"expecting str keys: {kc}")
            if kc in ("@", "%", "$", "#"):
                continue

            tvc = type(vc)

            if kc in self._LENGTH_LAMBDAS:
                if not tvc in (bool, int, float, str):
                    raise ModelError(f"unexpected type for {kc} {ttype}: {tvc}")
                lmd = self._LENGTH_LAMBDAS[kc]
                if tvc == int:
                    checks_nb.append(lmd(vc))
                elif tvc == str and vc.startswith("$"):
                    checks_nb.append(lmd(int(vc[1:])))
                elif ttype == tvc:
                    checks_val.append(lmd(vc))
                else:
                    raise ModelError(f"unexpected type for {kc} {ttype}: {tvc}")
            # elif kc == "in":
            #     if ttype not in (str, list, tuple):
            #         raise ModelError(f"unexpected type for {kc}: {ttype}")
            #     item_filter = self._raw_compile(vc)
            # elif kc == "mo":
            #     if type(vc) not in (int, float):
            #         raise ModelError(f"unexpected type for mo denominator: {type(vc)}")
            #     if ttype not in (int, float):
            #         raise ModelError(f"unexpected type for mo numerator: {ttype}")
            #     checks_val.append(self._lambda_mo(vc))
            elif kc == "distinct":
                if not isinstance(vc, bool):
                    raise ModelError(f"unexpected type for distinct: {type(vc)}")
                if vc:
                    checks_val.append(self._distinct())
            # OTHERS?
            else:
                raise ModelError(f"unexpected constraint: {kc}")

        # handle checks_nb
        if checks_nb:
            if item_filter:
                # chech "in" counts
                def in_check(v, p):
                    # count how many values match "in"
                    ins = 0
                    for i, e in enumerate(v):
                        if item_filter(e, f"{p}[{i}]"):
                            ins += 1
                    # then check "in" count against expectations
                    return all(map(lambda f: f(ins, p), checks_nb))
                checks_val.append(in_check)
            elif has_len:
                # check length of whatever
                def nb_check(v, p):
                    l = len(v)
                    return all(map(lambda f: f(l, p), checks_nb))
                checks_val.append(nb_check)
            else:
                # just apply on value
                checks_val.append(lambda v, p: all(map(lambda f: f(v, p), checks_nb)))

        # return final check
        if checks_val:
           return lambda v, p: all(map(lambda f: f(v, p), checks_val))
        else:
           return None

    def _constrained_model_check(self, model: dict[str, any]) -> CheckFun:
        """Check a constrained type type and constraints."""
        assert isinstance(model, dict) and "@" in model
        vtype = model["@"]
        ttype = type(vtype)
        # FIXME skip: None, bool???
        if not ttype in (bool, type(None), str, int, float, tuple, list, dict):
            raise ModelError(f"unexpected type object value type: {type(vtype)}")
        if self._is_vartuple(model):
            # FIXME should skip it in some cases?
            val_check = self._vartuple_check(vtype, False)
        else:
            val_check = self._raw_compile(vtype)
        # compile constraints
        val_cons = self._obj_constraints(model, ttype)
        # TODO or no?
        if val_cons:
            return lambda v, p: val_check(v, p) and val_cons(v, p)
        else:
            return val_check

    def _alternate_model_check(self, model: dict[str, any]) -> CheckFun:
        assert isinstance(model, dict) and "|" in model
        if not set(model.keys()).issubset(["#", "$", "%", "|"]):
            raise ModelError(f"key combination not implemented yet: {model}")
        mv = model["|"]
        if not isinstance(mv, (list, tuple)):
            raise ModelError(f"unexpected | alternate value: {mv} ({type(mv)})")
        if not mv: # empty list shortcut
            return lambda _v, p: self._no(p, "no value allowed")
        # try optimized disjuction
        check = self._disjunction(model)
        if check:
            return check
        # else alternate is to try till one matches, in order
        subs = [ self._raw_compile(m) for m in mv ]
        return lambda v, p: self._yes(True) if any(map(lambda f: f(v, p), subs)) else self._no(p, "not any matched")

    def _conjunctive_model_check(self, model: dict[str, any]) -> CheckFun:
        assert isinstance(model, dict) and "&" in model
        if not set(model.keys()).issubset(["#", "$", "%", "&"]):
            raise ModelError(f"key combination not implemented yet: {model}")
        mv = model["&"]
        if not isinstance(mv, (list, tuple)):
            raise ModelError(f"unexpected & conjonctive value: {mv} (type{mv})")
        subs = [ self._raw_compile(m) for m in mv ]
        # TODO tell which one(s) failed
        return lambda v, p: self._yes(True) if all(map(lambda f: f(v, p), subs)) else self._no(p, "not all matched")

    def _exclusive_model_check(self, model: dict[str, any]) -> CheckFun:
        assert isinstance(model, dict) and "^" in model
        if not set(model.keys()).issubset(["#", "$", "%", "^"]):
            raise ModelError(f"key combination not implemented yet: {model}")
        mv = model["^"]
        if not isinstance(mv, (list, tuple)):
            raise ModelError(f"unexpected & conjonctive value: {mv} (type{mv})")
        if not mv: # empty list shortcut
            return lambda _v, p: self._no(p, "no value allowed")
        subs = [ self._raw_compile(m) for m in mv ]
        # TODO tel why it failed (none or more than one)
        return lambda v, p: self._yes(True) if one(map(lambda f: f(v, p), subs)) else self._no(p, "not one matched")

    def _additive_model_check(self, model: dict[str, any]) -> CheckFun:
        # sanity checks
        assert isinstance(model, dict) and "+" in model
        if not set(model.keys()).issubset(["#", "$", "%", "+"]):
            raise ModelError(f"key combination not implemented yet: {model}")
        # merge!
        # get actual models
        models = model["+"]
        if not isinstance(models, (list, tuple)):
            raise ModelError(f"+ expects a list, got {type(models)}")
        if len(models) == 0:
            return lambda v, p: self._no(p, "empty +")
        models = [ self._ultimate_model(m) for m in models ]
        return self._dict_check(utils.merge_simple_models(models))

    def _none_raw_compile(self, model: type(None)) -> CheckFun:
        """Compile null."""
        return lambda v, p: v is None or self._no(p, "expecting null")

    def _bool_raw_compile(self, model: bool) -> CheckFun:
        """Compile a boolean."""
        return lambda v, p: isinstance(v, bool) or self._no(p, "expecting a boolean")

    def _int_raw_compile(self, model: int) -> CheckFun:
        """Compile a number (int)."""
        # NOTE beware that isinstace(true, int) == True
        assert isinstance(model, int)

        # loose int?
        if self._loose_int:
            is_an_int = lambda v, p: (type(v) == int or type(v) == float and v == int(v)) or \
                self._no(p, "expecting a (loose) integer")
        else:
            is_an_int = lambda v, p: type(v) == int or self._no(p, "expecting an integer")

        # signed int?
        if self._signed_int:
            if model == -1:
                check = is_an_int
            elif model == 0:
                check = lambda v, p: is_an_int(v, p) and v >= 0 or self._no(p, "must be positive")
            elif model == 1:
                check = lambda v, p: is_an_int(v, p) and v > 0 or self._no(p, "must be strictly positive")
            else:
                check = is_an_int
        else:
            check = is_an_int

        return check

    def _float_raw_compile(self, model: float) -> CheckFun:
        """Compile a number (float)."""
        assert isinstance(model, float)
        # NOTE does not handle NaN, +-Infinity
        # NOTE beware that isinstance(true, int) == True
        return lambda v, p: type(v) in (float, int) or self._no(p, "expecting a number")

    def _str_url_resolve(self, url: str):
        """Handle a URL reference."""
        assert isinstance(url, str) and re.match(r"(file|https?)://", url)

        # prevent recursion on full urls
        if url in self._urls or url in self._defs:
            return
        else:
            self._urls.add(url)

        umodel = self._cache.load(url)
        u = urllib.parse.urlparse(url)
        if u.fragment:
            if url.fragment.startswith("/"):
                # FIXME path handling
                raise ModelError(f"unsupported url path: {url}")
            else:
                model = umodel["%"][u.fragment]
        else:
            model = umodel

        self._defs[url] = self._raw_compile(model)

    def _str_raw_compile(self, model: str) -> CheckFun:
        """Compile a string."""
        if model == "":
            return lambda v, p: isinstance(v, str) or self._no(p, "expecting a string")
        # handle char prefix
        char, name = model[0], model[1:]
        if char == "=":
            # special constants
            if name == "true":
                return lambda v, p: isinstance(v, bool) and v or self._no(p, "expecting boolean true")
            elif name == "false":
                return lambda v, p: isinstance(v, bool) and not v or self._no(p, "expecting boolean false")
            elif name == "null":
                return lambda v, p: v is None or self._no(p, "expecting null")
            elif re.search("^-?[0-9]+$", name):
                val = int(name)
                return lambda v, p: type(v) == int and v == val or self._no(p, f"expecting integer {val}")
            else:
                try:
                    val = float(name)
                    return lambda v, p: type(v) in (int, float) and v == val or self._no(p, "expecting number {val}")
                except:
                    raise ModelError(f"unexpected str constant: {name}")
        elif char == "$":
            if len(model) == 1:
                raise ModelError(f"unexpected str model: {model}")
            else:
                if re.match(r"(file|https?)://", name):
                    self._str_url_resolve(name)
                if name in self._defs:
                    # log.warning(f"found defs[{name}]: {_DEFS[name](True)}")
                    # TODO or no, only dynamic?
                    return self._defs[name]
                else:
                    return lambda v, p: self._defs[name](v, p) or self._no(p, f"${name} failed")
        elif char == "_":
            return lambda v, p: isinstance(v, str) and v == name or self._no(p, f"expecting string {name}")
        elif char == "^":
            check_re = re.compile(model).search
            return lambda v, p: isinstance(v, str) and check_re(v) is not None or self._no(p, f"expecting regex {model}")
        else:
            return lambda v, p: isinstance(v, str) and v == model or self._no(p, f"expecting string {model}")

    def _list_raw_compile(self, model: any) -> CheckFun:
        """Compile an array."""
        nmodels = len(model)
        if nmodels == 1:
            return self._list_check(model[0])
        else:
            return self._tuple_check(model)

    def _dict_raw_compile(self, model: dict) -> CheckFun:
        """Compile a generic element."""

        # special properties
        if "$" in model and not isinstance(model["$"], str):
            raise ModelError(f"unexpected model name type: {type(model['$'])}")
        if "%" in model:
            defs = model["%"]
            if not isinstance(defs, dict):
                raise ModelError(f"unexpected % value: {defs}")
            for name, val in defs.items():
                if not isinstance(name, str): # or len(str) == 0:
                    raise ModelError(f"unexpected def name: {name} ({type(name)})")
                # if name in _DEFS:
                #    log.warning(f"overwriting definition for {name}")
                # _DEFS[name] = _raw_compile(val)
                self._defs.set(name, val)
        if "#" in model:
            # just basic checks
            meta = model["#"]
            if not isinstance(meta, (str, dict)):
                raise ModelError(f"unexpected # value: {meta} ({type(meta)})")
            # if isinstance(meta, dict) and "$$" in meta and not isinstance(meta["$$"], str):
            #     raise ModelError(f"unexpected $$ value: {meta['$$']} ({type(meta['$$'])})")

        # classes
        if "@" in model:
            check = self._constrained_model_check(model)
        elif "|" in model:
            check = self._alternate_model_check(model)
        elif "&" in model:
            check = self._conjunctive_model_check(model)
        elif "^" in model:
            check = self._exclusive_model_check(model)
        elif "+" in model:
            check = self._additive_model_check(model)
        else:
            check = self._dict_check(model)

        # maybe memoize for recursion
        if "$" in model:
            self._defs[model["$"]] = check

        return check

    def _raw_compile(self, model: any) -> CheckFun:
        """Dynamic "compilation" of a model."""
        # static switch on model type
        tmodel = type(model)
        if tmodel == type(None):
            return self._none_raw_compile(model)
        elif tmodel == bool:
            return self._bool_raw_compile(model)
        elif tmodel == int:
            return self._int_raw_compile(model)
        elif tmodel == float:
            return self._float_raw_compile(model)
        elif tmodel == str:
            return self._str_raw_compile(model)
        elif tmodel in (list, tuple):
            return self._list_raw_compile(model)
        elif tmodel == dict:
            return self._dict_raw_compile(model)
        else:
            raise ModelError(f"unexpected model type {type(model)}: {model}")


def compileModel(model: ModelType) -> CheckFun:
    """Compile a JSON Model."""
    return CompileModel(model)
