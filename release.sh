#!/bin/bash
set -x

test -d build && rm -rf build
mkdir -p dist/release
mkdir build

cd build || exit 1
cmake -DCPACK_GENERATOR="TBZ2;ZIP;DEB" -DCPACK_SOURCE_GENERATOR="TBZ2;ZIP;DEB" ..
make html man package package_source
mv libubjsc0.5-*.{tar.bz2,zip,deb} ../dist/release
cd .. || exit 1

./upload-artifacts.sh release
