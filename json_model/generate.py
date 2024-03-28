import json

import logging
log = logging.getLogger("s2m")
log.setLevel(logging.DEBUG)

#
# SCHEMA TO MODEL CONVERSION
#

def only(schema, *props):
    """Tell whether schema only contains these props."""
    assert isinstance(schema, dict)
    ok = set(schema.keys()).issubset(set(props))
    if not ok:
        ttype = schema.get("type", "<>")
        log.debug(f"BAD SCHEMA {ttype}: {list(schema.keys())} {props}")
    return ok

def has(schema, *props):
    """Tell whether schema has any of these props."""
    assert isinstance(schema, dict)
    for p in schema.keys():
        if p not in props:
            return False
    return True

def esc(s):
    """Escape a string if necessary."""
    if isinstance(s, str) and (len(s) == 0 or s[0] in ("$", "?", "_", "!", "=", "^")):
        return "_" + s
    else:
        return s

def numberConstraints(schema):
    assert "type" in schema and schema["type"] in ("integer", "number")
    constraints = {}
    if "multipleOf" in schema:
        mo = schema["multipleOf"]
        assert type(mo) in (int, float)
        constraints["mo"] = mo
    if "minimum" in schema:
        mini = schema["minimum"]
        assert type(mini) in (int, float)
        constraints[">="] = mini
    if "maximum" in schema:
        maxi = schema["maximum"]
        assert type(maxi) in (int, float)
        constraints["<="] = maxi
    if "exclusiveMinimum" in schema:
        mini = schema["exclusiveMinimum"]
        assert type(mini) in (int, float)
        constraints[">"] = mini
    if "exclusiveMaximum" in schema:
        maxi = schema["exclusiveMaximum"]
        assert type(maxi) in (int, float)
        constraints["<"] = maxi
    return constraints

def buildModel(model, constraints: dict, defs: dict, sharp: dict):
    if constraints or sharp or defs:
        if constraints:
            m = { "@": model, **constraints }
        elif isinstance(model, dict):
            m = model
        else:
            m = { "@": model }
        if sharp:
            m["#"] = sharp
        if defs:
            m["%"] = defs
        return m
    else:
        return model

_definitions = 0
def new_def():
    """Generate a new definition name."""
    global _definitions
    _definitions += 1
    return f"_{_definitions}"

META_KEYS = [
    "title", "description", "default", "examples", "deprecated", "readOnly", "writeOnly", "id",
    "$schema", "$id",
    # OLD?
    "context", "notes",
]

IGNORE = META_KEYS + [ "$defs", "definitions" ]

# keywords specific to a type
TYPE_SPLIT = {
    "number": [ "minimum", "maximum", "exclusiveMinimum", "exclusiveMaximum", "multipleOf" ],
    "string": [ "minLength", "maxLength", "pattern" ],
    "array": [ "minItems", "maxItems", "uniqueItems", "items", "prefixItems", "contains", "minContains", "maxContains" ],
    "object": [ "properties", "required", "additionalProperties", "minProperties", "maxProperties" ],
}

SPLIT = {}
for k in TYPE_SPLIT.keys():
    for n in TYPE_SPLIT[k]:
        SPLIT[n] = k
# log.warning(f"SPLIT = {SPLIT}")

def split_schema(schema: dict[str, any]) -> dict[str, dict[str, any]]:
    assert isinstance(schema, dict) and "type" in schema
    types = schema["type"]
    assert isinstance(types, (list, tuple))
    # log.info(f"splitting on {types}")
    # per type
    schemas = { t: {"type": t} for t in types }
    for prop, val in schema.items():
        if prop in META_KEYS or prop == "type":
            pass
        elif prop == "format":
            fmt = schema["format"]
            if "string" in schemas:
                schemas["string"]["format"] = fmt
            elif "number" in schemas:
                schemas["number"]["format"] = fmt
            elif "integer" in schemas:
                schemas["integer"]["format"] = fmt
            else:
                assert False, f"cannot map format to {types}"
        elif prop in SPLIT:
            assert SPLIT[prop] in types
            schemas[SPLIT[prop]][prop] = val
        else:
            assert False, f"cannot map {prop} to a type"
    # log.debug(f"splitted: {schemas}")
    return schemas

# identifiers
CURRENT_SCHEMA: str = None
IDS: dict[str, dict[str, any]] = {}

EXPLICIT_TYPE: bool = False

def reset():
    global CURRENT_SCHEMA, IDS
    CURRENT_SCHEMA = None
    IDS = {}

_FMT2MODEL = {
    "password": "$STRING",  # OpenAPI
    "date": "$DATE",
    "date-time": "$DATETIME",
    "time": "$TIME",
    "duration": "$DURATION",
    "email": "$EMAIL",
    "idn-email": "$EMAIL",
    "hostname": "$HOSTNAME",
    "idn-hostname": "$HOSTNAME",
    "ipv4": "$IP4",
    "ipv6": "$IP6",
    "uri": "$URI",
    "iri": "$URI",
    "iri-reference": "$URI",
    "uri-reference": "$URI",
    "uri-template": "$URI",
    "uuid": "$UUID",
    "json-pointer": "$JSONPT",
    "relative-json-pointer": "$JSONPT",
    "regex": "$REGEX",
    # hmmm…
    "color": "$STRING",
    "phone": "$STRING",
}

def format2model(fmt: str):
    if fmt in _FMT2MODEL:
        return _FMT2MODEL[fmt]
    else:
        return f"${fmt}"

def schema2model(schema, path: str=""):
    """Convert a JSON schema to a JSON model."""

    global CURRENT_SCHEMA, IDS, EXPLICIT_TYPE

    # 4.3.2 Boolean JSON Schemas
    if isinstance(schema, bool):
        return "$ANY" if schema else "$NONE"

    assert isinstance(schema, dict), path

    if "$schema" in schema:
        sname = schema["$schema"]
        if CURRENT_SCHEMA is not None:
            log.error(f"nested $schema: {sname}")
        CURRENT_SCHEMA = sname

    # handle metadata
    sharp = {}
    for prop in META_KEYS:
        if prop in schema:
            sharp[prop] = schema[prop]

    # handle defs
    # FIXME should delay conversion...
    defs = {}
    if "$defs" in schema or "definitions" in schema:
        dname = "$defs" if "$defs" in schema else "definitions"
        IDS[dname] = {}
        _defs = schema[dname]
        assert isinstance(_defs, dict)
        for name, val in _defs.items():
            log.warning(f"registering {dname}/{name}")
            # keep json schema for handling $ref #
            IDS[dname][name] = val
            # provide a local converted version as well?
            # this may not be enough in some cases
            defs[name] = schema2model(val, path + f"/{dname}/{name}")

    # FIXME cleanup OpenAPI extentions "x-*", nullable
    for prop in list(schema.keys()):
        if prop.startswith("x-"):
            log.warning(f"deleting {prop} on {path}")
            del schema[prop]
        if "nullable" in schema:
            nullable = schema["nullable"]
            assert isinstance(nullable, bool)
            if nullable:
                if "type" in schema and isinstance(schema["type"], str):
                    schema["type"] = [ schema["type"], "null" ]
                log.warning(f"ignoring nullable directive")
            del schema["nullable"]

    # FIX missing type in some cases
    if "type" not in schema:
        if "properties" in schema:
            schema["type"] = "object"
        elif "pattern" in schema or "maxLength" in schema or "minLength" in schema:
            schema["type"] = "string"

    # FIXME adhoc handling for table-schema.json and ADEME
    if "type" in schema and schema["type"] == "object" and ("anyOf" in schema or "oneOf" in schema):
        log.warning(f"distributing object on anyOf/oneOf on {path}")
        # special case for Ademe
        if "anyOf" in schema:
            assert "oneOf" not in schema
            lof = schema["anyOf"]
        elif "oneOf" in schema:
            assert "anyOf" not in schema
            lof = schema["oneOf"]
        else:
            assert False  # dead code
        # transfer type in list
        del schema["type"]
        for s in lof:
            assert isinstance(s, dict)
            s["type"] = "object"
        if "required" in schema:
            required = schema["required"]
            del schema["required"]
            for s in lof:
                if "required" in s:
                    s["required"].append(required)
                else:
                    s["required"] = required
        if "properties" in schema:
            props = schema["properties"]
            del schema["properties"]
            for s in lof:
                if "properties" in s:
                    s["properties"].update(props)
                else:
                    s["properties"] = props
        if "additionalProperties" in schema:
            addprop = schema["additionalProperties"]
            del schema["additionalProperties"]
            for s in lof:
                # cold overwrite
                s["additionalProperties"] = addprop

    if "type" in schema and ("allOf" in schema or "anyOf" in schema or "oneOf" in schema or "enum" in schema or "$ref" in schema):
        log.warning(f"removing type from constructed schema?")
        del schema["type"]

    # handle a schema
    if "$ref" in schema:
        assert only(schema, "$ref", *IGNORE), path
        ref = schema["$ref"]
        assert isinstance(ref, str) and len(ref) > 0
        if ref.startswith("#/$defs/") and only(schema, "$ref", *IGNORE):
            # keep a reference if simple
            return buildModel("$" + ref[8:], {}, defs, sharp)
        elif ref.startswith("#/"):
            names = ref[2:].split("/")
            val = IDS
            for name in names:
                assert name in val, f"following path in {ref}: missing {name} ({IDS})"
                val = val[name]
            model = schema2model(val, path + "/$ref")
            return buildModel(model, {}, defs, sharp)
        else:
            assert False, f"$ref handling not implemented: {ref}"
    elif "type" in schema:
        ts = schema["type"]
        if isinstance(ts, (list, tuple)):
            # ooops
            schemas = split_schema(schema)
            return buildModel({"|": [ schema2model(v, path + "/typeS") for v in schemas.values() ]}, {}, defs, sharp)
        elif ts == "string" and "const" in schema:
            assert only(schema, "type", "const", *IGNORE), path
            const = schema["const"]
            return buildModel(f"_{const}", {}, defs, sharp)
        elif ts == "string":
            assert only(schema, "enum", "type", "format", "pattern", "minLength", "maxLength",
                        "contentMediaType", "contentEncoding",
                        *IGNORE), path
            model = "$STRING" if EXPLICIT_TYPE else ""
            if "format" in schema:
                fmt = schema["format"]
                if fmt is not None:
                    model = format2model(fmt)
                else:
                    log.warning("ignoring null format")
            constraints = {}
            if "enum" in schema:
                ve = schema["enum"]
                assert isinstance(ve, list), path
                # TODO check stat *all* items are strings
                if len(ve) == 1:
                    assert isinstance(ve[0], str), path
                    model = esc(ve[0])
                else:
                    model = {"|": [ esc(v) for v in ve ] }
            if "pattern" in schema:
                pattern = schema["pattern"]
                assert isinstance(pattern, str), path
                assert model in ("", "$STRING"), path
                model = f"/{pattern}/"
            if "minLength" in schema:
                minlen = schema["minLength"]
                assert isinstance(minlen, int), path
                constraints[">="] = minlen
            if "maxLength" in schema:
                maxlen = schema["maxLength"]
                assert isinstance(maxlen, int), path
                constraints["<="] = maxlen
            # if "contentMediaType" in schema:
            #     val = schema["contentMediaType"]
            #     assert isinstance(val, str), path
            #     constraints["mime"] = val
            # if "contentEncoding" in schema:
            #     val = schema["contentEncoding"]
            #     assert isinstance(val, str), path
            #     constraints["encoding"] = val
            return buildModel(model, constraints, defs, sharp)
        elif ts == "number":
            assert only(schema, "type", "format", "multipleOf", "minimum", "maximum", "exclusiveMinimum", "exclusiveMaximum", *IGNORE), path
            model = "$NUMBER" if EXPLICIT_TYPE else 0.0
            if "format" in schema:
                fmt = schema["format"]
                assert fmt in ("double", "float"), f"bad format {fmt} on {path}"
                if fmt == "double":
                    model = "$DOUBLE"
                elif fmt == "float":
                    model = "$FLOAT"
                else:
                    assert False, f"unexpected number format {fmt} on {path}"
            constraints = numberConstraints(schema)
            return buildModel(model, constraints, defs, sharp)
        elif ts == "integer":
            assert only(schema, "type", "format", "multipleOf", "minimum", "maximum", "exclusiveMinimum", "exclusiveMaximum", *IGNORE), path
            model = "$INTEGER" if EXPLICIT_TYPE else 0
            # OpenAPI
            if "format" in schema:
                fmt = schema["format"]
                log.warning(f"ignoring format {fmt}")
                assert fmt in ("int32", "int64"), f"bad format {fmt} on {path}"
                if fmt == "int32":
                    model = "$I32"
                elif fmt == "int64":
                    model = "$I64"
                else:
                    assert False, f"unexpected integer format: {fmt} on {path}"
            constraints = numberConstraints(schema)
            return buildModel(model, constraints, defs, sharp)
        elif ts == "boolean":
            log.warning("'required' ignored for boolean")
            assert only(schema, "type", "required", *IGNORE), path
            model = "$BOOL" if EXPLICIT_TYPE else True
            return buildModel(model, {}, defs, sharp)
        elif ts == "null":
            model = "$NULL" if EXPLICIT_TYPE else None
            assert only(schema, "type", *IGNORE), path
            return buildModel(model, {}, defs, sharp)
        elif ts == "array":
            assert only(schema, "type", "prefixItems", "items",
                        "contains", "minContains", "maxContains",
                        "minItems", "maxItems", "uniqueItems", *IGNORE), path
            constraints = {}
            if "minItems" in schema:
                mini = schema["minItems"]
                assert type(mini) == int, path
                constraints[">="] = mini
            if "maxItems" in schema:
                maxi = schema["maxItems"]
                assert type(maxi) == int, path
                constraints["<="] = maxi
            if "uniqueItems" in schema:
                unique = schema["uniqueItems"]
                assert isinstance(unique, bool), path
                if unique:
                    constraints["distinct"] = True
            if "prefixItems" in schema:
                assert only(schema, "type", "prefixItems", "items", "minItems", "maxItems", "uniqueItems", *IGNORE), path
                # tuple
                vpi = schema["prefixItems"]
                assert isinstance(vpi, list), path
                model = [ schema2model(i, path + "/prefixItems") for i in vpi ]
                if "items" in schema:
                    # cas prefixItems + items
                    if isinstance(schema["items"], bool):
                        assert not constraints, f"not implemented yet {path}"
                        if not schema["items"]:
                            return buildModel(model, { ">=": 0, "<=": len(model) }, defs, sharp)
                        else:
                            assert False, f"not implemented yet {path}"
                    # items is a type
                    model.append(schema2model(schema["items"], path + "/items"))
                    if not constraints:
                        constraints[">="] = len(model) - 1
                    return buildModel(model, constraints, defs, sharp)
                else:
                    model.append("$ANY")
                    if not constraints:
                        constraints[">="] = len(model) - 1
                    return buildModel(model, constraints, defs, sharp)
            elif "items" in schema:
                assert only(schema, "type", "items", "minItems", "maxItems", "uniqueItems", *IGNORE), path
                sitems = schema["items"]
                assert isinstance(sitems, (dict, bool)), path
                model = [ schema2model(schema["items"], path + "/items!") ]
                return buildModel(model, constraints, defs, sharp)
            elif "contains" in schema:
                # NO contains/items mixing yet
                assert only(schema, "type", "contains", "minContains", "maxContains", "uniqueItems", *IGNORE), path
                model = { "@": ["$ANY"], "in": schema2model(schema["contains"], path + "/contains") }
                if "minContains" in schema:
                    mini = schema["minContains"]
                    assert type(mini) == int, path
                    model[">="] = mini
                if "maxContains" in schema:
                    maxi = schema["maxContains"]
                    assert type(maxi) == int, path
                    model["<="] = maxi
                return buildModel(model, constraints, defs, sharp)
            else:
                return buildModel([ "$ANY" ], constraints, defs, sharp)
        elif ts == "object":
            if "discriminator" in schema:  # OpenAPI
                log.warning(f"ignoring discriminator on {path}")
                del schema["discriminator"]
            # handle meta data
            assert only(schema, "type", "properties", "additionalProperties", "required",
                        "minProperties", "maxProperties", "patternProperties", "propertyNames",
                        *IGNORE), path
            constraints = {}
            model = {}
            if "minProperties" in schema:
                mini = schema["minProperties"]
                assert type(mini) == int, path
                constraints[">="] = mini
            if "maxProperties" in schema:
                maxi = schema["maxProperties"]
                assert type(maxi) == int, path
                constraints["<="] = maxi
            if "patternProperties" in schema:
                pats = schema["patternProperties"]
                assert isinstance(pats, dict), path
                for pp in sorted(pats.keys()):
                    name = new_def()
                    defs[name] = { "@": f"/{pp}/" }
                    model[f"${name}"] = schema2model(pats[pp], path + f"/patternProperties[{pp}]")
            if "propertyNames" in schema:
                # does not seem very useful?
                pnames = schema["propertyNames"]
                assert only(pnames, "pattern", "type", *IGNORE), path
                # if given a type, it must be string
                if "type" in pnames:
                    assert pnames["type"] == "string", path
                if "pattern" in pnames:
                    pat = pnames["pattern"]
                    assert isinstance(pat, str), path
                    name = new_def()
                    defs[name] = pat if pat[0] == "^" else f"^.*{pat}"
                    model[f"${name}"] = "$ANY"
                # else nothing?!
            if "properties" in schema:
                props = schema["properties"]
                required = schema.get("required", [])
                assert isinstance(props, dict), path
                for k, v in props.items(): 
                    if k in required:
                        model[f"_{k}"] = schema2model(v, path + f"/properties[_{k}]")
                    else:
                        model[f"?{k}"] = schema2model(v, path + f"/properties[?{k}]")
                if "additionalProperties" in schema:
                    ap = schema["additionalProperties"]
                    if isinstance(ap, bool):
                        if ap:
                            model[""] = "$ANY"
                        # else nothing else is allowed
                    elif isinstance(ap, dict):
                        model[""] = schema2model(ap, path + "/additionalProperties")
                    else:
                        assert False, f"not implemented yet, {path}"
                else:
                    model[""] = "$ANY"
            elif "additionalProperties" in schema:
                # "additionalProperties" without "properties"
                assert only(schema, "type", "additionalProperties", *IGNORE), path
                ap = schema["additionalProperties"]
                if isinstance(ap, bool):
                    if ap:
                        model[""] = "$ANY"
                    # else nothing else is allowed
                elif isinstance(ap, dict):
                    model[""] = schema2model(ap, path + "/additionalProperties")
                else:
                    assert False, f"not implemented yet, {path}"
            else:
                assert only(schema, "type", "maxProperties", "minProperties", "patternProperties", "propertyNames", *IGNORE), path
                if "propertyNames" in schema:
                    pass
                else:
                    model[""] = "$ANY"
            # handle constraints
            return buildModel(model, constraints, defs, sharp)
        else:
            assert False, f"unexpected type: {ts} {path}"
    elif "enum" in schema:
        # FIXME currently assume only a list of string
        for prop in ("maxLength", "minLength"):
            if prop in schema:
                log.warning(f"ignoring doubtful {prop} from enum")
                del schema[prop]
        assert only(schema, "enum", *IGNORE), path
        ve = schema["enum"]
        assert isinstance(ve, list), path
        if len(ve) == 1:
            model = esc(ve[0])
        else:
            model = { "|": [ esc(v) for v in ve ] }
        # vérifier les valeurs?
        return buildModel(model, {}, defs, sharp)
    elif "const" in schema:
        assert only(schema, "const", *IGNORE), path
        const = schema["const"]
        # what is the type of the constant? assume a string for NOW, could be anything?
        assert isinstance(const, str), path
        return buildModel(f"_{const}", {}, defs, sharp)
    elif "oneOf" in schema:
        assert only(schema, "oneOf", *IGNORE), path
        choices = schema["oneOf"]
        assert isinstance(choices, (list, tuple)), path
        model = {"^": [schema2model(s, path + f"/oneOf[{i}]") for i, s in enumerate(choices)]}
        return buildModel(model, {}, defs, sharp)
    elif "anyOf" in schema:
        assert only(schema, "anyOf", *IGNORE), path
        choices = schema["anyOf"]
        assert isinstance(choices, (list, tuple)), path
        model = {"|": [schema2model(s, path + f"/anyOf[{i}]") for i, s in enumerate(choices)]}
        return buildModel(model, {}, defs, sharp)
    elif "allOf" in schema:
        # NOTE types should be compatible to avoid an empty match
        assert only(schema, "allOf", *IGNORE), path
        choices = schema["allOf"]
        assert isinstance(choices, (list, tuple)), path
        model = {"&": [schema2model(s, path + f"/allOf[{i}]") for i, s in enumerate(choices)]}
        return buildModel(model, {}, defs, sharp)
    elif "not" in schema:
        # NOTE other option:
        assert only(schema, "not", *IGNORE), path
        val = schema["not"]
        assert isinstance(val, dict), path
        if len(val) == 0:
            # { "not": {} }
            model = "$none"
        else:
            model = {"^": ["$ANY", schema2model(val, path + "/not")]}
        return buildModel(model, {}, defs, sharp)
    else:
        # empty schema
        return buildModel("$ANY", {}, defs, sharp)


#
# MODEL TO SCHEMA CONVERSION
#

# Identifiers
DEF_MODEL: dict[str, any] = {}

def model2schema(model):
    global DEF_MODEL

    tmodel = type(model)
    schema = {}

    if tmodel == type(None):
        schema["type"] = "null"
    elif tmodel == int:
        schema["type"] = "integer"
        # implement extension
        # FIXME should check for option
        if model == 0:
            schema["minimum"] = 0
        elif model == 1:
            schema["minimum"] = 1
    elif tmodel == float:
        schema["type"] = "number"
    elif tmodel == bool:
        schema["type"] = "boolean"
    elif tmodel == str:
        if model == "":
            schema["type"] = "string"
        elif model == "$ANY":
            # objet vide => ce qu'on veut
            pass
        elif model == "$NONE":
            schema["not"] = {}
        elif model[0] == "_":
            schema["const"] = model[1:]
        elif model[0] == "$":
            # FIXME let us hope that it is an anchor elsewhere...
            schema["$ref"] = "#" + model[1:]
        elif model[0] == "/":
            schema["type"] = "string"
            assert model.endswith("/")  # no support for /.../i
            schema["pattern"] = model[1:-1]
        else:
            schema["const"] = model
    elif tmodel == list:
        if len(model) == 1:
            schema["type"] = "array"
            schema["items"] = model2schema(model[0])
        elif len(model) > 1:
            # tuple: prefixItems/items?
            schema["type"] = "array"
            pitems = []
            for item in model:
                pitems.append(model2schema(item))
            schema["prefixItems"] = pitems
            schema["items"] = False
        else:
            # liste vide : tableau maxItems = 0
            schema["type"] = "array"
            schema["maxItems"] = 0
    elif tmodel == dict:
        schema = {}

        if "$" in model:
            schema["$anchor"] = model["$"]

        # meta donnees
        if "#" in model:
            sharp = model["#"]
            if isinstance(sharp, str):
                schema["description"] = sharp
            elif isinstance(sharp, dict):
                for prop, val in sharp.items():
                    if prop in META_KEYS:
                        schema[prop] = val
                    else:
                        log.warning(f"prop ignored = {prop}")
            else:
                log.error("invalid # type")

        if "%" in model:
            # nom -> model: keep track of defines locally for now...
            # FIXME maybe it could/should be a "$defs" in some cases
            if "$defs" not in schema:
                schema["$defs"] = {}
            for nom, m in model["%"].items():
                DEF_MODEL[nom] = m 
                schema["$defs"][nom] = model2schema(m)

        if "@" in model:
            # constraint...
            subschema = model2schema(model["@"])
            if isinstance(subschema, dict):
                schema.update(**subschema)
            else:
                assert isinstance(subschema, bool)
                if not subschema:
                    schema["not"] = {}
            if "type" in schema:
                # contraints on string
                if schema["type"] == "string":
                    if "<=" in model:
                        schema["maxLength"] = model["<="]
                    if ">=" in model:
                        schema["minLength"] = model[">="]
                    # FIXME extension? remove?
                    if "mime" in model:
                        schema["contentEncoding"] = model["mime"]
                    if "encoding" in model:
                        schema["contentMediaType"] = model["encoding"]
                # contraints on number or integer
                if schema["type"] in ("number","integer"):
                    if "<=" in model:
                        schema["maximum"] = model["<="]
                    if ">=" in model:
                        schema["minimum"] = model[">="]
                    if "<" in model:
                        schema["exclusiveMaximum"] = model["<"]
                    if ">" in model:
                        schema["exclusiveMinimum"] = model[">"]
                    # FIXME extension? remove?
                    if "*" in model:
                        schema["multipleOf"] = model["*"]
                # contraints on object
                if schema["type"] == "object":
                    if "<=" in model:
                        schema["maxProperties"] = model["<="]
                    if ">=" in model:
                        schema["minProperties"] = model[">="]
                # constraints on array
                if schema["type"] == "array":
                    if "~" in model:
                        schema["contains"] = model2schema(model["~"])
                        if "<=" in model:
                            schema["maxContains"] = model["<="]
                        if ">=" in model:
                            schema["minContains"] = model[">="]
                    else:
                        if "<=" in model:
                            schema["maxItems"] = model["<="]
                        if ">=" in model:
                            schema["minItems"] = model[">="]
                    if "!" in model and model["!"] == True:
                        schema["uniqueItems"] = True
        elif "&" in model:
            schema["allOf"] = [model2schema(m) for m in model["&"]]
        elif "^" in model:
            schema["oneOf"] = [model2schema(m) for m in model["^"]]
        elif "|" in model:
            # enum - liste de chaînes non vides
            choices = model["|"]
            # all choices are string
            if all(map(lambda s: isinstance(s, str) and len(s), choices)):
                schema["enum"] = choices
            else:
                # anyOf
                schema["anyOf"] = [model2schema(m) for m in choices]
        elif "+" in model:
            # TODO remove with some preprocessing?
            assert False
        else:
            schema["type"] = "object"
            properties = {}
            required = []
            addProp = None
            # récupérer properties/required
            for prop, val in model.items():
                # skip some properties: already managed before 
                if prop == "%" or prop == "#" or prop == "$":
                    continue
                if prop == "":
                    addProp = model2schema(val)
                elif prop[0] == "_":
                    required.append(prop[1:])
                    properties[prop[1:]] =  model2schema(val)
                elif prop[0] == "?":
                    properties[prop[1:]] =  model2schema(val)
                elif prop[0] == "/":
                    assert prop.endswith("/")
                    regex = prop[1:-1]
                    if "patternProperties" not in schema:
                        schema["patternProperties"] = {}
                    schema["patternProperties"][regex] = model2schema(val)
                    if addProp is None:
                        addProp = False
                elif prop[0] == "$":
                    # FIXME could handle indirect pattern prop?
                    assert False, f"model2chema not implemented yet for {model}"
                else:
                    properties[prop] = model2schema(val)

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
