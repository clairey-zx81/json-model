#! /bin/env node
// we may need require to load re2
import { createRequire } from 'node:module';
const require = createRequire(import.meta.url);
import * as runtime from "json_model_runtime"
const JSON_MODEL_VERSION = "2";

let _jm_map_0 = new Map()
export var check_model_map = new Map()

function _jm_obj_0(val, path, rep)
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
    if (! val.hasOwnProperty("d"))
    {
        return false;
    }
    pval = val["d"];
    let res = ((typeof pval === 'string' || pval instanceof String)) && pval == "n";
    if (! res)
    {
        return false;
    }
    if (! val.hasOwnProperty("v"))
    {
        return false;
    }
    pval = val["v"];
    return pval === null;
}

function _jm_obj_1(val, path, rep)
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
    if (! val.hasOwnProperty("d"))
    {
        return false;
    }
    pval = val["d"];
    let res = ((typeof pval === 'string' || pval instanceof String)) && pval == "b";
    if (! res)
    {
        return false;
    }
    if (! val.hasOwnProperty("v"))
    {
        return false;
    }
    pval = val["v"];
    return (typeof pval === 'boolean' || pval instanceof Boolean);
}

function _jm_obj_2(val, path, rep)
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
    if (! val.hasOwnProperty("d"))
    {
        return false;
    }
    pval = val["d"];
    let res = ((typeof pval === 'string' || pval instanceof String)) && pval == "i";
    if (! res)
    {
        return false;
    }
    if (! val.hasOwnProperty("v"))
    {
        return false;
    }
    pval = val["v"];
    return (typeof pval === 'number' || pval instanceof Number) && Number.isInteger(pval);
}

function _jm_obj_3(val, path, rep)
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
    if (! val.hasOwnProperty("d"))
    {
        return false;
    }
    pval = val["d"];
    let res = ((typeof pval === 'string' || pval instanceof String)) && pval == "u";
    if (! res)
    {
        return false;
    }
    if (! val.hasOwnProperty("v"))
    {
        return false;
    }
    pval = val["v"];
    return ((typeof pval === 'number' || pval instanceof Number) && Number.isInteger(pval)) && pval >= 0;
}

function _jm_obj_4(val, path, rep)
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
    if (! val.hasOwnProperty("d"))
    {
        return false;
    }
    pval = val["d"];
    let res = ((typeof pval === 'string' || pval instanceof String)) && pval == "f";
    if (! res)
    {
        return false;
    }
    if (! val.hasOwnProperty("v"))
    {
        return false;
    }
    pval = val["v"];
    return (typeof pval === 'number' || pval instanceof Number);
}

function _jm_obj_5(val, path, rep)
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
    if (! val.hasOwnProperty("d"))
    {
        return false;
    }
    pval = val["d"];
    let res = ((typeof pval === 'string' || pval instanceof String)) && pval == "s";
    if (! res)
    {
        return false;
    }
    if (! val.hasOwnProperty("v"))
    {
        return false;
    }
    pval = val["v"];
    return (typeof pval === 'string' || pval instanceof String);
}

function _jm_obj_6(val, path, rep)
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
    if (! val.hasOwnProperty("d"))
    {
        return false;
    }
    pval = val["d"];
    let res = ((typeof pval === 'string' || pval instanceof String)) && pval == "a";
    if (! res)
    {
        return false;
    }
    if (! val.hasOwnProperty("v"))
    {
        return false;
    }
    pval = val["v"];
    return Array.isArray(pval);
}

function _jm_obj_7(val, path, rep)
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
    if (! val.hasOwnProperty("d"))
    {
        return false;
    }
    pval = val["d"];
    let res = ((typeof pval === 'string' || pval instanceof String)) && pval == "o";
    if (! res)
    {
        return false;
    }
    if (! val.hasOwnProperty("v"))
    {
        return false;
    }
    pval = val["v"];
    return Object.prototype.toString.call(pval) === '[object Object]';
}


function json_model_1(val, path, rep)
{
    let res = Object.prototype.toString.call(val) === '[object Object]';
    if (res)
    {
        let tag_0;
        if ((tag_0 = val["d"]) != null)
        {
            let fun_0 = _jm_map_0.get(tag_0);
            res = fun_0 !== undefined && fun_0(val, null, null);
        }
        else
        {
            res = false;
        }
    }
    return res;
}


var initialized = false

// differed module initializations
export function check_model_init()
{
    if (! initialized)
    {
        initialized = true;
        runtime.jm_set_rx(RegExp)
        _jm_map_0.set("n", _jm_obj_0)
        _jm_map_0.set("b", _jm_obj_1)
        _jm_map_0.set("i", _jm_obj_2)
        _jm_map_0.set("u", _jm_obj_3)
        _jm_map_0.set("f", _jm_obj_4)
        _jm_map_0.set("s", _jm_obj_5)
        _jm_map_0.set("a", _jm_obj_6)
        _jm_map_0.set("o", _jm_obj_7)
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
