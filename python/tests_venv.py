"""
"Test" that setups a virtualenv and runs subscript there.
This will copy tests_venv2.py and previously created ubjspy*.whl
into the virtualenv folder.
"""

# coding=utf-8
import glob
import os
import shutil
import subprocess


if __name__ == '__main__':
    HERE = os.path.dirname(__file__)

    subprocess.check_call(["virtualenv", "env"])
    shutil.copy(os.path.join(HERE, "tests_venv2.py"), "env")

    WHEELS = glob.glob('ubjspy-*.whl')
    if len(WHEELS) == 0:
        raise Exception("No whl")
    shutil.copy(WHEELS[0], "env")

    subprocess.check_call([os.path.join("env", "bin", "python3"),
                           os.path.join("env", "tests_venv2.py")])
