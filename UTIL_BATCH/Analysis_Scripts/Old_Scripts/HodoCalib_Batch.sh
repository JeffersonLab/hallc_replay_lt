#!/bin/bash

### Script for running (via batch or otherwise) the hodoscope calibration, this one script does all of the relevant steps for the calibration proces
### Note that the second part also has an additional bit where it checks for a database file based upon the run number

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

# Set replaypath depending upon hostname. Change as needed
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
if [ ! -d "$REPLAYPATH/DBASE/COIN/HMS_HodoCalib" ]; then
    mkdir "$REPLAYPATH/DBASE/COIN/HMS_HodoCalib"
fi

if [ ! -d "$REPLAYPATH/DBASE/COIN/SHMS_HodoCalib" ]; then
    mkdir "$REPLAYPATH/DBASE/COIN/SHMS_HodoCalib"
fi

if [ ! -d "$REPLAYPATH/PARAM/HMS/HODO/Calibration" ]; then
    mkdir "$REPLAYPATH/PARAM/HMS/HODO/Calibration"
fi

if [ ! -d "$REPLAYPATH/PARAM/SHMS/HODO/Calibration" ]; then
    mkdir "$REPLAYPATH/PARAM/SHMS/HODO/Calibration"
fi

if [ ! -d "$REPLAYPATH/CALIBRATION/hms_hodo_calib/Calibration_Plots" ]; then
    mkdir "$REPLAYPATH/CALIBRATION/hms_hodo_calib/Calibration_Plots"
fi

if [ ! -d "$REPLAYPATH/CALIBRATION/shms_hodo_calib/Calibration_Plots" ]; then
    mkdir "$REPLAYPATH/CALIBRATION/shms_hodo_calib/Calibration_Plots"
fi

eval "$REPLAYPATH/hcana -l -q \"SCRIPTS/"$OPT"/PRODUCTION/"$OPT"Hodo_Calib_Coin_Pt1.C($RUNNUMBER,$MAXEVENTS)\""
ROOTFILE="$REPLAYPATH/ROOTfilesHodoCalib/"$OPT"_Hodo_Calib_Pt1_"$RUNNUMBER"_"$MAXEVENTS".root" 

if [[ $OPT == "HMS" ]]; then
    spec="hms"
    specL="h"
elif [[ $OPT == "SHMS" ]]; then
    spec="shms"
    specL="p"
fi

cd "$REPLAYPATH/CALIBRATION/"$spec"_hodo_calib/"
root -l -q -b "$REPLAYPATH/CALIBRATION/"$spec"_hodo_calib/timeWalkHistos.C(\"$ROOTFILE\", $RUNNUMBER, \"$spec\")"
root -l -q -b "$REPLAYPATH/CALIBRATION/"$spec"_hodo_calib/timeWalkCalib.C($RUNNUMBER)"

# After executing first two root scripts, should have a new .param file so long as scripts ran ok, IF NOT THEN EXIT
if [ ! -f "$REPLAYPATH/PARAM/"$OPT"/HODO/"$specL"hodo_TWcalib_$RUNNUMBER.param" ]; then
    echo ""$specL"hodo_TWCalib_$RUNNUMBER.param not found, calibration script likely failed"
    exit 2
fi

### Now we set up the second replay by making some .database and .param files for them
cd "$REPLAYPATH/DBASE/COIN"
if [ "$RUNNUMBER" -le "5334" ]; then
    # Copy our normal ones
    cp "$REPLAYPATH/DBASE/COIN/standard.database" "$REPLAYPATH/DBASE/COIN/"$OPT"_HodoCalib/standard_$RUNNUMBER.database"
    cp "$REPLAYPATH/DBASE/COIN/OnlineAutumn18.param" "$REPLAYPATH/DBASE/COIN/"$OPT"_HodoCalib/general_$RUNNUMBER.param"
    # Use sed to replace the strings, 3 means line 3, note for sed to work with a variable we need to use "", \ is an ignore character which we need to get the \ in there syntax "Line# s/TEXT TO REPLACE/REPLACEMENT/" FILE
    sed -i "s/OnlineAutumn18.param/"$OPT"_HodoCalib\/general_$RUNNUMBER.param/" $REPLAYPATH"/DBASE/COIN/"$OPT"_HodoCalib/standard_$RUNNUMBER.database"
    if [[ $OPT == "HMS" ]]; then
	sed -i "s/hhodo_TWcalib_Autumn18.param/hhodo_TWcalib_$RUNNUMBER.param/" $REPLAYPATH/DBASE/COIN/HMS_HodoCalib/general_$RUNNUMBER.param 
    elif [[ $OPT == "SHMS" ]]; then
	sed -i "s/phodo_TWcalib_Autumn18.param/phodo_TWcalib_$RUNNUMBER.param/" $REPLAYPATH/DBASE/COIN/SHMS_HodoCalib/general_$RUNNUMBER.param
    fi
fi

if [ "$RUNNUMBER" -ge "5335" -a "$RUNNUMBER" -le "7045" ]; then
    cp "$REPLAYPATH/DBASE/COIN/standard.database" "$REPLAYPATH/DBASE/COIN/"$OPT"_HodoCalib/standard_$RUNNUMBER.database"
    cp "$REPLAYPATH/DBASE/COIN/OnlineWinter18.param" "$REPLAYPATH/DBASE/COIN/"$OPT"_HodoCalib/general_$RUNNUMBER.param"
    sed -i "s/OnlineWinter18.param/"$OPT"_HodoCalib\/general_$RUNNUMBER.param/" $REPLAYPATH"/DBASE/COIN/"$OPT"_HodoCalib/standard_$RUNNUMBER.database"
    if [[ $OPT == "HMS" ]]; then
	sed -i "s/hhodo_TWcalib_Winter18.param/hhodo_TWcalib_$RUNNUMBER.param/" $REPLAYPATH/DBASE/COIN/HMS_HodoCalib/general_$RUNNUMBER.param 
    elif [[ $OPT == "SHMS" ]]; then
	sed -i "s/phodo_TWcalib_Winter18.param/phodo_TWcalib_$RUNNUMBER.param/" $REPLAYPATH/DBASE/COIN/SHMS_HodoCalib/general_$RUNNUMBER.param
    fi
fi

if [ "$RUNNUMBER" -ge "7046" -a "$RUNNUMBER" -le "8375" ]; then
    cp "$REPLAYPATH/DBASE/COIN/standard.database" "$REPLAYPATH/DBASE/COIN/"$OPT"_HodoCalib/standard_$RUNNUMBER.database"
    cp "$REPLAYPATH/DBASE/COIN/OnlineSpring19.param" "$REPLAYPATH/DBASE/COIN/"$OPT"_HodoCalib/general_$RUNNUMBER.param"
    sed -i "s/OnlineSpring19.param/"$OPT"_HodoCalib\/general_$RUNNUMBER.param/" $REPLAYPATH"/DBASE/COIN/"$OPT"_HodoCalib/standard_$RUNNUMBER.database"
    if [[ $OPT == "HMS" ]]; then
	sed -i "s/hhodo_TWcalib_Spring19.param/hhodo_TWcalib_$RUNNUMBER.param/" $REPLAYPATH/DBASE/COIN/HMS_HodoCalib/general_$RUNNUMBER.param 
    elif [[ $OPT == "SHMS" ]]; then
	sed -i "s/phodo_TWcalib_Spring19.param/phodo_TWcalib_$RUNNUMBER.param/" $REPLAYPATH/DBASE/COIN/SHMS_HodoCalib/general_$RUNNUMBER.param
    fi
fi

if [ "$RUNNUMBER" -ge "8376" ]; then
    cp "$REPLAYPATH/DBASE/COIN/standard.database" "$REPLAYPATH/DBASE/COIN/"$OPT"_HodoCalib/standard_$RUNNUMBER.database"
    cp "$REPLAYPATH/DBASE/COIN/OnlineSummer19.param" "$REPLAYPATH/DBASE/COIN/"$OPT"_HodoCalib/general_$RUNNUMBER.param"
    sed -i "s/OnlineSummer19.param/"$OPT"_HodoCalib\/general_$RUNNUMBER.param/" $REPLAYPATH"/DBASE/COIN/"$OPT"_HodoCalib/standard_$RUNNUMBER.database"
    if [[ $OPT == "HMS" ]]; then
	sed -i "s/hhodo_TWcalib_Spring19.param/hhodo_TWcalib_$RUNNUMBER.param/" $REPLAYPATH/DBASE/COIN/HMS_HodoCalib/general_$RUNNUMBER.param 
    elif [[ $OPT == "SHMS" ]]; then
	sed -i "s/phodo_TWcalib_Spring19.param/phodo_TWcalib_$RUNNUMBER.param/" $REPLAYPATH/DBASE/COIN/SHMS_HodoCalib/general_$RUNNUMBER.param
    fi
fi

# Back to the main directory
cd "$REPLAYPATH"                                
# Off we go again replaying
eval "$REPLAYPATH/hcana -l -q \"SCRIPTS/"$OPT"/PRODUCTION/"$OPT"Hodo_Calib_Coin_Pt2.C($RUNNUMBER,$MAXEVENTS)\""
# Clean up the directories of our generated files
mv "$REPLAYPATH/PARAM/"$OPT"/HODO/"$specL"hodo_TWcalib_$RUNNUMBER.param" "$REPLAYPATH/PARAM/"$OPT"/HODO/Calibration/"$specL"hodo_TWcalib_$RUNNUMBER.param"
mv "$REPLAYPATH/CALIBRATION/"$spec"_hodo_calib/timeWalkHistos_"$RUNNUMBER".root" "$REPLAYPATH/CALIBRATION/"$spec"_hodo_calib/Calibration_Plots/timeWalkHistos_"$RUNNUMBER".root"

cd "$REPLAYPATH/CALIBRATION/"$spec"_hodo_calib/"
# Define the path to the second replay root file
ROOTFILE2="$REPLAYPATH/ROOTfilesHodoCalib/"$OPT"_Hodo_Calib_Pt2_"$RUNNUMBER"_"$MAXEVENTS".root"
# Execute final script
root -l -q -b "$REPLAYPATH/CALIBRATION/"$spec"_hodo_calib/fitHodoCalib.C(\"$ROOTFILE2\", $RUNNUMBER)" 
# Check our new file exists, if not exit, if yes, move it
if [ ! -f "$REPLAYPATH/PARAM/"$OPT"/HODO/"$specL"hodo_Vpcalib_$RUNNUMBER.param" ]; then
    echo ""$specL"hodo_Vpcalib_$RUNNUMBER.param not found, calibration script likely failed"
    exit 2
fi

mv "$REPLAYPATH/PARAM/"$OPT"/HODO/"$specL"hodo_Vpcalib_$RUNNUMBER.param" "$REPLAYPATH/PARAM/"$OPT"/HODO/Calibration/"$specL"hodo_Vpcalib_$RUNNUMBER.param"

# Check our new file exists, if not exit, if yes, move it
if [ ! -f "$REPLAYPATH/CALIBRATION/"$spec"_hodo_calib/HodoCalibPlots_$RUNNUMBER.root" ]; then
    echo "HodoCalibPlots_$RUNNUMBER.root not found, calibration script likely failed"
    exit 2
fi

mv "$REPLAYPATH/CALIBRATION/"$spec"_hodo_calib/HodoCalibPlots_$RUNNUMBER.root" "$REPLAYPATH/CALIBRATION/"$spec"_hodo_calib/Calibration_Plots/HodoCalibPlots_$RUNNUMBER.root"

### Now we set up the third replay by editing our general.param file
cd "$REPLAYPATH/DBASE/COIN"

if [[ $OPT == "HMS" ]]; then
    sed -i "s/hhodo_TWcalib_$RUNNUMBER.param/Calibration\/hhodo_TWcalib_$RUNNUMBER.param/" $REPLAYPATH/DBASE/COIN/HMS_HodoCalib/general_$RUNNUMBER.param 
    if [ "$RUNNUMBER" -le "5334" ]; then
	sed -i "s/hhodo_Vpcalib_Autumn18.param/Calibration\/hhodo_Vpcalib_$RUNNUMBER.param/" $REPLAYPATH/DBASE/COIN/HMS_HodoCalib/general_$RUNNUMBER.param
    fi
    if [ "$RUNNUMBER" -ge "5335" -a "$RUNNUMBER" -le "7045" ]; then
	sed -i "s/hhodo_Vpcalib_Winter18.param/Calibration\/hhodo_Vpcalib_$RUNNUMBER.param/" $REPLAYPATH/DBASE/COIN/HMS_HodoCalib/general_$RUNNUMBER.param
    fi
    if [ "$RUNNUMBER" -ge "7046" -a "$RUNNUMBER" -le "8375" ]; then
	sed -i "s/hhodo_Vpcalib_Spring19.param/Calibration\/hhodo_Vpcalib_$RUNNUMBER.param/" $REPLAYPATH/DBASE/COIN/HMS_HodoCalib/general_$RUNNUMBER.param
    fi
    if [ "$RUNNUMBER" -ge "8376" ]; then
	sed -i "s/hhodo_Vpcalib_Spring19.param/Calibration\/hhodo_Vpcalib_$RUNNUMBER.param/" $REPLAYPATH/DBASE/COIN/HMS_HodoCalib/general_$RUNNUMBER.param
    fi
elif [[ $OPT == "SHMS" ]]; then
    sed -i "s/phodo_TWcalib_$RUNNUMBER.param/Calibration\/phodo_TWcalib_$RUNNUMBER.param/" $REPLAYPATH/DBASE/COIN/SHMS_HodoCalib/general_$RUNNUMBER.param 
    if [ "$RUNNUMBER" -le "5334" ]; then
	sed -i "s/phodo_Vpcalib_Autumn18.param/Calibration\/phodo_Vpcalib_$RUNNUMBER.param/" $REPLAYPATH/DBASE/COIN/SHMS_HodoCalib/general_$RUNNUMBER.param
    fi
    if [ "$RUNNUMBER" -ge "5335" -a "$RUNNUMBER" -le "7045" ]; then
	sed -i "s/phodo_Vpcalib_Winter18.param/Calibration\/phodo_Vpcalib_$RUNNUMBER.param/" $REPLAYPATH/DBASE/COIN/SHMS_HodoCalib/general_$RUNNUMBER.param
    fi
    if [ "$RUNNUMBER" -ge "7046" -a "$RUNNUMBER" -le "8375" ]; then
	sed -i "s/phodo_Vpcalib_Spring19.param/Calibration\/phodo_Vpcalib_$RUNNUMBER.param/" $REPLAYPATH/DBASE/COIN/SHMS_HodoCalib/general_$RUNNUMBER.param
    fi
    if [ "$RUNNUMBER" -ge "8376" ]; then
	sed -i "s/phodo_Vpcalib_Spring19.param/Calibration\/phodo_Vpcalib_$RUNNUMBER.param/" $REPLAYPATH/DBASE/COIN/SHMS_HodoCalib/general_$RUNNUMBER.param
    fi    
fi

cd "$REPLAYPATH"
eval "$REPLAYPATH/hcana -l -q \"SCRIPTS/"$OPT"/PRODUCTION/"$OPT"Hodo_Calib_Coin_Pt3.C($RUNNUMBER,$MAXEVENTS)\""
exit 0
