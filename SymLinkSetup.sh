#!/bin/bash

# 24/02/21 - Stephen JD Kay - University of Regina
# This script sets up the relevant sim links for running your replay scripts
# It makes the relevant directories in /volatile if they do not exist

echo "Beginning setup of folders and symlinks"
# Set path depending upon hostname. Change or add more as needed  
if [[ "${HOSTNAME}" = *"farm"* ]]; then 
    GROUPPATH="/group/c-kaonlt"
    USERPATH="${GROUPPATH}/USERS/${USER}"
    VOLATILEPATH="/volatile/hallc/c-kaonlt"
    cd "${USERPATH}/hallc_replay_lt"
else echo "Host not recognised, please add relevant pathing for hostname to the script and re-run"
fi
# Set up the hcana sym link and execute setup for this
if [ ! -L "${USERPATH}/hallc_replay_lt/hcana" ]; then
    ln -s "${GROUPPATH}/hcana/hcana" "${USERPATH}/hallc_replay_lt/hcana"
elif [ -L "${USERPATH}/hallc_replay_lt/hcana" ]; then
    if [ ! -e "${USERPATH}/hallc_replay_lt/hcana" ]; then
	echo "hcana sym link exists but is broken, replacing"
	rm "${USERPATH}/hallc_replay_lt/hcana"
	ln -s "${GROUPPATH}/hcana/hcana" "${USERPATH}/hallc_replay_lt/hcana"
    else read -p "hcana sym link exists and isn't broken, update it anyway? <Y/N> " prompt
	if [[ $prompt == "y" || $prompt == "Y" || $prompt == "yes" || $prompt == "Yes" ]]; then
	    rm "${USERPATH}/hallc_replay_lt/hcana"
	    ln -s "${GROUPPATH}/hcana/hcana" "${USERPATH}/hallc_replay_lt/hcana"
	fi
    fi
fi
# Next, need to make a load of directories, check they exist, if not, make em!
if [ ! -d "${VOLATILEPATH}/${USER}" ]; then
    mkdir "${VOLATILEPATH}/${USER}"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/ROOTfiles" ]; then
    mkdir "${VOLATILEPATH}/${USER}/ROOTfiles"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/OUTPUT" ]; then
    mkdir "${VOLATILEPATH}/${USER}/OUTPUT"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/REPORT_OUTPUT" ]; then
    mkdir "${VOLATILEPATH}/${USER}/REPORT_OUTPUT"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/HISTOGRAM" ]; then
    mkdir "${VOLATILEPATH}/${USER}/HISTOGRAMS"
fi

# Now, check if subdirectories exist for ROOTfiles, if not, make them
# Analysis subdirectories
if [ ! -d "${VOLATILEPATH}/${USER}/ROOTfiles/Analysis" ]; then
    mkdir "${VOLATILEPATH}/${USER}/ROOTfiles/Analysis"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/ROOTfiles/Analysis/HeeP" ]; then
    mkdir "${VOLATILEPATH}/${USER}/ROOTfiles/Analysis/HeeP"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/ROOTfiles/Analysis/Lumi" ]; then
    mkdir "${VOLATILEPATH}/${USER}/ROOTfiles/Analysis/Lumi"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/ROOTfiles/Analysis/PionLT" ]; then
    mkdir "${VOLATILEPATH}/${USER}/ROOTfiles/Analysis/PionLT"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/ROOTfiles/Analysis/PID" ]; then
    mkdir "${VOLATILEPATH}/${USER}/ROOTfiles/Analysis/PID"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/ROOTfiles/Analysis/Optics" ]; then
    mkdir "${VOLATILEPATH}/${USER}/ROOTfiles/Analysis/Optics"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/ROOTfiles/Analysis/General" ]; then
    mkdir "${VOLATILEPATH}/${USER}/ROOTfiles/Analysis/General"
fi
# Calib sub directories
if [ ! -d "${VOLATILEPATH}/${USER}/ROOTfiles/Calib" ]; then
    mkdir "${VOLATILEPATH}/${USER}/ROOTfiles/Calib"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/ROOTfiles/Calib/Hodo" ]; then
    mkdir "${VOLATILEPATH}/${USER}/ROOTfiles/Calib/Hodo"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/ROOTfiles/Calib/DC" ]; then
    mkdir "${VOLATILEPATH}/${USER}/ROOTfiles/Calib/DC"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/ROOTfiles/Calib/Cal" ]; then
    mkdir "${VOLATILEPATH}/${USER}/ROOTfiles/Calib/Cal"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/ROOTfiles/Calib/HGC" ]; then
    mkdir "${VOLATILEPATH}/${USER}/ROOTfiles/Calib/HGC"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/ROOTfiles/Calib/Aero" ]; then
    mkdir "${VOLATILEPATH}/${USER}/ROOTfiles/Calib/Aero"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/ROOTfiles/Calib/NGC" ]; then
    mkdir "${VOLATILEPATH}/${USER}/ROOTfiles/Calib/NGC"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/ROOTfiles/Calib/General" ]; then
    mkdir "${VOLATILEPATH}/${USER}/ROOTfiles/Calib/General"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/ROOTfiles/Calib/Timing" ]; then
    mkdir "${VOLATILEPATH}/${USER}/ROOTfiles/Calib/Timing"
fi
# Scalers ROOTfiles directory
if [ ! -d "${VOLATILEPATH}/${USER}/ROOTfiles/Scalers" ]; then
    mkdir "${VOLATILEPATH}/${USER}/ROOTfiles/Scalers"
fi
# Now, check if subdirectories exist for OUTPUT, if not, make them
# Analysis subdirectories
if [ ! -d "${VOLATILEPATH}/${USER}/OUTPUT/Analysis" ]; then
    mkdir "${VOLATILEPATH}/${USER}/OUTPUT/Analysis"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/OUTPUT/Analysis/HeeP" ]; then
    mkdir "${VOLATILEPATH}/${USER}/OUTPUT/Analysis/HeeP"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/OUTPUT/Analysis/Lumi" ]; then
    mkdir "${VOLATILEPATH}/${USER}/OUTPUT/Analysis/Lumi"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/OUTPUT/Analysis/PionLT" ]; then
    mkdir "${VOLATILEPATH}/${USER}/OUTPUT/Analysis/PionLT"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/OUTPUT/Analysis/PID" ]; then
    mkdir "${VOLATILEPATH}/${USER}/OUTPUT/Analysis/PID"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/OUTPUT/Analysis/Optics" ]; then
    mkdir "${VOLATILEPATH}/${USER}/OUTPUT/Analysis/Optics"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/OUTPUT/Analysis/General" ]; then
    mkdir "${VOLATILEPATH}/${USER}/OUTPUT/Analysis/General"
fi
# Calib sub directories
if [ ! -d "${VOLATILEPATH}/${USER}/OUTPUT/Calib" ]; then
    mkdir "${VOLATILEPATH}/${USER}/OUTPUT/Calib"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/OUTPUT/Calib/Hodo" ]; then
    mkdir "${VOLATILEPATH}/${USER}/OUTPUT/Calib/Hodo"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/OUTPUT/Calib/DC" ]; then
    mkdir "${VOLATILEPATH}/${USER}/OUTPUT/Calib/DC"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/OUTPUT/Calib/Cal" ]; then
    mkdir "${VOLATILEPATH}/${USER}/OUTPUT/Calib/Cal"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/OUTPUT/Calib/HGC" ]; then
    mkdir "${VOLATILEPATH}/${USER}/OUTPUT/Calib/HGC"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/OUTPUT/Calib/Aero" ]; then
    mkdir "${VOLATILEPATH}/${USER}/OUTPUT/Calib/Aero"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/OUTPUT/Calib/NGC" ]; then
    mkdir "${VOLATILEPATH}/${USER}/OUTPUT/Calib/NGC"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/OUTPUT/Calib/General" ]; then
    mkdir "${VOLATILEPATH}/${USER}/OUTPUT/Calib/General"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/OUTPUT/Calib/Timing" ]; then
    mkdir "${VOLATILEPATH}/${USER}/OUTPUT/Calib/Timing"
fi
# Scalers OUTPUT directory
if [ ! -d "${VOLATILEPATH}/${USER}/OUTPUT/Scalers" ]; then
    mkdir "${VOLATILEPATH}/${USER}/OUTPUT/Scalers"
fi
# Now, check if subdirectories exist for REPORT_OUTPUT, if not, make them
# Analysis subdirectories
if [ ! -d "${VOLATILEPATH}/${USER}/REPORT_OUTPUT/Analysis" ]; then
    mkdir "${VOLATILEPATH}/${USER}/REPORT_OUTPUT/Analysis"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/REPORT_OUTPUT/Analysis/HeeP" ]; then
    mkdir "${VOLATILEPATH}/${USER}/REPORT_OUTPUT/Analysis/HeeP"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/REPORT_OUTPUT/Analysis/Lumi" ]; then
    mkdir "${VOLATILEPATH}/${USER}/REPORT_OUTPUT/Analysis/Lumi"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/REPORT_OUTPUT/Analysis/PionLT" ]; then
    mkdir "${VOLATILEPATH}/${USER}/REPORT_OUTPUT/Analysis/PionLT"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/REPORT_OUTPUT/Analysis/PID" ]; then
    mkdir "${VOLATILEPATH}/${USER}/REPORT_OUTPUT/Analysis/PID"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/REPORT_OUTPUT/Analysis/Optics" ]; then
    mkdir "${VOLATILEPATH}/${USER}/REPORT_OUTPUT/Analysis/Optics"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/REPORT_OUTPUT/Analysis/General" ]; then
    mkdir "${VOLATILEPATH}/${USER}/REPORT_OUTPUT/Analysis/General"
fi
# Calib sub directories
if [ ! -d "${VOLATILEPATH}/${USER}/REPORT_OUTPUT/Calib" ]; then
    mkdir "${VOLATILEPATH}/${USER}/REPORT_OUTPUT/Calib"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/REPORT_OUTPUT/Calib/Hodo" ]; then
    mkdir "${VOLATILEPATH}/${USER}/REPORT_OUTPUT/Calib/Hodo"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/REPORT_OUTPUT/Calib/DC" ]; then
    mkdir "${VOLATILEPATH}/${USER}/REPORT_OUTPUT/Calib/DC"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/REPORT_OUTPUT/Calib/Cal" ]; then
    mkdir "${VOLATILEPATH}/${USER}/REPORT_OUTPUT/Calib/Cal"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/REPORT_OUTPUT/Calib/HGC" ]; then
    mkdir "${VOLATILEPATH}/${USER}/REPORT_OUTPUT/Calib/HGC"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/REPORT_OUTPUT/Calib/Aero" ]; then
    mkdir "${VOLATILEPATH}/${USER}/REPORT_OUTPUT/Calib/Aero"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/REPORT_OUTPUT/Calib/NGC" ]; then
    mkdir "${VOLATILEPATH}/${USER}/REPORT_OUTPUT/Calib/NGC"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/REPORT_OUTPUT/Calib/General" ]; then
    mkdir "${VOLATILEPATH}/${USER}/REPORT_OUTPUT/Calib/General"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/REPORT_OUTPUT/Calib/Timing" ]; then
    mkdir "${VOLATILEPATH}/${USER}/REPORT_OUTPUT/Calib/Timing"
fi
# Scalers REPORT_OUTPUT directory
if [ ! -d "${VOLATILEPATH}/${USER}/REPORT_OUTPUT/Scalers" ]; then
    mkdir "${VOLATILEPATH}/${USER}/REPORT_OUTPUT/Scalers"
fi
# Now, check if subdirectories exist for HISTOGRAMS, if not, make them
# Analysis subdirectories
if [ ! -d "${VOLATILEPATH}/${USER}/HISTOGRAMS/Analysis" ]; then
    mkdir "${VOLATILEPATH}/${USER}/HISTOGRAMS/Analysis"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/HISTOGRAMS/Analysis/HeeP" ]; then
    mkdir "${VOLATILEPATH}/${USER}/HISTOGRAMS/Analysis/HeeP"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/HISTOGRAMS/Analysis/Lumi" ]; then
    mkdir "${VOLATILEPATH}/${USER}/HISTOGRAMS/Analysis/Lumi"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/HISTOGRAMS/Analysis/PionLT" ]; then
    mkdir "${VOLATILEPATH}/${USER}/HISTOGRAMS/Analysis/PionLT"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/HISTOGRAMS/Analysis/PID" ]; then
    mkdir "${VOLATILEPATH}/${USER}/HISTOGRAMS/Analysis/PID"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/HISTOGRAMS/Analysis/Optics" ]; then
    mkdir "${VOLATILEPATH}/${USER}/HISTOGRAMS/Analysis/Optics"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/HISTOGRAMS/Analysis/General" ]; then
    mkdir "${VOLATILEPATH}/${USER}/HISTOGRAMS/Analysis/General"
fi
# Calib sub directories
if [ ! -d "${VOLATILEPATH}/${USER}/HISTOGRAMS/Calib" ]; then
    mkdir "${VOLATILEPATH}/${USER}/HISTOGRAMS/Calib"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/HISTOGRAMS/Calib/Hodo" ]; then
    mkdir "${VOLATILEPATH}/${USER}/HISTOGRAMS/Calib/Hodo"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/HISTOGRAMS/Calib/DC" ]; then
    mkdir "${VOLATILEPATH}/${USER}/HISTOGRAMS/Calib/DC"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/HISTOGRAMS/Calib/Cal" ]; then
    mkdir "${VOLATILEPATH}/${USER}/HISTOGRAMS/Calib/Cal"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/HISTOGRAMS/Calib/HGC" ]; then
    mkdir "${VOLATILEPATH}/${USER}/HISTOGRAMS/Calib/HGC"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/HISTOGRAMS/Calib/Aero" ]; then
    mkdir "${VOLATILEPATH}/${USER}/HISTOGRAMS/Calib/Aero"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/HISTOGRAMS/Calib/NGC" ]; then
    mkdir "${VOLATILEPATH}/${USER}/HISTOGRAMS/Calib/NGC"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/HISTOGRAMS/Calib/General" ]; then
    mkdir "${VOLATILEPATH}/${USER}/HISTOGRAMS/Calib/General"
fi
if [ ! -d "${VOLATILEPATH}/${USER}/HISTOGRAMS/Calib/Timing" ]; then
    mkdir "${VOLATILEPATH}/${USER}/HISTOGRAMS/Calib/Timing"
fi
# Scalers HISTOGRAMS directory
if [ ! -d "${VOLATILEPATH}/${USER}/HISTOGRAMS/Scalers" ]; then
    mkdir "${VOLATILEPATH}/${USER}/HISTOGRAMS/Scalers"
fi
# Make a raw data directory on volatile
if [ ! -d "${VOLATILEPATH}/${USER}/raw" ]; then
    mkdir "${VOLATILEPATH}/${USER}/raw"
fi

# Directories now created, make the sym links
echo "Directories have been created in volatile if they did not already exists, sym links will now be made for - "
echo ""
echo "${VOLATILEPATH}/${USER}/ROOTfiles/ - ROOTfiles"
echo "${VOLATILEPATH}/${USER}/OUTPUT/ - OUTPUT"
echo "${VOLATILEPATH}/${USER}/REPORT_OUTPUT/ - REPORT_OUTPUT"
echo "${VOLATILEPATH}/${USER}/HISTOGRAMS/ - HISTOGRAMS"
echo "/cache/hallc/spring17/raw - raw"
echo "/cache/hallc/spring17/raw - cache"
echo "${VOLATILEPATH}/${USER}/raw - raw_volatile"
echo""
read -p "Proceed with sym link setup setup? <Y/N> " prompt2
if [[ $prompt2 == "y" || $prompt2 == "Y" || $prompt2 == "yes" || $prompt2 == "Yes" ]]; then
    echo "Creating sym links"
else 
    echo "Please update script with desired changes to sym links and re-run if desired"
    exit 1
fi
# Each loop checks if the link exists, if it doesn't, make it
# If it DOES, check it's not broken, if broken, replace, if not, just print that it exists

if [ ! -L "${USERPATH}/hallc_replay_lt/ROOTfiles" ]; then
    ln -s "${VOLATILEPATH}/${USER}/ROOTfiles/" "${USERPATH}/hallc_replay_lt/ROOTfiles"
elif [ -L "${USERPATH}/hallc_replay_lt/ROOTfiles" ]; then
    if [ ! -e "${USERPATH}/hallc_replay_lt/ROOTfiles" ]; then
	echo "ROOTfiles sym link exits but is broken, replacing"
	rm "${USERPATH}/hallc_replay_lt/ROOTfiles"
	ln -s "${VOLATILEPATH}/${USER}/ROOTfiles/" "${USERPATH}/hallc_replay_lt/ROOTfiles"
    else echo "${USERPATH}/hallc_replay_lt/ROOTfiles sym link already exists and not broken"
    fi
fi

if [ ! -L "${USERPATH}/hallc_replay_lt/OUTPUT" ]; then
    ln -s "${VOLATILEPATH}/${USER}/OUTPUT/" "${USERPATH}/hallc_replay_lt/OUTPUT"
elif [ -L "${USERPATH}/hallc_replay_lt/OUTPUT" ]; then
    if [ ! -e "${USERPATH}/hallc_replay_lt/OUTPUT" ]; then
	echo "OUTPUT sym link exits but is broken, replacing"
	rm "${USERPATH}/hallc_replay_lt/OUTPUT"
	ln -s "${VOLATILEPATH}/${USER}/OUTPUT/" "${USERPATH}/hallc_replay_lt/OUTPUT"
    else echo "${USERPATH}/hallc_replay_lt/OUTPUT sym link already exists and not broken"
    fi
fi

if [ ! -L "${USERPATH}/hallc_replay_lt/REPORT_OUTPUT" ]; then
    ln -s "${VOLATILEPATH}/${USER}/REPORT_OUTPUT/" "${USERPATH}/hallc_replay_lt/REPORT_OUTPUT"
elif [ -L "${USERPATH}/hallc_replay_lt/REPORT_OUTPUT" ]; then
    if [ ! -e "${USERPATH}/hallc_replay_lt/REPORT_OUTPUT" ]; then
	echo "REPORT_OUTPUT sym link exits but is broken, replacing"
	rm "${USERPATH}/hallc_replay_lt/REPORT_OUTPUT"
	ln -s "${VOLATILEPATH}/${USER}/REPORT_OUTPUT/" "${USERPATH}/hallc_replay_lt/REPORT_OUTPUT"
    else echo "${USERPATH}/hallc_replay_lt/REPORT_OUTPUT sym link already exists and not broken"
    fi
fi

if [ ! -L "${USERPATH}/hallc_replay_lt/HISTOGRAMS" ]; then
    ln -s "${VOLATILEPATH}/${USER}/HISTOGRAMS/" "${USERPATH}/hallc_replay_lt/HISTOGRAMS"
elif [ -L "${USERPATH}/hallc_replay_lt/HISTOGRAMS" ]; then
    if [ ! -e "${USERPATH}/hallc_replay_lt/HISTOGRAMS" ]; then
	echo "HISTOGRAMS sym link exits but is broken, replacing"
	rm "${USERPATH}/hallc_replay_lt/HISTOGRAMS"
	ln -s "${VOLATILEPATH}/${USER}/HISTOGRAMS/" "${USERPATH}/hallc_replay_lt/HISTOGRAMS"
    else echo "${USERPATH}/hallc_replay_lt/HISTOGRAMS sym link already exists and not broken"
    fi
fi

if [ ! -L "${USERPATH}/hallc_replay_lt/raw_volatile" ]; then
    ln -s "${VOLATILEPATH}/${USER}/raw" "${USERPATH}/hallc_replay_lt/raw_volatile"
elif [ -L "${USERPATH}/hallc_replay_lt/raw_volatile" ]; then
    if [ ! -e "${USERPATH}/hallc_replay_lt/raw_volatile" ]; then
	echo "raw_volatile sym link exits but is broken, replacing"
	rm "${USERPATH}/hallc_replay_lt/raw_volatile"
	ln -s "${VOLATILEPATH}/${USER}/raw" "${USERPATH}/hallc_replay_lt/raw_volatile"
    else echo "${USERPATH}/hallc_replay_lt/raw_volatile sym link already exists and not broken"
    fi
fi

if [ ! -L "${USERPATH}/hallc_replay_lt/raw" ]; then
    ln -s "/cache/hallc/spring17/raw" "${USERPATH}/hallc_replay_lt/raw"
elif [ -L "${USERPATH}/hallc_replay_lt/raw" ]; then
    if [ ! -e "${USERPATH}/hallc_replay_lt/raw" ]; then
	echo "raw sym link exits but is broken, replacing"
	rm "${USERPATH}/hallc_replay_lt/raw"
	ln -s "/cache/hallc/spring17/raw" "${USERPATH}/hallc_replay_lt/raw"
    else echo "${USERPATH}/hallc_replay_lt/raw sym link already exists and not broken"
    fi
fi

if [ ! -L "${USERPATH}/hallc_replay_lt/cache" ]; then
    ln -s "/cache/hallc/spring17/raw" "${USERPATH}/hallc_replay_lt/cache"
elif [ -L "${USERPATH}/hallc_replay_lt/cache" ]; then
    if [ ! -e "${USERPATH}/hallc_replay_lt/cache" ]; then
	echo "cache sym link exits but is broken, replacing"
	rm "${USERPATH}/hallc_replay_lt/cache"
	ln -s "/cache/hallc/spring17/raw" "${USERPATH}/hallc_replay_lt/cache"
    else echo "${USERPATH}/hallc_replay_lt/cache sym link already exists and not broken"
    fi
fi

echo ""
echo "Directories and sym links for hallc_replay_lt now setup"
echo "Setting up hcana path too"
# Set hcana with setup script
exec "${GROUPPATH}/hcana/setup.csh"

exit 0
