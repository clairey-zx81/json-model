# differed module initializations
def initialize():
    global initialized
    if not initialized:
        initialized = True
INIT_BLOCK

# only actual call
initialize()
