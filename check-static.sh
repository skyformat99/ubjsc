#!/bin/bash
set -x

FAILED=0
HEADERS_C=$(find ubjsc ubjsc-glue-dict-ptrie -name '*.h')
SOURCES_C=$(find ubjsc ubjsc-glue-dict-ptrie -name '*.c')
SOURCES_NOTEST_C=$(find ubjsc/src ubjsc-glue-dict-ptrie/src -name '*.c')
SOURCES_PY=$(find ubjspy -name '*.py')

# shellcheck disable=SC2086
cppcheck --error-exitcode=1 --enable=all --language=c \
    --suppress=missingIncludeSystem ${SOURCES_C} \
|| FAILED=1

# shellcheck disable=SC2086
vera++ -e \
    ${HEADERS_C} ${SOURCES_C} \
|| FAILED=1

# shellcheck disable=SC2086
pep8 --max-line-length=100 \
    ${SOURCES_PY} \
|| FAILED=1

# shellcheck disable=SC2086
complexity --score --threshold=13 \
    ${SOURCES_NOTEST_C} \
&& FAILED=1

# shellcheck disable=SC2086
pylint \
    ${SOURCES_PY} \
|| FAILED=1

# shellcheck disable=SC2086
shellcheck ./*.sh \
|| FAILED=1

(
    test -d build && rm -r build
    mkdir build
    cd build
    cmake .. &> /dev/null
    make man html
) || FAILED=1

# shellcheck disable=SC2086

cat << EOF > markdown.config
[general]
ignore=R1
EOF

for AFILE in *.md
do
    python2 "$(which markdownlint)" --config markdown.config "${AFILE}" || FAILED=1
done
rm markdown.config

exit $FAILED
