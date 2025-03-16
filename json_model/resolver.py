import json
from .utils import ModelError, Path, Jsonable
from .url_cache import JsonURLCache


class Resolver:

    def __init__(self, cache_dir: str|None = None, maps: dict[str, str] = {}):
        self._maps = maps
        self._cache = JsonURLCache(cache_dir)
        self._jsons: dict[str, Jsonable] = {}

    def __call__(self, ref: str, path: Path):

        if "#" in ref:
            url, fragment = ref.split("#", 1)
        else:
            url, fragment = ref, None

        changes, previous = 0, -1
        while changes != previous and changes <= len(self._maps):
            previous = changes
            for s, d in self._maps.items():
                if url.startswith(s):
                    url = d + url[len(s):]
                    changes += 1

        if changes > len(self._maps):
            raise ModelError(f"URL mapping cycle detected, cannot resolve at {path}: {ref}")

        if url in self._jsons:
            return self._jsons[url]

        # handle local files
        if url.startswith("./") or url.startswith("../") or url.startswith("/"):
            fn = url
        elif ref.startswith("file://"):
            fn = url[7:]
        else:
            fn = None

        # TODO handle fragment
        if fn:
            with open(fn) as f:
                self._jsons[url] = j = json.load(f)
                return j
        else:  # other URLs
            self._jsons[url] = j = self._cache.load(url)
            return j
