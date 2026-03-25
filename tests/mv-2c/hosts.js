#! /bin/env node
// we may need require to load re2
import { createRequire } from 'node:module';
const require = createRequire(import.meta.url);
import * as runtime from "json_model_runtime"
const JSON_MODEL_VERSION = "2";

export var check_model_map = new Map()
const jm_is_eth_re = new runtime.RX("^([0-9a-f]{2}:){5}[0-9a-f]{2}$", "i")
const jm_is_host_re = new runtime.RX("^([a-z0-9][-a-z0-9]{0,62})(\\.([a-z0-9][-a-z0-9]{0,62}))*$", "i")
const jm_is_ip4_re = new runtime.RX("^(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])$", "")
const jm_is_ip6_re = new runtime.RX("^(([0-9a-f]{1,4}:){7}[0-9a-f]{1,4}|([0-9a-f]{1,4}:){1,7}:|([0-9a-f]{1,4}:){1,6}(:[0-9a-f]{1,4}){1}|([0-9a-f]{1,4}:){1,5}(:[0-9a-f]{1,4}){1,2}|([0-9a-f]{1,4}:){1,4}(:[0-9a-f]{1,4}){1,3}|([0-9a-f]{1,4}:){1,3}(:[0-9a-f]{1,4}){1,4}|([0-9a-f]{1,4}:){1,2}(:[0-9a-f]{1,4}){1,5}|[0-9a-f]{1,4}:(:[0-9a-f]{1,4}){1,6}|:(:[0-9a-f]{1,4}){1,7}|::)$", "i")

function json_model_1(val, path, rep)
{
    if (! (Object.prototype.toString.call(val) === '[object Object]'))
    {
        return false;
    }
    let res;
    for (const [prop, pval] of Object.entries(val))
    {
        if (prop == "eth")
        {
            res = ((typeof pval === 'string' || pval instanceof String)) && jm_is_eth(pval, null, null);
            if (! res)
            {
                return false;
            }
            continue;
        }
        else if (prop == "host")
        {
            res = ((typeof pval === 'string' || pval instanceof String)) && jm_is_host(pval, null, null) && pval.length <= 255;
            if (! res)
            {
                return false;
            }
            continue;
        }
        else if (prop == "ipv4")
        {
            res = ((typeof pval === 'string' || pval instanceof String)) && jm_is_ip4(pval, null, null);
            if (! res)
            {
                return false;
            }
            continue;
        }
        else if (prop == "ipv6")
        {
            res = ((typeof pval === 'string' || pval instanceof String)) && jm_is_ip6(pval, null, null);
            if (! res)
            {
                return false;
            }
            continue;
        }
        return false;
    }
    return true;
}


const jm_is_eth = (s) => jm_is_eth_re.exec(s) !== null

const jm_is_host = (s) => jm_is_host_re.exec(s) !== null

const jm_is_ip4 = (s) => jm_is_ip4_re.exec(s) !== null

const jm_is_ip6 = (s) => jm_is_ip6_re.exec(s) !== null

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
