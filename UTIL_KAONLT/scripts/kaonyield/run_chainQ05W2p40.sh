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
	script_Q05W2p40="../scripts_Summaries/Q05W2p40left_lowe.C"
	run_script_Q05W2p40="root -l -b -q \"${script_Q05W2p40}\""
	echo "Running ${script_Q05W2p40}"
	eval ${run_script_Q05W2p40}
	mv ../OUTPUT/Kinematics_1uA_allPlots.pdf ../OUTPUT/Q0.5_W2.40_x0.09_lowe/Kinematics_leftQ05W2p40-lowe.pdf
	mv ../OUTPUT/Kinematics_1uA_allPlots.png ../OUTPUT/Q0.5_W2.40_x0.09_lowe/Kinematics_leftQ05W2p40-lowe.png
	mv ../OUTPUT/Kinematics_1uA_allPlots_coin.png ../OUTPUT/Q0.5_W2.40_x0.09_lowe/Kinematics_leftQ05W2p40-lowe_coin.png
	echo "Kinematics_1uA_allPlots.pdf changed to Kinematics_leftQ05W2p40_lowe.pdf"
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	echo "CHAIN AT LEFT ANGLE COMPLETE AT LOW EPSILON"
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    fi
    if [[ ${angle} = "center" ]]; then
	## Chain runs script ##
	script_Q05W2p40="../scripts_Summaries/Q05W2p40center_lowe.C"
	run_script_Q05W2p40="root -l -b -q  \"${script_Q05W2p40}\""
	echo "Running ${script_Q05W2p40}"
	eval ${run_script_Q05W2p40}
	mv ../OUTPUT/Kinematics_1uA_allPlots.pdf ../OUTPUT/Q0.5_W2.40_x0.09_lowe/Kinematics_centerQ05W2p40-lowe.pdf
	mv ../OUTPUT/Kinematics_1uA_allPlots.png ../OUTPUT/Q0.5_W2.40_x0.09_lowe/Kinematics_centerQ05W2p40-lowe.png
	mv ../OUTPUT/Kinematics_1uA_allPlots_coin.png ../OUTPUT/Q0.5_W2.40_x0.09_lowe/Kinematics_centerQ05W2p40-lowe_coin.png
	echo "Kinematics_1uA_allPlots.pdf changed to Kinematics_centerQ05W2p40_lowe.pdf"
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	echo "CHAIN AT CENTER ANGLE COMPLETE AT LOW EPSILON"
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    fi
fi

if [[ ${epsilon} = "high" ]]; then
    if [[ ${angle} = "left" ]]; then
	## Chain runs script ##
	script_Q05W2p40="../scripts_Summaries/Q05W2p40left_highe.C"
	run_script_Q05W2p40="root -l -b -q  \"${script_Q05W2p40}\""
	echo "Running ${script_Q05W2p40}"
	eval ${run_script_Q05W2p40}
	mv ../OUTPUT/Kinematics_1uA_allPlots.pdf ../OUTPUT/Q0.5_W2.40_x0.09_highe/Kinematics_leftQ05W2p40-highe.pdf
	mv ../OUTPUT/Kinematics_1uA_allPlots.png ../OUTPUT/Q0.5_W2.40_x0.09_highe/Kinematics_leftQ05W2p40-highe.png
	mv ../OUTPUT/Kinematics_1uA_allPlots_coin.png ../OUTPUT/Q0.5_W2.40_x0.09_highe/Kinematics_leftQ05W2p40-highe_coin.png
	echo "Kinematics_1uA_allPlots.pdf changed to Kinematics_leftQ05W2p40_highe.pdf"
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	echo "CHAIN AT LEFT ANGLE COMPLETE AT HIGH EPSILON"
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    fi
    if [[ ${angle} = "center" ]]; then
	## Chain runs script ##
	script_Q05W2p40="../scripts_Summaries/Q05W2p40center_highe.C"
	run_script_Q05W2p40="root -l -b -q  \"${script_Q05W2p40}\""
	echo "Running ${script_Q05W2p40}"
	eval ${run_script_Q05W2p40}
	mv ../OUTPUT/Kinematics_1uA_allPlots.pdf ../OUTPUT/Q0.5_W2.40_x0.09_highe/Kinematics_centerQ05W2p40-highe.pdf
	mv ../OUTPUT/Kinematics_1uA_allPlots.png ../OUTPUT/Q0.5_W2.40_x0.09_highe/Kinematics_centerQ05W2p40-highe.png
	mv ../OUTPUT/Kinematics_1uA_allPlots_coin.png ../OUTPUT/Q0.5_W2.40_x0.09_highe/Kinematics_centerQ05W2p40-highe_coin.png
	echo "Kinematics_1uA_allPlots.pdf changed to Kinematics_centerQ05W2p40_highe.pdf"
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	echo "CHAIN AT CENTER ANGLE COMPLETE AT HIGH EPSILON"
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    fi
    if [[ ${angle} = "right" ]]; then
	## Chain runs script ##
	script_Q05W2p40="../scripts_Summaries/Q05W2p40right_highe.C"
	run_script_Q05W2p40="root -l -b -q  \"${script_Q05W2p40}\""
	echo "Running ${script_Q05W2p40}"
	eval ${run_script_Q05W2p40}
	mv ../OUTPUT/Kinematics_1uA_allPlots.pdf ../OUTPUT/Q0.5_W2.40_x0.09_highe/Kinematics_rightQ05W2p40-highe.pdf
	mv ../OUTPUT/Kinematics_1uA_allPlots.png ../OUTPUT/Q0.5_W2.40_x0.09_highe/Kinematics_rightQ05W2p40-highe.png
	mv ../OUTPUT/Kinematics_1uA_allPlots_coin.png ../OUTPUT/Q0.5_W2.40_x0.09_highe/Kinematics_rightQ05W2p40-highe_coin.png
	echo "Kinematics_1uA_allPlots.pdf changed to Kinematics_rightQ05W2p40_highe.pdf"
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	echo "CHAIN AT RIGHT ANGLE COMPLETE AT HIGH EPSILON"
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    fi
fi
