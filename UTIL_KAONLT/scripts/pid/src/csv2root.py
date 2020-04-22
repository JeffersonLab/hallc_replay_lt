#! /usr/bin/python

#
# Description:
# ================================================================
# Time-stamp: "2020-04-21 21:41:55 trottar"
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
r = r2p.pyRoot()

USER = subprocess.getstatusoutput("whoami")

inp_f = "/u/group/c-kaonlt/USERS/%s/hallc_replay_lt/UTIL_KAONLT/scripts/pid/OUTPUTS/pid_data.csv" % str(USER[1])

try:
    pid_data = dict(pd.read_csv(inp_f))
except IOError:
    print("Error: %s does not appear to exist." % inp_f)
print(lumi_data.keys())

r.py2root(pid_data,"../OUTPUTS/pid_data.root")
