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
      exit;
    }
  }

  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  if(Hostname.Contains("farm")){
    Rootpath = "/group/c-kaonlt/USERS/${USER}/ROOTfiles/";
    Outpath = "/group/c-kaonlt/USERS/${USER}/OUTPUT/";
    Histopath = "/group/c-kaonlt/USERS/${USER}/HISTOGRAMS/";
  }
  else if(Hostname.Contains("qcd")){ // Empty for now, fill in later
    Rootpath = "/group/c-kaonlt/USERS/${USER}/ROOTfiles/";
    Outpath = "/group/c-kaonlt/USERS/${USER}/OUTPUT/";
    Histopath = "/group/c-kaonlt/USERS/${USER}/HISTOGRAMS/";
  }
  // Need to change this, probably expliticly require a ROOTfile name as an argument in future (Or just the file prefix)
  else if (Hostname.Contains("phys.uregina.ca")){
    Rootpath = "/dsk3/${USER}/JLab/ROOTfiles/";
    Outpath = "/dsk3/${USER}/JLab/OUTPUT/";
    Histopath = "/dsk3/${USER}/JLab/HISTOGRAMS/";
  }
  rootFileNameString = Rootpath + Form("%s_%i_%i.root", RunPrefix.c_str(), RunNumber, MaxEvent);  
  cout << rootFileNameString << endl;
  // Should process a different script for COIN/HMS/SHMS
  TChain ch("T");
  ch.Add(rootFileNameString);
  TString option = Form("%i.Coin", RunNumber);
  TProof *proof = TProof::Open("workers=4");
  ch.SetProof();
  ch.Process("DetTCuts_Coin.C+",option);
  proof->Close();
}
