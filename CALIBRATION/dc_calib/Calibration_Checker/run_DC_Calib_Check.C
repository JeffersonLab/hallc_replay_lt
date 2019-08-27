#include <TProof.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <TSystem.h>

void run_DC_Calib_Check(Int_t RunNumber = 0, Int_t MaxEvent = 0, string Detector = "")
{
  TString Hostname = gSystem->HostName();
  TString rootFileNameString1;
  TString rootFileNameString2;
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
    rootFileNameString1 = Form("/group/c-kaonlt/USERS/${USER}/hallc_replay_lt/ROOTfilesDCCalib/%s_DC_Calib_Pt1_%i_%i.root", Detector.c_str(), RunNumber, MaxEvent);
    rootFileNameString2 = Form("/group/c-kaonlt/USERS/${USER}/hallc_replay_lt/ROOTfilesDCCalib/%s_DC_Calib_Pt2_%i_%i.root", Detector.c_str(), RunNumber, MaxEvent);
  }
  else if(Hostname.Contains("qcd")){
    rootFileNameString1 = Form("/group/c-kaonlt/USERS/${USER}/hallc_replay_lt/ROOTfilesDCCalib/%s_DC_Calib_Pt1_%i_%i.root", Detector.c_str(), RunNumber, MaxEvent);
    rootFileNameString2 = Form("/group/c-kaonlt/USERS/${USER}/hallc_replay_lt/ROOTfilesDCCalib/%s_DC_Calib_Pt2_%i_%i.root", Detector.c_str(), RunNumber, MaxEvent);
  }
  else if (Hostname.Contains("cdaq")){
    rootFileNameString1 = Form("/home/cdaq/hallc-online/hallc_replay_lt/ROOTfilesDCCalib/%s_DC_Calib_Pt1_%i_%i.root", Detector.c_str(), RunNumber, MaxEvent);
    rootFileNameString2 = Form("/home/cdaq/hallc-online/hallc_replay_lt/ROOTfilesDCCalib/%s_DC_Calib_Pt2_%i_%i.root", Detector.c_str(), RunNumber, MaxEvent);
  }
  else if (Hostname.Contains("phys.uregina.ca")){
    rootFileNameString1 = Form("/home/${USER}/work/JLab/hallc_replay_lt/ROOTfilesDCCalib/ROOTfiles_KaonOL/%s_DC_Calib_Pt1_%i_%i.root", Detector.c_str(), RunNumber, MaxEvent);
    rootFileNameString2 = Form("/home/${USER}/work/JLab/hallc_replay_lt/ROOTfilesDCCalib/ROOTfiles_KaonOL/%s_DC_Calib_Pt2_%i_%i.root", Detector.c_str(), RunNumber, MaxEvent);
    
}

  TChain ch2("T");
  ch2.Add(rootFileNameString2);
  TString option2 = Form("%i.%i",RunNumber, 2);
  
  TProof *proof2 = TProof::Open("workers=4");
  //proof->SetProgressDialog(0);  
  ch2.SetProof();
  if (Detector == "HMS"){
    ch2.Process("DC_Calib_Check_HMS.C+",option2);
  }
  else if (Detector == "SHMS"){
    ch2.Process("DC_Calib_Check_SHMS.C+",option2);
  }
  else{
    proof2->Close();
    cerr << "Error, enter HMS or SHMS as detector \n";
    exit;
  }
  proof2->Close();
  
  TChain ch1("T");
  ch1.Add(rootFileNameString1);
  TString option1 = Form("%i.%i",RunNumber, 1);
  TProof *proof1 = TProof::Open("workers=4");
  //proof->SetProgressDialog(0);  
  ch1.SetProof();
  if (Detector == "HMS"){
    ch1.Process("DC_Calib_Check_HMS.C+",option1);
  }
  else if (Detector == "SHMS"){
    ch1.Process("DC_Calib_Check_SHMS.C+",option1);
  }
  else{
    proof1->Close();
    cerr << "Error, enter HMS or SHMS as detector \n";
    exit;
  }
 proof1->Close();

}
