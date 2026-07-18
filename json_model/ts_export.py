#
# Generate typescript interface from model definitions
#

import re
from collections.abc import Collection
import json

from .model import JsonModel
from .language import Block
from .mtypes import ModelType, ModelError
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

def _check_name_collisions(names: Collection[str], context: str) -> None:
    seen: dict[str, str] = {}
    for name in names:
        safe = ts_name(name)
        if safe in seen and seen[safe] != name:
            raise ModelError(
                f"Typescript name collision in {context}: "
                f"{seen[safe]!r} and {name!r} both map to indentifier {safe!r}"
            )
        seen[safe] = name

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

def _comment(model: ModelType) -> str | None:
    if isinstance(model, dict):
        meta = model.get("#")
        if isinstance(meta, str) and meta:
            return meta
    return None

def _comment_block(text: str, indent: str = "") -> Block:
    lines = text.split("\n")
    if len(lines) == 1:
        return [f"{indent}/* {lines[0]} */"]
    return [f"{indent}/*"] + [f"{indent} * {ln}" for ln in lines] + [f"{indent} */"]

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
        props = {k: v for k, v in model.items() if k != "#"}
        fields = [key[1:] if key[:1] in "?!_" else key for key in props]
        _check_name_collisions(fields, f"object {name!r}")
        hoisted: Block = []
        doc = _comment(model)
        code += _comment_block(doc) if doc else []
        code += [f"export interface {ts_name(name)} {{"]
        catch_all_solo = list(props) == [""]
        for key, jm in props.items():
            optional = key.startswith("?")
            field = key[1:] if key[:1] in "?!_" else key
            safe = ts_name(field)
            if key == "":
                if catch_all_solo:
                    ftype, extra = field_type(f"{name}_{safe}", jm, def_keys)
                    hoisted += extra
                else:
                    ftype = "any"
                code += [f"\t[key: string]: {ftype}"]
                continue

            ftype, extra = field_type(f"{name}_{safe}", jm, def_keys)
            hoisted += extra
            prop = field if _IDENT.match(field) else json.dumps(field)
            code += [f"\t{prop}{'?' if optional else ''}: {ftype}"]
        code += ["}"]
        code = hoisted + code
    else:
        base = f"{name}_item" if isinstance(model, list) else name
        ftype, extra = field_type(base, model, def_keys)
        code = extra + [f"export type {ts_name(name)} = {ftype}"]
        doc = _comment(model)
        if doc:
            code = _comment_block(doc) + code

    return code

def model2tsinterface(model: JsonModel, root: str|None = "RootModel") -> Block:
    def_keys = model._defs.keys()
    _check_name_collisions(def_keys, "definitions ($)")
    blocks: list[Block] = []
    for name, jm in model._defs.items():
        blocks.insert(0, m2ts(name, jm._model, def_keys))
    if root is not None:
        blocks.append(m2ts(root, model._model, def_keys))
    code: Block = []
    for b in blocks:
        if code and b:
            code += [""]
        code += b
    return code
