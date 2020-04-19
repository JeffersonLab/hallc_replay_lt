#!/bin/bash

echo "Starting Particle ID Script"
echo "I take as arguments the Run Number and max number of events!"
RUNNUMBER=$1
# MAXEVENTS=$2
MAXEVENTS=50000

if [[ $1 -eq "" ]]; then
    echo "I need a Run Number!"
    exit 2
fi

# if [[ $2 -eq "" ]]; then
#     echo "Only Run Number entered...I'll assume -1 events!" 
#     MAXEVENTS=-1 
# fi

cd /group/c-kaonlt/USERS/${USER}/hallc_replay_lt/UTIL_KAONLT/scripts/pid/src/
python3 pid_eff.py ${RUNNUMBER} ${MAXEVENTS}

cd /group/c-kaonlt/USERS/${USER}/hallc_replay_lt/UTIL_KAONLT/scripts/pid/OUTPUTS/
convert noID_hms_cer_${RUNNUMBER}.png PID_hms_cer_${RUNNUMBER}.png noID_hms_cal_${RUNNUMBER}.png PID_hms_cal_${RUNNUMBER}.png noID_shms_hgcer_${RUNNUMBER}.png PID_shms_hgcer_${RUNNUMBER}.png noID_shms_aero_${RUNNUMBER}.png PID_shms_aero_${RUNNUMBER}.png noID_shms_cal_${RUNNUMBER}.png PID_shms_cal_${RUNNUMBER}.png pid_plots_${RUNNUMBER}.pdf
rm -rf *.png
