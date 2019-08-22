#include <TProof.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <TSystem.h>

void run_DC_Calib_Check(Int_t RunNumber = 0, Int_t MaxEvent = 0, TString Detector = "")
{
  TString Hostname = gSystem->HostName();
  TString rootFileNameString;
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
  if(Detector = "") {
    cout << "Enter a Detector: ";
    cin >> Detector;
   
  }

  //Begin Scaler Efficiency Calculation
  if(Hostname.Contains("farm")){
    rootFileNameString = Form("/group/c-kaonlt/USERS/${USER}/hallc_replay_lt/ROOTfilesDCCalib/%s_DC_Calib_Pt1_%i_%i.root", Detector, RunNumber, MaxEvent);
  }
  else if(Hostname.Contains("qcd")){
    rootFileNameString = Form("/group/c-kaonlt/USERS/${USER}/hallc_replay_lt/ROOTfilesDCCalib/%s_DC_Calib_Pt1_%i_%i.root", Detector, RunNumber, MaxEvent);
  }
  else if (Hostname.Contains("cdaq")){
    rootFileNameString = Form("/home/cdaq/hallc-online/hallc_replay_lt/ROOTfilesDCCalib/%s_DC_Calib_Pt1_%i_%i.root", Detector, RunNumber, MaxEvent);
  }
  else if (Hostname.Contains("phys.uregina.ca")){
    rootFileNameString = Form("/home/${USER}/work/JLab/hallc_replay_lt/ROOTfilesDCCalib/ROOTfiles_KaonOL/%s_DC_Calib_Pt1_%i_%i.root", Detecotr, RunNumber, MaxEvent);
  }
  //Begin Counting Good Proton Events
  TChain ch("T");
  ch.Add(rootFileNameString);
  TString option = Form("%i",RunNumber);

  // Need to add conditional statements to run different processes depending upon spectrometer chosen

  TProof *proof = TProof::Open("workers=4");
  //proof->SetProgressDialog(0);  
  ch.SetProof();
  ch.Process("DC_Calib_Check.C+",option);
  proof->Close();
}
