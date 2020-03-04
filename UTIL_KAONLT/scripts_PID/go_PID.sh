#! /bin/bash

#
# Description:
# ================================================================
# Time-stamp: "2020-01-13 15:06:23 trottar"
# ================================================================
#
# Author:  Richard L. Trotta III <trotta@cua.edu>
#
# Copyright (c) trottar
#

runNum=$1
# numEvts=$2
numEvts=-1

# HMS
root -b -q -l "run_detectEfficiency.C+($runNum,$numEvts,\"hms\",\"cer\")"
# root -b -q -l "run_detectEfficiency.C+($runNum,$numEvts,\"hms\",\"cal\")"

# shms
# root -b -q -l "run_detectEfficiency.C+($runNum,$numEvts,\"shms\",\"cer\")"
# root -b -q -l "run_detectEfficiency.C+($runNum,$numEvts,\"shms\",\"cal\")"
# root -b -q -l "run_detectEfficiency.C+($runNum,$numEvts,\"shms\",\"aero\")"
