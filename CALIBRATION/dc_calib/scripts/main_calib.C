//Main Calibration Code
#include "DC_calib.h"
#include "DC_calib.C"
#include <TString.h>
#include <iostream>
#include <ctime>
using namespace std;

int main_calib(TString SpecFlag, string inputname, Int_t RunNum)
{
  cout << "Provide a spectrometer flag (HMS/SHMS), a rootfille and a run number!" << endl;
  cout << "e.g. root -l `main_calib.C(\"HMS\", \"../../ROOTFiles/Test.root\", 9001)" << endl;
  //prevent root from displaying graphs while executing
  gROOT->SetBatch(1);

  //measure execution time
  clock_t cl;
  cl = clock();                                                    
                                                                                                        //pid_elec,  pid_kFALSE (no PID cuts) 
                                                                                                        // |
                                                                                                        // v
  //  DC_calib obj("HMS", "../../../ROOTfiles/hms_replay_production_all_1856_hodtrefcut1000_-1.root", 1856,-1, "pid_elec", "card");
    
  DC_calib obj(SpecFlag, inputname, RunNum, -1, "pid_elec", "card");                                                                                           
  obj.setup_Directory();
  obj.SetPlaneNames();
  obj.GetDCLeafs();
  obj.AllocateDynamicArrays();
  obj.SetTdcOffset();
  obj.CreateHistoNames();
  obj.EventLoop("FillUncorrectedTimes");
  obj.Calculate_tZero();
  obj.EventLoop("ApplyT0Correction");
  obj.WriteTZeroParam();
  obj.WriteLookUpTable();
  obj.WriteToFile(1);  //set argument to (1) for debugging
 

  //stop clock
 cl = clock() - cl;
 cout << "execution time: " << cl/(double)CLOCKS_PER_SEC << " sec" << endl;

  return 0;
}
