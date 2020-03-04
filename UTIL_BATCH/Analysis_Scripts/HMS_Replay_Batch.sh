#!/bin/bash

echo "Starting Replay script"
echo "I take as arguments the Run Number and max number of events!"
RUNNUMBER=$1
MAXEVENTS=-1
# MAXEVENTS=50000
if [[ $1 -eq "" ]]; then
    echo "I need a Run Number!"
    exit 2
fi

#Initialize enviroment
source /site/12gev_phys/softenv.sh 2.1

#Initialize hcana
cd "/group/c-kaonlt/hcana"
source "/group/c-kaonlt/hcana/setup.sh"
cd "/group/c-kaonlt/USERS/sjdkay/hallc_replay_lt"
source "/group/c-kaonlt/USERS/sjdkay/hallc_replay_lt/setup.sh"

echo -e "\n\nStarting Replay Script\n\n"
eval "/group/c-kaonlt/USERS/sjdkay/hallc_replay_lt/hcana -l -q \"SCRIPTS/HMS/PRODUCTION/replay_production_hms_coin_all_DC_Calib.C($RUNNUMBER,$MAXEVENTS)\""                                                            
