#!/bin/bash

HERE=$(dirname "$0")
FAIL=0

echo "parses: array-populated"
echo -n "    js2ubj ... "
./js2ubj < "${HERE}/array-populated.js"> tested.txt
diff "${HERE}/array-populated.ubjson" tested.txt
if test $? -eq 0
then
    echo "[OK]"
else
    echo "[FAIL]"
    FAIL=1
fi

rm tested.txt
echo -n "    js2ubj -v ... "
./js2ubj -v < "${HERE}/array-populated.js"> tested.txt
diff "${HERE}/array-populated.v.ubjson" tested.txt
if test $? -eq 0
then
    echo "[OK]"
else
    echo "[FAIL]"
    FAIL=1
fi
rm tested.txt

echo -n "    js2ubj -v --pretty-print-output ... "
./js2ubj -v --pretty-print-output < "${HERE}/array-populated.js"> tested.txt
diff "${HERE}/array-populated.vpp.ubjson" tested.txt
if test $? -eq 0
then
    echo "[OK]"
else
    echo "[FAIL]"
    FAIL=1
fi
rm tested.txt

echo -n "    ubj2js ... "
./ubj2js < "${HERE}/array-populated.ubjson" > tested.txt
diff "${HERE}/array-populated.ubjson2js" tested.txt
if test $? -eq 0
then
    echo "[OK]"
else
    echo "[FAIL]"
    FAIL=1
fi
rm tested.txt

echo -n "    ubj2js -v ... "
./ubj2js -v < "${HERE}/array-populated.ubjson" > tested.txt
diff "${HERE}/array-populated.v.ubjson2js" tested.txt
if test $? -eq 0
then
    echo "[OK]"
else
    echo "[FAIL]"
    FAIL=1
fi
rm tested.txt

echo -n "    ubj2js -v --pretty-print-input ... "
./ubj2js -v --pretty-print-input < "${HERE}/array-populated.ubjson" > tested.txt
diff "${HERE}/array-populated.vpp.ubjson2js" tested.txt
if test $? -eq 0
then
    echo "[OK]"
else
    echo "[FAIL]"
    FAIL=1
fi
rm tested.txt

echo -n "    ubjq ... "
./ubjq < "${HERE}/array-populated.ubjson" > tested.txt
diff "${HERE}/array-populated.ubjq" tested.txt
if test $? -eq 0
then
    echo "[OK]"
else
    echo "[FAIL]"
    FAIL=1
fi
rm tested.txt

exit "${FAIL}"

