#!/usr/bin/python3
"""
"""

import os
import os.path
from pyftpdlib.authorizers import DummyAuthorizer
from pyftpdlib.handlers import FTPHandler
from pyftpdlib.servers import FTPServer

if __name__ == '__main__':
    data = os.path.join(os.getcwd(), 'files')
    authorizer = DummyAuthorizer()

    authorizer.add_user('pipelines', 'rower666', data, perm='elrmw')
    authorizer.add_anonymous(data)

    handler = FTPHandler
    handler.authorizer = authorizer

    address = ('', 2121)
    server = FTPServer(address, handler)

    server.serve_forever()
