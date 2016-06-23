#!/bin/bash

test -d build && rm -rf build

mkdir build
cd build
mkdir logs

echo "conan..."
conan install .. &> logs/build-conan.txt || exit 1

echo "cmake..."
cmake -DCMAKE_BUILD_TYPE=Debug .. &> logs/build-cmake.txt|| exit 1

echo "build..."
make all &> logs/build-build.txt || exit 1

echo "OK"
cd ..
