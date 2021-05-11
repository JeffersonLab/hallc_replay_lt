#!/bin/bash

### Stephen JD Kay --- University of Regina --- 05/05/21 ###
### Reads in a csv param file containing CT peak positions and appends them to the end of standard.kinematics

echo "Adding CT Offset to standard.kinematics file"
echo "I take as arguments the Timing Parameter csv file and a standard.kinematics file"
CTInputFile="$1"
if [[ -z "$1" ]]; then
    echo "I need a Timing Parameters csv file to copy info from!"
    echo "Please provide a filename as an input"
    exit 1
fi
KinInputFile="$2"
if [[ -z "$2" ]]; then
    echo "I need a standard.kinematics file to modify!"
    echo "Please provide a filename as an input"
    exit 2
fi

if [[ "${HOSTNAME}" = *"farm"* ]]; then  
    REPLAYPATH="/group/c-kaonlt/USERS/${USER}/hallc_replay_lt"
elif [[ "${HOSTNAME}" = *"qcd"* ]]; then
    REPLAYPATH="/group/c-kaonlt/USERS/${USER}/hallc_replay_lt"
elif [[ "${HOSTNAME}" = *"cdaq"* ]]; then
    REPLAYPATH="/home/cdaq/hallc-online/hallc_replay_lt"
elif [[ "${HOSTNAME}" = *"phys.uregina.ca"* ]]; then
    REPLAYPATH="/home/${USER}/work/JLab/hallc_replay_lt"
fi

CTFile="${REPLAYPATH}/DBASE/COIN/CT_Offsets/${CTInputFile}"
KinFile="${REPLAYPATH}/DBASE/COIN/CT_Offsets/${KinInputFile}"

if [ ! -f "${CTFile}" ]; then
    echo "${CTFile} not found! Check the path to the file is correct and tweak as needed!"
    exit 3
fi

if [ ! -f "${KinFile}" ]; then
    echo "${KinFile} not found! Check the path to the file is correct and tweak as needed!"
    exit 3
fi

while IFS=',' read -r Run_Start Run_End Bunch_Spacing Coin_Offset nSkip nWindows Pion_Prompt_Peak Kaon_Prompt_Peak Proton_Prompt_Peak RF_Offset; do
    echo  >> ${KinFile}
    echo "${Run_Start}" >> ${KinFile}
    echo "eHadCoinTime_Offset = ${Pion_Prompt_Peak}" >> ${KinFile}
done <  <(tail -n +2 ${CTFile}) # Ignores header line by using tail here
