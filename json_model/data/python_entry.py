def CHECK_FUNCTION_NAME_fun(name: str) -> CheckFun:
    """Return check function for JSON model name."""
    return CHECK_FUNCTION_NAME_map[name]

# entry point for generated checkers
def CHECK_FUNCTION_NAME(val: Jsonable, name: str = "", rep: Report = None) -> bool:
    """Check val validity agains JSON Model name."""
    if name not in CHECK_FUNCTION_NAME_map:
        raise Exception(f"unexpected model name: {name}")
    checker = CHECK_FUNCTION_NAME_map[name]
    return checker(val, [], rep)
