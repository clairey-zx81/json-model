def _value_len(value: Jsonable, path: str) -> None|bool|int|float:
    match value:
        case str()|list()|dict():
            return len(value)
        case _:
            # FIXME should error out on None|bool?
            return value
