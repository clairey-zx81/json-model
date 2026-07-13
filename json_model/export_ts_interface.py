#
# Generate typescript interface from model definitions
#

import re
from collections.abc import Collection
import json

from .model import JsonModel
from .language import Block
from .mtypes import ModelType
from .predefs import INT_MODEL_PREDEFS, FLOAT_MODEL_PREDEFS, BOOL_MODEL_PREDEFS

_IDENT = re.compile(r"[A-Za-z_$][\w$]*$")
_TS_RESERVED = [
      # ECMAScript reserved words
      "break", "case", "catch", "class", "const", "continue", "debugger",
      "default", "delete", "do", "else", "enum", "export", "extends",
      "false", "finally", "for", "function", "if", "import", "in",
      "instanceof", "new", "null", "return", "super", "switch", "this",
      "throw", "true", "try", "typeof", "var", "void", "while", "with",
      # reserved in strict mode / modules
      "await", "implements", "interface", "let", "package", "private",
      "protected", "public", "static", "yield",
      # TypeScript primitive type names — TS2457
      "any", "bigint", "boolean", "never", "number", "object",
      "string", "symbol", "undefined", "unknown",
 ]

def ts_name(name: str) -> str:
    safe = re.sub(r"\W", "_", name)
    if not _IDENT.match(safe) or safe in _TS_RESERVED:
        safe = "JM_" + safe
    return safe

def _unwrap(model: ModelType) -> ModelType:
    while isinstance(model, dict) and "@" in model:
        model = model["@"]
    return model

def _is_operator(model: ModelType) -> bool:
    return isinstance(model, dict) and any(op in model for op in ("|", "^", "&", "+"))

def _combine(name: str, members: list, sep: str, empty: str,
             def_keys: Collection[str]) -> tuple[str, Block]:
    parts: list[str] = []
    hoisted: Block = []
    for i, alt in enumerate(members):
        t, extra = field_type(f"{name}_{i}", alt, def_keys)
        parts.append(t)
        hoisted += extra
    uniq = list(dict.fromkeys(parts))
    if not uniq:
        return empty, hoisted
    if len(uniq) == 1:
        return uniq[0], hoisted
    return "(" + f" {sep} ".join(uniq) + ")", hoisted

def m2type(model: ModelType, def_keys: Collection[str]) -> str | None:
    if model is None:
        return "null"
    if isinstance(model, bool):
        return "boolean"
    if isinstance(model, (int, float)):
        return "number"
    if isinstance(model, str):
        if len(model) > 0 and model[0] == "$":
            if model == "$NULL":
                return "null"
            if model == "$ANY":
                return "any"
            if model == "$NONE":
                return "never"
            if model in BOOL_MODEL_PREDEFS:
                return "boolean"
            if model in INT_MODEL_PREDEFS | FLOAT_MODEL_PREDEFS:
                return "number"
            if model[1:] in def_keys:
                return ts_name(model[1:])
            return "string"
        if model.startswith("="):
            return model[1:]
        if model.startswith("_"):
            return json.dumps(model[1:])
        return "string"
    return None

def field_type(name: str, model: ModelType, def_keys: Collection[str]) -> tuple[str, Block]:
    model = _unwrap(model)
    if isinstance(model, dict):
        if "|" in model or "^" in model:
            return _combine(name, model.get("|", model.get("^")), "|", "never", def_keys)
        if "&" in model or "+" in model:
            return _combine(name, model.get("&", model.get("+")), "&", "any", def_keys)

        return ts_name(name), m2ts(name, model, def_keys) + [""]
    if isinstance(model, list):
        cells = [c for c in model if not (isinstance(c, str) and c.startswith("#"))]
        if len(cells) == 1:

            t, extra = field_type(name, cells[0], def_keys)
            return f"{t}[]", extra

        parts: list[str] = []
        hoisted: Block = []
        for i, cell in enumerate(cells):
            t, extra = field_type(f"{name}_{i}", cell, def_keys)
            parts.append(t)
            hoisted += extra
        return "[" + ", ".join(parts) + "]", hoisted
    return m2type(model, def_keys) or "any", []

def m2ts(name: str, model: ModelType, def_keys: Collection[str]) -> Block:
    model = _unwrap(model)
    code: Block = []
    if isinstance(model, dict) and not _is_operator(model):
        hoisted: Block = []
        code += [f"export interface {ts_name(name)} {{"]
        for key, jm in model.items():
            optional = key.startswith("?")
            field = key[1:] if key[:1] in "?!_" else key
            safe = ts_name(field)            
            ftype, extra = field_type(f"{name}_{safe}", jm, def_keys)
            hoisted += extra
            prop = field if _IDENT.match(field) else '"' + field + '"'
            code += [f"\t{prop}{'?' if optional else ''}: {ftype}"]
        code += ["}"]
        code = hoisted + code
    else:
        base = f"{name}_item" if isinstance(model, list) else name
        ftype, extra = field_type(base, model, def_keys)
        code = extra + [f"export type {ts_name(name)} = {ftype}"]

    return code

def model2tsinterface(model: JsonModel, root: str|None = "RootModel") -> Block:
    code: Block = []
    def_keys = model._defs.keys()
    for name, jm in model._defs.items():
        code = m2ts(name, jm._model, def_keys) + code

    if root is not None:
        code = code + [""] + m2ts(root, model._model, def_keys)

    return code
