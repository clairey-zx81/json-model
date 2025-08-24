#! /bin/env python
import person  # adjust depending on where the generated module is stored                           
                                                                                                    
person.check_model_init()                                                                           
print("hobbes is a person:", person.check_model({"name": "Hobbes", "birth": "2020-07-29"}))         
person.check_model_free()                                                                           
