#!/bin/bash
echo "***** MISC *****"

test -d build || exit 1
cd build

echo "coverage..."
make coverage &> logs/misc-coverage.txt

echo "valgrind..."
valgrind --leak-check=full bin/unittests &> logs/misc-valgrind.txt

echo "cppcheck..."
cppcheck --enable=all ../include/*.h ../src/*.c ../src/*.h ../test/*.h ../test/*.c &> logs/misc-cppcheck.txt

echo "vera++..."
vera++ -w include/*.h src/*.h src/*.c test/*.h test/*.c &> logs/misc-vera.txt

echo "OK"
cd ..
