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
TDirectory *betaDir, *cutsDir; 

//histograms
TH1F *beta1, *beta2;
TH1F *th1_cal, *th1_calCut, *th1_hgcer, *th1_hgcerCut, *th1_aero, *th1_aeroCut;


//variables for cutting trees and plotting
Double_t calEtot, hgcerNpeSum, aeroNpeSum, gtrBeta;

//cuts
const Double_t calEtotLow = 0.1; //normaized energy
const Double_t hgcerNpeSumLow = 1.5; //unit NPE
const Double_t aeroNpeSumLow = 1.5; //unit NPE

Bool_t calCut, hgcerCut, aeroCut;

const Int_t INILENGTH = 64;
Int_t NumEvents = -1;


//function makes the beta plots and saves them to output file
void makePlots ( TString rootFile1, TString rootFile2, Int_t runNum ) // first root file is assumed to be the before, second is the after.
{

    // make empty histograms
	beta1 = new TH1F("Beta_Pt1", "Beta_Pt1", 120, 0.0, 1.2);
	beta2 = new TH1F("Beta_Pt2", "Beta_Pt2", 120, 0.0, 1.2);
	th1_cal = new TH1F("P.cal.etottracknorm_Pt1", "P.cal.etottracknorm_Pt1", 100, 0.0, 1.5);
	th1_calCut = new TH1F("P.cal.etottracknormCut_Pt1", "P.cal.etottracknormCut_Pt1", 100, 0.0, 1.5);
	th1_hgcer = new TH1F("hgcerNpeSum_Pt1", "hgcerNpeSum_Pt1", 120, 0.0, 30.0);
	th1_hgcerCut = new TH1F("hgcerNpeSumCut_Pt1", "hgcerNpeSumCut_Pt1", 120, 0.0, 30.0);
	th1_aero = new TH1F("aeroNpeSum_Pt1", "aeroNpeSum_Pt1", 120, 0.0, 30.0);
	th1_aeroCut = new TH1F("aeroNpeSumCut_Pt1", "aeroNpeSumCut_Pt1", 120, 0.0, 30.0);

	input1 = new TFile(rootFile1, "READ");
	input2 = new TFile(rootFile2, "READ");
	cout << "\n";
	
	if(!input1 || !input2)
	{
		cout << "File not open properly!\nTried to open:\n     " << rootFile1 << "\nand: " << rootFile2;
		return;
	}
	
	tree1 = dynamic_cast <TTree*> (input1->Get("T")); //get T tree from root files
	tree2 = dynamic_cast <TTree*> (input2->Get("T"));
	
	tree1->SetBranchAddress("P.cal.etottracknorm", &calEtot);
	tree1->SetBranchAddress("P.hgcer.npeSum", &hgcerNpeSum);
	tree1->SetBranchAddress("P.aero.npeSum", &aeroNpeSum);
	tree1->SetBranchAddress("P.gtr.beta", &gtrBeta);
	
	
	
	Int_t nEntries;
	if (NumEvents == -1)
	{
	    nEntries = tree1->GetEntries();
	}else{
	    nEntries = NumEvents;
	}
	cout << "****************************\n" << nEntries << " Entries to be processed in part 1\n";
	for(Int_t iEntry = 0; iEntry < nEntries; iEntry++)
	{
		tree1->GetEntry(iEntry);
		
		th1_cal->Fill(calEtot);
		th1_hgcer->Fill(hgcerNpeSum);
		th1_aero->Fill(aeroNpeSum);
		
		//cuts
		calCut = (calEtot >= calEtotLow);
		hgcerCut = (hgcerNpeSum >= hgcerNpeSumLow);
		aeroCut = (aeroNpeSum >= aeroNpeSumLow);
	
		if(calCut)   { th1_calCut->Fill(calEtot); }
		if(hgcerCut) { th1_hgcerCut->Fill(hgcerNpeSum); }
		if(aeroCut)  { th1_aeroCut->Fill(aeroNpeSum); }
		
		if(calCut && hgcerCut && aeroCut) 
		{
			beta1->Fill(gtrBeta);
		}

		if(iEntry % 100000 == 0) {cout << iEntry << endl;}
	}
	
	//name and set stats, and write to directory all cut summary plots for 1st replay
	th1_cal->SetStats();
	cutsDir->WriteObject(th1_cal, "calEtot_Pt1");
	
	th1_calCut->SetStats();
	cutsDir->WriteObject(th1_calCut, "calEtotCut_Pt1");
	
	th1_hgcer->SetStats();
	cutsDir->WriteObject(th1_hgcer, "hgcerNpeSum_Pt1");
	
	th1_hgcerCut->SetStats();
	cutsDir->WriteObject(th1_hgcerCut, "hgcerNpeSumCut_Pt1");
	
	th1_aero->SetStats();
	cutsDir->WriteObject(th1_aero, "aeroNpeSum_Pt1");
	
	th1_aeroCut->SetStats();
	cutsDir->WriteObject(th1_aeroCut, "aeroNpeSumCut_Pt1");
	
	//to avoid memory leak delete histograms since we make new ones for part 2
	delete(th1_cal); 
	delete(th1_calCut); 
	delete(th1_hgcer);
	delete(th1_hgcerCut); 
	delete(th1_aero);
	delete(th1_aeroCut);
	
	//start again for the second tree
	tree2->SetBranchAddress("P.cal.etottracknorm", &calEtot);
	tree2->SetBranchAddress("P.hgcer.npeSum", &hgcerNpeSum);
	tree2->SetBranchAddress("P.aero.npeSum", &aeroNpeSum);
	tree2->SetBranchAddress("P.gtr.beta", &gtrBeta);
	
	// make empty histograms
	th1_cal = new TH1F("P.cal.etottracknorm_Pt3", "P.cal.etottracknorm_Pt3", 100, 0.0, 1.5);
	th1_calCut = new TH1F("P.cal.etottracknormCut_ Pt3", "P.cal.etottracknormCut_ Pt3", 100, 0.0, 1.5);
	th1_hgcer = new TH1F("hgcerNpeSum_ Pt3", "hgcerNpeSum_ Pt3", 120, 0.0, 30.0);
	th1_hgcerCut = new TH1F("hgcerNpeSumCut_ Pt3", "hgcerNpeSumCut_ Pt3", 120, 0.0, 30.0);
	th1_aero = new TH1F("aeroNpeSum_ Pt3", "aeroNpeSum_ Pt3", 120, 0.0, 30.0);
	th1_aeroCut = new TH1F("aeroNpeSumCut_ Pt3", "aeroNpeSumCut_ Pt3", 120, 0.0, 30.0);
	
	if (NumEvents == -1)
	{
	    nEntries = tree2->GetEntries();
	}else{
	    nEntries = NumEvents;
	}
	cout << "****************************\n" << nEntries << " Entries to be processed in part 3\n";  
	for(Int_t iEntry = 0; iEntry < nEntries; iEntry++)
	{
		tree2->GetEntry(iEntry);
		
		th1_cal->Fill(calEtot);
		th1_hgcer->Fill(hgcerNpeSum);
		th1_aero->Fill(aeroNpeSum);
		
		//cuts
		calCut = (calEtot >= calEtotLow);
		hgcerCut = (hgcerNpeSum >= hgcerNpeSumLow);
		aeroCut = (aeroNpeSum >= aeroNpeSumLow);
	
		if(calCut)   { th1_calCut->Fill(calEtot); }
		if(hgcerCut) { th1_hgcerCut->Fill(hgcerNpeSum); }
		if(aeroCut)  { th1_aeroCut->Fill(aeroNpeSum); }
		
		if(calCut && hgcerCut && aeroCut) 
		{
			beta2->Fill(gtrBeta);
		}
		
		if ( iEntry % 100000 == 0 ) {cout << iEntry << endl;}
	}
	
	//set stats, and write to directory all cut summary plots for 2nd replay
	th1_cal->SetStats();
	cutsDir->WriteObject(th1_cal, "calEtot_Pt3");
	
	th1_calCut->SetStats();
	cutsDir->WriteObject(th1_calCut, "calEtotCut_Pt3");
	
	th1_hgcer->SetStats();
	cutsDir->WriteObject(th1_hgcer, "hgcerNpeSum_Pt3");
	
	th1_hgcerCut->SetStats();
	cutsDir->WriteObject(th1_hgcerCut, "hgcerNpeSumCut_Pt3");
	
	th1_aero->SetStats();
	cutsDir->WriteObject(th1_aero, "aeroNpeSum_Pt3");
	
	th1_aeroCut->SetStats();
	cutsDir->WriteObject(th1_aeroCut, "aeroNpeSumCut_Pt3");
	
	//to avoid memory leak delete histograms since we make new ones for part 3
	delete(th1_cal); 
	delete(th1_calCut); 
	delete(th1_hgcer);
	delete(th1_hgcerCut); 
	delete(th1_aero);
	delete(th1_aeroCut);
	
	//make canvas for beta comparison plot
	TCanvas *c1 = new TCanvas(Form("Beta_Comparison_%d", rumNum),Form("Beta_Comparison_%d", rumNum),10, 10, 1000, 800);
	c1->SetGrid();
   	//gStyle->SetOptTitle(kFALSE);
   	gStyle->SetOptStat("nemr");

	beta1->SetLineColor(kBlue);
	beta1->SetName(Form("Beta_preCalib_Run%d", runNum));
	beta1->SetStats(); //gets stat box
	
	//this makes the stat box
	beta1->Draw();
	gPad->Update();
	
	beta2->SetLineColor(kRed);
	beta2->SetName(Form("Beta_postCalib_Run%d", runNum));
	beta2->SetStats();

	beta2->Draw("sames");
	gPad->Update();
	
	TPaveStats *s1;
	s1 = (TPaveStats*)c1->GetPrimitive("stats");
	s1->SetName("s1");
	s1->SetY1NDC(.4);
	s1->SetY2NDC(.6);
	s1->SetTextColor(kBlue);
			
	TPaveStats *s2;
	s2 = (TPaveStats*)c1->GetPrimitive("stats");
	s2->SetName("s2");
	s2->SetY1NDC(.1);
	s2->SetY2NDC(.3);
	s2->SetTextColor(kRed);
	
	gPad->Update();
	betaDir->WriteObject(c1, Form("Beta_Comp_%d", runNum));
	
	cout << "Finished making plots for run: " << runNum << endl;
	
	delete(tree1);
	delete(tree2);
	
	input1->Close();
	input2->Close();
	
	return;
}

void plotBeta (  Int_t runNumber, Int_t NumEventsInput ) 
{
	gROOT->SetBatch(1);
  	cout << "\n\n";

	cout << "Running Run: '"<<runNumber<<"' for " << NumEventsInput << " Events\n";
	
	Int_t *runList;
	Int_t Length = 0, Iteration = 1;
	NumEvents = NumEventsInput;

	TString rootFileName1, rootFileName2;
	//open output File
	Outfile = new TFile (Form("./Calibration_Plots/BetaComp%d.root", runNumber),"RECREATE");
	// make dirrectories for putting output
	betaDir = Outfile->mkdir("BetaDists");
	cutsDir = Outfile->mkdir("CutsSummary");
	rootFileName1 = Form("../../ROOTfiles/Calib/Hodo/Hodo_Calib_Pt1_%d_-1.root", runNumber);
	rootFileName2 = Form("../../ROOTfiles/Calib/Hodo/Hodo_Calib_Pt3_%d_-1.root", runNumber);
	
	makePlots(rootFileName1, rootFileName2, runNumber);
	
	Outfile->Close();
	return;
}








