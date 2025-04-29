#! /bin/env python

# NOTE on false the system should say *why*

from typing import Callable, Any
try:
    import re2 as re
    is_re2 = True
except ModuleNotFoundError:
    import re
    is_re2 = False
import json
import argparse
import logging

from . import utils
from .utils import ValueType, ModelType, ModelError, distinct_values, log
from .defines import Validator


def _is_really_int(v):
    """Python allucinates booleans as integers…"""
    return isinstance(v, int) and not isinstance(v, bool)


_ANYWHERE_KW: set[str] = {"#", "$", "%"}
_CONSTRAINT_KW: set[str] = {"@", "<", "<=", "=", "!=", ">", ">=", "!"}


# TODO rename class
class DSV(Validator):
    """Data Structure Validator Evaluator."""

    def __init__(self):

        super().__init__()

        # per-type recursion
        self._type: dict[type, Callable[[ValueType, ModelType, bool], bool]] = {
            type(None): lambda v, _, _s: v is None,
            bool: lambda v, _, _s: isinstance(v, bool),
            int: self._int,
            float: lambda v, _, _s: type(v) in (int, float),
            str: self._str,
            list: self._list,
            tuple: self._list,
            dict: self._dict,
        }

        # defined "<name>": check_value_fun(v)
        self.set("ANY", lambda _, _p: True, "<ANY>")
        self.set("NONE", lambda _, _p: False, "<NONE>")
        self.set("REGEX", utils.is_regex, "<REGEX>")
        self.set("URI", lambda s, _p: isinstance(s, str), "<URI>")
        self.set("URL-REFERENCE", lambda s, _p: isinstance(s, str), "<URL-REFERENCE>")
        self.set("STRING", lambda s, _p: isinstance(s, str), "<STRING>")
        self.set("BOOL", lambda b, _p: isinstance(b, bool), "<BOOL>")

    def _int(self, value: ValueType, model: ModelType, _strict: bool = True):
        assert _is_really_int(model)
        if not _is_really_int(value):
            return False
        assert isinstance(value, (int, float))  # redundant type hint
        if model == 0:
            return value >= 0
        elif model == 1:
            return value >= 1
        elif model == -1:
            return True
        else:
            raise ModelError(f"unexpected int model: {model}")

    def _dollar(self, name: str, val: ValueType) -> bool:
        """Handle "$name"."""
        if name not in self._defs:
            raise ModelError(f"unexpected name: {name}")
        dfun = self._defs[name]
        return dfun(val, "")  # type: ignore

    def _follow_references(self, model):
        while isinstance(model, str) and model and model[0] == "$":
            model = self._defs.model(model[1:])
        return model

    def _dict_constraint(self, value: ValueType, model: ModelType) -> bool:
        assert isinstance(model, dict) and "@" in model
        assert set(model.keys()).issubset(_ANYWHERE_KW | _CONSTRAINT_KW)
        #
        submodel = model["@"]
        # what are the expected submodels?
        assert type(submodel) in (type(None), bool, int, float, str, list, tuple, dict), \
            f"unexpected expanded model: {submodel}"
        # first, check type
        if not self.check(value, submodel, strict=False):
            return False
        # then check constraints
        has_nb = False
        # if "in" in model:
        #     assert type(submodel) in (str, list, tuple)
        #     imodel = model["in"]
        #     ivalue, has_nb = 0, True
        #     for v in value:
        #         if self.check(v, imodel):
        #             ivalue += 1
        # FIXME the logic is broken!
        if submodel == "$ANY":  # FIXME handle $ here?
            ivalue = None
        elif isinstance(value, int):
            ivalue, has_nb = value, True
        elif type(submodel) in (list, tuple, dict, str):
            ivalue, has_nb = len(value), True  # type: ignore
        else:
            ivalue = None
        # handle numeric operators
        if "=" in model:
            val = model["="]
            if has_nb and _is_really_int(val):
                if not ivalue == val:
                    return False
            elif type(val) is type(value):
                if not value == val:
                    return False
            else:
                return False
        if "!=" in model:
            val = model["!="]
            if has_nb and _is_really_int(val):
                if not ivalue != val:
                    return False
            elif type(val) is type(value):
                if not value != val:
                    return False
            else:
                return False
        if "<=" in model:
            val = model["<="]
            if has_nb and _is_really_int(val):
                if not ivalue <= val:  # pyright: ignore
                    return False
            elif type(val) is type(value):
                if not value <= val:  # pyright: ignore
                    return False
            else:
                return False
        if "<" in model:
            val = model["<"]
            if has_nb and _is_really_int(val):
                if not ivalue < val:  # pyright: ignore
                    return False
            elif type(val) is type(value):
                if not value < val:  # pyright: ignore
                    return False
            else:
                return False
        if ">=" in model:
            val = model[">="]
            if has_nb and _is_really_int(val):
                if not ivalue >= val:  # pyright: ignore
                    return False
            elif type(val) is type(value):
                if not value >= val:  # pyright: ignore
                    return False
            else:
                return False
        if ">" in model:
            val = model[">"]
            if has_nb and _is_really_int(val):
                if not ivalue > val:  # pyright: ignore
                    return False
            elif type(val) is type(value):
                if not value > val:  # pyright: ignore
                    return False
            else:
                return False
        # if "mo" in model:
        #     val = model["mo"]
        #     if value % val != 0:
        #         return False
        # if "re" in model and not re.search(model["re"], value):
        #     return False
        # if "prop" in model:
        #     assert isinstance(model["prop"], str)
        #     assert isinstance(value, (list, tuple, str)), "distinct on iterables"
        #     if model["prop"] == "distinct" and not distinct_values(value):
        #         return False
        #     if model["prop"] == "invalid":
        #         return False
        if "!" in model:
            assert isinstance(model["!"], bool), "expecting a boolean value"
            assert isinstance(value, (list, tuple, str)), "distinct on iterables"
            if model["!"] and not distinct_values(value):
                return False
        return True

    def _object_value_model_check(self, value, must, may, maybe, regex, others) -> bool:

        # for checking that all mandatory props are there
        must_see = len(must)

        # test all value properties
        value_keys = list(value.keys())  # FIXME why? someone changes the value??
        for key in value_keys:
            val = value[key]

            if not isinstance(key, str):
                return False
            elif key in must:
                must_see -= 1
                if not self.check(val, must[key]):
                    return False
            elif key in may:
                if not self.check(val, may[key]):
                    return False
            else:
                # first, try maybes
                checked = False
                for name in maybe:
                    assert name in self._defs
                    if self._defs[name](key, ""):  # type: ignore
                        checked = True
                        if not self.check(val, maybe[name]):
                            return False
                        break
                # then regex
                if not checked:
                    for r in regex:
                        if re.match(r, key):
                            checked = True
                            if not self.check(val, regex[r]):
                                return False
                            break
                # then others
                if not checked:
                    # try catch all case
                    if others:
                        if not self.check(val, others[""]):
                            return False
                    else:
                        # unexpected property name
                        return False

        # all properties and values are checked

        # return whether all mandatory properties were seen
        return must_see == 0

    def _dict(self, value: ValueType, model: ModelType, _strict: bool = True) -> bool:
        """Handle an object model."""
        assert isinstance(model, dict)

        # TODO check for specials and consistency
        # log.debug(f"object: value={value}, model={model}")
        # FIXME should it be : instead? something else?
        if "$" in model:
            # FIXME should clean afterwards!?
            assert isinstance(model["$"], str), f"illegal model name: {model['$']}"
            self.set(model["$"], model)
        if "%" in model:
            # model local definitions
            assert isinstance(model["%"], dict), f"illegal %-definitions: {model['%']}"
            for name, mod in model["%"].items():
                assert isinstance(name, str)
                self.set(name, mod, f"$.%.{name}")
        if "#" in model:
            # ignore metadata
            pass
        # variants
        if "|" in model:
            # special disjonctive case
            assert set(model.keys()).issubset({"$", "%", "#", "|"})
            assert isinstance(model["|"], (list, tuple)), f"illegal disjunction: {model['|']}"
            # return on first match
            for m in model["|"]:
                # log.warning(f"{value}/{m}")
                if self.check(value, m):
                    return True
            return False
        elif "&" in model:
            # NOTE empty accepts anything…
            assert set(model.keys()).issubset({"$", "%", "#", "&"})
            assert isinstance(model["&"], (list, tuple)), f"illegal conjunction: {model['&']}"
            # return on first fail
            for m in model["&"]:
                if not self.check(value, m):
                    return False
            return True
        elif "^" in model:
            # NOTE empty accepts anything…
            assert set(model.keys()).issubset({"$", "%", "#", "^"})
            assert isinstance(model["^"], (list, tuple)), f"illegal disjunction: {model['^']}"
            # return on second success
            seen = False
            for m in model["^"]:
                log.warning(f"model={m} value={value}")
                if self.check(value, m):
                    if seen:
                        return False
                    seen = True
            return seen
        elif "+" in model:
            raise ModelError("+ operator must be resolved before validation")
        elif "@" in model:
            return self._dict_constraint(value, model)
        #
        # ELSE standard object
        #
        if not isinstance(value, dict):
            return False

        # NOTE this is not very efficient :-(
        props = utils.split_object(model, ["*"])

        return self._object_value_model_check(value, *props)

    def _list(self, value: ValueType, model: ModelType, strict: bool = True) -> bool:
        """Validate value wrt a list or tuple model."""
        assert isinstance(model, (list, tuple))
        if not isinstance(value, (list, tuple)):
            return False
        # empty list case
        if len(model) == 0:
            return len(value) == 0
        # check tuple length if necessary
        if strict and len(model) > 1 and len(model) != len(value):
            return False
        # size is checked, just look at list items
        for i in range(len(value)):
            imodel = model[i] if i < len(model) else model[-1]
            if not self.check(value[i], imodel):
                return False
        return True

    # per root type checkers
    def _str(self, value: ValueType, model: ModelType, strict: bool = True) -> bool:
        """Validate value wrt a string model."""
        assert isinstance(model, str)
        log.debug("string check with {model}")
        if not model:  # empty string
            return isinstance(value, str)
        else:
            c, name = model[0], model[1:]
            if c == "$":
                return self._dollar(name, value)
            elif c == "_":
                return isinstance(value, str) and name == value
            elif c == "/":
                if name.endswith("/"):
                    return isinstance(value, str) and re.search(name[:-1], value) is not None
                elif name.endswith("/i"):
                    pattern = name[:-2]
                    if is_re2:
                        pattern = "(?i)" + pattern
                        return isinstance(value, str) and re.search(pattern, value) is not None
                    else:
                        return (isinstance(value, str) and
                                re.search(pattern, value, re.I) is not None)  # type: ignore
                else:
                    raise ModelError(f"invalid regex: {model}")
            elif c == "=":
                if name == "null":
                    return value is None
                elif name == "true":
                    return isinstance(value, bool) and value
                elif name == "false":
                    return isinstance(value, bool) and not value
                elif re.match(r"^[0-9]+$", name):
                    return isinstance(value, int) and value == int(name)
                else:
                    return isinstance(value, (int, float)) and value == float(name)
            elif re.match(r"^[A-Za-z0-9]", c):
                return isinstance(value, str) and model == value
            else:
                raise ModelError(f"unexpected sentinel character: {c} ({model})")

    def check(self, value: Any, model: Any, strict: bool = True) -> bool:
        """Recursive type checker."""
        # FIXME ???
        defs = {k: self._defs.model(k) for k in self._defs._models.keys()}
        return self._type[type(model)](value, model, strict)

    def set(self, ident: str, model: Callable[[Any], bool]|Any, mpath: str = ""):
        """Extend validator with a new definition."""
        self._defs.set(ident, model, mpath)  # type: ignore

#
# check some json files against a model
#
# usage: $0 model.json file.json …
#


def v_check_model():

    logging.basicConfig()

    ap = argparse.ArgumentParser()
    ap.add_argument("--debug", "-d", action="store_true", help="debug mode")
    ap.add_argument("model", help="model to check")
    ap.add_argument("values", nargs="*", help="JSON values files to check")
    args = ap.parse_args()

    log.setLevel(logging.DEBUG if args.debug else logging.INFO)

    log.debug("debugging mode…")

    with open(args.model) as f:
        model = json.load(f)

    validator = DSV()

    for fn, fh in utils.openfiles(args.values):
        valid = False
        try:
            m = json.load(fh)
            valid = validator.check(m, model)
            print(f"{fn}: {valid}")
        except Exception as e:
            log.error(f"{fn}: {e}")
