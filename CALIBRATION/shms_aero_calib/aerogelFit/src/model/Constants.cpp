/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Constants.cpp
 * Author: petrstepanov
 *
 * Created on October 29, 2017, 7:34 PM
 */

// Disable warnings for -Wwrite-strings
// https://stackoverflow.com/questions/925179/selectively-remove-warning-message-gcc

#include <iostream>
#include <cstdlib>
#include <utility>
#include "Constants.h"
#include <TObjString.h>
#include <RooRealVar.h>
#include "../utils/StringUtils.h"
#include <TMath.h>


Constants::Constants(){
};

Constants* Constants::instance = NULL;

Constants* Constants::getInstance(){
    if (!instance){
        instance = new Constants;
    }
    return instance;
}
const char* Constants::APPLICATION_NAME = "KaonLT Fit";

// Variable limits set experimentally by zooming into axis
// ----------+-------+------------------+----------------+
// Variable  | bins  | lo_bin_left_edge | hi_bin_up_edge |
// ----------+-------+------------------+----------------+
// Channels  | 21000 |            -1000 |          20000 |
// Tile      |   145 |                1 |            146 |
// Amplitude |  4096 |                0 |           4096 |
// ----------+-------+------------------+----------------+

const Int_t Constants::AMP_MIN = 0;
const Int_t Constants::AMP_MAX = 4096;

const Int_t Constants::N_PX = 1024;

const Int_t Constants::N_BEAM_COLS = 3;

const Double_t Constants::SIGMA_TO_FWHM = TMath::Sqrt(8*TMath::Log(2));

// Parse command line parameters
void Constants::parseParameters(int argc, char* argv[]){
	// Print command line argumants
	// Parameter with zero index [0] is the application name. So we start with [1]
	std::cout << "Command line arguments:" << std::endl;
	for (Int_t i = 1; i < argc; i++){
		std::cout << "\t" << argv[i] << std::endl;
	}

	// Parse arguments into program parameters struct
	std::cout << "\nParsing command line arguments:" << std::endl;
	for (Int_t i = 1; i < argc; i++){
		std::pair<TString,TString> pair = StringUtils::parseParameter(argv[i]);
		if (pair.first == "tree-name"){
			// Name of the TTree in the ROOT file
			parameters.treeName = pair.second;
		}
		else if (pair.first == "plot-tree"){
			// Whether to draw the TTree plots or not
			if (pair.second == "kFALSE" || pair.second == "0"){
				parameters.plotTree = kFALSE;
			}
		}
		else if (pair.first == "plot-profiles"){
			// Whether to draw the TTree plots or not
			if (pair.second == "kFALSE" || pair.second == "0"){
				parameters.plotProfiles = kFALSE;
			}
		}
		else if (pair.first == "tile-profile"){
			// Tile value for the histogram projection
			parameters.tileProfile = atoi(pair.second);
		}
		else if (pair.first == "terms-number"){
			// Number of terms in the fitting function
			parameters.termsNumber = atoi(pair.second);
		}
		else if (pair.first == "convolution-bins"){
			// Number of terms in the fitting function
			parameters.convolutionBins = atoi(pair.second);
		}
		else if (pair.first == "file-name"){
			// Add filename to the list of files
			TObjString* fileName = new TObjString(pair.second);
			parameters.inputFiles->Add(fileName);
		}
		else if (pair.first == "fit-type"){
			pair.second.ToLower();
			if (pair.second == "root-analytical"){
				parameters.fitType = FitType::root;
			} else if (pair.second == "root-fft"){
				parameters.fitType = FitType::rootConv;
			} else if (pair.second == "roofit-fft"){
				parameters.fitType = FitType::rooFit;
			} else if (pair.second == "none"){
				parameters.fitType = FitType::none;
			} else {
				parameters.fitType = FitType::test;
			}
		}
		else if (pair.first == "minimize"){
			pair.second.ToLower();
			if (pair.second == "chi2"){
				parameters.minimize = Minimization::chi2;
			} else {
				parameters.minimize = Minimization::likelihood;
			}
		}
		else if (pair.first == "params-filename"){
			// Name of the file with parameters
			parameters.fitParamsFileName = pair.second;
		}
		else if (pair.first ==  "tile-min"){
			// Number of terms in the fitting function
			parameters.tileMin = atoi(pair.second);
		}
		else if (pair.first ==  "tile-max"){
			// Number of terms in the fitting function
			parameters.tileMax = atoi(pair.second);
		}
		else if (pair.first ==  "ch-min"){
			// Number of terms in the fitting function
			parameters.chMin = atoi(pair.second);
		}
		else if (pair.first ==  "ch-max"){
			// Number of terms in the fitting function
			parameters.chMax = atoi(pair.second);
		}
		else if (pair.first ==  "ch-bins"){
			// Number of terms in the fitting function
			parameters.chBins = atoi(pair.second);
		}
		else if (pair.first ==  "ch-fit-min"){
			// Number of terms in the fitting function
			parameters.chFitMin = atof(pair.second);
		}
		else if (pair.first ==  "ch-fit-max"){
			// Number of terms in the fitting function
			parameters.chFitMax = atof(pair.second);
		}
		else if (pair.first ==  "ch-fit-range-min"){
			// Number of terms in the fitting function
			parameters.chFitRangeMin = atof(pair.second);
		}
		else if (pair.first ==  "param-deviation"){
			// Number of terms in the fitting function
			parameters.paramDeviation = atof(pair.second);
		}
		std::cout << "\t" << pair.first << ": " << pair.second << std::endl;
	}

	// Tweak default parameters values after parameters were processed
	if (parameters.chBins == 0) parameters.chBins = parameters.chMax - parameters.chMin;
	if (parameters.chFitMin == 0) parameters.chFitMin = parameters.chMin;
	if (parameters.chFitMax == 0) parameters.chFitMax = parameters.chMax;
}
