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

cd /group/c-kaonlt/USERS/${USER}/hallc_replay_lt/
#   Load params for BCM
#   const char* CurrentFileNamePattern = "PARAM/HMS/BCM/CALIB/bcmcurrent_%d.param";
#   gHcParms->Load(Form(CurrentFileNamePattern, RunNumber));
# When we comment out the below bit ONLY when the bit above is commented out in replay_luminosity_coin.C
echo -e "\n\nStarting Scaler Replay Script\n\n"
./hcana -q "/group/c-kaonlt/USERS/${USER}/hallc_replay_lt/SCRIPTS/COIN/SCALERS/replay_coin_scalers.C($RUNNUMBER,$MAXEVENTS)"
cd CALIBRATION/bcm_current_map/
root -b<<EOF
.L ScalerCalib.C+
.x run.C("../../ROOTfiles/coin_replay_scalers_${RUNNUMBER}_${MAXEVENTS}.root")
EOF

mv bcmcurrent_$RUNNUMBER.param ../../PARAM/HMS/BCM/CALIB/bcmcurrent_$RUNNUMBER.param
cd ../../

echo -e "\n\nStarting Replay Script\n\n"
./hcana -q "/group/c-kaonlt/USERS/${USER}/hallc_replay_lt/UTIL_KAONLT/scripts/luminosity/src/replay/replay_lumi_coin_offline.C($RUNNUMBER,$MAXEVENTS)"

cd /group/c-kaonlt/USERS/${USER}/hallc_replay_lt/UTIL_KAONLT/scripts/luminosity/src/
python3 lumiyield.py ${RUNNUMBER} ${MAXEVENTS}
