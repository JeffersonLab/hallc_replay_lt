#!/bin/bash

### Stephen Kay --- University of Regina --- 12/11/19 ###
### Script for running (via batch or otherwise) the calorimeter calibration
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
    elif [[ $OPT == "SHMS" ]]; then
    spec="shms"
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
	source /site/12gev_phys/softenv.sh 2.3
    fi
    cd "/group/c-kaonlt/hcana/"
    source "/group/c-kaonlt/hcana/setup.sh"
    cd "$REPLAYPATH"
    source "$REPLAYPATH/setup.sh"
elif [[ "${HOSTNAME}" = *"qcd"* ]]; then
    REPLAYPATH="/group/c-kaonlt/USERS/${USER}/hallc_replay_lt"
    source /site/12gev_phys/softenv.sh 2.3
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
if [ ! -d "$REPLAYPATH/CALIBRATION/shms_cal_calib/Input" ]; then
    mkdir "$REPLAYPATH/CALIBRATION/shms_cal_calib/Input"
fi
if [ ! -d "$REPLAYPATH/CALIBRATION/shms_cal_calib/Output" ]; then
    mkdir "$REPLAYPATH/CALIBRATION/shms_cal_calib/Output"
fi
if [ ! -d "$REPLAYPATH/CALIBRATION/hms_cal_calib/Input" ]; then
    mkdir "$REPLAYPATH/CALIBRATION/hms_cal_calib/Input"
fi
if [ ! -d "$REPLAYPATH/CALIBRATION/hms_cal_calib/Output" ]; then
    mkdir "$REPLAYPATH/CALIBRATION/hms_cal_calib/Output"
fi

### Run the first replay script, then, run the calibration macro
### Kind of a stupid way to get the correct file but prevents constantly writing to a file when analysing
### hcana on 1 event writes configs used to a file which is then read to get the correct file later.
### Probably a better way of doing this with some if/while statement and tee but decided to go for the stupid (but working) solution for now
touch "Tmp_"$RUNNUMBER"_"$OPT".txt"
eval "$REPLAYPATH/hcana -l -q  \"SCRIPTS/COIN/CALIBRATION/"$OPT"Cal_Calib_Coin.C($RUNNUMBER, 1)\"" | tee "Tmp_"$RUNNUMBER"_"$OPT".txt"
if [ $OPT == "HMS" ]; then
    if [ "$RUNNUMBER" -le 8375 ]; then 
	# Find and obtain the calibration used in the replay, assuming it follows one of two patterns
	CALIBFILE=$(grep -o "PARAM/HMS/CAL/hcal_.*" "Tmp_"$RUNNUMBER"_"$OPT".txt")
	CALIBFILE=$(grep -o "PARAM/HMS/CAL/CALIB/hcal_.*" "Tmp_"$RUNNUMBER"_"$OPT".txt")
    fi
    if [ "$RUNNUMBER" -ge 8376 ]; then
	CALIBFILE=$(grep -o "PARAM/HMS/CAL/new_hcal.*" "Tmp_"$RUNNUMBER"_"$OPT".txt")
	CALIBFILE=$(grep -o "PARAM/HMS/CAL/CALIB/hcal_.*" "Tmp_"$RUNNUMBER"_"$OPT".txt")
    fi
fi
if [ $OPT == "SHMS" ]; then
    CALIBFILE=$(grep -o "PARAM/SHMS/CAL/pcal_calib.*" "Tmp_"$RUNNUMBER"_"$OPT".txt")
fi
sleep 10
rm -rf "Tmp_"$RUNNUMBER"_"$OPT".txt"
rm -rf "$REPLAYPATH/ROOTfilesCalCalib/"$OPT"_Cal_Calib_"$RUNNUMBER"_1.root" 
eval "$REPLAYPATH/hcana -l -q \"SCRIPTS/COIN/CALIBRATION/"$OPT"Cal_Calib_Coin.C($RUNNUMBER,$MAXEVENTS)\""
ROOTFILE="$REPLAYPATH/ROOTfilesCalCalib/"$OPT"_Cal_Calib_"$RUNNUMBER"_"$MAXEVENTS".root" 
cd "$REPLAYPATH/CALIBRATION/"$spec"_cal_calib/"
# Copy the input file with a one specific to this run
cp "input.dat" "Input/input_"$RUNNUMBER".dat"
# Snip off the parameters in the input file leaving only the setup conditions and add a new line to the file (which is CRUCIAL!)
sed -i '8, $d' "Input/input_"$RUNNUMBER".dat"
echo $'\n' >> "Input/input_"$RUNNUMBER".dat"
# We now need to copy in the relevant parameters that were used in the replay
# Copies block of parameters and appends them to our input file, expects block of params to be in first 21 lines!
sed -n '1, 21p' $REPLAYPATH"/"$CALIBFILE | tee -a "Input/input_"$RUNNUMBER".dat"
if [ $OPT == "HMS" ]; then
    hcana -l -q -b "hcal_calib.cpp+(\"HMS_Cal_Calib\", $RUNNUMBER, $MAXEVENTS)"
    mv "HMS_Cal_Calib_"$RUNNUMBER"_"$MAXEVENTS".pdf" "Output/HMS_Cal_Calib_"$RUNNUMBER"_"$MAXEVENTS".pdf"
    mv "hcal.param.HMS_Cal_Calib_"$RUNNUMBER"_"$MAXEVENTS "Output/hcal.param.HMS_Cal_Calib_"$RUNNUMBER"_"$MAXEVENTS
fi
if [ $OPT == "SHMS" ]; then
    hcana -l -q -b "pcal_calib.cpp+(\"SHMS_Cal_Calib\", $RUNNUMBER, $MAXEVENTS)"
    mv "SHMS_Cal_Calib_"$RUNNUMBER"_"$MAXEVENTS".pdf" "Output/SHMS_Cal_Calib_"$RUNNUMBER"_"$MAXEVENTS".pdf"
    mv "pcal.param.SHMS_Cal_Calib_"$RUNNUMBER"_"$MAXEVENTS "Output/pcal.param.SHMS_Cal_Calib_"$RUNNUMBER"_"$MAXEVENTS
fi
exit 0
