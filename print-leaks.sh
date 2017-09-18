#!/bin/bash
set -x

test -d build || exit 1
cd build
find . -maxdepth 1 -type f -name 'memcheck.*.txt' \
    -exec bash -c "grep 'ERROR SUMMARY: 0 errors from 0 contexts' \$1 >/dev/null || (echo \$1;cat \$1;echo)" \
    _ {} \;
