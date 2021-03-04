// Stephen Kay - University of Regina - 2019 // 

#include <TProof.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

void run_DetTCuts(string RunPrefix = "", Int_t RunNumber = 0, Int_t MaxEvent = 0)
{
  cout << "Script to plot detector timing windows" << endl;
  cout << "Input is RootfilePrefix, run number and number of events" << endl;
  TString Hostname = gSystem->HostName();
  TString User = (gSystem->GetUserInfo())->fUser;
  TString RunPref;
  TString rootFileNameString;
  TString Rootpath;
  TString Outpath;
  TString Histopath;
 
  RunPref = RunPrefix;
  if(RunPref == "") {
    cout << "Enter a Rootfile name prefix (Assumed format is PREFIX_RUN#_#EVENTS.root): ";
    cin >> RunPrefix;
    RunPref = RunPrefix;
  }
  if (RunNumber == 0)
    {
      cout << "Enter a Run Number (-1 to exit): ";
      cin >> RunNumber;
      if (RunNumber <= 0) return;
    }  
  if(MaxEvent == 0) {
    cout << "\nNumber of Events to analyze: ";
    cin >> MaxEvent;
    if(MaxEvent == 0) {
      cerr << "...Invalid entry\n";
      return;
    }
  }

  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  if(Hostname.Contains("farm")){
    Rootpath = "/group/c-pionlt/USERS/"+User+"/hallc_replay_lt/ROOTfiles/";
    Outpath = "/group/c-pionlt/USERS/"+User+"/hallc_replay_lt/OUTPUT/";
    Histopath = "/group/c-pionlt/USERS/"+User+"/hallc_replay_lt/HISTOGRAMS/";
  }
  else if(Hostname.Contains("qcd")){
    Rootpath = "/group/c-pionlt/USERS/"+User+"/hallc_replay_lt/ROOTfiles/";
    Outpath = "/group/c-pionlt/USERS/"+User+"/hallc_replay_lt/OUTPUT/";
    Histopath = "/group/c-pionlt/USERS/"+User+"/hallc_replay_lt/HISTOGRAMS/";
  }
  // Need to change this, probably expliticly require a ROOTfile name as an argument in future (Or just the file prefix)
  else if (Hostname.Contains("phys.uregina.ca")){
    Rootpath = "/dsk3/"+User+"/JLab/ROOTfiles/";
    Outpath = "/dsk3/"+User+"/JLab/OUTPUT/";
    Histopath = "/dsk3/"+User+"/JLab/HISTOGRAMS/";
  }
  rootFileNameString = Rootpath + Form("%s_%i_%i.root", RunPrefix.c_str(), RunNumber, MaxEvent);  
  if (gSystem->AccessPathName(rootFileNameString) == kTRUE){
    cerr << "!!!!! ERROR !!!!! " << endl << rootFileNameString <<  " not found" << endl <<  "!!!!! ERRROR !!!!!" << endl;
    return;
  }
  // Should process a different script for COIN/HMS/SHMS
  TChain ch("T");
  ch.Add(rootFileNameString);
  TString option = Form("%i.Coin", RunNumber);
  TProof *proof = TProof::Open("workers=4");
  ch.SetProof();
  ch.Process("DetTCuts_Coin.C+",option);
  proof->Close();
}
