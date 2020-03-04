#!/bin/bash

##Select epsilon (high, low)
epsilon=$1

##Select angle (left, center)##
angle=$2

if [[ ${epsilon} == "" ]]; then
    echo "Please select high or low epsilon..."
    exit 2
fi
if [[ ${angle} == "" ]]; then
    echo "Please select an angle setting..."
    exit 2
fi

if [[ ${epsilon} = "low" ]]; then
    if [[ ${angle} = "left" ]]; then
	## Chain runs script ##
	script_Q4p4W2p74="../scripts_Summaries/Q4p4W2p74left_lowe.C"
	run_script_Q4p4W2p74="root -l -b -q \"${script_Q4p4W2p74}\""
	echo "Running ${script_Q4p4W2p74}"
	eval ${run_script_Q4p4W2p74}
	mv ../OUTPUT/Kinematics_1uA_allPlots.pdf ../OUTPUT/Q4.4_W2.74_x0.40_lowe/Kinematics_leftQ4p4W2p74-lowe.pdf
	mv ../OUTPUT/Kinematics_1uA_allPlots.png ../OUTPUT/Q4.4_W2.74_x0.40_lowe/Kinematics_leftQ4p4W2p74-lowe.png
	mv ../OUTPUT/Kinematics_1uA_allPlots_coin.png ../OUTPUT/Q4.4_W2.74_x0.40_lowe/Kinematics_leftQ4p4W2p74-lowe_coin.png
	echo "Kinematics_1uA_allPlots.pdf changed to Kinematics_leftQ4p4W2p74_lowe.pdf"
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	echo "CHAIN AT LEFT ANGLE COMPLETE AT LOW EPSILON"
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    fi
    if [[ ${angle} = "center" ]]; then
	## Chain runs script ##
	script_Q4p4W2p74="../scripts_Summaries/Q4p4W2p74center_lowe.C"
	run_script_Q4p4W2p74="root -l -b -q \"${script_Q4p4W2p74}\""
	echo "Running ${script_Q4p4W2p74}"
	eval ${run_script_Q4p4W2p74}
	mv ../OUTPUT/Kinematics_1uA_allPlots.pdf ../OUTPUT/Q4.4_W2.74_x0.40_lowe/Kinematics_centerQ4p4W2p74-lowe.pdf
	mv ../OUTPUT/Kinematics_1uA_allPlots.png ../OUTPUT/Q4.4_W2.74_x0.40_lowe/Kinematics_centerQ4p4W2p74-lowe.png
	mv ../OUTPUT/Kinematics_1uA_allPlots_coin.png ../OUTPUT/Q4.4_W2.74_x0.40_lowe/Kinematics_centerQ4p4W2p74-lowe_coin.png
	echo "Kinematics_1uA_allPlots.pdf changed to Kinematics_centerQ4p4W2p74_lowe.pdf"
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	echo "CHAIN AT CENTER ANGLE COMPLETE AT LOW EPSILON"
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    fi
fi

if [[ ${epsilon} = "high" ]]; then
    if [[ ${angle} = "left" ]]; then
	## Chain runs script ##
	script_Q4p4W2p74="../scripts_Summaries/Q4p4W2p74left_highe.C"
	run_script_Q4p4W2p74="root -l -b -q \"${script_Q4p4W2p74}\""
	echo "Running ${script_Q4p4W2p74}"
	eval ${run_script_Q4p4W2p74}
	mv ../OUTPUT/Kinematics_1uA_allPlots.pdf ../OUTPUT/Q4.4_W2.74_x0.40_highe/Kinematics_leftQ4p4W2p74-highe.pdf
	mv ../OUTPUT/Kinematics_1uA_allPlots.png ../OUTPUT/Q4.4_W2.74_x0.40_highe/Kinematics_leftQ4p4W2p74-highe.png
	mv ../OUTPUT/Kinematics_1uA_allPlots_coin.png ../OUTPUT/Q4.4_W2.74_x0.40_highe/Kinematics_leftQ4p4W2p74-highe_coin.png
	echo "Kinematics_1uA_allPlots.pdf changed to Kinematics_leftQ4p4W2p74_highe.pdf"
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	echo "CHAIN AT LEFT ANGLE COMPLETE AT HIGH EPSILON"
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    fi
    if [[ ${angle} = "center" ]]; then
	## Chain runs script ##
	script_Q4p4W2p74="../scripts_Summaries/Q4p4W2p74center_highe.C"
	run_script_Q4p4W2p74="root -l -b -q \"${script_Q4p4W2p74}\""
	echo "Running ${script_Q4p4W2p74}"
	eval ${run_script_Q4p4W2p74}
	mv ../OUTPUT/Kinematics_1uA_allPlots.pdf ../OUTPUT/Q4.4_W2.74_x0.40_highe/Kinematics_centerQ4p4W2p74-highe.pdf
	mv ../OUTPUT/Kinematics_1uA_allPlots.png ../OUTPUT/Q4.4_W2.74_x0.40_highe/Kinematics_centerQ4p4W2p74-highe.png
	mv ../OUTPUT/Kinematics_1uA_allPlots_coin.png ../OUTPUT/Q4.4_W2.74_x0.40_highe/Kinematics_centerQ4p4W2p74-highe_coin.png
	echo "Kinematics_1uA_allPlots.pdf changed to Kinematics_centerQ4p4W2p74_highe.pdf"
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	echo "CHAIN AT CENTER ANGLE COMPLETE AT HIGH EPSILON"
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    fi
    if [[ ${angle} = "right" ]]; then
	## Chain runs script ##
	script_Q4p4W2p74="../scripts_Summaries/Q4p4W2p74right_highe.C"
	run_script_Q4p4W2p74="root -l -b -q \"${script_Q4p4W2p74}\""
	echo "Running ${script_Q4p4W2p74}"
	eval ${run_script_Q4p4W2p74}
	mv ../OUTPUT/Kinematics_1uA_allPlots.pdf ../OUTPUT/Q4.4_W2.74_x0.40_highe/Kinematics_rightQ4p4W2p74-highe.pdf
	mv ../OUTPUT/Kinematics_1uA_allPlots.png ../OUTPUT/Q4.4_W2.74_x0.40_highe/Kinematics_rightQ4p4W2p74-highe.png
	mv ../OUTPUT/Kinematics_1uA_allPlots_coin.png ../OUTPUT/Q4.4_W2.74_x0.40_highe/Kinematics_rightQ4p4W2p74-highe_coin.png
	echo "Kinematics_1uA_allPlots.pdf changed to Kinematics_rightQ4p4W2p74_highe.pdf"
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	echo "CHAIN AT RIGHT ANGLE COMPLETE AT HIGH EPSILON"
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    fi
fi
