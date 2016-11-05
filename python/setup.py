"""
Simply setup.py.
"""

import glob
import os
import os.path
import sys
from setuptools import setup, Extension

CMAKE_SOURCE_DIR = sys.argv.pop()

SOURCES = glob.glob(os.path.join(CMAKE_SOURCE_DIR, 'src/*.c')) + \
          glob.glob(os.path.join(CMAKE_SOURCE_DIR, 'ptrie/src/*.c')) + \
          glob.glob(os.path.join(CMAKE_SOURCE_DIR, 'python/*.c'))
INCLUDES = [os.path.join(CMAKE_SOURCE_DIR, x)
            for x in
            ['include', 'src', 'ptrie/include', 'ptrie/src']] + \
            ["../src", "../ptrie/src"]
MODULE = Extension('ubjspy', sources=SOURCES, include_dirs=INCLUDES)

setup(
    name='ubjspy',
    version='0.4-dev',
    test_suite='test.unittests',
    ext_modules=[MODULE]
)
