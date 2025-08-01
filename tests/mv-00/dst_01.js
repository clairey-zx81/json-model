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

// object .'|'.5
function _jm_obj_0(val, path, rep)
{
    if (! (Object.prototype.toString.call(val) === '[object Object]'))
    {
        rep !== null && rep.push(["not an object [.'|'.5]", path])
        return false;
    }
    let res;
    let must_count = 0;
    for (const [prop, pval] of Object.entries(val))
    {
        let lpath_0 = path ? path.concat([prop]) : null;
        if (prop == "a")
        {
            // handle must a property
            must_count += 1;
            // .'|'.5.a
            res = ((typeof pval === 'number' || pval instanceof Number) && Number.isInteger(pval)) && pval >= 0;
            if (! res)
            {
                rep !== null && rep.push(["not a 0 strict int [.'|'.5.a]", (path ? lpath_0 : null)])
            }
            if (! res)
            {
                rep !== null && rep.push(["invalid mandatory prop value [.'|'.5.a]", (path ? lpath_0 : null)])
                return false;
            }
        }
        else if (prop == "c")
        {
            // handle must c property
            must_count += 1;
            // .'|'.5.c
            res = ((typeof pval === 'number' || pval instanceof Number) && Number.isInteger(pval)) && pval >= 1;
            if (! res)
            {
                rep !== null && rep.push(["not a 1 strict int [.'|'.5.c]", (path ? lpath_0 : null)])
            }
            if (! res)
            {
                rep !== null && rep.push(["invalid mandatory prop value [.'|'.5.c]", (path ? lpath_0 : null)])
                return false;
            }
        }
        else if (prop == "f")
        {
            // handle must f property
            must_count += 1;
            // .'|'.5.f
            res = (typeof pval === 'string' || pval instanceof String);
            if (! res)
            {
                rep !== null && rep.push(["unexpected string [.'|'.5.f]", (path ? lpath_0 : null)])
            }
            if (! res)
            {
                rep !== null && rep.push(["invalid mandatory prop value [.'|'.5.f]", (path ? lpath_0 : null)])
                return false;
            }
        }
        else
        {
            rep !== null && rep.push(["unexpected prop [.'|'.5]", (path ? lpath_0 : null)])
            return false;
        }
    }
    if (must_count != 3)
    {
        if (rep !== null)
        {
            if (! val.hasOwnProperty("a"))
            {
                rep !== null && rep.push(["missing mandatory prop <a> [.'|'.5]", path])
            }
            if (! val.hasOwnProperty("c"))
            {
                rep !== null && rep.push(["missing mandatory prop <c> [.'|'.5]", path])
            }
            if (! val.hasOwnProperty("f"))
            {
                rep !== null && rep.push(["missing mandatory prop <f> [.'|'.5]", path])
            }
        }
        return false;
    }
    return true;
}

// object .'|'.4
function _jm_obj_1(val, path, rep)
{
    if (! (Object.prototype.toString.call(val) === '[object Object]'))
    {
        rep !== null && rep.push(["not an object [.'|'.4]", path])
        return false;
    }
    let res;
    let must_count = 0;
    for (const [prop, pval] of Object.entries(val))
    {
        let lpath_1 = path ? path.concat([prop]) : null;
        if (prop == "a")
        {
            // handle must a property
            must_count += 1;
            // .'|'.4.a
            res = ((typeof pval === 'number' || pval instanceof Number) && Number.isInteger(pval)) && pval >= 0;
            if (! res)
            {
                rep !== null && rep.push(["not a 0 strict int [.'|'.4.a]", (path ? lpath_1 : null)])
            }
            if (! res)
            {
                rep !== null && rep.push(["invalid mandatory prop value [.'|'.4.a]", (path ? lpath_1 : null)])
                return false;
            }
        }
        else if (prop == "c")
        {
            // handle must c property
            must_count += 1;
            // .'|'.4.c
            res = ((typeof pval === 'number' || pval instanceof Number) && Number.isInteger(pval)) && pval >= 1;
            if (! res)
            {
                rep !== null && rep.push(["not a 1 strict int [.'|'.4.c]", (path ? lpath_1 : null)])
            }
            if (! res)
            {
                rep !== null && rep.push(["invalid mandatory prop value [.'|'.4.c]", (path ? lpath_1 : null)])
                return false;
            }
        }
        else if (prop == "e")
        {
            // handle must e property
            must_count += 1;
            // .'|'.4.e
            res = (typeof pval === 'string' || pval instanceof String);
            if (! res)
            {
                rep !== null && rep.push(["unexpected string [.'|'.4.e]", (path ? lpath_1 : null)])
            }
            if (! res)
            {
                rep !== null && rep.push(["invalid mandatory prop value [.'|'.4.e]", (path ? lpath_1 : null)])
                return false;
            }
        }
        else
        {
            rep !== null && rep.push(["unexpected prop [.'|'.4]", (path ? lpath_1 : null)])
            return false;
        }
    }
    if (must_count != 3)
    {
        if (rep !== null)
        {
            if (! val.hasOwnProperty("a"))
            {
                rep !== null && rep.push(["missing mandatory prop <a> [.'|'.4]", path])
            }
            if (! val.hasOwnProperty("c"))
            {
                rep !== null && rep.push(["missing mandatory prop <c> [.'|'.4]", path])
            }
            if (! val.hasOwnProperty("e"))
            {
                rep !== null && rep.push(["missing mandatory prop <e> [.'|'.4]", path])
            }
        }
        return false;
    }
    return true;
}

// object .'|'.3
function _jm_obj_2(val, path, rep)
{
    if (! (Object.prototype.toString.call(val) === '[object Object]'))
    {
        rep !== null && rep.push(["not an object [.'|'.3]", path])
        return false;
    }
    let res;
    let must_count = 0;
    for (const [prop, pval] of Object.entries(val))
    {
        let lpath_2 = path ? path.concat([prop]) : null;
        if (prop == "a")
        {
            // handle must a property
            must_count += 1;
            // .'|'.3.a
            res = ((typeof pval === 'number' || pval instanceof Number) && Number.isInteger(pval)) && pval >= 0;
            if (! res)
            {
                rep !== null && rep.push(["not a 0 strict int [.'|'.3.a]", (path ? lpath_2 : null)])
            }
            if (! res)
            {
                rep !== null && rep.push(["invalid mandatory prop value [.'|'.3.a]", (path ? lpath_2 : null)])
                return false;
            }
        }
        else if (prop == "c")
        {
            // handle must c property
            must_count += 1;
            // .'|'.3.c
            res = ((typeof pval === 'number' || pval instanceof Number) && Number.isInteger(pval)) && pval >= 1;
            if (! res)
            {
                rep !== null && rep.push(["not a 1 strict int [.'|'.3.c]", (path ? lpath_2 : null)])
            }
            if (! res)
            {
                rep !== null && rep.push(["invalid mandatory prop value [.'|'.3.c]", (path ? lpath_2 : null)])
                return false;
            }
        }
        else if (prop == "d")
        {
            // handle must d property
            must_count += 1;
            // .'|'.3.d
            res = (typeof pval === 'string' || pval instanceof String);
            if (! res)
            {
                rep !== null && rep.push(["unexpected string [.'|'.3.d]", (path ? lpath_2 : null)])
            }
            if (! res)
            {
                rep !== null && rep.push(["invalid mandatory prop value [.'|'.3.d]", (path ? lpath_2 : null)])
                return false;
            }
        }
        else
        {
            rep !== null && rep.push(["unexpected prop [.'|'.3]", (path ? lpath_2 : null)])
            return false;
        }
    }
    if (must_count != 3)
    {
        if (rep !== null)
        {
            if (! val.hasOwnProperty("a"))
            {
                rep !== null && rep.push(["missing mandatory prop <a> [.'|'.3]", path])
            }
            if (! val.hasOwnProperty("c"))
            {
                rep !== null && rep.push(["missing mandatory prop <c> [.'|'.3]", path])
            }
            if (! val.hasOwnProperty("d"))
            {
                rep !== null && rep.push(["missing mandatory prop <d> [.'|'.3]", path])
            }
        }
        return false;
    }
    return true;
}

// object .'|'.2
function _jm_obj_3(val, path, rep)
{
    if (! (Object.prototype.toString.call(val) === '[object Object]'))
    {
        rep !== null && rep.push(["not an object [.'|'.2]", path])
        return false;
    }
    let res;
    let must_count = 0;
    for (const [prop, pval] of Object.entries(val))
    {
        let lpath_3 = path ? path.concat([prop]) : null;
        if (prop == "a")
        {
            // handle must a property
            must_count += 1;
            // .'|'.2.a
            res = ((typeof pval === 'number' || pval instanceof Number) && Number.isInteger(pval)) && pval >= 0;
            if (! res)
            {
                rep !== null && rep.push(["not a 0 strict int [.'|'.2.a]", (path ? lpath_3 : null)])
            }
            if (! res)
            {
                rep !== null && rep.push(["invalid mandatory prop value [.'|'.2.a]", (path ? lpath_3 : null)])
                return false;
            }
        }
        else if (prop == "b")
        {
            // handle must b property
            must_count += 1;
            // .'|'.2.b
            res = ((typeof pval === 'number' || pval instanceof Number) && Number.isInteger(pval)) && pval >= 1;
            if (! res)
            {
                rep !== null && rep.push(["not a 1 strict int [.'|'.2.b]", (path ? lpath_3 : null)])
            }
            if (! res)
            {
                rep !== null && rep.push(["invalid mandatory prop value [.'|'.2.b]", (path ? lpath_3 : null)])
                return false;
            }
        }
        else if (prop == "f")
        {
            // handle must f property
            must_count += 1;
            // .'|'.2.f
            res = (typeof pval === 'string' || pval instanceof String);
            if (! res)
            {
                rep !== null && rep.push(["unexpected string [.'|'.2.f]", (path ? lpath_3 : null)])
            }
            if (! res)
            {
                rep !== null && rep.push(["invalid mandatory prop value [.'|'.2.f]", (path ? lpath_3 : null)])
                return false;
            }
        }
        else
        {
            rep !== null && rep.push(["unexpected prop [.'|'.2]", (path ? lpath_3 : null)])
            return false;
        }
    }
    if (must_count != 3)
    {
        if (rep !== null)
        {
            if (! val.hasOwnProperty("a"))
            {
                rep !== null && rep.push(["missing mandatory prop <a> [.'|'.2]", path])
            }
            if (! val.hasOwnProperty("b"))
            {
                rep !== null && rep.push(["missing mandatory prop <b> [.'|'.2]", path])
            }
            if (! val.hasOwnProperty("f"))
            {
                rep !== null && rep.push(["missing mandatory prop <f> [.'|'.2]", path])
            }
        }
        return false;
    }
    return true;
}

// object .'|'.1
function _jm_obj_4(val, path, rep)
{
    if (! (Object.prototype.toString.call(val) === '[object Object]'))
    {
        rep !== null && rep.push(["not an object [.'|'.1]", path])
        return false;
    }
    let res;
    let must_count = 0;
    for (const [prop, pval] of Object.entries(val))
    {
        let lpath_4 = path ? path.concat([prop]) : null;
        if (prop == "a")
        {
            // handle must a property
            must_count += 1;
            // .'|'.1.a
            res = ((typeof pval === 'number' || pval instanceof Number) && Number.isInteger(pval)) && pval >= 0;
            if (! res)
            {
                rep !== null && rep.push(["not a 0 strict int [.'|'.1.a]", (path ? lpath_4 : null)])
            }
            if (! res)
            {
                rep !== null && rep.push(["invalid mandatory prop value [.'|'.1.a]", (path ? lpath_4 : null)])
                return false;
            }
        }
        else if (prop == "b")
        {
            // handle must b property
            must_count += 1;
            // .'|'.1.b
            res = ((typeof pval === 'number' || pval instanceof Number) && Number.isInteger(pval)) && pval >= 1;
            if (! res)
            {
                rep !== null && rep.push(["not a 1 strict int [.'|'.1.b]", (path ? lpath_4 : null)])
            }
            if (! res)
            {
                rep !== null && rep.push(["invalid mandatory prop value [.'|'.1.b]", (path ? lpath_4 : null)])
                return false;
            }
        }
        else if (prop == "e")
        {
            // handle must e property
            must_count += 1;
            // .'|'.1.e
            res = (typeof pval === 'string' || pval instanceof String);
            if (! res)
            {
                rep !== null && rep.push(["unexpected string [.'|'.1.e]", (path ? lpath_4 : null)])
            }
            if (! res)
            {
                rep !== null && rep.push(["invalid mandatory prop value [.'|'.1.e]", (path ? lpath_4 : null)])
                return false;
            }
        }
        else
        {
            rep !== null && rep.push(["unexpected prop [.'|'.1]", (path ? lpath_4 : null)])
            return false;
        }
    }
    if (must_count != 3)
    {
        if (rep !== null)
        {
            if (! val.hasOwnProperty("a"))
            {
                rep !== null && rep.push(["missing mandatory prop <a> [.'|'.1]", path])
            }
            if (! val.hasOwnProperty("b"))
            {
                rep !== null && rep.push(["missing mandatory prop <b> [.'|'.1]", path])
            }
            if (! val.hasOwnProperty("e"))
            {
                rep !== null && rep.push(["missing mandatory prop <e> [.'|'.1]", path])
            }
        }
        return false;
    }
    return true;
}

// object .'|'.0
function _jm_obj_5(val, path, rep)
{
    if (! (Object.prototype.toString.call(val) === '[object Object]'))
    {
        rep !== null && rep.push(["not an object [.'|'.0]", path])
        return false;
    }
    let res;
    let must_count = 0;
    for (const [prop, pval] of Object.entries(val))
    {
        let lpath_5 = path ? path.concat([prop]) : null;
        if (prop == "a")
        {
            // handle must a property
            must_count += 1;
            // .'|'.0.a
            res = ((typeof pval === 'number' || pval instanceof Number) && Number.isInteger(pval)) && pval >= 0;
            if (! res)
            {
                rep !== null && rep.push(["not a 0 strict int [.'|'.0.a]", (path ? lpath_5 : null)])
            }
            if (! res)
            {
                rep !== null && rep.push(["invalid mandatory prop value [.'|'.0.a]", (path ? lpath_5 : null)])
                return false;
            }
        }
        else if (prop == "b")
        {
            // handle must b property
            must_count += 1;
            // .'|'.0.b
            res = ((typeof pval === 'number' || pval instanceof Number) && Number.isInteger(pval)) && pval >= 1;
            if (! res)
            {
                rep !== null && rep.push(["not a 1 strict int [.'|'.0.b]", (path ? lpath_5 : null)])
            }
            if (! res)
            {
                rep !== null && rep.push(["invalid mandatory prop value [.'|'.0.b]", (path ? lpath_5 : null)])
                return false;
            }
        }
        else if (prop == "d")
        {
            // handle must d property
            must_count += 1;
            // .'|'.0.d
            res = (typeof pval === 'string' || pval instanceof String);
            if (! res)
            {
                rep !== null && rep.push(["unexpected string [.'|'.0.d]", (path ? lpath_5 : null)])
            }
            if (! res)
            {
                rep !== null && rep.push(["invalid mandatory prop value [.'|'.0.d]", (path ? lpath_5 : null)])
                return false;
            }
        }
        else
        {
            rep !== null && rep.push(["unexpected prop [.'|'.0]", (path ? lpath_5 : null)])
            return false;
        }
    }
    if (must_count != 3)
    {
        if (rep !== null)
        {
            if (! val.hasOwnProperty("a"))
            {
                rep !== null && rep.push(["missing mandatory prop <a> [.'|'.0]", path])
            }
            if (! val.hasOwnProperty("b"))
            {
                rep !== null && rep.push(["missing mandatory prop <b> [.'|'.0]", path])
            }
            if (! val.hasOwnProperty("d"))
            {
                rep !== null && rep.push(["missing mandatory prop <d> [.'|'.0]", path])
            }
        }
        return false;
    }
    return true;
}

// check $ (.)
function json_model_1(val, path, rep)
{
    let res;
    // .
    res = Object.prototype.toString.call(val) === '[object Object]';
    if (! res)
    {
        rep !== null && rep.push(["unexpected type [.'|']", path])
    }
    if (res)
    {
        // .'|'.0
        res = _jm_obj_5(val, path, rep);
        if (! res)
        {
            rep !== null && rep.push(["unexpected element [.'|'.0]", path])
        }
        if (! res)
        {
            // .'|'.1
            res = _jm_obj_4(val, path, rep);
            if (! res)
            {
                rep !== null && rep.push(["unexpected element [.'|'.1]", path])
            }
            if (! res)
            {
                // .'|'.2
                res = _jm_obj_3(val, path, rep);
                if (! res)
                {
                    rep !== null && rep.push(["unexpected element [.'|'.2]", path])
                }
                if (! res)
                {
                    // .'|'.3
                    res = _jm_obj_2(val, path, rep);
                    if (! res)
                    {
                        rep !== null && rep.push(["unexpected element [.'|'.3]", path])
                    }
                    if (! res)
                    {
                        // .'|'.4
                        res = _jm_obj_1(val, path, rep);
                        if (! res)
                        {
                            rep !== null && rep.push(["unexpected element [.'|'.4]", path])
                        }
                        if (! res)
                        {
                            // .'|'.5
                            res = _jm_obj_0(val, path, rep);
                            if (! res)
                            {
                                rep !== null && rep.push(["unexpected element [.'|'.5]", path])
                            }
                        }
                    }
                }
            }
        }
        if (res)
        {
            if (rep !== null) rep.length = 0
        }
        else
        {
            rep !== null && rep.push(["no model matched [.'|']", path])
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
