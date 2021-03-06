#!/bin/bash

test -d build && rm -r build
SOURCES_PY=$(find . -name '*.py')

# shellcheck disable=SC2086
pep8 --max-line-length=100 \
    ${SOURCES_PY} || exit 1

# shellcheck disable=SC2086
pylint \
    ${SOURCES_PY} || exit 1
