#!/bin/bash

### Stephen Kay --- University of Regina --- 19/08/20 ###
### Replace hodoscope cut param file with one used for other detector ###
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
    HMSHodCutFile=$(sed -n 34p "Offline"$runNum".param")
    HMSCalCutFile=$(sed -n 36p "Offline"$runNum".param")
    SHMSCalCutFile=$(sed -n 70p "Offline"$runNum".param")
    SHMSHodCutFile=$(sed -n 67p "Offline"$runNum".param")
    
    HMSCalCutRunNo=$((${HMSCalCutFile:40:4}))
    HMSHodCutRunNo=$((${HMSHodCutFile:48:4}))
    SHMSCalCutRunNo=$((${SHMSCalCutFile:41:4}))
    SHMSHodCutRunNo=$((${SHMSHodCutFile:49:4}))
    
    if [ $HMSCalCutRunNo != $HMSHodCutRunNo ]; then
       sed -i "s/hhodo_cuts_${HMSHodCutRunNo}/hhodo_cuts_${HMSCalCutRunNo}/" "Offline"$runNum".param"
    fi
    if [ $SHMSCalCutRunNo != $SHMSHodCutRunNo ]; then 
       sed -i "s/phodo_cuts_${SHMSHodCutRunNo}/phodo_cuts_${SHMSCalCutRunNo}/" "Offline"$runNum".param"
    fi

done < "$inputFile"
