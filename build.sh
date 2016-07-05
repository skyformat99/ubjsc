#!/bin/bash
echo '***** BUILD *****'

test -d build && rm -rf build

mkdir build
cd build
mkdir logs

echo "conan..."
if ! conan install .. &> logs/build-conan.txt
then
	cat logs/build-conan.txt
	exit 1
fi

echo "cmake..."
if ! cmake -DCMAKE_BUILD_TYPE=Debug .. &> logs/build-cmake.txt
then
	cat logs/build-cmake.txt
	exit 1
fi

echo "build..."
if ! make all &> logs/build-make.txt
then
	cat logs/build-make.txt
	exit 1
fi

echo "OK"
cd ..
