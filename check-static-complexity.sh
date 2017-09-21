#!/bin/bash

test -d build && rm -r build
SOURCES_NOTEST_C=$(find tools ubjsc/src ubjsc-glue-dict-ptrie/src -name '*.c')

# shellcheck disable=SC2086
complexity --scores --histogram --threshold=10 \
    ${SOURCES_NOTEST_C} | tee a.tmp
grep 'No procedures were scored' a.tmp &> /dev/null
EXIT=$?
rm a.tmp
exit ${EXIT}
