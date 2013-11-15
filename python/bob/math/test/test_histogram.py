#!/usr/bin/env python
# vim: set fileencoding=utf-8 :
# Manuel Guenther <Manuel.Guenther@idiap.ch>
# Tue May  1 18:12:43 CEST 2012
#
# Copyright (C) 2011-2013 Idiap Research Institute, Martigny, Switzerland

"""Tests bob interior point Linear Programming solvers
"""

import os, sys
import unittest
import bob
import numpy



class HistogramMeasureTest(unittest.TestCase):

  def chi_square(self, h1, h2):
    """Computes the chi-square distance between two histograms (or histogram sequences)"""
    d = 0
    for i in range(h1.shape[0]):
      if h1[i] != h2[i]: d += int(((h1[i] - h2[i])**2) / (h1[i] + h2[i]))
    return d


  def histogram_intersection(self, h1, h2):
    """Computes the intersection measure of the given histograms (or histogram sequences)"""
    dist = 0
    for i in range(h1.shape[0]):
      dist += min(h1[i], h2[i])
    return dist


  # initialize histograms to test the two measures
  m_h1 = numpy.array([0,15,3,7,4,0,3,0,17,12], dtype = numpy.int32)
  m_h2 = numpy.array([2,7,14,3,25,0,7,1,0,4], dtype = numpy.int32)

  m_h3 = numpy.random.random_integers(0,99,size=(100000,))
  m_h4 = numpy.random.random_integers(0,99,size=(100000,))

  m_h5 = numpy.array([1,0,0,1,0,0,1,0,1,1], dtype = numpy.float64)
  m_h6 = numpy.array([1,0,1,0,0,0,1,0,1,1], dtype = numpy.float64)

  index_1 = numpy.array([0,3,6,8,9], dtype = numpy.uint16)
  index_2 = numpy.array([0,2,6,8,9], dtype = numpy.uint16)
  values = numpy.array([1,1,1,1,1], dtype = numpy.float64)

  def test_histogram_intersection(self):
    # compare our implementation with bob.math
    self.assertEqual(
      self.histogram_intersection(self.m_h1, self.m_h2),
      bob.math.histogram_intersection(self.m_h1, self.m_h2)
    )
    self.assertEqual(
      self.histogram_intersection(self.m_h3, self.m_h4),
      bob.math.histogram_intersection(self.m_h3, self.m_h4)
    )

    # test specific (simple) case
    self.assertEqual(bob.math.histogram_intersection(self.m_h5, self.m_h5), 5.)
    self.assertEqual(bob.math.histogram_intersection(self.m_h5, self.m_h6), 4.)

    self.assertEqual(bob.math.histogram_intersection(self.index_1, self.values, self.index_1, self.values), 5.)
    self.assertEqual(bob.math.histogram_intersection(self.index_1, self.values, self.index_2, self.values), 4.)

  def test_chi_square(self):
    # compare our implementation with bob.math
    self.assertEqual(
      self.chi_square(self.m_h1, self.m_h2),
      bob.math.chi_square(self.m_h1, self.m_h2)
    )
    self.assertEqual(
      self.chi_square(self.m_h3, self.m_h4),
      bob.math.chi_square(self.m_h3, self.m_h4)
    )

    # test specific (simple) case
    self.assertEqual(bob.math.chi_square(self.m_h5, self.m_h5), 0.)
    self.assertEqual(bob.math.chi_square(self.m_h5, self.m_h6), 2.)

    self.assertEqual(bob.math.chi_square(self.index_1, self.values, self.index_1, self.values), 0.)
    self.assertEqual(bob.math.chi_square(self.index_1, self.values, self.index_2, self.values), 2.)

  def test_kullback_leibler(self):
    # compare our implementation with bob.math
    self.assertEqual(
      self.chi_square(self.m_h1, self.m_h2),
      bob.math.chi_square(self.m_h1, self.m_h2)
    )
    self.assertEqual(
      self.chi_square(self.m_h3, self.m_h4),
      bob.math.chi_square(self.m_h3, self.m_h4)
    )

    # test specific (simple) case
    self.assertEqual(bob.math.kullback_leibler(self.m_h5, self.m_h5), 0.)
    self.assertAlmostEqual(bob.math.kullback_leibler(self.m_h5, self.m_h6), 23.0256, 4)

    self.assertEqual(bob.math.kullback_leibler(self.index_1, self.values, self.index_1, self.values), 0.)
    self.assertAlmostEqual(bob.math.kullback_leibler(self.index_1, self.values, self.index_2, self.values), 23.0256, 4)
