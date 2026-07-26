#! /bin/env node
// we may need require to load re2
import { createRequire } from 'node:module';
const require = createRequire(import.meta.url);
import * as runtime from "json_model_runtime"
const JSON_MODEL_VERSION = "2";

const _jm_re_0_re = new runtime.RX("^[-\\w]*$", "s")
export var check_model_map = new Map()

function json_model_2(val, path, rep)
{
    return ((typeof val === 'string' || val instanceof String)) && runtime.jm_char_length(val) > 0
}

function json_model_3(val, path, rep)
{
    let res = Array.isArray(val) && val.length == 2
    if (res)
    {
        res = (typeof val[0] === 'boolean' || val[0] instanceof Boolean)
        if (res)
            res = true
    }
    return res
}

const _jm_re_0 = (s) => _jm_re_0_re.exec(s) !== null

function json_model_4(val, path, rep)
{
    let res = Array.isArray(val) && val.length == 3
    if (res)
    {
        res = (typeof val[0] === 'boolean' || val[0] instanceof Boolean)
        if (res)
        {
            res = ((typeof val[1] === 'string' || val[1] instanceof String)) && _jm_re_0(val[1], null, null)
            if (res)
                res = true
        }
    }
    return res
}

function json_model_5(val, path, rep)
{
    return json_model_2(val, null, null) || json_model_3(val, null, null) || json_model_4(val, null, null)
}

function json_model_1(val, path, rep)
{
    let res = Array.isArray(val)
    if (res)
    {
        for (let arr_0_idx = 0; arr_0_idx < val.length; arr_0_idx++)
        {
            let arr_0_item = val[arr_0_idx]
            res = json_model_5(arr_0_item, null, null)
            if (! res)
                break
        }
    }
    return res
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
        check_model_map.set("Comment", json_model_2)
        check_model_map.set("Test2", json_model_3)
        check_model_map.set("Test3", json_model_4)
        check_model_map.set("Test", json_model_5)
    }
}

// differed module cleanup
export function check_model_free()
{
    if (initialized)
        initialized = false;
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
