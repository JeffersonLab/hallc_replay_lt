BCM Calibration Code,

Last updated by Nathan Heinrich (heinricn) 2024/04/29

This is code to take a BCM calibration run and turn it into a calibration of the BCMs.

contained within is 2 main scripts: bcm_cal_4.C and run_bcm_calibration.

=========================================================================
bcm_cal_4.C 
The code that actually does the conversion from raw Unser rate values to usable Currents, then fits the result to obtain the gain and offset used in calibration files.

Usage:
first make sure the directory ./bcm_data/ exists as this is where it will try to save output.
*** IF IT DOES NOT EXIST IT WILL NOT SAVE FILES AND MOST LIKELY NOT GIVE ANY ERRORS ***
Then: 
root -l
.x bcm_cal_4.C("../../ROOTfiles/BCMcalib/coin_replay_scalers_16898_-1.root","16898_BCMcalib_onOffTimes",16898,"BCM1",0)

1. The first argument is the full path to a scaler replay with all the BCM varibles in the tree

2. Second argument is the full path to file with the times when the beam was off and on during the run, to generate follow these instructions from Dave Mack:

    root
    new TBrowser()
    
    In the left menu, click on an appropriate root file (*.root) with scaler information,
    then click on a tree with a name like "TSH     H Scaler Data"  (ie, for HMS scalers)
    
    To pick off points for the range file, you can use the cursor after typing in
    
    TSH->Draw("H.BCM4C.scalerRate:H.1MHz.scalerTime","","L")
    
    or for another example
    
    TSH->Draw("H.Unser.scalerRate:H.1MHz.scalerTime","","L")

    One should use the BCM, But it's also important to take a look at the Unser
    rates to make sure the data are present as expected.
    
    My format for the range file names is "runNumber_BCMcalib_onOffTimes". The inflexible ROOT macro requires every beam on interval to have a beam off interval before it and after it. 
    The format for the range file data is therefore:
    
    beam off Low Limit, Upper Limit
    beam on LL, UL
    beam off LL, UL
    beam on LL, UL
    .
    .
    .
    beam off LL, UL
    
    ie. the file should look like:
    5       103
    115     200
    210     273
    .
    .
    .
    2003    2150
    
    check the "frequencyVtime" plots after running, to make sure that you've done it right
        
3. The Third Argument is the run number, this is only used for naming output files

4. The forth Argument is which BCM you want to analyze there is only BCM1 BCM2 BCM4A BCM4B and BCM4C

5. This is whether or not you want the plots to go to screen (i.e. batch mode), wuns much faster without (ie. 1)


=================================================================
run_bcm_calibration.sh

Simple shell script that runs through all the bcms in one command.

Usage:
./run_bcm_calibration.sh "../../ROOTfiles/BCMcalib/coin_replay_scalers_16898_-1.root" "16898_BCMcalib_onOffTimes" 16898

arguments are the same as the root script, execpt it runs 5 times (once for each BCM), and assumes batch mode.






