#!/bin/bash
test -d build || ./build.sh || exit 1

cd build
cmake -DCMAKE_BUILD_TYPE=Debug .. || exit 1
cmake --build . || exit 1

echo "########## Valgrind"
# Yeah, we really use this much memory.
valgrind --error-exitcode=1 --leak-check=full --show-leak-kinds=all \
    --track-origins=yes ./unittests-c > /dev/null
DID_VALGRIND_SURVIVE=$?
echo "Did valgrind survive? ${DID_VALGRIND_SURVIVE}"

echo "########## Gcovr"
#./unittests-c &> /dev/null
ctest
cd ..
gcovr -p -r . -e 'test' -e 'ptrie'
gcovr -p -r . -e 'test' -e 'ptrie' -x > coverage.xml
BRANCH_RATE=$(xmlstarlet sel -t -v 'coverage/@branch-rate' \
    coverage.xml 2> /dev/null)
LINE_RATE=$(xmlstarlet sel -t -v 'coverage/@line-rate' \
    coverage.xml 2> /dev/null)
rm coverage.xml
DID_GCOVR_SURVIVE=0
if test $(echo "${BRANCH_RATE} >= 0.9"|bc) -eq 0
then
    DID_GCOVR_SURVIVE=1
fi

if test $(echo "${LINE_RATE} >= 0.95"|bc) -eq 0
then
    DID_GCOVR_SURVIVE=1
fi
echo "Branch coverage rate: ${BRANCH_RATE}"
echo "Line coverage rate: ${LINE_RATE}"
echo "Did gcovr survive? ${DID_GCOVR_SURVIVE}"

echo "########## Cppcheck"
cppcheck --error-exitcode=1 --enable=all --language=c --suppress=missingIncludeSystem src/*.c test/*.c test/*.cpp tools/*.c
DID_CPPCHECK_SURVIVE=$?
echo "Did cppcheck survive? ${DID_CPPCHECK_SURVIVE}"

echo "########## Vera"
vera++ -e include/*.h src/*.h src/*.c test/*.h test/*.c tools/*.c
DID_VERA_SURVIVE=$?
echo "Did vera survive? ${DID_VERA_SURVIVE}"

if test ${DID_VALGRIND_SURVIVE} -ne 0 || \
   test ${DID_CPPCHECK_SURVIVE} -ne 0 || \
   test ${DID_VERA_SURVIVE} -ne 0 || \
   test ${DID_GCOVR_SURVIVE} -ne 0
then
  echo "At least one static check failed"
  exit 1
fi

echo "########## Doxygen"
cd build
make man html
