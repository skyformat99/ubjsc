#!/bin/bash

astyle -q {include,src,test}/*.{c,h} 

test -d dist && rm -rf dist
test -d build && rm -rf build

mkdir build
cd build
mkdir logs

echo "conan..."
conan install .. &> logs/conan.txt || exit 1

echo "cmake..."
cmake -DCMAKE_INSTALL_PREFIX:PATH=../dist -DCMAKE_BUILD_TYPE=Debug .. &> logs/cmake.txt|| exit 1

echo "build..."
make all &> logs/build.txt || exit 1

echo "test..."
ctest -VV . &> logs/test.txt || exit 1

echo "coverage..."
make coverage &> logs/coverage.txt

echo "valgrind..."
valgrind --leak-check=full bin/ubjstest &> logs/valgrind.txt || exit 1

echo "ohcount..."
ohcount ../ubjs/*.{c,h} > logs/loc-impl.txt
ohcount -i ../ubjs/*.{c,h} >> logs/loc-impl.txt
ohcount ../test/*.{c,h} > logs/loc-test.txt
ohcount -i ../test/*.{c,h} >> logs/loc-test.txt

echo "dist..."
make install/strip

echo "OK!"
cd ..
