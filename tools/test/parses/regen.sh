#!/bin/bash
HERE=$(dirname "$0")

for AFILE in "${HERE}/"*.js
do
    AFILEBASE=$(basename "${AFILE}" .js)
    ./js2ubj < "${AFILE}" > "${HERE}/${AFILEBASE}.ubjson"
    ./js2ubj -v < "${AFILE}" > "${HERE}/${AFILEBASE}.v.ubjson"
    ./js2ubj -v --pretty-print-output < "${AFILE}" > "${HERE}/${AFILEBASE}.vpp.ubjson"

    ./ubj2js < "${HERE}/${AFILEBASE}.ubjson" > "${HERE}/${AFILEBASE}.ubjson2js"
    ./ubj2js -v < "${HERE}/${AFILEBASE}.ubjson" > "${HERE}/${AFILEBASE}.v.ubjson2js"
    ./ubj2js -v --pretty-print-input < "${HERE}/${AFILEBASE}.ubjson" > "${HERE}/${AFILEBASE}.vpp.ubjson2js"

    ./ubjq < "${HERE}/${AFILEBASE}.ubjson" > "${HERE}/${AFILEBASE}.ubjq"

    cat << EOF > "${HERE}/test-${AFILEBASE}.sh"
#!/bin/bash

HERE=\$(dirname "\$0")
FAIL=0

echo "parses: ${AFILEBASE}"
echo -n "    js2ubj ... "
./js2ubj < "\${HERE}/${AFILEBASE}.js"> tested.txt
diff "\${HERE}/${AFILEBASE}.ubjson" tested.txt
if test \$? -eq 0
then
    echo "[OK]"
else
    echo "[FAIL]"
    FAIL=1
fi

rm tested.txt
echo -n "    js2ubj -v ... "
./js2ubj -v < "\${HERE}/${AFILEBASE}.js"> tested.txt
diff "\${HERE}/${AFILEBASE}.v.ubjson" tested.txt
if test \$? -eq 0
then
    echo "[OK]"
else
    echo "[FAIL]"
    FAIL=1
fi
rm tested.txt

echo -n "    js2ubj -v --pretty-print-output ... "
./js2ubj -v --pretty-print-output < "\${HERE}/${AFILEBASE}.js"> tested.txt
diff "\${HERE}/${AFILEBASE}.vpp.ubjson" tested.txt
if test \$? -eq 0
then
    echo "[OK]"
else
    echo "[FAIL]"
    FAIL=1
fi
rm tested.txt

echo -n "    ubj2js ... "
./ubj2js < "\${HERE}/${AFILEBASE}.ubjson" > tested.txt
diff "\${HERE}/${AFILEBASE}.ubjson2js" tested.txt
if test \$? -eq 0
then
    echo "[OK]"
else
    echo "[FAIL]"
    FAIL=1
fi
rm tested.txt

echo -n "    ubj2js -v ... "
./ubj2js -v < "\${HERE}/${AFILEBASE}.ubjson" > tested.txt
diff "\${HERE}/${AFILEBASE}.v.ubjson2js" tested.txt
if test \$? -eq 0
then
    echo "[OK]"
else
    echo "[FAIL]"
    FAIL=1
fi
rm tested.txt

echo -n "    ubj2js -v --pretty-print-input ... "
./ubj2js -v --pretty-print-input < "\${HERE}/${AFILEBASE}.ubjson" > tested.txt
diff "\${HERE}/${AFILEBASE}.vpp.ubjson2js" tested.txt
if test \$? -eq 0
then
    echo "[OK]"
else
    echo "[FAIL]"
    FAIL=1
fi
rm tested.txt

echo -n "    ubjq ... "
./ubjq < "\${HERE}/${AFILEBASE}.ubjson" > tested.txt
diff "\${HERE}/${AFILEBASE}.ubjq" tested.txt
if test \$? -eq 0
then
    echo "[OK]"
else
    echo "[FAIL]"
    FAIL=1
fi
rm tested.txt

exit "\${FAIL}"

EOF

    chmod +x "${HERE}/test-${AFILEBASE}.sh"
done
