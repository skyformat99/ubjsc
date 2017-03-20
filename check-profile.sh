#!/bin/bash
set -x

test -d build && rm -r build
mkdir build
cd build || exit 1
cmake -DCMAKE_BUILD_TYPE=Debug -DWITH_TESTING=ON .. &>/dev/null || exit 1
make test-ubjsc test-ubjsc-glue-dict-ptrie &>/dev/null || exit 1

valgrind --tool=callgrind --callgrind-out-file=callgrind-%p.ubjsc.out --trace-children=yes \
    ./test-ubjsc -j0 > /dev/null
for afile in callgrind-*.ubjsc.out
do
    callgrind_annotate "${afile}"
done

valgrind --tool=callgrind --callgrind-out-file=callgrind-%p.ubjsc-glue-dict-ptrie.out --trace-children=yes \
    ./test-ubjsc-glue-dict-ptrie -j0 > /dev/null
for afile in callgrind-*.ubjsc-glue-dict-ptrie.out
do
    callgrind_annotate "${afile}"
done
