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
    ap.add_argument("values", nargs="*", help="JSON files")
    args = ap.parse_args()

    log.setLevel(logging.DEBUG if args.debug else logging.INFO)

    for fn in args.values:
        try:
            with open(fn) as f:
                value = json.load(f)
            reasons = []
            if check_model(value, "", reasons):
                print(f"{fn}: PASS")
            else:
                print(f"{fn}: FAIL {reasons}")
        except Exception as e:
            log.debug(e, exc_info=args.debug)
            print(f"{fn}: ERROR ({e})")
