#!/bin/bash

# 26/05/20 - Stephen Kay, University of Regina

echo "Starting analysis of Q2 = 2.115, W = 2.95, central angle, high espilon setting"

# Set path depending upon hostname. Change or add more as needed  
if [[ "${HOSTNAME}" = *"farm"* ]]; then  
    REPLAYPATH="/group/c-kaonlt/USERS/${USER}/hallc_replay_lt"
    if [[ "${HOSTNAME}" != *"ifarm"* ]]; then
	source /site/12gev_phys/softenv.sh 2.3
    fi
    cd "$REPLAYPATH"
    source "$REPLAYPATH/setup.sh"
elif [[ "${HOSTNAME}" = *"qcd"* ]]; then
    REPLAYPATH="/group/c-kaonlt/USERS/${USER}/hallc_replay_lt"
    source /site/12gev_phys/softenv.sh 2.3
    cd "$REPLAYPATH"
    source "$REPLAYPATH/setup.sh" 
elif [[ "${HOSTNAME}" = *"cdaq"* ]]; then
    REPLAYPATH="/home/cdaq/hallc-online/hallc_replay_lt"
elif [[ "${HOSTNAME}" = *"phys.uregina.ca"* ]]; then
    REPLAYPATH="/home/${USER}/work/JLab/hallc_replay_lt"
fi
UTILPATH="${REPLAYPATH}/UTIL_KAONLT"
SCRIPTPATH="${REPLAYPATH}/UTIL_KAONLT/scripts/kaonyield/Analyse_Kaons.sh"
RunListFile="${UTILPATH}/scripts/kaonyield/kinematics/Q2p115W2p95center_highe"
while IFS='' read -r line || [[ -n "$line" ]]; do
    runNum=$line
    RootName+="${runNum}_-1_Analysed_Data.root "
    eval '"$SCRIPTPATH" $runNum -1'
done < "$RunListFile"
sleep 5
cd "${UTILPATH}/scripts/kaonyield/OUTPUT"
KINFILE="Q2p115W2p95center_highe.root"
hadd ${KINFILE} ${RootName}

if [ ! -f "${UTILPATH}/scripts/kaonyield/OUTPUT/Q2p115W2p95center_highe_Kaons.root" ]; then
    root -b -l -q "${UTILPATH}/scripts/kaonyield/PlotKaonPhysics.C(\"${KINFILE}\", \"Q2p115W2p95center_highe_Kaons\")"
elif [ ! -f "${UTILPATH}/scripts/kaonyield/OUTPUT/Q2p115W2p95center_highe_Kaons.pdf" ]; then
    root -b -l -q "${UTILPATH}/scripts/kaonyield/PlotKaonPhysics.C(\"${KINFILE}\", \"Q2p115W2p95center_highe_Kaons\")"
else echo "Kaon plots already found in - ${UTILPATH}/scripts/kaonyield/OUTPUT/Q2p115W2p95center_highe_Kaons.root and .pdf - Plotting macro skipped"
fi
exit 0
