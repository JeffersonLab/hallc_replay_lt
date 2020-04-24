#! /usr/bin/python

#
# Description:
# ================================================================
# Time-stamp: "2020-04-24 13:58:28 trottar"
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

from .root2py import pyDict, pyBranch, pyPlot, pyRoot

__version__ = '0.3.0'
__author__ = 'trottar'
__license__ = 'CUA'
__copyright__ = 'Copyright 2020 trottar'
