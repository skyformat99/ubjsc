#!/bin/bash
echo '***** BUILD *****'

test -d build && rm -rf build

mkdir build
cd build
mkdir logs

echo "conan..."
conan install .. &> logs/build-conan.txt || (cat logs/build-conan.txt; exit 1)

echo "cmake..."
cmake -DCMAKE_BUILD_TYPE=Debug .. &> logs/build-cmake.txt|| (cat logs/build-cmake.txt; exit 1)

echo "build..."
make all &> logs/build-make.txt || (cat logs/build-make.txt; exit 1)

echo "OK"
cd ..
