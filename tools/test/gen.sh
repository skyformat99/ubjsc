#!/bin/bash
set -x
HERE=$(dirname "$0")

for AFILE in "${HERE}"/*/gen.sh
do
    "${AFILE}"
done

