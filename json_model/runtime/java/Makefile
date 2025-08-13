SHELL   = /bin/bash
.ONESHELL:

.PHONY: clean
clean:
	$(RM) *.class json_model/*.class json-model*.jar json-model-*.zip
	$(RM) -r target org doc

# direct compilation
.PHONY: compile
# -Xlint:unchecked
compile:
	javac -Xlint:deprecation json_model/*.java

.PHONY: jar
jar: json-model.jar

json-model.jar: compile
	jar cf $@ json_model/*.class

#
# With maven
#
.PHONY: mvn.jar
mvn.jar:
	mvn install
	# see generated jar under ./target/

#
# 2nd stage
#
VERSION = $(shell sed -n 's,\s*<version>\(.*\)</version>,\1,p;/version/q' pom.xml)
JMV = json-model-$(VERSION)

.PHONY: src.jar
src.jar: $(JMV)-sources.jar
$(JMV)-sources.jar:
	jar cf $@ json_model/*.java

.PHONY: doc.jar
doc.jar: $(JMV)-javadoc.jar
$(JMV)-javadoc.jar:
	javadoc -d doc json_model
	jar cf $@ doc/

.PHONY: zip
zip: $(JMV).zip

$(JMV).zip: mvn.jar src.jar doc.jar
	dir="org/json-model/json-model/$(VERSION)"
	mkdir -p "$$dir"
	# copy POM and JAR files
	cp pom.xml "$$dir"/$(JMV).pom
	cp target/$(JMV).jar "$$dir"/
	cp $(JMV)-sources.jar "$$dir"/
	cp $(JMV)-javadoc.jar "$$dir"/
	# compute md5 & sha1 & signature
	for file in "$$dir"/*.{jar,pom} ; do
	  md5sum "$$file" | cut -d' ' -f1 > "$$file".md5
	  sha1sum "$$file" | cut -d' ' -f1 > "$$file".sha1
	  gpg -ab "$$file"
	  gpg --verify "$$file".asc
	done
	# zip
	zip -r $@ org/
