#include <TProof.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

void Q4p4W2p74left_highe()
{
  TChain ch("T");
  ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_4999_-1.root");
  ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_5000_-1.root");
  ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_5001_-1.root");
  ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_5002_-1.root");
  ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_5003_-1.root");
  ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_5004_-1.root");
  ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_5005_-1.root");
  ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_5006_-1.root");
  ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_5007_-1.root");
  ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_5008_-1.root");
  ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_5009_-1.root");

  TProof *proof = TProof::Open("workers=8");
  //proof->SetProgressDialog(0);  
  ch.SetProof();
  ch.Process("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/scripts_KaonYield/KaonYield_allfall.C+","1");
  proof->Close();
  
}
