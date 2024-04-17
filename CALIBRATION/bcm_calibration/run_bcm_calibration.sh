#!/bin/bash

### Nathan Heinrich, University of Regina
### 2024/04/17
### heinricn@jlab.org

echo "Starting quick script"
bcm_cal_4.C("/d8tb3/heinricn/ROOTfiles/BCMcalib/coin_replay_scalers_16432_-1.root","16432_BCMcalib_onOffTimes",16432,"BCM1",false)
ROOTFILE=$1
RANGEFILE=$2
RUNNUMBER=$3

#check if files are provided
if [[ $1 -eq "" ]]; then
    echo "please enter full path to a scaler replay file!"
    exit 2
fi

#check if files are provided
if [[ $2 -eq "" ]]; then
    echo "please enter full path to a BCM calib file!"
    exit 2
fi

if [[ $3 -eq "" ]]; then
    MAXEVENTS=-1
else
    MAXEVENTS=$2
fi

#run through all the BCMs
echo "root -l -q \"bcm_cal_4.C($ROOTFILE,$RANGEFILE,$RUNNUMBER,\"BCM1\",\"TRUE\")\""

eval "root -l -q \"bcm_cal_4.C($ROOTFILE,$RANGEFILE,$RUNNUMBER,\"BCM1\",\"TRUE\")\"" 
eval "root -l -q \"bcm_cal_4.C($ROOTFILE,$RANGEFILE,$RUNNUMBER,\"BCM2\",\"TRUE\")\"" 
eval "root -l -q \"bcm_cal_4.C($ROOTFILE,$RANGEFILE,$RUNNUMBER,\"BCM4A\",\"TRUE\")\"" 
eval "root -l -q \"bcm_cal_4.C($ROOTFILE,$RANGEFILE,$RUNNUMBER,\"BCM4B\",\"TRUE\")\"" 
eval "root -l -q \"bcm_cal_4.C($ROOTFILE,$RANGEFILE,$RUNNUMBER,\"BCM4C\",\"TRUE\")\"" 

exit 0
