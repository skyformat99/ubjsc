FROM debian:sid
MAINTAINER Tomasz Sieprawski <tomasz@sieprawski.eu
RUN apt-get update
RUN apt-get install -y cmake make gcc g++ doxygen graphviz lcov libjansson-dev libargtable2-dev valgrind mercurial cppcheck git wget unzip tcl8.5-dev xmlstarlet bc libcunit1-dev python3 python3-dev python3-setuptools python3-pip vera++ tar zip bzip2 build-essential shellcheck complexity
RUN pip3 install --upgrade pip
RUN pip3 install wheel virtualenv pep8 pylint
RUN hg clone https://bitbucket.org/tsieprawski/ptrie --rev 8b726adaf869 && \
    cd ptrie && \
    mkdir build && \
    cd build && \
    cmake -DCMAKE_INSTALL_PREFIX:PATH=/usr .. && \
    make all && \
    make install

RUN apt-get install -y python-setuptools
RUN git clone https://github.com/jorisroovers/pymarkdownlint.git && \
    cd pymarkdownlint && \
    python2 setup.py install

RUN wget -O - https://deb.nodesource.com/setup_7.x | bash -
RUN apt-get install -y nodejs
RUN npm install -g alex markdown-spellcheck

RUN apt-get install -y clang
