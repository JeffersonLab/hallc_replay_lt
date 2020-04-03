#!/bin/bash

##Select angle (left, center)##
angle=$1

##Select current##
current=$2
CURRENT=$(echo "$current" | tr '[:lower:]' '[:upper:]')

if [[ ${angle} == "" ]]; then
    echo "Please select an angle setting..."
    exit 2
fi
if [[ ${current} == "" ]]; then
    echo "No current entered...assuming chain of all runs at ${angle}" 
    echo ""
    current=-1
fi
if [[ ${angle} = "left" ]]; then
    ## Chain runs script ##
    script_Q05W2="scripts_Summaries/Q05W2Left.C"
    run_script_Q05W2="root -l -b -q \"${script_Q05W2}(${current})\""
    echo "Running ${script_Q05W2} for runs with ${current} uA"
    eval ${run_script_Q05W2}
    mv OUTPUT/Kinematics_${current}uA_allPlots.pdf OUTPUT/Kinematics_${current}uA_left.pdf
    echo "Kinematics_${current}uA_allPlots.pdf changed to Kinematics_${current}uA_left.pdf"
    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    echo "CHAIN AT ${CURRENT} UA LEFT ANGLE COMPLETE"
    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
fi
if [[ ${angle} = "center" ]]; then
    ## Chain runs script ##
    script_Q05W2="scripts_Summaries/Q05W2Center.C"
    run_script_Q05W2="root -l -b -q \"${script_Q05W2}(${current})\""
    echo "Running ${script_Q05W2} for runs with ${current} uA"
    eval ${run_script_Q05W2}
    mv OUTPUT/Kinematics_${current}uA_allPlots.pdf OUTPUT/Kinematics_${current}uA_center.pdf
    echo "Kinematics_${current}uA_allPlots.pdf changed to Kinematics_${current}uA_center.pdf"
    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    echo "CHAIN AT ${CURRENT} UA CENTER ANGLE COMPLETE"
    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
fi
if [[ ${angle} = "right" ]]; then
    ## Chain runs script ##
    script_Q05W2="scripts_Summaries/Q05W2Right.C"
    run_script_Q05W2="root -l -b -q \"${script_Q05W2}(${current})\""
    echo "Running ${script_Q05W2} for runs with ${current} uA"
    eval ${run_script_Q05W2}
    mv OUTPUT/Kinematics_${current}uA_allPlots.pdf OUTPUT/Kinematics_${current}uA_right.pdf
    echo "Kinematics_${current}uA_allPlots.pdf changed to Kinematics_${current}uA_right.pdf"
    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    echo "CHAIN AT ${CURRENT} UA RIGHT ANGLE COMPLETE"
    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
fi
