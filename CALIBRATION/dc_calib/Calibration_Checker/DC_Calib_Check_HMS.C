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
  printf("\n\n");
  TString option = GetOption();
}

void DC_Calib_Check_HMS::SlaveBegin(TTree * /*tree*/)
{
  printf("\n\n");
  TString option = GetOption();

  h1_1u1_DriftDistance = new TH1F("1u1_DriftDistance", "Drift Distance 1u1 Plane; Drift Distance; Counts", 200, -1, 1);
  h1_1u2_DriftDistance = new TH1F("1u2_DriftDistance", "Drift Distance 1u2 Plane; Drift Distance; Counts", 200, -1, 1);
  h1_1x1_DriftDistance = new TH1F("1x1_DriftDistance", "Drift Distance 1x1 Plane; Drift Distance; Counts", 200, -1, 1);
  h1_1x2_DriftDistance = new TH1F("1x2_DriftDistance", "Drift Distance 1x2 Plane; Drift Distance; Counts", 200, -1, 1);
  h1_1v1_DriftDistance = new TH1F("1v1_DriftDistance", "Drift Distance 1v1 Plane; Drift Distance; Counts", 200, -1, 1);
  h1_1v2_DriftDistance = new TH1F("1v2_DriftDistance", "Drift Distance 1v2 Plane; Drift Distance; Counts", 200, -1, 1);
  h1_2u1_DriftDistance = new TH1F("2u1_DriftDistance", "Drift Distance 2u1 Plane; Drift Distance; Counts", 200, -1, 1);
  h1_2u2_DriftDistance = new TH1F("2u2_DriftDistance", "Drift Distance 2u2 Plane; Drift Distance; Counts", 200, -1, 1);
  h1_2x1_DriftDistance = new TH1F("2x1_DriftDistance", "Drift Distance 2x1 Plane; Drift Distance; Counts", 200, -1, 1);
  h1_2x2_DriftDistance = new TH1F("2x2_DriftDistance", "Drift Distance 2x2 Plane; Drift Distance; Counts", 200, -1, 1);
  h1_2v1_DriftDistance = new TH1F("2v1_DriftDistance", "Drift Distance 2v1 Plane; Drift Distance; Counts", 200, -1, 1);
  h1_2v2_DriftDistance = new TH1F("2v2_DriftDistance", "Drift Distance 2v2 Plane; Drift Distance; Counts", 200, -1, 1);

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

Bool_t DC_Calib_Check_HMS::Process(Long64_t entry)
{
  fReader.SetEntry(entry);

  if (H_cer_npeSum[0] < 1.0) return kTRUE;
  if (T_hms_hEL_CLEAN_tdcTime[0] < 0) return kTRUE;

  for (Int_t i = 0; i < 12; i++){
    h1_Residual[i]->Fill(H_dc_residual[i]);
    h1_Residual[i]->Fill(H_dc_residualExclPlane[i]);
  }

  for (Int_t i = 0; i < H_dc_1u1_time.GetSize(); i++){
    if (H_dc_1u1_time[i] > 0){
      h1_1u1_DriftDistance->Fill(H_dc_1u1_dist[i]);
    }
  }
  
  for (Int_t i = 0; i < H_dc_1u2_time.GetSize(); i++){
    if (H_dc_1u2_time[i] > 0){
      h1_1u2_DriftDistance->Fill(H_dc_1u2_dist[i]);
    }
  }

  for (Int_t i = 0; i < H_dc_1x1_time.GetSize(); i++){
    if (H_dc_1x1_time[i] > 0){
      h1_1x1_DriftDistance->Fill(H_dc_1x1_dist[i]);
    }
  }
  
  for (Int_t i = 0; i < H_dc_1x2_time.GetSize(); i++){
    if (H_dc_1x2_time[i] > 0){
      h1_1x2_DriftDistance->Fill(H_dc_1x2_dist[i]);
    }
  }
  
  for (Int_t i = 0; i < H_dc_1v1_time.GetSize(); i++){
    if (H_dc_1v1_time[i] > 0){
      h1_1v1_DriftDistance->Fill(H_dc_1v1_dist[i]);
    }
  }
  
  for (Int_t i = 0; i < H_dc_1v2_time.GetSize(); i++){
    if (H_dc_1v2_time[i] > 0){
      h1_1v2_DriftDistance->Fill(H_dc_1v2_dist[i]);
    }
  }

  for (Int_t i = 0; i < H_dc_2u1_time.GetSize(); i++){
    if (H_dc_2u1_time[i] > 0){
      h1_2u1_DriftDistance->Fill(H_dc_2u1_dist[i]);
    }
  }
  
  for (Int_t i = 0; i < H_dc_2u2_time.GetSize(); i++){
    if (H_dc_2u2_time[i] > 0){
      h1_2u2_DriftDistance->Fill(H_dc_2u2_dist[i]);
    }
  }

  for (Int_t i = 0; i < H_dc_2x1_time.GetSize(); i++){
    if (H_dc_2x1_time[i] > 0){
      h1_2x1_DriftDistance->Fill(H_dc_2x1_dist[i]);
    }
  }
  
  for (Int_t i = 0; i < H_dc_2x2_time.GetSize(); i++){
    if (H_dc_2x2_time[i] > 0){
      h1_2x2_DriftDistance->Fill(H_dc_2x2_dist[i]);
    }
  }
  
  for (Int_t i = 0; i < H_dc_2v1_time.GetSize(); i++){
    if (H_dc_2v1_time[i] > 0){
      h1_2v1_DriftDistance->Fill( H_dc_2v1_dist[i]);
    }
  }
  
  for (Int_t i = 0; i < H_dc_2v2_time.GetSize(); i++){
    if (H_dc_2v2_time[i] > 0){
      h1_2v2_DriftDistance->Fill(H_dc_2v2_dist[i]);
    }
  }  

  return kTRUE;
}

void DC_Calib_Check_HMS::SlaveTerminate()
{
}

void DC_Calib_Check_HMS::Terminate()
{
  TString option = GetOption();
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
  TString foutname = Form("OUTPUT/HMS_DC_Calib_Check_Run%i", option.Atoi());
  TString outputpdf = foutname + ".pdf";
  TCanvas *cDC1 = new TCanvas("DC1","Drift Chamber 1 Planes",100,0,1000,900);
  cDC1->Divide(2,3);
  cDC1->cd(1); h1_1u1_DriftDistance->Draw();
  cDC1->cd(2); h1_1u2_DriftDistance->Draw();
  cDC1->cd(3); h1_1x1_DriftDistance->Draw();
  cDC1->cd(4); h1_1x2_DriftDistance->Draw();
  cDC1->cd(5); h1_1v1_DriftDistance->Draw();
  cDC1->cd(6); h1_1v2_DriftDistance->Draw();
  cDC1->Print(outputpdf + '(');               
  TCanvas *cDC2 = new TCanvas("DC2","Drift Chamber 2 Planes",100,0,1000,900);
  cDC2->Divide(2,3);
  cDC2->cd(1); h1_2u1_DriftDistance->Draw();
  cDC2->cd(2); h1_2u2_DriftDistance->Draw();
  cDC2->cd(3); h1_2x1_DriftDistance->Draw();
  cDC2->cd(4); h1_2x2_DriftDistance->Draw();
  cDC2->cd(5); h1_2v1_DriftDistance->Draw();
  cDC2->cd(6); h1_2v2_DriftDistance->Draw();
  cDC2->Print(outputpdf);
  TCanvas *cDC1_Res = new TCanvas("DC1_Res","Drift Chamber 1 Residuals",100,0,1000,900);
  cDC1_Res->Divide(2,3);
  cDC1_Res->cd(1); Residual[0]->Draw();
  cDC1_Res->cd(2); Residual[1]->Draw();
  cDC1_Res->cd(3); Residual[2]->Draw();
  cDC1_Res->cd(4); Residual[3]->Draw();
  cDC1_Res->cd(5); Residual[4]->Draw();
  cDC1_Res->cd(6); Residual[5]->Draw();
  cDC1_Res->Print(outputpdf);
  TCanvas *cDC2_Res = new TCanvas("DC2_Res","Drift Chamber 2 Residuals",100,0,1000,900);
  cDC2_Res->Divide(2,3);
  cDC2_Res->cd(1); Residual[6]->Draw();
  cDC2_Res->cd(2); Residual[7]->Draw();
  cDC2_Res->cd(3); Residual[8]->Draw();
  cDC2_Res->cd(4); Residual[9]->Draw();
  cDC2_Res->cd(5); Residual[10]->Draw();
  cDC2_Res->cd(6); Residual[11]->Draw();
  cDC2_Res->Print(outputpdf);              
  TCanvas *cDC1ResExclPl = new TCanvas("DC1ResExclPl","Drift Chamber 1 ResidualExclPls",100,0,1000,900);
  cDC1ResExclPl->Divide(2,3);
  cDC1ResExclPl->cd(1); ResidualExclPl[0]->Draw();
  cDC1ResExclPl->cd(2); ResidualExclPl[1]->Draw();
  cDC1ResExclPl->cd(3); ResidualExclPl[2]->Draw();
  cDC1ResExclPl->cd(4); ResidualExclPl[3]->Draw();
  cDC1ResExclPl->cd(5); ResidualExclPl[4]->Draw();
  cDC1ResExclPl->cd(6); ResidualExclPl[5]->Draw();
  cDC1ResExclPl->Print(outputpdf);
  TCanvas *cDC2ResExclPl = new TCanvas("DC2ResExclPl","Drift Chamber 2 ResidualExclPls",100,0,1000,900);
  cDC2ResExclPl->Divide(2,3);
  cDC2ResExclPl->cd(1); ResidualExclPl[6]->Draw();
  cDC2ResExclPl->cd(2); ResidualExclPl[7]->Draw();
  cDC2ResExclPl->cd(3); ResidualExclPl[8]->Draw();
  cDC2ResExclPl->cd(4); ResidualExclPl[9]->Draw();
  cDC2ResExclPl->cd(5); ResidualExclPl[10]->Draw();
  cDC2ResExclPl->cd(6); ResidualExclPl[11]->Draw();
  cDC2ResExclPl->Print(outputpdf + ')');

  TFile *Histogram_file = new TFile(Form("HISTOGRAMS/HMS_DCCalib_Check_Run%i.root",option.Atoi()),"RECREATE");

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
