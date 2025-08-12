// JSON Model Runtime

// default regex engine, can be overriden
export var RX = RegExp

export function jm_set_rx(rx)
{
    // console.log(`setting RX to ${rx}`)
    RX = rx
}

// return whether pattern is a regular expression ($REGEX)
export function jm_is_valid_regex(pattern, extended, path, rep)
{
    if (typeof pattern !== 'string' && !(pattern instanceof String))
        return false

    try {
        new RX(pattern)
        return true
    }
    catch (e) {
        return false
    }
}

// return whether date is a valid date ($DATE)
const MONTH_DAYS = [ 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 ];

export function jm_is_valid_date(date, path, rep)
{
    if ((typeof date !== 'string' && !(date instanceof String)) || date.length != 10)
        return false

    try {
        // parsing is rather approximate…
        const [y, m, d] = date.split("-", 3)
        const year = Number(y), month = Number(m), day = Number(d)

        if (!Number.isInteger(year) || !Number.isInteger(month) || !Number.isInteger(day))
            return false
        if (year < 1)
            return false
        if (month < 1 || month > 12)
            return false
        if (day < 1 || day > MONTH_DAYS[month - 1])
            return false
        if (day === 29 && month === 2)  // only on leap years
            return (year % 4 === 0 && year % 100 !== 0) || (year % 400 === 0);
        return true
    }
    catch (e) {
        return false
    }
}

export function jm_is_valid_time(time, path, rep)
{
    return ((typeof time === 'string' || time instanceof String) &&
            /^[T ]?([01][0-9]|2[0-3]):?[0-5][0-9]:?[0-5][0-9](\.[0-9]{3})?(Z|[-+][0-9]{2}(:?[0-5][0-9])?)?$/.exec(time) != null)
}

export function jm_is_valid_datetime(datetime, path, rep)
{
    if (typeof datetime !== 'string' && !(datetime instanceof String))
        return false
    let okay = jm_is_valid_date(datetime.slice(0, 10), path, rep)
    if (!okay) {
        if (rep) rep.push(["invalid date part in $DATETIME", path])
        return false
    }
    if (datetime[10] !== 'T' && datetime[10] !== ' ') {
        if (rep) rep.push(["invalid date-time separator in $DATETIME", path])
        return false
    }
    okay = jm_is_valid_time(datetime.slice(10), path, rep)
    if (!okay && rep)
        rep.push(["invalid time part in $DATETIME", path])
    return okay
}

// return whether uuid is a valid uuid ($UUID)
export function jm_is_valid_uuid(uuid, path, rep)
{
    return ((typeof uuid === 'string' || uuid instanceof String) && uuid.length === 36 &&
            /^[0-9a-fA-F]{8}(-[0-9a-fA-F]{4}){3}-[0-9a-fA-F]{12}$/.exec(uuid) !== null)
}

// return whether url is a valid url ($URL)
export function jm_is_valid_url(url, path, rep)
{
    if (typeof url !== 'string' && !(url instanceof String))
        return false

    try {
        new URL(url)
        return true
    }
    catch (e) {
        return false
    }
}

// return whether email is a valid email address ($EMAIL)
export function jm_is_valid_email(email, path, rep)
{
    return ((typeof email === 'string' || email instanceof String) &&
            /^[_a-zA-Z0-9.]+@[_a-zA-Z0-9.]+$/.exec(email) !== null)
}

// return whether string is valid json ($JSON)
export function jm_is_valid_json(val, path, rep)
{
    if (typeof val !== 'string' && !(val instanceof String))
        return false
    try {
        JSON.parse(val)
        return true
    }
    catch (e) {
        return false
    }
}

// work around js abysmal type (?) system
export function jm_typeof(val)
{
    if (val === null)
        return 'null'
    const tval = typeof val
    if (tval === 'boolean' || val instanceof Boolean)
        return 'boolean'
    if (tval === BigInt || val instanceof BigInt)
        return 'integer'
    if (tval === 'number' || val instanceof Number)
        return Number.isInteger(val) ? 'integer' : 'number'
    if (tval === 'string' || val instanceof String)
        return 'string'
    if (Array.isArray(val))
        return 'array'
    return 'object'
}

// array comparison
export function jm_arr_cmp(a1, a2)
{
    let s1 = a1.length, s2 = a2.length
    if (s1 !== s2)
        return s1 < s2 ? -1 : 1
    // same size, compare elements
    for (let i = 0; i < s1; i++)
    {
        const cmp = jm_cmp(a1[i], a2[i])
        if (cmp !== 0)
            return cmp
    }
    return 0
}

// get a number value out of anything
export function jm_number_value(v)
{
    const t = jm_typeof(v)
    if (t === 'integer' || t === 'number')
        return v
    if (t === 'string' || t === 'array')
        return v.length
    if (t === 'object')  // O(n)
        return Object.keys(v).length
    throw `cannot extract number from ${v}`
}

// object comparison
export function jm_obj_cmp(o1, o2)
{
    // get sorted property names
    const k1 = Object.keys(o1).toSorted()
    const k2 = Object.keys(o2).toSorted()
    const acmp = jm_arr_cmp(k1, k2)
    if (acmp !== 0)
        return acmp
    // same keys, try values
    for (let k of k1)
    {
        const vcmp = jm_cmp(o1[k], o2[k])
        if (vcmp !== 0)
            return vcmp
    }
    return 0
}

// JSON value comparison
export function jm_cmp(v1, v2)
{
    let t1 = jm_typeof(v1), t2 = jm_typeof(v2)
    if (t1 !== t2)
        return t1 < t2 ? -1 : 1
    // same type
    if (t1 === 'null')
        return 0
    if (t1 === 'boolean')
        return v1 === v2 ? 0 : v1 ? -1 : 1
    if (t1 === 'integer' || t1 === 'number' || t1 === 'string')
        return v1 < v2 ? -1 : v1 === v2 ? 0 : 1
    if (t1 === 'array')
        return jm_arr_cmp(v1, v2)
    // object
    return jm_obj_cmp(v1, v2)
}

// works for anything
export function jm_array_is_unique(arr)
{
    let sorted = arr.length > 2 ? arr.toSorted(jm_cmp) : arr
    for (let i = 0; i < sorted.length - 1; i++)
        if (jm_cmp(sorted[i], sorted[i+1]) == 0)
            return false
    return true
}

// check constraints
export function jm_check_constraint(v1, op, v2, path, rep)
{
    const t1 = jm_typeof(v1), t2 = jm_typeof(v2)
    const v = t2 === 'integer' ? jm_number_value(v1) : v1
    if (op === '=')
        return v === v2
    if (op === '!=')
        return v !== v2
    if (op === '<')
        return v < v2
    if (op === '<=')
        return v <= v2
    if (op === '>')
        return v > v2
    if (op === '>=')
        return v >= v2
    throw `unexpected comparison operator ${op}`
}
