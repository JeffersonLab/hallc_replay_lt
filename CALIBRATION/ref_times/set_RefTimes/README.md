# Overview
Useful Docuentation: [https://hallcweb.jlab.org/DocDB/0010/001032/001/analysis_notes.pdf]()

### directory structure: <br>

`scripts/set_reftimes.C` main script to check/set reference times or detector time window cuts

`scripts/set_reftimes.h` header file to define variables used in the main script

`set_reftime.sh`: shell script that (1) replays data and (2) checks ref. time of replayed data

`set_timewin.sh`: shell script that (1) replays data and (2) checks detector time windows of replayed data

**NOTE**: Since checking/setting ref. times/detector time windows requires specific leaf variables to be in a ROOTfile, the shell script automatically replays the data with the  required variables and thne analyzes the output ROOTfile to determine the existing reference time/detector time windows currently
set and in the case of hodoscopes/calorimeters, it suggests new time window cuts as well, since these are high-density detectors with many channels for a user to set manually.

### how-to guide:
If there is an existing ROOTfile (assuming it has the required leaf variables), the user may run the main script directly.

The main script takes the following arguments:
`void set_reftimes(TString filename = "", int run = 0, TString daq_mode = "coin", Bool_t set_refTimes = true, Bool_t debug = false)
`

```sh
# To run the script on an existing ROOTfile, simply do:      
$ root -l                                                                                                                                                                   
$ .L scripts/set_reftimes.C

# Then, to check/set reference times or detector time windows, 
# change the 'Bool_t set_refTimes' flag to either 'true' (ref. times) or
# 'false' (detector time windows)

# Example: checking/setting reference times for run 16036
$ set_reftimes("../../ROOTfiles/reftime/cafe_replay_reftime_16036_20000.root", 16036, "coin", true, false)    

# Example: checking/setting detector time window for run 16036
$ set_reftimes("../../ROOTfiles/timewin/cafe_replay_timewin_16036_20000.root", 16036, "coin", false, false)      
                                                                                                                                
```
Continuing the example on run 16036: <br> 

1) running the script with `Bool_t set_refTimes=true`will generate an output directory: <br>

`Time_cuts_refTime16036/` with the contents: <br>

`HMS/`: sub-directory with plots showing the existing HMS reference times <br>
`SHMS/`: sub-directory with the plots showing the existing SHMS reference times <br>
`.root` a ROOTfile with the relevant histogram objects that were used to make the plots.

At this point, the user can decide whether the existing reference time cuts (blue lines) are satisfactory or whether they will need to be modified.


2) running the script with `Bool_t set_refTimes=false`will generate an output directory: <br>

`Time_cuts_tWinSet16036/` with contents: <br>

`param_files`: sub-directory with both `_existing.param` or `_new.param` files <br>
`HMS/`: sub-directory with detector plots showing the existing/new HMS time window cuts <br>
`SHMS/`: sub-directory with detector plots showing the existing/new SHMS time window cuts <br>
`.root` a ROOTfile with the relevant histogram objects that were used to make the plots.

There may also be an existing `.pdf` file with plots of trigger times, but this is subject to which variables the user will set a cut on the `tcoin.param` file (and can always be changed in the code, depending on which variables from `tcoin.param` the user will examine)

