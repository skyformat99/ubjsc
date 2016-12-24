"""
Simply setup.py.
"""

import glob
import os
import os.path
import sys
from setuptools import setup, Extension

CMAKE_SOURCE_DIR = sys.argv.pop()

SOURCES = glob.glob(os.path.join(CMAKE_SOURCE_DIR, 'ubjsc/src/*.c')) + \
          glob.glob(os.path.join(CMAKE_SOURCE_DIR, 'ubjsc-glue-dict-ptrie/src/*.c')) + \
          glob.glob(os.path.join(CMAKE_SOURCE_DIR, 'ubjspy/*.c'))
INCLUDES = [os.path.join(CMAKE_SOURCE_DIR, x)
            for x in
            ['ubjsc/include', 'ubjsc/src', 'ubjsc-glue-dict-ptrie/src']] + \
            ["../ubjsc/src", "../ubjsc-glue-dict-ptrie/src"]
LIBRARIES = ['ptrie']
MODULE = Extension('ubjspy', sources=SOURCES, include_dirs=INCLUDES, libraries=LIBRARIES)

setup(
    name='ubjspy',
    version='0.4.0',
    test_suite='test.unittests',
    ext_modules=[MODULE]
)
