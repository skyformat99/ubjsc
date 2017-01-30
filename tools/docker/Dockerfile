FROM debian:jessie-slim
MAINTAINER Tomasz Sieprawski <tomasz@sieprawski.eu

RUN echo "deb http://ftp.debian.org/debian jessie-backports main" >> /etc/apt/sources.list
RUN apt-get update
RUN apt-get upgrade -y
RUN apt-get install -y -t jessie-backports cmake make gcc mercurial wget unzip python3 python3-dev python3-setuptools python3-pip \
    tar zip bzip2 build-essential
RUN apt-get install -y -t jessie-backports libjansson-dev libargtable2-dev
RUN apt-get install -y -t jessie-backports doxygen graphviz tcl8.5-dev xmlstarlet bc curl lcov valgrind cppcheck vera++

RUN pip3 install --upgrade pip
RUN apt-get install -y -t jessie-backports libssl-dev
RUN pip3 install wheel virtualenv pep8 pylint pyftpdlib pyopenssl

RUN apt-get install -y -t jessie-backports autogen
RUN wget https://ftp.gnu.org/gnu/complexity/complexity-1.10.tar.xz && \
    tar xvfJ complexity-1.10.tar.xz && \
    cd complexity-1.10 && \
    ./configure && \
    make && \
    make install

RUN hg clone https://bitbucket.org/tsieprawski/ptrie && \
    cd ptrie && \
    mkdir build && \
    cd build && \
    cmake -DCMAKE_INSTALL_PREFIX:PATH=/usr .. && \
    make all && \
    make install

RUN apt-get install -y shellcheck
