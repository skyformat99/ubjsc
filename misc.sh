#!/bin/bash
echo "***** MISC *****"

test -d build || exit 1
cd build

echo "coverage..."
make coverage &> logs/misc-coverage.txt

echo "valgrind..."
valgrind --leak-check=full bin/unittests &> logs/misc-valgrind.txt

echo "ohcount..."
ohcount ../src/*.c ../src/*.h ../include/*.h > logs/misc-loc-impl.txt
ohcount -i ../src/*.c ../src/*.h ../include/*.h  >> logs/misc-loc-impl.txt
ohcount ../test/*.{c,h} > logs/misc-loc-test.txt
ohcount -i ../test/*.{c,h} >> logs/misc-loc-test.txt

echo "OK"
cd ..
