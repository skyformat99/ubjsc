#!/bin/bash
set -x

test -d build && rm -rf build
test -d dist && rm -rf dist

FAILED=0
HEADERS_C=$(find . -name '*.h')
SOURCES_C=$(find .  -name '*.c')
SOURCES_NOTEST_C=$(find tools ubjsc/src ubjsc-glue-dict-ptrie/src -name '*.c')
SOURCES_PY=$(find . -name '*.py')
SOURCES_SH=$(find . -name '*.sh')
SOURCES_MD=$(find . -name '*.md')

# shellcheck disable=SC2086
cppcheck --error-exitcode=1 --enable=all --language=c \
    --suppressions-list=cppcheck.suppressions.txt \
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
complexity --scores --histogram --threshold=13 \
    ${SOURCES_NOTEST_C} \
&& FAILED=1

# shellcheck disable=SC2086
#pylint \
#    ${SOURCES_PY} \
#|| FAILED=1

# shellcheck disable=SC2086
shellcheck ${SOURCES_SH} \
|| FAILED=1

(
    test -d build && rm -r build
    mkdir build
    cd build
    cmake .. &> /dev/null
    make man html
) || FAILED=1

cat << EOF > markdown.config
[general]
ignore=R1
EOF

# shellcheck disable=SC2086
for AFILE in ${SOURCES_MD}
do
    python2 "$(which markdownlint)" --config markdown.config "${AFILE}" || FAILED=1
done
rm markdown.config

# shellcheck disable=SC2086
alex ${SOURCES_MD} || FAILED=1

exit $FAILED
