#!/bin/bash

echo "Starting Luminosity Script"
echo "I take as arguments the Run Number and max number of events!"
RUNNUMBER=$1
MAXEVENTS=$2
# MAXEVENTS=50000

if [[ $1 -eq "" ]]; then
    echo "I need a Run Number!"
    exit 2
fi

if [[ $2 -eq "" ]]; then
    echo "Only Run Number entered...I'll assume -1 events!" 
    MAXEVENTS=-1 
fi

cd /group/c-kaonlt/USERS/${USER}/hallc_replay_lt/UTIL_KAONLT/scripts/luminosity/src/
python3 lumiyield.py ${RUNNUMBER} ${MAXEVENTS}
