#!/bin/bash
set -x

test -d build && rm -r build
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug .. &>/dev/null || exit 1
cmake --build . &>/dev/null || exit 1

# Yeah, we really use this much memory.
(
  valgrind --error-exitcode=1 --leak-check=full --show-leak-kinds=all \
   --max-stackframe=2900080 --track-origins=yes ./unittests-c > /dev/null \
#  && \
#  valgrind --error-exitcode=1 --leak-check=full --show-leak-kinds=all \
#      --track-origins=yes python3 ../../python/setup.py test > /dev/null
) || exit 1
