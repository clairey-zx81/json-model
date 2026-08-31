# AJV Docker and Wrapper

## Build

```sh
docker build -t zx80/ajv-cli -f ajv.docker .
```

## Run

Using the docker wrapper:

```sh
ajv-cli compile --messages=false --code-optimize=2 -s foo.schema.json -o foo.cjs
ajv-cli node foo.cjs -T 1000 *.json
```

## TODO

- check for optimization options
- actually strip error messaging
- handle errors
