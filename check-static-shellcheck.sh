#!/bin/bash

test -d build && rm -r build
SOURCES_SH=$(find . -name '*.sh')

# shellcheck disable=SC2086
shellcheck ${SOURCES_SH}
