#!/bin/bash
test -d build && rm -rf build
test -d dist && rm -rf dist
mkdir build
mkdir dist

cd build
cmake -DCPACK_SOURCE_GENERATOR="TBZ2;ZIP;DEB" ..
make package_source man html
mv *.zip *.tar.bz2 *.deb ../dist
