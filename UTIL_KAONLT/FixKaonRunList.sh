#!/bin/bash

echo "Starting Kaon Yield Estimation"
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
cd scripts_KaonYield/
echo -e "\n\nYield Calculation\n\n"
root -l "run_KaonYield.C($RUNNUMBER,$MAXEVENTS,5,1)"
cd ../
python reportSummary.py $RUNNUMBER $MAXEVENTS
emacs output.txt
mv output.txt OUTPUT/scalers_Run$RUNNUMBER.txt
if [[ -e "OUTPUT/scalers_Run$RUNNUMBER.txt" ]]; then
    while true; do
	read -p "Would you like to update the run list as well? (Please answer yes or no) " yn
	case $yn in
            [Yy]* ) break;;
            [Nn]* ) exit;;
            * ) echo "Please answer yes or no.";;
	esac
    done

    read -p "What type of production was this run? (e.g. Prod, Heep, ect.)" runType
    read -p "What was the target? (Dummy, LH2 ..?)" target
    
    fillrunList="./fill_runList $RUNNUMBER $runType $target"
    
    eval ${fillrunList}
    
fi
