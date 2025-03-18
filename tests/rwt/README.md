# Transformation Tests

Transformations of a model into another model.

## Syntax

Outline of a possible syntax (WIP)

```json
{
  "$": {
    "": "$URL of current model",
    "????": "URL of model spec",
    "name": "value"
  },
  "%": {
    "#": "this is a comment",
    "path#to#var.path.to.prop": {
      "|": [
        {
          "#": "this is a comment",
          "?~": "replacement value, or added definition?!",
          "?-": [ "fields", "or", "items", "to", "remove" ],
          "?+": { "|": [ { "prop": "toMerge" }, [ "items", "to", "append" ] ] }
        },
        "$ANY"
      ]
    }
  }
}
```
