#!/bin/sh

mkdir build
cd build
cmake ..
make

killall -qw sys_project
rm -f cmdqueue

echo "-- Running...\n"

./sys_project &

./client "$@" &

wait





