#!/bin/bash

### Stephen Kay --- University of Regina --- 15/11/19 ###
### Lazy boy script to go through and modify the parameter files that will be examined ###
### Reads in a list of run numbers from a text file ###
inputFile="$1"

while IFS='' read -r line || [[ -n "$line" ]]; do
    ##Run number#                                                         
    runNum=$line
    sed -i "s/hdc_calib_Autumn18.param/CALIB\/hdc_calib_$runNum.param/" "Offline"$runNum".param"
    sed -i "s/hdc_calib_Winter18.param/CALIB\/hdc_calib_$runNum.param/" "Offline"$runNum".param"
    sed -i "s/hdc_calib_Spring19.param/CALIB\/hdc_calib_$runNum.param/" "Offline"$runNum".param"
    sed -i "s/hdc_calib_Summer19.param/CALIB\/hdc_calib_$runNum.param/" "Offline"$runNum".param"
    sed -i "s/hdc_tzero_per_wire_Autumn18.param/CALIB\/hdc_tzero_per_wire_$runNum.param/" "Offline"$runNum".param"
    sed -i "s/hdc_tzero_per_wire_Winter18.param/CALIB\/hdc_tzero_per_wire_$runNum.param/" "Offline"$runNum".param"
    sed -i "s/hdc_tzero_per_wire_Spring19.param/CALIB\/hdc_tzero_per_wire_$runNum.param/" "Offline"$runNum".param"
    sed -i "s/hdc_tzero_per_wire_Summer19.param/CALIB\/hdc_tzero_per_wire_$runNum.param/" "Offline"$runNum".param"
    
done < "$inputFile"
