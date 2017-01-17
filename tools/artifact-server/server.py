#!/usr/bin/python3
"""
"""

import os
import os.path
import imp
import sys
from pyftpdlib.authorizers import DummyAuthorizer
from pyftpdlib.handlers import TLS_FTPHandler
from pyftpdlib.servers import FTPServer

if __name__ == '__main__':
    config = imp.load_source('config', sys.argv[1])

    data = os.path.join(os.getcwd(), 'files')
    authorizer = DummyAuthorizer()

    authorizer.add_user('pipelines', config.PASSWD, data, perm='elrmw')
    authorizer.add_anonymous(data)

    handler = TLS_FTPHandler
    handler.certfile = config.PEMFILE
    handler.authorizer = authorizer
    handler.tls_control_required = True
    handler.tls_data_required = True

    address = ('', 2121)
    server = FTPServer(address, handler)

    server.serve_forever()
