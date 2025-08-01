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

// object .'$Root'
function _jm_obj_0(val, path, rep)
{
    if (! (Object.prototype.toString.call(val) === '[object Object]'))
    {
        rep !== null && rep.push(["not an object [.'$Root']", path])
        return false;
    }
    let res;
    let must_count = 0;
    for (const [prop, pval] of Object.entries(val))
    {
        let lpath_0 = path ? path.concat([prop]) : null;
        if (prop == "id")
        {
            // handle must id property
            must_count += 1;
            // .'$Root'.id
            res = ((typeof pval === 'number' || pval instanceof Number) && Number.isInteger(pval)) && pval == 0;
            if (! res)
            {
                rep !== null && rep.push(["unexpected =0 [.'$Root'.id]", (path ? lpath_0 : null)])
            }
            if (! res)
            {
                rep !== null && rep.push(["invalid mandatory prop value [.'$Root'.id]", (path ? lpath_0 : null)])
                return false;
            }
        }
        else if (prop == "name")
        {
            // handle must name property
            must_count += 1;
            // .'$Root'.name
            res = (typeof pval === 'string' || pval instanceof String);
            if (! res)
            {
                rep !== null && rep.push(["unexpected string [.'$Root'.name]", (path ? lpath_0 : null)])
            }
            if (! res)
            {
                rep !== null && rep.push(["invalid mandatory prop value [.'$Root'.name]", (path ? lpath_0 : null)])
                return false;
            }
        }
        else
        {
            rep !== null && rep.push(["unexpected prop [.'$Root']", (path ? lpath_0 : null)])
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep !== null)
        {
            if (! val.hasOwnProperty("id"))
            {
                rep !== null && rep.push(["missing mandatory prop <id> [.'$Root']", path])
            }
            if (! val.hasOwnProperty("name"))
            {
                rep !== null && rep.push(["missing mandatory prop <name> [.'$Root']", path])
            }
        }
        return false;
    }
    return true;
}

// check $Root (.'$Root')
function json_model_2(val, path, rep)
{
    let res;
    // .'$Root'
    res = _jm_obj_0(val, path, rep);
    if (! res)
    {
        rep !== null && rep.push(["unexpected element [.'$Root']", path])
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
        rep !== null && rep.push(["unexpected $Root [.]", path])
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
        check_model_map.set("Root", json_model_2)
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
