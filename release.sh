#!/bin/bash
test -d dist && rm -rf dist
mkdir dist

cd build
make CPACK_SOURCE_GENERATOR="TBZ2;ZIP;DEB" package_source
mv *zip *tar.bz2 *deb ../dist
