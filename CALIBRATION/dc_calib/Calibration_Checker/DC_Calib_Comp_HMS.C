#define DC_Calib_Comp_HMS_cxx

#include "DC_Calib_Comp_HMS.h"
#include <TStyle.h>
#include <TCanvas.h>
#include <TLine.h>
#include <TMath.h>
#include <TPaveText.h>
#include <TGaxis.h>

void DC_Calib_Comp_HMS::Begin(TTree * /*tree*/)
{  
  printf("\n\n");
  TString option = GetOption();
}

void DC_Calib_Comp_HMS::SlaveBegin(TTree * /*tree*/)
{
  printf("\n\n");
  TString option = GetOption();

  h1_Residual = new TH1F*[12];
  h1_ResidualExclPlane = new TH1F*[12];
  TString Plane[12] = {"1u1", "1u2", "1x1", "1x2", "1v1", "1v2", "2u1", "2u2", "2x1", "2x2", "2v1", "2v2"};
  TString Name;
  TString Title;
  for (Int_t i = 0; i < 12; i++){
    Name = "h1_"+Plane[i]+"_Residual";
    Title = Plane[i]+" Plane Residual; Residual; Counts";
    h1_Residual[i] = new TH1F(Name, Title, 200, -0.5, 0.5);
    Name = "h1_ResidualExclPlane_"+Plane[i];
    Title = "ResidualExcl Plane "+Plane[i]+"; Residual; Counts";
    h1_ResidualExclPlane[i] = new TH1F(Name, Title, 200, -0.5, 0.5);   
    GetOutputList()->Add(h1_Residual[i]);
    GetOutputList()->Add(h1_ResidualExclPlane[i]);
  }
}

Bool_t DC_Calib_Comp_HMS::Process(Long64_t entry)
{
  fReader.SetEntry(entry);

  if (H_cer_npeSum[0] < 1.0) return kTRUE;
  if (T_hms_hEL_CLEAN_tdcTime[0] < 0) return kTRUE;

  for (Int_t i = 0; i < 12; i++){
    h1_Residual[i]->Fill(H_dc_residual[i]);
    h1_ResidualExclPlane[i]->Fill(H_dc_residualExclPlane[i]);
  }
  
  return kTRUE;
}

void DC_Calib_Comp_HMS::SlaveTerminate()
{
}

void DC_Calib_Comp_HMS::Terminate()
{
  TString option = GetOption();
  Int_t Run = option.Atoi(); 
  //Need to exact the histograms from the OutputList
  TH1F* Residual[12];
  TH1F* ResidualExclPl[12];
  TString Plane[12] = {"1u1", "1u2", "1x1", "1x2", "1v1", "1v2", "2u1", "2u2", "2x1", "2x2", "2v1", "2v2"};
  TString Name;
  TString Title;
  for (Int_t i = 0; i < 12; i++) {
    Name = "h1_"+Plane[i]+"_Residual";
    Residual[i] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Name));
    Name = "h1_ResidualExclPlane_"+Plane[i];
    ResidualExclPl[i] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Name));
  }             
  
  TFile *Histogram_file = new TFile(Form("HISTOGRAMS/HMS_DCCalib_Comp_Run%i.root", Run),"RECREATE");

  for (Int_t i = 0; i < 12; i++) {
    Residual[i]->Write();
    ResidualExclPl[i]->Write();
  }

  Histogram_file->Close();
}
