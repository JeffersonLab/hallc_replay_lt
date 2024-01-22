#!/bin/bash

# 30/06/20 - Stephen Kay, University of Regina
# Executes the root macro to determine the pedestal defaults for a given run number 
# Writes values (output to screen) to a text file for copying into other files
# In future, will get it to generate required files automatically

echo "I take as arguments the run Number and max number of events!"
RUNNUMBER=$1
MAXEVENTS=$2
if [[ -z "$1" ]]; then
    echo "I need a Run Number!"
    echo "Please provide a run number as input"
    exit 2
fi
if [[ -z "$2" ]]; then
    echo "Only Run Number entered...I'll assume -1 (all) events!" 
    MAXEVENTS=-1 
fi

# Set path depending upon hostname. Change or add more as needed  
if [[ "${HOSTNAME}" = *"farm"* ]]; then  
    REPLAYPATH="/group/c-pionlt/USERS/${USER}/hallc_replay_lt"
    cd "$REPLAYPATH"
    source "$REPLAYPATH/setup.sh"
elif [[ "${HOSTNAME}" = *"qcd"* ]]; then
    REPLAYPATH="/group/c-pionlt/USERS/${USER}/hallc_replay_lt"
    cd "$REPLAYPATH"
    source "$REPLAYPATH/setup.sh" 
elif [[ "${HOSTNAME}" = *"cdaq"* ]]; then
    REPLAYPATH="/home/cdaq/hallc-online/hallc_replay_lt"
elif [[ "${HOSTNAME}" = *"phys.uregina.ca"* ]]; then
    REPLAYPATH="/home/${USER}/work/JLab/hallc_replay_lt"
fi

ROOTFILE="$REPLAYPATH/ROOTfiles/Calib/Timing/RefTime${RUNNUMBER}_${MAXEVENTS}.root"

cd "$REPLAYPATH/CALIBRATION/set_peddefault"
if [ ! -d "$REPLAYPATH/CALIBRATION/set_peddefault/OUTPUT" ]; then
    mkdir "$REPLAYPATH/CALIBRATION/set_peddefault/OUTPUT"
fi

Outfile="PedDefaults_${RUNNUMBER}.txt"
# Run script to get pedestal default values, print the output to a text file
root -b <<EOF > ${Outfile}
.L run_ped_default.C
run_hms_ped_default("$ROOTFILE")
run_shms_ped_default("$ROOTFILE")
.q
EOF

sleep 2
mv "${Outfile}" "OUTPUT/${Outfile}"
# Check directories exit, make if not
if [ ! -d "$REPLAYPATH/CALIBRATION/set_peddefault/OUTPUT/HMS_Cer" ]; then
    mkdir "$REPLAYPATH/CALIBRATION/set_peddefault/OUTPUT/HMS_Cer"
fi

if [ ! -d "$REPLAYPATH/CALIBRATION/set_peddefault/OUTPUT/HMS_Cal" ]; then
    mkdir "$REPLAYPATH/CALIBRATION/set_peddefault/OUTPUT/HMS_Cal"
fi

if [ ! -d "$REPLAYPATH/CALIBRATION/set_peddefault/OUTPUT/SHMS_HGC" ]; then
    mkdir "$REPLAYPATH/CALIBRATION/set_peddefault/OUTPUT/SHMS_HGC"
fi

if [ ! -d "$REPLAYPATH/CALIBRATION/set_peddefault/OUTPUT/SHMS_Aero" ]; then
    mkdir "$REPLAYPATH/CALIBRATION/set_peddefault/OUTPUT/SHMS_Aero"
fi

if [ ! -d "$REPLAYPATH/CALIBRATION/set_peddefault/OUTPUT/SHMS_Cal" ]; then
    mkdir "$REPLAYPATH/CALIBRATION/set_peddefault/OUTPUT/SHMS_Cal"
fi
# Depending on runnumber, copy different "base" file to modify subsequently in script
if [ "$RUNNUMBER" -le "5334" ]; then
    cp "$REPLAYPATH/PARAM/HMS/CER/hcer_cuts_Autumn18.param" "$REPLAYPATH/CALIBRATION/set_peddefault/OUTPUT/HMS_Cer/hcer_cuts_${RUNNUMBER}.param"
    cp "$REPLAYPATH/PARAM/HMS/CAL/hcal_cuts_Autumn18.param" "$REPLAYPATH/CALIBRATION/set_peddefault/OUTPUT/HMS_Cal/hcal_cuts_${RUNNUMBER}.param"
    cp "$REPLAYPATH/PARAM/SHMS/HGCER/phgcer_cuts_Autumn18.param" "$REPLAYPATH/CALIBRATION/set_peddefault/OUTPUT/SHMS_HGC/phgcer_cuts_${RUNNUMBER}.param"
    cp "$REPLAYPATH/PARAM/SHMS/AERO/paero_cuts_Autumn18.param" "$REPLAYPATH/CALIBRATION/set_peddefault/OUTPUT/SHMS_Aero/paero_cuts_${RUNNUMBER}.param"
    cp "$REPLAYPATH/PARAM/SHMS/CAL/pcal_cuts_Autumn18.param" "$REPLAYPATH/CALIBRATION/set_peddefault/OUTPUT/SHMS_Cal/pcal_cuts_${RUNNUMBER}.param"
fi
if [ "$RUNNUMBER" -ge "5335" -a "$RUNNUMBER" -le "7045" ]; then 
    cp "$REPLAYPATH/PARAM/HMS/CER/hcer_cuts_Winter18.param" "$REPLAYPATH/CALIBRATION/set_peddefault/OUTPUT/HMS_Cer/hcer_cuts_${RUNNUMBER}.param"
    cp "$REPLAYPATH/PARAM/HMS/CAL/hcal_cuts_Winter18.param" "$REPLAYPATH/CALIBRATION/set_peddefault/OUTPUT/HMS_Cal/hcal_cuts_${RUNNUMBER}.param"
    cp "$REPLAYPATH/PARAM/SHMS/HGCER/phgcer_cuts_Winter18.param" "$REPLAYPATH/CALIBRATION/set_peddefault/OUTPUT/SHMS_HGC/phgcer_cuts_${RUNNUMBER}.param"
    cp "$REPLAYPATH/PARAM/SHMS/AERO/paero_cuts_Winter18.param" "$REPLAYPATH/CALIBRATION/set_peddefault/OUTPUT/SHMS_Aero/paero_cuts_${RUNNUMBER}.param"
    cp "$REPLAYPATH/PARAM/SHMS/CAL/pcal_cuts_Winter18.param" "$REPLAYPATH/CALIBRATION/set_peddefault/OUTPUT/SHMS_Cal/pcal_cuts_${RUNNUMBER}.param"
fi
if [ "$RUNNUMBER" -ge "7046" -a "$RUNNUMBER" -le "8375" ]; then 
    cp "$REPLAYPATH/PARAM/HMS/CER/hcer_cuts_Spring19.param" "$REPLAYPATH/CALIBRATION/set_peddefault/OUTPUT/HMS_Cer/hcer_cuts_${RUNNUMBER}.param"
    cp "$REPLAYPATH/PARAM/HMS/CAL/hcal_cuts_Spring19.param" "$REPLAYPATH/CALIBRATION/set_peddefault/OUTPUT/HMS_Cal/hcal_cuts_${RUNNUMBER}.param"
    cp "$REPLAYPATH/PARAM/SHMS/HGCER/phgcer_cuts_Spring19.param" "$REPLAYPATH/CALIBRATION/set_peddefault/OUTPUT/SHMS_HGC/phgcer_cuts_${RUNNUMBER}.param"
    cp "$REPLAYPATH/PARAM/SHMS/AERO/paero_cuts_Spring19.param" "$REPLAYPATH/CALIBRATION/set_peddefault/OUTPUT/SHMS_Aero/paero_cuts_${RUNNUMBER}.param"
    cp "$REPLAYPATH/PARAM/SHMS/CAL/pcal_cuts_Spring19.param" "$REPLAYPATH/CALIBRATION/set_peddefault/OUTPUT/SHMS_Cal/pcal_cuts_${RUNNUMBER}.param"
fi
if [ "$RUNNUMBER" -ge "8376" ]; then 
    cp "$REPLAYPATH/PARAM/HMS/CER/hcer_cuts_Summer19.param" "$REPLAYPATH/CALIBRATION/set_peddefault/OUTPUT/HMS_Cer/hcer_cuts_${RUNNUMBER}.param"
    cp "$REPLAYPATH/PARAM/HMS/CAL/hcal_cuts_Summer19.param" "$REPLAYPATH/CALIBRATION/set_peddefault/OUTPUT/HMS_Cal/hcal_cuts_${RUNNUMBER}.param"
    cp "$REPLAYPATH/PARAM/SHMS/HGCER/phgcer_cuts_Summer19.param" "$REPLAYPATH/CALIBRATION/set_peddefault/OUTPUT/SHMS_HGC/phgcer_cuts_${RUNNUMBER}.param"
    cp "$REPLAYPATH/PARAM/SHMS/AERO/paero_cuts_Summer19.param" "$REPLAYPATH/CALIBRATION/set_peddefault/OUTPUT/SHMS_Aero/paero_cuts_${RUNNUMBER}.param"
    cp "$REPLAYPATH/PARAM/SHMS/CAL/pcal_cuts_Summer19.param" "$REPLAYPATH/CALIBRATION/set_peddefault/OUTPUT/SHMS_Cal/pcal_cuts_${RUNNUMBER}.param"
fi

# Append a new line to each of the files to eliminate any potential line overlaps
echo "">>"$REPLAYPATH/CALIBRATION/set_peddefault/OUTPUT/HMS_Cer/hcer_cuts_${RUNNUMBER}.param"
echo "">>"$REPLAYPATH/CALIBRATION/set_peddefault/OUTPUT/HMS_Cal/hcal_cuts_${RUNNUMBER}.param"
echo "">>"$REPLAYPATH/CALIBRATION/set_peddefault/OUTPUT/SHMS_HGC/phgcer_cuts_${RUNNUMBER}.param"
echo "">>"$REPLAYPATH/CALIBRATION/set_peddefault/OUTPUT/SHMS_Aero/paero_cuts_${RUNNUMBER}.param"
echo "">>"$REPLAYPATH/CALIBRATION/set_peddefault/OUTPUT/SHMS_Cal/pcal_cuts_${RUNNUMBER}.param"
# Copy relevant lines to cuts param files
sed -n 9,9p "OUTPUT/${Outfile}">>"$REPLAYPATH/CALIBRATION/set_peddefault/OUTPUT/HMS_Cer/hcer_cuts_${RUNNUMBER}.param"
sed -n 10,17p "OUTPUT/${Outfile}">>"$REPLAYPATH/CALIBRATION/set_peddefault/OUTPUT/HMS_Cal/hcal_cuts_${RUNNUMBER}.param"
sed -n 18,18p "OUTPUT/${Outfile}">>"$REPLAYPATH/CALIBRATION/set_peddefault/OUTPUT/SHMS_HGC/phgcer_cuts_${RUNNUMBER}.param"
sed -n 20,21p "OUTPUT/${Outfile}">>"$REPLAYPATH/CALIBRATION/set_peddefault/OUTPUT/SHMS_Aero/paero_cuts_${RUNNUMBER}.param" 
sed -n 22,37p "OUTPUT/${Outfile}">>"$REPLAYPATH/CALIBRATION/set_peddefault/OUTPUT/SHMS_Cal/pcal_cuts_${RUNNUMBER}.param"

exit 0
