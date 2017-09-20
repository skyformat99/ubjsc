#!/bin/bash
SOURCES_NOTEST_C=$(find tools ubjsc/src ubjsc-glue-dict-ptrie/src -name '*.c')

# shellcheck disable=SC2086
complexity --scores --histogram --threshold=13 \
    ${SOURCES_NOTEST_C} && exit 1
