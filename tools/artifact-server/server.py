#!/usr/bin/python3
"""
@todo
"""

import os
import os.path
import imp
import sys
import threading
from http.server import SimpleHTTPRequestHandler
import socketserver
from pyftpdlib.authorizers import DummyAuthorizer
from pyftpdlib.handlers import TLS_FTPHandler
from pyftpdlib.servers import FTPServer

DATA = 'files'


class HS(SimpleHTTPRequestHandler):
    """
        Regular directory listing handler, except that it does not go of cwd(),
        but prespecified folder.
    """

    def translate_path(self, path):
        """
            Changes path to DATA + path.
        """

        return os.sep.join([DATA, path])


def run_http_server():
    """
        Runs HTTP server.
        This is blocking, so it should be run in a thread.
    """

    socketserver.TCPServer.allow_reuse_address = True
    httpd = socketserver.TCPServer(('', 2180), HS)
    httpd.serve_forever()


def run_ftps_server(config):
    """
        Runs FTPS push-only server.
        This is blocking, so it should be run in a thread.
    """

    authorizer = DummyAuthorizer()
    authorizer.add_user('pipelines', config.PASSWD, DATA, perm='elrmw')

    handler = TLS_FTPHandler
    handler.certfile = config.PEMFILE
    handler.authorizer = authorizer
    handler.tls_control_required = True
    handler.tls_data_required = True

    address = ('', 2121)
    server = FTPServer(address, handler)

    server.serve_forever()


def main():
    """
        Main.
    """

    config = imp.load_source('config', sys.argv[1])

    ftp = threading.Thread(target=run_ftps_server, args=(config,))
    ftp.daemon = True
    ftp.start()

    http = threading.Thread(target=run_http_server)
    http.daemon = True
    http.start()

    ftp.join()
    http.join()

if __name__ == '__main__':
    main()