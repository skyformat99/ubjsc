#!/bin/bash
set -x

test -d build && rm -r build
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug .. &>/dev/null || exit 1
cmake --build . &>/dev/null || exit 1

./unittests-c > /dev/null

cd python
python3 ../../python/setup.py test ../../python > /dev/null
cd ..
cd ..

gcovr -p -r . -e 'test' -e 'ptrie'
gcovr -p -r . -e 'test' -e 'ptrie' -x > coverage.xml
BRANCH_RATE=$(xmlstarlet sel -t -v 'coverage/@branch-rate' \
    coverage.xml 2> /dev/null)
LINE_RATE=$(xmlstarlet sel -t -v 'coverage/@line-rate' \
    coverage.xml 2> /dev/null)
rm coverage.xml

echo "Branch coverage rate: ${BRANCH_RATE}"
echo "Line coverage rate: ${LINE_RATE}"

DID_GCOVR_SURVIVE=0
if test $(echo "${BRANCH_RATE} >= 0.9"|bc) -eq 0
then
    exit 1
fi

if test $(echo "${LINE_RATE} >= 0.95"|bc) -eq 0
then
    exit 1
fi
