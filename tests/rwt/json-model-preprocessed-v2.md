# Preprocessed JSON Model

A preprocessed JSON Model does not have:

- merge operations (`+`), which have been processed as objects.
- transformations, which have been applied.

The model is built by transforming the meta-model:

- `Add` is nullified with `$NONE` and will be removed from `|`.
- `Rewrite` is nullified with `{}` which is ignored by `+`.
