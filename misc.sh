#!/bin/bash
echo "***** MISC *****"

test -d build || exit 1
cd build

echo "coverage..."
make coverage &> logs/test-coverage.txt || exit 1

echo "valgrind..."
valgrind --leak-check=full bin/unittest &> logs/test-valgrind.txt || exit 1

echo "ohcount..."
ohcount ../{src,include}/*.{c,h} > logs/7-loc-impl.txt
ohcount -i ../{src,include}/*.{c,h} >> logs/7-loc-impl.txt
ohcount ../test/*.{c,h} > logs/7-loc-test.txt
ohcount -i ../test/*.{c,h} >> logs/7-loc-test.txt

echo "OK"
cd ..
