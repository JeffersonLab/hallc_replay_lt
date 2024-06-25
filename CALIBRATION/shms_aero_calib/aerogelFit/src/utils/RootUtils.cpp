/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   RootUtils.cpp
 * Author: petrstepanov
 *
 * Created on August 24, 2017, 8:16 PM
 */

#include "RootUtils.h"
#include "StringUtils.h"
#include "../model/Constants.h"

#include <TUnixSystem.h>
#include <TGFrame.h>
#include <TObject.h>
#include <TMatrixD.h>
#include <TMatrixDUtils.h>
#include <TString.h>
#include <TObjString.h>
#include <TList.h>
#include <TFile.h>
#include <TFileInfo.h>
#include <TChain.h>
#include <TFileCollection.h>
#include <TSystem.h>
#include <TObjArray.h>

#include <RooHist.h>
#include <RooPlot.h>

#include <iostream>
#include <utility>

void RootUtils::deleteObject(const char* name){
    TObject* obj = gROOT->FindObject(name);
    deleteObject(obj);
}

void RootUtils::deleteObject(TObject* obj){
    if (obj){
        obj->Delete();
    }
}

Int_t RootUtils::getNumCpu(){
    SysInfo_t sysInfo;
    gSystem->GetSysInfo(&sysInfo);
    std::cout << "RootUtils::getNumCpu: sysInfo.fCpus = " << sysInfo.fCpus << std::endl;
    return (sysInfo.fCpus >= 0) ? sysInfo.fCpus : 1;
}

TStopwatch* RootUtils::watch = new TStopwatch();

void RootUtils::startTimer(){
	watch->Reset();
    watch->Start();
}

void RootUtils::stopAndPrintTimer(){
    watch->Stop();
    watch->Print();
	printf("Real time = %7.3f s, Cpu Time = %7.3f s\n", watch->RealTime(), watch->CpuTime());
}

InputFileType RootUtils::getInputFileType(const char* fileName){
	// Open ROOT file
	TFile *myFile = new TFile(fileName);
	if (myFile->IsZombie()) {
		std::cout << "Error opening file \"" << fileName << "\""<< std::endl;
		return InputFileType::Unknown;
	}

	// Get list of keys in ROOT file
	TList *keysList = myFile->GetListOfKeys();

	// Prototype spectra contain "tree1"
	if (keysList->FindObject("tree1")){
		std::cout << "File type is Prototype" << std::endl;
		return InputFileType::Prototype;
	}

	// Prototype spectra contain "tree1"
	if (keysList->FindObject("Positive_PMT_0")){
		std::cout << "File type is Beam" << std::endl;
		return InputFileType::Beam;
	}

	std::cout << "File type is Unknown" << std::endl;
	return InputFileType::Unknown;
}

TChain* RootUtils::buildChain(TList* fileNamesList, const char* treeName){
  TChain* chain = new TChain(treeName);
  for (TObject* object : *fileNamesList) {
    TObjString* objString = (TObjString*)object;
    if (objString){
      chain->Add(objString->GetString().Data());
    }
  }
  return chain;
}

TFile* RootUtils::mergeFiles(TList* fileNamesList){
	// If no files provides
	if (fileNamesList->LastIndex() < 0) return NULL;

	// If one filename provided
	const char* firstFileName = (((TObjString*)fileNamesList->At(0))->GetString()).Data();
	if (fileNamesList->LastIndex() == 0){
		TFile* file = new TFile(firstFileName);
		if (file->IsZombie()) {
			std::cout << "Error opening file \"" << firstFileName << "\""<< std::endl;
			return NULL;
		}
		return file;
	}

	// If multiple filenames provided - import file names into the chain
	// TString* firstFileNameNoExt = StringUtils::extractFilenameNoExtension(firstFileName);
	const char* treeName = Constants::getInstance()->parameters.treeName.Data();
	// TString chainName = TString::Format("chain-%s", firstFileNameNoExt->Data());
	TChain* chain = new TChain(treeName);
	for (TObject* object : *fileNamesList) {
		TObjString* objString = (TObjString*)object;
		if (objString){
			Int_t result = chain->Add(objString->GetString().Data());
			if (result == 0) return NULL;
		}
	}

	// Construct new TFile name and merge TChain into it
	TString* firstFileNameWithExt = StringUtils::extractFilenameWithExtension(firstFileName);
	TString newFileName = firstFileNameWithExt->ReplaceAll(".root", "-all.root");
	const char* absFilePath = gSystem->PrependPathName(gSystem->WorkingDirectory(), newFileName);
	Int_t result = chain->Merge(absFilePath);
	if (result == 0){
		std::cout << "Error merging to file \"" << absFilePath << "\""<< std::endl;
		return NULL;
	}

	// Open merged file and return it
	TFile* file = new TFile(absFilePath);
	if (file->IsZombie()) {
		std::cout << "Error opening file \"" << absFilePath << "\""<< std::endl;
		return NULL;
	}
	return file;
}


void RootUtils::setRooRealVarValueLimits(RooRealVar* var, Double_t value, Double_t min, Double_t max){
	// Tip: roofit can't set min larger than current max and vice versa
	var->setMin(std::numeric_limits<double>::min());
	var->setMax(std::numeric_limits<double>::max());
	var->setMin(min);
	var->setMax(max);
	var->setVal(value);
}

void RootUtils::parseWildcardFileNames(TList* fileNamesList){
	std::cout << "Original files list:" << std::endl;
	fileNamesList->Print();

	// Find wildcard filenames from the input files
	TList* wildcardFileNames = new TList();
	for (TObject* object : *fileNamesList){
		TObjString* objString = (TObjString*)object;
		if (objString){
			TString fileName = objString->GetString();
			if (fileName.Contains("*")){
				wildcardFileNames->Add(objString);
			}
		}
	}
	wildcardFileNames->Print("V");

	// Remove all wildcard filenames from input files
	fileNamesList->RemoveAll(wildcardFileNames);

	// Parse all wildcard filenames with TChain
	TList* wildcardFileNamesParsed = new TList();
	for (TObject* object : *wildcardFileNames){
		TObjString* objString = (TObjString*)object;
		if (objString){
		  TFileCollection* fileCollection = new TFileCollection("fileCollection"); // The name is irrelevant
		  fileCollection->Add(objString->GetString().Data());
		  std::cout << "Expanded file collection wildcard:" << std::endl;
      fileCollection->GetList()->Print("V");

			// Add all
			for (TObject* object : *(fileCollection->GetList())){
			  object->Print("V");
			  TFileInfo* fileInfo = (TFileInfo*)object;
			  if (fileInfo){
			    const char* url = fileInfo->GetCurrentUrl()->GetUrl();
			    std::cout << url << std::endl;
          TObjString* fileName = new TObjString(url);
          wildcardFileNamesParsed->Add(fileName);
			  }
			}
		}
	}

	// Add all passed FileNames to the original list
	fileNamesList->AddAll(wildcardFileNamesParsed);

	std::cout << "Expanded wildcards files list:" << std::endl;
	fileNamesList->Print("V");
}
