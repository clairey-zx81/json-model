#! /bin/env node
// we may need require to load re2
import { createRequire } from 'node:module';
const require = createRequire(import.meta.url);
import * as runtime from "json_model_runtime"
const JSON_MODEL_VERSION = "2";

export var check_model_map = new Map()

function json_model_1(val, path, rep)
{
    if (! (Object.prototype.toString.call(val) === '[object Object]'))
    {
        return false;
    }
    if (Object.keys(val).length != 2)
    {
        return false;
    }
    let pval;
    if (! val.hasOwnProperty("x"))
    {
        return false;
    }
    pval = val["x"];
    let res = ((typeof pval === 'number' || pval instanceof Number) && Number.isInteger(pval)) && pval >= 0;
    if (! res)
    {
        return false;
    }
    if (! val.hasOwnProperty("y"))
    {
        return false;
    }
    pval = val["y"];
    return ((typeof pval === 'number' || pval instanceof Number) && Number.isInteger(pval)) && pval >= 0;
}


var initialized = false

// differed module initializations
export function check_model_init()
{
    if (! initialized)
    {
        initialized = true;
        runtime.jm_set_rx(RegExp)
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
