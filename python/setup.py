import glob
import os
import os.path
import sys
from setuptools import setup, Extension

cmake_source_dir = sys.argv.pop()
sources = glob.glob(os.path.join(cmake_source_dir, 'src/*.c'))
sources += glob.glob(os.path.join(cmake_source_dir, 'ptrie/src/*.c'))
sources += glob.glob(os.path.join(cmake_source_dir, 'python/*.c'))
include_dirs = [os.path.join(cmake_source_dir, x)
                for x in ['include', 'src', 'ptrie/include', 'ptrie/src']] + \
                ["../src", "../ptrie/src"]
module = Extension('ubjspy', sources=sources, include_dirs=include_dirs)

setup(
    name='ubjspy',
    version='0.4-dev',
    test_suite='test.unittests',
    ext_modules=[module]
)
