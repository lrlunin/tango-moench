============
Installation
============

Follow the instructions to install the required dependencies and the package itself.

For advanced users or developers: see the :doc:`developer` section for more information.

.. contents::
   :depth: 4
   :local:

Dependencies installation
=========================

Common dependencies
-------------------

Ubuntu
^^^^^^

.. code-block:: bash

    sudo apt install build-essential cmake libzmq3-dev \
    rapidjson-dev libfmt-dev libhdf5-dev libboost-dev

CentOS/RedHat
^^^^^^^^^^^^^

.. code-block:: bash

    sudo yum install cmake gcc-c++ zeromq-devel rapidjson-devel \
    fmt-devel hdf5-devel boost-devel

cppTango
--------

Install prebuilt package 
^^^^^^^^^^^^^^^^^^^^^^^^

Follow the `original cppTango manual <https://gitlab.com/tango-controls/cppTango/-/blob/main/INSTALL.md>`_ for Ubuntu. There is only option to build it from source.

Install from source
^^^^^^^^^^^^^^^^^^^

Install omniORB
"""""""""""""""

Download the omniORB minimal version 4.3.2 from the `sourceforge <https://sourceforge.net/projects/omniorb/files/omniORB/omniORB-4.3.2/omniORB-4.3.2.tar.bz2/download>`_.

Unpack and install:

.. code-block:: bash

    tar xjvf omniORB.tar.bz2 && cd omniORB-4.3.2
    ./configure
    make -j 
    sudo make install

Install tango-idl
"""""""""""""""""

Checkout the source repository and install:

.. code-block:: bash

    git clone --depth 1 --branch 6.0.2 \
    https://gitlab.com/tango-controls/tango-idl.git
    cd tango-idl
    cmake -B build
    cmake --build build -j
    sudo cmake --install build

Install cppTango
""""""""""""""""

Checkout the source repository and install:

.. code-block:: bash

    git clone --recurse-submodules --depth 1 --branch 9.5.0 \
    https://gitlab.com/tango-controls/cppTango.git
    cd cppTango
    cmake -B build -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=OFF \
    -DTANGO_USE_JPEG=OFF -DTANGO_USE_TELEMETRY=OFF 
    cmake --build build -j
    sudo cmake --install build

Follow the `original Tango manual <https://tango-controls.readthedocs.io/en/latest/installation/tango-on-linux.html#centos>`_ for CentOS. You can either install a pre-built package from `MAX-IV repository <http://pubrepo.maxiv.lu.se/rpm/el9/x86_64/>`_ or build it from source as well.

slsDetectorPackage
------------------

Install the `required dependencies <https://slsdetectorgroup.github.io/devdoc/dependencies.html>`_ of slsDetectorPackage libraries and build the package from `sources <https://github.com/slsdetectorgroup/slsDetectorPackage>`_:

.. code-block:: bash

    # clone the library
    git clone --depth 1 --branch 8.0.1 \
    https://github.com/slsdetectorgroup/slsDetectorPackage.git
    cd slsDetectorGroup
    # create build folder
    # maybe you can also set -DSLS_USE_DETECTOR=OFF and
    # -DSLS_USE_RECEIVER=OFF if somehow you have to save space
    cmake -B build -DSLS_DEVEL_HEADERS=ON -DSLS_USE_MOENCH=ON
    # build the library
    cmake --build build
    # install the library (requires write access to /usr/lib etc)
    sudo cmake --install build -j

CUDA (optional)
---------------

Follow the `original CUDA manual <https://docs.nvidia.com/cuda/cuda-installation-guide-linux/index.html#package-manager-installation>`_ for your platform.

Package installation
====================

.. code-block:: bash

    git clone https://github.com/lrlunin/tango-moench.git
    cd tango-moench
    # configure the build files, use Release type for best performance
    cmake -B build -DCMAKE_BUILD_TYPE=Release
    # build the library
    cmake --build build -j
    # install the library (requires write access to /usr/lib etc)
    sudo cmake --install build
