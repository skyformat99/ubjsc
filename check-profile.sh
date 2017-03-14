#!/bin/bash
set -x

test -d build && rm -r build
mkdir build
cd build || exit 1
cmake -DCMAKE_BUILD_TYPE=Debug .. &>/dev/null || exit 1
make test-ubjsc test-ubjsc-glues test-ubjsc-glue-dict-ptrie &>/dev/null || exit 1

valgrind --tool=callgrind --callgrind-out-file=callgrind.ubjsc.%p.out --trace-children=yes \
    ./test-ubjsc > /dev/null
callgrind_annotate callgrind.ubjsc.*.out

valgrind --tool=callgrind --callgrind-out-file=callgrind.ubjsc-glues.%p.out --trace-children=yes \
    ./test-ubjsc-glues > /dev/null
callgrind_annotate callgrind.ubjsc-glues.*.out

valgrind --tool=callgrind --callgrind-out-file=callgrind.ubjsc-glue-dict-ptrie.%p.out --trace-children=yes \
    ./test-ubjsc-glue-dict-ptrie > /dev/null
callgrind_annotate callgrind.ubjsc-glue-dict-ptrie.*.out
