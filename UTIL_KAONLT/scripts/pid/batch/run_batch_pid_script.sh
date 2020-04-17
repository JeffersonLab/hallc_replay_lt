#! /bin/bash                                                                                                                                                                                                      

##### A batch submission script by Richard, insert the required script you want to batch run on line 51                                                                                                           
##### Modify required resources as needed!                                                                                                                                   

echo "Running as ${USER}"

##Output history file##                                                                                                                                                                                           
historyfile=hist.$( date "+%Y-%m-%d_%H-%M-%S" ).log

##Output batch script##                                                                                                                                                                                           
batch="${USER}_Job.txt"

##Input run numbers##                                                                                                                                                                                             
# inputFile="/group/c-kaonlt/USERS/${USER}/hallc_replay_lt/UTIL_BATCH/InputRunLists/Lumi_ALL" 
inputFile="/group/c-kaonlt/USERS/${USER}/hallc_replay_lt/UTIL_KAONLT/scripts/pid/batch/inputRuns" 

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
                tmp=tmp
                ##Finds number of lines of input file##                                                                                                                                                           
                numlines=$(eval "wc -l < ${inputFile}")
                echo "Job $(( $i + 2 ))/$(( $numlines +1 ))"
                echo "Running ${batch} for ${runNum}"
                cp /dev/null ${batch}
                ##Creation of batch script for submission##                                                                                                                                                       
                echo "PROJECT: c-kaonlt" >> ${batch}
                echo "TRACK: analysis" >> ${batch}
                # echo "TRACK: debug" >> ${batch} ### Use for testing                                                                                                                                              
                echo "JOBNAME: KaonLT_${runNum}" >> ${batch}
                echo "DISK_SPACE: 25 GB" >>${batch}                                                                                                                                                              
                echo "MEMORY: 2500 MB" >> ${batch}
                echo "OS: centos7" >> ${batch}
                echo "CPU: 1" >> ${batch} ### hcana single core, setting CPU higher will lower priority!                                                                                                          
		echo "INPUT_FILES: ${tape_file}" >> ${batch}
		#echo "TIME: 1" >> ${batch} 
		echo "COMMAND:/group/c-kaonlt/USERS/${USER}/hallc_replay_lt/UTIL_KAONLT/scripts/pid/pid_script.sh ${runNum}" >> ${batch}                                                        
		echo "MAIL: ${USER}@jlab.org" >> ${batch}
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

rm -rf tmp
