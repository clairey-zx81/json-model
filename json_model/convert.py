from typing import Any
import sys
import logging
import json
from .types import ModelType, ModelPath
from . import utils
from .utils import is_cst, cst, log

#
# MODEL TO SCHEMA CONVERSION
#

PREDEF_TYPES = {
    "$STRING": "string",
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

def model2schema(model: ModelType, path: ModelPath = []):
    """Convert model to schema."""

    schema: Jsonable = {}

    match model:
        case None:
            schema["type"] = "null"
        case bool():
            schema["type"] = "boolean"
        case float():
            schema["type"] = "number"
        case int():
            schema["type"] = "integer"
            # implement extension
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
            elif model[0] == "$":
                # FIXME let us hope that it is an anchor elsewhere...
                schema["$ref"] = "#" + model[1:]
            elif model[0] == "/":
                schema["type"] = "string"
                assert model.endswith("/") or model.endswith("/i")
                if model.endswith("/i"):
                    pattern = "(?i)" + model[1:-2]
                else:
                    pattern = model[1:-1]
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
            else:
                # liste vide : tableau maxItems = 0
                schema["type"] = "array"
                schema["maxItems"] = 0
        case dict():
            # commentaires
            if "#" in model:
                sharp = model["#"]
                assert isinstance(sharp, str)
                schema["description"] = sharp

            if "@" in model:
                # constraint...
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
                        # FIXME extension? remove?
                        # if "*" in model:
                        #     schema["multipleOf"] = model["*"]
                    # contraints on object
                    if schema["type"] == "object":
                        if "<=" in model:
                            schema["maxProperties"] = model["<="]
                        if ">=" in model:
                            schema["minProperties"] = model[">="]
                    # constraints on array
                    if schema["type"] == "array":
                        # if "~" in model:
                        #     schema["contains"] = model2schema(model["~"])
                        #     if "<=" in model:
                        #         schema["maxContains"] = model["<="]
                        #     if ">=" in model:
                        #         schema["minContains"] = model[">="]
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
            elif "&" in model:
                schema["allOf"] = [model2schema(m, path + ["&", i]) for i, m in enumerate(model["&"])]
            elif "^" in model:
                schema["oneOf"] = [model2schema(m, path + ["^", i]) for i, m in enumerate(model["^"])]
            elif "|" in model:
                # enum - liste de chaînes non vides
                choices = model["|"]
                if all(map(is_cst, choices)):  # all choices are constants
                    schema["enum"] = list(map(cst, choices))
                else:
                    schema["anyOf"] = [model2schema(m, path + ["|", i]) for i, m in enumerate(choices)]
            elif "+" in model:
                assert False,  f"+ must have been removed by preprocessing {path + ['+']}"
            else:
                schema["type"] = "object"
                properties, required, addProp = {}, [], None
                # récupérer properties/required
                for prop, val in model.items():
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
                        assert prop.endswith("/")
                        regex = prop[1:-1]
                        if "patternProperties" not in schema:
                            schema["patternProperties"] = {}
                        schema["patternProperties"][regex] = model2schema(val, lpath)
                        if addProp is None:
                            addProp = False
                    elif prop[0] == "$":
                        raise Exception(f"JSON Schema does not support properties as refs at {lpath}")
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

    # simplify final schema if possible
    if schema == {}:
        schema = True
    elif "not" in schema and schema["not"] == {}:
        if len(schema) == 1:
            schema = False
        else:
            schema["not"] = True

    return schema
