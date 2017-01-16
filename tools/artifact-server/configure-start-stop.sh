#!/bin/bash
set -x

USER=tomasz
HOMEDIR=$(pwd)
PIDFILE=/var/run/ubjsc-artifact-server.pid
PASSWD=rowery666
TARGETFILE=/etc/init.d/ubjsc-artifact-server

cp start-stop.sh.example start-stop.sh.1
sed -i "s|%USER%|${USER}|" start-stop.sh.1
sed -i "s|%HOMEDIR%|${HOMEDIR}|" start-stop.sh.1
sed -i "s|%PIDFILE%|${PIDFILE}|" start-stop.sh.1
sed -i "s|%PASSWD%|${PASSWD}|" start-stop.sh.1

diff start-stop.sh.example start-stop.sh.1 && exit 1
mv start-stop.sh.1 "${TARGETFILE}"
