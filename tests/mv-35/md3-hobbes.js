#! /bin/env node
// we may need require to load re2
import { createRequire } from 'node:module';
const require = createRequire(import.meta.url);
import * as runtime from "json_model_runtime"
const JSON_MODEL_VERSION = "2";

const _jm_re_0_re = new runtime.RX("^\\w+$", "s")
export var check_model_map = new Map()

const _jm_re_0 = (s) => _jm_re_0_re.exec(s) !== null

function json_model_1(val, path, rep)
{
    if (! (Object.prototype.toString.call(val) === '[object Object]'))
        return false
    let res
    let must_count = 0
    for (const [prop, pval] of Object.entries(val))
    {
        if (prop == "name")
        {
            must_count += 1
            res = ((typeof pval == 'string' || pval instanceof String)) && _jm_re_0(pval, null, null)
            if (! res)
                return false
            continue
        }
        else if (prop == "birth")
        {
            must_count += 1
            res = runtime.jm_is_valid_date(pval, null, null)
            if (! res)
                return false
            continue
        }
        if (prop == "friends")
        {
            res = Array.isArray(pval)
            if (res)
            {
                for (let arr_0_idx = 0; arr_0_idx < pval.length; arr_0_idx++)
                {
                    let arr_0_item = pval[arr_0_idx]
                    res = ((typeof arr_0_item == 'string' || arr_0_item instanceof String)) && _jm_re_0(arr_0_item, null, null)
                    if (! res)
                        break
                }
            }
            if (! res)
                return false
            continue
        }
        return false
    }
    return must_count == 2
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
