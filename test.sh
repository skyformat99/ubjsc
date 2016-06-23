#!/bin/bash
echo "***** TEST *****"

test -d build || exit 1
cd build

ctest -VV . &> logs/test-ctest.txt || exit 1

echo "OK!"
cd ..

