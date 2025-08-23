#! /usr/bin/env python
import json_model as jm                                                                          
                                                                                                    
hobbes = { "name": "Hobbes", "born": "2020-07-29" }                                              
                                                                                                    
# direct model                                                                                   
person = { "name": "/^\\w+$/", "born": "$DATE" }                                                 
is_person = jm.model_checker_from_json(person)                                                      
print("hobbes is a person:", is_person(hobbes))                                                  
                                                                                                
# from a URL                                                                                     
is_model = jm.model_checker_from_url("https://json-model.org/models/json-model", resolver=jm.resolver.Resolver())
print("person is a model:", is_model(person))                                                    
