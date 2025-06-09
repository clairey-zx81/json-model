// possibly run as main based on a guess
import main from "json_model_runtime/main.js"

if (import.meta.url.endsWith(process.argv[1]))
    main(CHECK_FUNCTION_NAME_init, CHECK_FUNCTION_NAME, CHECK_FUNCTION_NAME_free)
