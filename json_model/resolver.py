import sys
import re
import yaml

from .mtypes import ModelError, ModelPath, Jsonable
from .url_cache import JsonURLCache
from .utils import log, json_loads

JSON_SUFFIX = ["", ".json", ".model", ".model.json"]
YAML_SUFFIX = [".yaml", ".model.yaml", ".yml", ".model.yml"]
JS_SUFFIX = [".js", ".model.js"]

# guess type based on file contents
JS_RE = r"(?m)^\s*//\s"
JSON_RE = r"(?s)\s*(\[.*\]|\{.*\}|\".*\"|-?\d+(\.\d*)?([eE]-?\d+)?|null|true|false)\s*$"

# numbers, identifiers, "quoted", 'quoted', blanks, whatever (1 char, including separators)
JS_TOKEN = r"(?s)(-?\d+(\.\d*)?([eE]-?\d+)?|\w+|" + \
           r'"([^"]*(\\")?)*"|' + r"'([^']*(\\')?)*'|\s+|\W)"

def jsob2json(string: str) -> str:
    """Parse a js object string and return a json string."""
    tokens: list[str] = []
    for mtoken in re.finditer(JS_TOKEN, string):
        token = mtoken.group(0)
        if (re.match(r"\w", token) and token[0] not in "0123456789" and
                token not in ("null", "false", "true")):
            tokens.append(f"\"{token}\"")
        else:
            tokens.append(token)
    return "".join(tokens)


class Resolver:
    """Resolve external references to jsonable data.

    - `cache_dir`: where to store downloaded jsons.
    - `maps`: url to directory mapping for testing.
    """

    def __init__(self,
                 cache_dir: str|None = None,
                 maps: dict[str, str]|None = None,
                 *,
                 allow_duplicates: bool = False,
                 cache_ignore: bool = False,
            ):
        self._cache = JsonURLCache(cache_dir, cache_ignore)
        self._maps: dict[str, str] = maps if maps else {}
        self._jsons: dict[str, Jsonable] = {}
        self._allow_duplicates = allow_duplicates

    def __call__(self, url: str, *, path: ModelPath = [], follow: bool = True):
        """Resolve an external reference."""

        assert "#" not in url, f"no fragment in {url}"

        if url == "-":  # no caching, cannot read same input twice?
            log.info("reading: stdin")
            return json_loads(sys.stdin.read(), allow_duplicates=self._allow_duplicates)

        # possibly follow mappings
        if follow:
            changes, previous, skip = 0, -1, set()
            while changes != previous:
                previous = changes
                for s, d in self._maps.items():
                    if s not in skip and url.startswith(s):
                        url = d + url[len(s):]
                        skip.add(s)  # do not apply same rule twice
                        changes += 1

        if url in self._jsons:
            return self._jsons[url]

        # handle local files
        if url.startswith("./") or url.startswith("../") or url.startswith("/"):
            file = url
        elif url.startswith("file://"):
            file = url[7:]
        elif ":" not in url:
            file = "./" + url
        else:
            file = None

        if file:
            for suffix in JSON_SUFFIX + JS_SUFFIX + YAML_SUFFIX:
                fn = file + suffix
                try:
                    with open(fn) as f:
                        log.info(f"loading: {fn}")
                        content = f.read()
                        if fn.endswith(".js") or re.match(JS_RE, content):
                            # possibly remove js comments
                            content = re.sub(r"(?s)/\*.*?\*/", "", content)
                            content = re.sub(r"\s*//\s.*", "", content)
                            # quote bare identifiers
                            content = jsob2json(content)
                        # guess content type
                        if fn.endswith(".json") or re.match(JSON_RE, content):
                            # try JSON
                            self._jsons[url] = j = \
                                json_loads(content, allow_duplicates=self._allow_duplicates)
                        else:  # try yaml
                            self._jsons[url] = j = yaml.full_load(content)
                        return j
                except FileNotFoundError:
                    log.debug(f"no such file: {fn}")
                    continue
            raise ModelError(f"cannot resolve: {file}")
        else:  # other actual URLs will download
            log.info(f"downloading: {url}")
            self._jsons[url] = j = self._cache.load(url)
            return j

    def clear(self):
        """Clear underlying cache."""
        self._cache.clear()
