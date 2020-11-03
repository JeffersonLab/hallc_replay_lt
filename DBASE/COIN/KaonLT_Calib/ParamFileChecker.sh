#!/bin/bash

### Stephen Kay --- University of Regina --- 19/08/20 ###
### Check list of runs for discrepancies, cut param file names should all be the same length ###
### Would expect that Cal/Hod use same cut file too ###
### Reads in a list of run numbers from a text file ###
inputFile="$1"

if [[ "${HOSTNAME}" = *"farm"* ]]; then  
    REPLAYPATH="/group/c-kaonlt/USERS/${USER}/hallc_replay_lt"
elif [[ "${HOSTNAME}" = *"qcd"* ]]; then
    REPLAYPATH="/group/c-kaonlt/USERS/${USER}/hallc_replay_lt"
elif [[ "${HOSTNAME}" = *"cdaq"* ]]; then
    REPLAYPATH="/home/cdaq/hallc-online/hallc_replay_lt"
elif [[ "${HOSTNAME}" = *"phys.uregina.ca"* ]]; then
    REPLAYPATH="/home/${USER}/work/JLab/hallc_replay_lt"
fi

while IFS='' read -r line || [[ -n "$line" ]]; do
    #Run number#
    declare -i TestingVar=1
    runNum=$line
    HMSHodCutFile=$(sed -n 34p "Offline"$runNum".param")
    HMSCalCutFile=$(sed -n 36p "Offline"$runNum".param")
    SHMSCalCutFile=$(sed -n 70p "Offline"$runNum".param")
    SHMSHodCutFile=$(sed -n 67p "Offline"$runNum".param")
    
    if [ "${#HMSCalCutFile}" == 51 ]; then
	HMSCalCutRunNo=$((${HMSCalCutFile:40:4}))
    elif [ "${#HMSCalCutFile}" != 51 ]; then
	echo "$runNum HMS Cal" >> "Unmodified_files.txt"
    fi
    if [ "${#HMSHodCutFile}" == 59 ]; then
	HMSHodCutRunNo=$((${HMSHodCutFile:48:4}))
    elif [ "${#HMSHodCutFile}" != 59 ]; then
	echo "$runNum HMS Hod" >> "Unmodified_files.txt"
    fi
    if [ "${#SHMSCalCutFile}" == 52 ]; then
	SHMSCalCutRunNo=$((${SHMSCalCutFile:41:4}))
    elif [ "${#SHMSCalCutFile}" != 52 ]; then
	echo "$runNum SHMS Cal" >> "Unmodified_files.txt"
    fi
    if [ "${#SHMSHodCutFile}" == 60 ]; then
	SHMSHodCutRunNo=$((${SHMSHodCutFile:49:4}))
    elif [ "${#SHMSHodCutFile}" != 60 ]; then
	echo "$runNum SHMS Hod" >> "Unmodified_files.txt"    
    fi
    
    if [ $HMSCalCutRunNo != $HMSHodCutRunNo ]; then
       TestingVar=$((TestingVar+1))
    fi
    if [ $SHMSCalCutRunNo != $SHMSHodCutRunNo ]; then
       TestingVar=$((TestingVar+1))
    fi
    if [ $TestingVar != 1 ]; then
	echo $runNum >> "Differing_Runs.txt"
    fi

done < "$inputFile"
