#!/bin/bash

HERE=$(dirname "$0")
FAIL=0

echo "parses: null"
echo -n "    js2ubj ... "
./js2ubj < "${HERE}/null.js"> tested.txt
diff "${HERE}/null.ubjson" tested.txt
if test $? -eq 0
then
    echo "[OK]"
else
    echo "[FAIL]"
    FAIL=1
fi

rm tested.txt
echo -n "    js2ubj -v ... "
./js2ubj -v < "${HERE}/null.js"> tested.txt
diff "${HERE}/null.v.ubjson" tested.txt
if test $? -eq 0
then
    echo "[OK]"
else
    echo "[FAIL]"
    FAIL=1
fi
rm tested.txt

echo -n "    js2ubj -v --pretty-print-output ... "
./js2ubj -v --pretty-print-output < "${HERE}/null.js"> tested.txt
diff "${HERE}/null.vpp.ubjson" tested.txt
if test $? -eq 0
then
    echo "[OK]"
else
    echo "[FAIL]"
    FAIL=1
fi
rm tested.txt

echo -n "    ubj2js ... "
./ubj2js < "${HERE}/null.ubjson" > tested.txt
diff "${HERE}/null.ubjson2js" tested.txt
if test $? -eq 0
then
    echo "[OK]"
else
    echo "[FAIL]"
    FAIL=1
fi
rm tested.txt

echo -n "    ubj2js -v ... "
./ubj2js -v < "${HERE}/null.ubjson" > tested.txt
diff "${HERE}/null.v.ubjson2js" tested.txt
if test $? -eq 0
then
    echo "[OK]"
else
    echo "[FAIL]"
    FAIL=1
fi
rm tested.txt

echo -n "    ubj2js -v --pretty-print-input ... "
./ubj2js -v --pretty-print-input < "${HERE}/null.ubjson" > tested.txt
diff "${HERE}/null.vpp.ubjson2js" tested.txt
if test $? -eq 0
then
    echo "[OK]"
else
    echo "[FAIL]"
    FAIL=1
fi
rm tested.txt

echo -n "    ubjq ... "
./ubjq < "${HERE}/null.ubjson" > tested.txt
diff "${HERE}/null.ubjq" tested.txt
if test $? -eq 0
then
    echo "[OK]"
else
    echo "[FAIL]"
    FAIL=1
fi
rm tested.txt

exit "${FAIL}"

