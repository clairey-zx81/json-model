#! /bin/bash
#
# set/reset benchmarking on calcutta
#

if [ "$(hostname)" != "calcutta" ] ; then
  echo "$0: must run on calcutta" >&2
  exit 1
fi

op=${1:-on}

if [ "$op" = "on" ] ; then
  echo "$0: benchmarking setup"
  # temperature remains below 80°C (90W) with most core active
  # NOTE limit parallelism to 12 for java, 20 for others (24 cores, can handle HT)
  sudo cpupower frequency-set -g performance
  sudo cpupower frequency-set -u 2.4GHz
  sudo cpupower frequency-set -d 2.4GHz
  echo off | sudo tee /sys/devices/system/cpu/smt/control
elif [ "$op" = "off" ] ; then
  echo "$0: benchmarking reset"
  sudo cpupower frequency-set -g powersave
  sudo cpupower frequency-set -u 4.0GHz
  sudo cpupower frequency-set -d 1.2GHz
  echo on | sudo tee /sys/devices/system/cpu/smt/control
fi

# show status
cpupower frequency-info
