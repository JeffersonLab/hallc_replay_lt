# Vijay Kumar, Univerity of Regina - 24/07/20
# vijay36361@gmail.com

####################################
### Using the Calibration Script ###
####################################

This file assumes your replayed files are in a sym link (or folder) called ROOTfiles in your base hallc_replay directory. Please change or add your path to the block around Line60 of the run_cal.C macro in this folder.

To run the calibration, use the run_cal.C macro with root.

It is highly recommend you execute the script without displaying any graphics (run in batch mode).

This script requires between 4 and 6 arguments, these are -

RunPrefix - The prefix to the replayed rootfile you wish to run, e.g if you files are Coin_Replay_#RUNNUMBER_#NUMEVENTS.root, the prefix would be Coin_Replay, omit the trailing _ before the runnumber
NumEvents - The number of events per run (must all be equal), e.g. if you ran all events, enter -1 here
nRuns - Number of runs you want to chain together and attempt to calibrate over, the script can handle 1-3 runs - ONLY enter 1, 2 or 3 here
RunNumber1 - The run number for the first run you want to add to the chain

If you entered 2 or 3 for nRuns, you will also need to specify RunNumber2 and RunNumber3

RunNumber2 - The run number for the second run you want to add to the chain
RunNumber3 - The run number for the third run you want to add to the chain

As an example of running the script, suppose you want to analyse Coin_Replay_5555_-1.root, Coin_Replay_5556_-1.root and Coin_Replay_5557_-1.root

From the directory this README is located in, execute

root -l -b -q 'run_cal.C("Coin_Replay", -1, 3, 5555, 5556, 5557)'

When running the script, it will complain if a rootfile cannot be found. If everything looks OK, you will be prompted to provide any options you want.
Enter NA to skip this OR enter the options you want, see the final section for the options that are available.

#############################################
### How many runs should I chain together? ##
#############################################

Vijay - Add some info here on the criteria for good/bad fit and what people should look for.
