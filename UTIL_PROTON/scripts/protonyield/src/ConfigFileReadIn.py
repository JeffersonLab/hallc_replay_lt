#! /usr/bin/python

# 28/4/20 - Stephen Kay, University of Regina
#Short script to test reading in of config file
# Import relevant packages
import uproot as up
import numpy as np
import pandas as pd
import ROOT
import scipy
import scipy.integrate as integrate
import matplotlib.pyplot as plt
import sys, math, os, subprocess

sys.path.insert(0, 'python/')
ConfigFileName = sys.argv[1]
USER = subprocess.getstatusoutput("whoami") # Grab user info for file finding
HOST = subprocess.getstatusoutput("hostname")
if ("farm" in HOST[1]):
    REPLAYPATH = "/group/c-kaonlt/USERS/%s/hallc_replay_lt" % USER[1]
elif ("lark.phys.uregina" in HOST[1]):
    REPLAYPATH = "/home/%s/work/JLab/hallc_replay_lt" % USER[1]
ConfigFile = "%s/UTIL_PROTON/config/%s" % (REPLAYPATH,  ConfigFileName)
print("Using cuts defined in %s" % ConfigFile)

Configf = open(ConfigFile)
for line in Configf:
    if ("Timing_Cuts" in line):
        array = line.split("=")
        TimingTmp = array[1]
        TimingCutFile = "%s/UTIL_PROTON/config/%s" % (REPLAYPATH, TimingTmp)
    if ("PID_Cuts" in line):
        array = line.split("=")
        PIDTmp = array[1]
        PIDCutFile = "%s/UTIL_PROTON/config/%s" % (REPLAYPATH, PIDTmp)
    if ("Acceptance_Cuts" in line):
        array = line.split("=")
        AcceptTmp = array[1]
        AcceptCutFile = "%s/UTIL_PROTON/config/%s" % (REPLAYPATH, AcceptTmp)

try:
    TimingCutFile
    PIDCutFile
    AcceptCutFile
except NameError:
    print("Error, one (or more) of the cut files is not defined in the config file provided")
    sys.exit(2)
