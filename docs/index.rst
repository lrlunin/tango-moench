.. tango-moench documentation master file, created by
   sphinx-quickstart on Sat Feb  1 12:01:32 2025.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Welcome to ``tango-moench`` documentation
==========================

This project provides a set of tools to control the MÖNCH detector via Tango and to process the acquired data in real-time.

Checkout the `Sardana controller <https://github.com/MBI-Div-B/sardana-MOENCHTangoTwoDController>`_ for your world class quality experiements.

Main Features
-------------
``tango-moenchcontrol``
~~~~~~~~~~~~~~~~~~~~~~~
- all the parameters of the MÖNCH detector can be controlled via Tango
- the device server is fully compliant with the Tango Control System

``tango-moenchzmq``
~~~~~~~~~~~~~~~~~~~~~~~
- *blazingly fast* 🚀 online data processing and evaluation of the acquired frames
- extensive code coverage
- individual frame export into ``HDF5`` format


.. toctree::
   :maxdepth: 2
   :caption: Contents:

   install
   api
   faq
   developer
   about
