#!/bin/bash
set -x

mkdir -p dist/static

FAILED=0
HEADERS_C=$(find ubjsc ubjsc-glue-dict-ptrie -name '*.h')
SOURCES_C=$(find ubjsc ubjsc-glue-dict-ptrie -name '*.c')
SOURCES_NOTEST_C=$(find ubjsc/src ubjsc-glue-dict-ptrie/src -name '*.c')
SOURCES_PY=$(find ubjspy tools/artifact-server -name '*.py')
SOURCES_SH=$(find . tools/artifact-server -maxdepth 1 -name '*.sh')

# shellcheck disable=SC2086
cppcheck --error-exitcode=1 --enable=all --language=c \
    --suppress=missingIncludeSystem ${SOURCES_C} | tee dist/static/cppcheck.txt
test "${PIPESTATUS[0]}" -eq 0 || FAILED=1

# shellcheck disable=SC2086
vera++ -e \
    ${HEADERS_C} ${SOURCES_C} | tee dist/static/vera.txt
test "${PIPESTATUS[0]}" -eq 0 || FAILED=1

# shellcheck disable=SC2086
pep8 --max-line-length=100 \
    ${SOURCES_PY} | tee dist/static/pep8.txt
test "${PIPESTATUS[0]}" -eq 0 || FAILED=1

# shellcheck disable=SC2086
complexity --score --threshold=13 \
    ${SOURCES_NOTEST_C} | tee dist/static/complexity.txt
test "${PIPESTATUS[0]}" -ne 0 || FAILED=1

# shellcheck disable=SC2086
pylint ${SOURCES_PY} | tee dist/static/pylint.txt
test "${PIPESTATUS[0]}" -eq 0 || FAILED=1

# shellcheck disable=SC2086
shellcheck ${SOURCES_SH} | tee dist/static/shellcheck.txt
test "${PIPESTATUS[0]}" -eq 0 || FAILED=1

(
    test -d build && rm -r build
    mkdir build
    cd build || exit 1
    cmake .. || exit 1
    make man html
) | tee dist/static/man.html.txt
test "${PIPESTATUS[0]}" -eq 0 || FAILED=1

./upload-artifacts.sh

exit $FAILED
