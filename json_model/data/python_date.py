def _is_valid_date(value: Jsonable, path: str, rep: Report = None) -> bool:
    if isinstance(value, str):
        try:
            datetime.date.fromisoformat(value)
            return True
        except Exception as e:
            rep is None or rep.append(f"invalid date at {path}: {value} ({e})")
            return False
    rep is None or rep.append(f"incompatible type for date at {path}: {_tname(value)}")
    return False
