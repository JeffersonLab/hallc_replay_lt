Run the .sh script if you want to clean things up automatically as they finish, you can also run the script with root directly via 

root -l (-b) run_DetTCuts.C

I highly recommend running with -b unless you like a LOT of canvases!

Either way, the script will require 3 inputs - 

Rootfile prefix, run number and number of events. 

E.g. you wish to run on file PionLT_6619_1000.root

You would do ./DetTCuts.sh PionLT 6619 1000, if you do not provide the required arguments the script will prompt you to do so.

Note this script assumes you are running on the farm or from a machine at the UoR and have setup your ROOTfiles/HISTOGRAMS/OUTPUT sym-links in a specific way, change or add in the correct one in run_DetTCuts.C if this is not the case.