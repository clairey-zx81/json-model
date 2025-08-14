#
# Generate pydantic class from model definitions
#
import json
import re

from .mtypes import ModelType
from .language import Block
from .model import JsonModel
from .utils import is_obj_model, log

def ml2type(models: list[ModelType]) -> str|None:
    lpyd = [m2type(m) for m in models]
    if all(map(lambda i: i is not None, lpyd)):
        # all got something
        if any(map(lambda i: " = " in i, lpyd)):  # type: ignore
            # cannot combine constants,
            # let us retry with simpler expectations
            lpyd = [m2type(m, False) for m in models]
            # merge
            lpyd = set(lpyd)
        return "|".join(lpyd)  # type: ignore
    else:
        return "Any"

def m2type(model: ModelType, advanced: bool = True) -> str|None:
    if model is None:
        return "None"
    match model:
        case str(s):
            if s == "":
                return "str"
            elif s[0] == "_":
                return f"str = {json.dumps(s[1:])}" if advanced else "str"
            elif re.match(r"[a-zA-Z]", s):
                return f"str = {json.dumps(s)}" if advanced else "str"
            elif s[0] == "$":
                if s == "$DATE":
                    return "datetime.date" if advanced else "str"
                elif s == "$DATETIME":
                    return "datetime.datetime" if advanced else "str"
                elif s == "$TIME":
                    return "datetime.time" if advanced else "str"
                elif s == "$EMAIL":
                    return "pydantic.EmailStr" if advanced else "str"
                elif s == "$UUID":
                    return "uuid.UUID" if advanced else "str"
                elif s in ("$REGEX", "$EXREG", "$URL", "$URI", "$JSON"):
                    return "str"
                elif s == "$ANY":
                    return "Any"
                elif re.search(r"^\$\w+$", s):
                    return s[1:]
                else:
                    log.info(f"m2type skipping {s}")
                    return None
            elif s[0] == "/":  # a regex is a string
                return "str"
            elif s[0] == "=":
                # constants
                if s == "=null":
                    return "None = None" if advanced else "None"
                elif s == "=true":
                    return "bool = True" if advanced else "bool"
                elif s == "=false":
                    return "bool = False" if advanced else "bool"
                elif "." in s or "e" in s or "E" in s:
                    return f"float = {s[1:]}" if advanced else "float"
                else:
                    return f"int = {s[1:]}" if advanced else "int"
            return None
        case bool():
            return "bool"
        case int(i):
            if i == 1:
                return "pydantic.PositiveInt" if advanced else "int"
            elif i == 0:
                return "pydantic.NonNegativeInt" if advanced else "int"
            return "int"
        case float(f):
            if f == 1.0:
                return "pydantic.PositiveFloat" if advanced else "float"
            if f == 0.0:
                return "pydantic.NonNegativeFloat" if advanced else "float"
            return "float"
        case list(lm):
            if len(lm) == 0:
                return None
            elif len(lm) == 1:
                return f"list[{m2type(lm[0], advanced)}]"
            else:
                lt = [m2type(i) for i in lm]
                if all(map(lambda i: i is not None, lt)):
                    return f"tuple[{', '.join(lt)}]"  # type: ignore
                else:
                    return "list[Any]"
            return None
        case dict(d):
            if "@" in d:
                return m2type(d["@"], advanced)
            if "|" in d or "^" in d:
                lm = d["|" if "|" in d else "^"]
                assert isinstance(lm, list)
                return ml2type(lm)
            if "&" in d:
                # TODO be more precise!
                return "Any"
            # special case for { "": ... }
            if is_obj_model(d, {""}):
                vtype = m2type(d[""], advanced)
                if vtype is not None:
                    return f"dict[str, {vtype}]"
            # nesting
            return None

def m2py(name: str, model: ModelType) -> Block:
    while isinstance(model, dict) and "@" in model:
        model = model["@"]
    if not isinstance(model, dict):
        mtype = m2type(model)
        if mtype is not None:
            if "=" in mtype:  # constant
                return [f"{name}: {mtype}"]
            else:
                return [f"type {name} = {mtype}"]
        return [f"type {name} = Any"]
    if "|" in model  or "^" in model:
        lm = model["|" if "|" in model else "^"]
        assert isinstance(lm, list)
        return [f"type {name} = {ml2type(lm)}  # alt"]
    if "&" in model:
        return [f"type {name} = Any  # &"]

    others: Block = []
    code: Block = [f"class {name}(pydantic.BaseModel):"]
    opt: bool = False
    has_extra: bool = False

    for key, mod in model.items():
        if key == "":
            code.append("    # catchall")
            has_extra = True
            continue

        if key[0] in ("?", "!", "_"):
            opt = key[0] == "?"
            key = key[1:]
        elif key[0] == "/":
            has_extra = True
            code.append(f"    # reg {key}")
            continue
        elif key[0] == "$":
            has_extra = True
            code.append(f"    # ref {key}")
            continue
        elif key[0] == "#":
            # TODO key escaping
            code.append(f"    {key}")  # inline comment
            continue

        if key == "":
            code.append("    # skipping empty name")
            continue

        # TODO check whether key is a valid python identifier
        mtype = m2type(mod)
        if mtype is not None:
            if opt:
                mtype += "|None = None"
            code.append(f"    {key}: {mtype}")
        else:
            # mtype is None, maybe a subobject?
            if isinstance(mod, dict):
                kname = f"{name}_{key}"
                others += m2py(kname, mod) + [""]
                if opt:
                    kname += "|None = None"
                code.append(f"    {key}: {kname}")
            else:
                code.append(f"    # skipping {key}: no type")
    if has_extra:
        code.append("    model_config = pydantic.ConfigDict(extra=\"allow\")")
    return others + code

def model2python(model: JsonModel, root: str|None = "RootModel") -> Block:
    code: Block = [
        "from typing import Any",
        "import uuid",
        "import datetime",
        "import pydantic",
    ]
    for name, jm in model._defs.items():
        code += [""] + m2py(name, jm._model)
    if root is not None:
        code += [""] + m2py(root, model._model)
    return code
