#include <TProof.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

void Q4p4W2p74center_lowe()
{
  TChain ch("T");
ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_7978_-1.root");
ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_7979_-1.root");
ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_7980_-1.root");
ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_7981_-1.root");
ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_7982_-1.root");
ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_7983_-1.root");
ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_7984_-1.root");
ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_7985_-1.root");
ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_7986_-1.root");
ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_7987_-1.root");
ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_7988_-1.root");
ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_7989_-1.root");
ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_7994_-1.root");
ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_7995_-1.root");
ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_7996_-1.root");
ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_7997_-1.root");
ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_7998_-1.root");
ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_7999_-1.root");
ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_8000_-1.root");
ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_8001_-1.root");
ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_8002_-1.root");



  TProof *proof = TProof::Open("workers=8");
  //proof->SetProgressDialog(0);  
  ch.SetProof();
  ch.Process("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/scripts_Yield/ProtonYield.C+","1");
  proof->Close();
  
}
