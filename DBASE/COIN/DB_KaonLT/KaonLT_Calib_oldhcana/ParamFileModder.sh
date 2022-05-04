#!/bin/bash

### Stephen Kay --- University of Regina --- 15/11/19 ###
### Lazy boy script to go through and modify the parameter files that will be examined ###
### Reads in a list of run numbers from a text file ###
inputFile="$1"

while IFS='' read -r line || [[ -n "$line" ]]; do
    ##Run number#                                                         
    runNum=$line
    sed -i "s/hcal_calib_Autumn18.param/CALIB\/hcal_$runNum.param/" "Offline"$runNum".param"
    sed -i "s/hcal_calib_Winter18.param/CALIB\/hcal_$runNum.param/" "Offline"$runNum".param"
    sed -i "s/hcal_calib_Spring19.param/CALIB\/hcal_$runNum.param/" "Offline"$runNum".param"
    sed -i "s/new_hcal_calib_Summer19_0.448gev_pidlegs.param/CALIB\/hcal_$runNum.param/" "Offline"$runNum".param"
done < "$inputFile"
