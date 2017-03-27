#!/bin/bash
set -x

test -d build && rm -r build
mkdir build
cd build || exit 1
cmake -DCMAKE_BUILD_TYPE=Debug -DWITH_TESTING=ON .. &>/dev/null || exit 1
make test-api-ubjsc &>/dev/null || exit 1

valgrind --tool=callgrind --callgrind-out-file=callgrind-%p.out --trace-children=yes \
    ./test-api-ubjsc --verbose > /dev/null
valgrind --tool=callgrind --callgrind-out-file=callgrind-%p.out --trace-children=yes \
    ./test-api-ubjsc-glue --verbose > /dev/null
valgrind --tool=callgrind --callgrind-out-file=callgrind-%p.out --trace-children=yes \
    ./test-api-ubjsc-glue-dict-ptrie --verbose > /dev/null
for afile in callgrind-*.ubjsc.out
do
    callgrind_annotate "${afile}"
done
