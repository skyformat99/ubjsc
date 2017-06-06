#!/bin/bash
HERE=$(dirname "$0")
FAIL=0

echo -n "cannot convert to json: ../tools/test/cannot-convert-to-json/object-noop.ubjson ... "
echo "Sorry, this UBJSON primitive has insides I cannot convert into JSON." > source.txt
./ubj2js < "${HERE}/object-noop.ubjson" &> tested.txt
diff source.txt tested.txt
if test $? -eq 0
then
    echo "[OK]"
else
    echo "[FAIL]"
    FAIL=1
fi
rm tested.txt source.txt

exit "${FAIL}"

