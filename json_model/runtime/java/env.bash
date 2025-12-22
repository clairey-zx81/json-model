# set classpath with bash: source $PWD/path/to/env.bash

DIR=$(dirname $BASH_SOURCE)
export CLASSPATH="/usr/share/java/gnu-getopt.jar"

for jar in $DIR/*.jar ; do
  CLASSPATH+=":$jar"
done

CLASSPATH+=":."
