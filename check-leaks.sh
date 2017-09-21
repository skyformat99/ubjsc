#!/bin/bash
set -x

test -d build && rm -r build
mkdir build
cd build || exit 1

cmake -DWITH_TESTING=ON -DCMAKE_BUILD_TYPE=Debug -DWITH_VALGRIND=ON .. || exit 1
make || exit 1

ctest .

NUM_OF_FILES=$(find . -maxdepth 1 -type f -name 'memcheck.*.txt' | wc -l)
NUM_OF_PASSED=$(find . -maxdepth 1 -type f -name 'memcheck.*.txt' \
    -exec bash -c "grep 'ERROR SUMMARY: 0 errors from 0 contexts' >/dev/null \$1 && echo \$1" _ {} \;| wc -l)

if test "${NUM_OF_PASSED}" -ne "${NUM_OF_FILES}"
then
    find . -maxdepth 1 -type f -name 'memcheck.*.txt' \
        -exec bash -c "grep 'ERROR SUMMARY: 0 errors from 0 contexts' \$1 >/dev/null || (echo \$1;cat \$1;echo)" \
        _ {} \;
    exit 1
fi
