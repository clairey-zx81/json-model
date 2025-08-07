
export function CHECK_FUNCTION_NAME(val, name, rep)
{
    let checker = CHECK_FUNCTION_NAME_map.get(name)
    if (checker === undefined)
        throw `no checker for "${name}"`
    let path = rep !== null ? [] : null

    return checker(val, path, rep)
}
