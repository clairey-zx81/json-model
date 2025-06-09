// JSON Model Runtime

export function jm_is_valid_regex(pattern, options)
{
    try {
        new RegExp(pattern, options);
        return true;
    }
    catch (e) {
        return false;
    }
}

const MONTH_DAYS = [ 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 ];

export function jm_is_valid_date(date)
{
    if (typeof date !== 'string' || date.length != 10)
        return false;

    try {
        // parsing is rather approximate…
        const [y, m, d] = date.split("-", 3);
        const year = Number(y);
        const month = Number(m);
        const day = Number(d);

        if (!Number.isInteger(year) || !Number.isInteger(month) || !Number.isInteger(day))
            return false;
        if (year < 1)
            return false;
        if (month < 1 || month > 12)
            return false;
        if (day < 1 || day > MONTH_DAYS[month - 1])
            return false;
        if (day === 29 && month === 2)  // only on leap years
            return (year % 4 === 0 && year % 100 !== 0) || (year % 400 === 0);
        return true;
    }
    catch (e) {
        return false;
    }
}

export function jm_is_valid_uuid(uuid)
{
    // TODO
    return false;
}

export function jm_is_valid_url(url)
{
    // TODO
    return false;
}

// work around js abysmal type system
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

// FIXME this implementation only works for scalar types and assumes 0 === 0.0 (mv-01/uniq_2)
export function jm_array_is_unique(arr)
{
    let sorted = arr.toSorted(jm_cmp)
    for (let i = 0; i < sorted.length - 1; i++)
        if (jm_cmp(sorted[i], sorted[i+1]) == 0)
            return false
    return true
}

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
