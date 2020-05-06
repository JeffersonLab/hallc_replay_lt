
#include <TProof.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

void Q3W3p14left_highe()
{
  TChain ch("T");
  ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_5013_-1.root");
  ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_5014_-1.root");
  ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_5015_-1.root");
  ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_5016_-1.root");
  ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_5017_-1.root");
  ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_5018_-1.root");
  ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_5019_-1.root");
  ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_5020_-1.root");
  ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_5021_-1.root");
  ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_5022_-1.root");
  ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_5023_-1.root");
  ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_5024_-1.root");
  ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_5025_-1.root");
  ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_5026_-1.root");
  ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_5027_-1.root");
  ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_5029_-1.root");
  ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_5030_-1.root");
  ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_5031_-1.root");
  ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_5032_-1.root");
  ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_5033_-1.root");
  ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_5038_-1.root");
  ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_5039_-1.root");
  ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_5311_-1.root");
  ch.Add("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/ROOTfiles_KaonOL/KaonLT_coin_replay_production_5312_-1.root");

  TProof *proof = TProof::Open("workers=8");
  //proof->SetProgressDialog(0);  
  ch.SetProof();
  ch.Process("/home/sjdkay/work/JLab/hallc_replay_lt/UTIL_PROTON/scripts_Yield/ProtonYield.C+","1");
  proof->Close();
  
}
