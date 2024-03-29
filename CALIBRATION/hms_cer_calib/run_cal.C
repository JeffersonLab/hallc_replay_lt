#include <TProof.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

void run_cal(Int_t RunNumber = 0, Int_t NumEvents = 0, Int_t coin = 0)
{
  if (RunNumber == 0) {
    cout << "Enter a Run Number (-1 to exit): ";
    //    cin >> RunNumber;
    if (RunNumber <= 0) return;
  }
  if (NumEvents == 0) {
    cout << "\nNumber of Events to analyze: ";
    //  cin >> NumEvents;
  }
  if (coin == 0) {
    cout << "\nIf this is a coincident run enter 1: ";
    //cin >> coin;
  }

  //  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  string calib_raw;
  cout << "\nEnter options for calibration  (enter NA to skip): ";
  //getline(std::cin, calib_raw);
  TString calib_option = calib_raw;
  calib_option = "";

  cout << "\n\n";

  TChain ch("T");
  if (coin == 1) ch.Add(Form("../../ROOTfiles/Calib/CER/Pion_coin_replay_calibration_%d_%d.root", RunNumber, NumEvents));
  else ch.Add(Form("../../ROOTfiles/Analysis/50k/hms_coin_replay_production_%d_%d.root", RunNumber, NumEvents));
  TProof *proof = TProof::Open("");
  proof->SetProgressDialog(0);  
  ch.SetProof();

  if (calib_option != "NA") {
    //Start calibration process
    ch.Process("calibration.C+",calib_option);

    cout << "\n\nUpdate calibration constants with the better estimate (y/n)? ";
      
    TString user_input = "y";
    //cin >> user_input;
    if (user_input == "y") {
      ifstream temp;
      temp.open("calibration_temp.txt", ios::in);
      ifstream temp2;
      temp2.open("plots/HMS_cer_1.pdf", ios::in);
      ifstream temp3;
      temp3.open("Calib/calib_error.csv", ios::in);
      if (temp.is_open()) {
	rename("calibration_temp.txt", Form("Calib/hcer_calib_%d.param", RunNumber));
      }
      else cout << "Error opening calibration constants, may have to update constants manually!" << endl;

      if(temp2.is_open())
      {
	rename("plots/HMS_cer_1.pdf", Form("plots/HMS_cer_%d.pdf", RunNumber));
      }
      temp2.close();
      if(temp3.is_open()) rename("Calib/calib_error.csv", Form("Calib/calib_error_%d.csv", RunNumber));
      temp3.close();
    }

    else {
      remove("calibration_temp.txt"); 
    }
  }
}
