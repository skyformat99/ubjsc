#!/bin/bash
HERE=$(dirname "$0")

for AFILE in "${HERE}/"*.ubjson
do
    AFILEBASE=$(basename "${AFILE}" .ubjson)

    cat << EOF > "${HERE}/test-${AFILEBASE}.sh"
#!/bin/bash
HERE=\$(dirname "\$0")
FAIL=0

echo -n "cannot convert to json: ${AFILEBASE} ... "
echo "Sorry, this UBJSON primitive has insides I cannot convert into JSON." > source.txt
./ubj2js < "\${HERE}/${AFILEBASE}.ubjson" &> tested.txt
diff source.txt tested.txt
if test \$? -eq 0
then
    echo "[OK]"
else
    echo "[FAIL]"
    FAIL=1
fi
rm tested.txt source.txt

exit "\${FAIL}"

EOF

    chmod +x "${HERE}/test-${AFILEBASE}.sh"
done
