# coding=utf-8
import glob
import os
import re
import subprocess


if __name__ == '__main__':
    here = os.path.dirname(__file__)

    whl = glob.glob('ubjspy-*.whl')
    subprocess.check_call([os.path.join(here, "bin", "pip3"), "install", whl[0]])

    pattern = re.compile('^ubjspy')
    packages = subprocess.check_output([os.path.join(here, "bin", "pip3"), "list"]).decode('utf-8').split("\n")
    if len([x for x in packages if pattern.match(x)]) == 0:
        raise Exception("ubjspy not installed")

    subprocess.check_call([os.path.join(here, "bin", "python3"), "-c", "import ubjspy; print(ubjspy);"])
