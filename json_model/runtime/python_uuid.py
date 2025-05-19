_UUID_RE = r"(?i)^[0-9a-f]{8}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{12}$"
_UUID_SEARCH = re.compile(_UUID_RE).search

def _is_valid_uuid(value: Jsonable, path: str, rep: Report = None) -> bool:
    if isinstance(value, str):
        if _UUID_SEARCH(value) is not None:
            return True
        else:
            rep is None or rep.append(f"str not an uuid at {path}")
            return False
    else:
        rep is None or rep.append(f"incompatible type for uuid at {path}: {_tname(value)}")
        return False
