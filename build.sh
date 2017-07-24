#!/bin/bash
set -x
test -d build && rm -r build

mkdir build
cd build || exit 1

cmake .. || exit 1
make

cmake -DWITH_TESTING=ON .. || exit 1
make || exit 1
ctest -VV . || exit 1
