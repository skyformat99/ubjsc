#!/bin/bash
set +x

if ! test -d "dist"
then
    echo "Folder dist does not exist, no artifacts to upload."
    exit 0
fi

if test "${ARTIFACT_SERVER_URL}" == ""
then
    echo "Empty ARTIFACT_SERVER_URL, not uploading artifacts."
    exit 0
fi

cd dist || exit 1
find . -type f
find . -type f -exec curl --ftp-ssl --ftp-create-dirs -k -T {} "${ARTIFACT_SERVER_URL}/${BITBUCKET_COMMIT}/{}" \;
rm -r ./*
