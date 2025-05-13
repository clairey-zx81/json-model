# possibly run as a script: $0 values...
if __name__ == "__main__":
    import json
    import sys
    import argparse
    import logging

    logging.basicConfig()
    log = logging.getLogger("checker")

    ap = argparse.ArgumentParser()
    ap.add_argument("--debug", "-d", action="store_true", help="set verbose mode")
    ap.add_argument("--name", "-n", default="", help="select model by name")
    ap.add_argument("--list", "-l", action="store_true", help="show available model names and exit")
    ap.add_argument("--version", "-v", action="store_true", help="show JSON Model compiler version")
    ap.add_argument("--report", "-r", action="store_true", help="show error locations on failure")
    ap.add_argument("values", nargs="*", help="JSON files")
    args = ap.parse_args()

    log.setLevel(logging.DEBUG if args.debug else logging.INFO)

    CHECK_FUNCTION_NAME_init()

    if args.list:
        print(f"JSON Models (empty for root):{' '.join(sorted(_json_model_map.keys()))}")
        sys.exit(0)
    if args.version:
        print(f"Python from JSON Model compiler version {__version__}")
        sys.exit(0)

    try:
        checker: CheckFun = CHECK_FUNCTION_NAME_fun(args.name)
    except Exception as e:
        log.debug(e, exc_info=args.debug)
        log.error(f"error on model for {args.name}: {e}")
        sys.exit(1)

    for fn in args.values:
        try:
            with open(fn) as f:
                value = json.load(f)
            reasons = [] if args.report else None
            path = [] if args.report else None
            if checker(value, path, reasons):
                print(f"{fn}: PASS")
            elif reasons:
                print(f"{fn}: FAIL {reasons}")
            else:
                print(f"{fn}: FAIL")
        except Exception as e:
            log.debug(e, exc_info=args.debug)
            print(f"{fn}: ERROR ({e})")

    CHECK_FUNCTION_NAME_free()
