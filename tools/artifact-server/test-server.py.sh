#!/bin/bash
set -x

SERVERPID=0

setup()
{
    openssl req -x509 -newkey rsa:4096 -keyout testpem.pem -out testcert.pem -days 3650 -nodes -subj '/CN=www.mydom.com/O=My Company Name LTD./C=US'
    cat testpem.pem >> testcert.pem

    cat << EOF > testconfig.txt
PASSWD = "rower666"
PEMFILE = "testcert.pem"
EOF

    ./server.py testconfig.txt &
    SERVERPID=$!

    sleep 1
}

teardown()
{
    PASS=$1
    kill "${SERVERPID}"
    test -f files/testfile.txt && rm files/testfile.txt
    test -f testpem.pem && rm testpem.pem
    test -f testcert.pem && rm testcert.pem
    test -f testconfig.txt && rm testconfig.txt
    test -f testfile.txt && rm testfile.txt
    test -f testfile.txt.downloaded && rm testfile.txt.downloaded

    exit ${PASS}
}

setup

dd if=/dev/urandom bs=1024 count=1 | md5sum > testfile.txt
cat testfile.txt

curl --ftp-ssl -k --ftp-create-dirs -k -T testfile.txt --retry 0 ftp://127.0.0.1:2121/testfile.txt && teardown 1

curl --ftp-ssl -k --ftp-create-dirs -k -T testfile.txt ftp://pipelines:rower666@127.0.0.1:2121/testfile.txt || teardown 1
test -f files/testfile.txt || teardown 1

curl http://127.0.0.1:2180/testfile.txt -o testfile.txt.downloaded || teardown 1
diff testfile.txt testfile.txt.downloaded || teardown 1

teardown 0
