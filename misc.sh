#!/bin/bash
echo "***** MISC *****"

test -d build || exit 1
cd build

echo "coverage..."
make coverage &> logs/misc-coverage.txt

echo "valgrind..."
valgrind --leak-check=full bin/unittests &> logs/misc-valgrind.txt
valgrind --leak-check=full --xml=yes --xml-file=valgrind.xml bin/unittests

echo "cppcheck..."
cppcheck --enable=all ../include/*.h ../src/*.c ../src/*.h ../test/*.h ../test/*.c &> logs/misc-cppcheck.txt
cppcheck --xml --xml-version=2 --enable=all ../include/*.h ../src/*.c ../src/*.h ../test/*.h ../test/*.c 2> cppcheck.xml

echo "ohcount..."
ohcount ../src/*.c ../src/*.h ../include/*.h > logs/misc-loc-impl.txt
ohcount -i ../src/*.c ../src/*.h ../include/*.h  >> logs/misc-loc-impl.txt
ohcount ../test/*.{c,h} > logs/misc-loc-test.txt
ohcount -i ../test/*.{c,h} >> logs/misc-loc-test.txt

echo "OK"
cd ..
