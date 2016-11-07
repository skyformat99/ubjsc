#!/bin/bash
set -x

FAILED=0
HEADERS_C=$(find include test src -name '*.h')
SOURCES_C=$(find include test src -name '*.c')
SOURCES_PY=$(find python -name '*.py')

cppcheck --error-exitcode=1 --enable=all --language=c \
    --suppress=missingIncludeSystem ${SOURCES_C} \
|| FAILED=1

vera++ -e \
    ${HEADERS_C} ${SOURCES_C} \
|| FAILED=1

pep8 --max-line-length=100 \
    ${SOURCES_PY} \
|| FAILED=1

pylint \
    ${SOURCES_PY} \
|| FAILED=1

(
    test -d build && rm -r build
    mkdir build
    cd build
    cmake .. &> /dev/null
    make man html
) || FAILED=1

exit $FAILED
