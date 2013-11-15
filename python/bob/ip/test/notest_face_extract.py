#!/usr/bin/env python
# vim: set fileencoding=utf-8 :
# Niklas Johansson <niklas.johansson@idiap.ch>
# Wed Apr 6 19:07:07 2011 +0200
#
# Copyright (C) 2011-2013 Idiap Research Institute, Martigny, Switzerland

"""Test all ip image filters.
"""

import math
import os, sys
import unittest
import bob
import numpy
import pkg_resources

def F(f):
  """Returns the test file on the "data" subdirectory"""
  return pkg_resources.resource_filename(__name__, os.path.join('data', f))

# face data
LH = 120 # Left eye height
LW = 147 # Left eye width
RH = 90  # Right eye height
RW = 213 # Right eye width

GOAL_EYE_DISTANCE = 30

class FaceExtractTest(unittest.TestCase):
  """Performs various combined filter tests."""

  def test01_shiftColorImage(self):

    img = bob.io.Array(F(os.path.join('faceextract', 'test_001.png')))
    A = img.get()
    B = A.copy()

    delta_h = 100
    delta_w = 100

    # shift to center
    bob.ip.shift(A, B, delta_h, delta_w)

    # save image
    bob.io.Array(B).save(os.path.join('faceextract', 'test_001.shift.png'))

  def test02_shiftToCenterBlue(self):

    img = bob.io.Array(F(os.path.join('faceextract', 'test_001.png')))
    A = img.get()
    B = A.copy()

    # shift to center
    bob.ip.shiftToCenterOfPoints(A, B, LH, LW, RH, RW)

    # save image
    bob.io.Array(B).save(os.path.join('faceextract', 'test_001.blue.answer.png'))

  def test03_shiftToCenterBlue_And_LevelOut(self):

    img = bob.io.Array(F(os.path.join('faceextract', 'test_001.gray.png')))
    A = img.get()[1,:,:]
    B = A.copy()

    # shift to center
    bob.ip.shiftToCenterOfPoints(A, B, LH, LW, RH, RW)

    # rotate
    angle = bob.ip.getAngleToHorizontal(LH, LW, RH, RW)
    shape = bob.ip.getShapeRotated(B, angle)
    C = B.copy()
    C.resize(shape)
    bob.ip.rotate(B, C, angle)
    
    # save image
    bob.io.Array(C).save(F(os.path.join('faceextract', 'test_001.blue.level.answer.png')))

  def test04_geoNormBlue(self):

    # read up image
    img = bob.io.Array(F(os.path.join('faceextract', 'test_001.gray.png')))
    A = img.get()[1,:,:]
    B = A.copy()

    # shift to center
    bob.ip.shiftToCenterOfPoints(A, B, LH, LW, RH, RW)

    # rotate
    angle = bob.ip.getRotateAngleToLevelOutHorizontal(LH, LW, RH, RW)
    shape = bob.ip.getShapeRotated(B, angle)
    C = B.copy()
    C.resize(shape)
    bob.ip.rotate(B, C, angle)

    # normalise
    previous_eye_distance = math.sqrt((RH - LH) * (RH - LH) + (RW - LW) * (RW - LW))
    print(previous_eye_distance)

    scale_factor = GOAL_EYE_DISTANCE / previous_eye_distance

    #
    D = bob.ip.scaleAs(C, scale_factor)
    bob.ip.scale(C, D)

  def test05_geoNormFace(self):

    # read up image
    img = bob.io.Array(F(os.path.join('faceextract', 'test-faces.jpg')))
    A = img.get()[1,:,:]

    # read up the eye coordinates
    f = open(F(os.path.join('faceextract', 'test-faces.txt')))
    coord = f.readline().split('\n')[0].split(' ')
    print(coord)

    LH = int(coord[0])
    LW = int(coord[1])
    RH = int(coord[2])
    RW = int(coord[3])

    # shift to center
    B = A.copy()
    bob.ip.shiftToCenterOfPoints(A, B, LH, LW, RH, RW)

    # rotate
    angle = bob.ip.getRotateAngleToLevelOutHorizontal(LH, LW, RH, RW)
    shape = bob.ip.getShapeRotated(B, angle)
    C = B.copy()
    C.resize(shape)
    bob.ip.rotate(B, C, angle)

    # normalise
    previous_eye_distance = math.sqrt((RH - LH) * (RH - LH) + (RW - LW) * (RW - LW))
    print(previous_eye_distance)

    scale_factor = GOAL_EYE_DISTANCE / previous_eye_distance

    #
    D = bob.ip.scaleAs(C, scale_factor)
    bob.ip.scale(C, D)
    bob.io.Array(D).save(os.path.join('data', 'faceextract', 'test-faces.1.jpg'))

    
    # crop face
    E = numpy.ndarray((100, 100), 'uint8')
    bob.ip.cropFace(D, E, 30)
    bob.io.Array(E).save(os.path.join('data', 'faceextract', 'test-faces.E.jpg'))
