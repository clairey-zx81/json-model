export function CHECK_FUNCTION_NAME(val, name, rep)
{
    CHECK_FUNCTION_NAME_init()

    let checker = CHECK_FUNCTION_NAME_map[name]
    let path = rep !== null ? [] : null

    return checker(val, path, rep)
}
