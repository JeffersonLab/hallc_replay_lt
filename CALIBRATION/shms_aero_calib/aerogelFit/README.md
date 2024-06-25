# KaonTL Fit

A CERN ROOT based C++ program used for the Kaon LT prototype PMT spectra fitting.

## Description

Program opens a set of ROOT files specified as command line arguments. Class `Constants` parses command line arguments, constructs the list of filenames to be processed. 

<figure>
  <img src="https://raw.githubusercontent.com/petrstepanov/kaonlt-fit/master/resources/kaonlt-fit-diagram.png?1" alt="Diagram of the KaonLT Fit application"style="width: 100%">
 <figcaption>Diagram of the KaonLT Fit application.</figcaption>
</figure> 

Class `TreeHelper` opens each ROOT file and imports the ROOT Tree. Tree name is provided in in `--tree-name=tree1;3 ` command line parameter. The tree contains data from two PMTs. Namely, `tile`, `channel` and `amplitude` and has following structure:

        ************************************************************************************
        *    Row   *     tilel *     tiler *     amp_1 *     amp_2 *      ch_1 *      ch_2 *
        ************************************************************************************
        *        0 *        77 *        93 *         0 *         0 *         0 *         0 *
        *        1 *        75 *        29 *         0 *         0 *         0 *         0 *
        *        2 *       126 *        87 *         0 *         0 *         0 *         0 *
        *      ... *       ... *       ... *       ... *       ... *       ... *       ... *

Optional parameter `--plot-tree=kFALSE` controls whether the original Tree data is plotted. When set to `kTRUE`, program generates 2D histograms with the original Tree data and saves them to the hard drive. These plots look as follows:

<img src="https://raw.githubusercontent.com/petrstepanov/kaonlt-fit/master/resources/tree1;3-ch:tile-amp:tile.png" style="width: 100%">

Program constructs one-dimensional projections for each PMT histogram at the value of Tile (`tilel` for PMT1 and `tiler` for PMT2) equal to a certain value. This threshold value is specified in the `--tile-profile=55` command line argument. An extra condition is added for selection of the data for the projections. Only events with non-zero Tile pairs are considered (`tilel!=0 && tiler!=0`). This provies more clean experimental data. We make sure that there is a hit in each PMT.

Following projections for PMT histograms are obtained:

<img src="https://raw.githubusercontent.com/petrstepanov/kaonlt-fit/master/resources/pmtsCanvas.png" style="width: 100%">

Next the PMT spectra are fit in order to determine the number of the photoelectrons.

## Fit implementation

Fitting is implemented in three different ways: ROOT fit with analytical convolution, ROOT fit with FFT convolution and RooFit. General C++ classes with member functions with parameters are used to create the `TF1` objects used in the fit. [More information here](https://root.cern.ch/doc/master/classTF1.html#F6). 

## Installation on Windows 10

1. Install Ubuntu linux inside Windows Subsystem for Linux (WSL) as described [here](https://medium.com/@petrstepanov/installing-cern-root-in-windows-subsystem-for-linux-wsl-e83533a10a18).

2. Open _Start → Ubuntu_ to launch linux Terminal. Proceed with Installation on Linux below.

P.S. Running the program on older versions of Windows is currently not possible.

## Installation on Linux or macOS

1. Install CERN ROOT on your system. Details can be found [here](https://medium.com/@petrstepanov/install-cern-root-roofit-on-macos-and-linux-for-dummies-df787fd41ef4).

2. Open your Terminal and clone the program folder on your hard drive:

```
mkdir -p ~/Downloads && cd ~/Downloads
git clone https://github.com/petrstepanov/kaonlt-fit
```

3. Create a folder for the out-of-source build. Run CMake project generator to generate the Makefile.
```
rm -rf ./kaonlt-fit-build && mkdir -p ./kaonlt-fit-build && cd ./kaonlt-fit-build
cmake ./../kaonlt-fit
```

4. Compile the source code and link with ROOT libraries into a binary executable. Install the program.
```
make -j`nproc`
sudo make install
```
5. To launch the application type `kaonlt-fit` in Terminal.

## Installation on JLab computing farm

1. Login to the computing farm and source the latest environment:
```
source /site/12gev_phys/softenv.csh 2.4
```

2. Clone the program folder into `~/Downloads` folder:

```
mkdir -p ~/Downloads && cd ~/Downloads
git clone https://github.com/petrstepanov/kaonlt-fit
```

3. Run out-of-source CMake build:
```
rm -rf ./kaonlt-fit-build && mkdir -p ./kaonlt-fit-build && cd ./kaonlt-fit-build
cmake ./../kaonlt-fit
make -j`nproc`
```

4. Launch `kaonlt-fit` with command:
```
cd ~/Downloads/kaonlt-build/
./kaonlt-fit
```

## How to run the program on the Farm

Create a temporaty folder for the analysis. Copy the `/resources/fit-parameters.txt` file into the temporary folder. For instance,
```
mkdir -p /work/hallc/kaon/petrs/SHMS_Stability/ && cd /work/hallc/kaon/petrs/SHMS_Stability/
cp ~/Downloads/kaonlt-fit/resources/fit-params.txt ./
```
Start spectrum analysis by passing following list of parameters to the executable:
```
~/Downloads/kaonlt-fit-build/kaonlt-fit /work/hallc/kaon/petrs/SHMS_Aerogel_replay/result_*.root --params-filename=fit-params.txt --plot-profiles=kFALSE --terms-number=20 --tile-profile=55 --fit=root --ch-fit-min=0.1 --ch-fit-max=10 --ch-fit-range-min=0.5
```

## Generating Eclipse project for development

CMake allows easy generation of the Eclipse IDE project with enchanced development featured (code hilighting, debugging and more). Setup of the project is following:
```
mkdir -p ~/Development && cd ~/Development
git clone https://github.com/petrstepanov/kaonlt-fit
rm -rf ./kaonlt-fit-eclipse && mkdir -p ./kaonlt-fit-eclipse && cd ./kaonlt-fit-eclipse
cmake -G"Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug ../kaonlt-fit
```

Open Eclipse and go to File → Open Projects from File System... Specify the project location in the modal dialog by clicking the "Directory..." button. Locate the ~/Development/glass-prototype/eclipse project folder. Click "Finish".

CMake links program source folder to the project twice: as [Source directory] and [Subprojects]. Indexer is not working correctly when source code is opened in [Source directory]. Therefore we will filter out the [Source Folder] contents from the build and indexer. Right click the [Source directory] node, select "Properties". Go to "Resouce" → "Resource Filters". Click "Add Filter...". Select option buttons "Exclude All", "Files and Folders". In "Filter Details" specify "Name", "matches", "*". Click "Ok", "Apply and Close".

---

Feel free to reach me out with feedback or questions: [stepanovps@gmail.com](mailto:stepanovps@gmail.com)
