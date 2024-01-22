#include <TProof.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <TSystem.h>
#include <TLegend.h>
#include <TF1.h>
#include <TGraphErrors.h>
#include <TPaveText.h>

void run_DC_Calib_Comp(Int_t RunNumber = 0, Int_t MaxEvent = 0, string Detector = "")
{
  TString Hostname = gSystem->HostName();
  TString rootFileNameString;
  TString Outpath;
  TString Histopath;
  // Get RunNumber, MaxEvent, and current threshold if not provided.
  if(RunNumber == 0) {
    cout << "Enter a Run Number (-1 to exit): ";
    cin >> RunNumber;
    if( RunNumber<=0 ) return;
  }
  if(MaxEvent == 0) {
    cout << "\nNumber of Events to analyze: ";
    cin >> MaxEvent;
    if(MaxEvent == 0) {
      cerr << "...Invalid entry\n";
      exit;
    }
  }
  if(Detector == "") {
    cout << "Enter a Detector (HMS or SHMS): ";
    cin >> Detector;
  }
  // Need to convert string to char* for use in form command, do via .c_str()
  if(Hostname.Contains("farm")){
    rootFileNameString = Form("/group/c-pionlt/USERS/${USER}/hallc_replay_lt/ROOTfiles/Calib/DC/%s_DC_Calib_Check_Coin_%i_%i.root", Detector.c_str(), RunNumber, MaxEvent);
    Outpath = "/volatile/hallc/c-pionlt/${USER}/OUTPUT/Calib/DC";
    Histopath = "/volatile/hallc/c-pionlt/${USER}/HISTOGRAMS/Calib/DC";
  }
  else if(Hostname.Contains("qcd")){
    rootFileNameString = Form("/group/c-pionlt/USERS/${USER}/hallc_replay_lt/ROOTfiles/Calib/DC/%s_DC_Calib_Check_Coin_%i_%i.root", Detector.c_str(), RunNumber, MaxEvent);
    Outpath = "/volatile/hallc/c-pionlt/${USER}/OUTPUT/Calib/DC";
    Histopath = "/volatile/hallc/c-pionlt/${USER}/HISTOGRAMS/Calib/DC";
  }
  else if (Hostname.Contains("phys.uregina.ca")){
    rootFileNameString = Form("/dsk3/${USER}/JLab/ROOTfiles/DC_Calib/%s_DC_Calib_Check_Coin_%i_%i.root", Detector.c_str(), RunNumber, MaxEvent);
    Outpath = "/dsk3/${USER}/JLab/OUTPUT/Calib/DC";
    Histopath = "/dsk3/${USER}/JLab/HISTOGRAMS/Calib/DC" ;
  }
  else if(Hostname.Contains("cdaq")){
    rootFileNameString = Form("/home/cdaq/pionLT-2021/hallc_replay_lt/ROOTfiles/Calib/DC/%s_DC_Calib_Check_Coin_%i_%i.root", Detector.c_str(), RunNumber, MaxEvent);
    Outpath = "/home/cdaq/pionLT-2021/hallc_replay_lt/OUTPUT/Calib/DC";
    Histopath = "/home/cdaq/pionLT-2021/hallc_replay_lt/HISTOGRAMS/Calib/DC";
    }
 
 TChain ch("T");
  TString option;
  TProof *proof;  
  proof = TProof::Open("workers=4");  
  option  = Form("%i", RunNumber);
  ch.Add(rootFileNameString);
  if(Detector == "HMS") ch.Process("DC_Calib_Comp_HMS.C+", option);
  else if(Detector == "SHMS") ch.Process("DC_Calib_Comp_SHMS.C+", option);
  proof->Close();
  
}
