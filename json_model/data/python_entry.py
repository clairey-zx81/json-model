def CHECK_FUNCTION_NAME_fun(name: str) -> CheckFun:
    """Return check function for JSON model name."""
    return jm_check_model_map[name]

# entry point for generated checkers
def CHECK_FUNCTION_NAME(val: Jsonable, name: str = "", rep: Report = None) -> bool:
    """Check val validity agains JSON Model name."""
    if name not in jm_check_model_map:
        raise Exception(f"unexpected model name: {name}")
    checker = jm_check_model_map[name]
    return checker(val, [], rep)
