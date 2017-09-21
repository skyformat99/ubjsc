#!/bin/bash

test -d build && rm -r build
SOURCES_MD=$(find . -name '*.md')

cat << EOF > markdown.config
[general]
ignore=R1
EOF

# shellcheck disable=SC2086
for AFILE in ${SOURCES_MD}
do
    python2 "$(which markdownlint)" --config markdown.config "${AFILE}" || exit 1
done
rm markdown.config

# shellcheck disable=SC2086
alex ${SOURCES_MD} || exit 1
