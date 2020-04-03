#! /bin/bash

#Input run numbers

REPLAYPATH="/u/group/c-kaonlt/USERS/trottar/hallc_replay_lt"        

inputFile="$REPLAYPATH/UTIL_KAONLT/scripts_Luminosity/inputRuns"

runNum=$1
    
#Number of events   
numEvts=50000
# numEvts=-1

#Script to run
script="$REPLAYPATH/UTIL_KAONLT/scripts_Luminosity/run_LumiYield.py" 

#Excecute
# source /apps/root/6.18.04/setroot_CUE.csh

python2 --version

echo "Running ${script} for run  ${runNum}"
# eval ${runScript}
python2 $script $runNum $numEvts

echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"          
echo "END OF RUN ${runNum}"                                                                                        
echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" 

