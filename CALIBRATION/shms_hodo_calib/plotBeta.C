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

void plotBeta ( TString rootFile1, TString rootFile2, int runNumber ) // first root file is assumed to be the before, second is the after.
{

	TFile *input1, *input2;

	input1 = new TFile(Form(rootFile1, "READ");
	input2 = new TFile(Form(rootFile2, "READ");

	TH1 *beta1, *beta2;
	beta1 = (TH1 *)input1->Get("phodo_beta;1");
	beta2 = (TH1 *)input2->Get("phodo_beta;1");

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
	
	//THStack *hs = new THStack("hs", ""); //failed attempt
	//hs->Add(beta1);
	//hs->Add(beta2);
	//hs->Draw();

	//gPad->BuildLegend();
}


