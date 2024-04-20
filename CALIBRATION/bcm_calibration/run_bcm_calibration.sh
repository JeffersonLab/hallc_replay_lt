#!/bin/bash

### Nathan Heinrich, University of Regina
### 2024/04/17
### heinricn@jlab.org

echo "Starting quick script"
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

#check if files are provided
if [[ $3 -eq "" ]]; then
    echo "please enter run number"
    exit 2
fi


#run through all the BCMs
echo "root -l -q \"bcm_cal_4.C(\"$ROOTFILE\",\"$RANGEFILE\",$RUNNUMBER,\"BCM1\",1)\"" 

root -l -q  "bcm_cal_4.C(\"$ROOTFILE\",\"$RANGEFILE\",$RUNNUMBER,\"BCM1\",1)"
root -l -q  "bcm_cal_4.C(\"$ROOTFILE\",\"$RANGEFILE\",$RUNNUMBER,\"BCM2\",1)"
root -l -q  "bcm_cal_4.C(\"$ROOTFILE\",\"$RANGEFILE\",$RUNNUMBER,\"BCM4A\",1)"
root -l -q  "bcm_cal_4.C(\"$ROOTFILE\",\"$RANGEFILE\",$RUNNUMBER,\"BCM4B\",1)"
root -l -q  "bcm_cal_4.C(\"$ROOTFILE\",\"$RANGEFILE\",$RUNNUMBER,\"BCM4C\",1)"

exit 0
