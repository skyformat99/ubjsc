#!/bin/bash
test -d build || ./build.sh || exit 1
test -d dist && rm -rf dist
mkdir dist

cd build
cmake -DCPACK_SOURCE_GENERATOR="TBZ2;ZIP;DEB" ..
make package_source man html
mv *zip *tar.bz2 *deb ../dist
