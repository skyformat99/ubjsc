#!/bin/bash
set -x

lcov --directory . --zerocounters

mkdir -p dist/coverage
test -d build && rm -r build
mkdir build

cd build || exit 1
cmake -DCMAKE_BUILD_TYPE=Debug .. &>/dev/null || exit 1
make test-ubjsc test-ubjsc-glues test-ubjsc-glue-dict-ptrie ubjspy &> /dev/null || exit 1

./test-ubjsc &> /dev/null
./test-ubjsc-glues &> /dev/null
./test-ubjsc-glue-dict-ptrie &> /dev/null

cd ubjspy || exit 1
python3 ../../ubjspy/setup.py test ../../ubjspy > /dev/null
cd ../.. || exit 1

lcov --rc lcov_branch_coverage=1 --directory . --capture --output-file coverage.info || exit 1
lcov --rc lcov_branch_coverage=1 --remove coverage.info -o coverage2.info '*/test/*' '*/test-frmwrk/*' || exit 1

lcov --rc lcov_branch_coverage=1 --summary coverage2.info || exit 1
LINE_RATE=$(lcov --rc lcov_branch_coverage=1 --summary coverage2.info 2>&1|grep '^  lines'|sed 's/.*: //;s/%.*//')
FUNCTIONS_RATE=$(lcov --rc lcov_branch_coverage=1 --summary coverage2.info 2>&1|grep '^  functions'|sed 's/.*: //;s/%.*//')
BRANCH_RATE=$(lcov --rc lcov_branch_coverage=1 --summary coverage2.info 2>&1|grep '^  branches'|sed 's/.*: //;s/%.*//')

genhtml --branch-coverage -o dist/coverage coverage2.info || exit 1
rm coverage.info coverage2.info
./upload-artifacts.sh

if test "$(echo "${FUNCTIONS_RATE} >= 95"|bc)" -eq 0
then
    exit 1
fi

if test "$(echo "${LINE_RATE} >= 95"|bc)" -eq 0
then
    exit 1
fi

if test "$(echo "${BRANCH_RATE} >= 90"|bc)" -eq 0
then
    exit 1
fi

