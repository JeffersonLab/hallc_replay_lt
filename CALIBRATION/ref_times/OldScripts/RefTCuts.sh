#!/bin/bash

DEFAULTPREFIX="Full_coin_replay_Offline"
DEFAULTROOTDIR="ROOTfilesTmp"
ROOTPREFIX=${1:-$DEFAULTPREFIX}
RUNNUMBER=$2
MAXEVENTS=$3

if [[ -z "$1" ]]; then
    echo "I need a replay file prefix!"
    echo "Please provide a replay file prefix as input"
    echo "Default prefix is assumed as ${ROOTPREFIX}"
    exit 1
fi

if [[ $2 -eq "" ]]; then
    echo "I need a Run Number!"
    echo "Please provide a run number as input"
    exit 2
fi

if [[ $3 -eq "" ]]; then
    echo "I need a max number of events!"
    echo "Please provide a maximum number of events in the replay file as input"
    exit 3
fi

if [[ "${HOSTNAME}" = *"farm"* ]]; then  
    REPLAYPATH="/group/c-pionlt/USERS/${USER}/hallc_replay_lt"
elif [[ "${HOSTNAME}" = *"qcd"* ]]; then
    REPLAYPATH="/group/c-pionlt/USERS/${USER}/hallc_replay_lt"
elif [[ "${HOSTNAME}" = *"cdaq"* ]]; then
    REPLAYPATH="/home/cdaq/hallc-online/hallc_replay_lt"
elif [[ "${HOSTNAME}" = *"phys.uregina.ca"* ]]; then
    REPLAYPATH="/home/${USER}/work/JLab/hallc_replay_lt"
fi

cd "$REPLAYPATH/CALIBRATION/ref_times/"

# Check directories exist, make if not
if [ ! -d "$REPLAYPATH/CALIBRATION/ref_times/HMS/Hodo" ]; then
    mkdir "$REPLAYPATH/CALIBRATION/ref_times/HMS/Hodo"
fi
if [ ! -d "$REPLAYPATH/CALIBRATION/ref_times/SHMS/Hodo" ]; then
    mkdir "$REPLAYPATH/CALIBRATION/ref_times/SHMS/Hodo"
fi
if [ ! -d "$REPLAYPATH/CALIBRATION/ref_times/Plots" ]; then
    mkdir "$REPLAYPATH/CALIBRATION/ref_times/Plots"
fi
if [ ! -d "$REPLAYPATH/CALIBRATION/ref_times/Rootfiles" ]; then
    mkdir "$REPLAYPATH/CALIBRATION/ref_times/Rootfiles"
fi

root -b <<EOF
.x run_RefT_Cuts.C("$ROOTPREFIX", $RUNNUMBER, $MAXEVENTS)
.q
EOF
sleep 1

if [ -f "$REPLAYPATH/CALIBRATION/ref_times/RefTimeHistos_Run${RUNNUMBER}.root" ]; then
    mv "$REPLAYPATH/CALIBRATION/ref_times/RefTimeHistos_Run${RUNNUMBER}.root" "$REPLAYPATH/CALIBRATION/ref_times/Rootfiles/RefTimeHistos_Run${RUNNUMBER}.root"
fi

if [ -f "$REPLAYPATH/CALIBRATION/ref_times/HMS_Hodo_AdcTdc_Offset_${RUNNUMBER}.param" ]; then
    if [ "$RUNNUMBER" -le "5334" ]; then
	cp "$REPLAYPATH/PARAM/HMS/HODO/hhodo_cuts_Autumn18.param" "$REPLAYPATH/CALIBRATION/ref_times/HMS/Hodo/hhodo_cuts_${RUNNUMBER}.param"
    elif [ "$RUNNUMBER" -ge "5335" -a "$RUNNUMBER" -le "7045" ]; then 
	cp "$REPLAYPATH/PARAM/HMS/HODO/hhodo_cuts_Winter18.param" "$REPLAYPATH/CALIBRATION/ref_times/HMS/Hodo/hhodo_cuts_${RUNNUMBER}.param"
    elif [ "$RUNNUMBER" -ge "7046" -a "$RUNNUMBER" -le "8375" ]; then 
	cp "$REPLAYPATH/PARAM/HMS/HODO/hhodo_cuts_Spring19.param" "$REPLAYPATH/CALIBRATION/ref_times/HMS/Hodo/hhodo_cuts_${RUNNUMBER}.param"
    elif [ "$RUNNUMBER" -ge "8376" ]; then 
	cp "$REPLAYPATH/PARAM/HMS/HODO/hhodo_cuts_Summer19.param" "$REPLAYPATH/CALIBRATION/ref_times/HMS/Hodo/hhodo_cuts_${RUNNUMBER}.param"
    fi
    mv "$REPLAYPATH/CALIBRATION/ref_times/HMS_Hodo_AdcTdc_Offset_${RUNNUMBER}.param" "$REPLAYPATH/CALIBRATION/ref_times/HMS/Hodo/HMS_Hodo_AdcTdc_Offset_${RUNNUMBER}.param"
    # Copy new offset values from file, replace old values in cuts param file
    HMSNewOffset=$(sed -n '2p' "$REPLAYPATH/CALIBRATION/ref_times/HMS/Hodo/HMS_Hodo_AdcTdc_Offset_${RUNNUMBER}.param")
    sed -i "s/.*hhodo_adc_tdc_offset.*/${HMSNewOffset}/" "$REPLAYPATH/CALIBRATION/ref_times/HMS/Hodo/hhodo_cuts_${RUNNUMBER}.param"
    rm -rf "$REPLAYPATH/CALIBRATION/ref_times/HMS/Hodo/HMS_Hodo_AdcTdc_Offset_${RUNNUMBER}.param"
fi

if [ -f "$REPLAYPATH/CALIBRATION/ref_times/SHMS_Hodo_AdcTdc_Offset_${RUNNUMBER}.param" ]; then
    if [ "$RUNNUMBER" -le "5334" ]; then
	cp "$REPLAYPATH/PARAM/SHMS/HODO/phodo_cuts_Autumn18.param" "$REPLAYPATH/CALIBRATION/ref_times/SHMS/Hodo/phodo_cuts_${RUNNUMBER}.param"
    elif [ "$RUNNUMBER" -ge "5335" -a "$RUNNUMBER" -le "7045" ]; then 
	cp "$REPLAYPATH/PARAM/SHMS/HODO/phodo_cuts_Winter18.param" "$REPLAYPATH/CALIBRATION/ref_times/SHMS/Hodo/phodo_cuts_${RUNNUMBER}.param"
    elif [ "$RUNNUMBER" -ge "7046" -a "$RUNNUMBER" -le "8375" ]; then 
	cp "$REPLAYPATH/PARAM/SHMS/HODO/phodo_cuts_Spring19.param" "$REPLAYPATH/CALIBRATION/ref_times/SHMS/Hodo/phodo_cuts_${RUNNUMBER}.param"
    elif [ "$RUNNUMBER" -ge "8376" ]; then 
	cp "$REPLAYPATH/PARAM/SHMS/HODO/phodo_cuts_Summer19.param" "$REPLAYPATH/CALIBRATION/ref_times/SHMS/Hodo/phodo_cuts_${RUNNUMBER}.param"
    fi
    mv "$REPLAYPATH/CALIBRATION/ref_times/SHMS_Hodo_AdcTdc_Offset_${RUNNUMBER}.param" "$REPLAYPATH/CALIBRATION/ref_times/SHMS/Hodo/SHMS_Hodo_AdcTdc_Offset_${RUNNUMBER}.param"
    SHMSNewOffset=$(sed -n '2p' "$REPLAYPATH/CALIBRATION/ref_times/SHMS/Hodo/SHMS_Hodo_AdcTdc_Offset_${RUNNUMBER}.param")
    sed -i "s/.*phodo_adc_tdc_offset.*/${SHMSNewOffset}/" "$REPLAYPATH/CALIBRATION/ref_times/SHMS/Hodo/phodo_cuts_${RUNNUMBER}.param"
    rm -rf "$REPLAYPATH/CALIBRATION/ref_times/SHMS/Hodo/SHMS_Hodo_AdcTdc_Offset_${RUNNUMBER}.param"
fi

exit 0 
