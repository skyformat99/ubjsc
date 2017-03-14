#!/bin/bash
set -x

HERE=$(dirname "$0")
FAIL=0

./"js2ubj" -h &> tested.txt
diff "${HERE}/js2ubj"-h.txt tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./"js2ubj" --rower &> tested.txt
diff "${HERE}/js2ubj"-error.txt tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

exit "${FAIL}"

