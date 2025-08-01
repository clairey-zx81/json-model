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

const _jm_re_0_re = new runtime.RX("[a-z]", "")
var check_model_map = new Map()

const _jm_re_0 = (s) => _jm_re_0_re.exec(s) !== null

// check $A (.'$A')
function json_model_2(val, path, rep)
{
    let res;
    // .'$A'
    // .'$A'.'|'.0
    res = (typeof val === 'boolean' || val instanceof Boolean);
    if (! res)
    {
        rep !== null && rep.push(["not a bool [.'$A'.'|'.0]", path])
    }
    if (! res)
    {
        // .'$A'.'|'.1
        res = ((typeof val === 'number' || val instanceof Number) && Number.isInteger(val)) && val >= 1;
        if (! res)
        {
            rep !== null && rep.push(["not a 1 strict int [.'$A'.'|'.1]", path])
        }
        if (! res)
        {
            // .'$A'.'|'.2
            res = ((typeof val === 'number' || val instanceof Number)) && val > 0.0;
            if (! res)
            {
                rep !== null && rep.push(["not a 1.0 strict float [.'$A'.'|'.2]", path])
            }
            if (! res)
            {
                // .'$A'.'|'.3
                // "/[a-z]/"
                res = ((typeof val === 'string' || val instanceof String)) && _jm_re_0(val, path, rep);
                if (! res)
                {
                    rep !== null && rep.push(["unexpected /[a-z]/ [.'$A'.'|'.3]", path])
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
        rep !== null && rep.push(["no model matched [.'$A'.'|']", path])
    }
    return res;
}

// check $ (.)
function json_model_1(val, path, rep)
{
    let res;
    // .
    res = json_model_2(val, path, rep);
    if (! res)
    {
        rep !== null && rep.push(["unexpected $A [.]", path])
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
        check_model_map.set("A", json_model_2)
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
