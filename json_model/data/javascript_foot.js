export function check_model(val, name, rep)
{
    check_model_init()

    let checker = check_model_map[name]
    let path = rep !== null ? [] : null

    return checker(val, path, rep)
}

main(check_model)
