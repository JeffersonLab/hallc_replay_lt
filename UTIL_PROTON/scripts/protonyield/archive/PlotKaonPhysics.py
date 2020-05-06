#! /usr/bin/python

# 5/5/20 - Stephen Kay, University of Regina

# Python plotting script, reads in desired trees from analysed root file and plots some stuff
# Edit - This is probably not what we want to do so stopping development of this script - has some nice examples of stuff though so will retain in archive

# Import relevant packages
import uproot as up
import numpy as np
import pandas as pd
import ROOT
import scipy
import scipy.integrate as integrate
import matplotlib.pyplot as plt
import sys, math, os, subprocess
from os import path

sys.path.insert(0, 'python/')
if len(sys.argv)-1!=1:
    print("!!!!! ERROR !!!!!!\n Expected 1 argument\n Usage is with - Filename\n!!!!! ERROR !!!!!")
    sys.exit(1)
# Input params - run number and max number of events
Filename= sys.argv[1]
USER = subprocess.getstatusoutput("whoami") # Grab user info for file finding
HOST = subprocess.getstatusoutput("hostname")
if ("farm" in HOST[1]):
    REPLAYPATH = "/group/c-kaonlt/USERS/%s/hallc_replay_lt" % USER[1]
elif ("lark.phys.uregina" in HOST[1]):
    REPLAYPATH = "/home/%s/work/JLab/hallc_replay_lt" % USER[1]

# Add more path setting as needed in a similar manner
OUTPATH = "%s/UTIL_PROTON/scripts/protonyield/OUTPUT" % REPLAYPATH
sys.path.insert(0, '%s/UTIL_PROTON/bin/python/' % REPLAYPATH)
import kaonlt as klt

print("Running as %s on %s, searching for %s in %s" % (USER[1], HOST[1], Filename, OUTPATH))
rootName = "%s/%s" % (OUTPATH, Filename)
if path.exists("%s" % rootName) :
    print("Processing %s" % rootName)
else:
    print("!!!!! ERROR !!!!!\n %s not found \n Check filename argument and pathing\n!!!!! ERROR !!!!!" % rootName)
    sys.exit(2)

Uncut_tree = up.open(rootName)["Uncut_Kaon_Events"]
Cut_tree_all = up.open(rootName)["Cut_Kaon_Events_All"]
Cut_tree_prompt = up.open(rootName)["Cut_Kaon_Events_Prompt"]
Cut_tree_random = up.open(rootName)["Cut_Kaon_Events_Random"]


