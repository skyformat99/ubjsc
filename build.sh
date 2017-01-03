#!/bin/bash
set -x
test -d build && rm -r build

mkdir build
cd build || exit 1

cmake .. || exit 1
make test-ubjsc test-ubjsc-glue-dict-ptrie ubjspy || exit 1
ctest -VV . || exit 1
