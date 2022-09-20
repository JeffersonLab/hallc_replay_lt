# Introduction - LTSep_Analysis_2022

- This branch is the offline analysis branch for the LT separation experiments. hallc_replay_lt is common to KaonLT and PionLT
- If you're just getting started, consider executing the SymLinkSetup_iFarm.sh script to set up various folders and subdirectories that many of the analysis scripts rely upon to run successfully.

# Script Info

- The scripts are set up such that they will NOT run another replay IF an existing root file exists. If you want to replay again, comment out the relevant line in each script.	   
- Many rely upon symbolic links and folder being in place, see the comment above on running SymLinkSetup_iFarm.sh
- During the oline running, one steering script was used to run a selection of other analysis scripts
  - run_PionLT.sh
    - See the comments and info in this script to see how it works
    - This has been edited to run on the iFarm if desired
    - Most analysis is done it UTIL repositories
      - UTIL_PION - https://github.com/JeffersonLab/UTIL_PION
      - UTIL_KAONLT - https://github.com/JeffersonLab/UTIL_KAONLT
    - There is also a repository of scripts for processing files using the JLab batch queueing system
      - UTIL_BATCH - https://github.com/JeffersonLab/UTIL_BATCH