#! /bin/env node
// we may need require to load re2
import { createRequire } from 'node:module';
const require = createRequire(import.meta.url);
import * as runtime from "json_model_runtime"
const JSON_MODEL_VERSION = "2";

const _jm_re_0_re = new runtime.RX("^[a-z]+$", "")
export var check_model_map = new Map()

const _jm_re_0 = (s) => _jm_re_0_re.exec(s) !== null

function json_model_2(val, path, rep)
{
    return ((typeof val === 'string' || val instanceof String)) && _jm_re_0(val, null, null);
}

function json_model_1(val, path, rep)
{
    let res = Array.isArray(val) && val.length == 2;
    if (res)
    {
        res = json_model_2(val[0], null, null);
        if (res)
        {
            res = json_model_2(val[1], null, null);
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
        check_model_map.set("ident", json_model_2)
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
