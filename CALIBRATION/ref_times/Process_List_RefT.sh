#!/bin/bash

### Stephen Kay --- University of Regina --- 23/07/20 ###
### Reads in a list of run numbers from a text file and processes the detector ref time script for them ###
inputFile="$1"
DEFAULTPREFIX="Full_coin_replay_Offline"
DEFAULTROOTDIR="ROOTfiles"
PREFIX=${2:-$DEFAULTPREFIX}
ROOTDIR=${3:-$DEFAULTROOTDIR}
## Assume a default if not set
if [[ $2 -eq "" ]]; then
    echo "File prefix not specified"
    echo "Assuming ${PREFIX} as rootfile prefix"
fi
if [[ $3 -eq "" ]]; then
    echo "Rootfile directory not specified"
    echo "Assuming ${ROOTDIR} as rootfile directory"
fi

# Set path depending upon hostname. Change or add more as needed  
if [[ "${HOSTNAME}" = *"farm"* ]]; then  
    REPLAYPATH="/group/c-kaonlt/USERS/${USER}/hallc_replay_lt"
    cd "$REPLAYPATH"
    source "$REPLAYPATH/setup.sh"
elif [[ "${HOSTNAME}" = *"qcd"* ]]; then
    REPLAYPATH="/group/c-kaonlt/USERS/${USER}/hallc_replay_lt"
    cd "$REPLAYPATH"
    source "$REPLAYPATH/setup.sh" 
elif [[ "${HOSTNAME}" = *"cdaq"* ]]; then
    REPLAYPATH="/home/cdaq/hallc-online/hallc_replay_lt"
elif [[ "${HOSTNAME}" = *"phys.uregina.ca"* ]]; then
    REPLAYPATH="/home/${USER}/work/JLab/hallc_replay_lt"
fi

cd "$REPLAYPATH/CALIBRATION/ref_times"

while IFS='' read -r line || [[ -n "$line" ]]; do
    runNum=$line
    if [ -f "$REPLAYPATH/ROOTfiles/Calib/Timing/Full_coin_replay_Offline_${runNum}_-1.root" ]; then
	eval "${REPLAYPATH}/CALIBRATION/ref_times/RefTCuts.sh ${PREFIX} ${runNum} -1"
    elif [ ! -f "$REPLAYPATH/ROOTfiles/Calib/Timing/Full_coin_replay_Offline_${runNum}_-1.root" ]; then
	echo "$REPLAYPATH/ROOTfiles/Full_coin_replay_Offline_${runNum}_-1.root not found, skipping"
	if [ ! -f "$REPLAYPATH/CALIBRATION/ref_times/Skipped_Runs_${inputFile}" ]; then
	    echo "runNum" > "$REPLAYPATH/CALIBRATION/ref_times/Skipped_Runs"
	elif [ -f "$REPLAYPATH/CALIBRATION/ref_times/Skipped_Runs_${inputFile}" ]; then
	    echo "runNum" >> "$REPLAYPATH/CALIBRATION/ref_times/Skipped_Runs"
	fi
    fi
    sleep 1
done < "$inputFile"
