#! /usr/bin/env python

import json
import sys
import copy

def merge_object(i, j):
    assert isinstance(i, dict)
    assert isinstance(j, dict)
    if "+" in i:
        d = copy.deepcopy(i)
        d["+"].append(copy.deepcopy(j))
    elif "+" in j:
        d = copy.deepcopy(j)
        d["+"].append(copy.deepcopy(i))
    else:
        d = {"+": [i, j]}
    return d

def merge(data):

    if not isinstance(data, dict) or "+" not in data:
        return data

    assert isinstance(data["+"], list)
        
    merged = None
    for m in data["+"]:
        # pourrait être une reference
        assert isinstance(m, dict)
        if "|" in m:
            assert isinstance(m["|"], list)
            models = m["|"]
            tmerged = []
            if merged is None:
                merged = models
            else:
                for i in merged:
                    for j in models:
                        n = merge_object(i, j)
                        n = merge(n)
                        tmerged.append(n)     
                merged = tmerged
        else:
            if merged is None:
                merged = [m]
            else:
                merged = [ merge_object(i, m) for i in merged ]

    del data["+"]
    if merged:
        if len(merged) > 1:
            data["|"] = merged
        else:
            item = merged[0]
            if isinstance(item, dict) and "+" in item and len(item) == 1:
                data["+"]  = item["+"]
            else:
                data["@"] = merged
    else:
        pass
        # objet sans attribut
    return data

def merge_rewrite(data):
    if data is None:
        return data
    elif isinstance(data, (bool, int, float, str)):
        return data
    elif isinstance(data, list):
        return [merge_rewrite(i) for i in data]
    else:
        assert isinstance(data, dict)
        if "@" in data:
            data["@"] = merge_rewrite(data["@"])
        if "%" in data:
            defs = data["%"]
            assert isinstance(defs, dict)
            for k,v in defs.items():
                defs[k] = merge_rewrite(v)
        if "|" in data:
            models = data["|"]
            assert isinstance(models, list)
            data["|"] = merge_rewrite(models)
        if "&" in data:
            models = data["&"]
            assert isinstance(models, list)
            data["&"] = merge_rewrite(models)
        if "^" in data:
            models = data["^"]
            assert isinstance(models, list)
            data["^"] = merge_rewrite(models)
        if "+" in data:
            models = data["+"]
            assert isinstance(models, list)
            data["+"] = merge_rewrite(models)
            # Distribution des opérateurs avec le + et |
            data = merge(data)
        return data

for fn in sys.argv[1:]:
    with open(fn) as f:
        data = json.load(f)
        print(json.dumps(merge_rewrite(data), indent=2))
