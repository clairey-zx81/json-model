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

// check $V (.'$V')
function json_model_2(val, path, rep)
{
    let res;
    // .'$V'
    // .'$V'.'|'.0
    res = (typeof val === 'number' || val instanceof Number) && Number.isInteger(val);
    if (! res)
    {
        rep !== null && rep.push(["not a -1 strict int [.'$V'.'|'.0]", path])
    }
    if (! res)
    {
        // .'$V'.'|'.1
        res = (typeof val === 'string' || val instanceof String);
        if (! res)
        {
            rep !== null && rep.push(["unexpected string [.'$V'.'|'.1]", path])
        }
    }
    if (res)
    {
        if (rep !== null) rep.length = 0
    }
    else
    {
        rep !== null && rep.push(["no model matched [.'$V'.'|']", path])
    }
    return res;
}

// object .'$X'
function _jm_obj_0(val, path, rep)
{
    if (! (Object.prototype.toString.call(val) === '[object Object]'))
    {
        rep !== null && rep.push(["not an object [.'$X']", path])
        return false;
    }
    let res;
    let must_count = 0;
    for (const [prop, pval] of Object.entries(val))
    {
        let lpath_0 = path ? path.concat([prop]) : null;
        if (prop == "X")
        {
            // handle must X property
            must_count += 1;
            // .'$X'.X
            res = (typeof pval === 'string' || pval instanceof String);
            if (! res)
            {
                rep !== null && rep.push(["unexpected string [.'$X'.X]", (path ? lpath_0 : null)])
            }
            if (! res)
            {
                rep !== null && rep.push(["invalid mandatory prop value [.'$X'.X]", (path ? lpath_0 : null)])
                return false;
            }
        }
        else
        {
            rep !== null && rep.push(["unexpected prop [.'$X']", (path ? lpath_0 : null)])
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep !== null)
        {
            if (! val.hasOwnProperty("X"))
            {
                rep !== null && rep.push(["missing mandatory prop <X> [.'$X']", path])
            }
        }
        return false;
    }
    return true;
}

// check $X (.'$X')
function json_model_3(val, path, rep)
{
    let res;
    // .'$X'
    res = _jm_obj_0(val, path, rep);
    if (! res)
    {
        rep !== null && rep.push(["unexpected element [.'$X']", path])
    }
    return res;
}

// object .'$Y'
function _jm_obj_1(val, path, rep)
{
    if (! (Object.prototype.toString.call(val) === '[object Object]'))
    {
        rep !== null && rep.push(["not an object [.'$Y']", path])
        return false;
    }
    let res;
    let must_count = 0;
    for (const [prop, pval] of Object.entries(val))
    {
        let lpath_1 = path ? path.concat([prop]) : null;
        if (prop == "Y")
        {
            // handle must Y property
            must_count += 1;
            // .'$Y'.Y
            res = (typeof pval === 'string' || pval instanceof String);
            if (! res)
            {
                rep !== null && rep.push(["unexpected string [.'$Y'.Y]", (path ? lpath_1 : null)])
            }
            if (! res)
            {
                rep !== null && rep.push(["invalid mandatory prop value [.'$Y'.Y]", (path ? lpath_1 : null)])
                return false;
            }
        }
        else
        {
            rep !== null && rep.push(["unexpected prop [.'$Y']", (path ? lpath_1 : null)])
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep !== null)
        {
            if (! val.hasOwnProperty("Y"))
            {
                rep !== null && rep.push(["missing mandatory prop <Y> [.'$Y']", path])
            }
        }
        return false;
    }
    return true;
}

// check $Y (.'$Y')
function json_model_4(val, path, rep)
{
    let res;
    // .'$Y'
    res = _jm_obj_1(val, path, rep);
    if (! res)
    {
        rep !== null && rep.push(["unexpected element [.'$Y']", path])
    }
    return res;
}

// object .'$E'.'|'.1
function _jm_obj_2(val, path, rep)
{
    if (! (Object.prototype.toString.call(val) === '[object Object]'))
    {
        rep !== null && rep.push(["not an object [.'$E'.'|'.1]", path])
        return false;
    }
    let res;
    let must_count = 0;
    for (const [prop, pval] of Object.entries(val))
    {
        let lpath_2 = path ? path.concat([prop]) : null;
        if (prop == "Y")
        {
            // handle must Y property
            must_count += 1;
            // .'$E'.'|'.1.Y
            res = (typeof pval === 'string' || pval instanceof String);
            if (! res)
            {
                rep !== null && rep.push(["unexpected string [.'$E'.'|'.1.Y]", (path ? lpath_2 : null)])
            }
            if (! res)
            {
                rep !== null && rep.push(["invalid mandatory prop value [.'$E'.'|'.1.Y]", (path ? lpath_2 : null)])
                return false;
            }
        }
        else if (prop == "Z")
        {
            // handle may Z property
            // .'$E'.'|'.1.Z
            res = (typeof pval === 'string' || pval instanceof String);
            if (! res)
            {
                rep !== null && rep.push(["unexpected string [.'$E'.'|'.1.Z]", (path ? lpath_2 : null)])
            }
            if (! res)
            {
                rep !== null && rep.push(["invalid optional prop value [.'$E'.'|'.1.Z]", (path ? lpath_2 : null)])
                return false;
            }
        }
        else
        {
            rep !== null && rep.push(["unexpected prop [.'$E'.'|'.1]", (path ? lpath_2 : null)])
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep !== null)
        {
            if (! val.hasOwnProperty("Y"))
            {
                rep !== null && rep.push(["missing mandatory prop <Y> [.'$E'.'|'.1]", path])
            }
        }
        return false;
    }
    return true;
}

// object .'$E'.'|'.0
function _jm_obj_3(val, path, rep)
{
    if (! (Object.prototype.toString.call(val) === '[object Object]'))
    {
        rep !== null && rep.push(["not an object [.'$E'.'|'.0]", path])
        return false;
    }
    let res;
    let must_count = 0;
    for (const [prop, pval] of Object.entries(val))
    {
        let lpath_3 = path ? path.concat([prop]) : null;
        if (prop == "X")
        {
            // handle must X property
            must_count += 1;
            // .'$E'.'|'.0.X
            res = (typeof pval === 'string' || pval instanceof String);
            if (! res)
            {
                rep !== null && rep.push(["unexpected string [.'$E'.'|'.0.X]", (path ? lpath_3 : null)])
            }
            if (! res)
            {
                rep !== null && rep.push(["invalid mandatory prop value [.'$E'.'|'.0.X]", (path ? lpath_3 : null)])
                return false;
            }
        }
        else if (prop == "Z")
        {
            // handle may Z property
            // .'$E'.'|'.0.Z
            res = (typeof pval === 'string' || pval instanceof String);
            if (! res)
            {
                rep !== null && rep.push(["unexpected string [.'$E'.'|'.0.Z]", (path ? lpath_3 : null)])
            }
            if (! res)
            {
                rep !== null && rep.push(["invalid optional prop value [.'$E'.'|'.0.Z]", (path ? lpath_3 : null)])
                return false;
            }
        }
        else
        {
            rep !== null && rep.push(["unexpected prop [.'$E'.'|'.0]", (path ? lpath_3 : null)])
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep !== null)
        {
            if (! val.hasOwnProperty("X"))
            {
                rep !== null && rep.push(["missing mandatory prop <X> [.'$E'.'|'.0]", path])
            }
        }
        return false;
    }
    return true;
}

// check $E (.'$E')
function json_model_5(val, path, rep)
{
    let res;
    // .'$E'
    res = Object.prototype.toString.call(val) === '[object Object]';
    if (! res)
    {
        rep !== null && rep.push(["unexpected type [.'$E'.'|']", path])
    }
    if (res)
    {
        // .'$E'.'|'.0
        res = _jm_obj_3(val, path, rep);
        if (! res)
        {
            rep !== null && rep.push(["unexpected element [.'$E'.'|'.0]", path])
        }
        if (! res)
        {
            // .'$E'.'|'.1
            res = _jm_obj_2(val, path, rep);
            if (! res)
            {
                rep !== null && rep.push(["unexpected element [.'$E'.'|'.1]", path])
            }
        }
        if (res)
        {
            if (rep !== null) rep.length = 0
        }
        else
        {
            rep !== null && rep.push(["no model matched [.'$E'.'|']", path])
        }
    }
    return res;
}

// check $M (.'$M')
function json_model_6(val, path, rep)
{
    let res;
    // .'$M'
    // generic xor list
    let xc_0 = 0;
    let xr_0;
    // .'$M'.'^'.0
    xr_0 = json_model_2(val, path, rep);
    if (! xr_0)
    {
        rep !== null && rep.push(["unexpected $V [.'$M'.'^'.0]", path])
    }
    if (xr_0)
    {
        xc_0 += 1;
    }
    // .'$M'.'^'.1
    xr_0 = json_model_5(val, path, rep);
    if (! xr_0)
    {
        rep !== null && rep.push(["unexpected $E [.'$M'.'^'.1]", path])
    }
    if (xr_0)
    {
        xc_0 += 1;
    }
    res = xc_0 == 1;
    if (res)
    {
        if (rep !== null) rep.length = 0
    }
    else
    {
        rep !== null && rep.push(["not one model match [.'$M'.'^']", path])
    }
    return res;
}

// check $ (.)
function json_model_1(val, path, rep)
{
    let res;
    // .
    res = json_model_6(val, path, rep);
    if (! res)
    {
        rep !== null && rep.push(["unexpected $M [.]", path])
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
        check_model_map.set("V", json_model_2)
        check_model_map.set("X", json_model_3)
        check_model_map.set("Y", json_model_4)
        check_model_map.set("E", json_model_5)
        check_model_map.set("M", json_model_6)
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
