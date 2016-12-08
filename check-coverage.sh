#!/bin/bash
set -x

test -d build && rm -r build
mkdir build
cd build || exit 1
cmake -DCMAKE_BUILD_TYPE=Debug .. &>/dev/null || exit 1
cmake --build . &>/dev/null || exit 1

./test-ubjsc > /dev/null

cd ubjspy || exit 1
python3 ../../ubjspy/setup.py test ../../ubjspy > /dev/null
cd ../.. || exit 1

gcovr -p -r . -e 'ubjsc/test' -e 'tools'
gcovr -p -r . -e 'ubjsc/test' -e 'tools' -x > coverage.xml
BRANCH_RATE=$(xmlstarlet sel -t -v 'coverage/@branch-rate' \
    coverage.xml 2> /dev/null)
LINE_RATE=$(xmlstarlet sel -t -v 'coverage/@line-rate' \
    coverage.xml 2> /dev/null)
rm coverage.xml

echo "Branch coverage rate: ${BRANCH_RATE}"
echo "Line coverage rate: ${LINE_RATE}"

# Temporary
exit

if test "$(echo "${BRANCH_RATE} >= 0.9"|bc)" -eq 0
then
    exit 1
fi

if test "$(echo "${LINE_RATE} >= 0.95"|bc)" -eq 0
then
    exit 1
fi
