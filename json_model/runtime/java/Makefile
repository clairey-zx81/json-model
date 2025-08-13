.PHONY: clean
clean:
	$(RM) *.class json_model/*.class json-model.jar
	$(RM) -r target

# direct compilation
.PHONY: compile
# -Xlint:unchecked
compile:
	javac -Xlint:deprecation json_model/*.java

.PHONY: jar
jar: json-model.jar

json-model.jar: compile
	jar cf $@ json_model/*.class

# with maven
.PHONY: mvn.jar
mvn.jar:
	mvn install
	# see generated jar under ./target/
