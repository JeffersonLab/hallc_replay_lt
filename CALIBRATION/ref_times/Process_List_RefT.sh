#!/bin/bash

### Stephen Kay --- University of Regina --- 23/07/20 ###
### Reads in a list of run numbers from a text file and processes ped default script for them ###
inputFile="$1"
DEFAULTPREFIX="Full_coin_replay_Offline"
DEFAULTROOTDIR="ROOTfilesMKJTest"
PREFIX=${2:-$DEFAULTPREFIX}
ROOTDIR=${3:-$DEFAULTROOTDIR}
## Assume a default if not set
if [[ $2 -eq "" ]]; then
    echo "File prefix not specified"
    echo "Assuming ${PREFIX} as rootfile prefix"
fi
if [[ $3 -eq "" ]]; then
    echo "File prefix not specified"
    echo "Assuming ${ROOTDIR} as rootfile prefix"
fi

# Set path depending upon hostname. Change or add more as needed  
if [[ "${HOSTNAME}" = *"farm"* ]]; then  
    REPLAYPATH="/group/c-kaonlt/USERS/${USER}/hallc_replay_lt"
    cd "$REPLAYPATH"
    source "$REPLAYPATH/setup.sh"
elif [[ "${HOSTNAME}" = *"qcd"* ]]; then
    REPLAYPATH="/group/c-kaonlt/USERS/${USER}/hallc_replay_lt"
    cd "$REPLAYPATH"
    source "$REPLAYPATH/setup.sh" 
elif [[ "${HOSTNAME}" = *"cdaq"* ]]; then
    REPLAYPATH="/home/cdaq/hallc-online/hallc_replay_lt"
elif [[ "${HOSTNAME}" = *"phys.uregina.ca"* ]]; then
    REPLAYPATH="/home/${USER}/work/JLab/hallc_replay_lt"
fi

cd "$REPLAYPATH/CALIBRATION/ref_times"

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

while IFS='' read -r line || [[ -n "$line" ]]; do
    runNum=$line
    if [ -f "$REPLAYPATH/${ROOTDIR}/${PREFIX}_${runNum}_-1.root" ]; then
	eval "${REPLAYPATH}/CALIBRATION/ref_times/RefTCuts.sh ${PREFIX} ${runNum} -1"
    elif [ -f ! "$REPLAYPATH/${ROOTDIR}/${PREFIX}_${runNum}_-1.root" ]; then
	echo "$REPLAYPATH/${ROOTDIR}/${PREFIX}_${runNum}_-1.root not found, skipping"
	if [ -f ! "$REPLAYPATH/CALIBRATION/ref_times/Skipped_Runs_${inputFile}" ]; then
	    echo "runNum" > "$REPLAYPATH/CALIBRATION/set_peddefault/Skipped_Runs"
	elif [ -f "$REPLAYPATH/CALIBRATION/ref_timest/Skipped_Runs_${inputFile}" ]; then
	    echo "runNum" >> "$REPLAYPATH/CALIBRATION/ref_times/Skipped_Runs"
	fi
    fi
    sleep 1
    if [ -f "$REPLAYPATH/CALIBRATION/ref_times/RefTimeHistos_Run${runNum}.root" ]; then
	mv "$REPLAYPATH/CALIBRATION/ref_times/RefTimeHistos_Run${runNum}.root" "$REPLAYPATH/CALIBRATION/ref_times/Rootfiles/RefTimeHistos_Run${runNum}.root"
    fi
    if [ -f "$REPLAYPATH/CALIBRATION/ref_times/HMS_Hodo_AdcTdc_Offset_${runNum}.param" ]; then
	mv "$REPLAYPATH/CALIBRATION/ref_times/HMS_Hodo_AdcTdc_Offset_${runNum}.param" "$REPLAYPATH/CALIBRATION/ref_times/HMS/Hodo/HMS_Hodo_AdcTdc_Offset_${runNum}.param"
    fi
    if [ -f "$REPLAYPATH/CALIBRATION/ref_times/SHMS_Hodo_AdcTdc_Offset_${runNum}.param" ]; then
	mv "$REPLAYPATH/CALIBRATION/ref_times/SHMS_Hodo_AdcTdc_Offset_${runNum}.param" "$REPLAYPATH/CALIBRATION/ref_times/SHMS/Hodo/SHMS_Hodo_AdcTdc_Offset_${runNum}.param"
    fi
    # Depending on runnumber, copy different "base" file to modify subsequently in script
    if [ "$runNum" -le "5334" ]; then
	cp "$REPLAYPATH/PARAM/HMS/HODO/hhodo_cuts_Autumn18.param" "$REPLAYPATH/CALIBRATION/ref_times/HMS/Hodo/hhodo_cuts_${runNum}.param"
	cp "$REPLAYPATH/PARAM/SHMS/HODO/phodo_cuts_Autumn18.param" "$REPLAYPATH/CALIBRATION/ref_times/SHMS/Hodo/phodo_cuts_${runNum}.param"
    fi
    if [ "$runNum" -ge "5335" -a "$runNum" -le "7045" ]; then 
	cp "$REPLAYPATH/PARAM/HMS/HODO/hhodo_cuts_Winter18.param" "$REPLAYPATH/CALIBRATION/ref_times/HMS/Hodo/hhodo_cuts_${runNum}.param"
	cp "$REPLAYPATH/PARAM/SHMS/HODO/phodo_cuts_Winter18.param" "$REPLAYPATH/CALIBRATION/ref_times/SHMS/Hodo/phodo_cuts_${runNum}.param"
    fi
    if [ "$runNum" -ge "7046" -a "$runNum" -le "8375" ]; then 
	cp "$REPLAYPATH/PARAM/HMS/HODO/hhodo_cuts_Spring19.param" "$REPLAYPATH/CALIBRATION/ref_times/HMS/Hodo/hhodo_cuts_${runNum}.param"
	cp "$REPLAYPATH/PARAM/SHMS/HODO/phodo_cuts_Spring19.param" "$REPLAYPATH/CALIBRATION/ref_times/SHMS/Hodo/phodo_cuts_${runNum}.param"
    fi
    if [ "$runNum" -ge "8376" ]; then 
	cp "$REPLAYPATH/PARAM/HMS/HODO/hhodo_cuts_Summer19.param" "$REPLAYPATH/CALIBRATION/ref_times/HMS/Hodo/hhodo_cuts_${runNum}.param"
	cp "$REPLAYPATH/PARAM/SHMS/HODO/phodo_cuts_Summer19.param" "$REPLAYPATH/CALIBRATION/ref_times/SHMS/Hodo/phodo_cuts_${runNum}.param"
    fi
    # Copy new offset values from file, replace old values in cuts param file
    HMSNewOffset=$(sed -n '2p' "$REPLAYPATH/CALIBRATION/ref_times/HMS/Hodo/HMS_Hodo_AdcTdc_Offset_${runNum}.param")
    SHMSNewOffset=$(sed -n '2p' "$REPLAYPATH/CALIBRATION/ref_times/SHMS/Hodo/SHMS_Hodo_AdcTdc_Offset_${runNum}.param")
    sed -i "s/.*hhodo_adc_tdc_offset.*/${HMSNewOffset}/" "$REPLAYPATH/CALIBRATION/ref_times/HMS/Hodo/hhodo_cuts_${runNum}.param"
    sed -i "s/.*phodo_adc_tdc_offset.*/${SHMSNewOffset}/" "$REPLAYPATH/CALIBRATION/ref_times/SHMS/Hodo/phodo_cuts_${runNum}.param"
    # Clean up now useless text files
    rm -rf "$REPLAYPATH/CALIBRATION/ref_times/HMS/Hodo/HMS_Hodo_AdcTdc_Offset_${runNum}.param"
    rm -rf "$REPLAYPATH/CALIBRATION/ref_times/SHMS/Hodo/SHMS_Hodo_AdcTdc_Offset_${runNum}.param"

done < "$inputFile"
