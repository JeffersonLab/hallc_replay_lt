/*
	Mode10Check.C
	Author: Nathan Heinrich
	This is a peice of code to check the function of the changes to hcana 
	to do with the inclusion of mode 10 data.
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

static const int HGCER_MAX = 16;
static const int HGC_PMT = 4;

// Standard
Int_t hgcer_adcCounterNdata;
double hgcer_adcCounter[HGCER_MAX];
double hgcer_adcPulseAmpRaw[HGCER_MAX];
double hgcer_adcPulseIntRaw[HGCER_MAX];
double hgcer_adcPulseTimeRaw[HGCER_MAX];
double hgcer_adcPulseAmp[HGCER_MAX];
double hgcer_adcPulseInt[HGCER_MAX];
double hgcer_adcPulseTime[HGCER_MAX];

// Mode 10
Int_t hgcer_adcSampCounterNdata;
double hgcer_adcSampCounter[HGCER_MAX];
double hgcer_adcSampPulseAmpRaw[HGCER_MAX];
double hgcer_adcSampPulseIntRaw[HGCER_MAX];
double hgcer_adcSampPulseTimeRaw[HGCER_MAX];
double hgcer_adcSampPulseAmp[HGCER_MAX];
double hgcer_adcSampPulseInt[HGCER_MAX];
double hgcer_adcSampPulseTime[HGCER_MAX];


// multi Pmt Histos
TH2D* hgcer_PMTvPulseAmpRaw;
TH2D* hgcer_PMTvPulseIntRaw;
TH2D* hgcer_PMTvPulseTimeRaw;
TH2D* hgcer_PMTvPulseAmp;
TH2D* hgcer_PMTvPulseInt;
TH2D* hgcer_PMTvPulseTime;

TH2D* hgcer_PMTvSampPulseAmpRaw;
TH2D* hgcer_PMTvSampPulseIntRaw;
TH2D* hgcer_PMTvSampPulseTimeRaw;
TH2D* hgcer_PMTvSampPulseAmp;
TH2D* hgcer_PMTvSampPulseInt;
TH2D* hgcer_PMTvSampPulseTime;

//single pmt comparison histos
TH1D* hgcer_PulseAmpRaw[HGC_PMT];
TH1D* hgcer_PulseIntRaw[HGC_PMT];
TH1D* hgcer_PulseTimeRaw[HGC_PMT];
TH1D* hgcer_PulseAmp[HGC_PMT];
TH1D* hgcer_PulseInt[HGC_PMT];
TH1D* hgcer_PulseTime[HGC_PMT];

TH1D* hgcer_SampPulseAmpRaw[HGC_PMT];
TH1D* hgcer_SampPulseIntRaw[HGC_PMT];
TH1D* hgcer_SampPulseTimeRaw[HGC_PMT];
TH1D* hgcer_SampPulseAmp[HGC_PMT];
TH1D* hgcer_SampPulseInt[HGC_PMT];
TH1D* hgcer_SampPulseTime[HGC_PMT];


void setBranchAddresses(TTree* DataTree)
{
	// regular set
	DataTree->SetBranchAddress("Ndata.P.hgcer.adcCounter", &hgcer_adcCounterNdata);
	DataTree->SetBranchAddress("P.hgcer.adcCounter", hgcer_adcCounter);
	DataTree->SetBranchAddress("P.hgcer.adcPulseAmpRaw", hgcer_adcPulseAmpRaw);
	DataTree->SetBranchAddress("P.hgcer.adcPulseIntRaw", hgcer_adcPulseIntRaw);
	DataTree->SetBranchAddress("P.hgcer.adcPulseTimeRaw", hgcer_adcPulseTimeRaw);
	DataTree->SetBranchAddress("P.hgcer.adcPulseAmp", hgcer_adcPulseAmp);
	DataTree->SetBranchAddress("P.hgcer.adcPulseInt", hgcer_adcPulseInt);
	DataTree->SetBranchAddress("P.hgcer.adcPulseTime", hgcer_adcPulseTime);
	
	// Mode 10 set
	DataTree->SetBranchAddress("Ndata.P.hgcer.adcSampleCounter", &hgcer_adcSampCounterNdata);
	DataTree->SetBranchAddress("P.hgcer.adcSampleCounter", hgcer_adcSampCounter);
	DataTree->SetBranchAddress("P.hgcer.adcSampPulseAmpRaw", hgcer_adcSampPulseAmpRaw);
	DataTree->SetBranchAddress("P.hgcer.adcSampPulseIntRaw", hgcer_adcSampPulseIntRaw);
	DataTree->SetBranchAddress("P.hgcer.adcSampPulseTimeRaw", hgcer_adcSampPulseTimeRaw);
	DataTree->SetBranchAddress("P.hgcer.adcSampPulseAmp", hgcer_adcSampPulseAmp);
	DataTree->SetBranchAddress("P.hgcer.adcSampPulseInt", hgcer_adcSampPulseInt);
	DataTree->SetBranchAddress("P.hgcer.adcSampPulseTime", hgcer_adcSampPulseTime);
	
	return;
}

void makeHistos()
{
	// multi Pmt Histos
	hgcer_PMTvPulseAmpRaw 		= new TH2D("hgcer_PMTvPulseAmpRaw","hgcer_PMTvPulseAmpRaw", HGC_PMT, 0.5, 4.5, 600, 400, 1000);
	hgcer_PMTvPulseIntRaw 		= new TH2D("hgcer_PMTvPulseIntRaw","hgcer_PMTvPulseIntRaw", HGC_PMT, 0.5, 4.5, 1800, 2000, 20000);
	hgcer_PMTvPulseTimeRaw 		= new TH2D("hgcer_PMTvPulseTimeRaw","hgcer_PMTvPulseTimeRaw", HGC_PMT, 0.5, 4.5, 1000, 0, 1000);
	hgcer_PMTvPulseAmp 			= new TH2D("hgcer_PMTvPulseAmp","hgcer_PMTvPulseAmp", HGC_PMT, 0.5, 4.5, 1000, 0, 1000);
	hgcer_PMTvPulseInt 			= new TH2D("hgcer_PMTvPulseInt","hgcer_PMTvPulseInt", HGC_PMT, 0.5, 4.5, 200, 0, 400);
	hgcer_PMTvPulseTime 		= new TH2D("hgcer_PMTvPulseTime","hgcer_PMTvPulseTime", HGC_PMT, 0.5, 4.5, 1000, -1000, 1000);

	hgcer_PMTvSampPulseAmpRaw 	= new TH2D("hgcer_PMTvSampPulseAmpRaw","hgcer_PMTvSampPulseAmpRaw", HGC_PMT, 0.5, 4.5, 600, 400, 1000);
	hgcer_PMTvSampPulseIntRaw 	= new TH2D("hgcer_PMTvSampPulseIntRaw","hgcer_PMTvSampPulseIntRaw", HGC_PMT, 0.5, 4.5, 1800, 2000, 20000);
	hgcer_PMTvSampPulseTimeRaw 	= new TH2D("hgcer_PMTvSampPulseTimeRaw","hgcer_PMTvSampPulseTimeRaw", HGC_PMT, 0.5, 4.5, 500, 0, 1000);
	hgcer_PMTvSampPulseAmp 		= new TH2D("hgcer_PMTvSampPulseAmp","hgcer_PMTvSampPulseAmp", HGC_PMT, 0.5, 4.5, 1000, 0, 1000);
	hgcer_PMTvSampPulseInt 		= new TH2D("hgcer_PMTvSampPulseInt","hgcer_PMTvSampPulseInt", HGC_PMT, 0.5, 4.5, 200, 0, 400);
	hgcer_PMTvSampPulseTime 	= new TH2D("hgcer_PMTvSampPulseTime","hgcer_PMTvSampPulseTime", HGC_PMT, 0.5, 4.5, 1000, -1000, 1000);

	//single pmt comparison histos
	for(int i = 0; i< HGC_PMT; i++)
	{
		hgcer_PulseAmpRaw[i] 	= new TH1D(Form("hgcer_PulseAmpRaw_%d", i+1),Form("hgcer_PulseAmpRaw_%d", i+1), 400, 400, 1000);
		hgcer_PulseIntRaw[i] 	= new TH1D(Form("hgcer_PulseIntRaw_%d", i+1),Form("hgcer_PulseIntRaw_%d", i+1), 1800, 2000, 20000);
		hgcer_PulseTimeRaw[i] 	= new TH1D(Form("hgcer_PulseTimeRaw_%d", i+1),Form("hgcer_PulseTimeRaw_%d", i+1), 500, 0, 1000);
		hgcer_PulseAmp[i] 		= new TH1D(Form("hgcer_PulseAmp_%d", i+1),Form("hgcer_PulseAmp_%d", i+1), 500, 0, 1000);
		hgcer_PulseInt[i] 		= new TH1D(Form("hgcer_PulseInt_%d", i+1),Form("hgcer_PulseInt_%d", i+1), 200, 0, 400);
		hgcer_PulseTime[i] 		= new TH1D(Form("hgcer_PulseTime_%d", i+1),Form("hgcer_PulseTime_%d", i+1), 1000, -1000, 1000);

		hgcer_SampPulseAmpRaw[i]	= new TH1D(Form("hgcer_SampPulseAmpRaw_%d", i+1),Form("hgcer_SampPulseAmpRaw_%d", i+1), 600, 400, 1000);
		hgcer_SampPulseIntRaw[i] 	= new TH1D(Form("hgcer_SampPulseIntRaw_%d", i+1),Form("hgcer_SampPulseIntRaw_%d", i+1), 1800, 2000, 20000);
		hgcer_SampPulseTimeRaw[i] 	= new TH1D(Form("hgcer_SampPulseTimeRaw_%d", i+1),Form("hgcer_SampPulseTimeRaw_%d", i+1), 500, 0, 1000);
		hgcer_SampPulseAmp[i] 		= new TH1D(Form("hgcer_SampPulseAmp_%d", i+1),Form("hgcer_SampPulseAmp_%d", i+1), 500, 0, 1000);
		hgcer_SampPulseInt[i] 		= new TH1D(Form("hgcer_SampPulseInt_%d", i+1),Form("hgcer_SampPulseInt_%d", i+1), 200, 0, 400);
		hgcer_SampPulseTime[i] 		= new TH1D(Form("hgcer_SampPulseTime_%d", i+1),Form("hgcer_SampPulseTime_%d", i+1), 1000, -1000, 1000);
	}
	return;
}

void fillHistos(TTree *DataTree)
{
	Int_t MaxEvents = DataTree->GetEntries();
	cout << "Begining to fill histograms, " << MaxEvents << " events will be processed!\n";
    for(Int_t iEntry = 0; iEntry < MaxEvents; iEntry++)
    {
        DataTree->GetEntry(iEntry);
		
		//regular
		for(int i = 0; i < hgcer_adcCounterNdata; i++)
		{
			hgcer_PMTvPulseAmpRaw->Fill(hgcer_adcCounter[i], hgcer_adcPulseAmpRaw[i]);
			hgcer_PMTvPulseIntRaw->Fill(hgcer_adcCounter[i], hgcer_adcPulseIntRaw[i]);
			hgcer_PMTvPulseTimeRaw->Fill(hgcer_adcCounter[i], hgcer_adcPulseTimeRaw[i]);
			hgcer_PMTvPulseAmp->Fill(hgcer_adcCounter[i], hgcer_adcPulseAmp[i]);
			hgcer_PMTvPulseInt->Fill(hgcer_adcCounter[i], hgcer_adcPulseInt[i]);
			hgcer_PMTvPulseTime->Fill(hgcer_adcCounter[i], hgcer_adcPulseTime[i]);
		
		    int j = hgcer_adcCounter[i]-1;
			if( j < 0 || j > 3) 
			    cout << "Error! j out of bounds!!!!!!\n" << "j = " << j << "\n";
			hgcer_PulseAmpRaw[j]->Fill(hgcer_adcPulseAmpRaw[i]);
			hgcer_PulseIntRaw[j]->Fill(hgcer_adcPulseIntRaw[i]);
			hgcer_PulseTimeRaw[j]->Fill(hgcer_adcPulseTimeRaw[i]);
			hgcer_PulseAmp[j]->Fill(hgcer_adcPulseAmp[i]);
			hgcer_PulseInt[j]->Fill(hgcer_adcPulseInt[i]);
			hgcer_PulseTime[j]->Fill(hgcer_adcPulseTime[i]);
		}
		
		//Mode 10
		for(int i = 0; i < hgcer_adcCounterNdata; i++)
		{
			hgcer_PMTvSampPulseAmpRaw->Fill(hgcer_adcSampCounter[i], hgcer_adcSampPulseAmpRaw[i]);
			hgcer_PMTvSampPulseIntRaw->Fill(hgcer_adcSampCounter[i], hgcer_adcSampPulseIntRaw[i]);
			hgcer_PMTvSampPulseTimeRaw->Fill(hgcer_adcSampCounter[i], hgcer_adcSampPulseTimeRaw[i]);
			hgcer_PMTvSampPulseAmp->Fill(hgcer_adcSampCounter[i], hgcer_adcSampPulseAmp[i]);
			hgcer_PMTvSampPulseInt->Fill(hgcer_adcSampCounter[i], hgcer_adcSampPulseInt[i]);
			hgcer_PMTvSampPulseTime->Fill(hgcer_adcSampCounter[i], hgcer_adcSampPulseTime[i]);
		
		    int k = hgcer_adcSampCounter[i]-1;
		    if( k < 0 || k > 3)
		        cout << "Error! k out of bounds!!!!!!\n" << "k = " << k << "\n";
			hgcer_SampPulseAmpRaw[k]->Fill(hgcer_adcSampPulseAmpRaw[i]);
			hgcer_SampPulseIntRaw[k]->Fill(hgcer_adcSampPulseIntRaw[i]);
			hgcer_SampPulseTimeRaw[k]->Fill(hgcer_adcSampPulseTimeRaw[i]);
			hgcer_SampPulseAmp[k]->Fill(hgcer_adcSampPulseAmp[i]);
			hgcer_SampPulseInt[k]->Fill(hgcer_adcSampPulseInt[i]);
			hgcer_SampPulseTime[k]->Fill(hgcer_adcSampPulseTime[i]);
		}
	}
	return;
}

//function to draw a legend for the 1D plots
void makeLegend(TH1D* hist1, TH1D* hist2)
{
  TLegend* newLeg = new TLegend(0.15,0.85,0.75,0.93);
  newLeg->AddEntry(hist1, hist1->GetName());
  newLeg->AddEntry(hist2, hist2->GetName());
  newLeg->Draw();
}

void Mode10Check (TString rootFileName, int runNum)
{
    //prevent root from displaying graphs while executing
    gROOT->SetBatch(1);
    
	//get root file
    TFile* inFile = new TFile(rootFileName, "READ");
    
    if(!inFile->IsOpen())
    {
        cout << "File did not open properly.\nCheck That: '" << rootFileName << "' exists and is not corrupted.\n --- Ending --- \n";
        return;
    }
    
    //get tree from root file
    TTree *DataTree = dynamic_cast <TTree*> (inFile->Get("T"));
    
    //DataTree->Print();
    setBranchAddresses(DataTree);
    
    //make histograms
    makeHistos();
    
    //fill histos and apply cuts
    fillHistos(DataTree);
    
    cout << "Finished filling plots, saving output!\n";
    
    //save plots
	
	// first set of 2D plots
	TCanvas *MultiCanRaw = new TCanvas(Form("Mode10_hgcerRaw_%d", runNum),Form("Mode10_hgcerRaw_%d", runNum), 1200, 1200);
	MultiCanRaw->cd(1); MultiCanRaw->Divide(3,2);
	MultiCanRaw->cd(1);
	hgcer_PMTvPulseAmpRaw->Draw("colz");
	MultiCanRaw->cd(2);
	hgcer_PMTvPulseIntRaw->Draw("colz");
	MultiCanRaw->cd(3);
	hgcer_PMTvPulseTimeRaw->Draw("colz");
	MultiCanRaw->cd(4);
	hgcer_PMTvSampPulseAmpRaw->Draw("colz");
	MultiCanRaw->cd(5);
	hgcer_PMTvSampPulseIntRaw->Draw("colz");
	MultiCanRaw->cd(6);
	hgcer_PMTvSampPulseTimeRaw->Draw("colz");
	gPad->Modified(); gPad->Update();
	MultiCanRaw->Print(Form("OUTPUT/Analysis/Plots/Mode10_hgcerRaw_%d.png", runNum));
	
	// second set of 2d plots
	TCanvas *MultiCan = new TCanvas(Form("Mode10_hgcer_%d", runNum),Form("Mode10_hgcer_%d", runNum), 1200, 1200);
	MultiCan->cd(1); MultiCan->Divide(3,2);	
	MultiCan->cd(1);
	hgcer_PMTvPulseAmp->Draw("colz");
	gPad->Modified(); gPad->Update();
	
	MultiCan->cd(2);
	hgcer_PMTvPulseInt->Draw("colz");
	gPad->Modified(); gPad->Update();
	
	MultiCan->cd(3);
	hgcer_PMTvPulseTime->Draw("colz");
	gPad->Modified(); gPad->Update();
	
	MultiCan->cd(4);
	hgcer_PMTvSampPulseAmp->Draw("colz");
	gPad->Modified(); gPad->Update();
	
	MultiCan->cd(5);
	hgcer_PMTvSampPulseInt->Draw("colz");
	gPad->Modified(); gPad->Update();
	
	MultiCan->cd(6);
	hgcer_PMTvSampPulseTime->Draw("colz");
    gPad->Modified(); gPad->Update();
	MultiCan->Print(Form("OUTPUT/Analysis/Plots/Mode10_hgcer_%d.png", runNum));

	//fill the other histograms
	TCanvas *HistCan[HGC_PMT]; 
	for(int i = 0; i < HGC_PMT; i++)
	{
		HistCan[i] = new TCanvas(Form("Mode10_hgcerHist%d_%d", i, runNum),Form("Mode10_hgcerHist%d_%d", i, runNum), 1200, 1200);
		HistCan[i]->cd(1); HistCan[i]->Divide(3,2);
		HistCan[i]->cd(1);
		hgcer_PulseAmpRaw[i]->SetLineColor(1);
		hgcer_PulseAmpRaw[i]->Draw();
		hgcer_SampPulseAmpRaw[i]->SetLineColor(4);
		hgcer_SampPulseAmpRaw[i]->Draw("SAME");
		makeLegend(hgcer_PulseAmpRaw[i], hgcer_SampPulseAmpRaw[i]); 
		
		HistCan[i]->cd(2);
		hgcer_PulseIntRaw[i]->SetLineColor(1);
		hgcer_PulseIntRaw[i]->Draw();
		hgcer_SampPulseIntRaw[i]->SetLineColor(4);
		hgcer_SampPulseIntRaw[i]->Draw("SAME");
		makeLegend(hgcer_PulseIntRaw[i], hgcer_SampPulseIntRaw[i]);

		HistCan[i]->cd(3);
		hgcer_PulseTimeRaw[i]->SetLineColor(1);
		hgcer_PulseTimeRaw[i]->Draw();
		hgcer_SampPulseTimeRaw[i]->SetLineColor(4);
		hgcer_SampPulseTimeRaw[i]->Draw("SAME");
		makeLegend(hgcer_PulseTimeRaw[i], hgcer_SampPulseTimeRaw[i]);
		
		HistCan[i]->cd(4);
		hgcer_PulseAmp[i]->SetLineColor(1);
		hgcer_PulseAmp[i]->Draw();
		hgcer_SampPulseAmp[i]->SetLineColor(4);
		hgcer_SampPulseAmp[i]->Draw("SAME");
		makeLegend(hgcer_PulseAmp[i], hgcer_SampPulseAmp[i]);
		
		HistCan[i]->cd(5);
		hgcer_PulseInt[i]->SetLineColor(1);
		hgcer_PulseInt[i]->Draw();
		hgcer_SampPulseInt[i]->SetLineColor(4);
		hgcer_SampPulseInt[i]->Draw("SAME");
		makeLegend(hgcer_PulseInt[i], hgcer_SampPulseInt[i]);
		
		HistCan[i]->cd(6);
		hgcer_PulseTime[i]->SetLineColor(1);
		hgcer_PulseTime[i]->Draw();
		hgcer_SampPulseTime[i]->SetLineColor(4);
		hgcer_SampPulseTime[i]->Draw("SAME");	
		makeLegend(hgcer_PulseTime[i], hgcer_SampPulseTime[i]);
			
		HistCan[i]->Print(Form("OUTPUT/Analysis/Plots/Mode10_hgcerHist%d_%d.png", i, runNum));
	}
	TCanvas* PulseAmpZoom = new TCanvas(Form("Mode10_hgcer_PulseAmp_%d", runNum),Form("Mode10_hgcer_PulseAmp_%d", runNum), 1200, 1200);
	
	PulseAmpZoom->cd(1); PulseAmpZoom->Divide(2,2);	
	PulseAmpZoom->cd(1);
	hgcer_PMTvPulseAmp->GetYaxis()->SetRangeUser(0,50);	
	hgcer_PMTvPulseAmp->Draw("colz");
	gPad->Modified(); gPad->Update();

	PulseAmpZoom->cd(2);
	hgcer_PMTvSampPulseAmp->GetYaxis()->SetRangeUser(0,50);	
	hgcer_PMTvSampPulseAmp->Draw("colz");
	gPad->Modified(); gPad->Update();

	PulseAmpZoom->cd(3);
	hgcer_PMTvPulseAmpRaw->GetYaxis()->SetRangeUser(0,100);	
	hgcer_PMTvPulseAmpRaw->Draw("colz");
	gPad->Modified(); gPad->Update();

	PulseAmpZoom->cd(4);
	hgcer_PMTvSampPulseAmpRaw->GetYaxis()->SetRangeUser(0,100);	
	hgcer_PMTvSampPulseAmpRaw->Draw("colz");
	gPad->Modified(); gPad->Update();

	PulseAmpZoom->Print(Form("OUTPUT/Analysis/Plots/Mode10_hgcer_PulseAmp_%d.png", runNum));

	return;
}



