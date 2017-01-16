#!/bin/bash
set -x

SERVERPID=0

setup()
{
    ./server.py &
    SERVERPID=$!

    sleep 1
}

teardown()
{
    PASS=$1
    kill "${SERVERPID}"
    test -f files/testfile.txt && rm files/testfile.txt
    test -f testfile.txt && rm testfile.txt
    test -f testfile.txt.downloaded && rm testfile.txt.downloaded

    exit ${PASS}
}

setup

dd if=/dev/urandom bs=1024 count=1 | md5sum > testfile.txt
cat testfile.txt

wput testfile.txt ftp://127.0.0.1:2121/testfile.txt && teardown 1

wput testfile.txt ftp://pipelines:rower666@127.0.0.1:2121/testfile.txt || teardown 1
test -f files/testfile.txt || teardown 1

wget -O testfile.txt.downloaded ftp://127.0.0.1:2121/testfile.txt || teardown 1
diff testfile.txt testfile.txt.downloaded || teardown 1

teardown 0
