// Vijay Kumar, Univerity of Regina - 24/07/20
// vijay36361@gmail.com

#include <TProof.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

// Expected input is, rootfile prefix, number of events per run, number of runs to chain (1 to 3) and run number(s) 
void run_cal(string RunPrefix = "", Int_t NumEvents = 0, Int_t nRuns = 0, Int_t RunNumber1 = 0, Int_t RunNumber2 = 0, Int_t RunNumber3 = 0)
{
  TString Hostname = gSystem->HostName();
  TString User = (gSystem->GetUserInfo())->fUser;
  TString Rootpath;
  TString rootFileNameString1;
  TString rootFileNameString2;
  TString rootFileNameString3;
  TString RunPref;
  
  cout << "Processing HGC calibration, expected input is, rootfile prefix, number of runs to chain (1 to 3), run number(s) and number of events per run" << endl;

  RunPref = RunPrefix;
  if(RunPref == "") {
    cout << "Enter a Rootfile name prefix (Assumed format is PREFIX_RUN#_#EVENTS.root): ";
    cin >> RunPrefix;
    RunPref = RunPrefix;
  }
  if (NumEvents == 0){
    cout << "\nNumber of Events to analyze for all runs: ";
    cin >> NumEvents;
  }
  if(nRuns == 0) {
    cout << "Enter the number of runs to chain (1 to 3): ";
    cin >> nRuns;
    if (nRuns != 1 && nRuns !=2 && nRuns != 3){
      cerr << "...Invalid entry\n";
      cerr << "Enter either 1, 2 or 3\n";
      return;
    }   
  }
  if (RunNumber1 == 0){
    cout << "Enter the first Run Number : ";
    cin >> RunNumber1;
    if (RunNumber1 <= 0) return;
  }
  if(nRuns > 1){
    if (RunNumber2 == 0){
      cout << "Enter second Run Number : ";
      cin >> RunNumber2;
      if (RunNumber2 <= 0) return;
    }
  }
  if(nRuns > 2){
    if (RunNumber3 == 0){
      cout << "Enter third Run Number : ";
      cin >> RunNumber3;
      if (RunNumber3 <= 0) return;
    }
  }
  
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  // Change or add your own paths as needed!
  if(Hostname.Contains("farm")){ 
    Rootpath = "/group/c-kaonlt/USERS/"+User+"/hallc_replay_lt/ROOTfiles/";
  }
  else if(Hostname.Contains("qcd")){
    Rootpath = "/group/c-kaonlt/USERS/"+User+"/hallc_replay_lt/ROOTfiles";
  }
  else if (Hostname.Contains("phys.uregina.ca")){
    Rootpath = "/dsk3/"+User+"/JLab/ROOTfiles/";
  }

  rootFileNameString1 = Rootpath + Form("%s_%i_%i.root", RunPrefix.c_str(), RunNumber1, NumEvents);
  // Check files exist
  if (gSystem->AccessPathName(rootFileNameString1) == kTRUE){
    cerr << "!!!!! ERROR !!!!! " << endl << rootFileNameString1 <<  " not found" << endl <<  "!!!!! ERRROR !!!!!" << endl;
    return; 
  }
  if(nRuns >1){
    rootFileNameString2 = Rootpath + Form("%s_%i_%i.root", RunPrefix.c_str(), RunNumber2, NumEvents);
    if (gSystem->AccessPathName(rootFileNameString2) == kTRUE){
      cerr << "!!!!! ERROR !!!!! " << endl << rootFileNameString2 <<  " not found" << endl <<  "!!!!! ERRROR !!!!!" << endl;
      return; 
    }
  }
  if(nRuns > 2){
    rootFileNameString3 = Rootpath + Form("%s_%i_%i.root", RunPrefix.c_str(), RunNumber3, NumEvents);
    if (gSystem->AccessPathName(rootFileNameString3) == kTRUE){
      cerr << "!!!!! ERROR !!!!! " << endl << rootFileNameString3 <<  " not found" << endl <<  "!!!!! ERRROR !!!!!" << endl;
      return; 
    }
  }
    
  TChain ch("T");
  ch.Add(rootFileNameString1);
  if(nRuns >1){
    ch.Add(rootFileNameString2);
  }
  if (nRuns > 2){
    ch.Add(rootFileNameString3);
  }
  
  TProof *proof = TProof::Open("workers=4");
  TString option;
  if (nRuns==1){
    option = Form("%i,%i", RunNumber1, RunNumber1);
  }
  else if (nRuns == 2){
    option = Form("%i,%i", RunNumber1, RunNumber2);
  }
  else if (nRuns == 3){
    option = Form("%i,%i", RunNumber1, RunNumber3);
  }
  proof->SetProgressDialog(0);  
  ch.SetProof();
  //Start calibration process
  ch.Process("calibration.C",option);

}
