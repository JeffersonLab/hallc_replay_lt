#include <TProof.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

void Q2p115W2p95left_lowe()
{
  TChain ch("T");
ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_7891_-1.root");
ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_7892_-1.root");
ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_7893_-1.root");
ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_7894_-1.root");
ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_7895_-1.root");
ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_7896_-1.root");
ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_7899_-1.root");
ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_7900_-1.root");
ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_7901_-1.root");
ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_7902_-1.root");
ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_7903_-1.root");
ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_7904_-1.root");
ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_7905_-1.root");
ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_7906_-1.root");
ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_7907_-1.root");
ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_7908_-1.root");

  TProof *proof = TProof::Open("workers=8");
  //proof->SetProgressDialog(0);  
  ch.SetProof();
  ch.Process("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/scripts_Yield/ProtonYield.C+","1");
  proof->Close();
  
}
