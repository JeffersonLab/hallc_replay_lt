#!/bin/bash

### Stephen Kay --- University of Regina --- 11/09/20 ###
### Copies param files in provided list to current directory ###
### Reads in a list of param files to switch in ###
inputFile="$1"

if [[ "${HOSTNAME}" = *"farm"* ]]; then  
    REPLAYPATH="/group/c-pionlt/USERS/${USER}/hallc_replay_lt"
elif [[ "${HOSTNAME}" = *"qcd"* ]]; then
    REPLAYPATH="/group/c-pionlt/USERS/${USER}/hallc_replay_lt"
elif [[ "${HOSTNAME}" = *"cdaq"* ]]; then
    REPLAYPATH="/home/cdaq/hallc-online/hallc_replay_lt"
elif [[ "${HOSTNAME}" = *"phys.uregina.ca"* ]]; then
    REPLAYPATH="/home/${USER}/work/JLab/hallc_replay_lt"
fi
cd "${REPLAYPATH}/PARAM/SHMS/HGCER/CALIB"
while IFS='' read -r line || [[ -n "$line" ]]; do
    CalibFile=$line
    if [ -f "/volatile/hallc/c-pionlt/vijay/SHMS_HGC_calib_all_files/${CalibFile}" ]; then 
	cp "/volatile/hallc/c-pionlt/vijay/SHMS_HGC_calib_all_files/${CalibFile}" "./"
    else echo "!!! /volatile/hallc/c-pionlt/vijay/SHMS_HGC_calib_all_files/${CalibFile} not found !!!"
    fi
done < "$inputFile"
