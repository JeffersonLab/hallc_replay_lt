#!/bin/tcsh

### Template for a batch running script from Richard, modify with the script you want to run on the line 22

echo "Starting Kaon Yield Estimation"
echo "I take as arguments the Run Number and max number of events!"
set RUNNUMBER=$1
set MAXEVENTS=-1
#MAXEVENTS=50000
if ( $1 ==  "" ) then
    echo "I need a Run Number!"
    exit 2
    else

    #Initialise hcana
    cd "/home/apps/hcana"
    source "/home/apps/hcana/setup.csh"
    cd "/home/${USER}/work/JLab/hallc_replay_lt"
    source "/home/${USER}/work/JLab/hallc_replay_lt/setup.csh"

    echo  "\n\nStarting Replay Script\n\n"
    hcana -l -q "SCRIPTS/COIN/PRODUCTION/FullReplay_Lumi.C ($RUNNUMBER,$MAXEVENTS)"

endif
