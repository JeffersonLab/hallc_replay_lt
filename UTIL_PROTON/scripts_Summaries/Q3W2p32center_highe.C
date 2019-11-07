#include <TProof.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

void Q3W2p32center_highe()
{
  TChain ch("T");
  ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_4871_-1.root");
  ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_4873_-1.root");
  ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_4874_-1.root");
  ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_4875_-1.root");
  ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_4876_-1.root");
  ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_4877_-1.root");
  ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_4878_-1.root");
  ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_4879_-1.root");

  TProof *proof = TProof::Open("workers=4");
  //proof->SetProgressDialog(0);  
  ch.SetProof();
  ch.Process("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/scripts_Yield/ProtonYield.C+","1");
  proof->Close();
  
}
