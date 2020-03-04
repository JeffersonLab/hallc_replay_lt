#include <TProof.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

void run_LumiYield(Int_t RunNumber = 0, Int_t MaxEvent = 0, Double_t threshold_cut = 5, Int_t pscal = 1)
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

  fstream REPORT_file;
  REPORT_file.open (Form("/u/group/c-kaonlt/USERS/trottar/hallc_replay_lt/UTIL_KAONLT/REPORT_OUTPUT/COIN/PRODUCTION/Lumi_coin_replay_production_Offline_%i_%i.report",RunNumber,MaxEvent));
  Int_t line_num = 0;
  string line;
  TString line_PS1;
  TString line_PS3;

  if (REPORT_file.is_open()) {
    while (getline(REPORT_file,line)) {
      line_num++;
      if (line_num == 90) {
	line_PS1 = line;
      }
      if (line_num == 92) {
	line_PS3 = line;
      }
    }
  }
  
  REPORT_file.close();
  line_PS1 = line_PS1(13,line_PS1.Length());
  line_PS3 = line_PS3(13,line_PS3.Length());

  Int_t PS1 = line_PS1.Atoi();
  Int_t PS3 = line_PS3.Atoi();

  cout << Form("Using prescale factors: PS1 %i, PS3 %i\n",PS1,PS3);

  TString option = Form("%i.%i",PS1,PS3);
  
  ofstream myfile1;
  myfile1.open ("/u/group/c-kaonlt/USERS/trottar/hallc_replay_lt/UTIL_KAONLT/scripts_Luminosity/Yield_Data.dat", fstream::app);
  myfile1 << Form("%d ", RunNumber);
  myfile1.close();
  
  TProof *proof = TProof::Open("workers=4");
  // proof->SetProgressDialog(0);

  //Begin Counting Good Kaon Events
  TChain ch("T");
  ch.Add(Form("/u/group/c-kaonlt/USERS/trottar/hallc_replay_lt/UTIL_KAONLT/ROOTfiles/Lumi_coin_replay_production_Offline_%i_%i.root",RunNumber,MaxEvent));
  ch.SetProof();

  ch.Process("/u/group/c-kaonlt/USERS/trottar/hallc_replay_lt/UTIL_KAONLT/scripts_Luminosity/LumiYield.C+",option);
  
  TChain sc("TSH");
  sc.Add(Form("/u/group/c-kaonlt/USERS/trottar/hallc_replay_lt/UTIL_KAONLT/ROOTfiles/Lumi_coin_replay_production_Offline_%i_%i.root",RunNumber,MaxEvent));
  sc.Process("/u/group/c-kaonlt/USERS/trottar/hallc_replay_lt/UTIL_KAONLT/scripts_Luminosity/Scalers.C+",option);

  proof->Close();
 
}
