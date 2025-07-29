#! /usr/bin/env python
import Person
hobbes = {"name": "Hobbes", "birth": "2020-07-29"}
Person.check_model_init()
print("Hobbes is a person:", Person.check_model(hobbes, "", None))
Person.check_model_free()
