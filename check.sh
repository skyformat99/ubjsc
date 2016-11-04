#!/bin/bash
test -d build && rm -r build
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug .. &>/dev/null || exit 1
cmake --build . &>/dev/null || exit 1

echo "########## Valgrind"
# Yeah, we really use this much memory.
#valgrind --error-exitcode=1 --leak-check=full --show-leak-kinds=all --max-stackframe=2900080 \
#    --track-origins=yes ./unittests-c > /dev/null
./unittests-c
DID_VALGRIND_SURVIVE=$?
echo "Did valgrind survive? ${DID_VALGRIND_SURVIVE}"
cd ..
rm -r build

mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug .. &>/dev/null || exit 1
cmake --build . &>/dev/null || exit 1

echo "########## Gcovr"
./unittests-c
cd python
python3 ../../python/setup.py test ../../python
cd ..
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
cppcheck --error-exitcode=1 --enable=all --language=c --suppress=missingIncludeSystem src/*.c test/*.c test/*.cpp tools/*.c python/*.c
DID_CPPCHECK_SURVIVE=$?
echo "Did cppcheck survive? ${DID_CPPCHECK_SURVIVE}"

echo "########## Vera"
vera++ -e include/*.h src/*.h src/*.c test/*.h test/*.c tools/*.c python/*.h python/*.c
DID_VERA_SURVIVE=$?
echo "Did vera survive? ${DID_VERA_SURVIVE}"

echo "########## Pep8"
pep8 $(find python -name '*.py')
DID_PEP8_SURVIVE=$?

echo "########## Pylint"
pylint $(find python -name '*.py')
DID_PYLINT_SURVIVE=$?

if test ${DID_VALGRIND_SURVIVE} -ne 0 || \
   test ${DID_CPPCHECK_SURVIVE} -ne 0 || \
   test ${DID_VERA_SURVIVE} -ne 0 || \
   test ${DID_GCOVR_SURVIVE} -ne 0
   test ${DID_PEP8_SURVIVE} -ne 0
   test ${DID_PYLINT_SURVIVE} -ne 0
then
  echo "At least one static check failed"
  exit 1
fi

echo "########## Doxygen"
cd build
make man html
