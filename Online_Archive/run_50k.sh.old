#! /bin/bash

# Stephen JD Kay - University of Regina - 13/07/22
# Arguments should be run number, type of run and target type
# Anything but the valid options should be ignored and bounced back to the user as a prompt

# This script runs a quick 50k of each spectrometer, and then does a 50k analysis replay before printing the tracking efficiencies
# I did this in a slightly lazy way where it just uses the line number in the report files, if the report templates get changed, these will need adjusting!
# Free beer/chocolate to anyone who improves this and switches it to some grep/sed based statement which just gets the correct line wherever it is

# Set path depending upon hostname, should only run on cdaql1/cdaql2/cdaql3 as cdaq
if [[ "${HOSTNAME}" = *"cdaql"* ]]; then # Check the user is on cdaql1 or cdaql2
    if [[ "${USER}" = "cdaq" ]]; then # Check the script is being executed by cdaq
	REPLAYPATH="/home/cdaq/hallc-online/hallc_replay_lt"
    else
	echo " !!!! ERROR !!!!!"
	echo " Must run as cdaq"
	echo " !!!! ERROR !!!!!"
	exit 1
    fi
else
    echo " !!!!!!!!!!!!!!!! ERROR !!!!!!!!!!!!!"
    echo " Must run on cdaql1, cdaql2 or cdaql3"
    echo " !!!!!!!!!!!!!!!! ERROR !!!!!!!!!!!!!"
    exit 1
fi

UTILPATH="${REPLAYPATH}/UTIL_PION"
cd $REPLAYPATH
echo ""
echo "Starting physics analysis of PionLT data"
echo "Required arguments are run number, run type and target"
echo ""
echo "Run number must be a positive integer value"
echo "Run type must be one of - Prod - Lumi - HeePSing - HeePCoin - fADC - Optics - Case sensitive!"
echo "Target must be one of - LH2 - LD2 - Dummy10cm - Carbon0p5 - AuFoil - Optics1 - Optics2 - CarbonHole - Case sensitive!"
RUNNUMBER=$1
RUNTYPE=$2
TARGET=$3
NUMEVENTS=$4

# Need to change these a little, should check whether arguments are good or not REGARDLESS of whether they're blank
if [[ -z "$1" || ! "$RUNNUMBER" =~ ^-?[0-9]+$ ]]; then # Check an argument was provided and that it is a positive integer, if not, prompt for one
    echo ""
    echo "I need a valid run number - MUST be a positive integer"
    while true; do
	echo ""
	read -p "Please type in a run number (positive integer) as input or press ctrl-c to exit : " RUNNUMBER
	case $RUNNUMBER in
	    '' | *[!0-9]*);; # If the input is NOT a positive integer (or it's just an empty string), don't break the loop
	    *) break;;
	esac
    done
fi
if [[ -z "$2" || ! "$RUNTYPE" =~ Prod|Lumi|HeePSing|HeePCoin|fADC|Optics ]]; then # Check the 2nd argument was provided and that it's one of the valid options
    echo ""
    echo "I need a valid run type"
    while true; do
	echo ""
	read -p "Please type in a run type from - Prod - Lumi - HeePSing - HeePCoin - fADC - Optics - Case sensitive! - or press ctrl-c to exit : " RUNTYPE
	case $RUNTYPE in
	    '');; # If blank, prompt again
	    'Prod'|'Lumi'|'HeePSing'|'HeePCoin'|'Optics'|'fADC') break;; # If a valid option, break the loop and continue
	esac
    done
fi
if [[ -z "$3" || ! "$TARGET" =~ LH2|LD2|Dummy10cm|Carbon0p5|AuFoil|Optics1|Optics2|CarbonHole ]]; then # Check the 3rd argument was provided and that it's one of the valid options
    echo ""
    echo "I need a valid target"
    while true; do	
	echo ""
	read -p "Please type in a target from - LH2 - LD2 - Dummy10cm - Carbon0p5 - AuFoil - Optics1 - Optics2 - CarbonHole - Case sensitive! - or press ctrl-c to exit : " TARGET
	case $TARGET in
	    '');; # If blank, prompt again
	    'LH2'|'LD2'|'Dummy10cm'|'Carbon0p5'|'AuFoil'|'Optics1'|'Optics2'|'CarbonHole') break;; # If a valid option, break the loop and continue
	esac
    done
fi
echo ""

if [[ -z "$4" ]]; then
    NUMEVENTS=50000
fi

if [[ $RUNTYPE == "Prod" || $RUNTYPE == "fADC" ]]; then
    eval "$REPLAYPATH/hcana -l -q \"UTIL_PION/scripts/replay/PionLT/replay_production_coin.C($RUNNUMBER,$NUMEVENTS)\""
    REPORT_FILE="${REPLAYPATH}/REPORT_OUTPUT/Analysis/PionLT/Pion_replay_coin_production_${RUNNUMBER}_${NUMEVENTS}.report"
    El_Track_Eff=$(sed -n 82p $REPORT_FILE)
    Had_Track_Eff=$(sed -n 80p $REPORT_FILE)
    HMS_3of4_Eff=$(sed -n 289p $REPORT_FILE)
    SHMS_3of4_Eff=$(sed -n 274p $REPORT_FILE)
elif [[ $RUNTYPE == "HeePSing" || $RUNTYPE == "Lumi" ]]; then # HeePSingles and Lumi get analysed in the same way effectively
    eval "$REPLAYPATH/hcana -l -q \"$UTILPATH/scripts/replay/PionLT/replay_hms_heep.C($RUNNUMBER,$NUMEVENTS)\""
    eval "$REPLAYPATH/hcana -l -q \"$UTILPATH/scripts/replay/PionLT/replay_shms_heep.C($RUNNUMBER,$NUMEVENTS)\""
    HMS_REPORT_FILE="${REPLAYPATH}/REPORT_OUTPUT/Analysis/HeeP/Pion_replay_hms_production_${RUNNUMBER}_${NUMEVENTS}.report"
    SHMS_REPORT_FILE="${REPLAYPATH}/REPORT_OUTPUT/Analysis/HeeP/Pion_replay_shms_production_${RUNNUMBER}_${NUMEVENTS}.report"
    El_Track_Eff=$(sed -n 86p $HMS_REPORT_FILE)
    Had_Track_Eff=$(sed -n 84p $SHMS_REPORT_FILE) # Actually an electron tracking efficiency for lumi and heep singles
    HMS_3of4_Eff=$(sed -n 255p $HMS_REPORT_FILE)
    SHMS_3of4_Eff=$(sed -n 240p $SHMS_REPORT_FILE)
elif [[ $RUNTYPE == "HeePCoin" ]]; then
    eval "$REPLAYPATH/hcana -l -q \"$UTILPATH/scripts/replay/PionLT/replay_coin_heep.C($RUNNUMBER,$NUMEVENTS)\"" 
    REPORT_FILE="${REPLAYPATH}/REPORT_OUTPUT/Analysis/HeeP/Pion_replay_coin_production_${RUNNUMBER}_${NUMEVENTS}.report"
    El_Track_Eff=$(sed -n 82p $REPORT_FILE)
    Had_Track_Eff=$(sed -n 80p $REPORT_FILE)
    HMS_3of4_Eff=$(sed -n 246p $REPORT_FILE)
    SHMS_3of4_Eff=$(sed -n 231p $REPORT_FILE)
elif [[ $RUNTYPE == "Optics" ]]; then
    echo "Nope - Doesn't work for this yet"
fi

echo ""
echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
echo "!!!!!!!!!!!!!!!! Check Hodo and Tracking Efficiencies !!!!!!!!!!!!!!!!!"
echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
echo ""
echo "${El_Track_Eff}"
echo "${Had_Track_Eff}"
echo "HMS Hodo 3/4 Eff - ${HMS_3of4_Eff}"
echo "SHMS Hodo 3/4 Eff - ${SHMS_3of4_Eff}"
echo ""
echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
echo "!!!!!!!!!!!!!!!!!!! If under 95%, check DAQ windows !!!!!!!!!!!!!!!!!!!"
echo "!!!!!!!!!!!!!!!!!!! Look for errors in replay above !!!!!!!!!!!!!!!!!!!"
echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"

sleep 3

eval '"${REPLAYPATH}/run_coin_hms.sh" ${RUNNUMBER} ${NUMEVENTS}'

echo ""
echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
echo "!!!!!!!!!!!!!!!! Check Hodo and Tracking Efficiencies !!!!!!!!!!!!!!!!!"
echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
echo ""
echo "${El_Track_Eff}"
echo "${Had_Track_Eff}"
echo "HMS Hodo 3/4 Eff - ${HMS_3of4_Eff}"
echo "SHMS Hodo 3/4 Eff - ${SHMS_3of4_Eff}"
echo ""
echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
echo "!!!!!!!!!!!!!!!!!!! If under 95%, check DAQ windows !!!!!!!!!!!!!!!!!!!"
echo "!!!!!!!!!!!!!!!!!!! Look for errors in replay above !!!!!!!!!!!!!!!!!!!"
echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"

eval '"${REPLAYPATH}/run_coin_shms.sh" ${RUNNUMBER} ${NUMEVENTS}'

echo ""
echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
echo "!!!!!!!!!!!!!!!! Check Hodo and Tracking Efficiencies !!!!!!!!!!!!!!!!!"
echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
echo ""
echo "${El_Track_Eff}"
echo "${Had_Track_Eff}"
echo "HMS Hodo 3/4 Eff - ${HMS_3of4_Eff}"
echo "SHMS Hodo 3/4 Eff - ${SHMS_3of4_Eff}"
echo ""
echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
echo "!!!!!!!!!!!!!!!!!!! If under 95%, check DAQ windows !!!!!!!!!!!!!!!!!!!"
echo "!!!!!!!!!!!!!!!!!!! Look for errors in replay above !!!!!!!!!!!!!!!!!!!"
echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
echo ""

exit 0

