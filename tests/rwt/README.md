# Transformation Tests

Transformations of a model into another model.

## Syntax

Outline of a possible syntax (WIP)

```json
{
  "#": "schema version (FIXME apply rewrites!)",
  "?~": "$URL",
  "$": {
    "#": "local model definitions",
    "_": "$URL of current model",
    "": "$ANY"
  },
  "%": {
    "#": "rewrites",
    "/^\\..*$": "/^([|&^+$%/*@=<>!#~]|<=|>=|!=)$/",
    "path#to#var.path.to.prop": {
      "|": [
        {
          "#": "transformation spec",
          "?/": [ "fields", "or", "items", "to", "remove" ],
          "?*": { "|": [ { "prop": "toMerge" }, [ "items", "to", "append" ] ] }
        },
        "$ANY"
      ]
    }
  },
  "@": "$target…"
}
```

## TODO

- accept relative URL? automaps?
