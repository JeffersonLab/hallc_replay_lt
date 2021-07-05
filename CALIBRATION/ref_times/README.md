04/03/21 - SK, note, need to actually make some slimmed down timing replays for use here. They're now pointed to ROOTfiles/Calib/Timing e.t.c. to check stuff, but no replays actually write anything here YET
Should make some new replay scripts that DO and only include the relevant stuff for these scripts to keep file sizes down.

Run the .sh script if you want to clean things up automatically as they finish, you can also run the script with root directly via 

root -l (-b) run_DetTCuts.C

I highly recommend running with -b unless you like a LOT of canvases!

Either way, the script will require 3 inputs - 

Rootfile prefix, run number and number of events. 

E.g. you wish to run on file PionLT_6619_1000.root

You would do ./DetTCuts.sh PionLT 6619 1000, if you do not provide the required arguments the script will prompt you to do so.

Note this script assumes you are running on the farm or from a machine at the UoR and have setup your ROOTfiles/HISTOGRAMS/OUTPUT sym-links in a specific way, change or add in the correct one in run_DetTCuts.C if this is not the case.

######################
#### NEW 23/07/20 ####
######################

There's also a new script which plots the detector reference times AND the Hodoscope Adc/Tdc differences for a run.

If you just want the plots, run the root script on its own.

HOWEVER, if you want to automatically generate new cuts.param files with the new AdcTdc offsets, then run the shell script.

It runs in a similar way to the above

./RefTCuts.sh PREFIX RUNNUMBER NUMEVENTS

With the same three arguments.

If you want to run over a list of numbers, use the Process_List_RefT.sh script via

./Process_List_RefT.sh INPUTFILE PREFIX ROOTDIR

The input file should be the path to a text file with the runnumbers you want to analyse, each one on a new line. e.g

6600
6601
6602

and so on. PREFIX is the rootfile prefix as above. Note that this script is a little smarter, if arguments aren't specified for PREFIX and ROOTDIR, it assumes some defaults.

ROOTDIR is the ROOTfiles sym link in your hallc_replay_lt where the files in question are located. Again, a default is assumed if you don't provide anything.

DISCLAIMER - That final arg is a bit pointless currently, I had grand plans about linking it all up but this is a little bit of a nightmare. Hopefully it will be useful for making people realise if they have a broken path though!

The Process_List_RefT script will process every run in the list with the RefTCuts.sh script. As a result, you'll have a bunch of new cuts.param files which (hopefully) make things better.