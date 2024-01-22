#! /bin/bash

# Stephen JD Kay - University of Regina - 27/08/21
# Arguments should be run number, type of run and target type
# Anything but the valid options should be ignored and bounced back to the user as a prompt

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
#echo ""
#echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
echo "Please confirm the target type for this run."
echo "It's LD2, what a grand and intoxicating innoccence! How could you be so nieve?"
#while true; do	
#    echo ""
#    read -p "Please type in a target from - LH2 - LD2 - Dummy10cm - Carbon0p5 - AuFoil - Optics1 - Optics2 - CarbonHole - Case sensitive! - or press ctrl-c to exit : " TARGET
#    case $TARGET in
#	'');; # If blank, prompt again
#	'LH2'|'LD2'|'Dummy10cm'|'Carbon0p5'|'AuFoil'|'Optics1'|'Optics2'|'CarbonHole') break;; # If a valid option, break the loop and continue
#    esac
#done
if [[ -z "$4" ]]; then
    NUMEVENTS=-1
fi

if [[ $RUNTYPE == "Prod" ]]; then
    echo "Running production analysis script - ${UTILPATH}/scripts/online_physics/PionLT/pion_prod_replay_analysis_sw.sh"
    eval '"${UTILPATH}/scripts/online_physics/PionLT/pion_prod_replay_analysis_sw.sh" ${RUNNUMBER} ${TARGET} ${NUMEVENTS}' # NH 19/01/22 - Target now an optional argument for production analysis, sets MM range
elif [[ $RUNTYPE == "Lumi" ]]; then
    echo "Running luminosity analysis script - ${UTILPATH}/scripts/luminosity/replay_lumi.sh"
    eval '"${UTILPATH}/scripts/luminosity/replay_lumi.sh" ${RUNNUMBER} ${NUMEVENTS}'
    echo""
    echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
    echo "Ignore SHMS electron tracking runlist print out from lumi replay, trust the run_50k.sh output"
    echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
    echo ""
elif [[ $RUNTYPE == "HeePSing" ]]; then
    echo "Running HeeP Singles analysis script - ${UTILPATH}/scripts/heep/sing_heepYield.sh"
    eval '"${UTILPATH}/scripts/heep/sing_heepYield.sh" hms ${RUNNUMBER} ${NUMEVENTS}'
    eval '"${UTILPATH}/scripts/heep/sing_heepYield.sh" shms ${RUNNUMBER} ${NUMEVENTS}'
elif [[ $RUNTYPE == "HeePCoin" ]]; then
    echo "Running HeeP Coin analysis script - ${UTILPATH}/scripts/heep/coin_heepYield.sh"
    eval '"${UTILPATH}/scripts/heep/coin_heepYield.sh" ${RUNNUMBER} ${NUMEVENTS}'
elif [[ $RUNTYPE == "fADC" ]]; then
    echo "Running fADC Coin analysis script - ${UTILPATH}/scripts/fADC_SIDIS/fADC_Analysis.sh"
    eval '"${UTILPATH}/scripts/fADC_SIDIS/fADC_Analysis.sh" ${RUNNUMBER} ${NUMEVENTS}'
elif [[ $RUNTYPE == "Optics" ]]; then
    echo "Running optics analysis script - "
    eval '"${UTILPATH}/scripts/optics/run_optics.sh" ${RUNNUMBER} ${NUMEVENTS}'
fi
if [[ $RUNTYPE != "Optics" && $NUMEVENTS == -1 ]]; then
    eval '"${UTILPATH}/scripts/runlist/fill_runList.sh" ${RUNNUMBER} ${RUNTYPE} ${TARGET}'
    if [[ $RUNTYPE == "Lumi" ]]; then 
	echo""
	echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
	echo "Ignore SHMS electron tracking runlist print out from lumi replay, trust the run_50k.sh output"
	echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
	echo ""
    fi
else echo "Full replay for HMS and SHMS completed, check output rootfiles for plots"
fi
