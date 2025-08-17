#
# URL to JSON with 2 level caching
#

import os
import hashlib
import re
import urllib.parse
import requests
import json
import yaml

from .utils import Jsonable, log


class JsonURLCache:
    """Cache JSON URL contents."""

    # FIXME should invalidate old cache entries?

    def __init__(self, cache_dir: str|None = None, ignore: bool = False):

        # loader
        self._requests = requests.Session()
        self._ignore = ignore

        # cache retrieved url
        self._cache_dir: str
        if cache_dir is not None:
            self._cache_dir = cache_dir
        elif "JSON_MODEL_CACHEDIR" in os.environ:
            self._cache_dir = os.environ["JSON_MODEL_CACHEDIR"]
        else:
            self._cache_dir = os.environ.get("HOME", ".") + "/.cache/json-model"

        # create cache dir if necessary
        if not os.path.exists(self._cache_dir):
            os.mkdir(self._cache_dir)
        assert os.path.isdir(self._cache_dir)

        # in-memory cache
        self._cache: dict[str, Jsonable] = {}

    def getJSON(self, url: str) -> Jsonable:
        res = self._requests.get(url)
        try:
            return res.json()
        except requests.JSONDecodeError as e:  # else try YAML
            log.debug(e)
            return yaml.full_load(res.text)

    def load(self, url: str):
        """Load JSON URL."""

        if self._ignore:
            return self.getJSON(url)

        # hmmm… basically remove fragment
        up = urllib.parse.urlparse(url)
        u = up.scheme + "://" + up.netloc + up.path
        if up.query:
            u += "?" + up.query

        # first cache (memory)
        # log.error("skipping cache!")
        if u in self._cache:
            return self._cache[u]

        # second cache (file): we assume no hash collision
        h = hashlib.sha3_256(u.encode("UTF-8")).hexdigest()
        hfile = self._cache_dir + "/" + h
        if os.path.exists(hfile):
            log.info(f"loading: {url}")
            with open(hfile) as f:
                j = json.load(f)
                self._cache[u] = j
                return j

        # download
        log.info(f"downloading: {url}")
        j = self.getJSON(u)
        self._cache[u] = j
        with open(hfile, "w") as f:
            json.dump(j, f, sort_keys=True, indent=2)

        return j

    def clear(self):
        """Clear caches."""
        self._cache.clear()
        for file in os.listdir(self._cache_dir):
            if re.match(r"[0-9a-f]{64}$", file):
                os.unlink(self._cache_dir + "/" + file)
