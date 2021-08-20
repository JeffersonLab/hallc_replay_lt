#!/bin/bash

DEFAULTPREFIX="Full_coin_replay_Offline"
DEFAULTROOTDIR="ROOTfiles"
ROOTPREFIX=${1:-$DEFAULTPREFIX}
RUNNUMBER=$2
MAXEVENTS=$3

if [[ -z "$1" ]]; then
    echo "I need a replay file prefix!"
    echo "Please provide a replay file prefix as input"
    echo "Default prefix is assumed as ${ROOTPREFIX}"
    exit 1
fi

if [[ $2 -eq "" ]]; then
    echo "I need a Run Number!"
    echo "Please provide a run number as input"
    exit 2
fi

if [[ $3 -eq "" ]]; then
    echo "I need a max number of events!"
    echo "Please provide a maximum number of events in the replay file as input"
    exit 3
fi

if [[ "${HOSTNAME}" = *"farm"* ]]; then  
    REPLAYPATH="/group/c-pionlt/USERS/${USER}/hallc_replay_lt"
elif [[ "${HOSTNAME}" = *"qcd"* ]]; then
    REPLAYPATH="/group/c-pionlt/USERS/${USER}/hallc_replay_lt"
elif [[ "${HOSTNAME}" = *"cdaq"* ]]; then
    REPLAYPATH="/home/cdaq/hallc-online/hallc_replay_lt"
elif [[ "${HOSTNAME}" = *"phys.uregina.ca"* ]]; then
    REPLAYPATH="/home/${USER}/work/JLab/hallc_replay_lt"
fi

cd "$REPLAYPATH/CALIBRATION/ref_times/"

if [ ! -d "$REPLAYPATH/CALIBRATION/ref_times/Plots" ]; then
    mkdir "$REPLAYPATH/CALIBRATION/ref_times/Plots"
fi
if [ ! -d "$REPLAYPATH/CALIBRATION/ref_times/Rootfiles" ]; then
    mkdir "$REPLAYPATH/CALIBRATION/ref_times/Rootfiles"
fi

root -b << EOF
.x run_DetTCuts.C("$ROOTPREFIX", $RUNNUMBER, $MAXEVENTS)
.q 
EOF
sleep 1
mv "TimeWindowHistos_Coin_Run$RUNNUMBER.root" "Rootfiles/TimeWindowHistos_Coin_Run$RUNNUMBER.root"
mv "TimeWindowPlots_Coin_Run$RUNNUMBER.pdf" "Plots/TimeWindowPlots_Coin_Run$RUNNUMBER.pdf"
mv "SHMSHGC_xyPlots_Coin_Run$RUNNUMBER.pdf" "Plots/SHMSHGC_xyPlots_Coin_Run$RUNNUMBER.pdf"

exit 0 
