Aerogel Calibration Directory.

This Is the combination of wo sets of scripts.

In the oldCode directory is the old fit method. 
This code does a simple guassian fit to the PMT channel distribution, 
then 1/mean of these fits is saved as the calibration parameters.

The other two dirrectories are for the new fit method. 
The RootFileProccessor directory contains code in oder to preprocesses the replayed root files for the next fitting step.
The aerogel fit dirrectory contains code for the fit function. This code needs to be compiled in order to run.
Further instructions on how to use and compile the code are contained in its readme file.

The second method containes a much more robust fit method, fitting multiple gaussians with exponential tails.
The code fits on the Photo-electron distribution so the mean it gives is actually the percent error from the true mean.
For more details see presentations by Petr Stepenov on the calibration (2020):
https://redmine.jlab.org/attachments/1865
https://redmine.jlab.org/attachments/1864
You can also see the results from Nathan Heinrich's calibration (2023):
https://redmine.jlab.org/attachments/1863