#!/bin/bash
test -d dist && rm -rf dist
mkdir dist

cd build
make package_source
mv *zip *tar.bz2 *deb ../dist

