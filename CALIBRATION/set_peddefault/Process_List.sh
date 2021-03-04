#!/bin/bash

### Stephen Kay --- University of Regina --- 06/07/20 ###
### Reads in a list of run numbers from a text file and processes ped default script for them ###
inputFile="$1"
# Set path depending upon hostname. Change or add more as needed  
if [[ "${HOSTNAME}" = *"farm"* ]]; then  
    REPLAYPATH="/group/c-pionlt/USERS/${USER}/hallc_replay_lt"
    cd "$REPLAYPATH"
    source "$REPLAYPATH/setup.sh"
elif [[ "${HOSTNAME}" = *"qcd"* ]]; then
    REPLAYPATH="/group/c-pionlt/USERS/${USER}/hallc_replay_lt"
    cd "$REPLAYPATH"
    source "$REPLAYPATH/setup.sh" 
elif [[ "${HOSTNAME}" = *"cdaq"* ]]; then
    REPLAYPATH="/home/cdaq/hallc-online/hallc_replay_lt"
elif [[ "${HOSTNAME}" = *"phys.uregina.ca"* ]]; then
    REPLAYPATH="/home/${USER}/work/JLab/hallc_replay_lt"
fi

cd "$REPLAYPATH/CALIBRATION/set_peddefault"

while IFS='' read -r line || [[ -n "$line" ]]; do
    runNum=$line
    if [ -f "$REPLAYPATH/ROOTfiles/Calib/General/Full_coin_replay_Offline_${runNum}_-1.root" ]; then
	eval "${REPLAYPATH}/CALIBRATION/set_peddefault/SetPedDef.sh ${runNum}"
    elif [ -f ! "$REPLAYPATH/ROOTfiles/Calib/General/Full_coin_replay_Offline_${runNum}_-1.root" ]; then
	echo "$REPLAYPATH/ROOTfiles/Calib/General/Full_coin_replay_Offline_${runNum}_-1.root not found, skipping"
	if [ -f ! "$REPLAYPATH/CALIBRATION/set_peddefault/Skipped_Runs_${inputFile}" ]; then
	    echo "runNum" > "$REPLAYPATH/CALIBRATION/set_peddefault/Skipped_Runs"
	elif [ -f "$REPLAYPATH/CALIBRATION/set_peddefault/Skipped_Runs_${inputFile}" ]; then
	    echo "runNum" >> "$REPLAYPATH/CALIBRATION/set_peddefault/Skipped_Runs"
	fi
    fi
done < "$inputFile"
