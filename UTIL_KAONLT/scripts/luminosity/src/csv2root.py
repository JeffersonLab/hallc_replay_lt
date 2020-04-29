#! /usr/bin/python

#
# Description:
# ================================================================
# Time-stamp: "2020-04-29 12:09:33 trottar"
# ================================================================
#
# Author:  Richard L. Trotta III <trotta@cua.edu>
#
# Copyright (c) trottar
#
import pandas as pd
from csv import DictReader
import os, subprocess, sys

sys.path.insert(0, '../../../bin/python/')
import root2py as r2p
r = r2p.pyRoot()

csv = sys.argv[1]

# Add this to all files for more dynamic pathing
USER = subprocess.getstatusoutput("whoami") # Grab user info for file finding
HOST = subprocess.getstatusoutput("hostname")

if ("farm" in HOST[1]):
    REPLAYPATH = "/group/c-kaonlt/USERS/%s/hallc_replay_lt" % USER[1]
elif ("lark" in HOST[1]):
    REPLAYPATH = "/home/%s/work/JLab/hallc_replay_lt" % USER[1]
elif ("trottar" in HOST[1]):
    REPLAYPATH = "/home/trottar/Analysis/hallc_replay_lt"
    
print("Running as %s on %s, hallc_replay_lt path assumed as %s" % (USER[1], HOST[1], REPLAYPATH))

if csv == "lumi_data":
    inp_f = "%s/UTIL_KAONLT/scripts/luminosity/OUTPUTS/lumi_data.csv" % str(REPLAYPATH)
    out_f = "%s/UTIL_KAONLT/scripts/luminosity/OUTPUTS/lumi_data.root" % str(REPLAYPATH)
    try:
        lumi_data = dict(pd.read_csv(inp_f))
    except IOError:
        print("Error: %s does not appear to exist." % inp_f)
    print(lumi_data.keys())
    r.py2root(lumi_data,out_f)
elif csv == "yield_data":
    inp_f = "%s/UTIL_KAONLT/scripts/luminosity/OUTPUTS/yield_data.csv" % str(REPLAYPATH)
    out_f = "%s/UTIL_KAONLT/scripts/luminosity/OUTPUTS/yield_data.root" % str(REPLAYPATH)
    try:
        yield_data = dict(pd.read_csv(inp_f))
    except IOError:
        print("Error: %s does not appear to exist." % inp_f)
    print(yield_data.keys())
    for key,val in yield_data.items():
        yield_data[key] = eval(val.tolist()[0])
    r.py2root(yield_data,out_f)
else:
    print("ERROR: Invalid csv")
    exit
