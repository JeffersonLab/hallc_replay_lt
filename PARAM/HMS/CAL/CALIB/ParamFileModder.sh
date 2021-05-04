#!/bin/bash

### Stephen Kay --- University of Regina --- 15/11/19 ###
### Lazy boy script to move and modify the parameter files for the calorimeter ###
### Reads in a list of run numbers from a text file ###
inputFile="$1"

while IFS='' read -r line || [[ -n "$line" ]]; do
    ##Run number#                                                         
    runNum=$line
    #cp "/home/sjdkay/work/JLab/hallc_replay_lt/CALIBRATION/hms_cal_calib/Output/Pass2/hcal.param.HMS_Cal_Calib_${runNum}_-1" "/home/sjdkay/work/JLab/hallc_replay_lt/PARAM/HMS/CAL/CALIB/hcal_${runNum}.param"
    cp "/group/c-pionlt/USERS/sjdkay/hallc_replay_lt/CALIBRATION/hms_cal_calib/Output/hcal.param.HMS_Cal_Calib_${runNum}_-1" "/group/c-pionlt/USERS/sjdkay/hallc_replay_lt/PARAM/HMS/CAL/CALIB/hcal_${runNum}.param"
done < "$inputFile"
