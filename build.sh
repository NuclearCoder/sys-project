#!/bin/sh

mkdir -p build
cd build
cmake ..
make

killall -qw sys-project
rm -f cmdqueue
