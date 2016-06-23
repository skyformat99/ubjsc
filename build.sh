#!/bin/bash

astyle -q --recursive '*.h' '*.c'

test -d build && rm -rf build

mkdir build
cd build
mkdir logs

echo "conan..."
conan install .. &> logs/1-conan.txt || exit 1

echo "cmake..."
cmake -DCMAKE_INSTALL_PREFIX:PATH=../dist -DCMAKE_BUILD_TYPE=Debug .. &> logs/2-cmake.txt|| exit 1

echo "build..."
make all &> logs/3-build.txt || exit 1

echo "test..."
ctest -VV . &> logs/4-test.txt || exit 1

echo "coverage..."
make coverage &> logs/5-coverage.txt || exit 1

echo "valgrind..."
valgrind --leak-check=full bin/unittest &> logs/6-valgrind.txt || exit 1

echo "ohcount..."
ohcount ../{src,include}/*.{c,h} > logs/7-loc-impl.txt
ohcount -i ../{src,include}/*.{c,h} >> logs/7-loc-impl.txt
ohcount ../test/*.{c,h} > logs/7-loc-test.txt
ohcount -i ../test/*.{c,h} >> logs/7-loc-test.txt

echo "OK!"
cd ..
