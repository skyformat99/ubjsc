#!/bin/bash
set -x
HERE=$(dirname "$0")

for AFILE in "${HERE}"/*/regen.sh
do
    "${AFILE}"
done

