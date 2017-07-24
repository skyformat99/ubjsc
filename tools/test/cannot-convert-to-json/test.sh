#!/bin/bash
HERE=$(dirname "$0")
FAIL=0

for AFILE in "${HERE}"/test-*.sh
do
    "${AFILE}" || FAIL=1
done

exit "${FAIL}"

