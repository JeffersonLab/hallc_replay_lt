#!/bin/bash

#user input
runNum=$1    # run number
evtNum=$2    # event number
replay=$3

if [ -z "$1" ] || [ -z "$2" ]; then             
    echo ""                                                                                                                             
    echo ":=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:"                                                                              
    echo ""                                                                                                                                
    echo "Usage:  ./set_timewin.sh <run_number> <evt_number>"                                                
    echo ""                                                                                                        
    echo ":=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:"    
    
    exit 0        
fi

daq_mode="coin"
set_refTimes=0
debug=1
  
# Which analysis file type are we doing? 
ana_type="timewin"

# this rootfile name pattern assumes pattern defined in replay_cafe.C script (please do NOT modify replay script) 
filename="../../ROOTfiles/${ana_type}/cafe_replay_${ana_type}_${runNum}_${evtNum}.root"

replay_script="SCRIPTS/COIN/PRODUCTION/replay_cafe.C"
analysis_script="scripts/set_reftimes.C"

runHcana="./hcana -q \"${replay_script}(${runNum}, ${evtNum}, \\\"${ana_type}\\\")\""
runAna="root -l -q -b \"${analysis_script}(\\\"${filename}\\\", ${runNum}, \\\"${daq_mode}\\\", ${set_refTimes}, ${debug})\""   

# change to top direcotry and run analyzer to produce specified ROOTfile
if [ "${replay}" == "replay" ]; then
    cd ../../
    eval $runHcana
    # change back to original directory and execute analysis script
    cd CALIBRATION/set_reftimes
    eval $runAna
else
    eval $runAna 
fi
