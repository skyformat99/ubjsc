#!/bin/bash
test -d build && rm -r build

mkdir build
cd build

echo "########## Build & test"

cmake -DJANSSON_WITHOUT_TESTS=ON .. || exit 1
cmake --build . || exit 1
ctest -VV . || exit 1

rm -r *
echo "########## Static analisys"
cmake -DJANSSON_WITHOUT_TESTS=ON -DCMAKE_BUILD_TYPE=Debug .. || exit 1
cmake --build . || exit 1

echo "########## Valgrind"
valgrind --error-exitcode=1 --leak-check=full test/unittests > /dev/null
DID_VALGRIND_SURVIVE=$?
cd ..

echo "########## Gcovr"
test/unittests &> /dev/null
gcovr -p -r . -e 'test'
gcovr -p -r . -e 'test' -x > coverage.xml
BRANCH_RATE=$(xmlstarlet sel -t -v 'coverage/@branch-rate' coverage.xml 2> /dev/null)
LINE_RATE=$(xmlstarlet sel -t -v 'coverage/@line-rate' coverage.xml 2> /dev/null)
DID_GCOVR_SURVIVE=0
if test $(echo "${BRANCH_RATE} >= 0.975"|bc) -eq 0
then
    DID_GCOVR_SURVIVE=0
fi

if test $(echo "${LINE_RATE} >= 0.975"|bc) -eq 0
then
    DID_GCOVR_SURVIVE=0
fi

echo "Branch coverage rate: ${BRANCH_RATE}"
echo "Line coverage rate: ${LINE_RATE}"

echo "########## Cppcheck"
cppcheck --error-exitcode=1 --enable=all --language=c --suppress=missingIncludeSystem src/*.c test/*.c test/*.cpp tools/*.c
DID_CPPCHECK_SURVIVE=$?

echo "########## Vera"
export PATH=${PATH}:/opt/vera/bin
vera++ -e include/*.h src/*.h src/*.c test/*.h test/*.c tools/*.c
DID_VERA_SURVIVE=$?

if test ${DID_VALGRIND_SURVIVE} -ne 0 || \
   test ${DID_CPPCHECK_SURVIVE} -ne 0 || \
   test ${DID_VERA_SURVIVE} -ne 0 || \
   test ${DID_GCOVR_SURVIVE} -ne 0
then
  echo At least one static check failed
  exit 1
fi

# @todo sonar scanner

