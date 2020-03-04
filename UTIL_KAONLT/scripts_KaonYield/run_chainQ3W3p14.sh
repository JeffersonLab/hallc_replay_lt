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
	script_Q3W3p14="../scripts_Summaries/Q3W3p14left_lowe.C"
	run_script_Q3W3p14="root -l  \"${script_Q3W3p14}\""
	echo "Running ${script_Q3W3p14}"
	eval ${run_script_Q3W3p14}
	mv ../OUTPUT/Kinematics_1uA_allPlots.pdf ../OUTPUT/Q3.0_W3.14_x0.25_lowe/Kinematics_leftQ3W3p14-lowe.pdf
	mv ../OUTPUT/Kinematics_1uA_allPlots.png ../OUTPUT/Q3.0_W3.14_x0.25_lowe/Kinematics_leftQ3W3p14-lowe.png
	mv ../OUTPUT/Kinematics_1uA_allPlots_coin.png ../OUTPUT/Q3.0_W3.14_x0.25_lowe/Kinematics_leftQ3W3p14-lowe_coin.png
	echo "Kinematics_1uA_allPlots.pdf changed to Kinematics_leftQ3W3p14_lowe.pdf"
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	echo "CHAIN AT LEFT ANGLE COMPLETE AT LOW EPSILON"
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    fi
    if [[ ${angle} = "center" ]]; then
	## Chain runs script ##
	script_Q3W3p14="../scripts_Summaries/Q3W3p14center_lowe.C"
	run_script_Q3W3p14="root -l  \"${script_Q3W3p14}\""
	echo "Running ${script_Q3W3p14}"
	eval ${run_script_Q3W3p14}
	mv ../OUTPUT/Kinematics_1uA_allPlots.pdf ../OUTPUT/Q3.0_W3.14_x0.25_lowe/Kinematics_centerQ3W3p14-lowe.pdf
	mv ../OUTPUT/Kinematics_1uA_allPlots.png ../OUTPUT/Q3.0_W3.14_x0.25_lowe/Kinematics_centerQ3W3p14-lowe.png
	mv ../OUTPUT/Kinematics_1uA_allPlots_coin.png ../OUTPUT/Q3.0_W3.14_x0.25_lowe/Kinematics_centerQ3W3p14-lowe_coin.png
	echo "Kinematics_1uA_allPlots.pdf changed to Kinematics_centerQ3W3p14_lowe.pdf"
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	echo "CHAIN AT CENTER ANGLE COMPLETE AT LOW EPSILON"
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    fi
fi

if [[ ${epsilon} = "high" ]]; then
    if [[ ${angle} = "left" ]]; then
	## Chain runs script ##
	script_Q3W3p14="../scripts_Summaries/Q3W3p14left_highe.C"
	run_script_Q3W3p14="root -l  \"${script_Q3W3p14}\""
	echo "Running ${script_Q3W3p14}"
	eval ${run_script_Q3W3p14}
	mv ../OUTPUT/Kinematics_1uA_allPlots.pdf ../OUTPUT/Q3.0_W3.14_x0.25_highe/Kinematics_leftQ3W3p14-highe.pdf
	mv ../OUTPUT/Kinematics_1uA_allPlots.png ../OUTPUT/Q3.0_W3.14_x0.25_highe/Kinematics_leftQ3W3p14-highe.png
	mv ../OUTPUT/Kinematics_1uA_allPlots_coin.png ../OUTPUT/Q3.0_W3.14_x0.25_highe/Kinematics_leftQ3W3p14-highe_coin.png
	echo "Kinematics_1uA_allPlots.pdf changed to Kinematics_leftQ3W3p14_highe.pdf"
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	echo "CHAIN AT LEFT ANGLE COMPLETE AT HIGH EPSILON"
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    fi
    if [[ ${angle} = "center" ]]; then
	## Chain runs script ##
	script_Q3W3p14="../scripts_Summaries/Q3W3p14center_highe.C"
	run_script_Q3W3p14="root -l  \"${script_Q3W3p14}\""
	echo "Running ${script_Q3W3p14}"
	eval ${run_script_Q3W3p14}
	mv ../OUTPUT/Kinematics_1uA_allPlots.pdf ../OUTPUT/Q3.0_W3.14_x0.25_highe/Kinematics_centerQ3W3p14-highe.pdf
	mv ../OUTPUT/Kinematics_1uA_allPlots.png ../OUTPUT/Q3.0_W3.14_x0.25_highe/Kinematics_centerQ3W3p14-highe.png
	mv ../OUTPUT/Kinematics_1uA_allPlots_coin.png ../OUTPUT/Q3.0_W3.14_x0.25_highe/Kinematics_centerQ3W3p14-highe_coin.png
	echo "Kinematics_1uA_allPlots.pdf changed to Kinematics_centerQ3W3p14_highe.pdf"
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	echo "CHAIN AT CENTER ANGLE COMPLETE AT HIGH EPSILON"
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    fi
    if [[ ${angle} = "right" ]]; then
	## Chain runs script ##
	script_Q3W3p14="../scripts_Summaries/Q3W3p14right_highe.C"
	run_script_Q3W3p14="root -l  \"${script_Q3W3p14}\""
	echo "Running ${script_Q3W3p14}"
	eval ${run_script_Q3W3p14}
	mv ../OUTPUT/Kinematics_1uA_allPlots.pdf ../OUTPUT/Q3.0_W3.14_x0.25_highe/Kinematics_rightQ3W3p14-highe.pdf
	mv ../OUTPUT/Kinematics_1uA_allPlots.png ../OUTPUT/Q3.0_W3.14_x0.25_highe/Kinematics_rightQ3W3p14-highe.png
	mv ../OUTPUT/Kinematics_1uA_allPlots_coin.png ../OUTPUT/Q3.0_W3.14_x0.25_highe/Kinematics_rightQ3W3p14-highe_coin.png
	echo "Kinematics_1uA_allPlots.pdf changed to Kinematics_rightQ3W3p14_highe.pdf"
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	echo "CHAIN AT RIGHT ANGLE COMPLETE AT HIGH EPSILON"
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    fi
fi
