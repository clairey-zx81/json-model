#! /bin/env python

# NOTE on false the system should say *why*

from typing import Callable
try:
    import re2 as re
except ModuleNotFoundError:
    import re
import logging

import utils
from utils import ValueType, ModelType, ModelError, ModelDefs, distinct_values

logging.basicConfig()
log = logging.getLogger("dsv")
#log.setLevel(logging.DEBUG)
log.setLevel(logging.INFO)

# TODO rename class
class DSV:
    """Data Structure Validator Evaluator."""

    def __init__(self):

        # per-type recursion
        self._type: dict[type, Callable[[ValueType, ModelType, bool], bool]] = {
            type(None): lambda v, _, _s: v is None,
            bool: lambda v, _, _s: isinstance(v, bool),
            int: lambda v, _, _s: type(v) == int,
            float: lambda v, _, _s: type(v) in (int, float),
            str: self._str,
            list: self._list,
            tuple: self._list,
            dict: self._dict,
        }

        # defined "<name>": check_value_fun(v)
        self._defs = ModelDefs(compiler=lambda m: lambda v: self.check(v, m))
        self.set("any", lambda _: True)
        self.set("none", lambda _: False)
        self.set("regex", utils.is_regex)
        self.set("uri", lambda s: isinstance(s, str))
        self.set("uri-reference", lambda s: isinstance(s, str))

    def _dollar(self, name: str, val: ValueType) -> bool:
        """Handle "$name"."""
        if name in self._defs:
            return self._defs[name](val)
        elif name == "true":
            return isinstance(val, bool) and val
        elif name == "false":
            return isinstance(val, bool) and not val
        elif re.match(r"^\d+$", name):
            return type(val) == int and val == int(name)
        else:
            raise ModelError(f"unexpected name: {name}")

    def _dict_constraint(self, value: ValueType, model: ModelType) -> bool:
        assert "@" in model
        assert set(model.keys()).issubset({"$", "%", "#", "@", "eq", "ne", "lt", "le", "gt", "ge", "re", "in", "mo", "prop"})
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
        if "in" in model:
            assert type(submodel) in (str, list, tuple)
            imodel = model["in"]
            ivalue, has_nb = 0, True
            for v in value:
                if self.check(v, imodel):
                    ivalue += 1
        elif submodel == "$any":  # FIXME handle $ here?
            ivalue = None
        elif type(submodel) in (list, tuple, dict, str):
            ivalue, has_nb = len(value), True
        else:
            ivalue = None
        # handle numeric operators
        if "eq" in model:
            val = model["eq"]
            if has_nb and type(val) == int:
                if not ivalue == val:
                    return False
            elif type(val) == type(value):
                if not value == val:
                    return False
            else:
                return False
        if "ne" in model:
            val = model["ne"]
            if has_nb and type(val) == int:
                if not ivalue != val:
                    return False
            elif type(val) == type(value):
                if not value != val:
                    return False
            else:
                return False
        if "le" in model:
            val = model["le"]
            if has_nb and type(val) == int:
                if not ivalue <= val:
                    return False
            elif type(val) == type(value):
                if not value <= val:
                    return False
            else:
                return False
        if "lt" in model:
            val = model["lt"]
            if has_nb and type(val) == int:
                if not ivalue < val:
                    return False
            elif type(val) == type(value):
                if not value < val:
                    return False
            else:
                return False
        if "ge" in model:
            val = model["ge"]
            if has_nb and type(val) == int:
                if not ivalue >= val:
                    return False
            elif type(val) == type(value):
                if not value >= val:
                    return False
            else:
                return False
        if "gt" in model:
            val = model["gt"]
            if has_nb and type(val) == int:
                if not ivalue > val:
                    return False
            elif type(val) == type(value):
                if not value > val:
                    return False
            else:
                return False
        if "mo" in model:
            val = model["mo"]
            if value % val != 0:
                return False
        if "re" in model and not re.search(model["re"], value):
            return False
        if "prop" in model:
            assert isinstance(model["prop"], str)
            assert isinstance(value, (list, tuple, str)), "distinct on iterables"
            if model["prop"] == "distinct" and not distinct_values(value):
                return False
            if model["prop"] == "invalid":
                return False
        return True

    def _object_value_model_check(self, value, must, may, maybe, others) -> bool:

        # for checking that all mandatory props are there
        must_see = len(must)

        # test all value properties
        for key, val in value.items():

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
                    if self._defs[name](key):
                        checked = True
                        if not self.check(val, maybe[name]):
                            return False
                        break
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

    def _dict(self, value: ValueType, model: ModelType, _strict: bool=True) -> bool:
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
            assert isinstance(model["%"], dict), f"illegal :-definitions: {model[':']}"
            for name, mod in model["%"].items():
                assert isinstance(name, str)
                self.set(name, mod)
            # FIXME after cleanup?
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
            assert isinstance(model["^"], (list, tuple)), f"illegal conjunction: {model['^']}"
            # return on second success
            seen  = False
            for m in model["^"]:
                if self.check(value, m):
                    if seen:
                        return False
                    seen = True
            return seen
        elif "+" in model:
            assert set(model.keys()).issubset({"$", "%", "#", "+"})
            models = model["+"]
            assert isinstance(models, (list, tuple)), f"illegal addition: {models}"
            # very costly: object models are merged on each comparison...
            return self.check(value, utils.merge_simple_models(models))

            # raise ModelError("additive model not implemented yet")
        elif "@" in model:
            return self._dict_constraint(value, model)
        #
        # ELSE standard object
        #
        if not isinstance(value, dict):
            return False

        # NOTE this is not very efficient :-(
        props = utils.split_object(model)

        return self._object_value_model_check(value, *props)

    def _list(self, value: ValueType, model: ModelType, strict: bool=True) -> bool:
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
    def _str(self, value: ValueType, model: ModelType, strict: bool=True) -> bool:
        """Validate value wrt a string model."""
        assert isinstance(model, str)
        if not model:  # empty string
            return isinstance(value, str)
        else:
            c, name = model[0], model[1:]
            if c == "$":
                return self._dollar(name, value)
            elif c == "_":
                return isinstance(value, str) and name == value
            else:
                return isinstance(value, str) and model == value

    def check(self, value: any, model: any, strict: bool=True) -> bool:
        """Recursive type checker."""
        return self._type[type(model)](value, model, strict)

    def set(self, ident: str, model: Callable[[any], bool] | any):
        """Extend validator with a new definition."""
        #if ident in self._defs:
        #    log.warning(f"overriding {ident} previous definition")
        self._defs[ident] = model if callable(model) else lambda v: self.check(v, model)
