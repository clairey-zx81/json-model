#! /bin/env node
import { check_model_init, check_model, check_model_free } from "./person.mjs"
                                                                                                    
check_model_init()                                                                                  
console.log(`hobbes is a person: ${check_model({name: "Hobbes", birth: "2020-07-29"}, '', null)}`)
check_model_free()                                                                                  
