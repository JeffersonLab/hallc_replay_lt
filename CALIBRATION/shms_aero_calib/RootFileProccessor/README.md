# Aerogel Replay

A ROOT script that extracts data from the beam raw data and exports series of corresponding PMT histograms. Every output ROOT file contains seven Positive and seven negative PMT histograms.
There are two ROOT scripts in the repository. Script `replay.c` uses the TTreeReader interface to iterate the ROOT trees. It works quick but will more likely crash if the input ROOT files are corrupt.
A better ROOT TFile error handling is implemented in the script `replayConv.c` which uses a conventional TTRee::GetEntry() mechanism for reading the tree. The downside of this mechanism is the speed which is about 10 times more slow compared to the TTreeReader.

## How to use

1. Checkout the repository to the folder where the output data will be located.
```
git clone https://github.com/petrstepanov/aerogel-replay/ && cd aerogel-replay
```
2. Tweak the RegExp input filename pattern on the line 14 of the script to match the desired name of the input files.
3. Limit the the output spectra statistics by setting the maximum number of the reads from thetree on the line 77.
4. Run either `replay.c` or `replayConv.c` script specifying the path to the directory containing the raw spectra:

```
root 'replayConv.c("/path/to/the/root/replay/files")'
```
5. Script will automatically scan the directory for the input files and start processing them.

If the script crashes during the run you can restart the script from the desired input filename index. In order to do so specify the starting input filename index on line 13 of the script.