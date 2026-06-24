#! /bin/env node
// we may need require to load re2
import { createRequire } from 'node:module';
const require = createRequire(import.meta.url);
import * as runtime from "json_model_runtime"
const JSON_MODEL_VERSION = "2";

let _jm_cst_0 = new Set()
export var check_model_map = new Map()


function json_model_1(val, path, rep)
{
    if (! (Object.prototype.toString.call(val) === '[object Object]'))
    {
        return false
    }
    let res
    for (const [prop, pval] of Object.entries(val))
    {
        if (prop == "null")
        {
            res = ((pval === null || (typeof pval === 'number' || pval instanceof Number) || (typeof pval === 'boolean' || pval instanceof Boolean) || (typeof pval === 'string' || pval instanceof String))) && _jm_cst_0.has(pval)
            if (! res)
            {
                return false
            }
            continue
        }
        return false
    }
    return true
}


var initialized = false

// differed module initializations
export function check_model_init()
{
    if (! initialized)
    {
        initialized = true;
        runtime.jm_set_rx(RegExp)
        _jm_cst_0.add(null)
        _jm_cst_0.add("NULL")
        _jm_cst_0.add("NOPE")
        check_model_map.set("", json_model_1)
    }
}

// differed module cleanup
export function check_model_free()
{
    if (initialized)
    {
        initialized = false;
    }
}

export function check_model(val, name, rep)
{
    let checker = check_model_map.get(name)
    if (checker === undefined)
        throw `no checker for "${name}"`
    let path = rep !== null ? [] : null

    return checker(val, path, rep)
}

// possibly run as main based on a guess
import main from "json_model_runtime/main.js"

if (import.meta.url.endsWith(process.argv[1]))
    main(check_model_init, check_model, check_model_free)
