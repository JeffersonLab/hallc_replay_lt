/*
 * BeamOutputHelper.cpp
 *
 *  Created on: Jul 30, 2020
 *      Author: petrstepanov
 */

#include "BeamOutputHelper.h"
#include <TSystem.h>
#include <iostream>
#include <unistd.h>

BeamOutputHelper::BeamOutputHelper() {
	asciiFile = NULL;
	rootFile = NULL;
}

BeamOutputHelper::~BeamOutputHelper(){}

BeamOutputHelper* BeamOutputHelper::instance = NULL;

BeamOutputHelper* BeamOutputHelper::getInstance(){
    if (!instance){
        instance = new BeamOutputHelper;
    }
    return instance;
}

void BeamOutputHelper::createAsciiHeader(){
	fprintf(asciiFile, "\"Filename\"\t");
	fprintf(asciiFile, "\"Run Number\"\t");

	// Iterate Positive PMT (7 items)
	for (UInt_t j = 0; j < 7; j++){
		for (UInt_t i=0; i < FitParameters::parametersNumber; i++){
			fprintf(asciiFile, "\"%s_%s_%d\"\t", FitParameters::parameterNames[i], "pos", j);
			fprintf(asciiFile, "\"d%s_%s_%d\"\t", FitParameters::parameterNames[i], "pos", j);
		}
		fprintf(asciiFile, "\"chi2_%s_%d\"\t", "pos", j);
	}

	// Iterate Negative PMT (7 items)
	for (UInt_t j = 0; j < 7; j++){
		for (UInt_t i=0; i < FitParameters::parametersNumber; i++){
			fprintf(asciiFile, "\"%s_%s_%d\"\t", FitParameters::parameterNames[i], "neg", j);
			fprintf(asciiFile, "\"d%s_%s_%d\"\t", FitParameters::parameterNames[i], "neg", j);
		}
		fprintf(asciiFile, "\"chi2_%s_%d\"\t", "neg", j);
	}

	fprintf(asciiFile, "\n");
}

void BeamOutputHelper::writeToAsciiNoIndent(const char* string){
	fprintf(asciiFile, "%s", string);
}

void BeamOutputHelper::writeToAscii(const char* string){
	fprintf(asciiFile, "%s\t", string);
}

void BeamOutputHelper::writeToAscii(Double_t* pars, Double_t* parsErr){
	for (UInt_t i=0; i < 7; i++){
		fprintf(asciiFile, "%f\t%f\t", pars[i], parsErr[i]);
	}
}

void BeamOutputHelper::writeToAscii(FitParameters* parameters){
	for (UInt_t i = 0; i < FitParameters::parametersNumber; i++){
		RooRealVar* parameter = (RooRealVar*)(parameters->getList()->find(FitParameters::parameterNames[i]));
		Double_t value = parameter->getVal();
		Double_t error = parameter->getError();
		fprintf(asciiFile, "%f\t%f\t", value, error);
	}
}

void BeamOutputHelper::writeToAscii(Double_t value){
	fprintf(asciiFile, "%f\t", value);
}

void BeamOutputHelper::writeToAscii(Int_t value){
	fprintf(asciiFile, "%d\t", value);
}

int BeamOutputHelper::init(){
	// Check if the file already exists
	// if (access(outputAsciiFileName, F_OK) != -1 ) {
	// 	asciiFile = fopen(outputAsciiFileName, "a");
	// } else {
	// 	asciiFile = fopen(outputAsciiFileName, "w");
	// 	createAsciiHeader();
	// }

	// Open file for the ASCII output
	// Initialize ASCII file with output parameters
	const char* outputAsciiFileName = "beam-output.dat";
	asciiFile = fopen(outputAsciiFileName, "w");
	if (asciiFile == NULL) {
		TString outputAsciiFileNameString = outputAsciiFileName;
		const char* outputAsciiURI = gSystem->PrependPathName(gSystem->WorkingDirectory(), outputAsciiFileNameString);
		std::cout << "Error writing to file \"" << outputAsciiURI << "\"." << std::endl;
		return 1;
	}
	createAsciiHeader();

	// Create ROOT file for the output
	const char* outputRootFileName = "beam-output.root";
	rootFile = new TFile(outputRootFileName, "RECREATE");
	if (rootFile->IsZombie()) {
		TString outputRootFileNameString = outputRootFileName;
		const char* outputRootURI = gSystem->PrependPathName(gSystem->WorkingDirectory(), outputRootFileNameString);
		std::cout << "Error opening file \"" << outputRootURI << "\""<< std::endl;
		return 1;
	}

	return 0;
}

void BeamOutputHelper::writeObjectToRootFile(TObject* object){
	rootFile->WriteObject(object, object->GetName());
}

int BeamOutputHelper::finalize(){
	fclose(asciiFile);
	rootFile->Close();
	return 0;
}

