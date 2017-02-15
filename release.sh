#!/bin/bash
set -x
test -d build && rm -rf build
test -d dist && rm -rf dist
mkdir build
mkdir dist

cd build || exit 1
cmake -DCMAKE_BUILD_TYPE=Release \
    -DCPACK_GENERATOR="TBZ2;ZIP;DEB" \
    -DCPACK_SOURCE_GENERATOR="TBZ2;ZIP;DEB" ..
make html man package package_source
mv libubjsc0.5-*.{tar.bz2,zip,deb} ../dist
cd ../dist || exit 1

du -ah
for file in *.deb
do
    echo "###### #{$file}"
    dpkg -c "${file}"
done

for file in *.zip
do
    echo "###### #{$file}"
    unzip -l "${file}"
done

for file in *.tar.bz2
do
    echo "###### #{$file}"
    tar --bzip2 --list --verbose --file "${file}"
done

