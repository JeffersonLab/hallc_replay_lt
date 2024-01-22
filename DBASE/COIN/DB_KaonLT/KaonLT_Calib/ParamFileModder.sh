#!/bin/bash

### Stephen Kay --- University of Regina --- 15/11/19 ###
### Lazy boy script to go through and modify the parameter files that will be examined ###
### Reads in a list of run numbers from a text file ###
inputFile="$1"

if [[ "${HOSTNAME}" = *"farm"* ]]; then  
    REPLAYPATH="/group/c-pionlt/USERS/${USER}/hallc_replay_lt"
elif [[ "${HOSTNAME}" = *"qcd"* ]]; then
    REPLAYPATH="/group/c-pionlt/USERS/${USER}/hallc_replay_lt"
elif [[ "${HOSTNAME}" = *"cdaq"* ]]; then
    REPLAYPATH="/home/cdaq/hallc-online/hallc_replay_lt"
elif [[ "${HOSTNAME}" = *"phys.uregina.ca"* ]]; then
    REPLAYPATH="/home/${USER}/work/JLab/hallc_replay_lt"
fi

while IFS='' read -r line || [[ -n "$line" ]]; do
    #Run number#
    runNum=$line
    if [ -f "$REPLAYPATH/PARAM/HMS/HODO/Calibration/hhodo_cuts_$runNum.param" ]; then
	sed -i "s/hhodo_cuts_Autumn18.param/Calibration\/hhodo_cuts_$runNum.param/" "Offline"$runNum".param"
	sed -i "s/hhodo_cuts_Winter18.param/Calibration\/hhodo_cuts_$runNum.param/" "Offline"$runNum".param"
	sed -i "s/hhodo_cuts_Spring19.param/Calibration\/hhodo_cuts_$runNum.param/" "Offline"$runNum".param"
	sed -i "s/hhodo_cuts_Summer19.param/Calibration\/hhodo_cuts_$runNum.param/" "Offline"$runNum".param"
    fi

    if [ -f "$REPLAYPATH/PARAM/SHMS/HODO/Calibration/phodo_cuts_$runNum.param" ]; then
	sed -i "s/phodo_cuts_Autumn18.param/Calibration\/phodo_cuts_$runNum.param/" "Offline"$runNum".param"
	sed -i "s/phodo_cuts_Winter18.param/Calibration\/phodo_cuts_$runNum.param/" "Offline"$runNum".param"
	sed -i "s/phodo_cuts_Spring19.param/Calibration\/phodo_cuts_$runNum.param/" "Offline"$runNum".param"
	sed -i "s/phodo_cuts_Summer19.param/Calibration\/phodo_cuts_$runNum.param/" "Offline"$runNum".param"
    fi

done < "$inputFile"
