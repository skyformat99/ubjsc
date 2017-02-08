#!/bin/bash
set -x
HERE=$(dirname $0)
FAIL=0

for AFILE in "${HERE}/"*.js
do
    AFILEBASE=$(basename "${AFILE}" .js)
    "${HERE}/test-${AFILEBASE}.sh" || FAIL=1
done

exit "${FAIL}"

