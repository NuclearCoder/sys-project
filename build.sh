#!/bin/sh

cd cmake-build-debug
cmake ..
make

rm -f cmdqueue
killall -qw sys_project

echo "-- Running...\n"

./sys_project &
sleep 0.05

./client $@ &

wait





