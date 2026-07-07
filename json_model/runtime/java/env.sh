# set classpath: source $PWD/path/to/env.sh
# this assumes a build using maven: make mvn.jar mvn.deps

dir=$(dirname $BASH_SOURCE)

export CLASSPATH=$(echo $dir/target/*.jar)

for jar in $dir/target/dependency/*.jar ; do
  CLASSPATH+=":$jar"
done

CLASSPATH+=":."
