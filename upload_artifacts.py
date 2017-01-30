#!/usr/bin/python3
"""
Uploads artifacts to FTP server from tools/artifact_server/server.py.
"""

import os
import sys
import urllib.parse
import traceback

from ftplib import FTP_TLS, all_errors

DATA = 'dist'

if 'ARTIFACT_SERVER_URL' not in os.environ:
    sys.exit(0)

URL = urllib.parse.urlparse(os.environ['ARTIFACT_SERVER_URL'])
COMMIT = os.environ['BITBUCKET_COMMIT']

with FTP_TLS() as cli:
    cli.connect(host=URL.hostname, port=URL.port)
    cli.auth()
    cli.prot_p()
    cli.login(URL.username, URL.password)

    try:
        cli.mkd(COMMIT)
    except all_errors:
        traceback.print_exc()

    for root, dirs, files in os.walk(DATA):
        root_cut = root[len(DATA) + 1:]
        target_dir_path = os.sep.join([COMMIT, root_cut])
        try:
            cli.mkd(target_dir_path)
        except all_errors:
            traceback.print_exc()

        for file in files:
            local_path = os.sep.join([root, file])
            target_path = os.sep.join([COMMIT, root_cut, file])

            print(local_path)

            try:
                with open(local_path, 'rb') as fp:
                    cli.storbinary("STOR {}".format(target_path), fp)
            except all_errors:
                traceback.print_exc()
