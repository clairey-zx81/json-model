# differed module cleanup
def CHECK_FUNCTION_NAME_free():
    global initialized
    if initialized:
        initialized = False
CODE_BLOCK
