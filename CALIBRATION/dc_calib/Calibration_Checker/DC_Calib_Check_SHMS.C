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

  h2_1u1_DriftDistance = new TH2F("1u1_DriftDistance", "Drift Distance by wire number for 1u1 Plane; Wire Number; Drift Distance", 120, 0, 120, 100, 0, 1);
  h2_1u2_DriftDistance = new TH2F("1u2_DriftDistance", "Drift Distance by wire number for 1u2 Plane; Wire Number; Drift Distance", 120, 0, 120, 100, 0, 1);
  h2_1x1_DriftDistance = new TH2F("1x1_DriftDistance", "Drift Distance by wire number for 1x1 Plane; Wire Number; Drift Distance", 120, 0, 120, 100, 0, 1);
  h2_1x2_DriftDistance = new TH2F("1x2_DriftDistance", "Drift Distance by wire number for 1x2 Plane; Wire Number; Drift Distance", 120, 0, 120, 100, 0, 1);
  h2_1v1_DriftDistance = new TH2F("1v1_DriftDistance", "Drift Distance by wire number for 1v1 Plane; Wire Number; Drift Distance", 120, 0, 120, 100, 0, 1);
  h2_1v2_DriftDistance = new TH2F("1v2_DriftDistance", "Drift Distance by wire number for 1v2 Plane; Wire Number; Drift Distance", 120, 0, 120, 100, 0, 1);

  h2_2u1_DriftDistance = new TH2F("2u1_DriftDistance", "Drift Distance by wire number for 2u1 Plane; Wire Number; Drift Distance", 120, 0, 120, 100, 0, 1);
  h2_2u2_DriftDistance = new TH2F("2u2_DriftDistance", "Drift Distance by wire number for 2u2 Plane; Wire Number; Drift Distance", 120, 0, 120, 100, 0, 1);
  h2_2x1_DriftDistance = new TH2F("2x1_DriftDistance", "Drift Distance by wire number for 2x1 Plane; Wire Number; Drift Distance", 120, 0, 120, 100, 0, 1);
  h2_2x2_DriftDistance = new TH2F("2x2_DriftDistance", "Drift Distance by wire number for 2x2 Plane; Wire Number; Drift Distance", 120, 0, 120, 100, 0, 1);
  h2_2v1_DriftDistance = new TH2F("2v1_DriftDistance", "Drift Distance by wire number for 2v1 Plane; Wire Number; Drift Distance", 120, 0, 120, 100, 0, 1);
  h2_2v2_DriftDistance = new TH2F("2v2_DriftDistance", "Drift Distance by wire number for 2v2 Plane; Wire Number; Drift Distance", 120, 0, 120, 100, 0, 1);

  GetOutputList()->Add(h2_1u1_DriftDistance);
  GetOutputList()->Add(h2_1u2_DriftDistance);
  GetOutputList()->Add(h2_1x1_DriftDistance);
  GetOutputList()->Add(h2_1x2_DriftDistance);
  GetOutputList()->Add(h2_1v1_DriftDistance);
  GetOutputList()->Add(h2_1v2_DriftDistance);

  GetOutputList()->Add(h2_2u1_DriftDistance);
  GetOutputList()->Add(h2_2u2_DriftDistance);
  GetOutputList()->Add(h2_2x1_DriftDistance);
  GetOutputList()->Add(h2_2x2_DriftDistance);
  GetOutputList()->Add(h2_2v1_DriftDistance);
  GetOutputList()->Add(h2_2v2_DriftDistance);

}

Bool_t DC_Calib_Check_SHMS::Process(Long64_t entry)
{
  fReader.SetEntry(entry);

  if (P_hgcer_npeSum[0] < 1.0) return kTRUE;
  if (T_shms_pEL_CLEAN_tdcTime[0] < 0) return kTRUE;

  for (Int_t i = 0; i < P_dc_1u1_time.GetSize(); i++){
    if (P_dc_1u1_time[i] > 0){
      h2_1u1_DriftDistance->Fill(P_dc_1u1_wirenum[i], P_dc_1u1_dist[i]);
    }
  }
  
  for (Int_t i = 0; i < P_dc_1u2_time.GetSize(); i++){
    if (P_dc_1u2_time[i] > 0){
      h2_1u2_DriftDistance->Fill(P_dc_1u2_wirenum[i], P_dc_1u2_dist[i]);
    }
  }

  for (Int_t i = 0; i < P_dc_1x1_time.GetSize(); i++){
    if (P_dc_1x1_time[i] > 0){
      h2_1x1_DriftDistance->Fill(P_dc_1x1_wirenum[i], P_dc_1x1_dist[i]);
    }
  }
  
  for (Int_t i = 0; i < P_dc_1x2_time.GetSize(); i++){
    if (P_dc_1x2_time[i] > 0){
      h2_1x2_DriftDistance->Fill(P_dc_1x2_wirenum[i], P_dc_1x2_dist[i]);
    }
  }
  
  for (Int_t i = 0; i < P_dc_1v1_time.GetSize(); i++){
    if (P_dc_1v1_time[i] > 0){
      h2_1v1_DriftDistance->Fill(P_dc_1v1_wirenum[i], P_dc_1v1_dist[i]);
    }
  }
  
  for (Int_t i = 0; i < P_dc_1v2_time.GetSize(); i++){
    if (P_dc_1v2_time[i] > 0){
      h2_1v2_DriftDistance->Fill(P_dc_1v2_wirenum[i], P_dc_1v2_dist[i]);
    }
  }

  for (Int_t i = 0; i < P_dc_2u1_time.GetSize(); i++){
    if (P_dc_2u1_time[i] > 0){
      h2_2u1_DriftDistance->Fill(P_dc_2u1_wirenum[i], P_dc_2u1_dist[i]);
    }
  }
  
  for (Int_t i = 0; i < P_dc_2u2_time.GetSize(); i++){
    if (P_dc_2u2_time[i] > 0){
      h2_2u2_DriftDistance->Fill(P_dc_2u2_wirenum[i], P_dc_2u2_dist[i]);
    }
  }

  for (Int_t i = 0; i < P_dc_2x1_time.GetSize(); i++){
    if (P_dc_2x1_time[i] > 0){
      h2_2x1_DriftDistance->Fill(P_dc_2x1_wirenum[i], P_dc_2x1_dist[i]);
    }
  }
  
  for (Int_t i = 0; i < P_dc_2x2_time.GetSize(); i++){
    if (P_dc_2x2_time[i] > 0){
      h2_2x2_DriftDistance->Fill(P_dc_2x2_wirenum[i], P_dc_2x2_dist[i]);
    }
  }
  
  for (Int_t i = 0; i < P_dc_2v1_time.GetSize(); i++){
    if (P_dc_2v1_time[i] > 0){
      h2_2v1_DriftDistance->Fill(P_dc_2v1_wirenum[i], P_dc_2v1_dist[i]);
    }
  }
  
  for (Int_t i = 0; i < P_dc_2v2_time.GetSize(); i++){
    if (P_dc_2v2_time[i] > 0){
      h2_2v2_DriftDistance->Fill(P_dc_2v2_wirenum[i], P_dc_2v2_dist[i]);
    }
  }  

  return kTRUE;
}

void DC_Calib_Check_SHMS::SlaveTerminate()
{
}

void DC_Calib_Check_SHMS::Terminate()
{
  TString option = GetOption();

  TString foutname = Form("OUTPUT/SHMS_DC_Calib_Check_Run%i", option.Atoi());
  TString outputpdf = foutname + ".pdf";
  TCanvas *cDC1 = new TCanvas("DC1","Drift Chamber 1 Planes",100,0,1000,900);
  cDC1->Divide(2,3);
  cDC1->cd(1); h2_1u1_DriftDistance->Draw("COLZ");
  cDC1->cd(2); h2_1u2_DriftDistance->Draw("COLZ");
  cDC1->cd(3); h2_1x1_DriftDistance->Draw("COLZ");
  cDC1->cd(4); h2_1x2_DriftDistance->Draw("COLZ");
  cDC1->cd(5); h2_1v1_DriftDistance->Draw("COLZ");
  cDC1->cd(6); h2_1v2_DriftDistance->Draw("COLZ");
  cDC1->Print(outputpdf + '(');               
  TCanvas *cDC2 = new TCanvas("DC2","Drift Chamber 2 Planes",100,0,1000,900);
  cDC2->Divide(2,3);
  cDC2->cd(1); h2_2u1_DriftDistance->Draw("COLZ");
  cDC2->cd(2); h2_2u2_DriftDistance->Draw("COLZ");
  cDC2->cd(3); h2_2x1_DriftDistance->Draw("COLZ");
  cDC2->cd(4); h2_2x2_DriftDistance->Draw("COLZ");
  cDC2->cd(5); h2_2v1_DriftDistance->Draw("COLZ");
  cDC2->cd(6); h2_2v2_DriftDistance->Draw("COLZ");
  cDC2->Print(outputpdf + ')');               

  TFile *Histogram_file = new TFile(Form("HISTOGRAMS/SHMS_DCCalib_Check_Run%i.root",option.Atoi()),"RECREATE");

  h2_1u1_DriftDistance->Write();
  h2_1u2_DriftDistance->Write();
  h2_1x1_DriftDistance->Write();
  h2_1x2_DriftDistance->Write();
  h2_1v1_DriftDistance->Write();
  h2_1v2_DriftDistance->Write();

  h2_2u1_DriftDistance->Write();
  h2_2u2_DriftDistance->Write();
  h2_2x1_DriftDistance->Write();
  h2_2x2_DriftDistance->Write();
  h2_2v1_DriftDistance->Write();
  h2_2v2_DriftDistance->Write();

  Histogram_file->Close();
}
