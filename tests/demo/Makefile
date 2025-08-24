.PHONY: clean
clean:
	$(RM) person.out person.c person.py person.js person.mjs person.sql \
	    person.pl Person.pm person.schema.json Person*.class

person.out: person.model.json
	jmc -o $@ $<

person.py: person.model.json
	jmc -o $@ $<

person.js: person.model.json
	jmc -o $@ $<

person.c: person.model.json
	jmc -o $@ $<

person.schema.json: person.model.json
	jmc -o $@ $<

Person.class: person.model.json
	jmc -o $@ $<
