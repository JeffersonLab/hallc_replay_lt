#!/bin/bash                                                                                                                                                                                                      

##### A batch submission script by Richard, insert the required script you want to batch run on line 53                                                                                 
##### Modify required resources as needed! See comments, leave CPU as 1!                                                                      

echo "Running as ${USER}"

##Output history file##                                                                                                                                                                                           
historyfile=hist.$( date "+%Y-%m-%d_%H-%M-%S" ).log

##Output batch script##                                                                                                                                                                                           
batch="${USER}_Job.txt"

##Input run numbers##                                                                      
##Point this to the location of your input run list, see templates folder for examples ##                                                                                                                       
inputFile="/u/group/c-kaonlt/USERS/${USER}/hallc_replay_lt/UTIL_KAONLT/batch/inputRuns"

## Tape stub                                                                                                                                                                                                      
MSSstub='/mss/hallc/spring17/raw/coin_all_%05d.dat'

auger="augerID.tmp"

while true; do
    read -p "Do you wish to begin a new batch submission? (Please answer yes or no) " yn
    case $yn in
        [Yy]* )
            i=-1
            (
            ##Reads in input file##                                                                                                                                                                                
            while IFS='' read -r line || [[ -n "$line" ]]; do
                echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
                echo "Run number read from file: $line"
                echo ""
                ##Run number#                                                                                                                                                                                     
                runNum=$line
                tape_file=`printf $MSSstub $runNum`
		# Print the size of the raw .dat file (converted to GB) to screen. sed command reads line 3 of the tape stub without the leading size=
		echo "Raw .dat file is $(($(sed -n '3 s/^[^=]*= *//p' < $tape_file)/1000000000)) GB"
                tmp=tmp
                ##Finds number of lines of input file##                                                                                                                       
                numlines=$(eval "wc -l < ${inputFile}")
                echo "Job $(( $i + 2 ))/$(( $numlines +1 ))"
                echo "Running ${batch} for ${runNum}"
                cp /dev/null ${batch}
                ##Creation of batch script for submission##                                                                                                                                                       
                echo "PROJECT: c-kaonlt" >> ${batch}
                echo "TRACK: analysis" >> ${batch} ## Use this track for production running
                # echo "TRACK: debug" >> ${batch} ### Use this track for testing, higher priority
                echo "JOBNAME: KaonLT_${runNum}" >> ${batch} ## Change to be more specific if you want
                # Read the tape stub and check the .dat file size. Request disk space dependening upon this. For trunctuated replays edit the + 25 GB buffer down as needed
		# Note, unless this is set typically replays will produce broken root files
		echo "DISK_SPACE: $(($(sed -n '3 s/^[^=]*= *//p' < $tape_file)/1000000000 *2)) GB" >> ${batch}
		echo "MEMORY: 2500 MB" >> ${batch} ## Note, unless NEEDED do not increase this much as it will slow your jobs down
                echo "OS: centos77" >> ${batch}
                echo "CPU: 1" >> ${batch} ### hcana is single core, setting CPU higher will lower priority and gain you nothing!
		echo "INPUT_FILES: ${tape_file}" >> ${batch}
                echo "COMMAND:/u/group/c-kaonlt/USERS/${USER}/hallc_replay_lt/UTIL_KAONLT/Batch_Template.sh ${runNum}" >> ${batch} ### Insert your script at end!                                            
                echo "MAIL: ${USER}@jlab.org" >> ${batch} ## Consider commenting out for large runs unless you enjoy 1k email spam
                echo "Submitting batch"
                eval "jsub ${batch} 2>/dev/null"
                echo " "
                i=$(( $i + 1 ))
                string=$(cat ${inputFile} |tr "\n" " ")
                ##Converts input file to an array##                                                                                                                                                               
                rnum=($string)                                                                                                                                                                      
                eval "jobstat -u ${USER} 2>/dev/null" > ${tmp}
                ##Loop to find ID number of each run number##   
		for j in "${rnum[@]}"
		do
		    if [ $(grep -c $j ${tmp}) -gt 0 ]; then
			ID=$(echo $(grep $j ${tmp}) | head -c 8)
			#ID=$(echo $(grep $j ${tmp}) | head -c 8) 
			augerID[$i]=$ID
			echo "${augerID[@]}" >> $auger
		    fi	
		done   
		echo "${rnum[$i]} has an AugerID of ${augerID[$i]}" 
		if [ $i == $numlines ]; then
		    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
		    echo " "
		    echo "###############################################################################################################"
		    echo "############################################ END OF JOB SUBMISSIONS ###########################################"
		    echo "###############################################################################################################"
		    echo " "	
		fi
		done < "$inputFile"
	     )
	    break;;
        [Nn]* ) 
	        exit;;
        * ) echo "Please answer yes or no.";;
    esac
done

