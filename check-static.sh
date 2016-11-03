#!/bin/bash
set -x

FAILED=0

cppcheck --error-exitcode=1 --enable=all --language=c \
    --suppress=missingIncludeSystem \
    $(find include test src -name '*.h') \
    $(find include test src -name '*.c') \
|| FAILED=1

vera++ -e \
    $(find include test src -name '*.h') \
    $(find include test src -name '*.c') \
|| FAILED=1

pep8 --max-line-length=100 \
    $(find python -name '*.py') \
|| FAILED=1

pylint \
    $(find python -name '*.py') \
|| FAILED=1

(
    test -d build && rm -r build
    mkdir build
    cd build
    cmake ..
    make man html
) || FAILED=1
