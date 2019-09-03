#include <TProof.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <TSystem.h>
#include <TLegend.h>
#include <TF1.h>
#include <TGraphErrors.h>

void run_DC_Calib_Comp(string Det = "", TString Run_List="")
{
  cout << "Script to compare stability of DC calibration over a series of runs" << endl;
  cout << "Input is detector (HMS or SHMS) and a Run_List path" << endl;
  TString Hostname = gSystem->HostName();
  TString Detector;
  TString Outpath;
  TString Histopath;
  TString Rootpath;
  Detector = Det;
  if(Detector == "") {
    cout << "Enter a Detector (HMS or SHMS): ";
    cin >> Det;
    Detector = Det;
  }
  if(Detector.EqualTo("HMS")) cout << "HMS selected" << endl;
  else if(Detector.EqualTo("SHMS")) cout << "HMS selected" << endl;
  else if((Detector.EqualTo("HMS") == kFALSE) && (Detector.EqualTo("SHMS") == kFALSE) ) {
    cerr << "...Invalid entry, enter HMS or SHMS\n";
    return;
  }
   
  if(Run_List == "") {
    cout << "Enter path to list of runs to be compared: ";
    cin >> Run_List;
    if(gSystem->AccessPathName(Run_List)){
      cerr << "...Invalid file path\n";
      return; 
    }
  }

  // Set some paths
  if(Hostname.Contains("farm")){
    Outpath = "/volatile/hallc/c-kaonlt/${USER}/OUTPUT/DC_Calib";
    Histopath = "/volatile/hallc/c-kaonlt/${USER}/HISTOGRAMS/DC_Calib";
    Rootpath = "/volatile/hallc/c-kaonlt/${USER}/ROOTfiles/DC_Calib/Pass0";
  }
  else if(Hostname.Contains("qcd")){
    Outpath = "/volatile/hallc/c-kaonlt/${USER}/OUTPUT/DC_Calib";
    Histopath = "/volatile/hallc/c-kaonlt/${USER}/HISTOGRAMS/DC_Calib";
    Rootpath = "/volatile/hallc/c-kaonlt/${USER}/ROOTfiles/DC_Calib/Pass0";
  }
  else if (Hostname.Contains("phys.uregina.ca")){
    Outpath = "/dsk3/${USER}/JLab/OUTPUT/DC_Calib";
    Histopath = "/dsk3/${USER}/JLab/HISTOGRAMS/DC_Calib" ;
    Rootpath = "/dsk3/${USER}/JLab/ROOTfiles/DC_Calib" ;
  }

  // Open our list of runs and grab the run numbers
  fstream RunListFile;
  RunListFile.open(Run_List);
  Int_t line_num = 0;
  Int_t line_numTot = 0;
  string line;
  if(RunListFile.is_open()){
    while (getline(RunListFile, line)){
      line_num++;
    }
  }
  RunListFile.clear();
  RunListFile.seekg(0, ios::beg);
  line_numTot =line_num;
  cout << "Reading " <<  line_numTot <<  " lines in file" << endl;
  TString RunString[line_numTot];
  Int_t RunNumber[line_numTot];
  Double_t RunNumberD[line_numTot];
  line_num = 0;
  if(RunListFile.is_open()){
    while (getline(RunListFile, line)){
      RunString[line_num] = line;
      RunNumber[line_num] = RunString[line_num].Atoi();
      RunNumberD[line_num] = RunString[line_num].Atof();
      line_num++;
    }
  }
  RunListFile.close();

  // Now we have our run numbers, run a quick TProof script on them to select events we want and save relevant parameters
  TChain ch("T");
  TString option;
  TProof *proof;  
  for(Int_t i = 0; i < line_numTot; i++){
    proof = TProof::Open("workers=4");  
    option  = Form("%i",RunNumber[i]);
    ch.Add(Rootpath + Form("/%s_DC_Calib_Check_%i_-1.root", Det.c_str(), RunNumber[i]));
    if(Detector.EqualTo("HMS")) ch.Process("DC_Calib_Comp_HMS.C+", option);
    else if(Detector.EqualTo("SHMS")) ch.Process("DC_Calib_Comp_SHMS.C+", option);
    proof->Close();
    ch.Reset();
  }
  
  // Define array of new files we just made containing all the relevant histograms
  TFile *ROOTfiles[line_numTot];
  for (Int_t i = 0; i < line_numTot; i++){
    ROOTfiles[i] = new TFile(Histopath + Form("/%s_DCCalib_Comp_Run%i.root", Det.c_str(), RunNumber[i]));
  } 
  // Define string with planes and then the histogram arrays
  TString Plane[12] = {"1u1", "1u2", "1x1", "1x2", "1v1", "1v2", "2u1", "2u2", "2x1", "2x2", "2v1", "2v2"};
  TString hName1;
  TString hName2;
  TFile *Histogram_file = new TFile("HISTOGRAMS/HMS_DCCalib_Comparison.root","RECREATE");
  TH1F* h1_Residuals[12][line_numTot];
  TH1F* h1_ResidualsExclPlane[12][line_numTot];
  TH1F* HistTemp;
  TF1 *Gauss1 = new TF1("Gauss1", "gaus");
  Gauss1->SetParNames("Amplitude","Mean","Std. Dev.");
  Gauss1->SetParameter(1, 0);
  Gauss1->SetParLimits(1, -0.5, 0.5);
  Double_t Mean[2][12][line_numTot];
  Double_t MeanErr[2][12][line_numTot];
  Double_t StdDev[2][12][line_numTot];
  Double_t StdDevErr[2][12][line_numTot];
  // Pull out desired histograms from file, fit a simple Gaussian to residual plots, extract mean and std deviation of each and store in an array
  TDirectory *DHists = Histogram_file->mkdir("Histograms"); DHists->cd();
  for(Int_t i = 0; i < 12; i ++){ //Loop over planes
    hName1 = "h1_"+Plane[i]+"_Residual";
    hName2 = "h1_ResidualExclPlane_"+Plane[i];
    for(Int_t j = 0; j < line_numTot; j++){ //Loop over all runs
      h1_Residuals[i][j] = (TH1F*)(((TH1F*)ROOTfiles[j]->Get(hName1))->Clone(hName1 + Form("_%i", RunNumber[j])));
      h1_ResidualsExclPlane[i][j] = (TH1F*)(((TH1F*)ROOTfiles[j]->Get(hName2))->Clone(hName2 + Form("_%i", RunNumber[j])));
      h1_Residuals[i][j]->Fit(Gauss1, "Q"); 
      Mean[0][i][j] = Gauss1->GetParameter(1); MeanErr[0][i][j] = Gauss1->GetParError(1); StdDev[0][i][j] = Gauss1->GetParameter(2); StdDevErr[0][i][j] = Gauss1->GetParError(2);
      h1_ResidualsExclPlane[i][j]->Fit(Gauss1, "Q"); 
      Mean[1][i][j] = Gauss1->GetParameter(1); MeanErr[1][i][j] = Gauss1->GetParError(1); StdDev[1][i][j] = Gauss1->GetParameter(2); StdDevErr[1][i][j] = Gauss1->GetParError(2);
      h1_Residuals[i][j]->Write();
      h1_ResidualsExclPlane[i][j]->Write();
    }
  }
  // Have four arrays of values now, plot on a TGraphErrors - Need 1 plot per plane (12) for each quantity (2) and each fit parameter (2)
  TGraphErrors *StabilityPlots[2][2][12]; // Quantity/parameter/plane
  TDirectory *DGraphs = Histogram_file->mkdir("Graphs"); DGraphs->cd(); 
  for(Int_t i = 0; i<12; i++){ // loop over planes
    StabilityPlots[0][0][i] = new TGraphErrors(line_numTot, RunNumberD, Mean[0][i], 0, MeanErr[0][i]);
    StabilityPlots[0][0][i]->SetTitle(Plane[i] + " Residual Mean as a function of Run Number"); StabilityPlots[0][0][i]->SetName(Plane[i] + "ResMean");
    StabilityPlots[0][0][i]->SetMarkerSize(1); StabilityPlots[0][0][i]->SetMarkerStyle(4); StabilityPlots[0][0][i]->SetMarkerColor(2); StabilityPlots[0][0][i]->SetLineColor(2);
    StabilityPlots[0][0][i]->GetXaxis()->SetTitle("Run Number"); StabilityPlots[0][0][i]->GetXaxis()->SetDecimals(kFALSE); 
    StabilityPlots[0][0][i]->GetYaxis()->SetTitle("Residual Mean"); StabilityPlots[0][0][i]->GetYaxis()->SetRangeUser(-0.1, 0.1);
    StabilityPlots[0][0][i]->Write();
    StabilityPlots[0][1][i] = new TGraphErrors(line_numTot, RunNumberD, StdDev[0][i], 0, StdDevErr[0][i]);
    StabilityPlots[0][1][i]->SetTitle(Plane[i] + " Residual #{sigma} as a function of Run Number"); StabilityPlots[0][1][i]->SetName(Plane[i]+"ResStdDev");
    StabilityPlots[0][1][i]->SetMarkerSize(1); StabilityPlots[0][1][i]->SetMarkerStyle(4); StabilityPlots[0][1][i]->SetMarkerColor(2); StabilityPlots[0][1][i]->SetLineColor(2);
    StabilityPlots[0][1][i]->GetXaxis()->SetTitle("Run Number"); StabilityPlots[0][1][i]->GetXaxis()->SetDecimals(kFALSE); 
    StabilityPlots[0][1][i]->GetYaxis()->SetTitle("Residual #{sigma}"); StabilityPlots[0][1][i]->GetYaxis()->SetRangeUser(0, 0.2);
    StabilityPlots[0][1][i]->Write();

    StabilityPlots[1][0][i] = new TGraphErrors(line_numTot, RunNumberD, Mean[1][i], 0, MeanErr[1][i]);
    StabilityPlots[1][0][i]->SetTitle(Plane[i] + " Unbiased Residual Mean as a function of Run Number"); StabilityPlots[1][0][i]->SetName(Plane[i] + "UbResMean");
    StabilityPlots[1][0][i]->SetMarkerSize(1); StabilityPlots[1][0][i]->SetMarkerStyle(4); StabilityPlots[1][0][i]->SetMarkerColor(2); StabilityPlots[1][0][i]->SetLineColor(2);
    StabilityPlots[1][0][i]->GetXaxis()->SetTitle("Run Number"); StabilityPlots[1][0][i]->GetXaxis()->SetDecimals(kFALSE); 
    StabilityPlots[1][0][i]->GetYaxis()->SetTitle("Unbiased Residual Mean"); StabilityPlots[1][0][i]->GetYaxis()->SetRangeUser(-0.1, 0.1);
    StabilityPlots[1][0][i]->Write();
    StabilityPlots[1][1][i] = new TGraphErrors(line_numTot, RunNumberD, StdDev[1][i], 0,  StdDevErr[1][i]);
    StabilityPlots[1][1][i]->SetTitle(Plane[i] + " Unbiased Residual #{sigma} as a function of Run Number"); StabilityPlots[1][1][i]->SetName(Plane[i]+"UbResStdDev");
    StabilityPlots[1][1][i]->SetMarkerSize(1); StabilityPlots[1][1][i]->SetMarkerStyle(4); StabilityPlots[1][1][i]->SetMarkerColor(2); StabilityPlots[1][1][i]->SetLineColor(2);
    StabilityPlots[1][1][i]->GetXaxis()->SetTitle("Run Number"); StabilityPlots[1][1][i]->GetXaxis()->SetDecimals(kFALSE);
    StabilityPlots[1][1][i]->GetYaxis()->SetTitle("Unbiased Residual #{sigma}"); StabilityPlots[1][1][i]->GetYaxis()->SetRangeUser(0, 0.2); 
    StabilityPlots[1][1][i]->Write();
  }
  
  TCanvas *cResMean = new TCanvas("ResMean","Residual Means as a function of run number by Plane",300,100,1000,900);
  cResMean->Divide(3,4);
  for(Int_t i = 0; i<12; i++){ // loop over planes
    cResMean->cd(i+1);
    StabilityPlots[0][0][i]->Draw("AEP");
  }
  TCanvas *cResStdDev = new TCanvas("ResStdDev","Residual Standard Deviation as a function of run number by Plane",300,100,1000,900);
  cResStdDev->Divide(3,4);
  for(Int_t i = 0; i<12; i++){ // loop over planes
    cResStdDev->cd(i+1);
    StabilityPlots[0][1][i]->Draw("AEP");
  }
  TCanvas *cUbResMean = new TCanvas("UbResMean","Unbiased Residual Means as a function of run number by Plane",300,100,1000,900);
  cUbResMean->Divide(3,4);
  for(Int_t i = 0; i<12; i++){ // loop over planes
    cUbResMean->cd(i+1);
    StabilityPlots[1][0][i]->Draw("AEP");
  }
  TCanvas *cUbResStdDev = new TCanvas("UbResStdDev","Unbiased Residual Standard Deviation as a function of run number by Plane",300,100,1000,900);
  cUbResStdDev->Divide(3,4);
  for(Int_t i = 0; i<12; i++){ // loop over planes
    cUbResStdDev->cd(i+1);
    StabilityPlots[1][1][i]->Draw("AEP");
  }
  TString outputpdf = "Test.pdf"; // Temporary name, need to name sensibly
  cResMean->Print(outputpdf+"["); //Opens file without printing anything
  cResMean->Print(outputpdf);
  cResStdDev->Print(outputpdf);
  cUbResMean->Print(outputpdf);
  cUbResStdDev->Print(outputpdf);
  cResMean->Print(outputpdf+"]"); //Closes file without printing anything

  Histogram_file->Close();
}
