#!/bin/bash

### Stephen Kay --- University of Regina --- 24/03/21 ###
### Lazy boy script to go through and modify the parameter files that will be examined ###
### Reads in a list of run numbers from a text file ###
### This one just changes the gscalers.param file to match the new correct one ###

inputFile="$1"

while IFS='' read -r line || [[ -n "$line" ]]; do
    ##Run number#                                                         
    runNum=$line
    if [ "$runNum" -le "7040" ]; then
	sed -i "s/gscalers.param/gscalers_Fall18.param/" "Offline"$runNum".param"
    elif [ "$runNum" -ge "7041" -a "$runNum" -le "8350" ]; then
	sed -i "s/gscalers.param/gscalers_Spring19.param/" "Offline"$runNum".param"
    elif [ "$runNum" -ge "8351" -a "$runNum" -le "8587" ]; then
	sed -i "s/gscalers.param/gscalers_Summer19_1.param/" "Offline"$runNum".param"
    elif [ "$runNum" -ge "8588" ]; then
	sed -i "s/gscalers.param/gscalers_Summer19_2.param/" "Offline"$runNum".param"
    fi
done < "$inputFile"

#echo "$runNum"
#echo "gscalers_Fall18.param"
