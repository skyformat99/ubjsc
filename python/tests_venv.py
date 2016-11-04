# coding=utf-8
import glob
import os
import shutil
import subprocess


if __name__ == '__main__':
    here = os.path.dirname(__file__)

    subprocess.check_call(["virtualenv", "env"])
    shutil.copy(os.path.join(here, "tests_venv2.py"), "env")

    whl = glob.glob('ubjspy-*.whl')
    if len(whl) == 0:
        raise Exception("No whl")
    shutil.copy(whl[0], "env")

    subprocess.check_call([os.path.join("env", "bin", "python3"),
                           os.path.join("env", "tests_venv2.py")])

