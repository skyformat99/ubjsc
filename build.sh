#!/bin/bash
echo '***** BUILD *****'

test -d build && rm -rf build

mkdir build
cd build
mkdir logs

if ! cmake ..
then
	exit 1
fi

if ! cmake --build .
then
	exit 1
fi

cd ..
