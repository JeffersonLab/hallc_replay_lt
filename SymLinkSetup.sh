#!/bin/bash

# 10/08/21 - Stephen JD Kay - University of Regina
# This script sets up the relevant sym links for running your replay scripts
# It makes the relevant directories in the ROOTfiles and analysis areas if they don't exist
# This version is specific for cdaq

ANALYSISPATH="/home/cdaq/hallc-online"
OUTPUTPATH="/net/cdaq/cdaql1data/cdaq/hallc-online-pionLT"
CACHEPATH="/cache/hallc/c-pionlt/raw"
RAWPATH="/net/cdaq/cdaql1data/coda/data/raw"
RAWCOPIEDPATH="/net/cdaq/cdaql1data/coda/data/raw.copiedtotape"

# Set up the hcana sym link and execute setup for this
if [ ! -L "${ANALYSISPATH}/hallc_replay_lt/hcana" ]; then
    ln -s "${ANALYSISPATH}/hcana/hcana" "${ANALYSISPATH}/hallc_replay_lt/hcana"
elif [ -L "${ANALYSISPATH}/hallc_replay_lt/hcana" ]; then
    if [ ! -e "${ANALYSISPATH}/hallc_replay_lt/hcana" ]; then
	echo "hcana sym link exists but is broken, replacing"
	rm "${ANALYSISPATH}/hallc_replay_lt/hcana"
	ln -s "${ANALYSISPATH}/hcana/hcana" "${ANALYSISPATH}/hallc_replay_lt/hcana"
    else read -p "hcana sym link exists and isn't broken, update it anyway? <Y/N> " prompt
	if [[ $prompt == "y" || $prompt == "Y" || $prompt == "yes" || $prompt == "Yes" ]]; then
	    rm "${ANALYSISPATH}/hallc_replay_lt/hcana"
	    ln -s "${ANALYSISPATH}/hcana/hcana" "${ANALYSISPATH}/hallc_replay_lt/hcana"
	fi
    fi
fi
# Next, need to make a load of directories, check they exist, if not, make em!
if [ ! -d "${OUTPUTPATH}/ROOTfiles" ]; then
    mkdir "${OUTPUTPATH}/ROOTfiles"
fi
if [ ! -d "${OUTPUTPATH}/OUTPUT" ]; then
    mkdir "${OUTPUTPATH}/OUTPUT"
fi
if [ ! -d "${OUTPUTPATH}/MON_OUTPUT" ]; then
    mkdir "${OUTPUTPATH}/MON_OUTPUT"
fi
if [ ! -d "${OUTPUTPATH}/REPORT_OUTPUT" ]; then
    mkdir "${OUTPUTPATH}/REPORT_OUTPUT"
fi
if [ ! -d "${OUTPUTPATH}/HISTOGRAMS" ]; then
    mkdir "${OUTPUTPATH}/HISTOGRAMS"
fi

# Now, check if subdirectories exist for ROOTfiles, if not, make them
# Analysis subdirectories
if [ ! -d "${OUTPUTPATH}/ROOTfiles/Analysis" ]; then
    mkdir "${OUTPUTPATH}/ROOTfiles/Analysis"
fi
if [ ! -d "${OUTPUTPATH}/ROOTfiles/Analysis/HeeP" ]; then
    mkdir "${OUTPUTPATH}/ROOTfiles/Analysis/HeeP"
fi
if [ ! -d "${OUTPUTPATH}/ROOTfiles/Analysis/Lumi" ]; then
    mkdir "${OUTPUTPATH}/ROOTfiles/Analysis/Lumi"
fi
if [ ! -d "${OUTPUTPATH}/ROOTfiles/Analysis/PionLT" ]; then
    mkdir "${OUTPUTPATH}/ROOTfiles/Analysis/PionLT"
fi
if [ ! -d "${OUTPUTPATH}/ROOTfiles/Analysis/PID" ]; then
    mkdir "${OUTPUTPATH}/ROOTfiles/Analysis/PID"
fi
if [ ! -d "${OUTPUTPATH}/ROOTfiles/Analysis/Optics" ]; then
    mkdir "${OUTPUTPATH}/ROOTfiles/Analysis/Optics"
fi
if [ ! -d "${OUTPUTPATH}/ROOTfiles/Analysis/General" ]; then
    mkdir "${OUTPUTPATH}/ROOTfiles/Analysis/General"
fi
# Calib sub directories
if [ ! -d "${OUTPUTPATH}/ROOTfiles/Calib" ]; then
    mkdir "${OUTPUTPATH}/ROOTfiles/Calib"
fi
if [ ! -d "${OUTPUTPATH}/ROOTfiles/Calib/Hodo" ]; then
    mkdir "${OUTPUTPATH}/ROOTfiles/Calib/Hodo"
fi
if [ ! -d "${OUTPUTPATH}/ROOTfiles/Calib/DC" ]; then
    mkdir "${OUTPUTPATH}/ROOTfiles/Calib/DC"
fi
if [ ! -d "${OUTPUTPATH}/ROOTfiles/Calib/Cal" ]; then
    mkdir "${OUTPUTPATH}/ROOTfiles/Calib/Cal"
fi
if [ ! -d "${OUTPUTPATH}/ROOTfiles/Calib/HGC" ]; then
    mkdir "${OUTPUTPATH}/ROOTfiles/Calib/HGC"
fi
if [ ! -d "${OUTPUTPATH}/ROOTfiles/Calib/Aero" ]; then
    mkdir "${OUTPUTPATH}/ROOTfiles/Calib/Aero"
fi
if [ ! -d "${OUTPUTPATH}/ROOTfiles/Calib/NGC" ]; then
    mkdir "${OUTPUTPATH}/ROOTfiles/Calib/NGC"
fi
if [ ! -d "${OUTPUTPATH}/ROOTfiles/Calib/General" ]; then
    mkdir "${OUTPUTPATH}/ROOTfiles/Calib/General"
fi
if [ ! -d "${OUTPUTPATH}/ROOTfiles/Calib/Timing" ]; then
    mkdir "${OUTPUTPATH}/ROOTfiles/Calib/Timing"
fi
# Scalers ROOTfiles directory
if [ ! -d "${OUTPUTPATH}/ROOTfiles/Scalers" ]; then
    mkdir "${OUTPUTPATH}/ROOTfiles/Scalers"
fi
# Now, check if subdirectories exist for OUTPUT, if not, make them
# Analysis subdirectories
if [ ! -d "${OUTPUTPATH}/OUTPUT/Analysis" ]; then
    mkdir "${OUTPUTPATH}/OUTPUT/Analysis"
fi
if [ ! -d "${OUTPUTPATH}/OUTPUT/Analysis/HeeP" ]; then
    mkdir "${OUTPUTPATH}/OUTPUT/Analysis/HeeP"
fi
if [ ! -d "${OUTPUTPATH}/OUTPUT/Analysis/Lumi" ]; then
    mkdir "${OUTPUTPATH}/OUTPUT/Analysis/Lumi"
fi
if [ ! -d "${OUTPUTPATH}/OUTPUT/Analysis/PionLT" ]; then
    mkdir "${OUTPUTPATH}/OUTPUT/Analysis/PionLT"
fi
if [ ! -d "${OUTPUTPATH}/OUTPUT/Analysis/PID" ]; then
    mkdir "${OUTPUTPATH}/OUTPUT/Analysis/PID"
fi
if [ ! -d "${OUTPUTPATH}/OUTPUT/Analysis/Optics" ]; then
    mkdir "${OUTPUTPATH}/OUTPUT/Analysis/Optics"
fi
if [ ! -d "${OUTPUTPATH}/OUTPUT/Analysis/General" ]; then
    mkdir "${OUTPUTPATH}/OUTPUT/Analysis/General"
fi
# Calib sub directories
if [ ! -d "${OUTPUTPATH}/OUTPUT/Calib" ]; then
    mkdir "${OUTPUTPATH}/OUTPUT/Calib"
fi
if [ ! -d "${OUTPUTPATH}/OUTPUT/Calib/Hodo" ]; then
    mkdir "${OUTPUTPATH}/OUTPUT/Calib/Hodo"
fi
if [ ! -d "${OUTPUTPATH}/OUTPUT/Calib/DC" ]; then
    mkdir "${OUTPUTPATH}/OUTPUT/Calib/DC"
fi
if [ ! -d "${OUTPUTPATH}/OUTPUT/Calib/Cal" ]; then
    mkdir "${OUTPUTPATH}/OUTPUT/Calib/Cal"
fi
if [ ! -d "${OUTPUTPATH}/OUTPUT/Calib/HGC" ]; then
    mkdir "${OUTPUTPATH}/OUTPUT/Calib/HGC"
fi
if [ ! -d "${OUTPUTPATH}/OUTPUT/Calib/Aero" ]; then
    mkdir "${OUTPUTPATH}/OUTPUT/Calib/Aero"
fi
if [ ! -d "${OUTPUTPATH}/OUTPUT/Calib/NGC" ]; then
    mkdir "${OUTPUTPATH}/OUTPUT/Calib/NGC"
fi
if [ ! -d "${OUTPUTPATH}/OUTPUT/Calib/General" ]; then
    mkdir "${OUTPUTPATH}/OUTPUT/Calib/General"
fi
if [ ! -d "${OUTPUTPATH}/OUTPUT/Calib/Timing" ]; then
    mkdir "${OUTPUTPATH}/OUTPUT/Calib/Timing"
fi
# Scalers OUTPUT directory
if [ ! -d "${OUTPUTPATH}/OUTPUT/Scalers" ]; then
    mkdir "${OUTPUTPATH}/OUTPUT/Scalers"
fi
# Now, check if subdirectories exist for REPORT_OUTPUT, if not, make them
# Analysis subdirectories
if [ ! -d "${OUTPUTPATH}/REPORT_OUTPUT/Analysis" ]; then
    mkdir "${OUTPUTPATH}/REPORT_OUTPUT/Analysis"
fi
if [ ! -d "${OUTPUTPATH}/REPORT_OUTPUT/Analysis/HeeP" ]; then
    mkdir "${OUTPUTPATH}/REPORT_OUTPUT/Analysis/HeeP"
fi
if [ ! -d "${OUTPUTPATH}/REPORT_OUTPUT/Analysis/Lumi" ]; then
    mkdir "${OUTPUTPATH}/REPORT_OUTPUT/Analysis/Lumi"
fi
if [ ! -d "${OUTPUTPATH}/REPORT_OUTPUT/Analysis/PionLT" ]; then
    mkdir "${OUTPUTPATH}/REPORT_OUTPUT/Analysis/PionLT"
fi
if [ ! -d "${OUTPUTPATH}/REPORT_OUTPUT/Analysis/PID" ]; then
    mkdir "${OUTPUTPATH}/REPORT_OUTPUT/Analysis/PID"
fi
if [ ! -d "${OUTPUTPATH}/REPORT_OUTPUT/Analysis/Optics" ]; then
    mkdir "${OUTPUTPATH}/REPORT_OUTPUT/Analysis/Optics"
fi
if [ ! -d "${OUTPUTPATH}/REPORT_OUTPUT/Analysis/General" ]; then
    mkdir "${OUTPUTPATH}/REPORT_OUTPUT/Analysis/General"
fi
# Calib sub directories
if [ ! -d "${OUTPUTPATH}/REPORT_OUTPUT/Calib" ]; then
    mkdir "${OUTPUTPATH}/REPORT_OUTPUT/Calib"
fi
if [ ! -d "${OUTPUTPATH}/REPORT_OUTPUT/Calib/Hodo" ]; then
    mkdir "${OUTPUTPATH}/REPORT_OUTPUT/Calib/Hodo"
fi
if [ ! -d "${OUTPUTPATH}/REPORT_OUTPUT/Calib/DC" ]; then
    mkdir "${OUTPUTPATH}/REPORT_OUTPUT/Calib/DC"
fi
if [ ! -d "${OUTPUTPATH}/REPORT_OUTPUT/Calib/Cal" ]; then
    mkdir "${OUTPUTPATH}/REPORT_OUTPUT/Calib/Cal"
fi
if [ ! -d "${OUTPUTPATH}/REPORT_OUTPUT/Calib/HGC" ]; then
    mkdir "${OUTPUTPATH}/REPORT_OUTPUT/Calib/HGC"
fi
if [ ! -d "${OUTPUTPATH}/REPORT_OUTPUT/Calib/Aero" ]; then
    mkdir "${OUTPUTPATH}/REPORT_OUTPUT/Calib/Aero"
fi
if [ ! -d "${OUTPUTPATH}/REPORT_OUTPUT/Calib/NGC" ]; then
    mkdir "${OUTPUTPATH}/REPORT_OUTPUT/Calib/NGC"
fi
if [ ! -d "${OUTPUTPATH}/REPORT_OUTPUT/Calib/General" ]; then
    mkdir "${OUTPUTPATH}/REPORT_OUTPUT/Calib/General"
fi
if [ ! -d "${OUTPUTPATH}/REPORT_OUTPUT/Calib/Timing" ]; then
    mkdir "${OUTPUTPATH}/REPORT_OUTPUT/Calib/Timing"
fi
# Scalers REPORT_OUTPUT directory
if [ ! -d "${OUTPUTPATH}/REPORT_OUTPUT/Scalers" ]; then
    mkdir "${OUTPUTPATH}/REPORT_OUTPUT/Scalers"
fi
# Now, check if subdirectories exist for HISTOGRAMS, if not, make them
# Analysis subdirectories
if [ ! -d "${OUTPUTPATH}/HISTOGRAMS/Analysis" ]; then
    mkdir "${OUTPUTPATH}/HISTOGRAMS/Analysis"
fi
if [ ! -d "${OUTPUTPATH}/HISTOGRAMS/Analysis/HeeP" ]; then
    mkdir "${OUTPUTPATH}/HISTOGRAMS/Analysis/HeeP"
fi
if [ ! -d "${OUTPUTPATH}/HISTOGRAMS/Analysis/Lumi" ]; then
    mkdir "${OUTPUTPATH}/HISTOGRAMS/Analysis/Lumi"
fi
if [ ! -d "${OUTPUTPATH}/HISTOGRAMS/Analysis/PionLT" ]; then
    mkdir "${OUTPUTPATH}/HISTOGRAMS/Analysis/PionLT"
fi
if [ ! -d "${OUTPUTPATH}/HISTOGRAMS/Analysis/PID" ]; then
    mkdir "${OUTPUTPATH}/HISTOGRAMS/Analysis/PID"
fi
if [ ! -d "${OUTPUTPATH}/HISTOGRAMS/Analysis/Optics" ]; then
    mkdir "${OUTPUTPATH}/HISTOGRAMS/Analysis/Optics"
fi
if [ ! -d "${OUTPUTPATH}/HISTOGRAMS/Analysis/General" ]; then
    mkdir "${OUTPUTPATH}/HISTOGRAMS/Analysis/General"
fi
# Calib sub directories
if [ ! -d "${OUTPUTPATH}/HISTOGRAMS/Calib" ]; then
    mkdir "${OUTPUTPATH}/HISTOGRAMS/Calib"
fi
if [ ! -d "${OUTPUTPATH}/HISTOGRAMS/Calib/Hodo" ]; then
    mkdir "${OUTPUTPATH}/HISTOGRAMS/Calib/Hodo"
fi
if [ ! -d "${OUTPUTPATH}/HISTOGRAMS/Calib/DC" ]; then
    mkdir "${OUTPUTPATH}/HISTOGRAMS/Calib/DC"
fi
if [ ! -d "${OUTPUTPATH}/HISTOGRAMS/Calib/Cal" ]; then
    mkdir "${OUTPUTPATH}/HISTOGRAMS/Calib/Cal"
fi
if [ ! -d "${OUTPUTPATH}/HISTOGRAMS/Calib/HGC" ]; then
    mkdir "${OUTPUTPATH}/HISTOGRAMS/Calib/HGC"
fi
if [ ! -d "${OUTPUTPATH}/HISTOGRAMS/Calib/Aero" ]; then
    mkdir "${OUTPUTPATH}/HISTOGRAMS/Calib/Aero"
fi
if [ ! -d "${OUTPUTPATH}/HISTOGRAMS/Calib/NGC" ]; then
    mkdir "${OUTPUTPATH}/HISTOGRAMS/Calib/NGC"
fi
if [ ! -d "${OUTPUTPATH}/HISTOGRAMS/Calib/General" ]; then
    mkdir "${OUTPUTPATH}/HISTOGRAMS/Calib/General"
fi
if [ ! -d "${OUTPUTPATH}/HISTOGRAMS/Calib/Timing" ]; then
    mkdir "${OUTPUTPATH}/HISTOGRAMS/Calib/Timing"
fi
# Scalers HISTOGRAMS directory
if [ ! -d "${OUTPUTPATH}/HISTOGRAMS/Scalers" ]; then
    mkdir "${OUTPUTPATH}/HISTOGRAMS/Scalers"
fi

# Directories now created, make the sym links
echo "Directories have been created in volatile if they did not already exists, sym links will now be made for - "
echo ""
echo "${OUTPUTPATH}/ROOTfiles/ - ROOTfiles"
echo "${OUTPUTPATH}/OUTPUT/ - OUTPUT"
echo "${OUTPUTPATH}/REPORT_OUTPUT/ - REPORT_OUTPUT"
echo "${OUTPUTPATH}/HISTOGRAMS/ - HISTOGRAMS"
echo "${OUTPUTPATH}/MON_OUTPUT/ - MON_OUTPUT"
echo "${CACHEPATH} - cache"
echo "${RAWPATH} - raw"
echo "${RAWCOPIEDPATH} - raw.copedtotape"
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
if [ ! -L "${ANALYSISPATH}/hallc_replay_lt/ROOTfiles" ]; then
    ln -s "${OUTPUTPATH}/ROOTfiles/" "${ANALYSISPATH}/hallc_replay_lt/ROOTfiles"
elif [ -L "${ANALYSISPATH}/hallc_replay_lt/ROOTfiles" ]; then
    if [ ! -e "${ANALYSISPATH}/hallc_replay_lt/ROOTfiles" ]; then
	echo "ROOTfiles sym link exits but is broken, replacing"
	rm "${ANALYSISPATH}/hallc_replay_lt/ROOTfiles"
	ln -s "${OUTPUTPATH}/ROOTfiles/" "${ANALYSISPATH}/hallc_replay_lt/ROOTfiles"
    else echo "${ANALYSISPATH}/hallc_replay_lt/ROOTfiles sym link already exists and not broken"
    fi
fi

if [ ! -L "${ANALYSISPATH}/hallc_replay_lt/OUTPUT" ]; then
    ln -s "${OUTPUTPATH}/OUTPUT/" "${ANALYSISPATH}/hallc_replay_lt/OUTPUT"
elif [ -L "${ANALYSISPATH}/hallc_replay_lt/OUTPUT" ]; then
    if [ ! -e "${ANALYSISPATH}/hallc_replay_lt/OUTPUT" ]; then
	echo "OUTPUT sym link exits but is broken, replacing"
	rm "${ANALYSISPATH}/hallc_replay_lt/OUTPUT"
	ln -s "${OUTPUTPATH}/OUTPUT/" "${ANALYSISPATH}/hallc_replay_lt/OUTPUT"
    else echo "${ANALYSISPATH}/hallc_replay_lt/OUTPUT sym link already exists and not broken"
    fi
fi

if [ ! -L "${ANALYSISPATH}/hallc_replay_lt/REPORT_OUTPUT" ]; then
    ln -s "${OUTPUTPATH}/REPORT_OUTPUT/" "${ANALYSISPATH}/hallc_replay_lt/REPORT_OUTPUT"
elif [ -L "${ANALYSISPATH}/hallc_replay_lt/REPORT_OUTPUT" ]; then
    if [ ! -e "${ANALYSISPATH}/hallc_replay_lt/REPORT_OUTPUT" ]; then
	echo "REPORT_OUTPUT sym link exits but is broken, replacing"
	rm "${ANALYSISPATH}/hallc_replay_lt/REPORT_OUTPUT"
	ln -s "${OUTPUTPATH}/REPORT_OUTPUT/" "${ANALYSISPATH}/hallc_replay_lt/REPORT_OUTPUT"
    else echo "${ANALYSISPATH}/hallc_replay_lt/REPORT_OUTPUT sym link already exists and not broken"
    fi
fi

if [ ! -L "${ANALYSISPATH}/hallc_replay_lt/HISTOGRAMS" ]; then
    ln -s "${OUTPUTPATH}/HISTOGRAMS/" "${ANALYSISPATH}/hallc_replay_lt/HISTOGRAMS"
elif [ -L "${ANALYSISPATH}/hallc_replay_lt/HISTOGRAMS" ]; then
    if [ ! -e "${ANALYSISPATH}/hallc_replay_lt/HISTOGRAMS" ]; then
	echo "HISTOGRAMS sym link exits but is broken, replacing"
	rm "${ANALYSISPATH}/hallc_replay_lt/HISTOGRAMS"
	ln -s "${OUTPUTPATH}/HISTOGRAMS/" "${ANALYSISPATH}/hallc_replay_lt/HISTOGRAMS"
    else echo "${ANALYSISPATH}/hallc_replay_lt/HISTOGRAMS sym link already exists and not broken"
    fi
fi

if [ ! -L "${ANALYSISPATH}/hallc_replay_lt/MON_OUTPUT" ]; then
    ln -s "${OUTPUTPATH}/MON_OUTPUT/" "${ANALYSISPATH}/hallc_replay_lt/MON_OUTPUT"
elif [ -L "${ANALYSISPATH}/hallc_replay_lt/MON_OUTPUT" ]; then
    if [ ! -e "${ANALYSISPATH}/hallc_replay_lt/MON_OUTPUT" ]; then
	echo "OUTPUT sym link exits but is broken, replacing"
	rm "${ANALYSISPATH}/hallc_replay_lt/MON_OUTPUT"
	ln -s "${OUTPUTPATH}/MON_OUTPUT/" "${ANALYSISPATH}/hallc_replay_lt/MON_OUTPUT"
    else echo "${ANALYSISPATH}/hallc_replay_lt/MON_OUTPUT sym link already exists and not broken"
    fi
fi

if [ ! -L "${ANALYSISPATH}/hallc_replay_lt/raw" ]; then
    ln -s "${RAWPATH}" "${ANALYSISPATH}/hallc_replay_lt/raw"
elif [ -L "${ANALYSISPATH}/hallc_replay_lt/raw" ]; then
    if [ ! -e "${ANALYSISPATH}/hallc_replay_lt/raw" ]; then
	echo "raw sym link exits but is broken, replacing"
	rm "${ANALYSISPATH}/hallc_replay_lt/raw"
	ln -s "${RAWPATH}" "${ANALYSISPATH}/hallc_replay_lt/raw"
    else echo "${ANALYSISPATH}/hallc_replay_lt/raw sym link already exists and not broken"
    fi
fi

if [ ! -L "${ANALYSISPATH}/hallc_replay_lt/raw.copiedtotape" ]; then
    ln -s "${RAWCOPIEDPATH}" "${ANALYSISPATH}/hallc_replay_lt/raw.copiedtotape"
elif [ -L "${ANALYSISPATH}/hallc_replay_lt/raw.copiedtotape" ]; then
    if [ ! -e "${ANALYSISPATH}/hallc_replay_lt/raw.copiedtotape" ]; then
	echo "raw.copiedtotape sym link exits but is broken, replacing"
	rm "${ANALYSISPATH}/hallc_replay_lt/raw"
	ln -s "${RAWCOPIEDPATH}" "${ANALYSISPATH}/hallc_replay_lt/raw.copiedtotape"
    else echo "${ANALYSISPATH}/hallc_replay_lt/raw.copiedtotape sym link already exists and not broken"
    fi
fi

if [ ! -L "${ANALYSISPATH}/hallc_replay_lt/cache" ]; then
    ln -s "${CACHEPATH}" "${ANALYSISPATH}/hallc_replay_lt/cache"
elif [ -L "${ANALYSISPATH}/hallc_replay_lt/cache" ]; then
    if [ ! -e "${ANALYSISPATH}/hallc_replay_lt/cache" ]; then
	echo "cache sym link exits but is broken, replacing"
	rm "${ANALYSISPATH}/hallc_replay_lt/cache"
	ln -s "${CACHEPATH}" "${ANALYSISPATH}/hallc_replay_lt/cache"
    else echo "${ANALYSISPATH}/hallc_replay_lt/cache sym link already exists and not broken"
    fi
fi

echo ""
echo "Directories and sym links for hallc_replay_lt now setup"

exit 0
