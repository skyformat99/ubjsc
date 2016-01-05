#!/bin/bash
set -x
test -d build && rm -rf build
test -d dist && rm -rf dist
mkdir build
mkdir dist

cd build || exit 1
cmake -DCPACK_GENERATOR="TBZ2;ZIP;DEB" -DCPACK_SOURCE_GENERATOR="TBZ2;ZIP;DEB" ..
make package package_source html man
mv libubjsc0.4-*.{tar.bz2,zip,deb} ../dist
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

