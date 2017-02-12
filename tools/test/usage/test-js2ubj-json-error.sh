#!/bin/bash
set -x

HERE=$(dirname "$0")
FAIL=0

echo -n "[" | ./js2ubj &> tested.txt
diff "${HERE}/js2ubj-json-error.txt" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

exit "${FAIL}"

