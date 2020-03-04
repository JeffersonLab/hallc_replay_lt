#!/bin/bash

echo "Starting ADC Timing Window Calculation"
echo "I take as arguments the Run Number and max number of events!"
RUNNUMBER=$1
MAXEVENTS=$2
if [[ $1 -eq "" ]]; then
    echo "I need a Run Number!"
    exit 2
fi
if [[ $2 -eq "" ]]; then
    echo "Only Run Number entered...I'll assume -1 events!" 
    MAXEVENTS=-1  
fi
cd ../
echo -e "\n\nStarting Replay Script\n\n"
./hcana -q "UTIL_KAONLT/scripts_Replay/replay_ADC_HMS.C($RUNNUMBER,$MAXEVENTS)"
cd UTIL_KAONLT/ADCGates/
echo -e "\n\nADC Window Calculation\n\n"
root -l "run_HMSADCGates.C($RUNNUMBER,$MAXEVENTS)"

