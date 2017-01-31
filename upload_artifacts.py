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


def main(cli):
    """
        @todo
    """

    cli.connect(host=URL.hostname, port=URL.port)
    cli.auth()
    cli.prot_p()
    cli.login(URL.username, URL.password)

    tasks = []

    def do_tha_dir(adir):
        """
            @todo
        """
        print("MKDIR {}".format(adir))
        cli.mkd(adir)

    def do_tha_file(afrom, ato):
        """
            @todo
        """
        print("PUT {}".format(ato))
        with open(afrom, 'rb') as afile:
            cli.storbinary("STOR {}".format(ato), afile)

    tasks.append((do_tha_dir, COMMIT))

    for root, _unused, files in os.walk(DATA):
        _unused = _unused

        root_cut = root[len(DATA) + 1:]
        target_dir_path = os.sep.join([COMMIT, root_cut])
        tasks.append((do_tha_dir, target_dir_path))

        for file in files:
            local_path = os.sep.join([root, file])
            target_path = os.sep.join([COMMIT, root_cut, file])
            tasks.append((do_tha_file, local_path, target_path))

    for task in tasks:
        try:
            func, *args = task
            func(*args)
        except all_errors:
            traceback.print_exc(file=sys.stdout)

with FTP_TLS() as acli:
    main(acli)
