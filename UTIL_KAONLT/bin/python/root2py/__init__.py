#! /usr/bin/python

#
# Description:
# ================================================================
# Time-stamp: "2020-04-28 15:02:29 trottar"
# ================================================================
#
# Author:  Richard L. Trotta III <trotta@cua.edu>
#
# Copyright (c) trottar
#

from ROOT import TFile, TH1D
import numpy as np
import matplotlib.pyplot as plt
import uproot as up
import time, math, sys

from .root2py import pyDict, pyBranch, pyPlot, pyRoot, pyEquation

__version__ = '0.4.0'
__author__ = 'trottar'
__license__ = 'trottar'
__copyright__ = 'Copyright 2020 trottar'
