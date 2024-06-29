import enum
import json

class JsonType(enum.IntEnum):
    DATA = 0
    SCHEMA = 1
    MODEL = 2

_JSON_SCHEMA_METADATA = (
    "title", "description", "default", "examples", "deprecated", "readOnly",
    "writeOnly"
)

def _json_metrics(data, counts: dict[str, int], skip_metadata=False, json_type=JsonType.DATA):
    """Recursive internal computation of json data structure metrics."""
    counts["#nodes"] += 1
    tdata = type(data)
    if tdata == type(None):
        counts["null"] += 1
        return 0
    elif tdata == bool:
        counts["boolean"] += 1
        return 0
    elif tdata == int:
        counts["integer"] += 1
        return 0
    elif tdata == float:
        counts["number"] += 1
        return 0
    elif tdata == str:
        counts["string"] += 1
        counts["#length"] += len(data)
        return 0
    elif tdata in (list, tuple):
        counts["array"] += 1
        counts["#items"] += len(data)
        md = 0
        for m in data:
            md = max(md, _json_metrics(m, counts, skip_metadata, json_type))
        return 1 + md
    elif tdata == dict:
        counts["object"] += 1
        counts["#props"] += len(data)
        counts["#nodes"] += len(data)  # count property names
        md = 0
        for k, v in data.items():
            assert isinstance(k, str)
            counts["string"] += 1
            counts["#length"] += len(k)
            if skip_metadata:
               if json_type == JsonType.MODEL and k == "#":
                   continue
               elif json_type == JsonType.SCHEMA and k in _JSON_SCHEMA_METADATA:
                   continue
               else:
                   pass
            md = max(md, _json_metrics(v, counts, skip_metadata, json_type))
        return 1 + md
    else:
        raise ModelError(f"unexpected data node type: {tdata}")

# normalized cost of JSON elements, for comparison purposes
_COSTS = {
    "null": 1,
    "boolean": 1,
    "integer": 4,
    "number": 8,
    "string": 10,
    "#length": 0,
    "array": 2,
    "#items": 1,
    "object": 2,
    "#props": 2,
    "#nodes": 0,
}

def json_metrics_raw(data, skip_metadata=False, json_type=JsonType.DATA):
    """Compute metrics about a json data structure."""
    counts = {
        "null": 0,
        "boolean": 0,
        "integer": 0,
        "number": 0,
        "string": 0,
        "array": 0,
        "object": 0,
        "#items": 0,
        "#props": 0,
        "#length": 0,
        "#nodes": 0,
    }
    counts["_depth"] = _json_metrics(data, counts, skip_metadata, json_type)
    counts["_length"] = len(json.dumps(data))
    return counts

def json_metrics(data, skip_metadata=False, json_type=JsonType.DATA) -> \
    tuple[int, int, int, int, int, dict[str, int]]:
    """Compute metrics about a json data structure."""
    counts = json_metrics_raw(data, skip_metadata, json_type)
    metrics = (
        counts["_depth"],
        counts["array"] + 2* counts["object"],
        counts["null"] + counts["boolean"] + counts["integer"] +  counts["number"] + counts["string"],
        sum(_COSTS[k] * counts[k] for k in _COSTS.keys() if k in counts),
        counts["_length"],
    )
    return metrics + (counts, )
