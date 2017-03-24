#!/bin/bash
set -x

test -d build && rm -r build
mkdir build
cd build || exit 1
cmake -DWITH_TESTING=ON -DCMAKE_BUILD_TYPE=Debug .. || exit 1
make || exit 1

valgrind --log-file=memcheck.%p.ubjsc.txt --leak-check=full --show-leak-kinds=all --show-reachable=yes \
    --trace-children=yes \
    ./test-api-ubjsc --verbose --jobs 32
valgrind --log-file=memcheck.%p.ubjsc.txt --leak-check=full --show-leak-kinds=all --show-reachable=yes \
    --trace-children=yes \
    ./test-api-ubjsc-glue --verbose --jobs 32
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

# @todo this involves custom-built python
#(
#  cd python
#  valgrind --error-exitcode=1 --suppressions=/usr/lib/valgrind/python3.supp \
#    --leak-check=full \
#    python3 -X showrefcount ../../python/setup.py test > /dev/null \
#) \
#|| FAILED=1
