import json_model as jm

# direct model definition with 2 mandatory properties
person_model: jm.Jsonable = {
  "name": "/^[a-z]+$/i",
  "born": "$DATE"
}

# create a dynamically compiled checker function for the model
checker = jm.model_checker_from_json(person_model)

# test if JSON (Python) values validity
good_person = { "name": "Hobbes", "born": "2020-07-29" }
bad_person = { "name": "Unknown" }
print(good_person, "->", checker(good_person))
print(bad_person, "->", checker(bad_person))
reasons: jm.Report = []
assert not checker(bad_person, "", reasons)
print("reasons:", reasons)
