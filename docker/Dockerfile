# Dockerfile_935

ARG BASE_IMAGE=ubuntu:latest

# Use the latest version of Ubuntu as the base image
FROM ${BASE_IMAGE}

ARG OMNI_ORB_REF=https://sourceforge.net/projects/omniorb/files/omniORB/omniORB-4.3.2/omniORB-4.3.2.tar.bz2/download

ARG TANGO_GIT_REF=https://gitlab.com/tango-controls/cppTango.git

ARG TANGO_VERSION

ARG SLS_GIT_REF=https://github.com/slsdetectorgroup/slsDetectorPackage.git

ARG SLS_VERSION

# Set the name of the Docker image
LABEL name="tango-${TANGO_VERSION}-sls-${SLS_VERSION}"

# Update the package list and install necessary libraries
RUN apt-get update && apt-get install -y \
    build-essential \
    wget \
    cmake \
    git \
    python3-dev

# Install tango libs
RUN apt-get update && apt-get install -y \
    libmariadb-dev \
    libzmq3-dev \
    zlib1g-dev \
    # libomniorb4-dev \
    libcos4-dev \
    omniidl

# Downloda omniorb
RUN wget -O /tmp/omniORB.tar.bz2 ${OMNI_ORB_REF}

RUN cd /tmp/ && \
    tar xjvf omniORB.tar.bz2 && \
    cd omniORB-4.3.2 && \
    ./configure && \
    make -j && \
    make install

# Download tango-idl
RUN git clone --depth 1 --branch 6.0.2 https://gitlab.com/tango-controls/tango-idl.git /tmp/tango-idl

# Install tango-idl
RUN cd /tmp/tango-idl && \
    cmake -B build && \
    cmake --build build && \
    cmake --install build

# Download cppTango
RUN git clone --recurse-submodules --depth 1 --branch ${TANGO_VERSION} ${TANGO_GIT_REF} /tmp/cppTango

# Install Tango
RUN cd /tmp/cppTango && \
    cmake -B build -DBUILD_TESTING=OFF -DTANGO_USE_JPEG=OFF -DTANGO_USE_TELEMETRY=OFF -DCMAKE_BUILD_TYPE=Release && \
    cmake --build build -j && \
    cmake --install build

# Install sls detector libs
RUN apt-get update && apt-get install -y \
    rapidjson-dev \
    libtiff-dev

# Download slsDetectorPackage
RUN git clone --depth 1 --branch ${SLS_VERSION} ${SLS_GIT_REF} /tmp/slsDetectorPackage

# Install slsDetectorPackage
RUN cd /tmp/slsDetectorPackage && \
    cmake -B build -DCMAKE_BUILD_TYPE=${BUILD_TYPE} -DSLS_DEVEL_HEADERS=ON -DSLS_USE_MOENCH=ON && \
    cmake --build build -j && \
    cmake --install build

# install tango-moench libs
RUN apt-get update && apt-get install -y \
    libhdf5-dev \
    libboost-dev \
    libfmt-dev \
    lcov

# Clean up the package lists to reduce the image size
RUN apt-get clean && rm -rf /var/lib/apt/lists/* && rm -rf /tmp/*
