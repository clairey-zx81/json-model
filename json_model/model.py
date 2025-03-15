import logging
from .utils import ModelError, Path, Jsonable


class JsonModel:
    """JSON Model v2."""

    LIST_KW = ["|", "&", "^", "+"]
    ROOT_KW = ["$", "%"]
    SCAL_KW = ["@"]
    MISC_KW = ["!", "#", "<", "<=", ">", ">=", "=", "!="]
    TRAN_KW = ["+", "-", "~"]
    CONS_KW = MISC_KW + ["@"]
    KEYWORDS = LIST_KW + ROOT_KW + SCAL_KW + MISC_KW + TRAN_KW

    STR_SENTINELS = "_/$=."
    PROP_SENTINELS = "?!"
    SENTINELS = STR_SENTINELS + PROP_SENTINELS

    PREDEFS_MODELS: dict[str, Jsonable] = {
        "NONE": {"&": []},
        "ANY": {"|": []},
        "STRING": "",
        "BOOL": True,
        "INT": -1,
        "POS": 0,
        "FLOAT": -1.0,
        "NUMBER": {"|": [-1, -1.0]},
        "URL": r"/^\w+://.*/",
        "DATE": r"/^\d\d\d\d-\d\d?-\d\d?$/",  # FIXME
        # to be continued…
        "optBOOL": {"|": [None, "$BOOL"]},
        "optINT": {"|": [None, "$INT"]},
        "optPOS": {"|": [None, "$POS"]},
        "optFLOAT": {"|": [None, "$FLOAT"]},
        "optNUMBER": {"|": [None, "$NUMBER"]},
        "optSTRING": {"|": [None, "$STRING"]},
        "optURL": {"|": [None, "$URL"]},
        "optDATE": {"|": [None, "$DATE"]},
        # to be continued…
    }

    def __init__(self, model: Jsonable):
        self._model = model
        # %: names and rewrites
        self._name: dict[str, str] = {}
        self._rewrite: dict[str, Jsonable] = {}
        self._init_pc: dict[str, Jsonable] = {}
        if isinstance(model, dict) and "%" in model:
            # checks
            if not isinstance(model["%"], dict):
                raise ModelError(f"expecting an object at {['$', '%']}")
            bads = {
                name: kw
                    for name, kw in model["%"].items()
                        if (not isinstance(name, str) or name != "#" or
                            not isinstance(kw, str) or kw not in JsonModel.KEYWORDS)
            }
            if bads:
                lpath = ["$", "%"]
                raise ModelError(f"keyword renames must be json model keywords at {lpath}: {bads}")
            # keyword localization
            self._name = {
                name: kw
                    for name, kw in model["%"].items()
                        if isinstance(name, str) and name.startswith(".") and isinstance(kw, str)
            }
            # RENAMING!?
            # FIXME what is the scope of renamings, eg wrt references?
            self._model = model = self.rename(model, ["$"], True)
        if isinstance(model, dict) and "%" in model:
            # extract rewrites
            self._rewrite = {
                name: rw
                    for name, rw in model["%"].items()
                        if isinstance(name, str) and not name.startswith(".")
            }
            self._init_pc = model["%"]
            del model["%"]
        # definitions
        self._defs: dict[str, JsonModel] = {}
        self._init_dl: dict[str, Jsonable] = {}
        if isinstance(model, dict) and "$" in model:
            self._defs = {
                # NOTE for now models are not resolved
                n: JsonModel(m)
                    for n, m in model["$"].items()
                        if isinstance(n, str) and n != "#"
            }
            self._init_dl = model["$"]
            del model["$"]
        # TODO resolve references!
        # TODO apply rewrites!
        # TODO compute "+"

    def __json__(self) -> Jsonable:
        """Convenient JsonModel display."""
        return {
            "model": self._model,
            "defs": {name: jm.__json__() for name, jm in self._defs.items()},
            "rename": self._name,
            "rewrite": self._rewrite
        }

    def rename(self, model: Jsonable, path: Path = ["$"], root: bool = False):
        """Apply keyword renaming.

        NOTE we cannot simply use the recurse function because keywords
        are must be updated before proceeding.
        """
        # FIXME should check that all are ".…" are replaced?!
        if root and not self._name:
            return model
        if root and isinstance(model, dict):
            if "$" in model:
                defs = model["$"]
                model["$"] = {
                    n: self.rename(m, path + ["$", n])
                        for n, m in model["$"].items()
                            if n != "#"
                }
                if "#" in defs:
                    model["$"]["#"] = defs["#"]
            if "%" in model:
                # TODO
                ...
        else:  # not root sanity check
            if isinstance(model, dict) and ("$" in model or "%" in model):
                raise ModelError(f"'$' or '%' only at root, found at {path}")
        if model is None or isinstance(model, (bool, int, float, str)):
            return model
        elif isinstance(model, list):
            return [self.rename(m, path + [i]) for i, m in enumerate(model)]
        elif isinstance(model, dict):
            new: dict[str, Jsonable] = {}
            # rename
            for name, val in model.items():
                assert isinstance(name, str)
                repl = self._name[name] if name in self._name else name
                if repl in new:
                    raise ModelError(f"cannot rename {name} to {repl} at {path}")
                new[repl] = val
            assert len(new) == len(model)
            model, new = new, {}
            # recurse
            if "@" in model:
                allowed_kw = JsonModel.CONS_KW + JsonModel.ROOT_KW if root else []
                bads = [op for op in model.keys() if op not in allowed_kw]
                if bads:
                    raise ModelError(f"unexpected constraint keywords at {path}: {bads}")
                model["@"] = self.rename(val, path + ["@"])
            elif "|" in model or "&" in model or "^" in model or "+" in model:
                ops = [o for o in model.keys() if o not in ("#", "$", "%")]
                if len(ops) != 1:
                    raise ModelError(f"cannot mix list operators at {path}: {ops}")
                op, lpath = ops[0], path + ops
                if not isinstance(model[op], list):
                    raise ModelError(f"keyword {op} expects an array at {lpath}")
                model[op] = self.rename(model[op], lpath)
            else:  # simple Object
                for key, val in model.items():
                    lpath = path + [key]
                    k = self._name[key] if key in self._name else key
                    if k in new:
                        raise ModelError(f"rename collision at {lpath}: {k}")
                    new[k] = self.rename(val, lpath)
            return model
        else:  # pragma: no cover
            raise ModelError(f"unexpected model element while renaming: {type(model)}")


def test_script():

    logging.basicConfig()

    import json
    import argparse
    ap = argparse.ArgumentParser()
    # TODO resolver
    ap.add_argument("jsons", nargs="*", help="JSON Models to load")
    args = ap.parse_args()

    for fn in args.jsons:
        with open(fn) as file:
            print(f"# {fn}")
            jm = JsonModel(json.load(file))
            print(json.dumps(jm.__json__(), sort_keys=True, indent=2))
