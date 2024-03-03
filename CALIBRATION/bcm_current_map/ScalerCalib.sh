#! /bin/bash

#
# Description:
# ================================================================
# Time-stamp: "2024-02-09 12:05:00 junaid"
# ================================================================
#
# Author: Muhammad junaid  <mjo147@uregina.ca>
# Copyright (c) junaid
#

while getopts 'hs' flag; do
    case "${flag}" in
        h) 
        echo "-------------------------------------------------------------------"
        echo "./add_efficiencies_table.sh -{flags} {variable arguments, see help}"
        echo "-------------------------------------------------------------------"
        echo
        echo "The following flags can be called for the bcm param files"
	echo "    If no flags called arguments are..."
	echo "        coin -> RunList = arg1 RunType=arg2"
	echo "        sing -> RunList = arg1 RunType=arg2 SPEC=arg3 (requires -s flag)"		
        echo "    -h, help"
	echo "    -s, single arm"
        exit 0
        ;;
	s) s_flag='true' ;;
        *) print_usage
        exit 1 ;;
    esac
done

RunList=$2

# Runs script in the ltsep python package that grabs current path enviroment
if [[ ${HOSTNAME} = *"cdaq"* ]]; then
    PATHFILE_INFO=`python3 /home/cdaq/pionLT-2021/hallc_replay_lt/UTIL_PION/bin/python/ltsep/scripts/getPathDict.py $PWD` # The output of this python script is just a comma separated string
elif [[ "${HOSTNAME}" = *"farm"* ]]; then
    PATHFILE_INFO=`python3 /u/home/${USER}/.local/lib/python3.4/site-packages/ltsep/scripts/getPathDict.py $PWD` # The output of this python script is just a comma separated string
fi
#echo $PWD
#echo
#echo $PATHFILE_INFO
#echo
# Split the string we get to individual variables, easier for printing and use later
VOLATILEPATH=`echo ${PATHFILE_INFO} | cut -d ','  -f1` # Cut the string on , delimitter, select field (f) 1, set variable to output of command
ANALYSISPATH=`echo ${PATHFILE_INFO} | cut -d ','  -f2`
HCANAPATH=`echo ${PATHFILE_INFO} | cut -d ','  -f3`
REPLAYPATH=`echo ${PATHFILE_INFO} | cut -d ','  -f4`
UTILPATH=`echo ${PATHFILE_INFO} | cut -d ','  -f5`
PACKAGEPATH=`echo ${PATHFILE_INFO} | cut -d ','  -f6`
OUTPATH=`echo ${PATHFILE_INFO} | cut -d ','  -f7`
ROOTPATH=`echo ${PATHFILE_INFO} | cut -d ','  -f8`
REPORTPATH=`echo ${PATHFILE_INFO} | cut -d ','  -f9`
CUTPATH=`echo ${PATHFILE_INFO} | cut -d ','  -f10`
PARAMPATH=`echo ${PATHFILE_INFO} | cut -d ','  -f11`
SCRIPTPATH=`echo ${PATHFILE_INFO} | cut -d ','  -f12`
ANATYPE=`echo ${PATHFILE_INFO} | cut -d ','  -f13`
USER=`echo ${PATHFILE_INFO} | cut -d ','  -f14`
HOST=`echo ${PATHFILE_INFO} | cut -d ','  -f15`
#echo $ANATYPE

if [[ $s_flag = "true" ]]; then
    RunType=$3
    spec=$(echo "$4" | tr '[:upper:]' '[:lower:]')
    SPEC=$(echo "$spec" | tr '[:lower:]' '[:upper:]')
    if [[ $RunType = "HeePSing" ]]; then
	ROOTPREFIX=PionLT_${SPEC}_HeePSing_replay_production
	inputFile="${REPLAYPATH}/UTIL_BATCH/InputRunLists/eff_runlist/${RunList}"
        OUTPUT="/volatile/hallc/c-pionlt/junaid/ROOTfiles/Analysis/HeeP"
    elif [[ $RunType = "LumiSing" ]]; then
        ROOTPREFIX=PionLT_${SPEC}_Lumi_replay_production
        inputFile="${REPLAYPATH}/UTIL_BATCH/InputRunLists/eff_runlist/${RunList}"
        OUTPUT="/volatile/hallc/c-pionlt/junaid/ROOTfiles/Analysis/Lumi"
    else
        echo "Please Provide RUNTYPE"
    fi    

else
    RunType=$3
    if [[ $RunType = "HeePCoin" ]]; then
        ROOTPREFIX=PionLT_HeePCoin_replay_production
        inputFile="${REPLAYPATH}/UTIL_BATCH/InputRunLists/eff_runlist/${RunList}"
        OUTPUT="/volatile/hallc/c-pionlt/junaid/ROOTfiles/Analysis/HeeP"
    elif [[ $RunType = "LumiCoin" ]]; then
        ROOTPREFIX=PionLT_LumiCoin_replay_production
        inputFile="${REPLAYPATH}/UTIL_BATCH/InputRunLists/eff_runlist/${RunList}"
        OUTPUT="/volatile/hallc/c-pionlt/junaid/ROOTfiles/Analysis/Lumi"
    elif [[ $RunType = "pTRIG6" ]]; then
        ROOTPREFIX=PionLT_Coin_replay_production_pTRIG6
        inputFile="${REPLAYPATH}/UTIL_BATCH/InputRunLists/eff_runlist/${RunList}"
        OUTPUT="/volatile/hallc/c-pionlt/junaid/ROOTfiles/Analysis/pTRIG6"
    elif [[ $RunType = "Prod" ]]; then
        ROOTPREFIX=PionLT_Coin_replay_production
        inputFile="${REPLAYPATH}/UTIL_BATCH/InputRunLists/eff_runlist/${RunList}"
        OUTPUT="/volatile/hallc/c-pionlt/junaid/ROOTfiles/Analysis/PionLT"
#        OUTPUT="/cache/hallc/c-pionlt/analysis/PionLT_Fullreplay_Analysis_Files_Pass1_2021/Analysis/PionLT"
    else
        echo "Please Provide RUNTYPE"
    fi    
fi

cd "${REPLAYPATH}/CALIBRATION/bcm_current_map/"

##Reads in input file##
while IFS='' read -r line || [[ -n "$line" ]]; do
      echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
      echo "Run number read from file: $line"
      echo ""
      root -b -l <<EOF
.L ScalerCalib.C+
.x run.C("$OUTPUT/${ROOTPREFIX}_${line}_-1.root");
.q
EOF
      mv *.param "${REPLAYPATH}/PARAM/HMS/BCM/CALIB"
#      cp *.param "${REPLAYPATH}/PARAM/SHMS/BCM/CALIB"
done < "$inputFile"
