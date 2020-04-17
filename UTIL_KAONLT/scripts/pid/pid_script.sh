#!/bin/bash

echo "Starting Particle ID Script"
echo "I take as arguments the Run Number and max number of events!"
RUNNUMBER=$1
MAXEVENTS=$2
# MAXEVENTS=50000

cd /group/c-kaonlt/USERS/${USER}/hallc_replay_lt/UTIL_KAONLT/scripts/pid/src/
python3 pid_eff.py ${RUNNUMBER} ${MAXEVENTS}
