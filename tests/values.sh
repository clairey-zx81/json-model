#! /bin/bash

for name in "$@" ; do
  if [ -f $name.values.json ] ; then
    echo "skipping $name"
  else
    {
      echo "["
      for t in $name.*.true.json ; do
        echo -n "  [ true,  "
        cat $t
        echo " ],"
      done
      for f in $name.*.false.json ; do
        echo -n "  [ false, "
        cat $f
        echo " ],"
      done
      echo "]"
    } > $name.values.json
  fi
done
