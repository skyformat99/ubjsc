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
    glob.glob(os.path.join(CMAKE_SOURCE_DIR, 'ubjspy/*.c'))
INCLUDES = [os.path.join(CMAKE_SOURCE_DIR, x)
            for x in
            ['ubjsc/include', 'ubjsc/src']] + \
    ["../ubjsc/src"]
LIBRARIES = []
MODULE = Extension('ubjspy', sources=SOURCES,
                   include_dirs=INCLUDES, libraries=LIBRARIES)
DESCRIPTION = """
Enterprise grade-wannabe C library for manipulating and streaming data in UBJSON format.'
"""
setup(
    name='ubjspy',
    version='0.5.0',
    description=DESCRIPTION,
    author='Tomasz Sieprawski',
    author_email='tomasz@sieprawski.eu',
    url='https://bitbucket.org/tsieprawski/ubjsc',
    test_suite='test.unittests',
    ext_modules=[MODULE]
)
