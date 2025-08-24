#! /usr/bin/env python
import json_model as jm

# model and value
person = { "name": "/^\\w+$/", "born": "$DATE" }
hobbes = { "name": "Hobbes", "born": "2020-07-29" }

# direct model
is_person = jm.model_checker_from_json(person)

# from a URL
is_model = jm.model_checker_from_url("https://json-model.org/models/json-model", resolver=jm.resolver.Resolver())

# use model checkers on JSON values
print("hobbes is a person:", is_person(hobbes))
print("hobbes is a model:", is_model(hobbes))
print("person is a person:", is_person(person))
print("person is a model:", is_model(person))
