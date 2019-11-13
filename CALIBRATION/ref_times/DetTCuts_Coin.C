// Stephen Kay - University of Regina - 2019 // 

#define DetTCuts_Coin_cxx

#include "DetTCuts_Coin.h"
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

void DetTCuts_Coin::Begin(TTree * /*tree*/)
{
  printf("\n\n");
  TString option = GetOption();
}

void DetTCuts_Coin::SlaveBegin(TTree * /*tree*/)
{
  printf("\n\n");
  TString option = GetOption();

  //HMS Histos
  for (Int_t ipmt = 0; ipmt < 2; ipmt++){
    h1hCerAdcTdcTDiff[0][ipmt] = new TH1F (Form("hCER%d_timeDiff", ipmt+1), Form("HMS Cer PMT%d AdcTdcTimeDiff", ipmt+1), 200, 0, 200);
    h1hCerAdcTdcTDiff[1][ipmt] = new TH1F (Form("hCER%d_timeDiff_Cut", ipmt+1), Form("HMS Cer PMT%d AdcTdcTimeDiff, ADC Pulse Amp Cut", ipmt+1), 200, 0, 200);
    h2hCerTDiffADCAmp[ipmt] = new TH2F(Form("hCER%d_tDiffADCAmp", ipmt+1), Form("HMS Cer ADC TDC Diff Time PMT%d vs ADC Pulse Amp; Time (ns); Charge (pC)",ipmt+1), 200, 0, 200, 500, 0.0, 500);
    GetOutputList()->Add(h1hCerAdcTdcTDiff[0][ipmt]); GetOutputList()->Add(h1hCerAdcTdcTDiff[1][ipmt]);
    GetOutputList()->Add(h2hCerTDiffADCAmp[ipmt]);
  }
  for (Int_t i = 0; i < 12; i++){
    h1hdcTdcT[i] = new TH1F( Form("hDC%s_rawTDC", dc_pl_names[i].c_str()), Form("HMS DC Plane %s Raw TDC", dc_pl_names[i].c_str()), 200, -20000, 0);
    GetOutputList()->Add(h1hdcTdcT[i]);
  }
  for (Int_t npl = 0; npl < cal_planes; npl++){ // Loop over all calorimeter planes
    for (Int_t nside = 0; nside < sides; nside++){ //Loop over each side
      if(npl == 2 && nside == 1) continue; // Skip 3ta/4ta- since they don't exist!
      if(npl == 3 && nside == 1) continue;
      for (Int_t ipmt = 0; ipmt < 13; ipmt++){ // Loop over each PMT in a particular plane	
	h1hCalAdcTdcTDiff[npl][nside][ipmt] = new TH1F(Form("hCal%s%d%s_timeDiff", cal_pl_names[npl].c_str(), ipmt+1, nsign[nside].c_str()), Form("HMS Cal %s%d%s AdcTdcTimeDiff", cal_pl_names[npl].c_str(), ipmt+1, nsign[nside].c_str()), 200, -100, 100);
	GetOutputList()->Add(h1hCalAdcTdcTDiff[npl][nside][ipmt]);
      }
    }
  }
  for (Int_t npl = 0; npl < hod_planes; npl++){ // Loop over all hodoscope planes
    for (Int_t nside = 0; nside < sides; nside++){ //Loop over each side
      for (Int_t ipmt = 0; ipmt < hmaxPMT[npl]; ipmt++){ // Loop over each PMT in a particular plane	
	h1hHodoAdcTdcTDiff[npl][nside][ipmt] = new TH1F(Form("hHodo%s%d%s_timeDiff", hod_pl_names[npl].c_str(),ipmt+1,nsign[nside].c_str() ), Form("HMS Hodo %s%d%s AdcTdcTimeDiff", hod_pl_names[npl].c_str(), ipmt+1, nsign[nside].c_str()), 200, -100, 100);
	h2hHodoTDiffADCAmp[npl][nside][ipmt] = new TH2F(Form("hHodo%s%d%s_tDiffADCAmp", hod_pl_names[npl].c_str(),ipmt+1,nsign[nside].c_str() ), Form("HMS Hodo %s%d%s AdcTdcTimeDiff vs ADC Pulse Amp; Time (ns); Charge (pC)", hod_pl_names[npl].c_str(), ipmt+1,nsign[nside].c_str()), 200, -60, 60, 500, 0, 500);
	GetOutputList()->Add(h1hHodoAdcTdcTDiff[npl][nside][ipmt]);
	GetOutputList()->Add(h2hHodoTDiffADCAmp[npl][nside][ipmt]);
      }
    }
  }
  
  // SHMS Histos
  for (Int_t ipmt = 0; ipmt < 4; ipmt++){
    h1pHGCAdcTdcTDiff[0][ipmt] = new TH1F (Form("pHGCER%d_timeDiff", ipmt+1), Form("SHMS HGCer PMT%d AdcTdcTimeDiff", ipmt+1), 300, -50, 100);
    h1pHGCAdcTdcTDiff[1][ipmt] = new TH1F (Form("pHGCER%d_timeDiff_Cut", ipmt+1), Form("SHMS HGCer PMT%d AdcTdcTimeDiff, ADC Pulse Amp Cut", ipmt+1), 300, -50, 100);
    //h1pHGCAdcTdcTDiff[2][ipmt] = new TH1F (Form("pHGCER%d_timeDiff_AerogelTest", ipmt+1), Form("SHMS HGCer PMT%d AdcTdcTimeDiff Aerogel Cut", ipmt+1), 200, 0, 100);
    h2pHGCTDiffADCAmp[ipmt] = new TH2F(Form("pHGCER%d_tDiffADCAmp", ipmt+1), Form("SHMS HGC ADC TDC Diff Time PMT%d vs ADC Pulse Amp; Time (ns); Charge (pC)",ipmt+1), 300, -50, 100, 500, 0.0, 500); 
    GetOutputList()->Add(h1pHGCAdcTdcTDiff[0][ipmt]); GetOutputList()->Add(h1pHGCAdcTdcTDiff[1][ipmt]); //GetOutputList()->Add(h1pHGCAdcTdcTDiff[2][ipmt]);
    GetOutputList()->Add(h2pHGCTDiffADCAmp[ipmt]);
    h2HGCxyDist[ipmt] = new TH2F(Form("pHGCER%d_xyDist", ipmt+1), Form ("SHMS y vs x PMT%d for 0 < AdcDiffTime < 20; y(cm);x(cm)", ipmt+1), 100, -50, 50, 100, -50, 50);
    GetOutputList()->Add(h2HGCxyDist[ipmt]);
    
    // for(Int_t i = 0; i < 4; i++){
    //   h2HGCxyDist[i][ipmt] = new TH2F(Form("pHGCER%d_%d_xyDist", ipmt+1, i+1), Form ("SHMS y vs x PMT%d Peak %d; y(cm);x(cm)", ipmt+1, i+1), 100, -50, 50, 100, -50, 50);
    //   GetOutputList()->Add(h2HGCxyDist[i][ipmt]);
    // }
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
    h2pCalTDiffADCAmp[ipmt] = new TH2F(Form("pCalPMT%d_tDiffADCAmp", ipmt+1), Form("SHMS Calorimeter PMT%d AdcTdcTimeDiff vs ADC Pulse Amp; Time(ns); Charge(pC)", ipmt+1), 200, -100, 100, 200, 0, 500);
    GetOutputList()->Add(h1pCalAdcTdcTDiff[ipmt]);
    GetOutputList()->Add(h2pCalTDiffADCAmp[ipmt]);
  }
}

Bool_t DetTCuts_Coin::Process(Long64_t entry)
{
  fReader.SetEntry(entry);

  // if((abs(H_gtr_dp[0]) < 20) && (H_cal_etotnorm[0] > 0.8)){ // Delta cut to test if it removed ghost bands, still present
  // Fill our HMS timing histograms, explicitly select only multiplicity 1 events
  for (Int_t ipmt = 0; ipmt < 2; ipmt++){
    if(H_cer_goodAdcMult[ipmt] == 1){
      h1hCerAdcTdcTDiff[0][ipmt]->Fill(H_cer_goodAdcTdcDiffTime[ipmt]);
      if(H_cer_goodAdcPulseAmp[ipmt] > CerPulseAmpCut) h1hCerAdcTdcTDiff[1][ipmt]->Fill(H_cer_goodAdcTdcDiffTime[ipmt]); 
      h2hCerTDiffADCAmp[ipmt]->Fill(H_cer_goodAdcTdcDiffTime[ipmt], H_cer_goodAdcPulseAmp[ipmt]);
    }
  }
  // This is a disgustingly bad way of doing this, really need to figure out how to have some ARRAY of readers
  for (Int_t i = 0; i < 12; i++){
    if(i == 0){
      if(H_dc_1u1_nhit[0] == 1) h1hdcTdcT[i]->Fill(H_dc_1u1_rawtdc[0]);
    }
    else if(i == 1){
      if(H_dc_1u2_nhit[0] == 1) h1hdcTdcT[i]->Fill(H_dc_1u2_rawtdc[0]);
    }
    else if(i == 2){
      if(H_dc_1x1_nhit[0] == 1) h1hdcTdcT[i]->Fill(H_dc_1x1_rawtdc[0]);
    }
    else if(i == 3){
      if(H_dc_1x2_nhit[0] == 1) h1hdcTdcT[i]->Fill(H_dc_1x2_rawtdc[0]);
    }
    else if(i == 4){
      if(H_dc_1v1_nhit[0] == 1) h1hdcTdcT[i]->Fill(H_dc_1v1_rawtdc[0]);
    }
    else if(i == 5){
      if(H_dc_1v2_nhit[0] == 1) h1hdcTdcT[i]->Fill(H_dc_1v2_rawtdc[0]);
    }
    else if(i == 6){
      if(H_dc_2u1_nhit[0] == 1) h1hdcTdcT[i]->Fill(H_dc_2u1_rawtdc[0]);
    }
    else if(i == 7){
      if(H_dc_2u2_nhit[0] == 1) h1hdcTdcT[i]->Fill(H_dc_2u2_rawtdc[0]);
    }
    else if(i == 8){
      if(H_dc_2x1_nhit[0] == 1) h1hdcTdcT[i]->Fill(H_dc_2x1_rawtdc[0]);
    }
    else if(i == 9){
      if(H_dc_2x2_nhit[0] == 1) h1hdcTdcT[i]->Fill(H_dc_2x2_rawtdc[0]);
    }
    else if(i == 10){
      if(H_dc_2v1_nhit[0] == 1) h1hdcTdcT[i]->Fill(H_dc_2v1_rawtdc[0]);
    }
    else if(i == 11){
      if(H_dc_2v2_nhit[0] == 1) h1hdcTdcT[i]->Fill(H_dc_2v2_rawtdc[0]);
    }
  }
  
  for (Int_t npl = 0; npl < cal_planes; npl++){ // Loop over all calorimeter planes
    for (Int_t nside = 0; nside < sides; nside++){ //Loop over each side
      for (Int_t ipmt = 0; ipmt < 13; ipmt++){ // Loop over each PMT in a particular plane	
	if (npl == 0 && nside == 0) {
	  if (H_cal_1pr_goodPosAdcMult[ipmt] == 1) h1hCalAdcTdcTDiff[npl][nside][ipmt]->Fill(H_cal_1pr_goodPosAdcTdcDiffTime[ipmt]);
	}
	else if (npl == 1 && nside == 0){
	  if (H_cal_2ta_goodPosAdcMult[ipmt] == 1) h1hCalAdcTdcTDiff[npl][nside][ipmt]->Fill(H_cal_2ta_goodPosAdcTdcDiffTime[ipmt]);
	}
	else if (npl == 2 && nside == 0){
	  if (H_cal_3ta_goodPosAdcMult[ipmt] == 1) h1hCalAdcTdcTDiff[npl][nside][ipmt]->Fill(H_cal_3ta_goodPosAdcTdcDiffTime[ipmt]);
	}  
	else if (npl == 3 && nside == 0){
	  if (H_cal_4ta_goodPosAdcMult[ipmt] == 1) h1hCalAdcTdcTDiff[npl][nside][ipmt]->Fill(H_cal_4ta_goodPosAdcTdcDiffTime[ipmt]);
	}
	else if (npl == 0 && nside == 1){
	  if (H_cal_1pr_goodNegAdcMult[ipmt] == 1) h1hCalAdcTdcTDiff[npl][nside][ipmt]->Fill(H_cal_1pr_goodNegAdcTdcDiffTime[ipmt]);
	}
	else if (npl == 1 && nside == 1){
	  if (H_cal_2ta_goodNegAdcMult[ipmt] == 1) h1hCalAdcTdcTDiff[npl][nside][ipmt]->Fill(H_cal_2ta_goodNegAdcTdcDiffTime[ipmt]);
	}
      }
    }
  }

  for (Int_t npl = 0; npl < hod_planes; npl++){ // Loop over all hodoscope planes
    for (Int_t nside = 0; nside < sides; nside++){ //Loop over each side
      for (Int_t ipmt = 0; ipmt < hmaxPMT[npl]; ipmt++){ // Loop over each PMT in a particular plane	
	if (npl == 0 && nside == 0){
	  if (H_hod_1x_GoodPosAdcMult[ipmt] == 1){
	    h1hHodoAdcTdcTDiff[npl][nside][ipmt]->Fill(H_hod_1x_GoodPosAdcTdcDiffTime[ipmt]);
	    h2hHodoTDiffADCAmp[npl][nside][ipmt]->Fill(H_hod_1x_GoodPosAdcTdcDiffTime[ipmt], H_hod_1x_GoodPosAdcPulseAmp[ipmt]); 
	  }
	}
	else if (npl == 1 && nside == 0){
	  if (H_hod_1y_GoodPosAdcMult[ipmt] == 1){
	    h1hHodoAdcTdcTDiff[npl][nside][ipmt]->Fill(H_hod_1y_GoodPosAdcTdcDiffTime[ipmt]);
	    h2hHodoTDiffADCAmp[npl][nside][ipmt]->Fill(H_hod_1y_GoodPosAdcTdcDiffTime[ipmt], H_hod_1y_GoodPosAdcPulseAmp[ipmt]); 
	  }
	}
	else if (npl == 2 && nside == 0){
	  if (H_hod_2x_GoodPosAdcMult[ipmt] == 1){
	    h1hHodoAdcTdcTDiff[npl][nside][ipmt]->Fill(H_hod_2x_GoodPosAdcTdcDiffTime[ipmt]);
	    h2hHodoTDiffADCAmp[npl][nside][ipmt]->Fill(H_hod_2x_GoodPosAdcTdcDiffTime[ipmt], H_hod_2x_GoodPosAdcPulseAmp[ipmt]); 
	  }
	}  
	else if (npl == 3 && nside == 0){
	  if (H_hod_2y_GoodPosAdcMult[ipmt] == 1){
	    h1hHodoAdcTdcTDiff[npl][nside][ipmt]->Fill(H_hod_2y_GoodPosAdcTdcDiffTime[ipmt]);
	    h2hHodoTDiffADCAmp[npl][nside][ipmt]->Fill(H_hod_2y_GoodPosAdcTdcDiffTime[ipmt], H_hod_2y_GoodPosAdcPulseAmp[ipmt]); 
	  }
	}
	else if (npl == 0 && nside == 1){
	  if (H_hod_1x_GoodNegAdcMult[ipmt] == 1){
	    h1hHodoAdcTdcTDiff[npl][nside][ipmt]->Fill(H_hod_1x_GoodNegAdcTdcDiffTime[ipmt]);
	    h2hHodoTDiffADCAmp[npl][nside][ipmt]->Fill(H_hod_1x_GoodNegAdcTdcDiffTime[ipmt], H_hod_1x_GoodNegAdcPulseAmp[ipmt]); 
	  }
	}
	else if (npl == 1 && nside == 1){
	  if (H_hod_1y_GoodNegAdcMult[ipmt] == 1){
	    h1hHodoAdcTdcTDiff[npl][nside][ipmt]->Fill(H_hod_1y_GoodNegAdcTdcDiffTime[ipmt]);
	    h2hHodoTDiffADCAmp[npl][nside][ipmt]->Fill(H_hod_1y_GoodNegAdcTdcDiffTime[ipmt], H_hod_1y_GoodNegAdcPulseAmp[ipmt]); 
	  }
	}
	else if (npl == 2 && nside == 1){
	  if (H_hod_2x_GoodNegAdcMult[ipmt] == 1){
	    h1hHodoAdcTdcTDiff[npl][nside][ipmt]->Fill(H_hod_2x_GoodNegAdcTdcDiffTime[ipmt]);
	    h2hHodoTDiffADCAmp[npl][nside][ipmt]->Fill(H_hod_2x_GoodNegAdcTdcDiffTime[ipmt], H_hod_2x_GoodNegAdcPulseAmp[ipmt]); 
	  }
	}  
	else if (npl == 3 && nside == 1){
	  if (H_hod_2y_GoodNegAdcMult[ipmt] == 1){
	    h1hHodoAdcTdcTDiff[npl][nside][ipmt]->Fill(H_hod_2y_GoodNegAdcTdcDiffTime[ipmt]);
	    h2hHodoTDiffADCAmp[npl][nside][ipmt]->Fill(H_hod_2y_GoodNegAdcTdcDiffTime[ipmt], H_hod_2y_GoodNegAdcPulseAmp[ipmt]); 
	  }
	}
      }
    }
  }
  //} //Close of PID/delta cut loop

  if(*T_coin_pFADC_TREF_ROC2_adcPulseAmpRaw > 0){ // Cut any events where the ADC raw amplitude is zero, removes ghost band
    // Loop over all Aerogel PMTs, find events with no aerogel signals
    // AeroMultSum = 0;
    // for (Int_t nside = 0; nside < sides; nside++){
    //   for (Int_t ipmt = 0; ipmt < 7; ipmt++){
    // 	if(nside == 0){
    // 	  AeroMultSum += P_aero_goodPosAdcMult[ipmt];
    // 	}
    // 	if(nside == 1){
    // 	  AeroMultSum += P_aero_goodNegAdcMult[ipmt];
    // 	}
    //   }
    // }
    //if((abs(P_gtr_dp[0]) < 20) && (P_cal_etotnorm[0] > 0.8)){
    // Double_t PeakLow[4][4] = {{10, 23, 27, 31}, {10, 14, 22, 30}, {10, 16, 24, 30}, {10, 16, 22, 30}};
    // Double_t PeakHigh[4][4] = {{16, 28, 31, 40}, {14, 20, 30, 40}, {16, 20, 30, 40}, {16, 20, 30, 40}};
    // Fill our SHMS timing histograms, explicitly select only multiplicity 1 events
    for (Int_t ipmt = 0; ipmt < 4; ipmt++){
      if(P_hgcer_goodAdcMult[ipmt] == 1){
	//if (AeroMultSum == 0) h1pHGCAdcTdcTDiff[2][ipmt]->Fill(P_hgcer_goodAdcTdcDiffTime[ipmt]);	
	if(ipmt == 0){if(P_hgcer_goodAdcMult[1] != 0 || P_hgcer_goodAdcMult[2] != 0 || P_hgcer_goodAdcMult[3] != 0 ) continue;}
	else if(ipmt == 1){if(P_hgcer_goodAdcMult[0] != 0 || P_hgcer_goodAdcMult[2] != 0 || P_hgcer_goodAdcMult[3] != 0 ) continue;}
	else if(ipmt == 2){if(P_hgcer_goodAdcMult[1] != 0 || P_hgcer_goodAdcMult[0] != 0 || P_hgcer_goodAdcMult[3] != 0 ) continue;}
	else if(ipmt == 3){if(P_hgcer_goodAdcMult[1] != 0 || P_hgcer_goodAdcMult[2] != 0 || P_hgcer_goodAdcMult[0] != 0 ) continue;}
	h1pHGCAdcTdcTDiff[0][ipmt]->Fill(P_hgcer_goodAdcTdcDiffTime[ipmt]);
        if((0 < P_hgcer_goodAdcTdcDiffTime[ipmt]) && (20 > P_hgcer_goodAdcTdcDiffTime[ipmt]))h2HGCxyDist[ipmt]->Fill(*P_hgcer_yAtCer, *P_hgcer_xAtCer);
	// Fill xy timing plot for each peak, final peak (~30-40) is the "good peak"
	// if((PeakLow[ipmt][0] < P_hgcer_goodAdcTdcDiffTime[ipmt]) && (PeakHigh[ipmt][0] > P_hgcer_goodAdcTdcDiffTime[ipmt]))h2HGCxyDist[0][ipmt]->Fill(*P_hgcer_yAtCer, *P_hgcer_xAtCer);
	// else if((PeakLow[ipmt][1] < P_hgcer_goodAdcTdcDiffTime[ipmt]) && (PeakHigh[ipmt][1] > P_hgcer_goodAdcTdcDiffTime[ipmt]))h2HGCxyDist[1][ipmt]->Fill(*P_hgcer_yAtCer, *P_hgcer_xAtCer);
	// else if((PeakLow[ipmt][2] < P_hgcer_goodAdcTdcDiffTime[ipmt]) && (PeakHigh[ipmt][2] > P_hgcer_goodAdcTdcDiffTime[ipmt]))h2HGCxyDist[2][ipmt]->Fill(*P_hgcer_yAtCer, *P_hgcer_xAtCer);
	// else if((PeakLow[ipmt][3] < P_hgcer_goodAdcTdcDiffTime[ipmt]) && (PeakHigh[ipmt][3] > P_hgcer_goodAdcTdcDiffTime[ipmt]))h2HGCxyDist[3][ipmt]->Fill(*P_hgcer_yAtCer, *P_hgcer_xAtCer);
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
      if(P_cal_fly_goodAdcMult[ipmt] == 1) h2pCalTDiffADCAmp[ipmt]->Fill(P_cal_fly_goodAdcTdcDiffTime[ipmt], P_cal_fly_goodAdcPulseAmp[ipmt]);
    }
  }
  //}//Close of PID/delta cut loop
  return kTRUE;
}

void DetTCuts_Coin::SlaveTerminate()
{
}

void DetTCuts_Coin::Terminate()
{
  cout << "Finished processing" << endl;
  printf("\n");
  gStyle->SetOptLogz();
  TString option = GetOption();

  TFile *Histogram_file = new TFile(Form("TimeWindowHistos_Coin_Run%i.root",option.Atoi()),"RECREATE");
  TString outputpdf = Form("TimeWindowPlots_Coin_Run%i.pdf", option.Atoi()) ; 
  TF1 *Gauss_Fit = new TF1("Gauss_Fit","gaus"); 

  TDirectory *DHMSCER = Histogram_file->mkdir("HMS Cherenkov Timing"); DHMSCER->cd();
  TCanvas *CHMSCER = new TCanvas("CHMSCER", "HMS Cherenkov timing plots", 300,100,1000,900);
  TCanvas *CHMSCER2 = new TCanvas("CHMSCER2", "HMS Cherenkov 2D plots", 300,100,1000,900);
  CHMSCER->Divide(2,1); CHMSCER2->Divide(2,1);
  for (Int_t ipmt = 0; ipmt < 2; ipmt++){
    TH1F *HMSCER = dynamic_cast<TH1F *>(TProof::GetOutput(Form("hCER%d_timeDiff", ipmt+1), fOutput));
    TH1F *HMSCERCut = dynamic_cast<TH1F *>(TProof::GetOutput(Form("hCER%d_timeDiff_Cut", ipmt+1), fOutput));
    HMSCER_tMin[ipmt] = (HMSCERCut->GetMean() - (5*HMSCERCut->GetStdDev())); HMSCER_tMax[ipmt] = (HMSCERCut->GetMean() + (5*HMSCERCut->GetStdDev()));
    LHMSCER_tMin[ipmt] = new TLine(HMSCER_tMin[ipmt], 0, HMSCER_tMin[ipmt], HMSCERCut->GetMaximum());
    LHMSCER_tMax[ipmt] = new TLine(HMSCER_tMax[ipmt], 0, HMSCER_tMax[ipmt], HMSCERCut->GetMaximum());
    LHMSCER_tMin[ipmt]->SetLineColor(kRed); LHMSCER_tMin[ipmt]->SetLineStyle(7); LHMSCER_tMin[ipmt]->SetLineWidth(1);
    LHMSCER_tMax[ipmt]->SetLineColor(kRed); LHMSCER_tMax[ipmt]->SetLineStyle(7); LHMSCER_tMax[ipmt]->SetLineWidth(1);
    TH2F* HMSCER2D = dynamic_cast<TH2F *>(TProof::GetOutput(Form("hCER%d_tDiffADCAmp", ipmt+1), fOutput));
    LCerADCCut = new TLine(0, CerPulseAmpCut, HMSCER2D->GetXaxis()->GetBinCenter((HMSCER2D->GetMaximumBin())) , CerPulseAmpCut);
    LCerADCCut->SetLineColor(kRed); LCerADCCut->SetLineStyle(7); LCerADCCut->SetLineWidth(1);
    HMSCER->Write(); HMSCERCut->Write(); HMSCERCut->SetLineColor(kRed); HMSCER2D->Write();
    CHMSCER->cd(ipmt+1); HMSCER->Draw(); HMSCERCut->Draw("SAME"); LHMSCER_tMin[ipmt]->Draw("SAME"); LHMSCER_tMax[ipmt]->Draw("SAME"); 
    CHMSCER2->cd(ipmt+1); HMSCER2D->Draw("COLZ"); LCerADCCut->Draw("SAME");
  }

  TDirectory *DHMSDC = Histogram_file->mkdir("HMS DC Timing"); DHMSDC->cd();
  TCanvas *CHMSDC = new TCanvas("CHMSDC", "HMS DC timing plots", 300,100,1000,900);
  CHMSDC->Divide(4, 3);
  for (Int_t i = 0; i < 12; i++){
    TH1F *HMSDC = dynamic_cast<TH1F *>(TProof::GetOutput(Form("hDC%s_rawTDC", dc_pl_names[i].c_str()), fOutput));
    HMSDC->Write();
    HMSDC_tMin[i] = (HMSDC->GetMean() - (5*HMSDC->GetStdDev()));
    HMSDC_tMax[i] = (HMSDC->GetMean() + (5*HMSDC->GetStdDev()));
    LHMSDC_tMin[i] = new TLine(HMSDC_tMin[i], 0, HMSDC_tMin[i], HMSDC->GetMaximum());
    LHMSDC_tMax[i] = new TLine(HMSDC_tMax[i], 0, HMSDC_tMax[i], HMSDC->GetMaximum());
    LHMSDC_tMin[i]->SetLineColor(kRed); LHMSDC_tMin[i]->SetLineStyle(7); LHMSDC_tMin[i]->SetLineWidth(1);
    LHMSDC_tMax[i]->SetLineColor(kRed); LHMSDC_tMax[i]->SetLineStyle(7); LHMSDC_tMax[i]->SetLineWidth(1);
    CHMSDC->cd(i+1); HMSDC->Draw(); LHMSDC_tMin[i]->Draw("SAME"); LHMSDC_tMax[i]->Draw("SAME");
  }

  TDirectory *DHMSCAL = Histogram_file->mkdir("HMS Calorimeter Timing"); DHMSCAL->cd();  
  TCanvas *CHMSCAL[4][2];
  for (Int_t npl = 0; npl < cal_planes; npl++){ // Loop over all calorimeter planes
    for (Int_t nside = 0; nside < sides; nside++){ //Loop over each side
      if(npl == 2 && nside == 1) continue; // Skip 3ta/4ta- since they don't exist!
      if(npl == 3 && nside == 1) continue;
      CHMSCAL[npl][nside] = new TCanvas(Form("CHMSCAL%s%s", cal_pl_names[npl].c_str(), nsign[nside].c_str()),  Form("HMS Calorimeter %s%s Timing", cal_pl_names[npl].c_str(), nsign[nside].c_str()), 300,100,1000,900);
      CHMSCAL[npl][nside]->Divide(5, 3);
      for (Int_t ipmt = 0; ipmt < 13; ipmt++){ // Loop over each PMT in a particular plane	
	TH1F *HMSCAL = dynamic_cast<TH1F *>(TProof::GetOutput(Form("hCal%s%d%s_timeDiff", cal_pl_names[npl].c_str(), ipmt+1, nsign[nside].c_str()), fOutput));
	HMSCAL->Write();
	HMSCAL_tMin[npl][nside][ipmt] = (HMSCAL->GetMean() - (5*HMSCAL->GetStdDev()));
	HMSCAL_tMax[npl][nside][ipmt] = (HMSCAL->GetMean() + (5*HMSCAL->GetStdDev()));
	LHMSCAL_tMin[npl][nside][ipmt] = new TLine(HMSCAL_tMin[npl][nside][ipmt], 0, HMSCAL_tMin[npl][nside][ipmt], HMSCAL->GetMaximum());
	LHMSCAL_tMax[npl][nside][ipmt] = new TLine(HMSCAL_tMax[npl][nside][ipmt], 0, HMSCAL_tMax[npl][nside][ipmt], HMSCAL->GetMaximum());
	LHMSCAL_tMin[npl][nside][ipmt]->SetLineColor(kRed); LHMSCAL_tMin[npl][nside][ipmt]->SetLineStyle(7); LHMSCAL_tMin[npl][nside][ipmt]->SetLineWidth(1);
	LHMSCAL_tMax[npl][nside][ipmt]->SetLineColor(kRed); LHMSCAL_tMax[npl][nside][ipmt]->SetLineStyle(7); LHMSCAL_tMax[npl][nside][ipmt]->SetLineWidth(1);
	CHMSCAL[npl][nside]->cd(ipmt+1); HMSCAL->Draw(); LHMSCAL_tMin[npl][nside][ipmt]->Draw("SAME"); LHMSCAL_tMax[npl][nside][ipmt]->Draw("SAME");
      }
    }
  }

  TDirectory *DHMSHODO = Histogram_file->mkdir("HMS Hodoscope Timing"); DHMSHODO->cd();  
  TCanvas *CHMSHODO[4][2];  
  TCanvas *CHMSHODO2[4][2];
  for (Int_t npl = 0; npl < hod_planes; npl++){ // Loop over all hodoscope planes
    for (Int_t nside = 0; nside < sides; nside++){ //Loop over each side
      CHMSHODO[npl][nside] = new TCanvas(Form("CHMSHODO%s%s", hod_pl_names[npl].c_str(), nsign[nside].c_str()),  Form("HMS Hodoscope %s%s Timing", hod_pl_names[npl].c_str(), nsign[nside].c_str()), 300,100,1000,900);
      CHMSHODO2[npl][nside] = new TCanvas(Form("CHMSHODO2%s%s", hod_pl_names[npl].c_str(), nsign[nside].c_str()),  Form("HMS Hodoscope %s%s 2D", hod_pl_names[npl].c_str(), nsign[nside].c_str()), 300,100,1000,900);
      CHMSHODO[npl][nside]->Divide(4, 4); CHMSHODO2[npl][nside]->Divide(4, 4);
      for (Int_t ipmt = 0; ipmt < hmaxPMT[npl]; ipmt++){ // Loop over each PMT in a particular plane	
	TH1F *HMSHODO = dynamic_cast<TH1F *>(TProof::GetOutput(Form("hHodo%s%d%s_timeDiff", hod_pl_names[npl].c_str(),ipmt+1,nsign[nside].c_str() ), fOutput));
	HMSHODO->Write();
	HMSHODO_tMin[npl][nside][ipmt] = (HMSHODO->GetMean() - (5*HMSHODO->GetStdDev()));
	HMSHODO_tMax[npl][nside][ipmt] = (HMSHODO->GetMean() + (5*HMSHODO->GetStdDev()));
	LHMSHODO_tMin[npl][nside][ipmt] = new TLine(HMSHODO_tMin[npl][nside][ipmt], 0, HMSHODO_tMin[npl][nside][ipmt], HMSHODO->GetMaximum());
	LHMSHODO_tMax[npl][nside][ipmt] = new TLine(HMSHODO_tMax[npl][nside][ipmt], 0, HMSHODO_tMax[npl][nside][ipmt], HMSHODO->GetMaximum());
	LHMSHODO_tMin[npl][nside][ipmt]->SetLineColor(kRed); LHMSHODO_tMin[npl][nside][ipmt]->SetLineStyle(7); LHMSHODO_tMin[npl][nside][ipmt]->SetLineWidth(1);
	LHMSHODO_tMax[npl][nside][ipmt]->SetLineColor(kRed); LHMSHODO_tMax[npl][nside][ipmt]->SetLineStyle(7); LHMSHODO_tMax[npl][nside][ipmt]->SetLineWidth(1);
	CHMSHODO[npl][nside]->cd(ipmt+1); HMSHODO->Draw(); LHMSHODO_tMin[npl][nside][ipmt]->Draw("SAME"); LHMSHODO_tMax[npl][nside][ipmt]->Draw("SAME");
	TH2F *HMSHODO2D = dynamic_cast<TH2F *>(TProof::GetOutput(Form("hHodo%s%d%s_tDiffADCAmp", hod_pl_names[npl].c_str(),ipmt+1,nsign[nside].c_str() ), fOutput));
	HMSHODO2D->Write();
	CHMSHODO2[npl][nside]->cd(ipmt+1); HMSHODO2D->Draw("COLZ"); LHMSHODO_tMin[npl][nside][ipmt]->Draw("SAME"); LHMSHODO_tMax[npl][nside][ipmt]->Draw("SAME");
      }
    }
  }

  TDirectory *DSHMSHGC = Histogram_file->mkdir("SHMS HGC Timing"); DSHMSHGC->cd();  
  TCanvas *CSHMSHGC = new TCanvas("CSHMSHGC", "SHMS HGC timing plots", 300,100,1000,900);
  TCanvas *CSHMSHGC2 = new TCanvas("CSHMSHGC2", "SHMS HGC 2D plots", 300,100,1000,900);
  TCanvas *CSHMSHGC3 = new TCanvas("CSHMSHGC3", "SHMS HGC XY plots", 300,100,1000,900);

  // TCanvas *CSHMSHGC3[4];
  CSHMSHGC->Divide(2,2); CSHMSHGC2->Divide(2,2); CSHMSHGC3->Divide(2,2);
  for (Int_t ipmt = 0; ipmt < 4; ipmt++){
    TH1F *SHMSHGC = dynamic_cast<TH1F *>(TProof::GetOutput(Form("pHGCER%d_timeDiff", ipmt+1), fOutput));
    TH1F *SHMSHGCCut = dynamic_cast<TH1F *>(TProof::GetOutput(Form("pHGCER%d_timeDiff_Cut", ipmt+1), fOutput));
    //TH1F *SHMSHGCAeroCut = dynamic_cast<TH1F *>(TProof::GetOutput(Form("pHGCER%d_timeDiff_AerogelTest", ipmt+1), fOutput));
    //SHMSHGC->Fit("Gauss_Fit", "MQN");
    SHMSHGCCut->Fit("Gauss_Fit", "MQN");
    if (Gauss_Fit->GetParameter(2) > 2) Gauss_Fit->SetParameter(2, 2);
    SHMSHGC_tMin[ipmt] = (Gauss_Fit->GetParameter(1) - (5*Gauss_Fit->GetParameter(2))); SHMSHGC_tMax[ipmt] = (Gauss_Fit->GetParameter(1) + (5*Gauss_Fit->GetParameter(2)));     
    if (Gauss_Fit->GetParameter(2) > 3) Gauss_Fit->SetParameter(2, 3);
    LSHMSHGC_tMin[ipmt] = new TLine(SHMSHGC_tMin[ipmt], 0, SHMSHGC_tMin[ipmt], SHMSHGC->GetMaximum());
    LSHMSHGC_tMax[ipmt] = new TLine(SHMSHGC_tMax[ipmt], 0, SHMSHGC_tMax[ipmt], SHMSHGC->GetMaximum());
    LSHMSHGC_tMin[ipmt]->SetLineColor(kRed); LSHMSHGC_tMin[ipmt]->SetLineStyle(7); LSHMSHGC_tMin[ipmt]->SetLineWidth(1);
    LSHMSHGC_tMax[ipmt]->SetLineColor(kRed); LSHMSHGC_tMax[ipmt]->SetLineStyle(7); LSHMSHGC_tMax[ipmt]->SetLineWidth(1);
    TH2F* SHMSHGC2D = dynamic_cast<TH2F *>(TProof::GetOutput(Form("pHGCER%d_tDiffADCAmp", ipmt+1), fOutput));
    TH2F* SHMSHGCXY = dynamic_cast<TH2F *>(TProof::GetOutput(Form("pHGCER%d_xyDist", ipmt+1), fOutput));
    LCerADCCut = new TLine(-100, CerPulseAmpCut, SHMSHGC2D->GetXaxis()->GetBinCenter((SHMSHGC2D->GetMaximumBin())), CerPulseAmpCut);
    LCerADCCut->SetLineColor(kRed); LCerADCCut->SetLineStyle(7); LCerADCCut->SetLineWidth(1);
    SHMSHGC->Write(); SHMSHGCCut->Write(); SHMSHGCCut->SetLineColor(kRed); //SHMSHGCAeroCut->Write();
    SHMSHGC2D->Write();
    SHMSHGCXY->Write();
    CSHMSHGC->cd(ipmt+1); SHMSHGC->Draw(); 
    SHMSHGCCut->Draw("SAME"); 
    LSHMSHGC_tMin[ipmt]->Draw("SAME"); LSHMSHGC_tMax[ipmt]->Draw("SAME");
    CSHMSHGC2->cd(ipmt+1); SHMSHGC2D->Draw("COLZ"); LCerADCCut->Draw("SAME");
    CSHMSHGC3->cd(ipmt+1); SHMSHGCXY->Draw("COLZ");
    // CSHMSHGC3[ipmt] = new TCanvas(Form("CSHMSHGC_PMT%d", ipmt+1), Form("SHMS HGC y vs x PMT %d", ipmt+1), 300,100,1000,900);
    // CSHMSHGC3[ipmt]->Divide(2,2);
    // for (Int_t i = 0; i < 4; i++){
    //   TH2F* SHMSHGCXY2D = dynamic_cast<TH2F *>(TProof::GetOutput(Form("pHGCER%d_%d_xyDist", ipmt+1, i+1), fOutput));
    //   CSHMSHGC3[ipmt]->cd(i+1); SHMSHGCXY2D->Draw("COLZ"); SHMSHGCXY2D->Write();
    // }
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
      SHMSAERO_tMax[nside][ipmt] = (SHMSAERO->GetMean() + (2*SHMSAERO->GetStdDev()));
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
	  SHMSHODO_tMin[npl][nside][ipmt] = (Gauss_Fit->GetParameter(1) - (8*Gauss_Fit->GetParameter(2)));
	  SHMSHODO_tMax[npl][nside][ipmt] = (Gauss_Fit->GetParameter(1) + (10*Gauss_Fit->GetParameter(2))); // Higher up limit so poorly calibrated runs don't cut low amp stuff off
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
      	  SHMSPRSHCut->Fit("Gauss_Fit", "MQN");
      	  SHMSPRSH_tMin[nside][ipmt] = (Gauss_Fit->GetParameter(1) - (5*Gauss_Fit->GetParameter(2))); 
      	  SHMSPRSH_tMax[nside][ipmt] = (Gauss_Fit->GetParameter(1) + (5*Gauss_Fit->GetParameter(2)));
	  if (Gauss_Fit->GetParameter(2) > 2 || Gauss_Fit->GetParameter(2) < 1){ // Prevent the window from being too broad or too narrow
	    SHMSPRSH_tMin[nside][ipmt] = (Gauss_Fit->GetParameter(1) - 10); 
	    SHMSPRSH_tMax[nside][ipmt] = (Gauss_Fit->GetParameter(1) + 10);
	  }
      	}
      	else if(SHMSPRSHCut->GetBinContent((SHMSPRSHCut->GetMaximumBin())) < 50){
      	  SHMSPRSH_tMin[nside][ipmt] = (SHMSPRSHCut->GetMean() - 10); 
      	  SHMSPRSH_tMax[nside][ipmt] = (SHMSPRSHCut->GetMean() + 10);  
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
      SHMSPRSH->Write();SHMSPRSHCut->Write(); SHMSPRSHCut->SetLineColor(kRed); 
      SHMSPRSH2D->Write();
      CSHMSPRSH[nside]->cd(ipmt+1); SHMSPRSH->Draw(); SHMSPRSHCut->Draw("SAME"); 
      LSHMSPRSH_tMin[nside][ipmt]->Draw("SAME"); LSHMSPRSH_tMax[nside][ipmt]->Draw("SAME");
      CSHMSPRSH2[nside]->cd(ipmt+1); SHMSPRSH2D->Draw("COLZ"); LPrShADCCut->Draw("SAME");
    }
  }
  
  TDirectory *DSHMSCAL = Histogram_file->mkdir("SHMS Calorimeter Timing"); DSHMSCAL->cd();  
  TCanvas *CSHMSCAL[14]; // 16 histograms per canvas
  TCanvas *CSHMSCAL2[14];
  for(Int_t row = 0; row < 14; row++){
    CSHMSCAL[row] = new TCanvas(Form("CSHMSCAL%d", row+1),  Form("SHMS Calorimeter Row %d", row+1), 300,100,1000,900);
    CSHMSCAL2[row] = new TCanvas(Form("CSHMSCAL2%d", row+1),  Form("SHMS Calorimeter Row %d 2D", row+1), 300,100,1000,900);
    CSHMSCAL[row]->Divide(4, 4);  CSHMSCAL2[row]->Divide(4, 4);
    for(Int_t ipmt = 0; ipmt < 16; ipmt++){
      TH1F *SHMSCAL = dynamic_cast<TH1F *>(TProof::GetOutput(Form("pCalPMT%d", (row*16)+ipmt+1), fOutput)); 
      TH2F *SHMSCAL2D = dynamic_cast<TH2F *>(TProof::GetOutput(Form("pCalPMT%d_tDiffADCAmp", (row*16)+ipmt+1), fOutput));
      SHMSCAL->Write(); SHMSCAL2D->Write();
      if(SHMSCAL->GetEntries() >= 5){
	if(SHMSCAL->GetBinContent((SHMSCAL->GetMaximumBin())) >= 100){
	  SHMSCAL_tMin[row][ipmt] = (SHMSCAL->GetMean() - (5*SHMSCAL->GetStdDev()));
	  SHMSCAL_tMax[row][ipmt] = (SHMSCAL->GetMean() + (5*SHMSCAL->GetStdDev()));
	  if (SHMSCAL->GetStdDev() > 4 || SHMSCAL->GetStdDev() < 1){ // Stop the window being too wide or too narrow
	    SHMSCAL_tMin[row][ipmt] = (SHMSCAL->GetMean() - 20);
	    SHMSCAL_tMax[row][ipmt] = (SHMSCAL->GetMean() + 20);
	  }
	}
	else if(SHMSCAL->GetBinContent((SHMSCAL->GetMaximumBin())) < 100){
	  SHMSCAL_tMin[row][ipmt] = (SHMSCAL->GetMean() - 20);
	  SHMSCAL_tMax[row][ipmt] = (SHMSCAL->GetMean() + 20);	
	}
      }
      else if (SHMSCAL->GetEntries() < 5){
	SHMSCAL_tMin[row][ipmt] = -40;
	SHMSCAL_tMax[row][ipmt] = 40;	
      }
      
      if(SHMSCAL->GetEntries() >= 5){
	LSHMSCAL_tMin[row][ipmt] = new TLine(SHMSCAL_tMin[row][ipmt], 0, SHMSCAL_tMin[row][ipmt], SHMSCAL->GetMaximum());
	LSHMSCAL_tMax[row][ipmt] = new TLine(SHMSCAL_tMax[row][ipmt], 0, SHMSCAL_tMax[row][ipmt], SHMSCAL->GetMaximum());
      }
      else if (SHMSCAL->GetEntries() < 5){
	LSHMSCAL_tMin[row][ipmt] = new TLine(SHMSCAL_tMin[row][ipmt], 0, SHMSCAL_tMin[row][ipmt], 10);
	LSHMSCAL_tMax[row][ipmt] = new TLine(SHMSCAL_tMax[row][ipmt], 0, SHMSCAL_tMax[row][ipmt], 10);      
      }
      LSHMSCAL_tMin[row][ipmt]->SetLineColor(kRed); LSHMSCAL_tMin[row][ipmt]->SetLineStyle(7); LSHMSCAL_tMin[row][ipmt]->SetLineWidth(1);
      LSHMSCAL_tMax[row][ipmt]->SetLineColor(kRed); LSHMSCAL_tMax[row][ipmt]->SetLineStyle(7); LSHMSCAL_tMax[row][ipmt]->SetLineWidth(1);
      CSHMSCAL[row]->cd(ipmt+1); SHMSCAL->Draw(); SHMSCAL->Draw(); LSHMSCAL_tMin[row][ipmt]->Draw("SAME"); LSHMSCAL_tMax[row][ipmt]->Draw("SAME");
      CSHMSCAL2[row]->cd(ipmt+1); SHMSCAL2D->Draw("COLZ");
    }
  }

  CHMSCER->Print(outputpdf+"[");
  CHMSCER->Print(outputpdf);
  CHMSCER2->Print(outputpdf);
  CHMSDC->Print(outputpdf);
  for (Int_t npl = 0; npl < cal_planes; npl++){ // Loop over all calorimeter planes
    for (Int_t nside = 0; nside < sides; nside++){ //Loop over each side
      if(npl == 2 && nside == 1) continue; // Skip 3ta/4ta- since they don't exist!
      if(npl == 3 && nside == 1) continue;
      CHMSCAL[npl][nside]->Print(outputpdf);
    }
  }
  for (Int_t npl = 0; npl < hod_planes; npl++){ // Loop over all hodoscope planes
    for (Int_t nside = 0; nside < sides; nside++){ //Loop over each side
      CHMSHODO[npl][nside]->Print(outputpdf);
      CHMSHODO2[npl][nside]->Print(outputpdf);
    }
  }

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
    CSHMSCAL2[row]->Print(outputpdf);
  }
  CHMSCER->Print(outputpdf+"]");
  
  // TString outputpdf2 = Form("SHMSHGC_xyPlots_Coin_Run%i.pdf", option.Atoi()) ; 
  // CSHMSHGC3[0]->Print(outputpdf2 +"[");
  // CSHMSHGC->Print(outputpdf2);
  // CSHMSHGC2->Print(outputpdf2);
  // CSHMSHGC3[0]->Print(outputpdf2);
  // CSHMSHGC3[1]->Print(outputpdf2);
  // CSHMSHGC3[2]->Print(outputpdf2);
  // CSHMSHGC3[3]->Print(outputpdf2);
  // CSHMSHGC3[0]->Print(outputpdf2 +"]");

  TString outputpdf2 = Form("SHMSHGC_xyPlots_Coin_Run%i.pdf", option.Atoi()) ; 
  CSHMSHGC3->Print(outputpdf2 +"[");
  CSHMSHGC->Print(outputpdf2);
  CSHMSHGC2->Print(outputpdf2);
  CSHMSHGC3->Print(outputpdf2);
  CSHMSHGC3->Print(outputpdf2 +"]");  

  Histogram_file->Close();

  // Output time windows to some parameter files
  // This code is heavily based on code written by Carlos Yero for a similar analysis script so credit for it goes to him here!

  string n_side[2] = {"Pos", "Neg"};
  string n_side_cal[2] = {"pos", "neg"};
  string n_lim[2] = {"Min", "Max"};
  
  ofstream out_hhodo;
  ofstream out_phodo;
  ofstream out_hcal;
  ofstream out_pprsh;  
  ofstream out_pcal;  
  ofstream out_hdc;   
  ofstream out_pdc;   
  ofstream out_hcer; 
  ofstream out_phgcer;
  ofstream out_paero; 

  //HMS Hodo
  out_hhodo.open(Form("HMS/Hodo/hhodo_tWin_%d.param", option.Atoi()));
  out_hhodo << "; HMS Hodoscope Parameter File Containing TimeWindow Min/Max Cuts " << endl;
  out_hhodo << " " << endl;
  out_hhodo << " " << endl;
  out_hhodo << " " << endl;
  //SHMS Hodo
  out_phodo.open(Form("SHMS/Hodo/phodo_tWin_%d.param", option.Atoi()));
  out_phodo << "; SHMS Hodoscope Parameter File Containing TimeWindow Min/Max Cuts " << endl;
  out_phodo << " " << endl;
  out_phodo << " " << endl;
  out_phodo << " " << endl;
  //HMS Cal
  out_hcal.open(Form("HMS/Cal/hcal_tWin_%d.param", option.Atoi()));
  out_hcal << "; HMS Calorimeter Parameter File Containing TimeWindow Min/Max Cuts " << endl;
  out_hcal << " " << endl;
  out_hcal << " " << endl;
  out_hcal << " " << endl;
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
  //HMS DC
  out_hdc.open(Form("HMS/DC/hdc_tWin_%d.param", option.Atoi()));
  out_hdc << "; HMS DC  Parameter File Containing TimeWindow Min/Max Cuts " << endl;
  out_hdc << " " << endl;
  out_hdc << " " << endl;
  out_hdc << " " << endl;
  //SHMS DC
  out_pdc.open(Form("SHMS/DC/pdc_tWin_%d.param", option.Atoi()));
  out_pdc << "; SHMS DC  Parameter File Containing TimeWindow Min/Max Cuts " << endl;
  out_pdc << " " << endl;
  out_pdc << " " << endl;
  out_pdc << " " << endl;
  //HMS Cer
  out_hcer.open(Form("HMS/Cher/hcer_tWin_%d.param", option.Atoi()));
  out_hcer << "; HMS Cer  Parameter File Containing TimeWindow Min/Max Cuts " << endl;
  out_hcer << " " << endl;
  out_hcer << " " << endl;
  out_hcer << " " << endl;
  //SHMS HGCER
  out_phgcer.open(Form("SHMS/HGC/phgcer_tWin_%d.param", option.Atoi()));
  out_phgcer << "; SHMS Heavy Gas Cer Parameter File Containing TimeWindow Min/Max Cuts " << endl;
  out_phgcer << " " << endl;
  out_phgcer << " " << endl;
  out_phgcer << " " << endl;
  //SHMS AERO
  out_paero.open(Form("SHMS/Aero/paero_tWin_%d.param", option.Atoi()));
  out_paero << "; SHMS Aerogel Cer Parameter File Containing TimeWindow Min/Max Cuts " << endl;
  out_paero << " " << endl;
  out_paero << " " << endl;
  out_paero << " " << endl;

  for(Int_t iside = 0; iside<2; iside++){
    //Loop over Min/Max Window Limits
    for (Int_t lim = 0; lim<2; lim++){ 
      //Minimum Time Window
      if(lim==0){
	//HMS Hodo
	out_hhodo << "" << endl;
	out_hhodo << "; " << setw(32) << "1x " << setw(19) << "1y " << setw(16) << "2x " << setw(16) << "2y " << endl;
	out_hhodo << Form("hhodo_%sAdcTimeWindow%s = ", n_side[iside].c_str(), n_lim[lim].c_str());
	//SHMS Hodo
	out_phodo << "" << endl;
	out_phodo << "; " << setw(32) << "1x " << setw(19) << "1y " << setw(16) << "2x " << setw(16) << "2y " << endl;
	out_phodo << Form("phodo_%sAdcTimeWindow%s = ", n_side[iside].c_str(), n_lim[lim].c_str());
	//HMS Calorimeter
	out_hcal << "" << endl;
	out_hcal << Form("hcal_%s_AdcTimeWindow%s = ", n_side_cal[iside].c_str(), n_lim[lim].c_str());
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
	  //HMS DC
	  out_hdc << "" << endl;
	  out_hdc << "hdc_tdc_min_win = ";
	  //SHMS DC
	  out_pdc << "" << endl;
	  out_pdc << "pdc_tdc_min_win = ";
	  //HMS Cer
	  out_hcer << "" << endl;
	  out_hcer << "hcer_adcTimeWindowMin = ";
	  //SHMS HGCER
	  out_phgcer << "" << endl;
	  out_phgcer << "phgcer_adcTimeWindowMin = ";
	}
      }
      //Maximum Time Window
      if(lim==1){
	//HMS Hodo
	out_hhodo << "" << endl;
	out_hhodo << "; " << setw(32) << "1x " << setw(19) << "1y " << setw(16) << "2x " << setw(16) << "2y " << endl;
	out_hhodo << Form("hhodo_%sAdcTimeWindow%s = ", n_side[iside].c_str(), n_lim[lim].c_str());
	//SHMS Hodo
	out_phodo << "" << endl;
	out_phodo << "; " << setw(32) << "1x " << setw(19) << "1y " << setw(16) << "2x " << setw(16) << "2y " << endl;
	out_phodo << Form("phodo_%sAdcTimeWindow%s = ", n_side[iside].c_str(), n_lim[lim].c_str());
	//HMS Calorimeter
	out_hcal << "" << endl;
	out_hcal << Form("hcal_%s_AdcTimeWindow%s = ", n_side_cal[iside].c_str(), n_lim[lim].c_str());	        
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
	  //HMS DC
	  out_hdc << "" << endl;
	  out_hdc << "hdc_tdc_max_win = ";
	  //SHMS DC
	  out_pdc << "" << endl;
	  out_pdc << "pdc_tdc_max_win = ";
	  //HMS Cer
	  out_hcer << "" << endl;
	  out_hcer << "hcer_adcTimeWindowMax = ";
	  //SHMS HGCER
	  out_phgcer << "" << endl;
	  out_phgcer << "phgcer_adcTimeWindowMax = ";
	}
      }

      for(int ipmt = 0; ipmt<21; ipmt++){     
	//--------Write out HMS Hodo Param---------
	if(ipmt<16){
	  if(ipmt==0){   
	    if (lim==0){
	      out_hhodo << Form("%.1f", HMSHODO_tMin[0][iside][ipmt]) << ", " << setw(15) << Form("%.1f", HMSHODO_tMin[1][iside][ipmt]) << ", " << setw(15) << Form("%.1f", HMSHODO_tMin[2][iside][ipmt]) << ", " << setw(15) << Form("%.1f", HMSHODO_tMin[3][iside][ipmt]) << fixed << endl; 
	    }
	    if(lim==1){
	      out_hhodo << Form("%.1f", HMSHODO_tMax[0][iside][ipmt]) << ", " << setw(15) << Form("%.1f", HMSHODO_tMax[1][iside][ipmt]) << ", " << setw(15) << Form("%.1f", HMSHODO_tMax[2][iside][ipmt]) << ", " << setw(15) << Form("%.1f", HMSHODO_tMax[3][iside][ipmt]) << fixed << endl; 
	    }
	  }
	  else{
	    if(lim==0){
	      out_hhodo << setw(32) << Form("%.1f", HMSHODO_tMin[0][iside][ipmt]) << ", " << setw(15) << Form("%.1f", HMSHODO_tMin[1][iside][ipmt]) << ", " << setw(15) << Form("%.1f", HMSHODO_tMin[2][iside][ipmt]) << ", " << setw(15) << Form("%.1f", HMSHODO_tMin[3][iside][ipmt]) << fixed << endl; 
	    }
	    if(lim==1){
	      out_hhodo << setw(32) << Form("%.1f", HMSHODO_tMax[0][iside][ipmt]) << ", " << setw(15) << Form("%.1f", HMSHODO_tMax[1][iside][ipmt]) << ", " << setw(15) << Form("%.1f", HMSHODO_tMax[2][iside][ipmt]) << ", " << setw(15) << Form("%.1f", HMSHODO_tMax[3][iside][ipmt]) << fixed << endl; 
	    }   
	  }
	}//end HMS Hodo PMT Loop          
	//------Write out SHMS Hodo Param-------
	if(ipmt==0){	
	  if (lim==0){
	    out_phodo << Form("%.1f", SHMSHODO_tMin[0][iside][ipmt]) << ", " << setw(15) << Form("%.1f", SHMSHODO_tMin[1][iside][ipmt]) << ", " << setw(15) << Form("%.1f", SHMSHODO_tMin[2][iside][ipmt]) << ", " << setw(15) << Form("%.1f", SHMSHODO_tMin[3][iside][ipmt]) << fixed << endl; 
	  }
	  if(lim==1){
	    out_phodo << Form("%.1f", SHMSHODO_tMax[0][iside][ipmt]) << ", " << setw(15) << Form("%.1f", SHMSHODO_tMax[1][iside][ipmt]) << ", " << setw(15) << Form("%.1f", SHMSHODO_tMax[2][iside][ipmt]) << ", " << setw(15) << Form("%.1f", SHMSHODO_tMax[3][iside][ipmt]) << fixed << endl; 
	  }
	}   
	else{
	  if(lim==0){
	    out_phodo << setw(32) << Form("%.1f", SHMSHODO_tMin[0][iside][ipmt]) << ", " << setw(15) << Form("%.1f", SHMSHODO_tMin[1][iside][ipmt]) << ", " << setw(15) << Form("%.1f", SHMSHODO_tMin[2][iside][ipmt]) << ", " << setw(15) << Form("%.1f", SHMSHODO_tMin[3][iside][ipmt]) << fixed << endl; 
	  }
	  if(lim==1){
	    out_phodo << setw(32) << Form("%.1f", SHMSHODO_tMax[0][iside][ipmt]) << ", " << setw(15) << Form("%.1f", SHMSHODO_tMax[1][iside][ipmt]) << ", " << setw(15) << Form("%.1f", SHMSHODO_tMax[2][iside][ipmt]) << ", " << setw(15) << Form("%.1f", SHMSHODO_tMax[3][iside][ipmt]) << fixed << endl; 
	  }	
	}
      } //end loop over pmts

      //-----Write out HMS Calorimeter-------
      for(Int_t layer = 0; layer < 4; layer++){	            
	if(layer < 2 ){
	  if(lim==0){
	    out_hcal << Form("%.1f", HMSCAL_tMin[layer][iside][0])<<","
		     << Form("%.1f", HMSCAL_tMin[layer][iside][1])<<","
		     << Form("%.1f", HMSCAL_tMin[layer][iside][2])<<","
		     << Form("%.1f", HMSCAL_tMin[layer][iside][3])<<","
		     << Form("%.1f", HMSCAL_tMin[layer][iside][4])<<","
		     << Form("%.1f", HMSCAL_tMin[layer][iside][5])<<","
		     << Form("%.1f", HMSCAL_tMin[layer][iside][6])<<","
		     << Form("%.1f", HMSCAL_tMin[layer][iside][7])<<","
		     << Form("%.1f", HMSCAL_tMin[layer][iside][8])<<","
		     << Form("%.1f", HMSCAL_tMin[layer][iside][9])<<","
		     << Form("%.1f", HMSCAL_tMin[layer][iside][10])<<","
		     << Form("%.1f", HMSCAL_tMin[layer][iside][11])<<","
		     << Form("%.1f", HMSCAL_tMin[layer][iside][12])<< fixed << endl;
	  } // end Min Limit
	  if(lim==1){
	    out_hcal << Form("%.1f", HMSCAL_tMax[layer][iside][0])<<","
		     << Form("%.1f", HMSCAL_tMax[layer][iside][1])<<","
		     << Form("%.1f", HMSCAL_tMax[layer][iside][2])<<","
		     << Form("%.1f", HMSCAL_tMax[layer][iside][3])<<","
		     << Form("%.1f", HMSCAL_tMax[layer][iside][4])<<","
		     << Form("%.1f", HMSCAL_tMax[layer][iside][5])<<","
		     << Form("%.1f", HMSCAL_tMax[layer][iside][6])<<","
		     << Form("%.1f", HMSCAL_tMax[layer][iside][7])<<","
		     << Form("%.1f", HMSCAL_tMax[layer][iside][8])<<","
		     << Form("%.1f", HMSCAL_tMax[layer][iside][9])<<","
		     << Form("%.1f", HMSCAL_tMax[layer][iside][10])<<","
		     << Form("%.1f", HMSCAL_tMax[layer][iside][11])<<","
		     << Form("%.1f", HMSCAL_tMax[layer][iside][12])<< fixed << endl;
	  } //end Max Limit
	} //end layer<2 requirement
	else if (layer > 1){
	  if(iside == 0){ // Only do +ve side
	    if(lim==0){
	      out_hcal << Form("%.1f", HMSCAL_tMin[layer][iside][0])<<","
		       << Form("%.1f", HMSCAL_tMin[layer][iside][1])<<","
		       << Form("%.1f", HMSCAL_tMin[layer][iside][2])<<","
		       << Form("%.1f", HMSCAL_tMin[layer][iside][3])<<","
		       << Form("%.1f", HMSCAL_tMin[layer][iside][4])<<","
		       << Form("%.1f", HMSCAL_tMin[layer][iside][5])<<","
		       << Form("%.1f", HMSCAL_tMin[layer][iside][6])<<","
		       << Form("%.1f", HMSCAL_tMin[layer][iside][7])<<","
		       << Form("%.1f", HMSCAL_tMin[layer][iside][8])<<","
		       << Form("%.1f", HMSCAL_tMin[layer][iside][9])<<","
		       << Form("%.1f", HMSCAL_tMin[layer][iside][10])<<","
		       << Form("%.1f", HMSCAL_tMin[layer][iside][11])<<","
		       << Form("%.1f", HMSCAL_tMin[layer][iside][12])<< fixed << endl;
	    } // end Min Limit
	    if(lim==1){
	      out_hcal << Form("%.1f", HMSCAL_tMax[layer][iside][0])<<","
		       << Form("%.1f", HMSCAL_tMax[layer][iside][1])<<","
		       << Form("%.1f", HMSCAL_tMax[layer][iside][2])<<","
		       << Form("%.1f", HMSCAL_tMax[layer][iside][3])<<","
		       << Form("%.1f", HMSCAL_tMax[layer][iside][4])<<","
		       << Form("%.1f", HMSCAL_tMax[layer][iside][5])<<","
		       << Form("%.1f", HMSCAL_tMax[layer][iside][6])<<","
		       << Form("%.1f", HMSCAL_tMax[layer][iside][7])<<","
		       << Form("%.1f", HMSCAL_tMax[layer][iside][8])<<","
		       << Form("%.1f", HMSCAL_tMax[layer][iside][9])<<","
		       << Form("%.1f", HMSCAL_tMax[layer][iside][10])<<","
		       << Form("%.1f", HMSCAL_tMax[layer][iside][11])<<","
		       << Form("%.1f", HMSCAL_tMax[layer][iside][12])<< fixed << endl;
	    } //end Max Limit
	  }
	  else if (iside == 1){
	    if(lim==0){
	      out_hcal << setprecision(2) << 0.0 <<","
		       << 0.0 <<","
		       << 0.0 <<","
		       << 0.0 <<","
		       << 0.0 <<","
		       << 0.0 <<","
		       << 0.0 <<","
		       << 0.0 <<","
		       << 0.0 <<","
		       << 0.0 <<","
		       << 0.0 <<","
		       << 0.0 <<","
		       << 0.0 << fixed << endl;
	    } // end Min Limit
	    if(lim==1){
	      out_hcal << setprecision(2) << 0.0 <<","
		       << 0.0 <<","
		       << 0.0 <<","
		       << 0.0 <<","
		       << 0.0 <<","
		       << 0.0 <<","
		       << 0.0 <<","
		       << 0.0 <<","
		       << 0.0 <<","
		       << 0.0 <<","
		       << 0.0 <<","
		       << 0.0 <<","
		       << 0.0 << fixed << endl;
	    } //end Max Limit	      
	  } // End loop over side == 1
	} // End loop over last two layers
      } // End loop over layers

      // ------Write SHMS PreShower Param-------
      // Lower Limit Time Window Cut
	if(lim==0){
	  out_pprsh  << Form("%.1f", SHMSPRSH_tMin[iside][0]) << ", " << Form("%.1f", SHMSPRSH_tMin[iside][1])     << ", " 
		     << Form("%.1f", SHMSPRSH_tMin[iside][2]) << ", "  <<  Form("%.1f", SHMSPRSH_tMin[iside][3])   << ", " 
		     <<  Form("%.1f", SHMSPRSH_tMin[iside][4]) << ", "  <<  Form("%.1f", SHMSPRSH_tMin[iside][5])  << ", " 
		     <<  Form("%.1f", SHMSPRSH_tMin[iside][6]) << ", "  <<  Form("%.1f", SHMSPRSH_tMin[iside][7])  << ", "
		     <<  Form("%.1f", SHMSPRSH_tMin[iside][8]) << ", "  <<  Form("%.1f", SHMSPRSH_tMin[iside][9])  << ", " 
		     <<  Form("%.1f", SHMSPRSH_tMin[iside][10]) << ", " <<  Form("%.1f", SHMSPRSH_tMin[iside][11]) << ", " 
		     <<  Form("%.1f", SHMSPRSH_tMin[iside][12]) << ", " <<  Form("%.1f", SHMSPRSH_tMin[iside][13]) << fixed << endl;
	}
      //Upper Limit Time Window Cut
      if(lim==1){
	  out_pprsh  << Form("%.1f", SHMSPRSH_tMax[iside][0]) << ", "  << Form("%.1f", SHMSPRSH_tMax[iside][1])  << ", " 
		     << Form("%.1f", SHMSPRSH_tMax[iside][2]) << ", "  << Form("%.1f", SHMSPRSH_tMax[iside][3])  << ", " 
		     << Form("%.1f", SHMSPRSH_tMax[iside][4]) << ", "  << Form("%.1f", SHMSPRSH_tMax[iside][5])  << ", " 
		     << Form("%.1f", SHMSPRSH_tMax[iside][6]) << ", "  << Form("%.1f", SHMSPRSH_tMax[iside][7])  << ", "
		     << Form("%.1f", SHMSPRSH_tMax[iside][8]) << ", "  << Form("%.1f", SHMSPRSH_tMax[iside][9])  << ", " 
		     << Form("%.1f", SHMSPRSH_tMax[iside][10]) << ", " << Form("%.1f", SHMSPRSH_tMax[iside][11]) << ", " 
		     << Form("%.1f", SHMSPRSH_tMax[iside][12]) << ", " << Form("%.1f", SHMSPRSH_tMax[iside][13]) << fixed << endl;
      }

      //------Write SHMS Aerogel Param-------
      for(Int_t ipmt = 0; ipmt < 7; ipmt++){
	if(lim==0){
	  out_paero << setw(2) << Form("%.1f", SHMSAERO_tMin[iside][ipmt]) << ( (ipmt+1) == 7 ? "" : ", ") << fixed;
	}
	if(lim==1){
	  out_paero << setw(2) << Form("%.1f", SHMSAERO_tMax[iside][ipmt]) << ( (ipmt+1) == 7 ? "" : ", ") << fixed;
	}
      }
	  
      if(iside==0){
	//Loop over DC planes
	for(Int_t i = 0; i < 12; i++){
	  //Lower Limit Time Window Cut
	  if(lim==0){
	    out_hdc << setw(2)  << Form("%.0f", HMSDC_tMin[i]) << ", " << fixed;
	    out_pdc << setw(2)  << Form("%.0f", SHMSDC_tMin[i]) << ", " << fixed;
	  }
	  //Upper Limit Time Window Cut
	  if(lim==1){
	    out_hdc << setw(2) << Form("%.0f", HMSDC_tMax[i]) << ", " << fixed;
	    out_pdc << setw(2) << Form("%.0f", SHMSDC_tMax[i]) << ", " << fixed;
	  }
	} //End loop over DC Planes
		
	  //---------Write SHMS Fly's Eye Calorimeter Param-------------
	for(Int_t row = 0; row < 14; row++){
	  for(Int_t ipmt = 0; ipmt < 16; ipmt++){  
	    //Lower Limit Time Window Cut
	    if(lim==0){
	      out_pcal << setw(2) << Form("%.1f", SHMSCAL_tMin[row][ipmt]) << ( (ipmt+1) == 16 ? "\n" : ", ") << fixed;
	    }
	    //Upper Limit Time Window Cut
	    if(lim==1){
	      out_pcal << setw(2) << Form("%.1f", SHMSCAL_tMax[row][ipmt]) << ( (ipmt+1) == 16 ? "\n" : ", ") << fixed; 
	    }
	  }
	} //End Fly's Eye Cal PMT Loop

	  //---------Write HMS/SHMS CER Param-------------  
	  //Loop over PMTs
	for (int ipmt = 0; ipmt<4; ipmt++){
	  //Lower Limit Time Window Cut
	  if(lim==0){
	    //HMS Cer
	    if(ipmt<2){
	      out_hcer << Form("%.1f", HMSCER_tMin[ipmt]) << ((ipmt+1) == 2 ? "" : ", ") << fixed;
	    }
	    //SHMS HGCER
	    out_phgcer << Form("%.1f", SHMSHGC_tMin[ipmt]) << ((ipmt+1) == 4 ? "" : ", ") << fixed;
	  }
	 
	  //Upper Limit Time Window Cut
	  if(lim==1){
	    //HMS Cer
	    if(ipmt<2){
	      out_hcer << Form("%.1f", HMSCER_tMax[ipmt]) << ((ipmt+1) == 2 ? "" : ", ") << fixed;
	    }
	    //SHMS HGCER
	    out_phgcer << Form("%.1f", SHMSHGC_tMax[ipmt]) << ((ipmt+1) == 4 ? "" : ", ") << fixed;
	  }
	}
      } // End loop over min/max limits
    } // End loop over sides
  }
}

