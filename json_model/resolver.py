import sys
import re
import json
from .types import ModelError, ModelPath, Jsonable
from .url_cache import JsonURLCache
from .utils import log


class Resolver:
    """Resolve external references to json data.

    - `cache_dir`: where to store downloaded jsons.
    - `maps`: url to directory mapping for testing.
    """

    def __init__(self, cache_dir: str|None = None, maps: dict[str, str]|None = None):
        self._cache = JsonURLCache(cache_dir)
        self._maps: dict[str, str] = maps if maps else {}
        self._jsons: dict[str, Jsonable] = {}

    def __call__(self, ref: str, path: ModelPath):
        """Resolve an external reference."""

        # separate fragment
        # FIXME remove fragment support?
        if "#" in ref:
            url, _fragment = ref.split("#", 1)
        else:
            url, _fragment = ref, None

        if url == "-":  # no caching, cannot read same input twice?
            log.info(f"reading: stdin")
            return json.load(sys.stdin)

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
        elif ":" not in ref:
            file = "./" + ref
        else:
            file = None

        if file:
            for suffix in ["", ".json", ".model", ".model.json", ".js", ".model.js"]:
                fn = file + suffix
                try:
                    with open(fn) as f:
                        log.info(f"loading: {fn}")
                        j = f.read()
                        # possibly remove js comments, with some guessing
                        if fn.endswith(".js") or re.match(r"(?m)^\s*//\s", j):
                            j = re.sub(r"(?s)/\*.*?\*/", "", j)
                            j = re.sub(r"\s*//\s.*", "", j)
                        self._jsons[url] = j = json.loads(j)
                        return j
                except FileNotFoundError:
                    log.debug(f"no such file: {fn}")
                    continue
            raise ModelError(f"cannot resolve: {file}")
        else:  # other actual URLs will download
            log.info(f"downloading: {url}")
            self._jsons[url] = j = self._cache.load(url)
            return j
