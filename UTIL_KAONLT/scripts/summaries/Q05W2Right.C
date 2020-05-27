#include <TProof.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

void Q05W2Right(Int_t current = 0)
{

  if(current == 0) {
    cout << "Enter current for set of runs (-1 for all runs): ";
    cin >> current;
    //if( current<=0 ) return;
  }
  TChain ch("T");
  TString option = Form("%i",current);
  if(current == 11){
      /////////////////////////////////////////////////////////////////////////////////////
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7030_-1.root"); // 11 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7031_-1.root"); // 11 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7032_-1.root"); // 11 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7033_-1.root"); // 11 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7034_-1.root"); // 11 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7035_-1.root"); // 11 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7036_-1.root"); // 11 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7037_-1.root"); // 11 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7038_-1.root"); // 11 uA
    //ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7039_-1.root"); // 11 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7040_-1.root"); // 11 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7041_-1.root"); // 11 uA
    //ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7042_-1.root"); // 11 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7043_-1.root"); // 11 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7044_-1.root"); // 11 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7045_-1.root"); // 11 uA
  }
  if(current == 16){
      /////////////////////////////////////////////////////////////////////////////////////
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6980_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6981_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6982_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6983_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6984_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6985_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6986_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6987_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6988_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6989_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6990_-1.root"); // 16 uA
    //ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6991_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6992_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6993_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6994_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6995_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6996_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6997_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6998_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7002_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7003_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7004_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7005_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7006_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7007_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7008_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7009_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7010_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7011_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7012_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7013_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7014_-1.root"); // 16 uA
    //ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7015_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7016_-1.root"); // 16 uA
    //ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7017_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7018_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7019_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7022_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7023_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7024_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7025_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7026_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7028_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7029_-1.root"); // 16 uA
  }
  if(current <= 0){
      /////////////////////////////////////////////////////////////////////////////////////
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7030_-1.root"); // 11 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7031_-1.root"); // 11 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7032_-1.root"); // 11 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7033_-1.root"); // 11 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7034_-1.root"); // 11 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7035_-1.root"); // 11 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7036_-1.root"); // 11 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7037_-1.root"); // 11 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7038_-1.root"); // 11 uA
    //ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7039_-1.root"); // 11 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7040_-1.root"); // 11 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7041_-1.root"); // 11 uA
    //ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7042_-1.root"); // 11 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7043_-1.root"); // 11 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7044_-1.root"); // 11 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7045_-1.root"); // 11 uA
      /////////////////////////////////////////////////////////////////////////////////////
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6980_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6981_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6982_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6983_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6984_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6985_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6986_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6987_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6988_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6989_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6990_-1.root"); // 16 uA
    //ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6991_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6992_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6993_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6994_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6995_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6996_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6997_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6998_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7002_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7003_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7004_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7005_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7006_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7007_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7008_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7009_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7010_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7011_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7012_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7013_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7014_-1.root"); // 16 uA
    //ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7015_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7016_-1.root"); // 16 uA
    //ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7017_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7018_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7019_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7022_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7023_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7024_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7025_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7026_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7028_-1.root"); // 16 uA
    ch.Add("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_7029_-1.root"); // 16 uA
  }
  
  TProof *proof = TProof::Open("workers=8");
  //proof->SetProgressDialog(0);  
  ch.SetProof();
  ch.Process("/u/group/c-kaonlt/USERS/trottar/hallc_replay_kaonlt/UTIL_KAONLT/scripts_KaonYield/KaonYield_all.C+",option);
  proof->Close();
  
}
