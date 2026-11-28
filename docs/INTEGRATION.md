# JSON Schema Integration

## Python Flask FSA

Maybe add keyword related extension mechanism:

```python
@app.get("/foo", authz="OPEN", model="Name")
def get_foo():
    return a_model_thing, 200
```

Not very interesting: it is probably enough to only validate _incoming_ data and let the client
validate server outgoing data, or the database validate stored data.

For incoming data validation, this is already achieved with pydantic, so a pydantic export
would be enough?

## Python Script

- direct import and call of the check function?

## Python ORM

- SQLAlchemy
- Django

## JavaScript Client in Browser

- `fetch`
- `axios`
- `swr`

## JavaScript Server with Node

## Ruby on Rails

## Postgres JSON Data

- JS with `plv8` extension and some glue?

  ```sh
  pgxnclient install plv8
  ```

  The glue is not obvious.

- plpython?

- PL/pgSQL: Generate a set of PL/pgSQL functions?

  how to handle variable declaration with the code generator? `Block` is too simplistic for that.
  possibly add a stupid prefix which is grep-ed when generating the final function?

## MongoDB JSON Data

- JSON Schema (bson) export?
- MongoDB validation extension, hook? _not found_
