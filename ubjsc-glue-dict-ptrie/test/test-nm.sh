#!/bin/bash
set -x

HERE=$(dirname "$0")
FAIL=0

nm -g "./libubjsc-glue-dict-ptrie.so" | grep 'T ubjs' | sed 's/^[0-9a-f]* T //' &> tested.txt
diff "${HERE}/lib-nm.txt" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

exit "${FAIL}"

