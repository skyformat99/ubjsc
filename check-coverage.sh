#!/bin/bash
set -x

test -d build && rm -r build
lcov --directory . --zerocounters

mkdir build
cd build || exit 1
cmake -DWITH_TESTING=ON -DCMAKE_BUILD_TYPE=Debug .. || exit 1
make || exit 1

ctest &> /dev/null
cd .. || exit 1

lcov --rc lcov_branch_coverage=1 --directory . --capture --output-file coverage.info || exit 1
lcov --rc lcov_branch_coverage=1 --remove coverage.info -o coverage2.info \
    '*/test/*' '*/test-frmwrk/*' '*/test-frmwrk-glue/*' '/usr/*' || exit 1

lcov --rc lcov_branch_coverage=1 --summary coverage2.info || exit 1
LINE_RATE=$(lcov --rc lcov_branch_coverage=1 --summary coverage2.info 2>&1|grep '^  lines'|sed 's/.*: //;s/%.*//')
FUNCTIONS_RATE=$(lcov --rc lcov_branch_coverage=1 --summary coverage2.info 2>&1|grep '^  functions'|sed 's/.*: //;s/%.*//')
BRANCH_RATE=$(lcov --rc lcov_branch_coverage=1 --summary coverage2.info 2>&1|grep '^  branches'|sed 's/.*: //;s/%.*//')

genhtml --branch-coverage -o build/coverage coverage2.info || exit 1

if test "${COVERALLS_TOKEN}" != ""
then
    coveralls-lcov --repo-token "${COVERALLS_TOKEN}" coverage2.info || exit 1
fi

mv coverage2.info build/coverage.info
rm coverage.info

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

