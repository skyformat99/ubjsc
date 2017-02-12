#!/bin/bash
set -x
HERE=$(dirname "$0")

for AFILE in "${HERE}/"*.ubjson
do
    AFILEBASE=$(basename "${AFILE}" .ubjson)

    cat << EOF > "${HERE}/test-${AFILEBASE}.sh"
#!/bin/bash
set -x

HERE=\$(dirname "\$0")
FAIL=0

echo "Sorry, this UBJSON primitive has insides I cannot convert into JSON." > source.txt
./ubj2js < "\${HERE}/${AFILEBASE}.ubjson" &> tested.txt
diff source.txt tested.txt
test \$? -eq 0 || FAIL=1
rm tested.txt source.txt

exit "\${FAIL}"

EOF

    chmod +x "${HERE}/test-${AFILEBASE}.sh"
done
