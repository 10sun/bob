.. vim: set fileencoding=utf-8 :
.. Andre Anjos <andre.anjos@idiap.ch>
.. Sun Apr 3 19:18:37 2011 +0200
.. 
.. Copyright (C) 2011-2013 Idiap Research Institute, Martigny, Switzerland

.. Index file for the Python bob::core bindings

======
 Core
======

The ``core`` module contains a variety of utilities to handle random number
generation (w.r.t. |project|'s machines), array data conversion and error
reporting and logging.

.. toctree::
   :maxdepth: 2

   ErrorReportingAndLogging
   ArrayNote

.. module:: bob.core.array

.. rubric:: Range conversion utilities

.. autosummary::
   :toctree: generated/

   convert

.. module:: bob.core.random

.. rubric:: Random Number Generators (RNG)

.. autosummary::
   :toctree: generated/

   mt19937

.. rubric:: RNG Helpers
   
.. autosummary::
   :toctree: generated/

   variate_generator

.. rubric:: Probability Distributions

.. autosummary::
   :toctree: generated/

   binomial_float32
   binomial_float64
   discrete_int16
   discrete_int32
   discrete_int64
   discrete_int8
   discrete_uint16
   discrete_uint32
   discrete_uint64
   discrete_uint8
   gamma_float32
   gamma_float64
   lognormal_float32
   lognormal_float64
   normal_float32
   normal_float64
   uniform_float32
   uniform_float64
   uniform_int16
   uniform_int32
   uniform_int64
   uniform_int8
   uniform_uint16
   uniform_uint32
   uniform_uint64
