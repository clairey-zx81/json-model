.PHONY: clean
clean:
	$(RM) *.class json_model/*.class json-model.jar

.PHONY: compile
compile:
	javac json_model/*.java

.PHONY: jar
jar: json-model.jar

json-model.jar: compile
	jar cf $@ json_model/*.class
