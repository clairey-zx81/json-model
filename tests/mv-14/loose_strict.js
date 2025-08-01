#! /bin/env node
// we may need require to load re2
import { createRequire } from 'node:module';
const require = createRequire(import.meta.url);
//
// Generated by JSON Model Compiler version 2.0b1
// see https://github.com/clairey-zx81/json-model
//
import * as runtime from "json_model_runtime"
const JSON_MODEL_VERSION = "2";

var check_model_map = new Map()

// object .'$loose'
function _jm_obj_0(val, path, rep)
{
    if (! (Object.prototype.toString.call(val) === '[object Object]'))
    {
        rep !== null && rep.push(["not an object [.'$loose']", path])
        return false;
    }
    let res;
    let must_count = 0;
    for (const [prop, pval] of Object.entries(val))
    {
        let lpath_0 = path ? path.concat([prop]) : null;
        if (prop == "li")
        {
            // handle must li property
            must_count += 1;
            // .'$loose'.li
            res = ((typeof pval === 'number' || pval instanceof Number) && Number.isInteger(pval)) && pval >= 0;
            if (! res)
            {
                rep !== null && rep.push(["not a 0 loose int [.'$loose'.li]", (path ? lpath_0 : null)])
            }
            if (! res)
            {
                rep !== null && rep.push(["invalid mandatory prop value [.'$loose'.li]", (path ? lpath_0 : null)])
                return false;
            }
        }
        else
        {
            rep !== null && rep.push(["unexpected prop [.'$loose']", (path ? lpath_0 : null)])
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep !== null)
        {
            if (! val.hasOwnProperty("li"))
            {
                rep !== null && rep.push(["missing mandatory prop <li> [.'$loose']", path])
            }
        }
        return false;
    }
    return true;
}

// check $loose (.'$loose')
function json_model_5(val, path, rep)
{
    let res;
    // JSON_MODEL_LOOSE_INT
    // .'$loose'
    res = _jm_obj_0(val, path, rep);
    if (! res)
    {
        rep !== null && rep.push(["unexpected element [.'$loose']", path])
    }
    return res;
}

// object .'$strict'
function _jm_obj_1(val, path, rep)
{
    if (! (Object.prototype.toString.call(val) === '[object Object]'))
    {
        rep !== null && rep.push(["not an object [.'$strict']", path])
        return false;
    }
    let res;
    let must_count = 0;
    for (const [prop, pval] of Object.entries(val))
    {
        let lpath_1 = path ? path.concat([prop]) : null;
        if (prop == "si")
        {
            // handle must si property
            must_count += 1;
            // .'$strict'.si
            res = ((typeof pval === 'number' || pval instanceof Number) && Number.isInteger(pval)) && pval >= 0;
            if (! res)
            {
                rep !== null && rep.push(["not a 0 strict int [.'$strict'.si]", (path ? lpath_1 : null)])
            }
            if (! res)
            {
                rep !== null && rep.push(["invalid mandatory prop value [.'$strict'.si]", (path ? lpath_1 : null)])
                return false;
            }
        }
        else
        {
            rep !== null && rep.push(["unexpected prop [.'$strict']", (path ? lpath_1 : null)])
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep !== null)
        {
            if (! val.hasOwnProperty("si"))
            {
                rep !== null && rep.push(["missing mandatory prop <si> [.'$strict']", path])
            }
        }
        return false;
    }
    return true;
}

// check $strict (.'$strict')
function json_model_6(val, path, rep)
{
    let res;
    // JSON_MODEL_STRICT_INT
    // .'$strict'
    res = _jm_obj_1(val, path, rep);
    if (! res)
    {
        rep !== null && rep.push(["unexpected element [.'$strict']", path])
    }
    return res;
}

// object .'$combined'
function _jm_obj_2(val, path, rep)
{
    if (! (Object.prototype.toString.call(val) === '[object Object]'))
    {
        rep !== null && rep.push(["not an object [.'$combined']", path])
        return false;
    }
    let res;
    let must_count = 0;
    for (const [prop, pval] of Object.entries(val))
    {
        let lpath_2 = path ? path.concat([prop]) : null;
        if (prop == "li")
        {
            // handle must li property
            must_count += 1;
            // .'$combined'.li
            res = ((typeof pval === 'number' || pval instanceof Number) && Number.isInteger(pval)) && pval >= 0;
            if (! res)
            {
                rep !== null && rep.push(["not a 0 strict int [.'$combined'.li]", (path ? lpath_2 : null)])
            }
            if (! res)
            {
                rep !== null && rep.push(["invalid mandatory prop value [.'$combined'.li]", (path ? lpath_2 : null)])
                return false;
            }
        }
        else if (prop == "si")
        {
            // handle must si property
            must_count += 1;
            // .'$combined'.si
            res = ((typeof pval === 'number' || pval instanceof Number) && Number.isInteger(pval)) && pval >= 0;
            if (! res)
            {
                rep !== null && rep.push(["not a 0 strict int [.'$combined'.si]", (path ? lpath_2 : null)])
            }
            if (! res)
            {
                rep !== null && rep.push(["invalid mandatory prop value [.'$combined'.si]", (path ? lpath_2 : null)])
                return false;
            }
        }
        else
        {
            rep !== null && rep.push(["unexpected prop [.'$combined']", (path ? lpath_2 : null)])
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep !== null)
        {
            if (! val.hasOwnProperty("li"))
            {
                rep !== null && rep.push(["missing mandatory prop <li> [.'$combined']", path])
            }
            if (! val.hasOwnProperty("si"))
            {
                rep !== null && rep.push(["missing mandatory prop <si> [.'$combined']", path])
            }
        }
        return false;
    }
    return true;
}

// check $combined (.'$combined')
function json_model_4(val, path, rep)
{
    let res;
    // .'$combined'
    res = _jm_obj_2(val, path, rep);
    if (! res)
    {
        rep !== null && rep.push(["unexpected element [.'$combined']", path])
    }
    return res;
}

// check $ (.)
function json_model_1(val, path, rep)
{
    let res;
    // .
    res = json_model_4(val, path, rep);
    if (! res)
    {
        rep !== null && rep.push(["unexpected $combined [.]", path])
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
        check_model_map.set("", json_model_1)
        check_model_map.set("loose", json_model_5)
        check_model_map.set("strict", json_model_6)
        check_model_map.set("combined", json_model_4)
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
