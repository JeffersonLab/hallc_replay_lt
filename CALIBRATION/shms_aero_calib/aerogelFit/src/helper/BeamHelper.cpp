/*
 * BeamHelper.cpp
 *
 *  Created on: Jul 30, 2020
 *      Author: petrstepanov
 */

#include <iostream>
#include <TFile.h>
#include <TChain.h>
#include <TH2F.h>
#include <TTreeReader.h>
#include <TCanvas.h>
#include <TString.h>
#include <TSystem.h>
#include <TObjString.h>

#include "BeamHelper.h"
#include "../model/Constants.h"
#include "../utils/HistUtils.h"
#include "../utils/GraphicsUtils.h"
#include "../utils/RootUtils.h"

BeamHelper::BeamHelper(const char* fileNamePath) {
	myFile = new TFile(fileNamePath);
	if (myFile->IsZombie()) {
		std::cout << "Error opening file \"" << fileNamePath << "\""<< std::endl;
	}

	// Print list of keys in ROOT file
	TList *keys = myFile->GetListOfKeys();
	keys->Print();

	histogramsPositive = new TList();
	histogramsNegative = new TList();

	// Extract positive and negative hists
	for (UInt_t i = 0; i <= keys->LastIndex(); i++){
		TH1D *hist;
		TString key = ((TObjString*)keys->At(i))->GetString();
		myFile->GetObject(key.Data(), hist);
		if (hist){
			if (key.Contains("Positive")){
				histogramsPositive->Add(hist);
			}
			else {
				histogramsNegative->Add(hist);
			}
		}
	}

	// test print histograms
	// histogramsPositive->Print();
	// histogramsNegative->Print();
}

BeamHelper::~BeamHelper(){}

TList* BeamHelper::getHistogramsPositive(){
	return histogramsPositive;
}

TList* BeamHelper::getHistogramsNegative(){
	return histogramsNegative;
}

const char* BeamHelper::getFileName(){
	return myFile->GetName();
}
