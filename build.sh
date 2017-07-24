#!/bin/bash
set -x
test -d build && rm -r build

mkdir build
cd build || exit 1

cmake -DCMAKE_BUILD_TYPE=Release .. || exit 1
make || exit 1

cmake -DCMAKE_BUILD_TYPE=Debug -DWITH_TESTING=ON .. || exit 1
make || exit 1
ctest -VV . || exit 1
