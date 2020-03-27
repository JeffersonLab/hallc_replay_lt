#! /usr/bin/python

#
# Description:
# ================================================================
# Time-stamp: "2020-03-27 10:32:33 trottar"
# ================================================================
#
# Author:  Richard L. Trotta III <trotta@cua.edu>
#
# Copyright (c) trottar
#

from ROOT import TChain, TProof, TSelector, TTree
import sys

RunNumber=sys.argv[1]
MaxEvent=sys.argv[2]
# MaxEvent=50000

report = "/u/group/c-kaonlt/USERS/trottar/hallc_replay_lt/UTIL_KAONLT/REPORT_OUTPUT/COIN/PRODUCTION/Lumi_coin_replay_production_Offline_%s_%s.report" % (RunNumber,MaxEvent)

f = open(report)
fout = open("/u/group/c-kaonlt/USERS/trottar/hallc_replay_lt/UTIL_KAONLT/scripts_Luminosity/Yield_Data.dat","a")

psList = ['Ps1_factor','Ps3_factor','Ps5_factor']

psActual = ['-1','1','2','3','5','9','17','33','65','129','257','513','1025','2049','4097','8193','16385','32769']

psValue = ['-1','0','1','2','3','4','5','6','7','8','9','10','11','12','13','14','15','16']

for line in f:
    data = line.split('=')
    for index, obj in enumerate(psList) :
        if (psList[index] in data[0]) : 
            if (index == 0) :  
                ps1_tmp = data[1].split(" ")
            if (index == 1) : 
                ps3_tmp = data[1].split(" ")
            if (index == 2) :
                ps5_tmp = data[1].split(" ")
ps1=float(ps1_tmp[1])
ps3=float(ps3_tmp[1])
ps5=float(ps5_tmp[1])
i=0
for index in psActual:
    if (float(index) == ps1) :
        PS1 = str(psValue[i])
    if (float(index) == ps3) :
        PS3 = str(psValue[i])
    if (float(index) == ps5) :
        PS5 = str(psValue[i])
    i=i+1
fout.write(RunNumber + " ")
f.close()
fout.close()

option = "%s.%s" % (PS1,PS3)

# proof = TProof.Open("workers=4")

ch = TChain("T")
ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_lt/UTIL_KAONLT/ROOTfiles/Lumi_coin_replay_production_Offline_%s_%s.root" % (RunNumber,MaxEvent))

sc = TChain("TSH")
sc.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_lt/UTIL_KAONLT/ROOTfiles/Lumi_coin_replay_production_Offline_%s_%s.root" % (RunNumber,MaxEvent))

# ch.SetProof()
# sc.SetProof()

ch.Process("/u/group/c-kaonlt/USERS/trottar/hallc_replay_lt/UTIL_KAONLT/scripts_Luminosity/LumiYield.C+",option)
sc.Process("/u/group/c-kaonlt/USERS/trottar/hallc_replay_lt/UTIL_KAONLT/scripts_Luminosity/Scalers.C+",option)

# proof.Close()
