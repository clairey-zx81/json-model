# possibly run as a script: $0 values...
if __name__ == "__main__":
    import json
    import sys
    for fn in sys.argv[1:]:
        try:
            with open(fn) as f:
                value = json.load(f)
            reasons = []
            if check_model(value, "", reasons):
                print(f"{fn}: PASS")
            else:
                print(f"{fn}: FAIL {reasons}")
        except Exception as e:
            print(f"{fn}: ERROR ({e})")
