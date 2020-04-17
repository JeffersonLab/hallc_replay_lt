#include <TChain.h>
#include <TProof.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

void run_detectEfficiency(Int_t RunNumber = 0, Int_t MaxEvent = 0, string spec = "", string detec = "")
{
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
  if(spec == "") {
    cout << "Enter spec (hms or shms): ";
    cin >> spec;
  }
  if(detec == "") {
    cout << "Enter detector: ";
    cin >> detec;
  }
  
  TChain *ch = new TChain("T");
  TString option = Form("%i",RunNumber);
  ch->Add(Form("/u/group/c-kaonlt/USERS/trottar/hallc_replay_lt/UTIL_KAONLT/ROOTfiles/PID_%i_%i.root",RunNumber,MaxEvent));
  // ch->Add(Form("~/Analysis/hallc_replay_lt/UTIL_KAONLT/ROOTfiles/PID_%i_%i.root",RunNumber,MaxEvent));
  
  TProof *proof = TProof::Open("workers=8");
  //proof->SetProgressDialog(0);  
  ch->SetProof();
  ch->Process(Form("%s_%s_efficiency.C+",spec.c_str(),detec.c_str()),option);
  proof->Close();
  
  TChain *sc = new TChain("TSH");
  ch->Add(Form("/u/group/c-kaonlt/USERS/trottar/hallc_replay_lt/UTIL_KAONLT/ROOTfiles/PID_%i_%i.root",RunNumber,MaxEvent));
  // ch->Add(Form("~/Analysis/hallc_replay_lt/UTIL_KAONLT/ROOTfiles/PID_%i_%i.root",RunNumber,MaxEvent));
  sc->Process("HMS_Scalers.C+",option);
}
