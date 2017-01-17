#!/bin/bash
set -x
FOLDER=$1

if ! test -d "dist/${FOLDER}"
then
    echo "Folder dist/${FOLDER} does not exist!"
    exit 1
fi

if test "${ARTIFACT_SERVER_URL}" == ""
then
    echo "Empty ARTIFACT_SERVER_URL, not uploading artifacts."
    exit 0
fi

cd dist || exit 1
find "${FOLDER}"
cd "${FOLDER}" || exit 1

find . -type f -exec curl --ftp-ssl --ftp-create-dirs -k -T {} "${ARTIFACT_SERVER_URL}/${BITBUCKET_COMMIT}/${FOLDER}/{}" \;
