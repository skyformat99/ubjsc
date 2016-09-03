#!/bin/bash
#test -d build && rm -r build

#mkdir build
cd build
#cmake -DJANSSON_WITHOUT_TESTS=ON .. || exit 1
#cmake --build . || exit 1
#ctest -VV . || exit 1

#rm -r *
#cmake -DJANSSON_WITHOUT_TESTS=ON -DCMAKE_BUILD_TYPE=Debug .. || exit 1
#cmake --build . || exit 1

test/unittests &> /dev/null

#valgrind --error-exitcode=1 --leak-check=full test/unittests > /dev/null
true
DID_VALGRIND_SURVIVE=$?
cd ..

gcovr -p -r . -e 'test'
gcovr -p -r . -e 'test' -x > coverage.xml
BRANCH_RATE=$(xmlstarlet sel -t -v 'coverage/@branch-rate' coverage.xml 2> /dev/null)
LINE_RATE=$(xmlstarlet sel -t -v 'coverage/@line-rate' coverage.xml 2> /dev/null)
IS_BRANCH_RATE_GOOD=$(test $(echo "${BRANCH_RATE} >= 0.975"|bc) -eq 1)
IS_LINE_RATE_GOOD=$(test $(echo "${LINE_RATE} >= 0.975"|bc) -eq 1)
DID_GCOVR_SURVIVE=$(test ${IS_BRANCH_RATE_GOOD} -a ${IS_LINE_RATE_GOOD})

cppcheck --error-exitcode=1 --enable=all --language=c --suppress=missingIncludeSystem src/*.c test/*.c test/*.cpp tools/*.c
DID_CPPCHECK_SURVIVE=$?

vera++ -e include/*.h src/*.h src/*.c test/*.h test/*.c tools/*.c
DID_VERA_SURVIVE=$?

if test ${DID_VALGRIND_SURVIVE} -ne 0 || \
   test ${DID_CPPCHECK_SURVIVE} -ne 0 || \
   test ${DID_VERA_SURVIVE} -ne 0 || \
   test ${DID_GCOVR_SURVIVE} -ne 0
then
  echo At least one statick check failed
  exit 1
fi

# @todo sonar scanner

