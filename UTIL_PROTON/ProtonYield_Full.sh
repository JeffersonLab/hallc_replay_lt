#!/bin/bash

echo "Starting Proton Yield Estimation for ALL KaonLT Data"

while true; do
    read -p "Do you wish to run this analysis? (Please answer yes or no)" yn
    case $yn in
	[Yy]* )
            (	    
		# Set path depending upon hostname. Change or add more as needed  
		if [[ "${HOSTNAME}" = *"farm"* ]]; then  
		    REPLAYPATH="/group/c-kaonlt/USERS/${USER}/hallc_replay_lt"
		    if [[ "${HOSTNAME}" != *"ifarm"* ]]; then
			source /site/12gev_phys/softenv.sh 2.1
		    fi
		    cd "/group/c-kaonlt/hcana/"
		    source "/group/c-kaonlt/hcana/setup.sh"
		    cd "$REPLAYPATH"
		    source "$REPLAYPATH/setup.sh"
		elif [[ "${HOSTNAME}" = *"cdaq"* ]]; then
		    REPLAYPATH="/home/cdaq/hallc-online/hallc_replay_lt"
		elif [[ "${HOSTNAME}" = *"phys.uregina.ca"* ]]; then
		    REPLAYPATH="/home/${USER}/work/JLab/hallc_replay_lt"
		    OUTPUTPATH="/dsk3/${USER}/JLab/OUTPUT/Proton_Analysis"
		    HISTOPATH="/dsk3/${USER}/JLab/HISTOGRAMS/Proton_Analysis"
		fi
		cd "$REPLAYPATH/UTIL_PROTON/scripts_Summaries"
		# Use .* for equivalent of *, need \ for brackets since they're special characters
		sed -i "s/Offset\[3\] = .*/Offset\[3\] = \{47.15, 47.15, 48.65\};/" $REPLAYPATH/UTIL_PROTON/scripts_Yield/ProtonYield.C
		sed -i "s/PromptLow\[3\] = .*/PromptLow\[3\] = \{-1, -1, -1\};/" $REPLAYPATH/UTIL_PROTON/scripts_Yield/ProtonYield.C
		sed -i "s/PromptHigh\[3\] = .*/PromptHigh\[3\] = \{1, 1, 1\};/" $REPLAYPATH/UTIL_PROTON/scripts_Yield/ProtonYield.C
		sed -i "s/RandomLow\[3\] = .*/RandomLow\[3\] = \{5, 5 ,5\};/" $REPLAYPATH/UTIL_PROTON/scripts_Yield/ProtonYield.C
		sed -i "s/RandomHigh\[3\] = .*/RandomHigh\[3\] = \{9, 9, 9\};/" $REPLAYPATH/UTIL_PROTON/scripts_Yield/ProtonYield.C
		sed -i "s/new TH2F(\"WvsQ2\",\"Q2 vs W;Q2;W\",.*/new TH2F(\"WvsQ2\",\"Q2 vs W;Q2;W\", 200, 0.0, 6.0, 200, 2.0, 3.0);/" $REPLAYPATH/UTIL_PROTON/scripts_Yield/ProtonYield.C
		
		root -l -b -q "Q05W2p40left_highe.C"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots.pdf" "$OUTPUTPATH/Proton_Kinematics_Q05W2p40left_highe_AllPlots.pdf"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots_coin.png" "$OUTPUTPATH/Proton_Kinematics_Q05W2p40left_highe.png"
		mv "$HISTOPATH/KaonLT_Proton_Run1.root" "$HISTOPATH/KaonLT_Proton_Q05W2p40left_highe.root"
		root -l -b -q "Q05W2p40center_highe.C"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots.pdf" "$OUTPUTPATH/Proton_Kinematics_Q05W2p40center_highe_AllPlots.pdf"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots_coin.png" "$OUTPUTPATH/Proton_Kinematics_Q05W2p40center_highe.png"
		mv "$HISTOPATH/KaonLT_Proton_Run1.root" "$HISTOPATH/KaonLT_Proton_Q05W2p40center_highe.root"
	    	root -l -b -q "Q05W2p40right_highe.C"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots.pdf" "$OUTPUTPATH/Proton_Kinematics_Q05W2p40right_highe_AllPlots.pdf"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots_coin.png" "$OUTPUTPATH/Proton_Kinematics_Q05W2p40right_highe.png"
		mv "$HISTOPATH/KaonLT_Proton_Run1.root" "$HISTOPATH/KaonLT_Proton_Q05W2p40right_highe.root"
	        root -l -b -q "Q05W2p40left_lowe.C"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots.pdf" "$OUTPUTPATH/Proton_Kinematics_Q05W2p40left_lowe_AllPlots.pdf"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots_coin.png" "$OUTPUTPATH/Proton_Kinematics_Q05W2p40left_lowe.png"
		mv "$HISTOPATH/KaonLT_Proton_Run1.root" "$HISTOPATH/KaonLT_Proton_Q05W2p40left_lowe.root"
		root -l -b -q "Q05W2p40center_lowe.C"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots.pdf" "$OUTPUTPATH/Proton_Kinematics_Q05W2p40center_lowe_AllPlots.pdf"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots_coin.png" "$OUTPUTPATH/Proton_Kinematics_Q05W2p40center_lowe.png"
		mv "$HISTOPATH/KaonLT_Proton_Run1.root" "$HISTOPATH/KaonLT_Proton_Q05W2p40center_lowe.root"
		
		sed -i "s/Offset\[3\] = .*/Offset\[3\] = \{44.65, 44.65, 45.15\};/" $REPLAYPATH/UTIL_PROTON/scripts_Yield/ProtonYield.C
		sed -i "s/PromptLow\[3\] = .*/PromptLow\[3\] = \{-2, -2, -2\};/" $REPLAYPATH/UTIL_PROTON/scripts_Yield/ProtonYield.C
		sed -i "s/PromptHigh\[3\] = .*/PromptHigh\[3\] = \{2, 2, 2\};/" $REPLAYPATH/UTIL_PROTON/scripts_Yield/ProtonYield.C
		sed -i "s/RandomLow\[3\] = .*/RandomLow\[3\] = \{6.5, 6.5, 6.5\};/" $REPLAYPATH/UTIL_PROTON/scripts_Yield/ProtonYield.C
		sed -i "s/RandomHigh\[3\] = .*/RandomHigh\[3\] = \{18.5, 18.5, 18.5\};/" $REPLAYPATH/UTIL_PROTON/scripts_Yield/ProtonYield.C
		sed -i "s/new TH2F(\"WvsQ2\",\"Q2 vs W;Q2;W\",.*/new TH2F(\"WvsQ2\",\"Q2 vs W;Q2;W\", 200, 1, 4, 200, 2.5, 3.5);/" $REPLAYPATH/UTIL_PROTON/scripts_Yield/ProtonYield.C
       
		root -l -b -q "Q2p115W2p95left_highe.C"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots.pdf" "$OUTPUTPATH/Proton_Kinematics_Q2p115W2p95left_highe_AllPlots.pdf"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots_coin.png" "$OUTPUTPATH/Proton_Kinematics_Q2p115W2p95left_highe.png"
		mv "$HISTOPATH/KaonLT_Proton_Run1.root" "$HISTOPATH/KaonLT_Proton_Q2p115W2p95left_highe.root"
		root -l -b -q "Q2p115W2p95center_highe.C"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots.pdf" "$OUTPUTPATH/Proton_Kinematics_Q2p115W2p95center_highe_AllPlots.pdf"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots_coin.png" "$OUTPUTPATH/Proton_Kinematics_Q2p115W2p95center_highe.png"
		mv "$HISTOPATH/KaonLT_Proton_Run1.root" "$HISTOPATH/KaonLT_Proton_Q2p115W2p95center_highe.root"
	    	root -l -b -q "Q2p115W2p95right_highe.C"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots.pdf" "$OUTPUTPATH/Proton_Kinematics_Q2p115W2p95right_highe_AllPlots.pdf"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots_coin.png" "$OUTPUTPATH/Proton_Kinematics_Q2p115W2p95right_highe.png"
		mv "$HISTOPATH/KaonLT_Proton_Run1.root" "$HISTOPATH/KaonLT_Proton_Q2p115W2p95right_highe.root"

		sed -i "s/Offset\[3\] = .*/Offset\[3\] = \{43.5, 43.5, 43.65\};/" $REPLAYPATH/UTIL_PROTON/scripts_Yield/ProtonYield.C
	     	root -l -b -q "Q2p115W2p95left_lowe.C"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots.pdf" "$OUTPUTPATH/Proton_Kinematics_Q2p115W2p95left_lowe_AllPlots.pdf"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots_coin.png" "$OUTPUTPATH/Proton_Kinematics_Q2p115W2p95left_lowe.png"
		mv "$HISTOPATH/KaonLT_Proton_Run1.root" "$HISTOPATH/KaonLT_Proton_Q2p115W2p95left_lowe.root"
		root -l -b -q "Q2p115W2p95center_lowe.C"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots.pdf" "$OUTPUTPATH/Proton_Kinematics_Q2p115W2p95center_lowe_AllPlots.pdf"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots_coin.png" "$OUTPUTPATH/Proton_Kinematics_Q2p115W2p95center_lowe.png"
		mv "$HISTOPATH/KaonLT_Proton_Run1.root" "$HISTOPATH/KaonLT_Proton_Q2p115W2p95center_lowe.root"

		sed -i "s/Offset\[3\] = .*/Offset\[3\] = \{44.55, 44.1, 44.85\};/" $REPLAYPATH/UTIL_PROTON/scripts_Yield/ProtonYield.C
		sed -i "s/new TH2F(\"WvsQ2\",\"Q2 vs W;Q2;W\",.*/new TH2F(\"WvsQ2\",\"Q2 vs W;Q2;W\", 200, 1.5, 4.5, 200, 1.5, 3.5);/" $REPLAYPATH/UTIL_PROTON/scripts_Yield/ProtonYield.C
		root -l -b -q "Q3W2p32left_highe.C"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots.pdf" "$OUTPUTPATH/Proton_Kinematics_Q3W2p32left_highe_AllPlots.pdf"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots_coin.png" "$OUTPUTPATH/Proton_Kinematics_Q3W2p32left_highe.png"
		mv "$HISTOPATH/KaonLT_Proton_Run1.root" "$HISTOPATH/KaonLT_Proton_Q3W2p32left_highe.root"
		root -l -b -q "Q3W2p32center_highe.C"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots.pdf" "$OUTPUTPATH/Proton_Kinematics_Q3W2p32center_highe_AllPlots.pdf"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots_coin.png" "$OUTPUTPATH/Proton_Kinematics_Q3W2p32center_highe.png"
		mv "$HISTOPATH/KaonLT_Proton_Run1.root" "$HISTOPATH/KaonLT_Proton_Q3W2p32center_highe.root"

		sed -i "s/Offset\[3\] = .*/Offset\[3\] = \{47.25, 47.1, 47.8\};/" $REPLAYPATH/UTIL_PROTON/scripts_Yield/ProtonYield.C
	    	root -l -b -q "Q3W2p32right_highe.C"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots.pdf" "$OUTPUTPATH/Proton_Kinematics_Q3W2p32right_highe_AllPlots.pdf"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots_coin.png" "$OUTPUTPATH/Proton_Kinematics_Q3W2p32right_highe.png"
		mv "$HISTOPATH/KaonLT_Proton_Run1.root" "$HISTOPATH/KaonLT_Proton_Q3W2p32right_highe.root"

		sed -i "s/Offset\[3\] = .*/Offset\[3\] = \{43.45, 43.3, 43.7\};/" $REPLAYPATH/UTIL_PROTON/scripts_Yield/ProtonYield.C
	     	root -l -b -q "Q3W2p32left_lowe.C"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots.pdf" "$OUTPUTPATH/Proton_Kinematics_Q3W2p32left_lowe_AllPlots.pdf"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots_coin.png" "$OUTPUTPATH/Proton_Kinematics_Q3W2p32left_lowe.png"
		mv "$HISTOPATH/KaonLT_Proton_Run1.root" "$HISTOPATH/KaonLT_Proton_Q3W2p32left_lowe.root"
		root -l -b -q "Q3W2p32center_lowe.C"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots.pdf" "$OUTPUTPATH/Proton_Kinematics_Q3W2p32center_lowe_AllPlots.pdf"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots_coin.png" "$OUTPUTPATH/Proton_Kinematics_Q3W2p32center_lowe.png"
		mv "$HISTOPATH/KaonLT_Proton_Run1.root" "$HISTOPATH/KaonLT_Proton_Q3W2p32center_lowe.root"

		sed -i "s/Offset\[3\] = .*/Offset\[3\] = \{44.45, 44.55, 44.6\};/" $REPLAYPATH/UTIL_PROTON/scripts_Yield/ProtonYield.C
		sed -i "s/new TH2F(\"WvsQ2\",\"Q2 vs W;Q2;W\",.*/new TH2F(\"WvsQ2\",\"Q2 vs W;Q2;W\", 200, 1.5, 4.5, 200, 2.8, 3.8);/" $REPLAYPATH/UTIL_PROTON/scripts_Yield/ProtonYield.C
		root -l -b -q "Q3W3p14left_highe.C"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots.pdf" "$OUTPUTPATH/Proton_Kinematics_Q3W3p14left_highe_AllPlots.pdf"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots_coin.png" "$OUTPUTPATH/Proton_Kinematics_Q3W3p14left_highe.png"
		mv "$HISTOPATH/KaonLT_Proton_Run1.root" "$HISTOPATH/KaonLT_Proton_Q3W3p14left_highe.root"
		root -l -b -q "Q3W3p14center_highe.C"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots.pdf" "$OUTPUTPATH/Proton_Kinematics_Q3W3p14center_highe_AllPlots.pdf"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots_coin.png" "$OUTPUTPATH/Proton_Kinematics_Q3W3p14center_highe.png"
		mv "$HISTOPATH/KaonLT_Proton_Run1.root" "$HISTOPATH/KaonLT_Proton_Q3W3p14center_highe.root"
	    	root -l -b -q "Q3W3p14right_highe.C"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots.pdf" "$OUTPUTPATH/Proton_Kinematics_Q3W3p14right_highe_AllPlots.pdf"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots_coin.png" "$OUTPUTPATH/Proton_Kinematics_Q3W3p14right_highe.png"
		mv "$HISTOPATH/KaonLT_Proton_Run1.root" "$HISTOPATH/KaonLT_Proton_Q3W3p14right_highe.root"

		sed -i "s/Offset\[3\] = .*/Offset\[3\] = \{43.45, 43.55, 43.45\};/" $REPLAYPATH/UTIL_PROTON/scripts_Yield/ProtonYield.C
		root -l -b -q "Q3W3p14left_lowe.C"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots.pdf" "$OUTPUTPATH/Proton_Kinematics_Q3W3p14left_lowe_AllPlots.pdf"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots_coin.png" "$OUTPUTPATH/Proton_Kinematics_Q3W3p14left_lowe.png"
		mv "$HISTOPATH/KaonLT_Proton_Run1.root" "$HISTOPATH/KaonLT_Proton_Q3W3p14left_lowe.root"
		root -l -b -q "Q3W3p14center_lowe.C"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots.pdf" "$OUTPUTPATH/Proton_Kinematics_Q3W3p14center_lowe_AllPlots.pdf"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots_coin.png" "$OUTPUTPATH/Proton_Kinematics_Q3W3p14center_lowe.png"
		mv "$HISTOPATH/KaonLT_Proton_Run1.root" "$HISTOPATH/KaonLT_Proton_Q3W3p14center_lowe.root"
	
		sed -i "s/Offset\[3\] = .*/Offset\[3\] = \{44.4, 44.6, 44.7\};/" $REPLAYPATH/UTIL_PROTON/scripts_Yield/ProtonYield.C
		sed -i "s/new TH2F(\"WvsQ2\",\"Q2 vs W;Q2;W\",.*/new TH2F(\"WvsQ2\",\"Q2 vs W;Q2;W\", 200, 3.0, 6.0, 200, 2.4, 3.4);/" $REPLAYPATH/UTIL_PROTON/scripts_Yield/ProtonYield.C
		root -l -b -q "Q4p4W2p74left_highe.C"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots.pdf" "$OUTPUTPATH/Proton_Kinematics_Q4p4W2p74left_highe_AllPlots.pdf"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots_coin.png" "$OUTPUTPATH/Proton_Kinematics_Q4p4W2p74left_highe.png"
		mv "$HISTOPATH/KaonLT_Proton_Run1.root" "$HISTOPATH/KaonLT_Proton_Q4p4W2p74left_highe.root"
		root -l -b -q "Q4p4W2p74center_highe.C"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots.pdf" "$OUTPUTPATH/Proton_Kinematics_Q4p4W2p74center_highe_AllPlots.pdf"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots_coin.png" "$OUTPUTPATH/Proton_Kinematics_Q4p4W2p74center_highe.png"
		mv "$HISTOPATH/KaonLT_Proton_Run1.root" "$HISTOPATH/KaonLT_Proton_Q4p4W2p74center_highe.root"
	    	root -l -b -q "Q4p4W2p74right_highe.C"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots.pdf" "$OUTPUTPATH/Proton_Kinematics_Q4p4W2p74right_highe_AllPlots.pdf"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots_coin.png" "$OUTPUTPATH/Proton_Kinematics_Q4p4W2p74right_highe.png"
		mv "$HISTOPATH/KaonLT_Proton_Run1.root" "$HISTOPATH/KaonLT_Proton_Q4p4W2p74right_highe.root"

		sed -i "s/Offset\[3\] = .*/Offset\[3\] = \{43.5, 43.7, 43.5\};/" $REPLAYPATH/UTIL_PROTON/scripts_Yield/ProtonYield.C
		root -l -b -q "Q4p4W2p74left_lowe.C"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots.pdf" "$OUTPUTPATH/Proton_Kinematics_Q4p4W2p74left_lowe_AllPlots.pdf"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots_coin.png" "$OUTPUTPATH/Proton_Kinematics_Q4p4W2p74left_lowe.png"
		mv "$HISTOPATH/KaonLT_Proton_Run1.root" "$HISTOPATH/KaonLT_Proton_Q4p4W2p74left_lowe.root"
		root -l -b -q "Q4p4W2p74center_lowe.C"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots.pdf" "$OUTPUTPATH/Proton_Kinematics_Q4p4W2p74center_lowe_AllPlots.pdf"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots_coin.png" "$OUTPUTPATH/Proton_Kinematics_Q4p4W2p74center_lowe.png"
		mv "$HISTOPATH/KaonLT_Proton_Run1.root" "$HISTOPATH/KaonLT_Proton_Q4p4W2p74center_lowe.root"

		sed -i "s/Offset\[3\] = .*/Offset\[3\] = \{44.2, 44.3, 44.4\};/" $REPLAYPATH/UTIL_PROTON/scripts_Yield/ProtonYield.C
		sed -i "s/new TH2F(\"WvsQ2\",\"Q2 vs W;Q2;W\",.*/new TH2F(\"WvsQ2\",\"Q2 vs W;Q2;W\", 200, 4.0, 7.0, 200, 2.8, 3.8);/" $REPLAYPATH/UTIL_PROTON/scripts_Yield/ProtonYield.C
		root -l -b -q "Q5p5W3p02left_highe.C"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots.pdf" "$OUTPUTPATH/Proton_Kinematics_Q5p5W3p02left_highe_AllPlots.pdf"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots_coin.png" "$OUTPUTPATH/Proton_Kinematics_Q5p5W3p02left_highe.png"
		mv "$HISTOPATH/KaonLT_Proton_Run1.root" "$HISTOPATH/KaonLT_Proton_Q5p5W3p02left_highe.root"
		root -l -b -q "Q5p5W3p02center_highe.C"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots.pdf" "$OUTPUTPATH/Proton_Kinematics_Q5p5W3p02center_highe_AllPlots.pdf"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots_coin.png" "$OUTPUTPATH/Proton_Kinematics_Q5p5W3p02center_highe.png"
		mv "$HISTOPATH/KaonLT_Proton_Run1.root" "$HISTOPATH/KaonLT_Proton_Q5p5W3p02center_highe.root"
	    	root -l -b -q "Q5p5W3p02right_highe.C"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots.pdf" "$OUTPUTPATH/Proton_Kinematics_Q5p5W3p02right_highe_AllPlots.pdf"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots_coin.png" "$OUTPUTPATH/Proton_Kinematics_Q5p5W3p02right_highe.png"
		mv "$HISTOPATH/KaonLT_Proton_Run1.root" "$HISTOPATH/KaonLT_Proton_Q5p5W3p02right_highe.root"

		sed -i "s/Offset\[3\] = .*/Offset\[3\] = \{43.5, 43.6, 43.4\};/" $REPLAYPATH/UTIL_PROTON/scripts_Yield/ProtonYield.C
		root -l -b -q "Q5p5W3p02left_lowe.C"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots.pdf" "$OUTPUTPATH/Proton_Kinematics_Q5p5W3p02left_lowe_AllPlots.pdf"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots_coin.png" "$OUTPUTPATH/Proton_Kinematics_Q5p5W3p02left_lowe.png"
		mv "$HISTOPATH/KaonLT_Proton_Run1.root" "$HISTOPATH/KaonLT_Proton_Q5p5W3p02left_lowe.root"
		root -l -b -q "Q5p5W3p02center_lowe.C"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots.pdf" "$OUTPUTPATH/Proton_Kinematics_Q5p5W3p02center_lowe_AllPlots.pdf"
		mv "$OUTPUTPATH/Proton_Kinematics_Run1_AllPlots_coin.png" "$OUTPUTPATH/Proton_Kinematics_Q5p5W3p02center_lowe.png"
		mv "$HISTOPATH/KaonLT_Proton_Run1.root" "$HISTOPATH/KaonLT_Proton_Q5p5W3p02center_lowe.root"
	    )
	    break;;
	[Nn]* ) 
	    exit;;
	* ) echo "Please answer yes or no.";;
    esac
done

exit 0
