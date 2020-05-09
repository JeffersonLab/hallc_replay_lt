#! /usr/bin/python

#
# Description:
# ================================================================
# Time-stamp: "2020-05-08 21:29:13 trottar"
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
import kaonlt as klt
r = klt.pyRoot()

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

inp_f = "%s/UTIL_KAONLT/scripts/pid/OUTPUTS/pid_data.csv" % str(REPLAYPATH)
out_f = "%s/UTIL_KAONLT/scripts/pid/OUTPUTS/pid_data.root" % str(REPLAYPATH)

try:
    pid_data = dict(pd.read_csv(inp_f))
except IOError:
    print("Error: %s does not appear to exist." % inp_f)
print(pid_data.keys())
r.csv2root(pid_data,out_f)
