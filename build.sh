#!/bin/bash
echo '***** BUILD *****'

test -d build && rm -rf build

mkdir build
cd build

if ! cmake -DCMAKE_BUILD_TYPE=Debug ..
then
    exit 1
fi

if ! cmake --build .
then
    exit 1
fi

if ! ctest -VV .
then
    exit 1
fi

cd ..
