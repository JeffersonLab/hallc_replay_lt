#include <TProof.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <TSystem.h>
#include <TLegend.h>

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
  line_num = 0;
  if(RunListFile.is_open()){
    while (getline(RunListFile, line)){
      RunString[line_num] = line;
      RunNumber[line_num] = RunString[line_num].Atoi();
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
  TFile ROOTfiles[line_numTot];
  for (Int_t i = 0; i < line_numTot; i++){
    ROOTfiles[i] = new TFile(Histopath + Form("/%s_DC_Calib_Comp_%Runi.root", Det.c_str(), RunNumber[i]));
  } 
 
  // Define string with planes and then the histogram arrays
  TString Plane[12] = {"1u1", "1u2", "1x1", "1x2", "1v1", "1v2", "2u1", "2u2", "2x1", "2x2", "2v1", "2v2"};
  TString hName1;
  TString hName2;
  TFile *Histogram_file = new TFile("HISTOGRAMS/HMS_DCCalib_Comparison","RECREATE");
  TH1F* h1_Residuals[12][line_numTot];
  TH1F* h1_ResidualsExclPlane[12][line_numTot];
  TH1F* HistTemp;
  // Pull out desired histograms from file
  for(Int_t i = 0; i < 12; i ++){ //Loop over planes
    hName1 = "h1_"+Plane[i]+"_Residual";
    hName2 = "h1_ResidualExclPlane_"+Plane[i];
    for(Int_t j = 0; j < line_numTot; j++){ //Loop over all runs
      //h1_Residuals[i][j] = (TH1F*)(((TH1F*)ROOTfiles[j]->Get(hName1))->Clone(hName1 + Form("_%i", RunNumber[j])));
     //h1_ResidualsExclPlane[i][j] = (TH1F*)(((TH1F*)ROOTfiles[j]->Get(hName2))->Clone(hName2 + Form("_%i", RunNumber[j])));
      //h1_Residuals[i][j]->Write();
      //h1_ResidualsExclPlane[i][j]->Write();
    }
  }
   Histogram_file->Close();
}
