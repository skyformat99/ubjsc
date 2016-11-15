#!/bin/bash
set -x
test -d build && rm -r build

mkdir build
cd build || exit 1

cmake .. || exit 1
cmake --build . || exit 1
ctest -VV . || exit 1
