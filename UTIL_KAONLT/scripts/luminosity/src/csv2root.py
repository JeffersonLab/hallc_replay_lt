#! /usr/bin/python

#
# Description:
# ================================================================
# Time-stamp: "2020-04-21 21:49:15 trottar"
# ================================================================
#
# Author:  Richard L. Trotta III <trotta@cua.edu>
#
# Copyright (c) trottar
#
import pandas as pd
from csv import DictReader
import os, subprocess, sys

sys.path.insert(0, 'python/')
import root2py as r2p
r = r2p.pyRoot()

csv = sys.argv[0]

USER = subprocess.getstatusoutput("whoami")

if csv == "lumi_data":
    inp_f = "/u/group/c-kaonlt/USERS/%s/hallc_replay_lt/UTIL_KAONLT/scripts/luminosity/OUTPUTS/lumi_data.csv" % str(USER[1])
    out_f = "../OUTPUTS/lumi_data.root"
    try:
        lumi_data = dict(pd.read_csv(inp_f))
    except IOError:
        print("Error: %s does not appear to exist." % inp_f)
    print(lumi_data.keys())
    r.py2root(lumi_data,out_f)
elif csv == "yield_data":
    inp_f = "/u/group/c-kaonlt/USERS/%s/hallc_replay_lt/UTIL_KAONLT/scripts/luminosity/OUTPUTS/yield_data.csv" % str(USER[1])
    out_f = "../OUTPUTS/yield_data.root"
    try:
        yield_data = dict(pd.read_csv(inp_f))
    except IOError:
        print("Error: %s does not appear to exist." % inp_f)
    print(yield_data.keys())
    r.py2root(yield_data,out_f)
else:
    print("ERROR: Invalid csv")
    exit