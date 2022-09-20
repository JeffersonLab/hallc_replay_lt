#! /bin/bash

# Stephen JD Kay - University of Regina - 13/07/22 - See .old version for original comments

# Nathan Heinrich - University of Regina - 24/08/22
# I have updated this so that it only does 1 replay.
# SJDK - 27/08/22 - Added some extra print outs to clarify expected inputs for the user

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

lastRun=$( \
     ls raw/shms_all_*.dat raw/../raw.copiedtotape/shms_all_*.dat LUSTER_LINKS/cache/shms_all_*.dat -R 2>/dev/null | perl -ne 'if(/0*(\d+)/) {print "$1\n"}' | sort -n | tail -1 \
     #ls raw/shms_all_*.dat raw/../raw.copiedtotape/shms_all_*.dat -R 2>/dev/null | perl -ne 'if(/0*(\d+)/) {print "$1\n"}' | sort -n | tail -1 \
    #cache was down so I made a version that does not check it - NH
 )

echo ""
echo "Starting physics analysis of PionLT data"
echo "Arguments are run number and run type "
echo ""
echo "Run number must be a positive integer value"
echo "Run number defaults to latest run of no argument provided"
echo "Run type must be one of - Prod - Lumi - HeePSing - HeePCoin - fADC - Optics - Case sensitive!"
echo "Run type defualts to Prod, which will NOT work for HeeP Singles!!!"
RUNNUMBER=$1
RUNTYPE=$2
NUMEVENTS=$3

#echo "${lastRun}"
if [ -z "$1" ]; then # If no run number provided, default to latest run
    RUNNUMBER=$lastRun
fi

#echo "${RUNNUMBER}"
if [[ ! "$RUNNUMBER" =~ ^-?[0-9]+$ ]]; then # Check an argument was provided and that it is a positive integer, if not, prompt for one
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

if [[ -z "$2" ]]; then # If no arguments, default to production
    RUNTYPE="Prod"
fi
if [[ ! "$RUNTYPE" =~ Prod|Lumi|HeePSing|HeePCoin|fADC|Optics ]]; then # Check the 2nd argument was provided and that it's one of the valid options
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
echo ""

if [[ -z "$3" ]]; then
    NUMEVENTS=50000
fi

eval "$REPLAYPATH/hcana -l -q \"UTIL_PION/scripts/replay/PionLT/replay_production_coin_50k.C($RUNNUMBER,$NUMEVENTS)\""
if [ -f "${REPLAYPATH}/ROOTfiles/Analysis/50k/Pion_coin_replay_production_${RUNNUMBER}_latest.root" ]; then
    echo "Removing old soft link to rootfile."
    eval "rm ${REPLAYPATH}/ROOTfiles/Analysis/50k/Pion_coin_replay_production_${RUNNUMBER}_latest.root"
fi
eval "ln -sf ${REPLAYPATH}/ROOTfiles/Analysis/50k/Pion_coin_replay_production_${RUNNUMBER}_${NUMEVENTS}.root ${REPLAYPATH}/ROOTfiles/Analysis/50k/Pion_coin_replay_production_${RUNNUMBER}_latest.root"

if [[ $RUNTYPE == "Prod" || $RUNTYPE == "fADC" ]]; then
    REPORT_FILE="${REPLAYPATH}/REPORT_OUTPUT/Analysis/PionLT/Pion_replay_coin_production_${RUNNUMBER}_${NUMEVENTS}.report"
    El_Track_Eff=$(sed -n 80p $REPORT_FILE)
    Had_Track_Eff=$(sed -n 82p $REPORT_FILE)
    SHMS_Pi_Track_EFF=$(sed -n 86p $REPORT_FILE)
    HMS_3of4_Eff=$(sed -n 289p $REPORT_FILE)
    SHMS_3of4_Eff=$(sed -n 274p $REPORT_FILE)
elif [[ $RUNTYPE == "HeePSing" || $RUNTYPE == "Lumi" ]]; then # HeePSingles and Lumi get analysed in the same way effectively
    # SJDK - 27/08/22 - I'm not sure we actually need two replays for the HeePSingles either, we could just add the electron tracking efficiency to the 50k replay output and then grab that instead in this loop here
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
echo "${SHMS_Pi_Track_EFF}"
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

eval "./online -f onlineGUI/CONFIG/COIN/PRODUCTION/hms_coin_production.cfg -r ${RUNNUMBER}"
eval "./online -f onlineGUI/CONFIG/COIN/PRODUCTION/hms_coin_production_expert.cfg -r ${RUNNUMBER} -P"
eval "mv ${REPLAYPATH}/hms_coin_production_expert_${RUNNUMBER}.pdf ${REPLAYPATH}/HISTOGRAMS/Analysis/50k/PDF/"

echo ""
echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
echo "!!!!!!!!!!!!!!!! Check Hodo and Tracking Efficiencies !!!!!!!!!!!!!!!!!"
echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
echo ""
echo "${El_Track_Eff}"
echo "${Had_Track_Eff}"
echo "${SHMS_Pi_Track_EFF}"
echo "HMS Hodo 3/4 Eff - ${HMS_3of4_Eff}"
echo "SHMS Hodo 3/4 Eff - ${SHMS_3of4_Eff}"
echo ""
echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
echo "!!!!!!!!!!!!!!!!!!! If under 95%, check DAQ windows !!!!!!!!!!!!!!!!!!!"
echo "!!!!!!!!!!!!!!!!!!! Look for errors in replay above !!!!!!!!!!!!!!!!!!!"
echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"

eval "./online -f onlineGUI/CONFIG/COIN/PRODUCTION/shms_coin_production.cfg -r ${RUNNUMBER}"
eval "./online -f onlineGUI/CONFIG/COIN/PRODUCTION/shms_coin_production_expert.cfg -r ${RUNNUMBER} -P"
eval "mv ${REPLAYPATH}/shms_coin_production_expert_${RUNNUMBER}.pdf ${REPLAYPATH}/HISTOGRAMS/Analysis/50k/PDF/"

echo ""
echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
echo "!!!!!!!!!!!!!!!! Check Hodo and Tracking Efficiencies !!!!!!!!!!!!!!!!!"
echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
echo ""
echo "${El_Track_Eff}"
echo "${Had_Track_Eff}"
echo "${SHMS_Pi_Track_EFF}"
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

