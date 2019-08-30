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
  TString Detector = Det;
  TString Outpath;
  TString Histopath;
  TString Rootpath;

  if(Detector == "") {
    cout << "Enter a Detector (HMS or SHMS): ";
    cin >> Detector;
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
    Rootpath = "/volatile/hallc/c-kaonlt/${USER}/ROOTfiles/Pass0/DC_Calib";
  }
  else if(Hostname.Contains("qcd")){
    Outpath = "/volatile/hallc/c-kaonlt/${USER}/OUTPUT/DC_Calib";
    Histopath = "/volatile/hallc/c-kaonlt/${USER}/HISTOGRAMS/DC_Calib";
    Rootpath = "/volatile/hallc/c-kaonlt/${USER}/ROOTfiles/Pass0/DC_Calib";
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
      cout << RunNumber[line_num] << endl; 
      line_num++;
	}
  }
  RunListFile.close();

  // Now we have our run numbers, define and array of files to examine, we'll then pull the histograms we want from them and do something with them
  TFile ROOTfiles[line_numTot];
  //for (Int_t i = 0; i < line_numTot; i++){
  //  ROOTfiles[i] = new TFile(Rootpath + Form("/%s_DC_Calib_Check_%i_-1.root", Det.c_str(), RunNumber[i]));
  //}
 
}
