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
          glob.glob(os.path.join(CMAKE_SOURCE_DIR, 'python/*.c'))
INCLUDES = [os.path.join(CMAKE_SOURCE_DIR, x)
            for x in
            ['include', 'src']] + \
            ["../src", "../ptrie/src"]
LIBRARIES = ['ptrie']
MODULE = Extension('ubjspy', sources=SOURCES, include_dirs=INCLUDES, libraries=LIBRARIES)

setup(
    name='ubjspy',
    version='0.4.0',
    test_suite='test.unittests',
    ext_modules=[MODULE]
)
