#!/bin/bash

### Script for running (via batch or otherwise) the DC calibration, this one script does all of the relevant steps for the calibration process
### REQUIRES two arguments, runnumber and spectrometer (HMS or SHMS, the caps are important!)
### If you want to run with LESS than all of the events, provide a third argument with # events

RUNNUMBER=$1
OPT=$2
### Check you've provided the first argument
if [[ $1 -eq "" ]]; then
    echo "I need a Run Number!"
    echo "Please provide a run number as input"
    exit 2
fi
### Check you have provided the second argument correctly
if [[ ! $2 =~ ^("HMS"|"SHMS")$ ]]; then
    echo "Please specify spectrometer, HMS or SHMS"
    exit 2
fi
### Check if a third argument was provided, if not assume -1, if yes, this is max events
if [[ $3 -eq "" ]]; then
    MAXEVENTS=-1
else
    MAXEVENTS=$3
fi
if [[ $OPT == "HMS" ]]; then
    spec="hms"
    specL="h"
    elif [[ $OPT == "SHMS" ]]; then
    spec="shms"
    specL="p"
fi
if [[ ${USER} = "cdaq" ]]; then
    echo "Warning, running as cdaq."
    echo "Please be sure you want to do this."
    echo "Comment this section out and run again if you're sure."
    exit 2
fi        
# Set path depending upon hostname. Change or add more as needed  
if [[ "${HOSTNAME}" = *"farm"* ]]; then  
    REPLAYPATH="/group/c-kaonlt/USERS/${USER}/hallc_replay_lt"
    if [[ "${HOSTNAME}" != *"ifarm"* ]]; then
	source /site/12gev_phys/softenv.sh 2.1
    fi
    cd "/group/c-kaonlt/hcana/"
    source "/group/c-kaonlt/hcana/setup.sh"
    cd "$REPLAYPATH"
    source "$REPLAYPATH/setup.sh"
elif [[ "${HOSTNAME}" = *"qcd"* ]]; then
    REPLAYPATH="/group/c-kaonlt/USERS/${USER}/hallc_replay_lt"
    source /site/12gev_phys/softenv.sh 2.1
    cd "/group/c-kaonlt/hcana/"
    source "/group/c-kaonlt/hcana/setup.sh" 
    cd "$REPLAYPATH"
    source "$REPLAYPATH/setup.sh" 
elif [[ "${HOSTNAME}" = *"cdaq"* ]]; then
    REPLAYPATH="/home/cdaq/hallc-online/hallc_replay_lt"
elif [[ "${HOSTNAME}" = *"phys.uregina.ca"* ]]; then
    REPLAYPATH="/home/${USER}/work/JLab/hallc_replay_lt"
fi
cd $REPLAYPATH

### Check the extra folders you'll need exist, if they don't then make them
if [ ! -d "$REPLAYPATH/DBASE/COIN/HMS_DCCalib" ]; then
    mkdir "$REPLAYPATH/DBASE/COIN/HMS_DCCalib"
fi

if [ ! -d "$REPLAYPATH/DBASE/COIN/SHMS_DCCalib" ]; then
    mkdir "$REPLAYPATH/DBASE/COIN/SHMS_DCCalib"
fi

if [ ! -d "$REPLAYPATH/PARAM/HMS/DC/CALIB" ]; then
    mkdir "$REPLAYPATH/PARAM/HMS/DC/CALIB"
fi

if [ ! -d "$REPLAYPATH/PARAM/SHMS/DC/CALIB" ]; then
    mkdir "$REPLAYPATH/PARAM/SHMS/DC/CALIB"
fi

### Run the first replay script, then, run the calibration macro
eval "$REPLAYPATH/hcana -l -q \"SCRIPTS/"$OPT"/PRODUCTION/"$OPT"DC_Calib_Coin_Pt1.C($RUNNUMBER,$MAXEVENTS)\""
ROOTFILE="$REPLAYPATH/ROOTfilesDCCalib/"$OPT"_DC_Calib_Pt1_"$RUNNUMBER"_"$MAXEVENTS".root" 
cd "$REPLAYPATH/CALIBRATION/dc_calib/scripts"
root -l -b -q "$REPLAYPATH/CALIBRATION/dc_calib/scripts/main_calib.C(\"$OPT\", \"$ROOTFILE\", $RUNNUMBER)"

### Loop checks if the new parameter files exist, returns an error if they don't
if [[ ! -f "$REPLAYPATH/CALIBRATION/dc_calib/scripts/"$OPT"_DC_cardLog_"$RUNNUMBER"/"$specL"dc_calib_"$RUNNUMBER$".param" && ! -f  "$REPLAYPATH/CALIBRATION/dc_calib/scripts/"$OPT"_DC_cardLog_"$RUNNUMBER"/"$specL"dc_tzero\
_per_wire_"$RUNNUMBER$".param" ]]; then
    echo "New parameter files not found, calibration script likely failed"
    exit 2
fi

### Copy our new parameter files to another directory
cp "$REPLAYPATH/CALIBRATION/dc_calib/scripts/"$OPT"_DC_cardLog_"$RUNNUMBER"/"$specL"dc_calib_"$RUNNUMBER$".param" "$REPLAYPATH/PARAM/"$OPT"/DC/CALIB/"$specL"dc_calib_"$RUNNUMBER$".param"
cp "$REPLAYPATH/CALIBRATION/dc_calib/scripts/"$OPT"_DC_cardLog_"$RUNNUMBER"/"$specL"dc_tzero_per_wire_"$RUNNUMBER$".param" "$REPLAYPATH/PARAM/"$OPT"/DC/CALIB/"$specL"dc_tzero_per_wire_"$RUNNUMBER$".param"
cd "$REPLAYPATH/DBASE/COIN"

### For run numbers under 5334, we use the run period 1 files as a base
### Copy these files to a new directory and rename them
### Replace info in lines 3, 37 and 38 with the path to our new files via sed commands
if [ "$RUNNUMBER" -le "5334" ]; then
    cp "$REPLAYPATH/DBASE/COIN/standard.database" "$REPLAYPATH/DBASE/COIN/"$OPT"_DCCalib/standard_$RUNNUMBER.database"
    cp "$REPLAYPATH/DBASE/COIN/OnlineAutumn18.param" "$REPLAYPATH/DBASE/COIN/"$OPT"_DCCalib/general_$RUNNUMBER.param"
    sed -i "s/OnlineAutumn18.param/"$OPT"_DCCalib\/general_$RUNNUMBER.param/" $REPLAYPATH"/DBASE/COIN/"$OPT"_DCCalib/standard_"$RUNNUMBER".database"
    if [[ $OPT == "HMS" ]];then
	sed -i "s/hdc_calib_Autumn18.param/CALIB\/hdc_calib_$RUNNUMBER.param/" $REPLAYPATH"/DBASE/COIN/"$OPT"_DCCalib/general_"$RUNNUMBER".param"
	sed -i "s/hdc_tzero_per_wire_Autumn18.param/CALIB\/hdc_tzero_per_wire_$RUNNUMBER.param/" $REPLAYPATH"/DBASE/COIN/"$OPT"_DCCalib/general_"$RUNNUMBER".param"
    fi
    if [[ $OPT == "SHMS" ]];then
	sed -i "s/pdc_calib_Autumn18.param/CALIB\/pdc_calib_$RUNNUMBER.param/" $REPLAYPATH"/DBASE/COIN/"$OPT"_DCCalib/general_"$RUNNUMBER".param"
	sed -i "s/pdc_tzero_per_wire_Autumn18.param/CALIB\/pdc_tzero_per_wire_$RUNNUMBER.param/" $REPLAYPATH"/DBASE/COIN/"$OPT"_DCCalib/general_"$RUNNUMBER".param"
    fi
fi
### For run numbers 5335-7045, we use the run period 2 files as a base
### Copy these files to a new directory and rename them
### Replace info in lines 8, 37 and 38 with the path to our new files via sed commands
if [ "$RUNNUMBER" -ge "5335" -a "$RUNNUMBER" -le "7045" ]; then 
    cp "$REPLAYPATH/DBASE/COIN/standard.database" "$REPLAYPATH/DBASE/COIN/"$OPT"_DCCalib/standard_$RUNNUMBER.database"
    cp "$REPLAYPATH/DBASE/COIN/OnlineWinter18.param" "$REPLAYPATH/DBASE/COIN/"$OPT"_DCCalib/general_$RUNNUMBER.param"
    sed -i "s/OnlineWinter18.param/"$OPT"_DCCalib\/general_$RUNNUMBER.param/" $REPLAYPATH"/DBASE/COIN/"$OPT"_DCCalib/standard_"$RUNNUMBER".database"
    if [[ $OPT == "HMS" ]];then
	sed -i "s/hdc_calib_Winter18.param/CALIB\/hdc_calib_$RUNNUMBER.param/" $REPLAYPATH"/DBASE/COIN/"$OPT"_DCCalib/general_"$RUNNUMBER".param"
	sed -i "s/hdc_tzero_per_wire_Winter18.param/CALIB\/hdc_tzero_per_wire_$RUNNUMBER.param/" $REPLAYPATH"/DBASE/COIN/"$OPT"_DCCalib/general_"$RUNNUMBER".param"
    fi
    if [[ $OPT == "SHMS" ]]; then
	sed -i "s/pdc_calib_Winter18.param/CALIB\/pdc_calib_$RUNNUMBER.param/" $REPLAYPATH"/DBASE/COIN/"$OPT"_DCCalib/general_"$RUNNUMBER".param"
	sed -i "s/pdc_tzero_per_wire_Winter18.param/CALIB\/pdc_tzero_per_wire_$RUNNUMBER.param/" $REPLAYPATH"/DBASE/COIN/"$OPT"_DCCalib/general_"$RUNNUMBER".param"
    fi
fi
### For run numbers 7046 onwards, we use the run period 3 files as a base
### Copy these files to a new directory and rename them
### Replace info in lines 13, 37 and 38 with the path to our new files via sed commands
if [ "$RUNNUMBER" -ge "7046" -a "$RUNNUMBER" -le "8375" ]; then 
    cp "$REPLAYPATH/DBASE/COIN/standard.database" "$REPLAYPATH/DBASE/COIN/"$OPT"_DCCalib/standard_$RUNNUMBER.database"
    cp "$REPLAYPATH/DBASE/COIN/OnlineSpring19.param" "$REPLAYPATH/DBASE/COIN/"$OPT"_DCCalib/general_$RUNNUMBER.param"
    sed -i "s/OnlineSpring19.param/"$OPT"_DCCalib\/general_$RUNNUMBER.param/" $REPLAYPATH"/DBASE/COIN/"$OPT"_DCCalib/standard_"$RUNNUMBER".database"
    if [[ $OPT == "HMS" ]];then
	sed -i "s/hdc_calib_Spring19.param/CALIB\/hdc_calib_$RUNNUMBER.param/" $REPLAYPATH"/DBASE/COIN/"$OPT"_DCCalib/general_"$RUNNUMBER".param"
	sed -i "s/hdc_tzero_per_wire_Spring19.param/CALIB\/hdc_tzero_per_wire_$RUNNUMBER.param/" $REPLAYPATH"/DBASE/COIN/"$OPT"_DCCalib/general_"$RUNNUMBER".param"
    fi
    if [[ $OPT == "SHMS" ]]; then
	sed -i "s/pdc_calib_Spring19.param/CALIB\/pdc_calib_$RUNNUMBER.param/" $REPLAYPATH"/DBASE/COIN/"$OPT"_DCCalib/general_"$RUNNUMBER".param"
	sed -i "s/pdc_tzero_per_wire_Spring19.param/CALIB\/pdc_tzero_per_wire_$RUNNUMBER.param/" $REPLAYPATH"/DBASE/COIN/"$OPT"_DCCalib/general_"$RUNNUMBER".param"
    fi
fi

### For run numbers 8376 onwards, we use the run period 4 (PionLT start) files as a base
### Copy these files to a new directory and rename them
### Replace info in lines 13, 37 and 38 with the path to our new files via sed commands
if [ "$RUNNUMBER" -ge "8376" ]; then 
    cp "$REPLAYPATH/DBASE/COIN/standard.database" "$REPLAYPATH/DBASE/COIN/"$OPT"_DCCalib/standard_$RUNNUMBER.database"
    cp "$REPLAYPATH/DBASE/COIN/OnlineSummer19.param" "$REPLAYPATH/DBASE/COIN/"$OPT"_DCCalib/general_$RUNNUMBER.param"
    sed -i "s/OnlineSummer.param/"$OPT"_DCCalib\/general_$RUNNUMBER.param/" $REPLAYPATH"/DBASE/COIN/"$OPT"_DCCalib/standard_"$RUNNUMBER".database"
    if [[ $OPT == "HMS" ]];then
	sed -i "s/hdc_calib_Spring19.param/CALIB\/hdc_calib_$RUNNUMBER.param/" $REPLAYPATH"/DBASE/COIN/"$OPT"_DCCalib/general_"$RUNNUMBER".param"
	sed -i "s/hdc_tzero_per_wire_Spring19.param/CALIB\/hdc_tzero_per_wire_$RUNNUMBER.param/" $REPLAYPATH"/DBASE/COIN/"$OPT"_DCCalib/general_"$RUNNUMBER".param"
    fi
    if [[ $OPT == "SHMS" ]]; then
	sed -i "s/pdc_calib_Spring19.param/CALIB\/pdc_calib_$RUNNUMBER.param/" $REPLAYPATH"/DBASE/COIN/"$OPT"_DCCalib/general_"$RUNNUMBER".param"
	sed -i "s/pdc_tzero_per_wire_Spring19.param/CALIB\/pdc_tzero_per_wire_$RUNNUMBER.param/" $REPLAYPATH"/DBASE/COIN/"$OPT"_DCCalib/general_"$RUNNUMBER".param"
    fi
fi

### Finally, replay again with our new parameter files
cd $REPLAYPATH
eval "$REPLAYPATH/hcana -l -q \"SCRIPTS/"$OPT"/PRODUCTION/"$OPT"DC_Calib_Coin_Pt2.C($RUNNUMBER,$MAXEVENTS)\""
cd "$REPLAYPATH/CALIBRATION/dc_calib/Calibration_Checker/"
root -l -b -q "$REPLAYPATH/CALIBRATION/dc_calib/Calibration_Checker/run_DC_Calib_Check.C ($RUNNUMBER, $MAXEVENTS, \"$OPT\")"

exit 0
