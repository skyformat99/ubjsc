#!/bin/bash
set -x

test -d build && rm -r build
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug .. &>/dev/null || exit 1
cmake --build . &>/dev/null || exit 1

# Yeah, we really use this much memory.
FAILED=0
valgrind --error-exitcode=1 \
    ./unittests-c > /dev/null \
|| FAILED=1

# @todo this involves custom-built python
#(
#  cd python
#  valgrind --error-exitcode=1 --suppressions=/usr/lib/valgrind/python3.supp \
#    --leak-check=full \
#    python3 -X showrefcount ../../python/setup.py test > /dev/null \
#) \
#|| FAILED=1

exit $FAILED
