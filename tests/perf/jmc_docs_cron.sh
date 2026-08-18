#! /bin/bash
#
# build and deploy web site
#

WORK=${WORK:-$HOME/dev/cron-json-model}
DEST=${DEST:-$HOME/dev/www-json-model}
BRANCH=${BRANCH:-post}

function err()
{
  local status=$1
  shift 1
  echo "$@" >&2
  exit $status
}

# sanity checks
test -d $WORK || err 1 "missing working directory: $WORK"
test -d $WORK/.git || err 1 "missing git directory: $WORK/.git"
test -d $DEST/. || err 1 "missing target directory: $DEST/."

for cmd in make python cloc git cmp rsync cp pod2markdown ; do
  type $cmd > /dev/null 2>&1 || err 1 "missing command: $cmd"
done

# pull
cd $WORK || err 2 "cannot cd to: $WORK"
git checkout $BRANCH || err 3 "cannot git checkout $BRANCH: $?"
git pull || err 3 "cannot git pull: $?"
git submodule update || err 3 "cannot git submodule update: $?"

# check
git rev-parse HEAD > .published.tmp || err 3 "cannot git rev-parse HEAD: $?"
cmp -s .published.tmp .published.last && err 0 "nothing new to publish"

# environment needed for versioning
test -d venv || make venv/.init || err 4 "cannot build venv: $?"
source venv/bin/activate

# build and deploy
make clean.site || err 4 "cannot clean site: $?"
make _site || err 4 "cannot build site: $?"
rsync -rav _site/. $DEST/. || err 5 "cannot rsync site: $?"

# status
cp .published.tmp .published.last || err 6 "cannot update status: .published.last"
