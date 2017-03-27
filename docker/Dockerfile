FROM debian:sid
MAINTAINER Tomasz Sieprawski <tomasz@sieprawski.eu
RUN apt-get update
RUN apt-get install -y cmake make gcc g++ doxygen graphviz lcov libjansson-dev libargtable2-dev valgrind mercurial cppcheck git wget unzip tcl8.5-dev xmlstarlet bc libcunit1-dev python3 python3-dev python3-setuptools python3-pip vera++ tar zip bzip2 build-essential shellcheck complexity
RUN pip3 install --upgrade pip
RUN pip3 install wheel virtualenv pep8 pylint
RUN hg clone https://bitbucket.org/tsieprawski/ptrie --rev 2e9b1d2dd08 && \
    cd ptrie && \
    mkdir build && \
    cd build && \
    cmake -DCMAKE_INSTALL_PREFIX:PATH=/usr .. && \
    make all && \
    make install && \
    cd ../..

RUN apt-get install -y python-setuptools
RUN git clone https://github.com/jorisroovers/pymarkdownlint.git && \
    cd pymarkdownlint && \
    python2 setup.py install && \
    cd ..

RUN wget -O - https://deb.nodesource.com/setup_7.x | bash -
RUN apt-get install -y nodejs
RUN npm install -g alex markdown-spellcheck

RUN git clone https://github.com/Snaipe/Criterion.git && \
    cd Criterion && \
    git checkout tags/v2.3.1 && \
    mkdir build && \
    cd build && \
    cmake -DCMAKE_INSTALL_PREFIX:PATH=/usr .. && \
    make && \
    make install && \
    cd ..

RUN apt-get install -y ruby
RUN gem install bundler
RUN git clone https://tsieprawski@bitbucket.org/tsieprawski/coveralls-lcov.git && \
    cd coveralls-lcov && \
    rake install
