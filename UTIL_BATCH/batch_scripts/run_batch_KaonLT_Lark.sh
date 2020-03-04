#! /bin/bash                                                                                                                                                                                                      

##### A batch submission script by Richard, insert the required script you want to batch run on line 51                                                                                                           
##### Modify required resources as needed!                                                                                                                                   
##### This version is modified to use the batch queueing system on Lark

echo "Running as ${USER}" # Checks who you're running this as'

##Output history file##                                                                                                                                                                                           
historyfile=hist.$( date "+%Y-%m-%d_%H-%M-%S" ).log # Creates a log file

##Output batch script##                                                                                                                                                                                           
batch="${USER}_Job.txt" # The name of the job submission script it'll create each time'

##Input run numbers##                                                                                                                                                                                             
inputFile="/home/${USER}/work/JLab/hallc_replay_lt/UTIL_BATCH/InputRunLists/Carbon_ALL" # Path to your input file which is just a list of run numbers, see templates

auger="augerID.tmp"

while true; do
    read -p "Do you wish to begin a new batch submission? (Please answer yes or no) " yn # Check you actually want to do this
    case $yn in
        [Yy]* )
            i=-1
            (
            ##Reads in input file##                                                                                                                                                                               
            while IFS='' read -r line || [[ -n "$line" ]]; do # Reads each line in the file one by one
                echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
                echo "Run number read from file: $line" # Grabs the run number
                echo ""
                ##Run number#
                runNum=$line
                tmp=tmp
                ##Finds number of lines of input file##
                numlines=$(eval "wc -l < ${inputFile}")
                echo "Job $(( $i + 2 ))/$(( $numlines +1 ))"
                echo "Running ${batch} for ${runNum}"
                cp /dev/null ${batch}
                ##Creation of batch script for submission##                                    
                echo "#!/bin/csh" >> ${batch} # Tells your job which shell to run in
		echo "#PBS -N KaonLT_${runNum}" >> ${batch} # Name your job                                                                           
		echo "#PBS -m abe" >> ${batch} # Email you on job start, end or error
		echo "#PBS -M ${USER}@jlab.org" >>${batch} # Your email address, change it to be what you like
		echo "#PBS -r n" >> ${batch} # Don't re-run if it crashes
		echo "#PBS -o  /home/${USER}/trq_output/${runNum}.out" >> ${batch} # Output directory and file name, set to what you like
		echo "#PBS -e  /home/${USER}/trq_output/${runNum}.err" >> ${batch} # Error output directory and file name
		echo "date" >> ${batch} 
		echo "cd /home/${USER}/work/JLab/hallc_replay_lt/UTIL_BATCH/Analysis_Scripts" >> ${batch} # Tell your job to go to the directory with the script you want to run
		echo "./Full_KaonLT_Lark.csh ${runNum}" >> ${batch} # Run your script, change this to what you like
		echo "date">>${batch}
		echo "exit">>${batch} # End of your job script
		echo "Submitting batch"
                eval "qsub ${batch} 2>/dev/null" # Use qsub to actually submit your job
                echo " "
                i=$(( $i + 1 ))
                string=$(cat ${inputFile} |tr "\n" " ")
                ##Converts input file to an array##                                                                                                                                                               
                rnum=($string)                                                                                                                                                                      
                #eval "jobstat -u ${USER} 2>/dev/null" > ${tmp}
                ##Loop to find ID number of each run number##   
		#for j in "${rnum[@]}"
		#do
		#    if [ $(grep -c $j ${tmp}) -gt 0 ]; then
		#	ID=$(echo $(grep $j ${tmp}) | head -c 8)
		#	augerID[$i]=$ID
		#	echo "${augerID[@]}" >> $auger
		#    fi	
		#done   
		#echo "${rnum[$i]} has an AugerID of ${augerID[$i]}" 
		if [ $i == $numlines ]; then
		    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
		    echo " "
		    echo "###############################################################################################################"
		    echo "############################################ END OF JOB SUBMISSIONS ###########################################"
		    echo "###############################################################################################################"
		    echo " "
		fi
	    done < "$inputFile" # Keeps going till it hits the end of the input file
	    )
	    break;;
        [Nn]* ) 
	    exit;;
        * ) echo "Please answer yes or no.";; # What happens if you enter anything but yes or no
    esac
done
