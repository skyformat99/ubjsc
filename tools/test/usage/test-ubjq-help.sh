#!/bin/bash
set -x

HERE=$(dirname "$0")
FAIL=0

./"ubjq" -h &> tested.txt
diff "${HERE}/ubjq"-h.txt tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./"ubjq" --rower &> tested.txt
diff "${HERE}/ubjq"-error.txt tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

exit "${FAIL}"

