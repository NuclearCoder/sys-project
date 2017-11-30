#!/bin/sh

cd cmake-build-debug
cmake ..
make

killall -qw sys_project
rm -f cmdqueue

echo "-- Running...\n"

./sys_project &
sleep 0.05

./client "$@" &

wait





