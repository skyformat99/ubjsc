FROM debian:jessie
MAINTAINER Tomasz Sieprawski <tomasz@sieprawski.eu
RUN echo "deb http://ftp.debian.org/debian jessie-backports main" >> /etc/apt/sources.list
RUN apt-get update
RUN apt-get install -y cmake make gcc g++ doxygen graphviz gcovr libjansson-dev libargtable2-dev valgrind mercurial cppcheck git openjdk-8-jdk wget unzip tcl8.5-dev xmlstarlet

# vera++
RUN mkdir vera && \
    cd vera && \
    wget https://bitbucket.org/verateam/vera/get/v1.3.0.zip && \
    unzip -x v1.3.0.zip && \
    cd verateam-vera-* && \
    mkdir build && \
    cd build && \
    cmake -DCMAKE_INSTALL_PREFIX:PATH=/opt/vera -DVERA_USE_SYSTEM_LUA=OFF -DVERA_PYTHON=OFF -DVERA_LUA=OFF .. && \
    make && \
    make install && \
    /opt/vera/bin/vera++ --version && \
    cd ../../.. && \
    rm -r vera

# sonar scanner
RUN mkdir sonar-scanner && \
    cd sonar-scanner && \
    wget https://sonarsource.bintray.com/Distribution/sonar-scanner-cli/sonar-scanner-2.7.zip && \
    unzip sonar-scanner-2.7.zip && \
    mv sonar-scanner-2.7 /opt/sonar-scanner && \
    /opt/sonar-scanner/bin/sonar-scanner --version && \
    cd ..
