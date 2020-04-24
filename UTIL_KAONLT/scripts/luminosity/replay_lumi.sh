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

# Set path depending upon hostname. Change or add more as needed  
if [[ "${HOSTNAME}" = *"farm"* ]]; then  
    REPLAYPATH="/group/c-kaonlt/USERS/${USER}/hallc_replay_lt"
    if [[ "${HOSTNAME}" != *"ifarm"* ]]; then
	source /site/12gev_phys/softenv.sh 2.1
    fi
    cd "/group/c-kaonlt/hcana/"
    source "/group/c-kaonlt/hcana/setup.sh"
    cd "$REPLAYPATH"
    source "$REPLAYPATH/setup.sh"
elif [[ "${HOSTNAME}" = *"qcd"* ]]; then
    REPLAYPATH="/group/c-kaonlt/USERS/${USER}/hallc_replay_lt"
    source /site/12gev_phys/softenv.sh 2.1
    cd "/group/c-kaonlt/hcana/"
    source "/group/c-kaonlt/hcana/setup.sh" 
    cd "$REPLAYPATH"
    source "$REPLAYPATH/setup.sh" 
elif [[ "${HOSTNAME}" = *"cdaq"* ]]; then
    REPLAYPATH="/home/cdaq/hallc-online/hallc_replay_lt"
elif [[ "${HOSTNAME}" = *"phys.uregina.ca"* ]]; then
    REPLAYPATH="/home/${USER}/work/JLab/hallc_replay_lt"
elif [[ "${HOSTNAME}" = *"trottar"* ]]; then
    REPLAYPATH="/home/trottar/Analysis/hallc_replay_lt"
fi

cd ${REPLAYPATH}/
#   Load params for BCM
#   const char* CurrentFileNamePattern = "PARAM/HMS/BCM/CALIB/bcmcurrent_%d.param";
#   gHcParms->Load(Form(CurrentFileNamePattern, RunNumber));
# When we comment out the below bit ONLY when the bit above is commented out in replay_luminosity_coin.C
echo -e "\n\nStarting Scaler Replay Script\n\n"
./hcana -q "${REPLAYPATH}/SCRIPTS/COIN/SCALERS/replay_coin_scalers.C($RUNNUMBER,$MAXEVENTS)"
cd CALIBRATION/bcm_current_map/
root -b<<EOF
.L ScalerCalib.C+
.x run.C("../../ROOTfiles/coin_replay_scalers_${RUNNUMBER}_${MAXEVENTS}.root")
EOF

mv bcmcurrent_$RUNNUMBER.param ../../PARAM/HMS/BCM/CALIB/bcmcurrent_$RUNNUMBER.param
cd ../../

echo -e "\n\nStarting Replay Script\n\n"
./hcana -q "${REPLAYPATH}/UTIL_KAONLT/scripts/luminosity/src/replay/replay_lumi_coin_offline.C($RUNNUMBER,$MAXEVENTS)"

source /apps/root/6.18.04/setroot_CUE.bash
cd ${REPLAYPATH}/UTIL_KAONLT/scripts/luminosity/src/
python3 lumiyield.py ${RUNNUMBER} ${MAXEVENTS}

cd ${REPLAYPATH}/UTIL_KAONLT/scripts/luminosity/src/
python3 csv2root.py "lumi_data"
