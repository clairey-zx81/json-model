import re
from .mtypes import ModelType, ModelPath, JsonSchema, Jsonable, Symbols, JsonModel
from .utils import is_cst, cst, log, PREDEF_RE

#
# MODEL TO SCHEMA CONVERSION
#

PREDEF_TYPES = {
    "$STRING": "string",
    "$DATE": "string",
    "$TIME": "string",
    "$DATETIME": "string",
    "$REGEX": "string",
    "$EXREG": "string",
    "$UUID": "string",
    "$JSON": "string",
    "$URL": "string",
    "$URI": "string",
    "$EMAIL": "string",
    "$NUMBER": "number",
    "$BOOL": "boolean",
    "$BOOLEAN": "boolean",
    "$NULL": "null",
    "$INTEGER": "integer",
    "$INT": "integer",
    "$I32": "integer",
    "$I64": "integer",
    "$FLOAT": "number",
    "$F32": "number",
    "$F64": "number",
}

PREDEF_FORMATS = {
    "$DATE": "date",
    "$TIME": "time",
    "$DATETIME": "datetime",
    "$URL": "uri",
    "$REGEX": "regex",
    # not "$EXREG"?
    "$UUID": "uuid",
    "$EMAIL": "email",
    "$URI": "uri",
    # "$JSON": "?",
}

def unExreg(pat: str, opts: str) -> tuple[str, str]:
    """Convert extended regex to standard regex."""
    opts = re.sub("X", "", opts)
    pat = re.sub(r"\(\$\w+:", "(", pat)  # explicit re
    pat = re.sub(r"\$\w+", ".*", pat)    # remaining implicit re
    return pat, opts

def propRefRegex(jm: JsonModel, model: ModelType, path: ModelPath) -> str|None:
    """Try to handle a property refererence in some cases as a regex."""
    if isinstance(model, dict) and "|" in model:
        # try to build a regex
        alts = []
        assert isinstance(model["|"], list)
        for index, alt in enumerate(model["|"]):
            lpath = path + ["|", index]

            # resolve and recurse if needed, with some shortcuts
            changed = True
            while isinstance(alt, str) and changed:
                changed = False
                if alt == "":
                    return ""  # shortcut for default, any strings are ok
                if alt[0] == "$" and alt not in PREDEF_TYPES:
                    ja = jm.resolveRef(alt, path)  # type: ignore
                    alt, changed = ja._model, True

            if not isinstance(alt, str):
                salts = propRefRegex(jm, alt, lpath)
                if salts is not None:
                    if salts == "":
                        return ""
                    else:
                        alts.append(salts)
                        continue
                else:  # let caller do a rough approximation
                    log.debug(f"cannot handle prop ref at {lpath}")
                    return None

            if alt in PREDEF_RE:
                alts.append(PREDEF_RE[alt])
                continue

            # string constant and regex
            if re.match(r"[_a-zA-Z0-9]", alt):
                if alt[0] == "_":
                    alt = alt[1:]
                alt = re.escape(alt)
                alts.append(f"^{alt}$")
            elif alt[0] == "/":
                alt, opts = alt[1:].rsplit("/", 1)
                if "X" in opts:
                    alt, opts = unExreg(alt, opts)
                alts.append(f"(?{opts}){alt}" if opts else alt)
            else:
                log.debug(f"cannot handle prop ref at {lpath}")

        return "(" + "|".join(alts) + ")"
    else:  # not a |
        log.debug(f"cannot handle prop ref at {path}")
        return None

def _m2s(model: ModelType, path: ModelPath, defs: Symbols) -> JsonSchema:
    """Recursive model to schema conversion."""

    schema: Jsonable = {}

    match model:
        case None:
            schema["type"] = "null"
        case bool():
            schema["type"] = "boolean"
        case float():
            schema["type"] = "number"
            if model == 0.0:
                schema["minimum"] = 0.0
            elif model == 1.0:
                schema["exclusiveMinimum"] = 0.0
        case int():
            schema["type"] = "integer"
            # FIXME should check for option?
            if model == 0:
                schema["minimum"] = 0
            elif model == 1:
                schema["minimum"] = 1
        case str():
            if model == "":
                schema["type"] = "string"
            elif model == "$ANY":  # shortcuts
                return True
            elif model == "$NONE":
                return False
            elif model in PREDEF_TYPES:
                schema["type"] = PREDEF_TYPES[model]
                if model in PREDEF_FORMATS:
                    schema["format"] = PREDEF_FORMATS[model]
            elif model[0] == "$":
                if model == "$#":
                    schema["$ref"] = "#"
                elif "/" in model or "." in model:  # probable URL
                    schema["$ref"] = model[1:]
                else:
                    schema["$ref"] = "#/$defs/" + model[1:]
            elif model[0] == "/":
                schema["type"] = "string"
                try:
                    pattern, ropts = model[1:].rsplit("/", 1)
                    assert ropts == "" or ropts.isalpha(), f"invalid regex options: {ropts}"
                    if "X" in ropts:
                        pattern, ropts = unExreg(pattern, ropts)
                    pattern = f"(?{ropts}){pattern}" if ropts else pattern
                except Exception as e:
                    raise Exception(f"invalid regex {model}: {e}")
                schema["pattern"] = pattern
            else:  # _ = …
                schema["const"] = cst(model)
        case list():
            if len(model) == 1:
                schema["type"] = "array"
                schema["items"] = _m2s(model[0], path + [0], defs)
            elif len(model) > 1:
                # tuple: prefixItems/items?
                schema["type"] = "array"
                pitems = []
                for i, item in enumerate(model):
                    pitems.append(_m2s(item, path + [i], defs))
                schema["prefixItems"] = pitems
                schema["items"] = False
                # needed to ensure that all prefix items are there
                schema["minItems"] = len(model)
            else:
                # liste vide : tableau maxItems = 0
                schema["type"] = "array"
                schema["maxItems"] = 0

        case dict():

            # commentaires transformés en "description", "$comment" disponible si besoin
            if "#" in model:
                sharp = model["#"]
                assert isinstance(sharp, str)
                schema["description"] = sharp

            # constraint...
            if "@" in model:
                subschema = _m2s(model["@"], path + ["@"], defs)
                if isinstance(subschema, dict):
                    schema.update(**subschema)
                else:
                    assert isinstance(subschema, bool)
                    if not subschema:
                        # schema["not"] = {}
                        # no matching schema, no point in checking anything further
                        return False
                    # if true, we keep the schema as is
                if "type" in schema:
                    # contraints on string
                    if schema["type"] == "string":
                        if "<=" in model:
                            schema["maxLength"] = model["<="]
                        if ">=" in model:
                            schema["minLength"] = model[">="]
                        if "=" in model:
                            eq = model["="]
                            if isinstance(eq, int):
                                schema["minLength"] = eq
                                schema["maxLength"] = eq
                            elif isinstance(eq, str):
                                schema["const"] = eq
                            else:
                                log.warning(f"ignoring '=' constraint at {path}")
                        if "!=" in model:
                            schema["not"] = {"const": model["!="]}
                        # FIXME extension? remove?
                        # if "mime" in model:
                        #     schema["contentEncoding"] = model["mime"]
                        # if "encoding" in model:
                        #     schema["contentMediaType"] = model["encoding"]
                    # contraints on number or integer
                    if schema["type"] in ("number", "integer"):
                        if "<=" in model:
                            schema["maximum"] = model["<="]
                        if ">=" in model:
                            schema["minimum"] = model[">="]
                        if "<" in model:
                            schema["exclusiveMaximum"] = model["<"]
                        if ">" in model:
                            schema["exclusiveMinimum"] = model[">"]
                        if ".mo" in model:  # model extension
                            schema["multipleOf"] = model[".mo"]
                        if "=" in model:
                            eq = model["="]
                            if isinstance(eq, (int, float)):
                                if "const" in schema:
                                    if schema["const"] != eq:
                                        return False
                                    else:
                                        pass  # redundant
                                else:
                                    schema["const"] = eq
                            elif isinstance(eq, str):
                                return False
                        if "!=" in model:
                            assert "not" not in schema  # FIXME allOf?
                            schema["not"] = {"const": model["!="]}
                    # contraints on object
                    if schema["type"] == "object":
                        if "<=" in model:
                            assert isinstance(model["<="], int)
                            schema["maxProperties"] = model["<="]
                        if "<" in model:
                            assert isinstance(model["<"], int)
                            schema["maxProperties"] = model["<"] - 1
                        if ">=" in model:
                            assert isinstance(model[">="], int)
                            schema["minProperties"] = model[">="]
                        if ">" in model:
                            assert isinstance(model[">"], int)
                            schema["minProperties"] = model[">"] + 1
                        if "=" in model:
                            eq = model["="]
                            if isinstance(eq, int):
                                schema["minProperties"] = eq
                                schema["maxProperties"] = eq
                            else:
                                schema["const"] = eq  # probably infeasible
                        if "!=" in model:
                            assert "not" not in schema  # FIXME allOf?
                            schema["not"] = {"const": model["!="]}
                    # constraints on array
                    if schema["type"] == "array":
                        if ".in" in model:  # model extension
                            schema["contains"] = _m2s(model[".in"], path, defs)
                            if "<=" in model:
                                assert isinstance(model["<="], int)
                                schema["maxContains"] = model["<="]
                            if "<" in model:
                                assert isinstance(model["<"], int)
                                schema["maxContains"] = model["<"] - 1
                            if ">=" in model:
                                assert isinstance(model[">="], int)
                                schema["minContains"] = model[">="]
                            if ">" in model:
                                assert isinstance(model[">"], int)
                                schema["minContains"] = model[">"] + 1
                            # TODO
                        # else:
                        # FIXME check comparison value types!
                        if "<=" in model:
                            assert isinstance(model["<="], int)
                            schema["maxItems"] = model["<="]
                        if "<" in model:
                            assert isinstance(model["<"], int)
                            schema["maxItems"] = model["<"] - 1
                        if ">=" in model:
                            assert isinstance(model[">="], int)
                            schema["minItems"] = model[">="]
                        if ">" in model:
                            assert isinstance(model[">"], int)
                            schema["minItems"] = model[">"] + 1
                        if "!" in model:
                            v = model["!"]
                            assert isinstance(v, bool)
                            if v:
                                schema["uniqueItems"] = True
                else:
                    # no type, maybe because there are several, eg a or/xor
                    # random attempt at supporting some cases…
                    # we could do a better job if we knew here which types are actually possible
                    if ">=" in model and isinstance(model[">="], int):
                        v = int(model[">="])
                        schema["minimum"] = v
                        schema["minLength"] = v
                        schema["minProperties"] = v
                        schema["minItems"] = v
                    if ">" in model and isinstance(model[">"], int):
                        v = int(model[">"])
                        schema["exclusiveMinimum"] = v
                        schema["minLength"] = v + 1
                        schema["minProperties"] = v + 1
                        schema["minItems"] = v + 1
                    if "<=" in model and isinstance(model["<="], int):
                        v = int(model["<="])
                        schema["maximum"] = v
                        schema["maxLength"] = v
                        schema["maxProperties"] = v
                        schema["maxItems"] = v
                    if "<" in model and isinstance(model["<"], int):
                        v = int(model["<"])
                        schema["exclusiveMaximum"] = v
                        schema["maxLength"] = v - 1
                        schema["maxProperties"] = v - 1
                        schema["maxItems"] = v - 1
                    if "=" in model and isinstance(model["="], int):
                        v = int(model["="])
                        schema["minimum"] = v
                        schema["maximum"] = v
                        schema["minLength"] = v
                        schema["maxLength"] = v
                        schema["minProperties"] = v
                        schema["maxProperties"] = v
                        schema["minItems"] = v
                        schema["maxItems"] = v
            # combinations
            elif "&" in model:
                models = model["&"]
                assert isinstance(models, list)  # pyright hint
                schema["allOf"] = [_m2s(m, path + ["&", i], defs) for i, m in enumerate(models)]
            elif "^" in model:
                models = model["^"]
                assert isinstance(models, list)  # pyright hint
                schema["oneOf"] = [_m2s(m, path + ["^", i], defs) for i, m in enumerate(models)]
            elif "|" in model:
                models = model["|"]
                assert isinstance(models, list)
                if all(map(is_cst, models)):  # all choices are constants
                    schema["enum"] = list(map(cst, models))  # pyright: ignore
                else:
                    schema["anyOf"] = [_m2s(m, path + ["|", i], defs)
                                       for i, m in enumerate(models)]
            elif "+" in model:
                assert False, f"+ must have been removed by preprocessing {path + ['+']}"
            else:  # actual object!
                schema["type"] = "object"
                properties, required, addProp = {}, [], False

                # récupérer properties/required
                for prop, val in model.items():
                    assert isinstance(prop, str)
                    lpath = path + [prop]
                    # skip some properties: already managed before
                    if prop in ("~", "#", "$", "%"):
                        continue
                    if prop == "":
                        addProp = _m2s(val, lpath, defs)
                    elif prop[0] in ("_", "!"):
                        required.append(prop[1:])
                        properties[prop[1:]] = _m2s(val, lpath, defs)
                    elif prop[0] == "?":
                        properties[prop[1:]] = _m2s(val, lpath, defs)
                    elif prop[0] == "/":
                        try:
                            pattern, ropts = prop[1:].rsplit("/", 1)
                            assert ropts == "" or ropts.isalpha(), f"invalid regex: {prop}"
                            pattern = f"(?{ropts}){pattern}" if ropts else pattern
                        except Exception as e:
                            raise Exception(f"invalid prop regex {prop}: {e}")
                        if "patternProperties" not in schema:
                            schema["patternProperties"] = {}
                        assert isinstance(schema["patternProperties"], dict)
                        schema["patternProperties"][pattern] = _m2s(val, lpath, defs)
                        if addProp is None:
                            addProp = False
                    elif prop[0] == "$":
                        # NOTE should be ok if simple enough so that constant propagation removed it
                        raise Exception(f"JSON Schema: no support for property ref {prop} at {lpath}")
                    else:  # standard property
                        required.append(prop)
                        properties[prop] = _m2s(val, lpath, defs)

                # merge into schema
                if properties:
                    schema["properties"] = properties
                if required:
                    schema["required"] = required
                if addProp is not None:
                    schema["additionalProperties"] = addProp

            if ".schema" in model:  # model extension, overrides generated stuff
                sub = model[".schema"]
                assert isinstance(sub, dict)
                schema.update(sub)

    # simplify final schema if possible
    if schema == {}:
        schema = True
    elif "not" in schema and schema["not"] == {}:
        if len(schema) == 1:
            schema = False
        else:
            schema["not"] = True

    return schema

def model2schema(model: JsonModel, path: ModelPath, defs: Symbols) -> JsonSchema:
    """Entry point to convert a model to a Schema."""
    return _m2s(model, path, defs)
