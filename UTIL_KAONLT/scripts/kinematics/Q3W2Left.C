#include <TProof.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

void Q3W2Left()
{
  TChain ch("T");
  ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_4882_-1.root");
  ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_4884_-1.root");
  ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_4885_-1.root");
  ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_4887_-1.root");
  ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_4888_-1.root");
  ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_4889_-1.root");
  ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_4890_-1.root");

  TProof *proof = TProof::Open("workers=4");
  //proof->SetProgressDialog(0);  
  ch.SetProof();
  ch.Process("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/scripts_KaonYield/KaonYield_Q3W2Center.C+","1");
  proof->Close();
  
}
