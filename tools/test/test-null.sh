#!/bin/bash
set -x

HERE="$(dirname $0)"
FAIL=0

cat "${HERE}/null.js"

cat "${HERE}/null.js" | ./js2ubj > tested.txt
cat tested.txt
diff "${HERE}/null.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

cat "${HERE}/null.js" | ./js2ubj -v > tested.txt
cat tested.txt
diff "${HERE}/null.v.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

cat "${HERE}/null.js" | ./js2ubj -v --pretty-print-output > tested.txt
cat tested.txt
diff "${HERE}/null.vpp.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

cat "${HERE}/null.ubjson" | ./ubj2js > tested.txt
cat tested.txt
diff "${HERE}/null.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

cat "${HERE}/null.ubjson" | ./ubj2js -v > tested.txt
cat tested.txt
diff "${HERE}/null.v.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

cat "${HERE}/null.ubjson" | ./ubj2js -v --pretty-print-input > tested.txt
cat tested.txt
diff "${HERE}/null.vpp.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

exit "${FAIL}"

