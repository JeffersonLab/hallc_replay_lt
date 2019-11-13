#define DetTCuts_SHMS_cxx

#include "DetTCuts_SHMS.h"
#include <TH1.h>
#include <TH2.h>
#include <TF1.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TPaveText.h>
#include <TSpectrum.h>
#include <TList.h>
#include <TPolyMarker.h>
#include <TGraphErrors.h>
#include <TMath.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "TProof.h"

using namespace TMath;

void DetTCuts_SHMS::Begin(TTree * /*tree*/)
{
  printf("\n\n");
  TString option = GetOption();
}

void DetTCuts_SHMS::SlaveBegin(TTree * /*tree*/)
{
  printf("\n\n");
  TString option = GetOption();
  
  // SHMS Histos
  for (Int_t ipmt = 0; ipmt < 4; ipmt++){
    h1pHGCAdcTdcTDiff[0][ipmt] = new TH1F (Form("pHGCER%d_timeDiff", ipmt+1), Form("SHMS HGCer PMT%d AdcTdcTimeDiff", ipmt+1), 200, 0, 100);
    h1pHGCAdcTdcTDiff[1][ipmt] = new TH1F (Form("pHGCER%d_timeDiff_Cut", ipmt+1), Form("SHMS HGCer PMT%d AdcTdcTimeDiff, ADC Pulse Amp Cut", ipmt+1), 200, 0, 100);
    h2pHGCTDiffADCAmp[ipmt] = new TH2F(Form("pHGCER%d_tDiffADCAmp", ipmt+1), Form("SHMS HGC ADC TDC Diff Time PMT%d vs ADC Pulse Amp; Time (ns); Charge (pC)",ipmt+1), 200, 0, 100, 500, 0.0, 500); 
    GetOutputList()->Add(h1pHGCAdcTdcTDiff[0][ipmt]); GetOutputList()->Add(h1pHGCAdcTdcTDiff[1][ipmt]);
    GetOutputList()->Add(h2pHGCTDiffADCAmp[ipmt]);
  }
  for (Int_t nside = 0; nside < sides; nside++){ //Loop over each side
    for (Int_t ipmt = 0; ipmt < 7; ipmt++){ // Loop over PMTs
      h1pAeroAdcTdcTDiff[nside][ipmt] = new TH1F(Form("pAero%d%s_timeDiff", ipmt+1, nsign[nside].c_str()), Form("SHMS Aerogel PMT%d%s AdcTdcTimeDiff", ipmt+1, nsign[nside].c_str()), 200, 0, 300);
      GetOutputList()->Add(h1pAeroAdcTdcTDiff[nside][ipmt]);
    }
  }
  for (Int_t i = 0; i < 12; i++){
    h1pdcTdcT[i] = new TH1F( Form("pDC%s_rawTDC", dc_pl_names[i].c_str()), Form("SHMS DC Plane %s Raw TDC", dc_pl_names[i].c_str()), 200, -20000, 0);
    GetOutputList()->Add(h1pdcTdcT[i]);
  }
  for (Int_t npl = 0; npl < hod_planes; npl++){ // Loop over all hodoscope planes
    for (Int_t nside = 0; nside < sides; nside++){ //Loop over each side
      for (Int_t ipmt = 0; ipmt < pmaxPMT[npl]; ipmt++){ // Loop over each PMT in a particular plane	
	h1pHodoAdcTdcTDiff[npl][nside][ipmt] = new TH1F(Form("pHodo%s%d%s_timeDiff", hod_pl_names[npl].c_str(),ipmt+1,nsign[nside].c_str() ), Form("SHMS Hodo %s%d%s AdcTdcTimeDiff", hod_pl_names[npl].c_str(), ipmt+1,nsign[nside].c_str()), 200, -60, 60);
	h2pHodoTDiffADCAmp[npl][nside][ipmt] = new TH2F(Form("pHodo%s%d%s_tDiffADCAmp", hod_pl_names[npl].c_str(),ipmt+1,nsign[nside].c_str() ), Form("SHMS Hodo %s%d%s AdcTdcTimeDiff vs ADC Pulse Amp; Time (ns); Charge (pC)", hod_pl_names[npl].c_str(), ipmt+1,nsign[nside].c_str()), 200, -60, 60, 500, 0, 500);
	GetOutputList()->Add(h1pHodoAdcTdcTDiff[npl][nside][ipmt]);
	GetOutputList()->Add(h2pHodoTDiffADCAmp[npl][nside][ipmt]);
      }
    }
  }
  for (Int_t nside = 0; nside < sides; nside++){ //Loop over each side
    for (Int_t ipmt = 0; ipmt < 14; ipmt++){ // Loop over PMTs
      h1pPrShAdcTdcTDiff[0][nside][ipmt] = new TH1F(Form("pPrSh%d%s_timeDiff", ipmt+1, nsign[nside].c_str()), Form("SHMS Pre-Shower PMT%d%s AdcTdcTimeDiff", ipmt+1, nsign[nside].c_str()), 200, -100, 100);
      h1pPrShAdcTdcTDiff[1][nside][ipmt] = new TH1F(Form("pPrSh%d%s_timeDiff_Cut", ipmt+1, nsign[nside].c_str()), Form("SHMS Pre-Shower PMT%d%s AdcTdcTimeDiff With ADC Pulse Amp Cut", ipmt+1, nsign[nside].c_str()), 200, -100, 100);
      h2pPrShTDiffADCAmp[nside][ipmt] = new TH2F(Form("pPrSh%d%s_tDiffADCAmp", ipmt+1, nsign[nside].c_str()), Form("SHMS Pre-Shower PMT%d%s AdcTdcTimeDiff vs ADC Pulse Amp; Time(ns); Charge(pC)", ipmt+1, nsign[nside].c_str()), 200, -100, 100, 500, 0, 500);
      GetOutputList()->Add(h1pPrShAdcTdcTDiff[0][nside][ipmt]); GetOutputList()->Add(h1pPrShAdcTdcTDiff[1][nside][ipmt]); 
      GetOutputList()->Add(h2pPrShTDiffADCAmp[nside][ipmt]);
    }
  }
  for(Int_t ipmt = 0; ipmt < 224; ipmt++){
    h1pCalAdcTdcTDiff[ipmt] = new TH1F(Form("pCalPMT%d", ipmt+1), Form("SHMS Calorimeter PMT%d AdcTdcTimeDiff", ipmt+1), 200, -100, 100); 
    GetOutputList()->Add(h1pCalAdcTdcTDiff[ipmt]);
  }
}

Bool_t DetTCuts_SHMS::Process(Long64_t entry)
{
  fReader.SetEntry(entry);
    
  // Fill our SHMS timing histograms, explicitly select only multiplicity 1 events
  for (Int_t ipmt = 0; ipmt < 4; ipmt++){
    if(P_hgcer_goodAdcMult[ipmt] == 1){
      h1pHGCAdcTdcTDiff[0][ipmt]->Fill(P_hgcer_goodAdcTdcDiffTime[ipmt]);
      if(P_hgcer_goodAdcPulseAmp[ipmt] > CerPulseAmpCut) h1pHGCAdcTdcTDiff[1][ipmt]->Fill(P_hgcer_goodAdcTdcDiffTime[ipmt]);
      h2pHGCTDiffADCAmp[ipmt]->Fill(P_hgcer_goodAdcTdcDiffTime[ipmt], P_hgcer_goodAdcPulseAmp[ipmt]);
    }
  }
  
  for (Int_t nside = 0; nside < sides; nside++){
    for (Int_t ipmt = 0; ipmt < 7; ipmt++){
      if(nside == 0){
	if(P_aero_goodPosAdcMult[ipmt] == 1) h1pAeroAdcTdcTDiff[nside][ipmt]->Fill(P_aero_goodPosAdcTdcDiffTime[ipmt]);
      }
      else if(nside == 1){
	if(P_aero_goodNegAdcMult[ipmt] == 1) h1pAeroAdcTdcTDiff[nside][ipmt]->Fill(P_aero_goodNegAdcTdcDiffTime[ipmt]);  
      }
    }
  }

  for (Int_t i = 0; i < 12; i++){
    if(i == 0){if(P_dc_1u1_nhit[0] == 1) h1pdcTdcT[i]->Fill(P_dc_1u1_rawtdc[0]);}
    else if(i == 1){
      if(P_dc_1u2_nhit[0] == 1) h1pdcTdcT[i]->Fill(P_dc_1u2_rawtdc[0]);
    }
    else if(i == 2){
      if(P_dc_1x1_nhit[0] == 1) h1pdcTdcT[i]->Fill(P_dc_1x1_rawtdc[0]);
    }
    else if(i == 3){
      if(P_dc_1x2_nhit[0] == 1) h1pdcTdcT[i]->Fill(P_dc_1x2_rawtdc[0]);
    }
    else if(i == 4){
      if(P_dc_1v1_nhit[0] == 1) h1pdcTdcT[i]->Fill(P_dc_1v1_rawtdc[0]);
    }
    else if(i == 5){
      if(P_dc_1v2_nhit[0] == 1) h1pdcTdcT[i]->Fill(P_dc_1v2_rawtdc[0]);
    }
    else if(i == 6){
      if(P_dc_2u1_nhit[0] == 1) h1pdcTdcT[i]->Fill(P_dc_2u1_rawtdc[0]);
    }
    else if(i == 7){
      if(P_dc_2u2_nhit[0] == 1) h1pdcTdcT[i]->Fill(P_dc_2u2_rawtdc[0]);
    }
    else if(i == 8){
      if(P_dc_2x1_nhit[0] == 1) h1pdcTdcT[i]->Fill(P_dc_2x1_rawtdc[0]);
    }
    else if(i == 9){
      if(P_dc_2x2_nhit[0] == 1) h1pdcTdcT[i]->Fill(P_dc_2x2_rawtdc[0]);
    }
    else if(i == 10){
      if(P_dc_2v1_nhit[0] == 1) h1pdcTdcT[i]->Fill(P_dc_2v1_rawtdc[0]);
    }
    else if(i == 11){
      if(P_dc_2v2_nhit[0] == 1) h1pdcTdcT[i]->Fill(P_dc_2v2_rawtdc[0]);
    }
  }

  for (Int_t npl = 0; npl < hod_planes; npl++){ // Loop over all hodoscope planes
    for (Int_t nside = 0; nside < sides; nside++){ //Loop over each side
      for (Int_t ipmt = 0; ipmt < pmaxPMT[npl]; ipmt++){ // Loop over each PMT in a particular plane	
	if (npl == 0 && nside == 0){
	  if (P_hod_1x_GoodPosAdcMult[ipmt] == 1){
	    h1pHodoAdcTdcTDiff[npl][nside][ipmt]->Fill(P_hod_1x_GoodPosAdcTdcDiffTime[ipmt]);
	    h2pHodoTDiffADCAmp[npl][nside][ipmt]->Fill(P_hod_1x_GoodPosAdcTdcDiffTime[ipmt], P_hod_1x_GoodPosAdcPulseAmp[ipmt]); 
	  }
	}
	else if (npl == 1 && nside == 0){
	  if (P_hod_1y_GoodPosAdcMult[ipmt] == 1){
	    h1pHodoAdcTdcTDiff[npl][nside][ipmt]->Fill(P_hod_1y_GoodPosAdcTdcDiffTime[ipmt]);
	    h2pHodoTDiffADCAmp[npl][nside][ipmt]->Fill(P_hod_1y_GoodPosAdcTdcDiffTime[ipmt], P_hod_1y_GoodPosAdcPulseAmp[ipmt]);
	  }
	}
	else if (npl == 2 && nside == 0){
	  if (P_hod_2x_GoodPosAdcMult[ipmt] == 1) {
	    h1pHodoAdcTdcTDiff[npl][nside][ipmt]->Fill(P_hod_2x_GoodPosAdcTdcDiffTime[ipmt]);
	    h2pHodoTDiffADCAmp[npl][nside][ipmt]->Fill(P_hod_2x_GoodPosAdcTdcDiffTime[ipmt], P_hod_2x_GoodPosAdcPulseAmp[ipmt]);   
	  }
	}  
	else if (npl == 3 && nside == 0){
	  if (P_hod_2y_GoodPosAdcMult[ipmt] == 1){
	    h1pHodoAdcTdcTDiff[npl][nside][ipmt]->Fill(P_hod_2y_GoodPosAdcTdcDiffTime[ipmt]);
	    h2pHodoTDiffADCAmp[npl][nside][ipmt]->Fill(P_hod_2y_GoodPosAdcTdcDiffTime[ipmt], P_hod_2y_GoodPosAdcPulseAmp[ipmt]);     
	  }
	}
	else if (npl == 0 && nside == 1){
	  if (P_hod_1x_GoodNegAdcMult[ipmt] == 1){
	    h1pHodoAdcTdcTDiff[npl][nside][ipmt]->Fill(P_hod_1x_GoodNegAdcTdcDiffTime[ipmt]);
	    h2pHodoTDiffADCAmp[npl][nside][ipmt]->Fill(P_hod_1x_GoodNegAdcTdcDiffTime[ipmt], P_hod_1x_GoodNegAdcPulseAmp[ipmt]);   
	  }
	}
	else if (npl == 1 && nside == 1){
	  if (P_hod_1y_GoodNegAdcMult[ipmt] == 1){
	    h1pHodoAdcTdcTDiff[npl][nside][ipmt]->Fill(P_hod_1y_GoodNegAdcTdcDiffTime[ipmt]);
	    h2pHodoTDiffADCAmp[npl][nside][ipmt]->Fill(P_hod_1y_GoodNegAdcTdcDiffTime[ipmt], P_hod_1y_GoodNegAdcPulseAmp[ipmt]);
	  }
	}
	else if (npl == 2 && nside == 1){
	  if (P_hod_2x_GoodNegAdcMult[ipmt] == 1){
	    h1pHodoAdcTdcTDiff[npl][nside][ipmt]->Fill(P_hod_2x_GoodNegAdcTdcDiffTime[ipmt]);
	    h2pHodoTDiffADCAmp[npl][nside][ipmt]->Fill(P_hod_2x_GoodNegAdcTdcDiffTime[ipmt], P_hod_2x_GoodNegAdcPulseAmp[ipmt]);
	  }
	}  
	else if (npl == 3 && nside == 1){
	  if (P_hod_2y_GoodNegAdcMult[ipmt] == 1){
	    h1pHodoAdcTdcTDiff[npl][nside][ipmt]->Fill(P_hod_2y_GoodNegAdcTdcDiffTime[ipmt]);
	    h2pHodoTDiffADCAmp[npl][nside][ipmt]->Fill(P_hod_2y_GoodNegAdcTdcDiffTime[ipmt], P_hod_2y_GoodNegAdcPulseAmp[ipmt]);  
	  }
	}
      }
    }
  }  

  for (Int_t nside = 0; nside < sides; nside++){
    for (Int_t ipmt = 0; ipmt < 14; ipmt++){
      if(nside == 0){
	if(P_cal_pr_goodPosAdcMult[ipmt] == 1) {
	  h1pPrShAdcTdcTDiff[0][nside][ipmt]->Fill(P_cal_pr_goodPosAdcTdcDiffTime[ipmt]);
	  if(P_cal_pr_goodPosAdcPulseAmp[ipmt] > PrShPulseAmpCut) h1pPrShAdcTdcTDiff[1][nside][ipmt]->Fill(P_cal_pr_goodPosAdcTdcDiffTime[ipmt]);
	  h2pPrShTDiffADCAmp[nside][ipmt]->Fill(P_cal_pr_goodPosAdcTdcDiffTime[ipmt], P_cal_pr_goodPosAdcPulseAmp[ipmt]);
	}
      }
      else if(nside == 1){
	if(P_cal_pr_goodNegAdcMult[ipmt] == 1){
	  h1pPrShAdcTdcTDiff[0][nside][ipmt]->Fill(P_cal_pr_goodNegAdcTdcDiffTime[ipmt]);
	  if(P_cal_pr_goodNegAdcPulseAmp[ipmt] > PrShPulseAmpCut) h1pPrShAdcTdcTDiff[1][nside][ipmt]->Fill(P_cal_pr_goodNegAdcTdcDiffTime[ipmt]);
	  h2pPrShTDiffADCAmp[nside][ipmt]->Fill(P_cal_pr_goodNegAdcTdcDiffTime[ipmt], P_cal_pr_goodNegAdcPulseAmp[ipmt]);
	}  
      }
    }
  }

  for (Int_t ipmt = 0; ipmt < 224; ipmt++){
    if(P_cal_fly_goodAdcMult[ipmt] == 1) h1pCalAdcTdcTDiff[ipmt]->Fill(P_cal_fly_goodAdcTdcDiffTime[ipmt]);
  }

  return kTRUE;

}

void DetTCuts_SHMS::SlaveTerminate()
{
}

void DetTCuts_SHMS::Terminate()
{
  cout << "Finished processing" << endl;
  printf("\n");
  TString option = GetOption();

  TFile *Histogram_file = new TFile(Form("TimeWindowHistos_SHMS_Run%i.root",option.Atoi()),"RECREATE");
  TString outputpdf = Form("TimeWindowPlots_SHMS_Run%i.pdf", option.Atoi()) ; 
  TF1 *Gauss_Fit = new TF1("Gauss_Fit","gaus"); 

  TDirectory *DSHMSHGC = Histogram_file->mkdir("SHMS HGC Timing"); DSHMSHGC->cd();  
  TCanvas *CSHMSHGC = new TCanvas("CSHMSHGC", "SHMS HGC timing plots", 300,100,1000,900);
  TCanvas *CSHMSHGC2 = new TCanvas("CSHMSHGC2", "SHMS HGC 2D plots", 300,100,1000,900);
  CSHMSHGC->Divide(2,2); CSHMSHGC2->Divide(2,2);
  for (Int_t ipmt = 0; ipmt < 4; ipmt++){
    TH1F *SHMSHGC = dynamic_cast<TH1F *>(TProof::GetOutput(Form("pHGCER%d_timeDiff", ipmt+1), fOutput));
    TH1F *SHMSHGCCut = dynamic_cast<TH1F *>(TProof::GetOutput(Form("pHGCER%d_timeDiff_Cut", ipmt+1), fOutput));
    SHMSHGCCut->Fit("Gauss_Fit", "MQN");
    SHMSHGC_tMin[ipmt] = (Gauss_Fit->GetParameter(1) - (5*Gauss_Fit->GetParameter(2))); SHMSHGC_tMax[ipmt] = (Gauss_Fit->GetParameter(1) + (5*Gauss_Fit->GetParameter(2)));     
    LSHMSHGC_tMin[ipmt] = new TLine(SHMSHGC_tMin[ipmt], 0, SHMSHGC_tMin[ipmt], SHMSHGCCut->GetMaximum());
    LSHMSHGC_tMax[ipmt] = new TLine(SHMSHGC_tMax[ipmt], 0, SHMSHGC_tMax[ipmt], SHMSHGCCut->GetMaximum());
    LSHMSHGC_tMin[ipmt]->SetLineColor(kRed); LSHMSHGC_tMin[ipmt]->SetLineStyle(7); LSHMSHGC_tMin[ipmt]->SetLineWidth(1);
    LSHMSHGC_tMax[ipmt]->SetLineColor(kRed); LSHMSHGC_tMax[ipmt]->SetLineStyle(7); LSHMSHGC_tMax[ipmt]->SetLineWidth(1);
    TH2F* SHMSHGC2D = dynamic_cast<TH2F *>(TProof::GetOutput(Form("pHGCER%d_tDiffADCAmp", ipmt+1), fOutput));
    LCerADCCut = new TLine(0, CerPulseAmpCut, SHMSHGC2D->GetXaxis()->GetBinCenter((SHMSHGC2D->GetMaximumBin())) , CerPulseAmpCut);
    LCerADCCut->SetLineColor(kRed); LCerADCCut->SetLineStyle(7); LCerADCCut->SetLineWidth(1);
    SHMSHGC->Write(); SHMSHGCCut->Write(); SHMSHGCCut->SetLineColor(kRed); SHMSHGC2D->Write();
    CSHMSHGC->cd(ipmt+1); SHMSHGC->Draw(); SHMSHGCCut->Draw("SAME"); LSHMSHGC_tMin[ipmt]->Draw("SAME"); LSHMSHGC_tMax[ipmt]->Draw("SAME");
    CSHMSHGC2->cd(ipmt+1); SHMSHGC2D->Draw("COLZ"); LCerADCCut->Draw("SAME");
  }

  TDirectory *DSHMSAERO = Histogram_file->mkdir("SHMS Aerogel Cherenkov Timing"); DSHMSAERO->cd();  
  TCanvas *CSHMSAERO[2];
  for (Int_t nside = 0; nside < sides; nside++){ //Loop over each side
    CSHMSAERO[nside] = new TCanvas(Form("CSHMSAERO%s", nsign[nside].c_str()),  Form("SHMS Aerogel  %sPMT Timing", nsign[nside].c_str()), 300,100,1000,900);
    CSHMSAERO[nside]->Divide(2, 4);
    for (Int_t ipmt = 0; ipmt < 7; ipmt++){ // Loop over PMTs
      TH1F *SHMSAERO = dynamic_cast<TH1F *>(TProof::GetOutput(Form("pAero%d%s_timeDiff", ipmt+1, nsign[nside].c_str()), fOutput));
      SHMSAERO->Write();
      SHMSAERO_tMin[nside][ipmt] = (SHMSAERO->GetMean() - (5*SHMSAERO->GetStdDev()));
      SHMSAERO_tMax[nside][ipmt] = (SHMSAERO->GetMean() + (5*SHMSAERO->GetStdDev()));
      if(SHMSAERO_tMin[nside][ipmt] < 0) SHMSAERO_tMin[nside][ipmt] = 0;
      LSHMSAERO_tMin[nside][ipmt] = new TLine(SHMSAERO_tMin[nside][ipmt], 0, SHMSAERO_tMin[nside][ipmt], SHMSAERO->GetMaximum());
      LSHMSAERO_tMax[nside][ipmt] = new TLine(SHMSAERO_tMax[nside][ipmt], 0, SHMSAERO_tMax[nside][ipmt], SHMSAERO->GetMaximum());
      LSHMSAERO_tMin[nside][ipmt]->SetLineColor(kRed); LSHMSAERO_tMin[nside][ipmt]->SetLineStyle(7); LSHMSAERO_tMin[nside][ipmt]->SetLineWidth(1);
      LSHMSAERO_tMax[nside][ipmt]->SetLineColor(kRed); LSHMSAERO_tMax[nside][ipmt]->SetLineStyle(7); LSHMSAERO_tMax[nside][ipmt]->SetLineWidth(1);
      CSHMSAERO[nside]->cd(ipmt+1); SHMSAERO->Draw(); LSHMSAERO_tMin[nside][ipmt]->Draw("SAME"); LSHMSAERO_tMax[nside][ipmt]->Draw("SAME");
    }
  }
  
  TDirectory *DSHMSDC = Histogram_file->mkdir("SHMS DC Timing"); DSHMSDC->cd();  
  TCanvas *CSHMSDC = new TCanvas("CSHMSDC", "SHMS DC timing plots", 300,100,1000,900);
  CSHMSDC->Divide(4, 3);
  for (Int_t i = 0; i < 12; i++){
    TH1F *SHMSDC = dynamic_cast<TH1F *>(TProof::GetOutput(Form("pDC%s_rawTDC", dc_pl_names[i].c_str()), fOutput));
    SHMSDC->Write();
    SHMSDC_tMin[i] = (SHMSDC->GetMean() - (5*SHMSDC->GetStdDev()));
    SHMSDC_tMax[i] = (SHMSDC->GetMean() + (5*SHMSDC->GetStdDev()));
    LSHMSDC_tMin[i] = new TLine(SHMSDC_tMin[i], 0, SHMSDC_tMin[i], SHMSDC->GetMaximum());
    LSHMSDC_tMax[i] = new TLine(SHMSDC_tMax[i], 0, SHMSDC_tMax[i], SHMSDC->GetMaximum());
    LSHMSDC_tMin[i]->SetLineColor(kRed); LSHMSDC_tMin[i]->SetLineStyle(7); LSHMSDC_tMin[i]->SetLineWidth(1);
    LSHMSDC_tMax[i]->SetLineColor(kRed); LSHMSDC_tMax[i]->SetLineStyle(7); LSHMSDC_tMax[i]->SetLineWidth(1);
    CSHMSDC->cd(i+1); SHMSDC->Draw(); LSHMSDC_tMin[i]->Draw("SAME"); LSHMSDC_tMax[i]->Draw("SAME");
  }

  TDirectory *DSHMSHODO = Histogram_file->mkdir("SHMS Hodoscope Timing"); DSHMSHODO->cd();  
  TCanvas *CSHMSHODO[4][2];  
  TCanvas *CSHMSHODO2[4][2];
  for (Int_t npl = 0; npl < hod_planes; npl++){ // Loop over all hodoscope planes
    for (Int_t nside = 0; nside < sides; nside++){ //Loop over each side
      CSHMSHODO[npl][nside] = new TCanvas(Form("CSHMSHODO%s%s", hod_pl_names[npl].c_str(), nsign[nside].c_str()),  Form("SHMS Hodoscope %s%s Timing", hod_pl_names[npl].c_str(), nsign[nside].c_str()), 300,100,1000,900);
      CSHMSHODO2[npl][nside] = new TCanvas(Form("CSHMSHODO2%s%s", hod_pl_names[npl].c_str(), nsign[nside].c_str()),  Form("SHMS Hodoscope %s%s 2D", hod_pl_names[npl].c_str(), nsign[nside].c_str()), 300,100,1000,900);
      if (npl != 3){
	CSHMSHODO[npl][nside]->Divide(5, 3); CSHMSHODO2[npl][nside]->Divide(5, 3);
      }
      else if (npl == 3){
	CSHMSHODO[npl][nside]->Divide(7, 3); CSHMSHODO2[npl][nside]->Divide(7, 3);
      }
      for (Int_t ipmt = 0; ipmt < pmaxPMT[npl]; ipmt++){ // Loop over each PMT in a particular plane	
	TH1F *SHMSHODO = dynamic_cast<TH1F *>(TProof::GetOutput(Form("pHodo%s%d%s_timeDiff", hod_pl_names[npl].c_str(),ipmt+1,nsign[nside].c_str() ), fOutput));
	if((SHMSHODO->GetEntries()) == 0){ // If histo is empty, set some default window value
	  SHMSHODO_tMin[npl][nside][ipmt] = -80;
	  SHMSHODO_tMax[npl][nside][ipmt] = 80;
	}
	else if((SHMSHODO->GetEntries()) != 0){ // If entries in the histogram, get windows normally
	  SHMSHODO->Fit("Gauss_Fit", "MQN");
	  SHMSHODO_tMin[npl][nside][ipmt] = (Gauss_Fit->GetParameter(1) - (3*Gauss_Fit->GetParameter(2)));
	  SHMSHODO_tMax[npl][nside][ipmt] = (Gauss_Fit->GetParameter(1) + (5*Gauss_Fit->GetParameter(2)));
	}
	LSHMSHODO_tMin[npl][nside][ipmt] = new TLine(SHMSHODO_tMin[npl][nside][ipmt], 0, SHMSHODO_tMin[npl][nside][ipmt], SHMSHODO->GetMaximum());
	LSHMSHODO_tMax[npl][nside][ipmt] = new TLine(SHMSHODO_tMax[npl][nside][ipmt], 0, SHMSHODO_tMax[npl][nside][ipmt], SHMSHODO->GetMaximum());
	LSHMSHODO_tMin[npl][nside][ipmt]->SetLineColor(kRed); LSHMSHODO_tMin[npl][nside][ipmt]->SetLineStyle(7); LSHMSHODO_tMin[npl][nside][ipmt]->SetLineWidth(1);
	LSHMSHODO_tMax[npl][nside][ipmt]->SetLineColor(kRed); LSHMSHODO_tMax[npl][nside][ipmt]->SetLineStyle(7); LSHMSHODO_tMax[npl][nside][ipmt]->SetLineWidth(1);
	TH2F *SHMSHODO2D = dynamic_cast<TH2F *>(TProof::GetOutput(Form("pHodo%s%d%s_tDiffADCAmp", hod_pl_names[npl].c_str(),ipmt+1,nsign[nside].c_str() ), fOutput));
	SHMSHODO->Write(); SHMSHODO2D->Write();
	CSHMSHODO[npl][nside]->cd(ipmt+1); SHMSHODO->Draw(); LSHMSHODO_tMin[npl][nside][ipmt]->Draw("SAME"); LSHMSHODO_tMax[npl][nside][ipmt]->Draw("SAME");
	CSHMSHODO2[npl][nside]->cd(ipmt+1); SHMSHODO2D->Draw("COLZ"); LSHMSHODO_tMin[npl][nside][ipmt]->Draw("SAME"); LSHMSHODO_tMax[npl][nside][ipmt]->Draw("SAME");
      }
    }
  }

  TDirectory *DSHMSPRSH = Histogram_file->mkdir("SHMS Pre-Shower Timing"); DSHMSPRSH->cd();  
  TCanvas *CSHMSPRSH[2]; TCanvas *CSHMSPRSH2[2];
  for (Int_t nside = 0; nside < sides; nside++){ //Loop over each side
    CSHMSPRSH[nside] = new TCanvas(Form("CSHMSPRSH%s", nsign[nside].c_str()),  Form("SHMS Pre-Shower  %sPMT Timing", nsign[nside].c_str()), 300,100,1000,900);
    CSHMSPRSH2[nside] = new TCanvas(Form("CSHMSPRSH2%s", nsign[nside].c_str()),  Form("SHMS Pre-Shower  %sPMT 2D Timing", nsign[nside].c_str()), 300,100,1000,900);    
    CSHMSPRSH[nside]->Divide(5, 3); CSHMSPRSH2[nside]->Divide(5, 3);
    for (Int_t ipmt = 0; ipmt < 14; ipmt++){ // Loop over PMTs
      TH1F *SHMSPRSH = dynamic_cast<TH1F *>(TProof::GetOutput(Form("pPrSh%d%s_timeDiff", ipmt+1, nsign[nside].c_str()), fOutput));
      TH1F *SHMSPRSHCut = dynamic_cast<TH1F *>(TProof::GetOutput(Form("pPrSh%d%s_timeDiff_Cut", ipmt+1, nsign[nside].c_str()), fOutput));
      if((SHMSPRSHCut->GetEntries()) != 0){
	if ((SHMSPRSHCut->GetBinContent((SHMSPRSHCut->GetMaximumBin()))) >= 50){
	  SHMSPRSHCut->Fit("Gauss_Fit", "QNN");
	  SHMSPRSH_tMin[nside][ipmt] = (Gauss_Fit->GetParameter(1) - (5*Gauss_Fit->GetParameter(2))); 
	  SHMSPRSH_tMax[nside][ipmt] = (Gauss_Fit->GetParameter(1) + (5*Gauss_Fit->GetParameter(2)));
	}
	else if(SHMSPRSHCut->GetBinContent((SHMSPRSHCut->GetMaximumBin())) < 50){
	  SHMSPRSH_tMin[nside][ipmt] = (SHMSPRSHCut->GetMean() - 20); 
	  SHMSPRSH_tMax[nside][ipmt] = (SHMSPRSHCut->GetMean() + 20);  
	}
      }
      else if ((SHMSPRSHCut->GetEntries()) == 0){
	SHMSPRSH_tMin[nside][ipmt] = -80; 
	SHMSPRSH_tMax[nside][ipmt] = 80;  
      }
      LSHMSPRSH_tMin[nside][ipmt] = new TLine(SHMSPRSH_tMin[nside][ipmt], 0, SHMSPRSH_tMin[nside][ipmt], SHMSPRSH->GetMaximum());
      LSHMSPRSH_tMax[nside][ipmt] = new TLine(SHMSPRSH_tMax[nside][ipmt], 0, SHMSPRSH_tMax[nside][ipmt], SHMSPRSH->GetMaximum());
      LSHMSPRSH_tMin[nside][ipmt]->SetLineColor(kRed); LSHMSPRSH_tMin[nside][ipmt]->SetLineStyle(7); LSHMSPRSH_tMin[nside][ipmt]->SetLineWidth(1);
      LSHMSPRSH_tMax[nside][ipmt]->SetLineColor(kRed); LSHMSPRSH_tMax[nside][ipmt]->SetLineStyle(7); LSHMSPRSH_tMax[nside][ipmt]->SetLineWidth(1);
      TH2F *SHMSPRSH2D = dynamic_cast<TH2F *>(TProof::GetOutput(Form("pPrSh%d%s_tDiffADCAmp", ipmt+1, nsign[nside].c_str()), fOutput));
      LPrShADCCut = new TLine(-100, PrShPulseAmpCut, SHMSPRSH2D->GetXaxis()->GetBinCenter((SHMSPRSH2D->GetMaximumBin())) , PrShPulseAmpCut);
      LPrShADCCut->SetLineColor(kRed); LPrShADCCut->SetLineStyle(7); LPrShADCCut->SetLineWidth(1);
      SHMSPRSH->Write(); SHMSPRSHCut->Write(); SHMSPRSHCut->SetLineColor(kRed); SHMSPRSH2D->Write();
      CSHMSPRSH[nside]->cd(ipmt+1); SHMSPRSH->Draw(); SHMSPRSHCut->Draw("SAME"); LSHMSPRSH_tMin[nside][ipmt]->Draw("SAME"); LSHMSPRSH_tMax[nside][ipmt]->Draw("SAME");
      CSHMSPRSH2[nside]->cd(ipmt+1); SHMSPRSH2D->Draw("COLZ"); LPrShADCCut->Draw("SAME");
    }
  }
   
  TDirectory *DSHMSCAL = Histogram_file->mkdir("SHMS Calorimeter Timing"); DSHMSCAL->cd();  
  TCanvas *CSHMSCAL[14]; // 16 histograms per canvas
  for(Int_t row = 0; row < 14; row++){
    CSHMSCAL[row] = new TCanvas(Form("CSHMSCAL%d", row+1),  Form("SHMS Pre-Shower Row %d", row+1), 300,100,1000,900);
    CSHMSCAL[row]->Divide(4, 4);     
    for(Int_t ipmt = 0; ipmt < 16; ipmt++){
      TH1F *SHMSCAL = dynamic_cast<TH1F *>(TProof::GetOutput(Form("pCalPMT%d", (row*16)+ipmt+1), fOutput)); 
      SHMSCAL->Write();
      if(SHMSCAL->GetBinContent((SHMSCAL->GetMaximumBin())) >= 10){
	SHMSCAL_tMin[row][ipmt] = (SHMSCAL->GetMean() - (5*SHMSCAL->GetStdDev()));
	SHMSCAL_tMax[row][ipmt] = (SHMSCAL->GetMean() + (5*SHMSCAL->GetStdDev()));
      }
      else if(SHMSCAL->GetBinContent((SHMSCAL->GetMaximumBin())) < 10){
	SHMSCAL_tMin[row][ipmt] = (SHMSCAL->GetMean() - 20);
	SHMSCAL_tMax[row][ipmt] = (SHMSCAL->GetMean() + 20);	
      }
      LSHMSCAL_tMin[row][ipmt] = new TLine(SHMSCAL_tMin[row][ipmt], 0, SHMSCAL_tMin[row][ipmt], SHMSCAL->GetMaximum());
      LSHMSCAL_tMax[row][ipmt] = new TLine(SHMSCAL_tMax[row][ipmt], 0, SHMSCAL_tMax[row][ipmt], SHMSCAL->GetMaximum());
      LSHMSCAL_tMin[row][ipmt]->SetLineColor(kRed); LSHMSCAL_tMin[row][ipmt]->SetLineStyle(7); LSHMSCAL_tMin[row][ipmt]->SetLineWidth(1);
      LSHMSCAL_tMax[row][ipmt]->SetLineColor(kRed); LSHMSCAL_tMax[row][ipmt]->SetLineStyle(7); LSHMSCAL_tMax[row][ipmt]->SetLineWidth(1);
      CSHMSCAL[row]->cd(ipmt+1); SHMSCAL->Draw(); SHMSCAL->Draw(); LSHMSCAL_tMin[row][ipmt]->Draw("SAME"); LSHMSCAL_tMax[row][ipmt]->Draw("SAME");
    }
  }

  CSHMSHGC->Print(outputpdf+"[");
  CSHMSHGC->Print(outputpdf);
  CSHMSHGC2->Print(outputpdf);
  CSHMSAERO[0]->Print(outputpdf);
  CSHMSAERO[1]->Print(outputpdf);
  CSHMSDC->Print(outputpdf);
  for (Int_t npl = 0; npl < hod_planes; npl++){ // Loop over all hodoscope planes
    for (Int_t nside = 0; nside < sides; nside++){ //Loop over each side
      CSHMSHODO[npl][nside]->Print(outputpdf);
      CSHMSHODO2[npl][nside]->Print(outputpdf);
    }
  }
  CSHMSPRSH[0]->Print(outputpdf);
  CSHMSPRSH2[0]->Print(outputpdf);
  CSHMSPRSH[1]->Print(outputpdf);
  CSHMSPRSH2[1]->Print(outputpdf);
  for(Int_t row = 0; row < 14; row++){
    CSHMSCAL[row]->Print(outputpdf);
  }
  CSHMSHGC->Print(outputpdf+"]");
  
  Histogram_file->Close();

  // Output time windows to some parameter files
  // This code is heavily based on code written by Carlos Yero for a similar analysis script so credit for it goes to him here!

  string n_side[2] = {"Pos", "Neg"};
  string n_side_cal[2] = {"pos", "neg"};
  string n_lim[2] = {"Min", "Max"};
  
  ofstream out_phodo;
  ofstream out_pprsh;  
  ofstream out_pcal;  
  ofstream out_pdc;   
  ofstream out_phgcer;
  ofstream out_paero; 

  //SHMS Hodo
  out_phodo.open(Form("SHMS/Hodo/phodo_tWin_%d.param", option.Atoi()));
  out_phodo << "; SHMS Hodoscope Parameter File Containing TimeWindow Min/Max Cuts " << endl;
  out_phodo << " " << endl;
  out_phodo << " " << endl;
  out_phodo << " " << endl;
  //SHMS PreSh
  out_pprsh.open(Form("SHMS/Cal/pprsh_tWin_%d.param", option.Atoi()));
  out_pprsh << "; SHMS Pre-Shower Parameter File Containing TimeWindow Min/Max Cuts " << endl;
  out_pprsh << " " << endl;
  out_pprsh << " " << endl;
  out_pprsh << " " << endl;
  //SHMS Fly's Eye Cal
  out_pcal.open(Form("SHMS/Cal/pcal_tWin_%d.param", option.Atoi()));
  out_pcal << "; SHMS Fly's Eye Calorimeter  Parameter File Containing TimeWindow Min/Max Cuts " << endl;
  out_pcal << " " << endl;
  out_pcal << " " << endl;
  out_pcal << " " << endl;
  //SHMS DC
  out_pdc.open(Form("SHMS/DC/pdc_tWin_%d.param", option.Atoi()));
  out_pdc << "; SHMS DC  Parameter File Containing TimeWindow Min/Max Cuts " << endl;
  out_pdc << " " << endl;
  out_pdc << " " << endl;
  out_pdc << " " << endl;
  //SHMS HGCER
  out_phgcer.open(Form("/SHMS/HGC/phgcer_tWin_%d.param", option.Atoi()));
  out_phgcer << "; SHMS Heavy Gas Cer  Parameter File Containing TimeWindow Min/Max Cuts " << endl;
  out_phgcer << " " << endl;
  out_phgcer << " " << endl;
  out_phgcer << " " << endl;
  //SHMS AERO
  out_paero.open(Form("SHMS/Aero/paero_tWin_%d.param", option.Atoi()));
  out_paero << "; SHMS Aerogel Cer  Parameter File Containing TimeWindow Min/Max Cuts " << endl;
  out_paero << " " << endl;
  out_paero << " " << endl;
  out_paero << " " << endl;

  for(Int_t iside = 0; iside<2; iside++){
    //Loop over Min/Max Window Limits
    for (Int_t lim = 0; lim<2; lim++){ 
      //Minimum Time Window
      if(lim==0){
	//SHMS Hodo
	out_phodo << "" << endl;
	out_phodo << "; " << setw(32) << "1x " << setw(19) << "1y " << setw(16) << "2x " << setw(16) << "2y " << endl;
	out_phodo << Form("phodo_%sAdcTimeWindow%s = ", n_side[iside].c_str(), n_lim[lim].c_str());
	//SHMS PreSHower
	out_pprsh << "" << endl;
	out_pprsh << Form("pcal_%s_AdcTimeWindow%s = ", n_side_cal[iside].c_str(), n_lim[lim].c_str());   
	//SHMS_Aero
	out_paero << "" << endl;
	out_paero << Form("paero_adc%sTimeWindow%s = ", n_side[iside].c_str(),n_lim[lim].c_str());
	if(iside==0){
	  //SHMS Fly's Eye
	  out_pcal << "" << endl;
	  out_pcal << Form("pcal_arr_AdcTimeWindow%s = ", n_lim[lim].c_str());
	  //SHMS DC
	  out_pdc << "" << endl;
	  out_pdc << "pdc_tdc_min_win = ";
	  //SHMS HGCER
	  out_phgcer << "" << endl;
	  out_phgcer << "phgcer_adcTimeWindowMin = ";
	}
      }
      //Maximum Time Window
      if(lim==1){
	//SHMS Hodo
	out_phodo << "" << endl;
	out_phodo << "; " << setw(32) << "1x " << setw(19) << "1y " << setw(16) << "2x " << setw(16) << "2y " << endl;
	out_phodo << Form("phodo_%sAdcTimeWindow%s = ", n_side[iside].c_str(), n_lim[lim].c_str());
	//SHMS PreSHower
	out_pprsh << "" << endl;
	out_pprsh << Form("pcal_%s_AdcTimeWindow%s = ", n_side_cal[iside].c_str(), n_lim[lim].c_str());
	//SHMS_Aero
	out_paero << "" << endl;
	out_paero << Form("paero_adc%sTimeWindow%s = ", n_side[iside].c_str(),n_lim[lim].c_str());
	if(iside==0){
	  //SHMS Fly's Eye
	  out_pcal << "" << endl;
	  out_pcal << Form("pcal_arr_AdcTimeWindow%s = ", n_lim[lim].c_str());
	  //SHMS DC
	  out_pdc << "" << endl;
	  out_pdc << "pdc_tdc_max_win = ";
	  //SHMS HGCER
	  out_phgcer << "" << endl;
	  out_phgcer << "phgcer_adcTimeWindowMax = ";
	}
      }

      for(int ipmt = 0; ipmt<21; ipmt++){     
	//------Write out SHMS Hodo Param-------
	if(ipmt==0){	
	  if (lim==0){
	    out_phodo << setprecision(2) << SHMSHODO_tMin[0][iside][ipmt] << ", " << setw(15) << SHMSHODO_tMin[1][iside][ipmt] << ", " << setw(15) << SHMSHODO_tMin[2][iside][ipmt] << ", " << setw(15) << SHMSHODO_tMin[3][iside][ipmt] << fixed << endl; 
	  }
	  if(lim==1){
	    out_phodo << setprecision(2) << SHMSHODO_tMax[0][iside][ipmt] << ", " << setw(15) << SHMSHODO_tMax[1][iside][ipmt] << ", " << setw(15) << SHMSHODO_tMax[2][iside][ipmt] << ", " << setw(15) << SHMSHODO_tMax[3][iside][ipmt] << fixed << endl; 
	  }
	}   
	else{
	  if(lim==0){
	    out_phodo << setw(32) << setprecision(2) << SHMSHODO_tMin[0][iside][ipmt] << ", " << setw(15) << SHMSHODO_tMin[1][iside][ipmt] << ", " << setw(15) << SHMSHODO_tMin[2][iside][ipmt] << ", " << setw(15) << SHMSHODO_tMin[3][iside][ipmt] << fixed << endl; 
	  }
	  if(lim==1){
	    out_phodo << setw(32) << setprecision(2) << SHMSHODO_tMax[0][iside][ipmt] << ", " << setw(15) << SHMSHODO_tMax[1][iside][ipmt] << ", " << setw(15) << SHMSHODO_tMax[2][iside][ipmt] << ", " << setw(15) << SHMSHODO_tMax[3][iside][ipmt] << fixed << endl; 
	  }	
	}
      } //end loop over pmts

      // ------Write SHMS PreShower Param-------
      // Lower Limit Time Window Cut
	if(lim==0){
	  out_pprsh << setprecision(2) << SHMSPRSH_tMin[iside][0] << ", " << SHMSPRSH_tMin[iside][1] << ", " 
		    <<  SHMSPRSH_tMin[iside][2] << ", "  <<  SHMSPRSH_tMin[iside][3]  << ", " 
		    <<  SHMSPRSH_tMin[iside][4] << ", "  <<  SHMSPRSH_tMin[iside][5]  << ", " 
		    <<  SHMSPRSH_tMin[iside][6] << ", "  <<  SHMSPRSH_tMin[iside][7]  << ", "
		    <<  SHMSPRSH_tMin[iside][8] << ", "  <<  SHMSPRSH_tMin[iside][9]  << ", " 
		    <<  SHMSPRSH_tMin[iside][10] << ", " <<  SHMSPRSH_tMin[iside][11] << ", " 
		    <<  SHMSPRSH_tMin[iside][12] << ", " <<  SHMSPRSH_tMin[iside][13] << fixed << endl;
	}
      //Upper Limit Time Window Cut
      if(lim==1){
	out_pprsh << setprecision(2) << SHMSPRSH_tMax[iside][0] << ", " << SHMSPRSH_tMax[iside][1] << ", " 
		  <<  SHMSPRSH_tMax[iside][2] << ", "  <<  SHMSPRSH_tMax[iside][3]  << ", " 
		  <<  SHMSPRSH_tMax[iside][4] << ", "  <<  SHMSPRSH_tMax[iside][5]  << ", " 
		  <<  SHMSPRSH_tMax[iside][6] << ", "  <<  SHMSPRSH_tMax[iside][7]  << ", "
		  <<  SHMSPRSH_tMax[iside][8] << ", "  <<  SHMSPRSH_tMax[iside][9]  << ", " 
		  <<  SHMSPRSH_tMax[iside][10] << ", " <<  SHMSPRSH_tMax[iside][11] << ", " 
		  <<  SHMSPRSH_tMax[iside][12] << ", " <<  SHMSPRSH_tMax[iside][13] << fixed << endl;
      }

      //------Write SHMS Aerogel Param-------
      for(Int_t ipmt = 0; ipmt < 7; ipmt++){
	if(lim==0){
	  out_paero << setw(2) << setprecision(2) << SHMSAERO_tMin[iside][ipmt] << ( (ipmt+1) == 7 ? "\n" : ", ") << fixed;
	}
	if(lim==1){
	  out_paero << setw(2) << setprecision(2) << SHMSAERO_tMax[iside][ipmt] << ( (ipmt+1) == 7 ? "\n" : ", ") << fixed;
	}
      }
	  
      if(iside==0){
	//Loop over DC planes
	for(Int_t i = 0; i < 12; i++){
	  //Lower Limit Time Window Cut
	  if(lim==0){
	    out_pdc << setw(2) << setprecision(2) << SHMSDC_tMin[i] << ", " << fixed;
	  }
	  //Upper Limit Time Window Cut
	  if(lim==1){
	    out_pdc << setw(2) << setprecision(2) << SHMSDC_tMax[i] << ", " << fixed;
	  }
	} //End loop over DC Planes
		
	  //---------Write SHMS Fly's Eye Calorimeter Param-------------
	for(Int_t row = 0; row < 14; row++){
	  for(Int_t ipmt = 0; ipmt < 16; ipmt++){  
	    //Lower Limit Time Window Cut
	    if(lim==0){
	      out_pcal << setw(2) << setprecision(2) << SHMSCAL_tMin[row][ipmt] << ( (ipmt+1) == 16 ? "\n" : ", ") << fixed;
	    }
	    //Upper Limit Time Window Cut
	    if(lim==1){
	      out_pcal << setw(2) << setprecision(2) << SHMSCAL_tMax[row][ipmt] << ( (ipmt+1) == 16 ? "\n" : ", ") << fixed; 
	    }
	  }
	} //End Fly's Eye Cal PMT Loop

	  //---------Write HMS/SHMS CER Param-------------  
	  //Loop over PMTs
	for (int ipmt = 0; ipmt<4; ipmt++){
	  //Lower Limit Time Window Cut
	  if(lim==0){
	    //SHMS HGCER
	    out_phgcer << setprecision(2) << SHMSHGC_tMin[ipmt] << ", " << fixed;
	  }
	 
	  //Upper Limit Time Window Cut
	  if(lim==1){
	    //SHMS HGCER
	    out_phgcer << setprecision(2) << SHMSHGC_tMax[ipmt] << ", " << fixed;
	  }
	}
      } // End loop over min/max limits
    } // End loop over sides
  }
}

