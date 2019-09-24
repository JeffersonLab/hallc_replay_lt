#include <TProof.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

void run_DetTCuts(Int_t RunNumber = 0, Int_t MaxEvent = 0, string RunType = "")
{
  cout << "Script to plot detector timing windows" << endl;
  cout << "Input is run number, number of events and run type (HMS, SHMS or COIN)" << endl;
  TString Hostname = gSystem->HostName();
  TString RunT;
  TString rootFileNameString;
  TString Outpath;
  TString Histopath;
  
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

  RunT = RunType;
  if(RunT == "") {
    cout << "Enter a Run Type (COIN, HMS or SHMS): ";
    cin >> RunType;
    RunT = RunType;
  }
  if(RunT.EqualTo("HMS")) cout << "HMS singles run selected" << endl;
  else if(RunT.EqualTo("SHMS")) cout << "SHMS singles run selected" << endl;
  else if (RunT.EqualTo("COIN")) cout << "COIN run selected" << endl;
  else if((RunT.EqualTo("HMS") == kFALSE) && (RunT.EqualTo("SHMS") == kFALSE) && (RunT.EqualTo("COIN") == kFALSE)) {
    cerr << "...Invalid entry, enter HMS, SHMS or COIN\n";
    return;
  }
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  if(Hostname.Contains("farm")){
  }
  else if(Hostname.Contains("qcd")){ // Empty for now, fill in later
  }
  else if (Hostname.Contains("phys.uregina.ca")){
    if (RunT.EqualTo("HMS")) rootFileNameString = Form("/dsk3/${USER}/JLab/ROOTfiles/DC_Calib/HMS_DC_Calib_Check_%i_%i.root", RunNumber, MaxEvent); // NOTE, this file name is temporary and only for testing currently
    else if (RunT.EqualTo("SHMS")) rootFileNameString = Form("/dsk3/${USER}/JLab/ROOTfiles/DC_Calib/SHMS_DC_Calib_Check_%i_%i.root", RunNumber, MaxEvent); // NOTE, this file name is temporary and only for testing currently
    else if (RunT.EqualTo("COIN")) rootFileNameString = Form("/dsk3/${USER}/JLab/ROOTfiles/PionLT_coin_replay_production_%i_%i.root", RunNumber, MaxEvent);  
    Outpath = "/dsk3/${USER}/JLab/OUTPUT/";
    Histopath = "/dsk3/${USER}/JLab/HISTOGRAMS/";
  }
  // Should process a different script for COIN/HMS/SHMS
  TChain ch("T");
  ch.Add(rootFileNameString);
  TString option = Form("%i.%s", RunNumber, RunType.c_str());
  TProof *proof = TProof::Open("workers=4");
  ch.SetProof();
  if(RunT.EqualTo("HMS")) ch.Process("DetTCuts_Coin.C+",option);
  else if(RunT.EqualTo("SHMS")) ch.Process("DetTCuts_SHMS.C+",option);
  else if(RunT.EqualTo("COIN")) ch.Process("DetTCuts_Coin.C+",option);
  proof->Close();
}
