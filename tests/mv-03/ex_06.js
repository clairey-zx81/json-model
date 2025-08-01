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

// check $ex5 (.'$ex5')
function json_model_4(val, path, rep)
{
    let res;
    // .'$ex5'
    // .'$ex5'.'|'.0
    res = json_model_5(val, path, rep);
    if (! res)
    {
        rep !== null && rep.push(["unexpected $EX05a [.'$ex5'.'|'.0]", path])
    }
    if (! res)
    {
        // .'$ex5'.'|'.1
        res = json_model_6(val, path, rep);
        if (! res)
        {
            rep !== null && rep.push(["unexpected $EX05b [.'$ex5'.'|'.1]", path])
        }
    }
    if (res)
    {
        if (rep !== null) rep.length = 0
    }
    else
    {
        rep !== null && rep.push(["no model matched [.'$ex5'.'|']", path])
    }
    return res;
}

// check $EX06 (.'$EX06')
function json_model_3(val, path, rep)
{
    let res;
    // .'$EX06'
    res = (typeof val === 'boolean' || val instanceof Boolean);
    if (! res)
    {
        rep !== null && rep.push(["not a bool [.'$EX06']", path])
    }
    return res;
}

// check $ (.)
function json_model_1(val, path, rep)
{
    let res;
    // .
    res = Array.isArray(val) && val.length == 3;
    if (res)
    {
        let lpath_0 = path ? path.concat([0]) : null;
        // .0
        res = json_model_5(val[0], (path ? lpath_0 : null), rep);
        if (! res)
        {
            rep !== null && rep.push(["unexpected $ex5#EX05a [.0]", (path ? lpath_0 : null)])
        }
        if (res)
        {
            let lpath_0 = path ? path.concat([1]) : null;
            // .1
            res = json_model_6(val[1], (path ? lpath_0 : null), rep);
            if (! res)
            {
                rep !== null && rep.push(["unexpected $ex5#EX05b [.1]", (path ? lpath_0 : null)])
            }
            if (res)
            {
                let lpath_0 = path ? path.concat([2]) : null;
                // .2
                res = json_model_3(val[2], (path ? lpath_0 : null), rep);
                if (! res)
                {
                    rep !== null && rep.push(["unexpected $EX06 [.2]", (path ? lpath_0 : null)])
                }
            }
        }
    }
    if (! res)
    {
        rep !== null && rep.push(["not array or unexpected array [.]", path])
    }
    return res;
}

// check $ex5#EX05a (.'$ex5#EX05a')
function json_model_5(val, path, rep)
{
    let res;
    // .'$ex5#EX05a'
    res = ((typeof val === 'number' || val instanceof Number) && Number.isInteger(val)) && val >= 0;
    if (! res)
    {
        rep !== null && rep.push(["not a 0 strict int [.'$ex5#EX05a']", path])
    }
    return res;
}

// check $ex5#EX05b (.'$ex5#EX05b')
function json_model_6(val, path, rep)
{
    let res;
    // .'$ex5#EX05b'
    res = (typeof val === 'string' || val instanceof String);
    if (! res)
    {
        rep !== null && rep.push(["unexpected string [.'$ex5#EX05b']", path])
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
        check_model_map.set("ex5", json_model_4)
        check_model_map.set("EX06", json_model_3)
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
