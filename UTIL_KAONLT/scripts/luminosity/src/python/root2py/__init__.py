#! /usr/bin/python

#
# Description:
# ================================================================
# Time-stamp: "2020-03-25 17:30:46 trottar"
# ================================================================
#
# Author:  Richard L. Trotta III <trotta@cua.edu>
#
# Copyright (c) trottar
#

import numpy as np
import matplotlib.pyplot as plt
import uproot as up
import time, math, sys

from .root2py import pyDict, pyBranch, pyBin, pyPlot

__version__ = '0.1.0'
__author__ = 'trottar'
__license__ = 'CUA'
__copyright__ = 'Copyright 2020 trottar'
