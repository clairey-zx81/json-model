from .mtypes import ModelType, ModelPath, JsonSchema, Jsonable
from .utils import is_cst, cst

#
# MODEL TO SCHEMA CONVERSION
#

PREDEF_TYPES = {
    "$STRING": "string",
    "$DATE": "string",
    "$REGEX": "string",
    "$UUID": "string",
    "$URL": "string",
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
    "$URL": "uri",
    "$REGEX": "regex",
    "$UUID": "uuid",
}

def model2schema(model: ModelType, path: ModelPath = []) -> JsonSchema:
    """Convert model to schema."""

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
            # FIXME should check for option
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
                    pattern = f"(?{ropts}){pattern}" if ropts else pattern
                except Exception as e:
                    raise Exception(f"invalid regex {model}: {e}")
                schema["pattern"] = pattern
            else:  # _ = …
                schema["const"] = cst(model)
        case list():
            if len(model) == 1:
                schema["type"] = "array"
                schema["items"] = model2schema(model[0], path + [0])
            elif len(model) > 1:
                # tuple: prefixItems/items?
                schema["type"] = "array"
                pitems = []
                for i, item in enumerate(model):
                    pitems.append(model2schema(item, path + [i]))
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
                subschema = model2schema(model["@"], path + ["@"])
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
                    # contraints on object
                    if schema["type"] == "object":
                        if "<=" in model:
                            schema["maxProperties"] = model["<="]
                        if ">=" in model:
                            schema["minProperties"] = model[">="]
                    # constraints on array
                    if schema["type"] == "array":
                        if ".in" in model:  # model extension
                            schema["contains"] = model2schema(model[".in"])
                            if "<=" in model:
                                schema["maxContains"] = model["<="]
                            if ">=" in model:
                                schema["minContains"] = model[">="]
                        # else:
                        if "<=" in model:
                            schema["maxItems"] = model["<="]
                        if ">=" in model:
                            schema["minItems"] = model[">="]
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
                        v = int(model[">="])
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
                schema["allOf"] = [model2schema(m, path + ["&", i]) for i, m in enumerate(models)]
            elif "^" in model:
                models = model["^"]
                assert isinstance(models, list)  # pyright hint
                schema["oneOf"] = [model2schema(m, path + ["^", i]) for i, m in enumerate(models)]
            elif "|" in model:
                models = model["|"]
                assert isinstance(models, list)
                if all(map(is_cst, models)):  # all choices are constants
                    schema["enum"] = list(map(cst, models))  # pyright: ignore
                else:
                    schema["anyOf"] = [model2schema(m, path + ["|", i])
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
                        addProp = model2schema(val, lpath)
                    elif prop[0] in ("_", "!"):
                        required.append(prop[1:])
                        properties[prop[1:]] = model2schema(val, lpath)
                    elif prop[0] == "?":
                        properties[prop[1:]] = model2schema(val, lpath)
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
                        schema["patternProperties"][pattern] = model2schema(val, lpath)
                        if addProp is None:
                            addProp = False
                    elif prop[0] == "$":
                        # NOTE should be ok if simple enough so that constant propagation removed it
                        raise Exception(f"JSON Schema: no support for property ref at {lpath}")
                    else:  # standard property
                        required.append(prop)
                        properties[prop] = model2schema(val, lpath)

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
