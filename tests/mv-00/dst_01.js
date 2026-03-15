#! /bin/env node
// we may need require to load re2
import { createRequire } from 'node:module';
const require = createRequire(import.meta.url);
import * as runtime from "json_model_runtime"
const JSON_MODEL_VERSION = "2";

export var check_model_map = new Map()

function _jm_obj_0(val, path, rep)
{
    if (Object.keys(val).length != 3)
    {
        return false;
    }
    let pval;
    let res;
    if (! val.hasOwnProperty("a"))
    {
        return false;
    }
    pval = val["a"];
    res = ((typeof pval === 'number' || pval instanceof Number) && Number.isInteger(pval)) && pval >= 0;
    if (! res)
    {
        return false;
    }
    if (! val.hasOwnProperty("c"))
    {
        return false;
    }
    pval = val["c"];
    res = ((typeof pval === 'number' || pval instanceof Number) && Number.isInteger(pval)) && pval >= 1;
    if (! res)
    {
        return false;
    }
    if (! val.hasOwnProperty("f"))
    {
        return false;
    }
    pval = val["f"];
    return (typeof pval === 'string' || pval instanceof String);
}

function _jm_obj_1(val, path, rep)
{
    if (Object.keys(val).length != 3)
    {
        return false;
    }
    let pval;
    let res;
    if (! val.hasOwnProperty("a"))
    {
        return false;
    }
    pval = val["a"];
    res = ((typeof pval === 'number' || pval instanceof Number) && Number.isInteger(pval)) && pval >= 0;
    if (! res)
    {
        return false;
    }
    if (! val.hasOwnProperty("c"))
    {
        return false;
    }
    pval = val["c"];
    res = ((typeof pval === 'number' || pval instanceof Number) && Number.isInteger(pval)) && pval >= 1;
    if (! res)
    {
        return false;
    }
    if (! val.hasOwnProperty("e"))
    {
        return false;
    }
    pval = val["e"];
    return (typeof pval === 'string' || pval instanceof String);
}

function _jm_obj_2(val, path, rep)
{
    if (Object.keys(val).length != 3)
    {
        return false;
    }
    let pval;
    let res;
    if (! val.hasOwnProperty("a"))
    {
        return false;
    }
    pval = val["a"];
    res = ((typeof pval === 'number' || pval instanceof Number) && Number.isInteger(pval)) && pval >= 0;
    if (! res)
    {
        return false;
    }
    if (! val.hasOwnProperty("c"))
    {
        return false;
    }
    pval = val["c"];
    res = ((typeof pval === 'number' || pval instanceof Number) && Number.isInteger(pval)) && pval >= 1;
    if (! res)
    {
        return false;
    }
    if (! val.hasOwnProperty("d"))
    {
        return false;
    }
    pval = val["d"];
    return (typeof pval === 'string' || pval instanceof String);
}

function _jm_obj_3(val, path, rep)
{
    if (Object.keys(val).length != 3)
    {
        return false;
    }
    let pval;
    let res;
    if (! val.hasOwnProperty("a"))
    {
        return false;
    }
    pval = val["a"];
    res = ((typeof pval === 'number' || pval instanceof Number) && Number.isInteger(pval)) && pval >= 0;
    if (! res)
    {
        return false;
    }
    if (! val.hasOwnProperty("b"))
    {
        return false;
    }
    pval = val["b"];
    res = ((typeof pval === 'number' || pval instanceof Number) && Number.isInteger(pval)) && pval >= 1;
    if (! res)
    {
        return false;
    }
    if (! val.hasOwnProperty("f"))
    {
        return false;
    }
    pval = val["f"];
    return (typeof pval === 'string' || pval instanceof String);
}

function _jm_obj_4(val, path, rep)
{
    if (Object.keys(val).length != 3)
    {
        return false;
    }
    let pval;
    let res;
    if (! val.hasOwnProperty("a"))
    {
        return false;
    }
    pval = val["a"];
    res = ((typeof pval === 'number' || pval instanceof Number) && Number.isInteger(pval)) && pval >= 0;
    if (! res)
    {
        return false;
    }
    if (! val.hasOwnProperty("b"))
    {
        return false;
    }
    pval = val["b"];
    res = ((typeof pval === 'number' || pval instanceof Number) && Number.isInteger(pval)) && pval >= 1;
    if (! res)
    {
        return false;
    }
    if (! val.hasOwnProperty("e"))
    {
        return false;
    }
    pval = val["e"];
    return (typeof pval === 'string' || pval instanceof String);
}

function _jm_obj_5(val, path, rep)
{
    if (Object.keys(val).length != 3)
    {
        return false;
    }
    let pval;
    let res;
    if (! val.hasOwnProperty("a"))
    {
        return false;
    }
    pval = val["a"];
    res = ((typeof pval === 'number' || pval instanceof Number) && Number.isInteger(pval)) && pval >= 0;
    if (! res)
    {
        return false;
    }
    if (! val.hasOwnProperty("b"))
    {
        return false;
    }
    pval = val["b"];
    res = ((typeof pval === 'number' || pval instanceof Number) && Number.isInteger(pval)) && pval >= 1;
    if (! res)
    {
        return false;
    }
    if (! val.hasOwnProperty("d"))
    {
        return false;
    }
    pval = val["d"];
    return (typeof pval === 'string' || pval instanceof String);
}

function json_model_1(val, path, rep)
{
    return Object.prototype.toString.call(val) === '[object Object]' && (val.hasOwnProperty("d") && _jm_obj_5(val, null, null) || val.hasOwnProperty("e") && _jm_obj_4(val, null, null) || val.hasOwnProperty("f") && _jm_obj_3(val, null, null) || val.hasOwnProperty("d") && _jm_obj_2(val, null, null) || val.hasOwnProperty("e") && _jm_obj_1(val, null, null) || val.hasOwnProperty("f") && _jm_obj_0(val, null, null));
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
