def _is_valid_re(value: Jsonable, path: str, rep: Report = None) -> bool:
    if isinstance(value, str):
        try:
            re.compile(value)
            return True
        except Exception as e:
            rep is None or rep.append(f"regex compile error at {path}: {value} ({e})")
            return False
    rep is None or rep.append(f"incompatible type for regex at {path}: {_tname(value)}")
    return False
