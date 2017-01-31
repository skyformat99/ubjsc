#!/usr/bin/python3
"""
Uploads artifacts to FTP server from tools/artifact_server/server.py.
"""

from concurrent.futures import ThreadPoolExecutor

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


def main():
    """
        @todo
    """

    def start_ftp():
        """
            @todo
        """

        cli = FTP_TLS()
        cli.connect(host=URL.hostname, port=URL.port)
        cli.auth()
        cli.prot_p()
        cli.login(URL.username, URL.password)
        return cli

    def run_tasks(tasks):
        """
            @todo
        """
        executor = ThreadPoolExecutor(max_workers=10)
        for task in tasks:
            func, *args = task
            executor.submit(func, *args)
        executor.shutdown()

    def do_tha_dir(adir):
        """
            @todo
        """
        print("MKDIR {}".format(adir))

        try:
            cli = start_ftp()
            cli.mkd(adir)
        except all_errors:
            traceback.print_exc()

    def do_tha_file(afrom, ato):
        """
            @todo
        """
        print("PUT {}".format(ato))

        try:
            cli = start_ftp()
            with open(afrom, 'rb') as afile:
                cli.storbinary("STOR {}".format(ato), afile)
        except all_errors:
            traceback.print_exc()

    dirtasks = []
    filetasks = []
    dirtasks.append((do_tha_dir, COMMIT))

    for root, _unused, files in os.walk(DATA):
        _unused = _unused

        root_cut = root[len(DATA) + 1:]
        target_dir_path = os.sep.join([COMMIT, root_cut])
        dirtasks.append((do_tha_dir, target_dir_path))

        for file in files:
            local_path = os.sep.join([root, file])
            target_path = os.sep.join([COMMIT, root_cut, file])
            filetasks.append((do_tha_file, local_path, target_path))

    run_tasks(dirtasks)
    run_tasks(filetasks)

if __name__ == '__main__':
    main()
