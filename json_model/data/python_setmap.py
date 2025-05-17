# types: JsonScalar

from collections.abc import MutableMapping, MutableSet

class Const:
    """A constant holder suitable for set/dict, with a stricly typed comparison.

    The point is to avoid 1 == 1.0 == True, 0 == 0.0 == False, n == n.0
    """

    def __init__(self, val: JsonScalar):
        self._val = val

    def __hash__(self):
        return hash(self._val)

    def __eq__(self, val):
        return type(self._val) is type(val) and self._val == val


class ConstSet(MutableSet[JsonScalar]):
    """A set of constants, with strictly typed comparisons."""

    def __init__(self, init: list[JsonScalar]|str|None = None):
        self._set: set[Const] = set()
        if init:
            for item in init:
                self.add(item)

    def __len__(self):
        return len(self._set)

    def __iter__(self):
        return [ item._val for item in self._set ]

    def __contains__(self, item):
        return Const(item) in self._set

    def add(self, item):
        self._set.add(Const(item))

    def discard(self, item):
        self._set.discard(Const(item))


class ConstMap(MutableMapping[JsonScalar, CheckFun]):
    """A mapping of constants to check functions."""

    def __init__(self):
        self._map: dict[Const, CheckFun] = {}

    def __setitem__(self, key, val):
        self._map[Const(key)] = val

    def __getitem__(self, key):
        return self._map[Const(key)]

    def __delitem__(self, key):
        del self._map[Const(key)]

    def __iter__(self):
        return [ (k._val, v) for k, v in self._map.items() ]

    def __len__(self):
        return self._map.__len__()
