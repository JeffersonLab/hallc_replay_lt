#!/bin/bash

echo "Starting Replay script"
echo "I take as arguments the Run Number and max number of events!"
RUNNUMBER=$1
MAXEVENTS=50000
# MAXEVENTS=-1
### Check you've provided the an argument
if [[ $1 -eq "" ]]; then
    echo "I need a Run Number!"
    echo "Please provide a run number as input"
    exit 2
fi
if [[ ${USER} = "cdaq" ]]; then
    echo "Warning, running as cdaq."
    echo "Please be sure you want to do this."
    echo "Comment this section out and run again if you're sure."
    exit 2
fi          

# Set path depending upon hostname. Change or add more as needed  
if [[ "${HOSTNAME}" = *"farm"* ]]; then  
    REPLAYPATH="/group/c-kaonlt/USERS/${USER}/hallc_replay_lt"
    if [[ "${HOSTNAME}" != *"ifarm"* ]]; then
	source /site/12gev_phys/softenv.sh 2.3
    fi
    cd "/group/c-kaonlt/hcana/"
    source "/group/c-kaonlt/hcana/setup.sh"
    cd "$REPLAYPATH"
    source "$REPLAYPATH/setup.sh"
elif [[ "${HOSTNAME}" = *"qcd"* ]]; then
    REPLAYPATH="/group/c-kaonlt/USERS/${USER}/hallc_replay_lt"
    source /site/12gev_phys/softenv.sh 2.3
    cd "/group/c-kaonlt/hcana/"
    source "/group/c-kaonlt/hcana/setup.sh" 
    cd "$REPLAYPATH"
    source "$REPLAYPATH/setup.sh" 
elif [[ "${HOSTNAME}" = *"cdaq"* ]]; then
    REPLAYPATH="/home/cdaq/hallc-online/hallc_replay_lt"
elif [[ "${HOSTNAME}" = *"phys.uregina.ca"* ]]; then
    REPLAYPATH="/home/${USER}/work/JLab/hallc_replay_lt"
fi
cd $REPLAYPATH

echo -e "\n\nStarting Scaler Replay Script\n\n"
./hcana -q "$REPLAYPATH/SCRIPTS/COIN/SCALERS/replay_coin_scalers.C($RUNNUMBER,$MAXEVENTS)"
cd CALIBRATION/bcm_current_map/

root -b<<EOF
.L ScalerCalib.C+
.x run.C("../../ROOTfiles/coin_replay_scalers_${RUNNUMBER}_$MAXEVENTS.root")
EOF

mv bcmcurrent_$RUNNUMBER.param ../../PARAM/HMS/BCM/CALIB/bcmcurrent_$RUNNUMBER.param
cd ../../

echo -e "\n\nStarting Replay Script\n\n"
eval "$REPLAYPATH/hcana -l -q \"SCRIPTS/COIN/PRODUCTION/FullReplay_Lumi_Offline.C ($RUNNUMBER,$MAXEVENTS)\"" | tee UTIL_KAONLT/REPORT_OUTPUT/COIN/PRODUCTION/Lumi_coin_replay_production_Offline_${RUNNUMBER}_${MAXEVENTS}.report

cd UTIL_KAONLT/scripts_Luminosity/

echo -e "\n\nStarting Lumi Analysis\n\n"
eval "$REPLAYPATH/UTIL_KAONLT/scripts_Luminosity/run_LumiScript.sh $RUNNUMBER"
exit 0
