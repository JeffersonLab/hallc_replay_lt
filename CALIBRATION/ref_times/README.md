This is the new version of the reftimes plotting scripts.

The script RefTimes.C is a simple root script that just plots 
all of the ref time variambles for all the detectors in both the shms and the hms.

The script takes input parametters ("path to rootfile", runnumber)
						eg.		   ("../../ROOTfiles/Calib/Timing/reftimes_7777.root", 7777)
						
The script will output a root file labled with the run number indicated in the runnumber input
to the directory, format "./output/REF_TimePlots_RUNNUMBER.root" so you will need to double check
that the output directory exists.

The output contains both the ref time plots and the multiplticity plots.
This is important because the multiplticity values are the only cuts that are currently placed.
These cuts may need to be changed, to do so simply look in the fillHistos function 
(line 406 as of writing) and change the value of the cut on the effected variables. 