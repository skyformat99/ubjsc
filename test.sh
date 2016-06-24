#!/bin/bash
echo "***** TEST *****"

test -d build || exit 1
cd build

ctest -VV . &> logs/test-ctest.txt || exit 1
xsltproc -o results.xml ../tools/cunit-to-junit.xsl test/CUnitAutomated-Results.xml || exit 1

echo "OK!"
cd ..

