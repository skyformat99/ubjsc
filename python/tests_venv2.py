"""
"Test" that installs ubjspy*.whl and tries to import it,
to prove that wheel creation works.
Normally this occurs in virtualenv.
"""
# coding=utf-8
import glob
import os
import re
import subprocess


if __name__ == '__main__':
    HERE = os.path.dirname(__file__)

    WHEELS = glob.glob('ubjspy-*.whl')
    subprocess.check_call([os.path.join(HERE, "bin", "pip3"), "install", WHEELS[0]])

    PATTERN = re.compile('^ubjspy')
    PACKAGES = subprocess.check_output([os.path.join(HERE, "bin", "pip3"),
                                        "list"]).decode('utf-8').split("\n")
    if len([x for x in PACKAGES if PATTERN.match(x)]) == 0:
        raise Exception("ubjspy not installed")

    subprocess.check_call([os.path.join(HERE, "bin", "python3"), "-c",
                           "import ubjspy;"])
