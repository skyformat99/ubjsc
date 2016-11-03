#!/bin/bash
set -x
test -d build && rm -rf build
test -d dist && rm -rf dist
mkdir build
mkdir dist

cd build
cmake -DCPACK_SOURCE_GENERATOR="TBZ2;ZIP;DEB" ..
make ubjspy package_source man html
mv *.whl *.zip *.tar.bz2 *.deb ../dist
