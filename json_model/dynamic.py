# WIP
#
# This compiler generates dynamic (lambda) code to check a value.
#
# TODO str -> ModelPath
# TODO check for possibly undefined defs by tracking defs and uses
# TODO check for some obviously empty types?

from typing import Callable
import copy
import re  # re2?
import json
import argparse
import logging
import urllib.parse

from . import utils, url_cache
from .types import ModelError, ModelType, ModelArray, ModelObject
from .types import ValueType, CheckFun, KeyCheckFun, JsonModel, JsonObject, Jsonable
from .utils import distinct_values, model_in_models, tname, log

# FIXME move to validator? change name?!
from .defines import Validator

# whether to shorten one/all combinator computations
fast_fail: bool = False

def _trace(*args) -> bool:
    """Convenient expression debug tracer."""
    if True:
        log.debug(f"trace{args}")
    return True


def _show_index(checks: list[bool], val):
    """For better error messages, show failing indexes."""
    bads = [str(i) for i, b in enumerate(checks) if b == val]
    # log.warning(f"checks={checks} bads={bads}")
    assert bads
    return "[" + ",".join(bads) + "]"


class DynamicCompiler(Validator):

    def __init__(self, model: JsonModel, debug: bool = False):

        log.debug(f"dynamic compiling {model._id}")

        # TODO remove compiler
        super().__init__(self._raw_compile)

        self._debug = debug
        self._model = model
        self._compiled_ids: set[int] = set()
        self._compiled: dict[int, CheckFun] = {}

        self._loose_int = False  # is 2.0 an int?
        self._loose_float = False  # is 42 a float?
        # get options for meta-data
        if isinstance(model, dict) and "#" in model:
            meta = model["#"]
            assert isinstance(meta, str)
            if "JSON_MODEL_LOOSE_INT" in meta:
                self._loose_int = True
            if "JSON_MODEL_NOT_LOOSE_INT" in meta:
                self._loose_int = False
            if "JSON_MODEL_LOOSE_FLOAT" in meta:
                self._loose_float = True
            if "JSON_MODEL_NOT_LOOSE_FLOAT" in meta:
                self._loose_float = False
            # TODO other options?

        # comparison which can apply on length if necessary
        self._LENGTH_LAMBDAS = {
            "=": self._lambda_eq,
            "!=": self._lambda_ne,
            "<=": self._lambda_le,
            "<": self._lambda_lt,
            ">=": self._lambda_ge,
            ">": self._lambda_gt,
        }

        # load all predefs
        # FIXME ensure model.py consistency!
        self._defs.set("$ANY", self._ANY, "<ANY>", "accept anything")
        self._defs.set("$NONE", self._NONE, "<NONE>", "refuse everything")
        # FIXME /.../ vs ...?
        self._defs.set("$REGEX",
                       lambda v, p: utils.is_regex(v, p) or self._no("<REGEX>", p, "invalid regex"),
                       "<REGEX>", "valid regular expression")
        # these are permissive for now
        self._defs.set("$URI", lambda s, p: isinstance(s, str) or self._no("<URI>",
                       p, "invalid uri"))
        self._defs.set("$URI-REFERENCE",
                       lambda s, p: (isinstance(s, str) or
                                     self._no("<URI-REFERENCE>", p, "invalid uri-reference")))
        # some predefined numeric types (strict)
        self._defs.set("$I32", lambda v, p: (isinstance(v, int) and -2**31 <= v <= (2**31 - 1) or
                                            self._no("<I32>", p, "invalid I32")))
        self._defs.set("$U32", lambda v, p: (isinstance(v, int) and 0 <= v <= (2**32 - 1) or
                                            self._no("<U32>", p, "invalid U32")))
        self._defs.set("$I64", lambda v, p: (isinstance(v, int) and -2**63 <= v <= (2**63 - 1) or
                                            self._no("<I64>", p, "invalid I64")))
        self._defs.set("$U64", lambda v, p: (isinstance(v, int) and 0 <= v <= (2**64 - 1) or
                                            self._no("<U64>", p, "invalid U64")))
        # FIXME F32? FLOAT?
        self._defs.set("$F64", lambda v, p: isinstance(v, float) or
                                            self._no("<F64>", p, "invalid F64"))
        self._defs.set("$STRING", lambda v, p: isinstance(v, str) or
                                               self._no("<STRING>", p, "not a string"))
        self._defs.set("$BOOL", lambda v, p: isinstance(v, bool) or
                                             self._no("<BOOL>", p, "not a boolean"))
        self._defs.set("$NUMBER",
                       lambda v, p: isinstance(v, (int, float)) and not isinstance(v, bool) or
                                    self._no("<NUMBER>", p, "invalid number"))

        # actually compile the model
        # FIXME make path JsonPath?!
        for name, jm in model._defs.items():
            self._compile(jm, "." + name, False)

        # log.debug(f"compiled_ids: {self._compiled_ids}")
        # FIXME fix globals on references!?
        # NOTE may have been already compiled in references
        self._compile(self._model, "", True)

        self._fun = self._compiled[self._model._id]
        self._reasons = []

    def _compile(self, jm: JsonModel, mpath: str, is_root: bool = False):
        if jm._id not in self._compiled_ids:
            log.debug(f"compiling {mpath} ({jm._id})")
            self._compiled_ids.add(jm._id)
            self._compiled[jm._id] = self._raw_compile(jm, jm._model, mpath, is_root)

    def _ref2fun(self, jm: JsonModel, ref: str, mpath: str) -> CheckFun:
        # predefs…
        if ref in self._defs:
            return self._defs.get(ref)
        # URL or simple refs only
        jmref = jm.resolveRef(ref, mpath.split("."))
        refid = jmref._id
        if refid not in self._compiled_ids:
            self._compile(jmref, ref)
        if refid in self._compiled:  # static resolution
            return self._compiled[refid]
        else:  # not available yet, actual recursion, use dynamic resolution
            def dyna(v, p):
                fun = self._compiled[refid] if refid in self._compiled else None
                return fun(v, p) if fun else self._no(mpath, p, f"{ref} not found")
            return dyna

    def __str__(self):
        return f"defs={self._defs}, model={self._model}"

    def _NONE(self, _v, vpath: str):
        return self._no("<NONE>", vpath, "$NONE")

    def _ANY(self, _v, _p):
        return True

    # NOTE long implementation to collect all results
    def _one(self, lb, mpath, vpath) -> bool:
        okay = []
        for i, b in enumerate(lb):
            if b:
                okay.append(i)
                if fast_fail and len(okay) >= 2:
                    return self._no(mpath, vpath, f"multiple matches found: {okay}")
        if len(okay) != 1:
            if len(okay) == 0:
                return self._no(mpath, vpath, "no match found")
            else:
                return self._no(mpath, vpath, f"multiple matches found: {okay}")
        else:
            return True

    # NOTE long implementation to collect all failures
    def _all(self, lb, mpath, vpath) -> bool:
        failed, i = [], 0
        for i, b in enumerate(lb):
            if not b:
                if fast_fail:
                    return self._no(mpath, vpath, f"all failure on {i}")
                failed.append(i)
        if failed:
            return self._no(mpath, vpath, f"all failures {len(failed)}/{i + 1}: {failed}")
        else:
            return True

    def _no(self, mpath: str, vpath: str, msg: str, reset: bool = False):
        """On error, record where and why it failed."""
        if reset:
            self._reasons = []
        self._reasons.append((mpath, vpath, msg))
        return False

    def _yes(self, reset: bool = False):
        if reset:
            self._reasons = []
        return True

    def __call__(self, value: Jsonable, path: str = "$") -> bool:
        """Call the checker on a value."""
        self._reasons = []
        try:
            return self._fun(value, path)
        except Exception as e:
            # exceptions should not occur
            if self._debug:
                log.error(e, exc_info=True)
            # FIXME raise?!
            return False

    # stupid work around loop value capture
    def _lambda_eq(self, val: ValueType, mpath: str) -> CheckFun:
        return lambda v, p: v == val or self._no(mpath, p, f"== {val} failed")

    def _lambda_ne(self, val: ValueType, mpath: str) -> CheckFun:
        return lambda v, p: v != val or self._no(mpath, p, f"!= {val} failed")

    def _lambda_le(self, val: ValueType, mpath: str) -> CheckFun:
        return lambda v, p: v <= val or self._no(mpath, p, f"<= {val} failed")

    def _lambda_lt(self, val: ValueType, mpath: str) -> CheckFun:
        return lambda v, p: v < val or self._no(mpath, p, f"< {val} failed")

    def _lambda_ge(self, val: ValueType, mpath: str) -> CheckFun:
        return lambda v, p: v >= val or self._no(mpath, p, f">= {val} failed")

    def _lambda_gt(self, val: ValueType, mpath: str) -> CheckFun:
        return lambda v, p: v > val or self._no(mpath, p, f"> {val} failed")

    def _distinct(self, mpath: str) -> CheckFun:
        return (self.trace(lambda v, p: distinct_values(v) or
                self._no(mpath, p, "distinct failed"), mpath, "!"))

    # def _lambda_mo(self, val):
    #  # type check needed to avoid accepting bool
    #  return lambda v, p: type(v) in (int, float) and v % val == 0 or
    #         self._no(p, f"mo {val} failed")

    def trace(self, fun: CheckFun, mpath: str, what: str = "") -> CheckFun:
        """Trace check function execution and results."""
        if self._debug:
            def tfun(val, vpath):
                ok = fun(val, vpath)
                log.debug(f"{what} {vpath}: {ok} [{mpath}]")
                return ok
            return tfun
        else:
            return fun

    def _is_vartuple(self, model: ModelType) -> bool:
        """Is this model a variable-length tuple.

        I.e. a list in a constrained type.

        FIXME: for now only direct models are managed.
        """
        if not isinstance(model, dict) or "@" not in model:
            return False
        return isinstance(model["@"], list)

    def _vartuple_check(self, jm: JsonModel, model: ModelArray, mpath: str, length=True) -> CheckFun:
        """Check a variable-length tuple.

        The last model is implicitly expanded for tail values.
        It length is true, check for size as well.

        FIXME: for now only direct models are managed.
        """
        if not isinstance(model, list):
            raise ModelError(f"unexpected vartuple model: {model} ({tname(model)}) [{mpath}]")

        nmodels = len(model)
        if nmodels == 0:
            # empty list/tuple
            return self.trace(lambda v, p: isinstance(v, (list, tuple)) and len(v) == 0 or
                              self._no(mpath, p, "expecting empty list"), mpath, "()")
        # else: we have a non empty list of models

        checks = [self._raw_compile(jm, m, f"{mpath}[{i}]") for i, m in enumerate(model)]
        last = checks[-1]

        def check_vartuple(v, p) -> bool:
            if not isinstance(v, (list, tuple)):
                return self._no(mpath, p, "expecting an array")
            if length and len(v) != nmodels:
                return self._no(mpath, p, f"expecting {nmodels} items")
            for i in range(len(v)):
                check = checks[i] if i < nmodels else last
                if not check(v[i], f"{p}[{i}]"):
                    return False
            return True

        return self.trace(check_vartuple, mpath, "(+)")

    def _list_check(self, jm: JsonModel, model: ModelArray, mpath: str) -> CheckFun:
        """Check an array (list) and its contents."""
        item = self._raw_compile(jm, model, mpath)

        def check_list(v, p) -> bool:
            if not isinstance(v, list):
                return self._no(mpath, p, "expecting an array")
            # return all(map(lambda i, e: item(e, f"{p}[{i}]"), enumerate(v)))
            item_checks = []
            for i, e in enumerate(v):
                item_checks.append(item(e, f"{p}[{i}]"))
            return self._all(item_checks, mpath, p)

        return self.trace(check_list, mpath, "[*]")

    def _tuple_check(self, jm: JsonModel, model: ModelArray, mpath: str) -> CheckFun:
        """Check an array (tuple) and its contents."""

        if not isinstance(model, list):
            raise ModelError(f"unexpected tuple model: {model} ({tname(model)}) [{mpath}]")

        nmodels = len(model)
        items = [self._raw_compile(jm, m, f"{mpath}[{i}]") for i, m in enumerate(model)]

        def check_tuple(v, p) -> bool:
            if not isinstance(v, (list, tuple)):
                return self._no(mpath, p, "expecting an array")
            if len(v) != nmodels:
                return self._no(mpath, p, "bad array length")
            return all([items[i](v[i], f"{p}[{i}]") for i in range(nmodels)])

        return self.trace(check_tuple, mpath, "(*)")

    def _keyname_val_compile(self, jm: JsonModel, name: str, model: ModelType, mpath: str) -> KeyCheckFun:
        """Check object named property and its associated value."""
        val_check = self._raw_compile(jm, model, f"{mpath}.{name}")
        def_check = self._ref2fun(jm, name, mpath)
        # NOTE if $name is not defined it should coldly fail
        assert val_check is not None and def_check is not None  # pyright hint
        return lambda k, v, p: val_check(v, p) if def_check(k, p) else None

    def _keyreg_val_compile(self, jm: JsonModel, reg: str, model: ModelType, mpath: str) -> KeyCheckFun:
        """Check object named property and its associated value."""
        val_check = self._raw_compile(jm, model, f"{mpath}.{reg}")
        re_check = re.compile(reg).search
        return lambda k, v, p: val_check(v, p) if re_check(k) is not None else None

    def _dict_check(self, jm: JsonModel, model: ModelObject, mpath: str) -> CheckFun:
        """Check a standard object."""

        assert isinstance(model, dict)
        # log.warning(f"{mpath}: {model}")

        must, may, refs, regs, ots = utils.split_object(model, "*")

        # key/value checks functions
        mandatory = {key: self._raw_compile(jm, val, f"{mpath}.{key}") for key, val in must.items()}
        optional = {key: self._raw_compile(jm, val, f"{mpath}.{key}") for key, val in may.items()}

        # other optional properties have key-value check functions
        keyname_checks = {key: self._keyname_val_compile(jm, key, val, mpath)
                          for key, val in refs.items()}
        keyregs_checks = {key: self._keyreg_val_compile(jm, key, val, mpath)
                          for key, val in regs.items()}

        if "" in ots:
            path = mpath + ".''"
            fun = self._raw_compile(jm, ots[""], path)

            def others(k, v, p):  # type: ignore # pyright defect
                return (isinstance(k, str) and fun(v, p) or
                        self._no(path, f"{p}", f"bad property {k}"))
        else:  # reject unexpected properties

            def others(k, _v, p):
                return self._no(mpath, f"{p}", f"unexpected property {k}")

        # function for the actual checking
        # captures mandatory, optional, key_checks, others
        def check_dict(v: Jsonable, p: str) -> bool:

            if not isinstance(v, dict):
                return self._no(mpath, p, "not an object")

            must_see = len(mandatory)

            # check v keys
            for key, val in v.items():
                if key in mandatory:
                    must_see -= 1
                    if not mandatory[key](val, f"{p}.{key}"):
                        # self._no(f"{mpath}.{key}", f"{p}.{key}", "bad mandatory value")
                        return False
                elif key in optional:
                    if not optional[key](val, f"{p}.{key}"):
                        # self._no(f"{mpath}.{key}", f"{p}.{key}", "bad optional value")
                        return False
                else:
                    # else key checks, which return None if unchecked
                    checked = False
                    for k, kc in keyname_checks.items():
                        res = kc(key, val, p)
                        if res is not None:
                            if not res:
                                # self._no(f"{mpath}.{k}", f"{p}.{kc}",
                                #          f"bad name key value for {k}")
                                return False
                            checked = True
                    if not checked:
                        for k, kc in keyregs_checks.items():
                            res = kc(key, val, p)
                            if res is not None:
                                if not res:
                                    # self._no(f"{mpath}.{k}", f"{p}.{kc}",
                                    #          f"bad regex key value for {k}")
                                    return False
                                checked = True
                    # else try catch-all
                    if not checked and not others(key, val, f"{p}.{key}"):
                        return False  # self._no(f"{p}.{key}", "unexpected other property")

            # all mandatory are accounted for?
            if must_see != 0:
                missing = set(mandatory.keys()).difference(v.keys())
                return self._no(mpath, p, f"missing mandatory key: {' '.join(sorted(missing))}")

            return True

        return self.trace(check_dict, mpath, "{*}")

    def _disjunction(self, jm: JsonModel, model: ModelObject, mpath: str) -> CheckFun|None:

        dis = self._disjunct_analyse(jm, model, mpath)
        if dis is None:
            return None
        tag_name, tag_type, models, all_const_props = dis

        # map tag values to value check
        TAG_CHECKS = {}
        for i in range(len(models)):
            model = models[i]
            consts = all_const_props[i]
            TAG_CHECKS[consts[tag_name]] = self._raw_compile(jm, model, f"{mpath}[{i}]")

        mp = mpath + "[*]"

        # actual check function
        def disjunct_check(v, p):
            # log.warning(f"disjunct_check {p}")
            # is there a tag?
            if not isinstance(v, dict):
                return self._no(mp, p, "not an object")
            if tag_name not in v:
                return self._no(mp, p, f"missing tag {tag_name}")
            tag = v[tag_name]
            if type(tag) is not tag_type:
                return self._no(f"{mp}.{tag_name}", f"{p}.{tag_name}",
                                f"bad tag type {tname(tag)} for {tag_type.__name__}")
            if tag not in TAG_CHECKS:
                return self._no(f"{mp}.{tag_name}", f"{p}.{tag_name}",
                                f"unexpected tag {tag_name} value {tag}")

            tag_check = TAG_CHECKS.get(tag)
            assert tag_check
            return tag_check(v, p)

        return self.trace(disjunct_check, mpath, "{δ}")

    def _obj_constraints(self, jm: JsonModel, constraint: ModelObject, ttype: type, mpath: str):
        """Check a constrained type constraints."""
        checks_val, checks_nb = [], []
        has_len = ttype in (str, list, tuple, dict)
        item_filter = None
        for kc, vc in constraint.items():

            if not isinstance(kc, str):
                raise ModelError(f"expecting str keys: {kc}")
            if kc in ("@", "%", "~", "$", "#"):
                continue

            # value constraint type
            tvc = type(vc)

            if kc in self._LENGTH_LAMBDAS:
                if tvc not in (bool, int, float, str):
                    raise ModelError(f"unexpected type for {kc} {ttype}: {tvc} [{mpath}]")
                lmd = self._LENGTH_LAMBDAS[kc]
                path = mpath + "." + kc
                if tvc is int:
                    checks_nb.append(lmd(vc, path))
                elif tvc is str and vc.startswith("$"):
                    checks_nb.append(lmd(int(vc[1:]), path))
                elif ttype is tvc:
                    checks_val.append(lmd(vc, path))
                else:
                    raise ModelError(f"unexpected type for {kc} {ttype}: {tvc} [{mpath}]")
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
            elif kc == "!":
                if not isinstance(vc, bool):
                    raise ModelError(f"unexpected type for distinct: {tname(vc)} [{mpath}]")
                if vc:
                    checks_val.append(self._distinct(mpath + ".!"))
            # OTHERS?
            else:
                raise ModelError(f"unexpected constraint: {kc} [{mpath}]")

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
            elif ttype == UnknownModel:
                # dynamic version
                def nb_check_gen(v, p):
                    lv = len(v) if isinstance(v, (str, list, dict)) else v
                    return all(map(lambda f: f(lv, p), checks_nb))
                checks_val.append(nb_check_gen)
            elif has_len:
                # check length of whatever
                def nb_check_stat(v, p):
                    lv = len(v) if isinstance(v, (str, list, dict)) else v
                    return all(map(lambda f: f(lv, p), checks_nb))
                checks_val.append(nb_check_stat)
            else:
                # just apply on value
                checks_val.append(lambda v, p: all(map(lambda f: f(v, p), checks_nb)))

        # return final check
        if checks_val:
            return self.trace(lambda v, p: all(map(lambda f: f(v, p), checks_val)), mpath, "@")
        else:
            return None

    def _constrained_model_check(self, jm: JsonModel, model: ModelObject, mpath: str) -> CheckFun:
        """Check a constrained type type and constraints."""
        assert isinstance(model, dict) and "@" in model
        vtype = model["@"]
        ttype = type(vtype)
        # FIXME skip: None, bool???
        if ttype not in (bool, type(None), str, int, float, tuple, list, dict):
            raise ModelError(f"unexpected type object value type: {tname(vtype)} [{mpath}]")
        if self._is_vartuple(model):
            # FIXME should skip it in some cases?
            val_check = self._vartuple_check(jm, vtype, mpath + ".@", False)
        else:
            val_check = self._raw_compile(jm, vtype, mpath + ".@")
        # compile constraints
        val_cons = self._obj_constraints(jm, model, ttype, mpath)
        # TODO or no?
        if val_cons:
            return lambda v, p: val_check(v, p) and val_cons(v, p)
        else:
            return val_check

    def _alternate_model_check(self, jm: JsonModel, model: ModelObject, mpath: str) -> CheckFun:
        """Check a or-model |."""
        assert isinstance(model, dict) and "|" in model
        if not set(model.keys()).issubset(["#", "$", "%", "|"]):
            raise ModelError(f"key combination not implemented yet: {model} [{mpath}]")
        mv = model["|"]
        mp = mpath + ".|"
        if not isinstance(mv, (list, tuple)):
            raise ModelError(f"unexpected | alternate value: {mv} ({tname(mv)}) [{mp}]")
        if not mv:  # empty list shortcut
            return self.trace(self._NONE, mpath, "|")
        elif len(mv) == 1:
            return self._raw_compile(jm, mv[0], mp + "[0]")
        # try optimized disjunction
        if check := self._disjunction(jm, model, mp):
            return check
        # else alternate is to try till one matches, in order
        subs = [self._raw_compile(jm, m, f"{mp}[{i}]") for i, m in enumerate(mv)]
        return (self.trace(lambda v, p: any(f(v, p) for f in subs) or
                self._no(mp, p, "no any matched"), mpath, "|"))

    def _conjunctive_model_check(self, jm: JsonModel, model: ModelObject, mpath: str) -> CheckFun:
        """Check a and-model &."""
        assert isinstance(model, dict) and "&" in model
        if not set(model.keys()).issubset(["#", "$", "%", "&"]):
            raise ModelError(f"key combination not implemented yet: {model} [{mpath}]")
        mv = model["&"]
        mp = mpath + ".&"
        if not isinstance(mv, (list, tuple)):
            raise ModelError(f"unexpected & conjonctive value: {mv} (type{mv}) [{mp}]")
        if not mv:  # empty list shortcut
            return self.trace(self._ANY, mpath, "&")
        elif len(mv) == 1:
            return self._raw_compile(jm, mv[0], mp + "[0]")
        # else some work to do
        subs = [self._raw_compile(jm, m, f"{mp}[{i}]") for i, m in enumerate(mv)]
        return self.trace(lambda v, p: self._all(map(lambda f: f(v, p), subs), mp, p), mpath, "&")

    def _exclusive_model_check(self, jm: JsonModel, model: ModelObject, mpath: str) -> CheckFun:
        """Check a xor-model ^."""
        assert isinstance(model, dict) and "^" in model
        if not set(model.keys()).issubset(["#", "$", "%", "^"]):
            raise ModelError(f"key combination not implemented yet: {model} [{mpath}]")
        mv = model["^"]
        mp = mpath + ".^"
        if not isinstance(mv, (list, tuple)):
            raise ModelError(f"unexpected & conjonctive value: {mv} (type{mv}) [{mp}]")

        # fun optimization: duplicate models lead to immediate errors
        dcheck: Callable[[Jsonable, str], bool]|None
        if len(mv) >= 2:

            # detect duplicated (strictly equal) models
            seen, duplicated = [], []
            for m in mv:
                if model_in_models(m, seen):
                    # keep duplicates once
                    if not model_in_models(m, duplicated):
                        duplicated.append(m)
                else:
                    seen.append(m)

            if duplicated:
                # remove duplicated models which are managed independently
                mv = list(filter(lambda m: m not in duplicated, mv))
                # if v matchs a diplicated model, result is False
                fchecks = [self._raw_compile(jm, m, f"{mp}[?]") for m in duplicated]

                def _dcheck(v: Jsonable, p: str):
                    return (not any(f(v, p) for f in fchecks) or
                            self._no(mpath + "[*]", p, "duplicated match in ^"))
                dcheck = _dcheck  # stupid ruff error avoidance
            else:
                dcheck = None
        else:
            dcheck = None

        # disjunction? NO, preprocessor should have turned this case into a |

        # special cases
        if not mv:  # empty list shortcut
            # even if dcheck!
            return self.trace(self._NONE, mpath, "^")
        elif len(mv) == 1:
            fun: CheckFun = self._raw_compile(jm, mv[0], mp + "[0]")  # type: ignore
            if dcheck is not None:
                return lambda v, p: dcheck(v, p) and fun(v, p)  # type: ignore
            else:
                return fun
        elif len(mv) == 2 and "$ANY" in mv:
            #  {"^": ["$ANY", m]} means anything "not m"
            model = mv[1] if mv[0] == "$ANY" else mv[0]
            check = self._raw_compile(jm, model, f"{mp}[?]")
            return lambda v, p: (not check(v, p) or
                                 self._no(f"{mp}[?]", p, "model inversion (not with $ANY)"))

        # else standard case
        subs = [self._raw_compile(jm, m, f"{mp}[{i}]") for i, m in enumerate(mv)]

        def fun(v, p):
            return self._one(map(lambda f: f(v, p), subs), mp, p)

        # we try dcheck (shortcut), else we try the remaining models
        return self.trace((lambda v, p: dcheck(v, p) and fun(v, p)) if dcheck else fun, mpath, "^")

    def _none_raw_compile(self, model: None, mpath: str) -> CheckFun:
        """Compile null."""
        return lambda v, p: v is None or self._no(mpath, p, "expecting null")

    def _bool_raw_compile(self, model: bool, mpath: str) -> CheckFun:
        """Compile a boolean."""
        return lambda v, p: isinstance(v, bool) or self._no(mpath, p, "expecting a boolean")

    def _int_raw_compile(self, model: int, mpath: str) -> CheckFun:
        """Compile a number (int)."""
        # NOTE beware that isinstance(true, int) == True
        assert isinstance(model, int)

        # loose int?
        if self._loose_int:
            def is_an_int(v, p) -> bool:
                return (type(v) in (int, float) and v == int(v)) or \
                    self._no(mpath, p, "expecting a (loose) integer")
        else:
            def is_an_int(v, p) -> bool:
                return type(v) is int or self._no(mpath, p, "expecting an integer")

        # signed int?
        if model == -1:
            check = is_an_int
        elif model == 0:
            def check(v, p):
                return (is_an_int(v, p) and
                        (v >= 0 or self._no(mpath, p, "int must be positive")))
        elif model == 1:
            def check(v, p):
                return (is_an_int(v, p) and
                        (v > 0 or self._no(mpath, p, "int must be strictly positive")))
        else:
            check = is_an_int

        return check

    def _float_raw_compile(self, model: float, mpath: str) -> CheckFun:
        """Compile a number (float)."""
        assert isinstance(model, float)
        # NOTE does not handle NaN, +-Infinity
        # NOTE beware that isinstance(True, int) == True
        assert model in (0.0, 1.0, -1.0)
        if self._loose_float:
            if model == -1.0:
                return lambda v, p: type(v) in (float, int) or self._no(mpath, p, "expecting a number")
            elif model == 0.0:
                return lambda v, p: type(v) in (float, int) and v >= 0.0 or self._no(mpath, p, "expecting a positive number")
            else:
                return lambda v, p: type(v) in (float, int) and v > 0.0 or self._no(mpath, p, "expecting a strictly positive number")
        else:
            if model == -1.0:
                return lambda v, p: type(v) == float or self._no(mpath, p, "expecting a number")
            elif model == 0.0:
                return lambda v, p: type(v) == float and v >= 0.0 or self._no(mpath, p, "expecting a positive number")
            else:
                return lambda v, p: type(v) == float and v > 0.0 or self._no(mpath, p, "expecting a strictly positive number")

    def _str_raw_compile(self, jm: JsonModel, model: str, mpath: str) -> CheckFun:
        """Compile a string."""
        if model == "":
            return lambda v, p: isinstance(v, str) or self._no(mpath, p, "expecting a string")
        # handle char prefix
        char, name = model[0], model[1:]
        if char == "=":
            # special constants
            if name == "true":
                return lambda v, p: (isinstance(v, bool) and v or
                                     self._no(mpath, p, "expecting boolean true"))
            elif name == "false":
                return lambda v, p: (isinstance(v, bool) and not v or
                                     self._no(mpath, p, "expecting boolean false"))
            elif name == "null":
                return lambda v, p: v is None or self._no(mpath, p, "expecting null")
            elif re.search("^-?[0-9]+$", name):
                val = int(name)
                return lambda v, p: (type(v) is int and v == val or
                                     self._no(mpath, p, f"expecting integer {val}"))
            else:
                try:
                    val = float(name)
                    return lambda v, p: (type(v) in (int, float) and v == val or
                                         self._no(mpath, p, f"expecting number {val}"))
                except Exception:
                    raise ModelError(f"unexpected str constant: {name} [{mpath}]")
        elif char == "$":
            if len(model) == 1:
                raise ModelError(f"unexpected str model: {model} [{mpath}]")
            else:
                fun = self._ref2fun(jm, model, mpath)
                return lambda v, p: fun(v, p) or self._no(mpath, p, f"{model} failed")
        elif char == "_":
            return lambda v, p: (isinstance(v, str) and v == name or
                                 self._no(mpath, p, f"expecting string {name}"))
        elif char == "/":  # regular expression /.../i?
            if model.endswith("/i"):
                option = re.IGNORECASE
                regex = model[1:-2]
            elif model.endswith("/"):
                option = 0
                regex = model[1:-1]
            else:
                raise ModelError(f"invalid regex: {model} [{mpath}]")
            check_re = re.compile(regex, option).search
            return lambda v, p: (isinstance(v, str) and check_re(v) is not None or
                                 self._no(mpath, p, f"expecting regex {model}"))
        else:
            return lambda v, p: (isinstance(v, str) and v == model or
                                 self._no(mpath, p, f"expecting string {model}"))

    def _list_raw_compile(self, jm: JsonModel, model: ModelArray, mpath: str) -> CheckFun:
        """Compile an array."""
        nmodels = len(model)
        if nmodels == 1:
            return self._list_check(jm, model[0], mpath)
        else:
            return self._tuple_check(jm, model, mpath)

    def _dict_raw_compile(self, jm: JsonModel, model: ModelObject, mpath: str, is_root: bool = False) -> CheckFun:
        """Compile a generic element."""

        # special properties redundant sanity check
        if "#" in model:
            if not isinstance(meta := model["#"], str):
                raise ModelError(f"unexpected # value: {meta} ({tname(meta)}) [{mpath}.#]")
        if "~" in model and not is_root:
            raise ModelError(f"unexpected ~ not at root [{mpath}.~]")
        if "$" in model and not is_root:
            raise ModelError(f"unexpected $ not at root [{mpath}.$]")
        if "%" in model and not is_root:
            raise ModelError(f"unexpected % not at root [{mpath}.%]")

        # classes
        if "@" in model:
            check = self._constrained_model_check(jm, model, mpath)
        elif "|" in model:
            check = self._alternate_model_check(jm, model, mpath)
        elif "&" in model:
            check = self._conjunctive_model_check(jm, model, mpath)
        elif "^" in model:
            check = self._exclusive_model_check(jm, model, mpath)
        elif "+" in model:
            raise ModelError("+ operator must be resolved before compilation [{mpath}.+]")
        else:
            check = self._dict_check(jm, model, mpath)

        return check

    def _raw_compile(self, jm: JsonModel, model: ModelType, mpath: str, is_root: bool = False) -> CheckFun:
        """Dynamic "compilation" of a model."""
        # static switch on model type
        tmodel = type(model)
        if tmodel is type(None):
            return self._none_raw_compile(model, mpath)
        elif tmodel is bool:
            return self._bool_raw_compile(model, mpath)
        elif tmodel is int:
            return self._int_raw_compile(model, mpath)
        elif tmodel is float:
            return self._float_raw_compile(model, mpath)
        elif tmodel is str:
            return self._str_raw_compile(jm, model, mpath)
        elif tmodel in (list, tuple):
            return self._list_raw_compile(jm, model, mpath)
        elif tmodel is dict:
            return self._dict_raw_compile(jm, model, mpath, is_root)
        else:
            raise ModelError(f"unexpected model type {tname(model)}: {model} [{mpath}]")
