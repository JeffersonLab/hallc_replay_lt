#!/bin/bash

### Stephen Kay --- University of Regina --- 15/11/19 ###
### Lazy boy script to go through and modify the parameter files that will be examined ###
### Reads in a list of run numbers from a text file ###
inputFile="$1"
ReplaceRun=${inputFile:0:4}

if [[ "${HOSTNAME}" = *"farm"* ]]; then  
    REPLAYPATH="/group/c-pionlt/USERS/${USER}/hallc_replay_lt"
elif [[ "${HOSTNAME}" = *"qcd"* ]]; then
    REPLAYPATH="/group/c-pionlt/USERS/${USER}/hallc_replay_lt"
elif [[ "${HOSTNAME}" = *"cdaq"* ]]; then
    REPLAYPATH="/home/cdaq/hallc-online/hallc_replay_lt"
elif [[ "${HOSTNAME}" = *"phys.uregina.ca"* ]]; then
    REPLAYPATH="/home/${USER}/work/JLab/hallc_replay_lt"
fi

while IFS='' read -r line || [[ -n "$line" ]]; do
    #Run number#
    runNum=$line

    sed -i "s/hcal_cuts_$runNum.param/hcal_cuts_$ReplaceRun.param/" "Offline"$runNum".param"
    sed -i "s/hcal_cuts_$runNum.param/hcal_cuts_$ReplaceRun.param/" "Offline"$runNum".param"
    sed -i "s/hcal_cuts_$runNum.param/hcal_cuts_$ReplaceRun.param/" "Offline"$runNum".param"
    sed -i "s/hcal_cuts_$runNum.param/hcal_cuts_$ReplaceRun.param/" "Offline"$runNum".param"

    sed -i "s/hcer_cuts_$runNum.param/hcer_cuts_$ReplaceRun.param/" "Offline"$runNum".param"
    sed -i "s/hcer_cuts_$runNum.param/hcer_cuts_$ReplaceRun.param/" "Offline"$runNum".param"
    sed -i "s/hcer_cuts_$runNum.param/hcer_cuts_$ReplaceRun.param/" "Offline"$runNum".param"
    sed -i "s/hcer_cuts_$runNum.param/hcer_cuts_$ReplaceRun.param/" "Offline"$runNum".param"

    sed -i "s/pcal_cuts_$runNum.param/pcal_cuts_$ReplaceRun.param/" "Offline"$runNum".param"
    sed -i "s/pcal_cuts_$runNum.param/pcal_cuts_$ReplaceRun.param/" "Offline"$runNum".param"
    sed -i "s/pcal_cuts_$runNum.param/pcal_cuts_$ReplaceRun.param/" "Offline"$runNum".param"
    sed -i "s/pcal_cuts_$runNum.param/pcal_cuts_$ReplaceRun.param/" "Offline"$runNum".param"

    sed -i "s/phgcer_cuts_$runNum.param/phgcer_cuts_$ReplaceRun.param/" "Offline"$runNum".param"
    sed -i "s/phgcer_cuts_$runNum.param/phgcer_cuts_$ReplaceRun.param/" "Offline"$runNum".param"
    sed -i "s/phgcer_cuts_$runNum.param/phgcer_cuts_$ReplaceRun.param/" "Offline"$runNum".param"
    sed -i "s/phgcer_cuts_$runNum.param/phgcer_cuts_$ReplaceRun.param/" "Offline"$runNum".param"

    sed -i "s/paero_cuts_$runNum.param/paero_cuts_$ReplaceRun.param/" "Offline"$runNum".param"
    sed -i "s/paero_cuts_$runNum.param/paero_cuts_$ReplaceRun.param/" "Offline"$runNum".param"
    sed -i "s/paero_cuts_$runNum.param/paero_cuts_$ReplaceRun.param/" "Offline"$runNum".param"
    sed -i "s/paero_cuts_$runNum.param/paero_cuts_$ReplaceRun.param/" "Offline"$runNum".param"

done < "$inputFile"
