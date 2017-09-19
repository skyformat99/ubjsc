#!/bin/bash
HEADERS_C=$(find . -name '*.h')
SOURCES_C=$(find .  -name '*.c')

# shellcheck disable=SC2086
vera++ -eSs \
    ${HEADERS_C} ${SOURCES_C}
