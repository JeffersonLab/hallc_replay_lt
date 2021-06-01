/*
	plotBeta.C
	Author: Nathan Heinrich
	
	A short script for compairing the beta distributions of two root files.
	This is set up to do before and after plots for hodoscope calibration.

*/

#include <time.h>
#include <TSystem.h>
#include <TString.h>
#include "TFile.h"
#include "TTree.h"
#include <TNtuple.h>
#include "TCanvas.h"
#include <iostream>
#include <fstream>
#include "TMath.h"
#include "TH1F.h"
#include <TH2.h>
#include <TStyle.h>
#include <TGraph.h>
#include <TROOT.h>
#include <TMath.h>
#include <TLegend.h>
#include <TPaveLabel.h>
#include <TProfile.h>
#include <TPolyLine.h>
#include <TObjArray.h>
#include <TF1.h>

//Files and containers and histograms
TFile *Outfile;
TFile *input1, *input2;
TTree *tree1, *tree2;
TDirectory *betaDir, *cutsDir, *cutSubDir; 

//histograms
TH1F *beta1, *beta2;
TH1F *th1_cal, *th1_calCut, *th1_cer, *th1_cerCut;


//variables for cutting trees and plotting
Double_t calEtot, cerNpeSum, gtrBeta;

//cuts
const Double_t calEtotLow = 0.5; //unit GeV
const Double_t cerNpeSumLow = 1.5; //unit NPE

Bool_t calCut, cerCut;

const Int_t INILENGTH = 64;


//function makes the beta plots and saves them to output file
void makePlots ( TString rootFile1, TString rootFile2, Int_t runNum ) // first root file is assumed to be the before, second is the after.
{

	input1 = new TFile(rootFile1, "READ");
	input2 = new TFile(rootFile2, "READ");
	
	if(!input1 || !input2)
	{
		cout << "File not open properly!\nTried to open:\n     " << rootFile1 << "\nand: " << rootFile2;
		return;
	}
	
	tree1 = dynamic_cast <TTree*> (input1->Get("T")); //get T tree from root files
	tree2 = dynamic_cast <TTree*> (input2->Get("T"));
	
	tree1->SetBranchAddress("H.cal.etot", &calEtot);
	tree1->SetBranchAddress("H.cer.npeSum", &cerNpeSum);
	tree1->SetBranchAddress("H.gtr.beta", &gtrBeta);
	
	// make empty histograms
	beta1 = new TH1F("Beta_Pt1", "Beta_Pt1", 120, 0.0, 1.2);
	beta2 = new TH1F("Beta_Pt2", "Beta_Pt2", 120, 0.0, 1.2);
	th1_cal = new TH1F("calEtot_Pt1", "calEtot_Pt1", 20, 0.0, 20.0);
	th1_calCut = new TH1F("calEtotCut_Pt1", "calEtotCut_Pt1", 20, 0.0, 20.0);
	th1_cer = new TH1F("cerNpeSum_Pt1", "cerNpeSum_Pt1", 20, 0.0, 20.0);
	th1_cerCut = new TH1F("cerNpeSumCut_Pt1", "cerNpeSumCut_Pt1", 20, 0.0, 20.0);
	
	
	Int_t nEntries = tree1->GetEntries();
	cout << "****************************\n" << nEntries << " Entries to be processed in part 1\n";
	for(Int_t iEntry = 0; iEntry < 100000; iEntry++)
	{
		tree1->GetEntry(iEntry);
		
		th1_cal->Fill(calEtot);
		th1_cer->Fill(cerNpeSum);
		
		//cuts
		calCut = (calEtot >= calEtotLow);
		cerCut = (cerNpeSum >= cerNpeSumLow);
	
		if(calCut)   { th1_calCut->Fill(calEtot); }
		if(cerCut) { th1_cerCut->Fill(cerNpeSum); }
		
		if(calCut && cerCut) 
		{
			beta1->Fill(gtrBeta);
		}

		if(iEntry % 100000 == 0) {cout << iEntry << endl;}
	}
	
	//name and set stats, and write to directory all cut summary plots for 1st replay
	th1_cal->SetStats();
	cutSubDir->WriteObject(th1_cal, "calEtot_Pt1");
	
	th1_calCut->SetStats();
	cutSubDir->WriteObject(th1_calCut, "calEtotCut_Pt1");
	
	th1_cer->SetStats();
	cutSubDir->WriteObject(th1_cer, "cerNpeSum_Pt1");
	
	th1_cerCut->SetStats();
	cutSubDir->WriteObject(th1_cerCut, "cerNpeSumCut_Pt1");
	
	//to avoid memory leak delete histograms since we make new ones for part 2
	delete(th1_cal); 
	delete(th1_calCut); 
	delete(th1_cer);
	delete(th1_cerCut); 
	
	//start again for the second tree
	tree2->SetBranchAddress("H.cal.etot", &calEtot);
	tree2->SetBranchAddress("H.cer.npeSum", &cerNpeSum);
	tree2->SetBranchAddress("H.gtr.beta", &gtrBeta);
	
	// make empty histograms
	th1_cal = new TH1F("calEtot_Pt3", "calEtot_Pt3", 20, 0.0, 20.0);
	th1_calCut = new TH1F("calEtotCut_ Pt3", "calEtotCut_ Pt3", 20, 0.0, 20.0);
	th1_cer = new TH1F("cerNpeSum_ Pt3", "cerNpeSum_ Pt3", 20, 0.0, 20.0);
	th1_cerCut = new TH1F("cerNpeSumCut_ Pt3", "cerNpeSumCut_ Pt3", 20, 0.0, 20.0);
	
	nEntries = tree2->GetEntries();
	cout << "****************************\n" << nEntries << " Entries to be processed in part 3\n";  
	for(Int_t iEntry = 0; iEntry < 100000; iEntry++)
	{
		tree2->GetEntry(iEntry);
		
		th1_cal->Fill(calEtot);
		th1_cer->Fill(cerNpeSum);
		
		//cuts
		calCut = (calEtot >= calEtotLow);
		cerCut = (cerNpeSum >= cerNpeSumLow);
	
		if(calCut)   { th1_calCut->Fill(calEtot); }
		if(cerCut) { th1_cerCut->Fill(cerNpeSum); }
		
		if(calCut && cerCut) 
		{
			beta2->Fill(gtrBeta);
		}
		
		if ( iEntry % 100000 == 0 ) {cout << iEntry << endl;}
	}
	
	//set stats, and write to directory all cut summary plots for 2nd replay
	th1_cal->SetStats();
	cutSubDir->WriteObject(th1_cal, "calEtot_Pt3");
	
	th1_calCut->SetStats();
	cutSubDir->WriteObject(th1_calCut, "calEtotCut_Pt3");
	
	th1_cer->SetStats();
	cutSubDir->WriteObject(th1_cer, "cerNpeSum_Pt3");
	
	th1_cerCut->SetStats();
	cutSubDir->WriteObject(th1_cerCut, "cerNpeSumCut_Pt3");
	
	//to avoid memory leak delete histograms since we make new ones for part 3
	delete(th1_cal); 
	delete(th1_calCut); 
	delete(th1_cer);
	delete(th1_cerCut); 

	delete(tree1);
	delete(tree2);
	
	input1.Close();
	delete(input1);
	input2.Close();
	delete(input2);

	cout << "Finished making plots for run: " << runNum << endl;
	
	//make canvas for beta comparison plot
	TCanvas *c1 = new TCanvas("c1","c1",10, 10, 1000, 800);
	c1->SetGrid();
   	//gStyle->SetOptTitle(kFALSE);
   	gStyle->SetOptStat("nemr");

	beta1->SetLineColor(kBlue);
	beta1->SetName("Beta_preCalib");
	beta1->SetStats(); //gets stat box
	
	//this makes the stat box
	beta1->Draw();
	gPad->Update();
	
	TPaveStats *s1;
	s1 = (TPaveStats*)c1->GetPrimitive("stats");
	s1->SetName("s1");
	s1->SetY1NDC(.4);
	s1->SetY2NDC(.6);
	s1->SetTextColor(kBlue);
	
	beta2->SetLineColor(kRed);
	beta2->SetName("Beta_postCalib");
	beta2->SetStats();

	beta2->Draw("sames");
	gPad->Update();
			
	TPaveStats *s2;
	s2 = (TPaveStats*)c1->GetPrimitive("stats");
	s2->SetName("s2");
	s2->SetY1NDC(.1);
	s2->SetY2NDC(.3);
	s2->SetTextColor(kRed);
	
	gPad->Update();
	betaDir->WriteObject(c1, Form("Beta_Comp_%d", runNum));
	
	return;
}

void plotBeta (  TString runNumbers ) 
{
	gROOT->SetBatch(1);
  	cout << "\n\n";
	ifstream runNumFile;
	runNumFile.open(runNumbers);
	if (!runNumFile)
	{
		cout << "Runfile that was specified does not exist !!!!!!  \n\n Shuting down!!! \n\n";
		return; 
	}
	
	Int_t *runList;
	Int_t Length = 0, Iteration = 1;
	runList = new Int_t [INILENGTH];
	
	//fill runlist
	while (!runNumFile.eof())
	{
		// for if there are greater than INILENGTH runs that need to be read in.
		if (Length >= Iteration*INILENGTH)
		{
			Iteration++;
			// copy current list into one that has INILENGTH more spots
			Int_t *temp = new Int_t [Iteration*INILENGTH];
			for (Int_t i = 0; i < Length; i++)
			{
				temp[i] = runList[i];
			}
			//return memory
			delete[] runList;
			//copy pionter into new list location
			runList = temp;
		}
		runNumFile >> runList[Length];
		
		Length++;
	}
	runNumFile.close();
	
	cout << "Processing The following runs:\n";
	for(Int_t i = 0; i < Length; i++)
	{
	  cout << runList[i] << "\n";
	}

	TString rootFileName1, rootFileName2;
	//open output File
	Outfile = new TFile ("./Calibration_Plots/BetaComp.root","RECREATE");
	// make dirrectories for putting output
	betaDir = Outfile->mkdir("BetaDists");
	cutsDir = Outfile->mkdir("CutsSummary");
	//Loop over all run numbers
	for(Int_t i = 0; i < Length; i++)
	{
	    rootFileName1 = Form("../../ROOTfiles/Calib/Hodo/Hodo_Calib_Pt1_%d_-1.root", runList[i]);
	    rootFileName2 = Form("../../ROOTfiles/Calib/Hodo/Hodo_Calib_Pt3_%d_-1.root", runList[i]);
		
		// make a directory for plots of cut variables by run number
		cutSubDir = cutsDir->mkdir(Form("Cuts_Run_%d", runList[i]));
		
		// generate and save plots of delta, with cuts.
		cout << "\n\nprocessing Run " << runList[i] << "\n";
		makePlots(rootFileName1, rootFileName2, runList[i]);
	}
	
	Outfile->Close();
	return;
}











