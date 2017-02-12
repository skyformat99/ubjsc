#!/bin/bash
set -x

PEMFILE=/etc/ubjsc-artifact-server.pem
USER=tomasz
HOMEDIR=$(pwd)
PIDFILE=/var/run/ubjsc-artifact-server.pid

TARGETCONFIG=/etc/ubjsc-artifact-server.config
TARGETFILE=/etc/init.d/ubjsc-artifact-server

cat << EOF > config.1
PASSWD = "rowery666"
PEMFILE = "${PEMFILE}"
EOF

openssl req -x509 -newkey rsa:4096 -keyout key.pem -out keycert.pem -days 3650 -nodes -subj '/CN=www.mydom.com/O=My Company Name LTD./C=US'
cat key.pem >> keycert.pem
rm key.pem

cp start-stop.sh.example start-stop.sh.1
sed -i "s|%USER%|${USER}|" start-stop.sh.1
sed -i "s|%HOMEDIR%|${HOMEDIR}|" start-stop.sh.1
sed -i "s|%PIDFILE%|${PIDFILE}|" start-stop.sh.1
sed -i "s|%CONFIG%|${TARGETCONFIG}|" start-stop.sh.1

diff start-stop.sh.example start-stop.sh.1 && exit 1

mv config.1 "${TARGETCONFIG}"
mv start-stop.sh.1 "${TARGETFILE}"
mv keycert.pem "${PEMFILE}"
chmod 660 "${PEMFILE}"
chown tomasz:root "${PEMFILE}"
