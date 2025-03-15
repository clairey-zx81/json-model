import json
from .utils import ModelError, Path, Jsonable
from .url_cache import JsonURLCache


class Resolver:

    def __init__(self, cache_dir: str|None = None, maps: dict[str, str] = {}):
        self._maps = maps
        self._cache = JsonURLCache(cache_dir)
        self._local: dict[str, Jsonable] = {}

    def __call__(self, ref: str, path: Path):

        # FIXME detect local references
        if ":" not in ref:
            return ref

        # FIXME handle '#'
        assert "#" not in ref, "not implemented yet: {ref}"

        iref = ref

        changes, previous = 0, -1
        while changes != previous and changes <= len(self._maps):
            previous = changes
            for s, d in self._maps.items():
                if ref.startswith(s):
                    ref = d + ref[len(s):]
                    changes += 1

        if changes > len(self._maps):
            raise ModelError(f"URL mapping cycle detected, cannot resolve at {path}: {iref}")

        if ref in self._local:
            return self._local[ref]

        # handle local files
        if ref.startswith("./"):
            fn = ref
        elif ref.startswith("file://"):
            fn = ref[7:]
        else:
            fn = None

        if fn:
            with open(fn) as f:
                j = json.load(f)
                self._local[ref] = j
                return j

        # other URLs
        return self._cache.load(ref)
