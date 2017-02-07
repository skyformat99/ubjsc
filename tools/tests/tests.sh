#!/bin/bash
set -x

js_ub_js()
{
    AFILE=$1
    INPUT=$(cat "${AFILE}")
    OUTPUT=$(cat "${AFILE}" | ./js2ubj | ./ubj2js)
    test "${INPUT}" == "${OUTPUT}" || exit 1
}

HERE=$(dirname $0)

for afile in ${HERE}/test_*.js
do
    js_ub_js "${afile}"
done
