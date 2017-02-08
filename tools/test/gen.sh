#!/bin/bash
set -x
HERE=$(dirname $0)

for AFILE in "${HERE}/"*.js
do
    AFILEBASE=$(basename "${AFILE}" .js)
    cat "${AFILE}" | ./js2ubj > "${HERE}/${AFILEBASE}.ubjson"
    cat "${AFILE}" | ./js2ubj -v > "${HERE}/${AFILEBASE}.v.ubjson"
    cat "${AFILE}" | ./js2ubj -v --pretty-print-output > "${HERE}/${AFILEBASE}.vpp.ubjson"

    cat "${HERE}/${AFILEBASE}.ubjson" | ./ubj2js > "${HERE}/${AFILEBASE}.ubjson2js"
    cat "${HERE}/${AFILEBASE}.ubjson" | ./ubj2js -v > "${HERE}/${AFILEBASE}.v.ubjson2js"
    cat "${HERE}/${AFILEBASE}.ubjson" | ./ubj2js -v --pretty-print-input > "${HERE}/${AFILEBASE}.vpp.ubjson2js"

    cat << EOF > "${HERE}/test-${AFILEBASE}.sh"
#!/bin/bash
set -x

HERE="\$(dirname \$0)"
FAIL=0

cat "\${HERE}/${AFILEBASE}.js"

cat "\${HERE}/${AFILEBASE}.js" | ./js2ubj > tested.txt
cat tested.txt
diff "\${HERE}/${AFILEBASE}.ubjson" tested.txt
test \$? -eq 0 || FAIL=1
rm tested.txt

cat "\${HERE}/${AFILEBASE}.js" | ./js2ubj -v > tested.txt
cat tested.txt
diff "\${HERE}/${AFILEBASE}.v.ubjson" tested.txt
test \$? -eq 0 || FAIL=1
rm tested.txt

cat "\${HERE}/${AFILEBASE}.js" | ./js2ubj -v --pretty-print-output > tested.txt
cat tested.txt
diff "\${HERE}/${AFILEBASE}.vpp.ubjson" tested.txt
test \$? -eq 0 || FAIL=1
rm tested.txt

cat "\${HERE}/${AFILEBASE}.ubjson" | ./ubj2js > tested.txt
cat tested.txt
diff "\${HERE}/${AFILEBASE}.ubjson2js" tested.txt
test \$? -eq 0 || FAIL=1
rm tested.txt

cat "\${HERE}/${AFILEBASE}.ubjson" | ./ubj2js -v > tested.txt
cat tested.txt
diff "\${HERE}/${AFILEBASE}.v.ubjson2js" tested.txt
test \$? -eq 0 || FAIL=1
rm tested.txt

cat "\${HERE}/${AFILEBASE}.ubjson" | ./ubj2js -v --pretty-print-input > tested.txt
cat tested.txt
diff "\${HERE}/${AFILEBASE}.vpp.ubjson2js" tested.txt
test \$? -eq 0 || FAIL=1
rm tested.txt

exit "\${FAIL}"

EOF

    chmod +x "${HERE}/test-${AFILEBASE}.sh"
done
