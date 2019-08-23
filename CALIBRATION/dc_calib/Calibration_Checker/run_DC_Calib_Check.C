#include <TProof.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <TSystem.h>

void run_DC_Calib_Check(Int_t RunNumber = 0, Int_t MaxEvent = 0, string Detector = "")
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
  if(Detector == "") {
    cout << "Enter a Detector (HMS or SHMS): ";
    cin >> Detector;
  }
  // Need to convert string to char* for use in form command, do via .c_str()
  if(Hostname.Contains("farm")){
    rootFileNameString = Form("/group/c-kaonlt/USERS/${USER}/hallc_replay_lt/ROOTfilesDCCalib/%s_DC_Calib_Pt2_%i_%i.root", Detector.c_str(), RunNumber, MaxEvent);
  }
  else if(Hostname.Contains("qcd")){
    rootFileNameString = Form("/group/c-kaonlt/USERS/${USER}/hallc_replay_lt/ROOTfilesDCCalib/%s_DC_Calib_Pt2_%i_%i.root", Detector.c_str(), RunNumber, MaxEvent);
  }
  else if (Hostname.Contains("cdaq")){
    rootFileNameString = Form("/home/cdaq/hallc-online/hallc_replay_lt/ROOTfilesDCCalib/%s_DC_Calib_Pt2_%i_%i.root", Detector.c_str(), RunNumber, MaxEvent);
  }
  else if (Hostname.Contains("phys.uregina.ca")){
    rootFileNameString = Form("/home/${USER}/work/JLab/hallc_replay_lt/ROOTfilesDCCalib/ROOTfiles_KaonOL/%s_DC_Calib_Pt2_%i_%i.root", Detector.c_str(), RunNumber, MaxEvent);
  }

  TChain ch("T");
  ch.Add(rootFileNameString);
  TString option = Form("%i",RunNumber);
  
  TProof *proof = TProof::Open("workers=4");
  //proof->SetProgressDialog(0);  
  ch.SetProof();
  if (Detector == "HMS"){
    ch.Process("DC_Calib_Check_HMS.C+",option);
  }
  else if (Detector == "SHMS"){
    ch.Process("DC_Calib_Check_SHMS.C+",option);
  }
  else{
    proof->Close();
    cerr << "Error, enter HMS or SHMS as detector \n";
    exit;
  }
 proof->Close();
}
