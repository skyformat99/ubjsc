#!/bin/bash

test -d build && rm -r build
SOURCES_C=$(find .  -name '*.c')

# shellcheck disable=SC2086
cppcheck --error-exitcode=1 --enable=all --language=c \
    --suppress=missingIncludeSystem ${SOURCES_C}
