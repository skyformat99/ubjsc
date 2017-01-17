#!/usr/bin/python3
"""
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

    def translate_path(self, path):
        return os.sep.join([DATA, path])


def run_http_server(config):
    socketserver.TCPServer.allow_reuse_address = True
    httpd = socketserver.TCPServer(('', 2180), HS)
    httpd.serve_forever()


def run_ftps_server(config):
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

if __name__ == '__main__':
    config = imp.load_source('config', sys.argv[1])

    ftp = threading.Thread(target=run_ftps_server, args=(config,))
    ftp.daemon = True
    ftp.start()

    http = threading.Thread(target=run_http_server, args=(config,))
    http.daemon = True
    http.start()

    ftp.join()
    http.join()
