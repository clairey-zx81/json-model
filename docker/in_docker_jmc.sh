#! /bin/bash
#
# Run JMC under some id
#

if [ $(id -u) -ne 0 ] ; then
  echo "$0 unexpected non-root user: $(uid -u)" >&2
  exit 1
fi

uid=$1
shift

# create or reuse user of expected uid
if ! id $uid > /dev/null 2>&1 ; then
  created=1
  user=u$uid
  adduser --uid $uid --quiet --disabled-password --comment $user $user
else
  created=
  user=$(id -nu $uid)
fi

# run jmc command as the user
cd /workspace
su -s /bin/bash $user -c "mkdir /home/$user/.cache"
su -s /bin/bash $user -c "/venv/bin/jmc $*"
status=$?

# cleanup
# [ "$created" ] && deluser --quiet --remove-home $user

exit $status
