#!/bin/bash

### Stephen Kay --- University of Regina --- 02/09/20 ###
### Switches out SHMS HGC calibs in param file with new ones ###
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
cd "${REPLAYPATH}/DBASE/COIN/KaonLT_Calib/"
# Uncomment line that pipes echo to tmp.txt for testing
# Run with list of param files, then diff tmp.txt and the run list of all of the calibration files you expect
#rm "tmp.txt"
#touch "tmp.txt"
# Read from list of param files
while IFS='' read -r line || [[ -n "$line" ]]; do
    CalibFile=$line
    RunNum1=$((${CalibFile:13:4}))
    RunNum2=$((${CalibFile:18:4}))
    # Get correct list of runs to modify to use this parameter file
    RunSetFile="SHMS_HGC_RunLists/HGC_${RunNum1}_${RunNum2}_Files"
    # Debugging line, uncomment this and later echo command to check which files are being modified
    #echo "$RunSetFile"
    # # Check file exists
    if [ -f "$RunSetFile" ]; then
    	# Loop over all runs in file
    	while IFS='' read -r line || [[ -n "$line" ]]; do
    	    ParamRunNum=$line
	    # echo lines are for testing only
	    #echo "$ParamRunNum"
	    #echo "$ParamRunNum" >> "tmp.txt"
    	    # Set OfflineXXXX.param file to use new SHMS HGC calibration
    	    sed -i "s/phgcer_calib_Autumn18.param/CALIB\/${CalibFile}/" "Offline"$ParamRunNum".param" 
    	    sed -i "s/phgcer_calib_Winter18.param/CALIB\/${CalibFile}/" "Offline"$ParamRunNum".param" 
    	    sed -i "s/phgcer_calib_Spring19.param/CALIB\/${CalibFile}/" "Offline"$ParamRunNum".param" 
    	    sed -i "s/phgcer_calib_Summer19.param/CALIB\/${CalibFile}/" "Offline"$ParamRunNum".param" 
    	done < "$RunSetFile" 
    else echo "!!! ERROR !!! - $RunSetFile not found! - !!! ERROR !!!"
    fi

done < "$inputFile"
