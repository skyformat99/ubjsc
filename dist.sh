#!/bin/bash
echo '***** DIST *****'

test -d build || exit 1
cd build

echo "packages..."
cmake .. &> logs/8-cmake.txt|| exit 1
make package package_source &> logs/8-make.txt || exit 1

echo "OK"
cd ..
