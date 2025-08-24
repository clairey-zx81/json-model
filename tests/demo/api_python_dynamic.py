#! /bin/env python
import json_model as jm                                                                             
                                                                                                    
is_person = jm.model_checker_from_url("./Person.model.json")                                        
print("hobbes is a person:", is_person({"name": "Hobbes", "birth": "2020-07-29"}))                  
