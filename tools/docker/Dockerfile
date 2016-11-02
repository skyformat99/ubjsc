FROM debian:stretch
MAINTAINER Tomasz Sieprawski <tomasz@sieprawski.eu
RUN apt-get update
RUN apt-get install -y cmake make gcc g++ doxygen graphviz gcovr libjansson-dev libargtable2-dev valgrind mercurial cppcheck git openjdk-8-jdk wget unzip tcl8.5-dev xmlstarlet bc libcunit1-dev

# vera++
RUN mkdir vera && \
    cd vera && \
    wget https://bitbucket.org/verateam/vera/get/v1.3.0.zip && \
    unzip -x v1.3.0.zip && \
    cd verateam-vera-* && \
    mkdir build && \
    cd build && \
    cmake -DCMAKE_INSTALL_PREFIX:PATH=/usr -DVERA_USE_SYSTEM_LUA=OFF -DVERA_PYTHON=OFF -DVERA_LUA=OFF .. && \
    make && \
    make install && \
    vera++ --version && \
    cd ../../.. && \
    rm -r vera
