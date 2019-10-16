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
    if (RunT.EqualTo("HMS")) rootFileNameString = Form("/lustre/expphy/volatile/hallc/spring17/trottar/ROOTfiles/hms_reftime_%i_%i.root", RunNumber, MaxEvent); // NOTE, this file name is temporary and only for testing currently
    else if (RunT.EqualTo("SHMS")) rootFileNameString = Form("/lustre/expphy/volatile/hallc/spring17/trottar/ROOTfiles/shms_reftime_%i_%i.root", RunNumber, MaxEvent); // NOTE, this file name is temporary and only for testing currently
    else if (RunT.EqualTo("COIN")) rootFileNameString = Form("/lustre/expphy/volatile/hallc/spring17/trottar/ROOTfiles/coin_reftime_%i_%i.root", RunNumber, MaxEvent);  
    Outpath = "/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/CALIBRATION/setREF_cuts/OUTPUT/";
    Histopath = "/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/CALIBRATION/setREF_cuts/HISTOGRAMS/";
  }
  else if(Hostname.Contains("qcd")){ // Empty for now, fill in later
  }
  else if (Hostname.Contains("trottar")){
    if (RunT.EqualTo("HMS")) rootFileNameString = Form("~/ResearchNP/ROOTfiles/kaon-coin/hms_reftime_%i_%i.root", RunNumber, MaxEvent); // NOTE, this file name is temporary and only for testing currently
    else if (RunT.EqualTo("SHMS")) rootFileNameString = Form("~/ResearchNP/ROOTfiles/kaon-coin/shms_reftime_%i_%i.root", RunNumber, MaxEvent); // NOTE, this file name is temporary and only for testing currently
    else if (RunT.EqualTo("COIN")) rootFileNameString = Form("~/ResearchNP/ROOTfiles/kaon-coin/coin_reftime_%i_%i.root", RunNumber, MaxEvent);  
    Outpath = "~/Analysis/hallc_replay_kaonlt/CALIBRATION/setREF_cuts/OUTPUT/";
    Histopath = "~/Analysis/hallc_replay_kaonlt/CALIBRATION/setREF_cuts/HISTOGRAMS/";
  }
  // Should process a different script for COIN/HMS/SHMS
  TChain ch("T");
  ch.Add(rootFileNameString);
  TString option = Form("%i.%s", RunNumber, RunType.c_str());
  TProof *proof = TProof::Open("workers=4");
  ch.SetProof();
  if(RunT.EqualTo("HMS")) ch.Process("DetTCuts_HMS.C+",option);
  else if(RunT.EqualTo("SHMS")) ch.Process("DetTCuts_SHMS.C+",option);
  else if(RunT.EqualTo("COIN")) ch.Process("DetTCuts_Coin.C+",option);
  proof->Close();
}
