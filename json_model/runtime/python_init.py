# initialization guard
initialized: bool = False

# differed module initializations
def CHECK_FUNCTION_NAME_init():
    global initialized
    if not initialized:
        initialized = True
CODE_BLOCK
