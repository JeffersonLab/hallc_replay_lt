#! /usr/bin/python

#
# Description:
# ================================================================
# Time-stamp: "2020-04-21 21:38:13 trottar"
# ================================================================
#
# Author:  Richard L. Trotta III <trotta@cua.edu>
#
# Copyright (c) trottar
#
from csv import DictReader
import os, subprocess, sys

sys.path.insert(0, 'python/')
import root2py as r2p

csv = sys.argv[0]

r = r2p.pyRoot()

if csv == "lumi_data":
    inp_f = "/u/group/c-kaonlt/USERS/%s/hallc_replay_lt/UTIL_KAONLT/scripts/luminosity/OUTPUTS/lumi_data.csv" % str(USER[1])
    out_f = "../OUTPUTS/lumi_data.root"
elif csv == "yield_data":
    inp_f = "/u/group/c-kaonlt/USERS/%s/hallc_replay_lt/UTIL_KAONLT/scripts/luminosity/OUTPUTS/yield_data.csv" % str(USER[1])
    out_f = "../OUTPUTS/yield_data.root"
else:
    print("ERROR: Invalid csv")
    exit
    
try:
    pid_data = dict(pd.read_csv(inp_f))
except IOError:
    print("Error: %s does not appear to exist." % inp_f)
print(lumi_data.keys())

r.py2root(pid_data,out_f)
