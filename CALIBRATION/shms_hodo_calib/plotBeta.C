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
TH2F *th2_delta1, *th2_xfp1, *th2_yfp1;
TH2F *th2_delta2, *th2_xfp2, *th2_yfp2;
TH1F *th1_delta1, *th1_xfp1, *th1_yfp1;
TH1F *th1_delta2, *th1_xfp2, *th1_yfp2;

//variables for cutting trees and plotting
Double_t calEtot, hgcerNpeSum, aeroNpeSum, gtrBeta;
Double_t delta, xfp, yfp;
Double_t CT;

//cuts
const Double_t calEtotLow = 0.1; //normaized energy
//const Double_t hgcerNpeSumLow = 1.5; //unit NPE
const Double_t hgcerNpeSumLow = 0; //unit NPE
const Double_t aeroNpeSumLow = 1.5; //unit NPE
const Double_t CTcutwidth = 4; //unit ns
const Double_t CTcutcenter = 0; //unit ns

Bool_t calCut, hgcerCut, aeroCut;
Bool_t CoinTimeCut;

const Int_t INILENGTH = 64;
Int_t NumEvents = -1;


//function makes the beta plots and saves them to output file
void makePlots ( TString rootFile1, TString rootFile2, Int_t runNum ) // first root file is assumed to be the before, second is the after.
{

    // make empty histograms
	beta1 = new TH1F("Beta_Pt1", "Beta_Pt1", 120, 0.0, 1.2);
	beta2 = new TH1F("Beta_Pt2", "Beta_Pt2", 120, 0.0, 1.2);
	
	th1_cal = new TH1F("P.cal.etottracknorm_Pt1", "P.cal.etottracknorm_Pt1", 100, 0.0, 1.6);
	th1_calCut = new TH1F("P.cal.etottracknormCut_Pt1", "P.cal.etottracknormCut_Pt1", 100, 0.0, 1.6);
	th1_hgcer = new TH1F("hgcerNpeSum_Pt1", "hgcerNpeSum_Pt1", 120, 0.0, 30.0);
	th1_hgcerCut = new TH1F("hgcerNpeSumCut_Pt1", "hgcerNpeSumCut_Pt1", 120, 0.0, 30.0);
	th1_aero = new TH1F("aeroNpeSum_Pt1", "aeroNpeSum_Pt1", 120, 0.0, 30.0);
	th1_aeroCut = new TH1F("aeroNpeSumCut_Pt1", "aeroNpeSumCut_Pt1", 120, 0.0, 30.0);
	
	th2_delta1 = new TH2F("deltaVBeta_Before", "deltaVBeta_Before", 400, -40.0, 40.0, 100, 0.0, 2.0);
	th2_xfp1 = new TH2F("xfpVbeta_Before", "xfpVbeta_Before", 400, -40.0, 40.0, 100, 0.0, 2.0);
	th2_yfp1 = new TH2F("yfpVbeta_Before", "yfpVbeta_Before", 400, -40.0, 40.0, 100, 0.0, 2.0);
	th2_delta2 = new TH2F("deltaVBeta_After", "deltaVBeta_After", 400, -40.0, 40.0, 100, 0.0, 2.0);
	th2_xfp2 = new TH2F("xfpVbeta_After", "xfpVbeta_After", 400, -40.0, 40.0, 100, 0.0, 2.0);
	th2_yfp2 = new TH2F("yfpVbeta_After", "yfpVbeta_After", 400, -40.0, 40.0, 100, 0.0, 2.0);
	
	th1_delta1 = new TH1F("delta_Before", "delta_Before", 400, -20.0, 20.0);
    th1_xfp1 = new TH1F("xfp_Before", "xfp_Before", 400, -2.0, 2.0);
	th1_yfp1 = new TH1F("yfp_Before", "yfp_Before", 400, -5.0, 5.0);
	th1_delta2 = new TH1F("delta_After", "delta_After", 400, -20.0, 20.0);
	th1_xfp2 = new TH1F("xfp_After", "xfp_After", 400, -2.0, 2.0);
	th1_yfp2 = new TH1F("yfp_After", "yfp_After", 400, -5.0, 5.0);

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
	tree1->SetBranchAddress("P.gtr.dp", &delta);
	tree1->SetBranchAddress("P.dc.x_fp", &xfp);
	tree1->SetBranchAddress("P.dc.y_fp", &yfp);
	tree1->SetBranchAddress("CTime.epiCoinTime_ROC1", &CT);
	
	
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
		CoinTimeCut = (CT > (CTcutcenter - CTcutwidth/2)) || (CT < (CTcutcenter + CTcutwidth/2));
	
		if(calCut)   { th1_calCut->Fill(calEtot); }
		if(hgcerCut) { th1_hgcerCut->Fill(hgcerNpeSum); }
		if(aeroCut)  { th1_aeroCut->Fill(aeroNpeSum); }
		
		if(calCut && hgcerCut && aeroCut && CoinTimeCut) 
		{
			beta1->Fill(gtrBeta);
			th2_delta1->Fill(delta, gtrBeta);
			th2_xfp1->Fill(xfp, gtrBeta);
			th2_yfp1->Fill(yfp, gtrBeta);
			
			th1_delta1->Fill(delta);
            th1_xfp1->Fill(xfp);
			th1_yfp1->Fill(yfp);
		}

		if(iEntry % 100000 == 0) {cout << iEntry << endl;}
	}
	
	TCanvas *PIDCut = new TCanvas("PIDCuts", "PIDCuts", 1200, 2400);
	PIDCut->Divide(2, 3);
	
	
	//name and set stats, and write to directory all cut summary plots for 1st replay
	PIDCut->cd(1);
	th1_cal->SetStats();
	th1_cal->Draw("");
	cutsDir->WriteObject(th1_cal, "calEtot_Pt1");
	
	PIDCut->cd(2);
	th1_calCut->SetStats();
	th1_calCut->Draw("");
	cutsDir->WriteObject(th1_calCut, "calEtotCut_Pt1");
	
	PIDCut->cd(3);
	th1_hgcer->SetStats();
	th1_hgcer->Draw("");
	cutsDir->WriteObject(th1_hgcer, "hgcerNpeSum_Pt1");
	
	PIDCut->cd(4);
	th1_hgcerCut->SetStats();
	th1_hgcerCut->Draw("");
	cutsDir->WriteObject(th1_hgcerCut, "hgcerNpeSumCut_Pt1");
	
	PIDCut->cd(5);
	th1_aero->SetStats();
	th1_aero->Draw("");
	cutsDir->WriteObject(th1_aero, "aeroNpeSum_Pt1");
	
	PIDCut->cd(6);
	th1_aeroCut->SetStats();
	th1_aeroCut->Draw("");
	cutsDir->WriteObject(th1_aeroCut, "aeroNpeSumCut_Pt1");
	
	PIDCut->Print(Form("SHMSBeta_output_%d.pdf(", runNum));
	
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
	tree2->SetBranchAddress("P.gtr.dp", &delta);
	tree2->SetBranchAddress("P.dc.x_fp", &xfp);
	tree2->SetBranchAddress("P.dc.y_fp", &yfp);
	tree2->SetBranchAddress("CTime.epiCoinTime_ROC1", &CT);
	
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
		CoinTimeCut = (CT > (CTcutcenter - CTcutwidth/2)) || (CT < (CTcutcenter + CTcutwidth/2));
	
		if(calCut)   { th1_calCut->Fill(calEtot); }
		if(hgcerCut) { th1_hgcerCut->Fill(hgcerNpeSum); }
		if(aeroCut)  { th1_aeroCut->Fill(aeroNpeSum); }
		
		if(calCut && hgcerCut && aeroCut && CoinTimeCut) 
		{
			beta2->Fill(gtrBeta);
			th2_delta2->Fill(delta, gtrBeta);
			th2_xfp2->Fill(xfp, gtrBeta);
			th2_yfp2->Fill(yfp, gtrBeta);
			
			th1_delta2->Fill(delta);
            th1_xfp2->Fill(xfp);
			th1_yfp2->Fill(yfp);
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
	TCanvas *c1 = new TCanvas(Form("Beta_Comparison_%d", runNum),Form("Beta_Comparison_%d", runNum), 1200, 2400);
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
	c1->Print(Form("SHMSBeta_output_%d.pdf", runNum));
	betaDir->WriteObject(c1, Form("Beta_Comp_%d", runNum));
	
	TCanvas *c2 = new TCanvas(Form("Beta_Comparison2d_%d", runNum),Form("Beta_Comparison2d_%d", runNum), 1200, 2400);
	c2->Divide(2,3);
	
	c2->cd(1);
	gPad->SetLogz(1);
	th2_delta1->Draw("colz");
	
	c2->cd(3);
	gPad->SetLogz(1);
	th2_xfp1->Draw("colz");
	
	c2->cd(5);
	gPad->SetLogz(1);
	th2_yfp1->Draw("colz");
	
	c2->cd(2);
	gPad->SetLogz(1);
	th2_delta2->Draw("colz");
	
	c2->cd(4);
	gPad->SetLogz(1);
	th2_xfp2->Draw("colz");
	
	c2->cd(6);
	gPad->SetLogz(1);
	th2_yfp2->Draw("colz");
	
	c2->Print(Form("SHMSBeta_output_%d.pdf", runNum));
	
	TCanvas *c3 = new TCanvas(Form("Comparison1d_%d", runNum),Form("Comparison1d_%d", runNum), 1200, 2400);
	c3->Divide(2,2);
	
	c3->cd(1);
	th1_delta1->SetLineColor(kBlue);
	th1_delta1->SetName(Form("Delta_preCalib_Run%d", runNum));
	//th1_delta1->SetStats();
	th1_delta1->Draw("");
	gPad->Update();
	
	th1_delta2->SetLineColor(kRed);
	th1_delta2->SetName(Form("Delta_postCalib_Run%d", runNum));
	//th1_delta2->SetStats();
	th1_delta2->Draw("same");
	gPad->Update();
	
	c3->cd(2);
	th1_xfp1->SetLineColor(kBlue);
	th1_xfp1->SetName(Form("Delta_preCalib_Run%d", runNum));
	//th1_xfp1->SetStats();
	th1_xfp1->Draw();
	gPad->Update();
	
	th1_xfp2->SetLineColor(kRed);
	th1_xfp2->SetName(Form("Delta_postCalib_Run%d", runNum));
	//th1_xfp2->SetStats();
	th1_xfp2->Draw("same");
	gPad->Update();
	
	c3->cd(3);
	th1_yfp1->SetLineColor(kBlue);
	th1_yfp1->SetName(Form("Delta_preCalib_Run%d", runNum));
	//th1_yfp1->SetStats();
	th1_yfp1->Draw();
	gPad->Update();
	
	th1_yfp2->SetLineColor(kRed);
	th1_yfp2->SetName(Form("Delta_postCalib_Run%d", runNum));
	//th1_yfp2->SetStats();
	th1_yfp2->Draw("SAME");
	gPad->Update();
	
	c3->Print(Form("SHMSBeta_output_%d.pdf)", runNum));
	
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
	rootFileName1 = Form("../../ROOTfiles/Calib/Hodo/SHMS_Hodo_Calib_Pt1_%d_-1.root", runNumber);
	rootFileName2 = Form("../../ROOTfiles/Calib/Hodo/SHMS_Hodo_Calib_Pt3_%d_-1.root", runNumber);
	
	makePlots(rootFileName1, rootFileName2, runNumber);
	
	Outfile->Close();
	return;
}











