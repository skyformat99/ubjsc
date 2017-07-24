#!/bin/bash

HERE=$(dirname "$0")
FAIL=0

echo "parses: uint8"
echo -n "    js2ubj ... "
./js2ubj < "${HERE}/uint8.js"> tested.txt
diff "${HERE}/uint8.ubjson" tested.txt
if test $? -eq 0
then
    echo "[OK]"
else
    echo "[FAIL]"
    FAIL=1
fi

rm tested.txt
echo -n "    js2ubj -v ... "
./js2ubj -v < "${HERE}/uint8.js"> tested.txt
diff "${HERE}/uint8.v.ubjson" tested.txt
if test $? -eq 0
then
    echo "[OK]"
else
    echo "[FAIL]"
    FAIL=1
fi
rm tested.txt

echo -n "    js2ubj -v --pretty-print-output ... "
./js2ubj -v --pretty-print-output < "${HERE}/uint8.js"> tested.txt
diff "${HERE}/uint8.vpp.ubjson" tested.txt
if test $? -eq 0
then
    echo "[OK]"
else
    echo "[FAIL]"
    FAIL=1
fi
rm tested.txt

echo -n "    ubj2js ... "
./ubj2js < "${HERE}/uint8.ubjson" > tested.txt
diff "${HERE}/uint8.ubjson2js" tested.txt
if test $? -eq 0
then
    echo "[OK]"
else
    echo "[FAIL]"
    FAIL=1
fi
rm tested.txt

echo -n "    ubj2js -v ... "
./ubj2js -v < "${HERE}/uint8.ubjson" > tested.txt
diff "${HERE}/uint8.v.ubjson2js" tested.txt
if test $? -eq 0
then
    echo "[OK]"
else
    echo "[FAIL]"
    FAIL=1
fi
rm tested.txt

echo -n "    ubj2js -v --pretty-print-input ... "
./ubj2js -v --pretty-print-input < "${HERE}/uint8.ubjson" > tested.txt
diff "${HERE}/uint8.vpp.ubjson2js" tested.txt
if test $? -eq 0
then
    echo "[OK]"
else
    echo "[FAIL]"
    FAIL=1
fi
rm tested.txt

echo -n "    ubjq ... "
./ubjq < "${HERE}/uint8.ubjson" > tested.txt
diff "${HERE}/uint8.ubjq" tested.txt
if test $? -eq 0
then
    echo "[OK]"
else
    echo "[FAIL]"
    FAIL=1
fi
rm tested.txt

exit "${FAIL}"

