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
TH1F *th1_cal, *th1_calCut, *th1_hgcer, *th1_hgcerCut, *th1_aero, *th1_aeroCut;


//variables for cutting trees and plotting
Double_t calEtot, hgcerNpeSum, aeroNpeSum, gtrBeta;

//cuts
const Double_t calEtotLow = 0.5; //unit GeV
const Double_t hgcerNpeSumLow = 1.5; //unit NPE
const Double_t aeroNpeSumLow = 1.5; //unit NPE

Bool_t calCut, hgcerCut, aeroCut;

const Int_t INILENGTH = 64;


//function makes the beta plots and saves them to output file
void makePlots ( TString rootFile1, TString rootFile2, Int_t runNum ) // first root file is assumed to be the before, second is the after.
{

	input1 = new TFile(Form(rootFile1, "READ");
	input2 = new TFile(Form(rootFile2, "READ");
	
	tree1 = dynamic_cast <TTree*> (input1->Get("T")); //get T tree from root files
	tree2 = dynamic_cast <TTree*> (input2->Get("T"));
	
	tree1->SetBranchAddress("P.cal.etot", &calEtot);
	tree1->SetBranchAddress("P.hgcer.npeSum", &hgcerNpeSum);
	tree1->SetBranchAddress("P.aero.npeSum", &aeroNpeSum);
	tree1->SetBranchAddress("P.gtr.beta", &gtrBeta);
	
	// make empty histograms
	beta1 = new TH1F();
	beta2 = new TH1F();
	th1_cal = new TH1F();
	th1_calCut = new TH1F();
	th1_hgcer = new TH1F();
	th1_hgcerCut = new TH1F();
	th1_aero = new TH1F();
	th1_aeroCut = new TH1F();
	
	Int_t nEntries = tree1->GetEntries();
	for(Int_t iEntry = 0; iEntry < nEntries; iEntrie++)
	{
		tree1->GetEntry(iEntry);
		
		th1_cal->Fill(calEtot);
		th1_hgcer->Fill(hgcerNpeSum);
		th1_aero->Fill(aeroNpeSum);
		
		//cuts
		calCut = (calEtot >= calEtotLow);
		hgcerCut = (hgcerNpeSum >= hcgerNpeSumLow);
		aeroCut = (aeroNpeSum >= aeroNpeSumLow);
	
		if(calCut)   { th1_calCut->Fill(calEtot); }
		if(hgcerCut) { th1_hgcerCut->Fill(hgcerNpeSum); }
		if(aeroCut)  { th1_aeroCut->Fill(aeroNpeSum); }
		
		if(calCut && hgcerCut && aeroCut) 
		{
			beta1->Fill(gtrBeta)
		}
	}

	//make canvas for beta comparison plot
	TCanvas *c1 = new TCanvas("c1","c1",10, 10, 1000, 800);
	c1->SetGrid();
   	//gStyle->SetOptTitle(kFALSE);
   	gStyle->SetOptStat("nemr");

	beta1->SetLineColor(kBlue);
	beta1->SetName("Beta_preCalib");
	beta1->SetBinContent(beta1->FindBin(0), 0);
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
	beta2->SetBinContent(beta2->FindBin(0), 0);
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

	
}

void plotBeta (  TString runNumbers ) 
{
	ifstream runNumFile;
	runNumFile.open(runNumbers)
	if (!runNumFile)
	{
		cout << "Runfile that was specified does not exist !!!!!!  \n\n Shuting down!!! \n\n";
		return; 
	}
	
	Int_t *runList;
	Int_t Length = 1, Iteration = 1;
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
		runNumFile >> runList[Length - 1];
		
		Length++;
	}
	runNumFile.close();
	
	TString rootFileName1, rootFileName2;
	//open output File
	Outfile = new TFile ("./Calibration_Plots/BetaComp.root","RECREATE");
	// make dirrectories for putting output
	betaDir = Outfile->mkdir("BetaDists");
	cutsDir = Outfile->mkdir("CutsSummary");
	//Loop over all run numbers
	for(Int_t i = 0; i < Length; i++)
	{
		rootFileName1 = form("../../ROOTfiles/Calib/Hodo/Hodo_Calib_Pt1_%d_-1.root", runList[i]);
		rootFileName2 = form("../../ROOTfiles/Calib/Hodo/Hodo_Calib_Pt3_%d_-1.root", runList[i]);
		
		// make a directory for plots of cut variables by run number
		cutSubDir = cutsDir->mkdir(form("Cuts_Run_%d", runList[i]));
		
		// generate and save plots of delta, with cuts.
		makePlots(rootFileName1, rootFileName2, runList[i]);
	}
	
	Outfile.close();
	return;
}











