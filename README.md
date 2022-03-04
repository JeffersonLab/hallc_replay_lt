# Introduction - LTSepAnalysis_2022

This branch, LTSep_Analysis_2022, reflects the current state of the analysis effort for the kaon and
pion LT separation experiments. It includes the param files and scripts used in the recent 2021 PionLT 
run.

If you're just getting started, consider executing the SymLinkSetup_iFarm.sh script to set up various
folders and subdirectories that many of the analysis scripts rely upon to run successfully.

# Script Info

- The scripts are set up such that they will NOT run another replay IF an existing root file exists.
If you want to replay again, comment out the relevant line in each script.
- Many rely upon symbolic links and folder being in place, see the comment above on running SymLinkSetup_iFarm.sh
- During the oline running, one steering script was used to run a selection of other analysis scripts
  - run_PionLT.sh
    - See the comments and info in this script to see how it works
    - This has been edited to run on the iFarm if desired