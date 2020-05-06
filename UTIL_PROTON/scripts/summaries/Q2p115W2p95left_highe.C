#include <TProof.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

void Q2p115W2p95left_highe()
{
  TChain ch("T");
  ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_4892_-1.root");
  ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_4893_-1.root");
  ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_4894_-1.root");
  ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_4895_-1.root");
  ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_4896_-1.root");
  ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_4897_-1.root");
  ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_4898_-1.root");
  ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_4899_-1.root");
  ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_4900_-1.root");
  ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_4901_-1.root");


  ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_4904_-1.root");
  ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_4905_-1.root");
  ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_4906_-1.root");
  ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_4907_-1.root");
  ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_4908_-1.root");
  ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_4909_-1.root");

  TProof *proof = TProof::Open("workers=8");
  //proof->SetProgressDialog(0);  
  ch.SetProof();
  ch.Process("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/scripts_Yield/ProtonYield.C+","1");
  proof->Close();
  
}
