#!/bin/bash

HERE=$(dirname "$0")
FAIL=0

echo "parses: array"
echo -n "    js2ubj ... "
./js2ubj < "${HERE}/array.js"> tested.txt
diff "${HERE}/array.ubjson" tested.txt
if test $? -eq 0
then
    echo "[OK]"
else
    echo "[FAIL]"
    FAIL=1
fi

rm tested.txt
echo -n "    js2ubj -v ... "
./js2ubj -v < "${HERE}/array.js"> tested.txt
diff "${HERE}/array.v.ubjson" tested.txt
if test $? -eq 0
then
    echo "[OK]"
else
    echo "[FAIL]"
    FAIL=1
fi
rm tested.txt

echo -n "    js2ubj -v --pretty-print-output ... "
./js2ubj -v --pretty-print-output < "${HERE}/array.js"> tested.txt
diff "${HERE}/array.vpp.ubjson" tested.txt
if test $? -eq 0
then
    echo "[OK]"
else
    echo "[FAIL]"
    FAIL=1
fi
rm tested.txt

echo -n "    ubj2js ... "
./ubj2js < "${HERE}/array.ubjson" > tested.txt
diff "${HERE}/array.ubjson2js" tested.txt
if test $? -eq 0
then
    echo "[OK]"
else
    echo "[FAIL]"
    FAIL=1
fi
rm tested.txt

echo -n "    ubj2js -v ... "
./ubj2js -v < "${HERE}/array.ubjson" > tested.txt
diff "${HERE}/array.v.ubjson2js" tested.txt
if test $? -eq 0
then
    echo "[OK]"
else
    echo "[FAIL]"
    FAIL=1
fi
rm tested.txt

echo -n "    ubj2js -v --pretty-print-input ... "
./ubj2js -v --pretty-print-input < "${HERE}/array.ubjson" > tested.txt
diff "${HERE}/array.vpp.ubjson2js" tested.txt
if test $? -eq 0
then
    echo "[OK]"
else
    echo "[FAIL]"
    FAIL=1
fi
rm tested.txt

echo -n "    ubjq ... "
./ubjq < "${HERE}/array.ubjson" > tested.txt
diff "${HERE}/array.ubjq" tested.txt
if test $? -eq 0
then
    echo "[OK]"
else
    echo "[FAIL]"
    FAIL=1
fi
rm tested.txt

exit "${FAIL}"

