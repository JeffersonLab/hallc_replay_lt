#define DC_Calib_Check_SHMS_cxx

#include "DC_Calib_Check_SHMS.h"
#include <TStyle.h>
#include <TCanvas.h>
#include <TLine.h>
#include <TMath.h>
#include <TPaveText.h>
#include <TGaxis.h>

void DC_Calib_Check_SHMS::Begin(TTree * /*tree*/)
{  
  printf("\n\n");
  TString option = GetOption();
}

void DC_Calib_Check_SHMS::SlaveBegin(TTree * /*tree*/)
{
  printf("\n\n");
  TString option = GetOption();

  h1_1u1_DriftDistance = new TH1F("1u1_DriftDistance", "Drift Distance 1u1 Plane; Drift Distance; Counts", 120, 0, 0.6);
  h1_1u2_DriftDistance = new TH1F("1u2_DriftDistance", "Drift Distance 1u2 Plane; Drift Distance; Counts", 120, 0, 0.6);
  h1_1x1_DriftDistance = new TH1F("1x1_DriftDistance", "Drift Distance 1x1 Plane; Drift Distance; Counts", 120, 0, 0.6);
  h1_1x2_DriftDistance = new TH1F("1x2_DriftDistance", "Drift Distance 1x2 Plane; Drift Distance; Counts", 120, 0, 0.6);
  h1_1v1_DriftDistance = new TH1F("1v1_DriftDistance", "Drift Distance 1v1 Plane; Drift Distance; Counts", 120, 0, 0.6);
  h1_1v2_DriftDistance = new TH1F("1v2_DriftDistance", "Drift Distance 1v2 Plane; Drift Distance; Counts", 120, 0, 0.6);
  h1_2u1_DriftDistance = new TH1F("2u1_DriftDistance", "Drift Distance 2u1 Plane; Drift Distance; Counts", 120, 0, 0.6);
  h1_2u2_DriftDistance = new TH1F("2u2_DriftDistance", "Drift Distance 2u2 Plane; Drift Distance; Counts", 120, 0, 0.6);
  h1_2x1_DriftDistance = new TH1F("2x1_DriftDistance", "Drift Distance 2x1 Plane; Drift Distance; Counts", 120, 0, 0.6);
  h1_2x2_DriftDistance = new TH1F("2x2_DriftDistance", "Drift Distance 2x2 Plane; Drift Distance; Counts", 120, 0, 0.6);
  h1_2v1_DriftDistance = new TH1F("2v1_DriftDistance", "Drift Distance 2v1 Plane; Drift Distance; Counts", 120, 0, 0.6);
  h1_2v2_DriftDistance = new TH1F("2v2_DriftDistance", "Drift Distance 2v2 Plane; Drift Distance; Counts", 120, 0, 0.6);

  GetOutputList()->Add(h1_1u1_DriftDistance);
  GetOutputList()->Add(h1_1u2_DriftDistance);
  GetOutputList()->Add(h1_1x1_DriftDistance);
  GetOutputList()->Add(h1_1x2_DriftDistance);
  GetOutputList()->Add(h1_1v1_DriftDistance);
  GetOutputList()->Add(h1_1v2_DriftDistance);
  GetOutputList()->Add(h1_2u1_DriftDistance);
  GetOutputList()->Add(h1_2u2_DriftDistance);
  GetOutputList()->Add(h1_2x1_DriftDistance);
  GetOutputList()->Add(h1_2x2_DriftDistance);
  GetOutputList()->Add(h1_2v1_DriftDistance);
  GetOutputList()->Add(h1_2v2_DriftDistance);

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

Bool_t DC_Calib_Check_SHMS::Process(Long64_t entry)
{
  fReader.SetEntry(entry);

  if (P_hgcer_npeSum[0] < 1.0) return kTRUE;
  for (Int_t i = 0; i < 12; i++){
    h1_Residual[i]->Fill(P_dc_residual[i]);
    h1_ResidualExclPlane[i]->Fill(P_dc_residualExclPlane[i]);
  }

  if (P_dc_1u1_time[0] > 0){
    h1_1u1_DriftDistance->Fill(P_dc_1u1_dist[0]);
    }
   
  if (P_dc_1u2_time[0] > 0){
    h1_1u2_DriftDistance->Fill(P_dc_1u2_dist[0]);
  }
  
  if (P_dc_1x1_time[0] > 0){
    h1_1x1_DriftDistance->Fill(P_dc_1x1_dist[0]);
  }
  
  if (P_dc_1x2_time[0] > 0){
    h1_1x2_DriftDistance->Fill(P_dc_1x2_dist[0]);
  }
  
  if (P_dc_1v1_time[0] > 0){
    h1_1v1_DriftDistance->Fill(P_dc_1v1_dist[0]);
  }
  
  if (P_dc_1v2_time[0] > 0){
    h1_1v2_DriftDistance->Fill(P_dc_1v2_dist[0]);
  }
  
  if (P_dc_2u1_time[0] > 0){
    h1_2u1_DriftDistance->Fill(P_dc_2u1_dist[0]);
  }
  
  if (P_dc_2u2_time[0] > 0){
    h1_2u2_DriftDistance->Fill(P_dc_2u2_dist[0]);
  }
  
  if (P_dc_2x1_time[0] > 0){
    h1_2x1_DriftDistance->Fill(P_dc_2x1_dist[0]);
  }
  
  if (P_dc_2x2_time[0] > 0){
    h1_2x2_DriftDistance->Fill(P_dc_2x2_dist[0]);
  }
    
  if (P_dc_2v1_time[0] > 0){
     h1_2v1_DriftDistance->Fill( P_dc_2v1_dist[0]);
   }
  
  if (P_dc_2v2_time[0] > 0){
     h1_2v2_DriftDistance->Fill(P_dc_2v2_dist[0]);
   }

  return kTRUE;
}

void DC_Calib_Check_SHMS::SlaveTerminate()
{
}

void DC_Calib_Check_SHMS::Terminate()
{
  TString option = GetOption();
  TString Run_temp = option(0,option.Index("."));
  TString Part_temp = option(option.Index(".")+1,option.Length());
  Int_t Run = Run_temp.Atoi(); 
  Int_t Part =  Part_temp.Atoi();
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
  
//  TFile *Histogram_file = new TFile(Form("/group/c-pionlt/USERS/${USER}/hallc_replay_lt/HISTOGRAMS/Calib/DC/SHMS_DCCalib_Check_Run%i_Pt%i.root", Run, Part),"RECREATE");
    TFile *Histogram_file = new TFile(Form("/home/cdaq/pionLT-2021/hallc_replay_lt/HISTOGRAMS/Calib/DC/SHMS_DCCalib_Check_Run%i_Pt%i.root", Run, Part),"RECREATE");

  h1_1u1_DriftDistance->Write();
  h1_1u2_DriftDistance->Write();
  h1_1x1_DriftDistance->Write();
  h1_1x2_DriftDistance->Write();
  h1_1v1_DriftDistance->Write();
  h1_1v2_DriftDistance->Write();

  h1_2u1_DriftDistance->Write();
  h1_2u2_DriftDistance->Write();
  h1_2x1_DriftDistance->Write();
  h1_2x2_DriftDistance->Write();
  h1_2v1_DriftDistance->Write();
  h1_2v2_DriftDistance->Write();

  for (Int_t i = 0; i < 12; i++) {
    Residual[i]->Write();
    ResidualExclPl[i]->Write();
  }

  Histogram_file->Close();
}
