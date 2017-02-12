#!/bin/bash
set -x

test -d build && rm -rf build
test -d dist && rm -rf dist
mkdir -p dist/static

FAILED=0
HEADERS_C=$(find . -name '*.h')
SOURCES_C=$(find .  -name '*.c')
SOURCES_NOTEST_C=$(find tools ubjsc/src ubjsc-glue-dict-ptrie/src -name '*.c')
SOURCES_PY=$(find . -name '*.py')
SOURCES_SH=$(find . -name '*.sh')
SOURCES_MD=$(find . -name '*.md')

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

cat << EOF > markdown.config
[general]
ignore=R1
EOF

# shellcheck disable=SC2086
for AFILE in ${SOURCES_MD}
do
    python2 "$(which markdownlint)" --config markdown.config "${AFILE}"  | tee -a dist/static/markdownlint.txt
    test "${PIPESTATUS[0]}" -eq 0 || FAILED=1
done
rm markdown.config

# shellcheck disable=SC2086
alex ${SOURCES_MD} | tee dist/static/alex.txt
test "${PIPESTATUS[0]}" -eq 0 || FAILED=1

./upload_artifacts.py

exit $FAILED
