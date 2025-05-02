# URL to JSON with 2 level caching
#
# TODO add specific environment variable for cache directory, for testing
# TODO fix add url parameters? use provided url as is?

import os
import hashlib
import urllib.parse
import requests
import json
import yaml

from .utils import Jsonable, log

class JsonURLCache:
    """Cache JSON URL."""

    # FIXME should invalidate old cache entries?

    def __init__(self, cache_dir: str|None = None):

        # loader
        self._requests = requests.Session()

        # keep a local copy
        self._cache_dir = cache_dir or (os.environ.get("HOME", ".") + "/.cache/json-model")
        if not os.path.exists(self._cache_dir):
            os.mkdir(self._cache_dir)
        assert os.path.isdir(self._cache_dir)

        # class cache
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

        up = urllib.parse.urlparse(url)
        # FIXME add query?
        u = up.scheme + "://" + up.netloc + up.path

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
            # sort_keys?
            json.dump(j, f, sort_keys=True, indent=2)

        return j
