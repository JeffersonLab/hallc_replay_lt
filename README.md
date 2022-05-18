# Introduction - online_pionlt

This branch, online_pionlt, is the active running branch for the 2022 PionLT experiment. It will be kept up to date during the experiment.
Cdaq should be fully up to date at all times. Regular snapshots of this branch will be taken for quick access to specific states of the repo.

# Script Info

- The scripts are set up such that they will NOT run another replay IF an existing root file exists.
If you want to replay again, comment out the relevant line in each script.
- Many rely upon symbolic links and folder being in place, see the comment above on running SymLinkSetup_iFarm.sh
  - You should NOT need to run this on cdaq, contact an expert if a sym link seems to be missing or you see a pathing issue
- During the oline running, one steering script is used to run a selection of other analysis scripts
  - run_PionLT.sh
    - See the comments and info in this script to see how it works
    - This has been edited to run on the iFarm if desired

# PionLT Experts

- If you have any issues running any of the scripts or bump into any errors or issues, contact one of the experts listed below
  - Stephen Kay - stephen.kay@uregina.ca - JLab ID - sjdkay
  - Nathan Heinrich - heinricn@uregina.ca - JLab ID - heinricn
  - Muhammad Junaid - junaid@jlab.org - JLab ID - junaid
  - Jacob Murphy - jm443918@ohio.edu - JLab ID - jmurphy