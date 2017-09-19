#!/bin/bash

HERE=$(dirname "$0")
FAIL=0

echo "parses: object"
echo -n "    js2ubj ... "
./js2ubj < "${HERE}/object.js"> tested.txt
diff "${HERE}/object.ubjson" tested.txt
if test $? -eq 0
then
    echo "[OK]"
else
    echo "[FAIL]"
    FAIL=1
fi

rm tested.txt
echo -n "    js2ubj -v ... "
./js2ubj -v < "${HERE}/object.js"> tested.txt
diff "${HERE}/object.v.ubjson" tested.txt
if test $? -eq 0
then
    echo "[OK]"
else
    echo "[FAIL]"
    FAIL=1
fi
rm tested.txt

echo -n "    js2ubj -v --pretty-print-output ... "
./js2ubj -v --pretty-print-output < "${HERE}/object.js"> tested.txt
diff "${HERE}/object.vpp.ubjson" tested.txt
if test $? -eq 0
then
    echo "[OK]"
else
    echo "[FAIL]"
    FAIL=1
fi
rm tested.txt

echo -n "    ubj2js ... "
./ubj2js < "${HERE}/object.ubjson" > tested.txt
diff "${HERE}/object.ubjson2js" tested.txt
if test $? -eq 0
then
    echo "[OK]"
else
    echo "[FAIL]"
    FAIL=1
fi
rm tested.txt

echo -n "    ubj2js -v ... "
./ubj2js -v < "${HERE}/object.ubjson" > tested.txt
diff "${HERE}/object.v.ubjson2js" tested.txt
if test $? -eq 0
then
    echo "[OK]"
else
    echo "[FAIL]"
    FAIL=1
fi
rm tested.txt

echo -n "    ubj2js -v --pretty-print-input ... "
./ubj2js -v --pretty-print-input < "${HERE}/object.ubjson" > tested.txt
diff "${HERE}/object.vpp.ubjson2js" tested.txt
if test $? -eq 0
then
    echo "[OK]"
else
    echo "[FAIL]"
    FAIL=1
fi
rm tested.txt

echo -n "    ubjq ... "
./ubjq < "${HERE}/object.ubjson" > tested.txt
diff "${HERE}/object.ubjq" tested.txt
if test $? -eq 0
then
    echo "[OK]"
else
    echo "[FAIL]"
    FAIL=1
fi
rm tested.txt

exit "${FAIL}"

