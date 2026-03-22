# set perllib with bash: source $PWD/path/to/env.bash

DIR=$(dirname $BASH_SOURCE)
export PERLLIB="$DIR/lib:."
