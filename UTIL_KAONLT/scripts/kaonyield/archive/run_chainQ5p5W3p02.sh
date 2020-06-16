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
	script_Q5p5W3p02="../scripts_Summaries/Q5p5W3p02left_lowe.C"
	run_script_Q5p5W3p02="root -l \"${script_Q5p5W3p02}\""
	echo "Running ${script_Q5p5W3p02}"
	eval ${run_script_Q5p5W3p02}
	mv ../OUTPUT/Kinematics_1uA_allPlots.pdf ../OUTPUT/Q5.5_W3.02_x0.40_lowe/Kinematics_leftQ5p5W3p02-lowe.pdf
	mv ../OUTPUT/Kinematics_1uA_allPlots.png ../OUTPUT/Q5.5_W3.02_x0.40_lowe/Kinematics_leftQ5p5W3p02-lowe.png
	mv ../OUTPUT/Kinematics_1uA_allPlots_coin.png ../OUTPUT/Q5.5_W3.02_x0.40_lowe/Kinematics_leftQ5p5W3p02-lowe_coin.png
	echo "Kinematics_1uA_allPlots.pdf changed to Kinematics_leftQ5p5W3p02_lowe.pdf"
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	echo "CHAIN AT LEFT ANGLE COMPLETE AT LOW EPSILON"
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    fi
    if [[ ${angle} = "center" ]]; then
	## Chain runs script ##
	script_Q5p5W3p02="../scripts_Summaries/Q5p5W3p02center_lowe.C"
	run_script_Q5p5W3p02="root -l \"${script_Q5p5W3p02}\""
	echo "Running ${script_Q5p5W3p02}"
	eval ${run_script_Q5p5W3p02}
	mv ../OUTPUT/Kinematics_1uA_allPlots.pdf ../OUTPUT/Q5.5_W3.02_x0.40_lowe/Kinematics_centerQ5p5W3p02-lowe.pdf
	mv ../OUTPUT/Kinematics_1uA_allPlots.png ../OUTPUT/Q5.5_W3.02_x0.40_lowe/Kinematics_centerQ5p5W3p02-lowe.png
	mv ../OUTPUT/Kinematics_1uA_allPlots_coin.png ../OUTPUT/Q5.5_W3.02_x0.40_lowe/Kinematics_centerQ5p5W3p02-lowe_coin.png
	echo "Kinematics_1uA_allPlots.pdf changed to Kinematics_centerQ5p5W3p02_lowe.pdf"
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	echo "CHAIN AT CENTER ANGLE COMPLETE AT LOW EPSILON"
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    fi
fi

if [[ ${epsilon} = "high" ]]; then
    if [[ ${angle} = "left" ]]; then
	## Chain runs script ##
	script_Q5p5W3p02="../scripts_Summaries/Q5p5W3p02left_highe.C"
	run_script_Q5p5W3p02="root -l \"${script_Q5p5W3p02}\""
	echo "Running ${script_Q5p5W3p02}"
	eval ${run_script_Q5p5W3p02}
	mv ../OUTPUT/Kinematics_1uA_allPlots.pdf ../OUTPUT/Q5.5_W3.02_x0.40_highe/Kinematics_leftQ5p5W3p02-highe.pdf
	mv ../OUTPUT/Kinematics_1uA_allPlots.png ../OUTPUT/Q5.5_W3.02_x0.40_highe/Kinematics_leftQ5p5W3p02-highe.png
	mv ../OUTPUT/Kinematics_1uA_allPlots_coin.png ../OUTPUT/Q5.5_W3.02_x0.40_highe/Kinematics_leftQ5p5W3p02-highe_coin.png
	echo "Kinematics_1uA_allPlots.pdf changed to Kinematics_leftQ5p5W3p02_highe.pdf"
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	echo "CHAIN AT LEFT ANGLE COMPLETE AT HIGH EPSILON"
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    fi
    if [[ ${angle} = "center" ]]; then
	## Chain runs script ##
	script_Q5p5W3p02="../scripts_Summaries/Q5p5W3p02center_highe.C"
	run_script_Q5p5W3p02="root -l \"${script_Q5p5W3p02}\""
	echo "Running ${script_Q5p5W3p02}"
	eval ${run_script_Q5p5W3p02}
	mv ../OUTPUT/Kinematics_1uA_allPlots.pdf ../OUTPUT/Q5.5_W3.02_x0.40_highe/Kinematics_centerQ5p5W3p02-highe.pdf
	mv ../OUTPUT/Kinematics_1uA_allPlots.png ../OUTPUT/Q5.5_W3.02_x0.40_highe/Kinematics_centerQ5p5W3p02-highe.png
	mv ../OUTPUT/Kinematics_1uA_allPlots_coin.png ../OUTPUT/Q5.5_W3.02_x0.40_highe/Kinematics_centerQ5p5W3p02-highe_coin.png
	echo "Kinematics_1uA_allPlots.pdf changed to Kinematics_centerQ5p5W3p02_highe.pdf"
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	echo "CHAIN AT CENTER ANGLE COMPLETE AT HIGH EPSILON"
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    fi
    if [[ ${angle} = "right" ]]; then
	## Chain runs script ##
	script_Q5p5W3p02="../scripts_Summaries/Q5p5W3p02right_highe.C"
	run_script_Q5p5W3p02="root -l \"${script_Q5p5W3p02}\""
	echo "Running ${script_Q5p5W3p02}"
	eval ${run_script_Q5p5W3p02}
	mv ../OUTPUT/Kinematics_1uA_allPlots.pdf ../OUTPUT/Q5.5_W3.02_x0.40_highe/Kinematics_rightQ5p5W3p02-highe.pdf
	mv ../OUTPUT/Kinematics_1uA_allPlots.png ../OUTPUT/Q5.5_W3.02_x0.40_highe/Kinematics_rightQ5p5W3p02-highe.png
	mv ../OUTPUT/Kinematics_1uA_allPlots_coin.png ../OUTPUT/Q5.5_W3.02_x0.40_highe/Kinematics_rightQ5p5W3p02-highe_coin.png
	echo "Kinematics_1uA_allPlots.pdf changed to Kinematics_rightQ5p5W3p02_highe.pdf"
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	echo "CHAIN AT RIGHT ANGLE COMPLETE AT HIGH EPSILON"
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    fi
fi
