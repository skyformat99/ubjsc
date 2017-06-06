#!/bin/bash
HERE=$(dirname "$0")

for TOOL in js2ubj ubj2js ubjq
do
    ./"${TOOL}" -h &> "${HERE}/${TOOL}"-h.txt
    ./"${TOOL}" --rower &> "${HERE}/${TOOL}"-error.txt

    cat << EOF > "${HERE}/test-${TOOL}-help.sh"
#!/bin/bash

HERE=\$(dirname "\$0")
FAIL=0

echo -n "usage: ${TOOL} ..."
./"${TOOL}" -h &> tested.txt
diff "\${HERE}/${TOOL}"-h.txt tested.txt
if test \$? -eq 0
then
    echo "[OK]"
else
    echo "[FAIL]"
    FAIL=1
fi
rm tested.txt

echo -n "usage: ${TOOL} --rower ..."
./"${TOOL}" --rower &> tested.txt
diff "\${HERE}/${TOOL}"-error.txt tested.txt
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

    chmod +x "${HERE}/test-${TOOL}-help.sh"
done

echo -n "[" | ./js2ubj &> "${HERE}/js2ubj-json-error.txt"
cat << EOF > "${HERE}/test-js2ubj-json-error.sh"
#!/bin/bash
HERE=\$(dirname "\$0")
FAIL=0

echo -n "usage: js2ubj json error ..."
echo -n "[" | ./js2ubj &> tested.txt
diff "\${HERE}/js2ubj-json-error.txt" tested.txt
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
chmod +x "${HERE}/test-js2ubj-json-error.sh"

for TOOL in ubj2js ubjq
do
    echo -n "SZ" | ./"${TOOL}" &> "${HERE}/${TOOL}-ubjson-error.txt"
    cat << EOF > "${HERE}/test-${TOOL}-ubjson-error.sh"
#!/bin/bash

HERE=\$(dirname "\$0")
FAIL=0

echo -n "usage: ${TOOL} ubjson error ..."
echo -n "SZ" | ./"${TOOL}" &> tested.txt
diff "\${HERE}/${TOOL}-ubjson-error.txt" tested.txt
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

    chmod +x "${HERE}/test-${TOOL}-ubjson-error.sh"
done
