export function check_model(val, name, rep)
{
    check_model_init()

    let checker = check_model_map[name]
    let path = rep !== null ? [] : null

    return checker(val, path, rep)
}

// possibly run as main based on a guess
if (import.meta.url.endsWith(process.argv[1]))
    main(check_model)
