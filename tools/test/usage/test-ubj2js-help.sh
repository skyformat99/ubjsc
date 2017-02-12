#!/bin/bash
set -x

HERE=$(dirname "$0")
FAIL=0

./"ubj2js" -h &> tested.txt
diff "${HERE}/ubj2js"-h.txt tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./"ubj2js" --rower &> tested.txt
diff "${HERE}/ubj2js"-error.txt tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

exit "${FAIL}"

