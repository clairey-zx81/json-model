# JSON Model How To …

## How to use JSON Model in my _Python_ project?

## How to use JSON Model in my _JavaScript_ project?

## How to use JSON Model in my _Postgres_ database?

1. install the `json_model` Postgres extension, from source _or_
   from [pgxn](https://pgxn.org/dist/json_model/):

   ```sh
   sudo make -C json_model/runtime install
   sudo pgxn install json_model
   ```

2. compile a model to PL/pgSQL:

   ```sh
   jmc -o stuff.sql Stuff.model.sql
   ```

3. load the generated functions into your `stuff` database:

   ```sh
   psql -f stuff.sql stuff
   ```

4. check the root model (empty name) against a `JSONB` value:

   ```sql
   SELECT check_model(JSONB '3.14', '', NULL);  # TRUE or FALSE…
   ```

## How to … ?

