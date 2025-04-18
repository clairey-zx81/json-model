import json
from .types import ModelError, ModelPath, Jsonable
from .url_cache import JsonURLCache
from .utils import log


class Resolver:
    """Resolve references to json data.

    - `cache_dir`: where to store downloaded jsons.
    - `maps`: url to directory mapping for testing.
    """

    def __init__(self, cache_dir: str|None = None, maps: dict[str, str] = {}):
        self._maps = maps
        self._cache = JsonURLCache(cache_dir)
        self._jsons: dict[str, Jsonable] = {}

    def __call__(self, ref: str, path: ModelPath):
        """Resolve a reference."""

        # separate fragment
        # FIXME use parse url instead?
        if "#" in ref:
            url, fragment = ref.split("#", 1)
        else:
            url, fragment = ref, None

        # follow mappings
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
            file = url
        elif ref.startswith("file://"):
            file = url[7:]
        elif not ":" in ref:
            file = "./" + ref
        else:
            file = None

        # TODO handle fragment
        if file:
            for fn in [file, file + ".json", file + ".model", file + ".model.json"]:
                try:
                    with open(fn) as f:
                        log.info(f"loading: {fn}")
                        self._jsons[url] = j = json.load(f)
                        return j
                except FileNotFoundError:
                    log.debug(f"no such file: {fn}")
                    continue
            raise ModelError(f"cannot resolve: {file}")
        else:  # other URLs
            self._jsons[url] = j = self._cache.load(url)
            return j
