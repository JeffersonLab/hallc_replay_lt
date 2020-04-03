#include <TProof.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

void run_TREFHMS(Int_t RunNumber = 0, Int_t MaxEvent = 0)
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

  //Begin Checking ADC Gates
  TChain ch("T");
  ch.Add(Form("/u/group/c-kaonlt/hallc_replay_kaonlt/ROOTfiles/hms_coin_replay_production_all_%i_%i.root",RunNumber,MaxEvent));
  TString option = Form("%i",RunNumber);

  TProof *proof = TProof::Open("workers=4");
  //proof->SetProgressDialog(0);  
  ch.SetProof();
  ch.Process("TREFHMS.C+",option);
  proof->Close();
}
