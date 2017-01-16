#!/bin/bash
set -x

mkdir -p dist/leaks
test -d build && rm -r build
mkdir build

cd build || exit 1
cmake -DCMAKE_BUILD_TYPE=Debug .. &>/dev/null || exit 1
make test-ubjsc test-ubjsc-glues test-ubjsc-glue-dict-ptrie ubjspy &>/dev/null || exit 1

# Yeah, we really use this much memory.
FAILED=0
valgrind --error-exitcode=1 --leak-check=full --show-leak-kinds=all --show-reachable=yes \
    --suppressions=../valgrind.supp --gen-suppressions=all \
    ./test-ubjsc 2>&1| tee ../dist/leaks/test-ubjsc.txt
test "${PIPESTATUS[0]}" -eq 0 || FAILED=1

valgrind --error-exitcode=1 --leak-check=full --show-leak-kinds=all --show-reachable=yes \
    --suppressions=../valgrind.supp --gen-suppressions=all \
    ./test-ubjsc-glues 2>&1 | tee ../dist/leaks/test-ubjsc-glues.txt
test "${PIPESTATUS[0]}" -eq 0 || FAILED=1

valgrind --error-exitcode=1 --leak-check=full --show-leak-kinds=all --show-reachable=yes \
    --suppressions=../valgrind.supp --gen-suppressions=all \
    ./test-ubjsc-glue-dict-ptrie 2>&1 | tee ../dist/leaks/test-ubjsc-glue-dict-ptrie.txt
test "${PIPESTATUS[0]}" -eq 0 || FAILED=1

cd .. || exit 1
./upload-artifacts.sh leaks

# @todo this involves custom-built python
#(
#  cd python
#  valgrind --error-exitcode=1 --suppressions=/usr/lib/valgrind/python3.supp \
#    --leak-check=full \
#    python3 -X showrefcount ../../python/setup.py test > /dev/null \
#) \
#|| FAILED=1

exit $FAILED
