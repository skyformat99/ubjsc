#!/bin/bash
set -x
test -d build && rm -r build

mkdir build
cd build || exit 1

cmake .. || exit 1
make test-ubjsc test-ubjsc-glues test-ubjsc-glue-dict-ptrie ubjspy \
    ubj2js js2ubj ubjq || exit 1
ctest -VV . || exit 1
