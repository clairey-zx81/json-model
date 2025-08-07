.PHONY: clean
clean:
	$(RM) *.class json_model/*.class json-model.jar

.PHONY: compile
# -Xlint:unchecked
compile:
	javac -Xlint:deprecation json_model/*.java

.PHONY: jar
jar: json-model.jar

json-model.jar: compile
	jar cf $@ json_model/*.class
