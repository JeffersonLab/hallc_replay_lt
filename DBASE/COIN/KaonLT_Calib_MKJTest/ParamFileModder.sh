#!/bin/bash

### Stephen Kay --- University of Regina --- 15/11/19 ###
### Lazy boy script to go through and modify the parameter files that will be examined ###
### Reads in a list of run numbers from a text file ###
inputFile="$1"

while IFS='' read -r line || [[ -n "$line" ]]; do
    ##Run number#                                                         
    runNum=$line
    sed -i "s/hcal_cuts_Autumn18.param/CALIB\/hcal_cuts_$runNum.param/" "Offline"$runNum".param"
    sed -i "s/hcal_cuts_Winter18.param/CALIB\/hcal_cuts_$runNum.param/" "Offline"$runNum".param"
    sed -i "s/hcal_cuts_Spring19.param/CALIB\/hcal_cuts_$runNum.param/" "Offline"$runNum".param"
    sed -i "s/hcal_cuts_Summer19.param/CALIB\/hcal_cuts_$runNum.param/" "Offline"$runNum".param"

    sed -i "s/hcer_cuts_Autumn18.param/CALIB\/hcer_cuts_$runNum.param/" "Offline"$runNum".param"
    sed -i "s/hcer_cuts_Winter18.param/CALIB\/hcer_cuts_$runNum.param/" "Offline"$runNum".param"
    sed -i "s/hcer_cuts_Spring19.param/CALIB\/hcer_cuts_$runNum.param/" "Offline"$runNum".param"
    sed -i "s/hcer_cuts_Summer19.param/CALIB\/hcer_cuts_$runNum.param/" "Offline"$runNum".param"

    sed -i "s/pcal_cuts_Autumn18.param/CALIB\/pcal_cuts_$runNum.param/" "Offline"$runNum".param"
    sed -i "s/pcal_cuts_Winter18.param/CALIB\/pcal_cuts_$runNum.param/" "Offline"$runNum".param"
    sed -i "s/pcal_cuts_Spring19.param/CALIB\/pcal_cuts_$runNum.param/" "Offline"$runNum".param"
    sed -i "s/pcal_cuts_Summer19.param/CALIB\/pcal_cuts_$runNum.param/" "Offline"$runNum".param"

    sed -i "s/phgcer_cuts_Autumn18.param/CALIB\/phgcer_cuts_$runNum.param/" "Offline"$runNum".param"
    sed -i "s/phgcer_cuts_Winter18.param/CALIB\/phgcer_cuts_$runNum.param/" "Offline"$runNum".param"
    sed -i "s/phgcer_cuts_Spring19.param/CALIB\/phgcer_cuts_$runNum.param/" "Offline"$runNum".param"
    sed -i "s/phgcer_cuts_Summer19.param/CALIB\/phgcer_cuts_$runNum.param/" "Offline"$runNum".param"

    sed -i "s/paero_cuts_Autumn18.param/CALIB\/paero_cuts_$runNum.param/" "Offline"$runNum".param"
    sed -i "s/paero_cuts_Winter18.param/CALIB\/paero_cuts_$runNum.param/" "Offline"$runNum".param"
    sed -i "s/paero_cuts_Spring19.param/CALIB\/paero_cuts_$runNum.param/" "Offline"$runNum".param"
    sed -i "s/paero_cuts_Summer19.param/CALIB\/paero_cuts_$runNum.param/" "Offline"$runNum".param"

done < "$inputFile"
