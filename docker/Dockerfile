FROM debian:stretch-backports
MAINTAINER Tomasz Sieprawski <tomasz@sieprawski.eu>

RUN apt-get update
RUN apt-get dist-upgrade -y
RUN apt-get install -y build-essential make gcc g++ mercurial git wget unzip tar bzip2 zip cmake

# Libraries
RUN git clone https://github.com/akheron/jansson.git && \
    cd jansson && \
#    git checkout 2.10 && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make && \
    make install && \
    cd ../.. && \
    rm -r jansson

# ./build.sh
RUN git clone https://github.com/Snaipe/Criterion.git && \
    cd Criterion && \
    git checkout tags/v2.3.1 && \
    mkdir build && \
    cd build && \
    cmake -DCMAKE_INSTALL_PREFIX:PATH=/usr .. && \
    make && \
    make install && \
    cd ../.. && \
    rm -r Criterion

# ./check-leaks.sh
RUN apt-get install -y valgrind

# ./check-coverage.sh
RUN apt-get install -y ruby rake
RUN gem install bundler
RUN git clone https://bitbucket.org/tsieprawski/coveralls-lcov.git && \
    cd coveralls-lcov && \
    rake install && \
    cd .. && \
    rm -r coveralls-lcov

# ./check-static.sh
RUN apt-get install -y doxygen graphviz lcov cppcheck xmlstarlet bc python3 python3-dev python3-setuptools python3-pip vera++ shellcheck
RUN apt-get install -y complexity

RUN pip3 install --upgrade pip
RUN pip3 install wheel virtualenv pep8 pylint
RUN hg clone https://bitbucket.org/tsieprawski/ptrie && \
    cd ptrie && \
    mkdir build && \
    cd build && \
    cmake -DCMAKE_INSTALL_PREFIX:PATH=/usr .. && \
    make all && \
    make install && \
    cd ../.. && \
    rm -r ptrie

RUN apt-get install -y python-setuptools
RUN git clone https://github.com/jorisroovers/pymarkdownlint.git && \
    cd pymarkdownlint && \
    python2 setup.py install && \
    cd .. && \
    rm -r pymarkdownlint

RUN wget -O - https://deb.nodesource.com/setup_7.x | bash -
RUN apt-get install -y nodejs
RUN npm install -g alex markdown-spellcheck

