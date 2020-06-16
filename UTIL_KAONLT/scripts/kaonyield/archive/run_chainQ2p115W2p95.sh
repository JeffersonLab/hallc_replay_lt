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
	script_Q2p115W2p95="../scripts_Summaries/Q2p115W2p95left_lowe.C"
	run_script_Q2p115W2p95="root -l -b -q \"${script_Q2p115W2p95}\""
	echo "Running ${script_Q2p115W2p95}"
	eval ${run_script_Q2p115W2p95}
	mv ../OUTPUT/Kinematics_1uA_allPlots.pdf ../OUTPUT/Q2.115_W2.95_x0.21_lowe/Kinematics_leftQ2p115W2p95-lowe.pdf
	mv ../OUTPUT/Kinematics_1uA_allPlots.png ../OUTPUT/Q2.115_W2.95_x0.21_lowe/Kinematics_leftQ2p115W2p95-lowe.png
	mv ../OUTPUT/Kinematics_1uA_allPlots_coin.png ../OUTPUT/Q2.115_W2.95_x0.21_lowe/Kinematics_leftQ2p115W2p95-lowe_coin.png
	echo "Kinematics_1uA_allPlots.pdf changed to Kinematics_leftQ2p115W2p95_lowe.pdf"
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	echo "CHAIN AT LEFT ANGLE COMPLETE AT LOW EPSILON"
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    fi
    if [[ ${angle} = "center" ]]; then
	## Chain runs script ##
	script_Q2p115W2p95="../scripts_Summaries/Q2p115W2p95center_lowe.C"
	run_script_Q2p115W2p95="root -l -b -q \"${script_Q2p115W2p95}\""
	echo "Running ${script_Q2p115W2p95}"
	eval ${run_script_Q2p115W2p95}
	mv ../OUTPUT/Kinematics_1uA_allPlots.pdf ../OUTPUT/Q2.115_W2.95_x0.21_lowe/Kinematics_centerQ2p115W2p95-lowe.pdf
	mv ../OUTPUT/Kinematics_1uA_allPlots.png ../OUTPUT/Q2.115_W2.95_x0.21_lowe/Kinematics_centerQ2p115W2p95-lowe.png
	mv ../OUTPUT/Kinematics_1uA_allPlots_coin.png ../OUTPUT/Q2.115_W2.95_x0.21_lowe/Kinematics_centerQ2p115W2p95-lowe_coin.png
	echo "Kinematics_1uA_allPlots.pdf changed to Kinematics_centerQ2p115W2p95_lowe.pdf"
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	echo "CHAIN AT CENTER ANGLE COMPLETE AT LOW EPSILON"
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    fi
fi

if [[ ${epsilon} = "high" ]]; then
    if [[ ${angle} = "left" ]]; then
	## Chain runs script ##
	script_Q2p115W2p95="../scripts_Summaries/Q2p115W2p95left_highe.C"
	run_script_Q2p115W2p95="root -l -b -q \"${script_Q2p115W2p95}\""
	echo "Running ${script_Q2p115W2p95}"
	eval ${run_script_Q2p115W2p95}
	mv ../OUTPUT/Kinematics_1uA_allPlots.pdf ../OUTPUT/Q2.115_W2.95_x0.21_highe/Kinematics_leftQ2p115W2p95-highe.pdf
	mv ../OUTPUT/Kinematics_1uA_allPlots.png ../OUTPUT/Q2.115_W2.95_x0.21_highe/Kinematics_leftQ2p115W2p95-highe.png
	mv ../OUTPUT/Kinematics_1uA_allPlots_coin.png ../OUTPUT/Q2.115_W2.95_x0.21_highe/Kinematics_leftQ2p115W2p95-highe_coin.png
	echo "Kinematics_1uA_allPlots.pdf changed to Kinematics_leftQ2p115W2p95_highe.pdf"
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	echo "CHAIN AT LEFT ANGLE COMPLETE AT HIGH EPSILON"
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    fi
    if [[ ${angle} = "center" ]]; then
	## Chain runs script ##
	script_Q2p115W2p95="../scripts_Summaries/Q2p115W2p95center_highe.C"
	run_script_Q2p115W2p95="root -l -b -q \"${script_Q2p115W2p95}\""
	echo "Running ${script_Q2p115W2p95}"
	eval ${run_script_Q2p115W2p95}
	mv ../OUTPUT/Kinematics_1uA_allPlots.pdf ../OUTPUT/Q2.115_W2.95_x0.21_highe/Kinematics_centerQ2p115W2p95-highe.pdf
	mv ../OUTPUT/Kinematics_1uA_allPlots.png ../OUTPUT/Q2.115_W2.95_x0.21_highe/Kinematics_centerQ2p115W2p95-highe.png
	mv ../OUTPUT/Kinematics_1uA_allPlots_coin.png ../OUTPUT/Q2.115_W2.95_x0.21_highe/Kinematics_centerQ2p115W2p95-highe_coin.png
	echo "Kinematics_1uA_allPlots.pdf changed to Kinematics_centerQ2p115W2p95_highe.pdf"
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	echo "CHAIN AT CENTER ANGLE COMPLETE AT HIGH EPSILON"
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    fi
    if [[ ${angle} = "right" ]]; then
	## Chain runs script ##
	script_Q2p115W2p95="../scripts_Summaries/Q2p115W2p95right_highe.C"
	run_script_Q2p115W2p95="root -l -b -q \"${script_Q2p115W2p95}\""
	echo "Running ${script_Q2p115W2p95}"
	eval ${run_script_Q2p115W2p95}
	mv ../OUTPUT/Kinematics_1uA_allPlots.pdf ../OUTPUT/Q2.115_W2.95_x0.21_highe/Kinematics_rightQ2p115W2p95-highe.pdf
	mv ../OUTPUT/Kinematics_1uA_allPlots.png ../OUTPUT/Q2.115_W2.95_x0.21_highe/Kinematics_rightQ2p115W2p95-highe.png
	mv ../OUTPUT/Kinematics_1uA_allPlots_coin.png ../OUTPUT/Q2.115_W2.95_x0.21_highe/Kinematics_rightQ2p115W2p95-highe_coin.png
	echo "Kinematics_1uA_allPlots.pdf changed to Kinematics_rightQ2p115W2p95_highe.pdf"
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	echo "CHAIN AT RIGHT ANGLE COMPLETE AT HIGH EPSILON"
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    fi
fi
