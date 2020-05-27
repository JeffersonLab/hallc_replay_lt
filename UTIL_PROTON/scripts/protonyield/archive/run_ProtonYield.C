#include <TProof.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <TSystem.h>

void run_ProtonYield(Int_t RunNumber = 0, Int_t MaxEvent = 0, Double_t threshold_cut = 5, Int_t pscal = 1)
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
  if(threshold_cut == 0) {
    cout << "Enter a current threshold: ";
    cin >> threshold_cut;
    //if( threshold_cut<=0 ) return;
  }
  if(pscal == 0) {
    cout << "Enter a prescale factor: ";
    cin >> pscal;
    if( pscal<=0 ) return;
  }

  //Begin Scaler Efficiency Calculation
  if(Hostname.Contains("farm")){
    rootFileNameString = Form("/group/c-kaonlt/USERS/${USER}/hallc_replay_lt/UTIL_PROTON/ROOTfilesProton/Proton_coin_replay_production_%i_%i.root",RunNumber,MaxEvent);
  }
  else if(Hostname.Contains("qcd")){
    rootFileNameString = Form("/group/c-kaonlt/USERS/${USER}/hallc_replay_lt/UTIL_PROTON/ROOTfilesProton/Proton_coin_replay_production_%i_%i.root",RunNumber,MaxEvent);
  }
  else if (Hostname.Contains("phys.uregina.ca")){
    rootFileNameString = Form("/home/${USER}/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_%i_%i.root",RunNumber,MaxEvent);
  }
  TString threshold = Form("%f",threshold_cut);
  TString runNum = Form("%d",RunNumber);
  TString prescal = Form("%d", pscal);
  TString line1 = ".L coin_cut.C+";
  TString line2 = "coin_cut t(\"" + rootFileNameString + "\")";
  TString line3 = "t.Loop(\"" + runNum + "\"," + threshold + "," + prescal + ")";

  //Begin Counting Good Proton Events
  TChain ch("T");
  ch.Add(rootFileNameString);
  TString option = Form("%i",RunNumber);

  TProof *proof = TProof::Open("workers=4");
  //proof->SetProgressDialog(0);  
  ch.SetProof();
  ch.Process("ProtonYield.C+",option);
  proof->Close();
  
  TChain sc("TSH");
  sc.Add(rootFileNameString);
  sc.Process("HMS_Scalers.C+",option);
}
