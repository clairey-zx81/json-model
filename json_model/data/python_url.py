def _is_valid_url(value: Jsonable, path: str, rep: Report = None) -> bool:
    if isinstance(value, str):
        try:
            urllib.parse.urlparse(value)
            return True
        except Exception as e:
            rep is None or re.append(f"invalid url at {path}: {value} ({e})")
            return False
    rep is None or rep.append(f"incompatible type for url at {path}: {_tname(value)}")
    return False
