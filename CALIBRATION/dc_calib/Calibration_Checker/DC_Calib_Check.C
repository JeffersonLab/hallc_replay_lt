#define DC_Calib_Check_HMS_cxx

#include "DC_Calib_Check_HMS.h"
#include <TStyle.h>
#include <TCanvas.h>
#include <TLine.h>
#include <TMath.h>
#include <TPaveText.h>
#include <TGaxis.h>

void DC_Calib_Check_HMS::Begin(TTree * /*tree*/)
{  
  TString option = GetOption();
}

void DC_Calib_Check_HMS::SlaveBegin(TTree * /*tree*/)
{
  TString option = GetOption();
  // Timing Windows, may change to be some 2D array

}

Bool_t DC_Calib_Check_HMS::Process(Long64_t entry)
{
  fReader.SetEntry(entry);
  return kTRUE;
}

void DC_Calib_Check_HMS::SlaveTerminate()
{
}

void DC_Calib_Check_HMS::Terminate()
{
}
