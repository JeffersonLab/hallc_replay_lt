#define DetTCuts_HMS_cxx

#include "DetTCuts_HMS.h"
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

void DetTCuts_HMS::Begin(TTree * /*tree*/)
{
  printf("\n\n");
  TString option = GetOption();
}

void DetTCuts_HMS::SlaveBegin(TTree * /*tree*/)
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
	GetOutputList()->Add(h1hHodoAdcTdcTDiff[npl][nside][ipmt]);
      }
    }
  }  
}

Bool_t DetTCuts_HMS::Process(Long64_t entry)
{
  fReader.SetEntry(entry);
  
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
	  if (H_hod_1x_GoodPosAdcMult[ipmt] == 1) h1hHodoAdcTdcTDiff[npl][nside][ipmt]->Fill(H_hod_1x_GoodPosAdcTdcDiffTime[ipmt]);
	}
	else if (npl == 1 && nside == 0){
	  if (H_hod_1y_GoodPosAdcMult[ipmt] == 1) h1hHodoAdcTdcTDiff[npl][nside][ipmt]->Fill(H_hod_1y_GoodPosAdcTdcDiffTime[ipmt]);
	}
	else if (npl == 2 && nside == 0){
	  if (H_hod_2x_GoodPosAdcMult[ipmt] == 1) h1hHodoAdcTdcTDiff[npl][nside][ipmt]->Fill(H_hod_2x_GoodPosAdcTdcDiffTime[ipmt]);
	}  
	else if (npl == 3 && nside == 0){
	  if (H_hod_2y_GoodPosAdcMult[ipmt] == 1) h1hHodoAdcTdcTDiff[npl][nside][ipmt]->Fill(H_hod_2y_GoodPosAdcTdcDiffTime[ipmt]);
	}
	else if (npl == 0 && nside == 1){
	  if (H_hod_1x_GoodNegAdcMult[ipmt] == 1) h1hHodoAdcTdcTDiff[npl][nside][ipmt]->Fill(H_hod_1x_GoodNegAdcTdcDiffTime[ipmt]);
	}
	else if (npl == 1 && nside == 1){
	  if (H_hod_1y_GoodNegAdcMult[ipmt] == 1) h1hHodoAdcTdcTDiff[npl][nside][ipmt]->Fill(H_hod_1y_GoodNegAdcTdcDiffTime[ipmt]);
	}
	else if (npl == 2 && nside == 1){
	  if (H_hod_2x_GoodNegAdcMult[ipmt] == 1) h1hHodoAdcTdcTDiff[npl][nside][ipmt]->Fill(H_hod_2x_GoodNegAdcTdcDiffTime[ipmt]);
	}  
	else if (npl == 3 && nside == 1){
	  if (H_hod_2y_GoodNegAdcMult[ipmt] == 1) h1hHodoAdcTdcTDiff[npl][nside][ipmt]->Fill(H_hod_2y_GoodNegAdcTdcDiffTime[ipmt]);
	} 	
      }
    }
  }
  return kTRUE;
}

void DetTCuts_HMS::SlaveTerminate()
{
}

void DetTCuts_HMS::Terminate()
{
  cout << "Finished processing" << endl;
  printf("\n");
  TString option = GetOption();

  TFile *Histogram_file = new TFile(Form("TimeWindowHistos_HMS_Run%i.root",option.Atoi()),"RECREATE");
  TString outputpdf = Form("TimeWindowPlots_HMS_Run%i.pdf", option.Atoi()) ; 
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
  for (Int_t npl = 0; npl < hod_planes; npl++){ // Loop over all hodoscope planes
    for (Int_t nside = 0; nside < sides; nside++){ //Loop over each side
      CHMSHODO[npl][nside] = new TCanvas(Form("CHMSHODO%s%s", hod_pl_names[npl].c_str(), nsign[nside].c_str()),  Form("HMS Hodoscope %s%s Timing", hod_pl_names[npl].c_str(), nsign[nside].c_str()), 300,100,1000,900);
      CHMSHODO[npl][nside]->Divide(4, 4);
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
      }
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
    }
  }
  CHMSCER->Print(outputpdf+"]");
  
  Histogram_file->Close();

  // Output time windows to some parameter files
  // This code is heavily based on code written by Carlos Yero for a similar analysis script so credit for it goes to him here!

  string n_side[2] = {"Pos", "Neg"};
  string n_side_cal[2] = {"pos", "neg"};
  string n_lim[2] = {"Min", "Max"};
  
  ofstream out_hhodo;
  ofstream out_hcal;
  ofstream out_hdc;   
  ofstream out_hcer; 
  
  //HMS Hodo
  out_hhodo.open(Form("HMS/Hodo/hhodo_tWin_%d.param", option.Atoi()));
  out_hhodo << "; HMS Hodoscope Parameter File Containing TimeWindow Min/Max Cuts " << endl;
  out_hhodo << " " << endl;
  out_hhodo << " " << endl;
  out_hhodo << " " << endl;
  //HMS Cal
  out_hcal.open(Form("HMS/Cal/hcal_tWin_%d.param", option.Atoi()));
  out_hcal << "; HMS Calorimeter Parameter File Containing TimeWindow Min/Max Cuts " << endl;
  out_hcal << " " << endl;
  out_hcal << " " << endl;
  out_hcal << " " << endl;
  //HMS DC
  out_hdc.open(Form("HMS/DC/hdc_tWin_%d.param", option.Atoi()));
  out_hdc << "; HMS DC  Parameter File Containing TimeWindow Min/Max Cuts " << endl;
  out_hdc << " " << endl;
  out_hdc << " " << endl;
  out_hdc << " " << endl;
  //HMS Cer
  out_hcer.open(Form("HMS/Cher/hcer_tWin_%d.param", option.Atoi()));
  out_hcer << "; HMS Cer  Parameter File Containing TimeWindow Min/Max Cuts " << endl;
  out_hcer << " " << endl;
  out_hcer << " " << endl;
  out_hcer << " " << endl;
  for(Int_t iside = 0; iside<2; iside++){
    //Loop over Min/Max Window Limits
    for (Int_t lim = 0; lim<2; lim++){ 
      //Minimum Time Window
      if(lim==0){
	//HMS Hodo
	out_hhodo << "" << endl;
	out_hhodo << "; " << setw(32) << "1x " << setw(19) << "1y " << setw(16) << "2x " << setw(16) << "2y " << endl;
	out_hhodo << Form("hhodo_%sAdcTimeWindow%s = ", n_side[iside].c_str(), n_lim[lim].c_str());
	//HMS Calorimeter
	out_hcal << "" << endl;
	out_hcal << Form("hcal_%s_AdcTimeWindow%s = ", n_side_cal[iside].c_str(), n_lim[lim].c_str());
	if(iside==0){
	  //HMS DC
	  out_hdc << "" << endl;
	  out_hdc << "hdc_tdc_min_win = ";
	  //HMS Cer
	  out_hcer << "" << endl;
	  out_hcer << "hcer_adcTimeWindowMin = ";
	}
      }
      //Maximum Time Window
      if(lim==1){
	//HMS Hodo
	out_hhodo << "" << endl;
	out_hhodo << "; " << setw(32) << "1x " << setw(19) << "1y " << setw(16) << "2x " << setw(16) << "2y " << endl;
	out_hhodo << Form("hhodo_%sAdcTimeWindow%s = ", n_side[iside].c_str(), n_lim[lim].c_str());
	//HMS Calorimeter
	out_hcal << "" << endl;
	out_hcal << Form("hcal_%s_AdcTimeWindow%s = ", n_side_cal[iside].c_str(), n_lim[lim].c_str());	        
	if(iside==0){
	  //HMS DC
	  out_hdc << "" << endl;
	  out_hdc << "hdc_tdc_max_win = ";
	  //HMS Cer
	  out_hcer << "" << endl;
	  out_hcer << "hcer_adcTimeWindowMax = ";
	}
      }

      for(int ipmt = 0; ipmt<21; ipmt++){     
	//--------Write out HMS Hodo Param---------
	if(ipmt<16){
	  if(ipmt==0){   
	    if (lim==0){
	      out_hhodo << setprecision(2) << HMSHODO_tMin[0][iside][ipmt] << ", " << setw(15) << HMSHODO_tMin[1][iside][ipmt] << ", " << setw(15) << HMSHODO_tMin[2][iside][ipmt] << ", " << setw(15) << HMSHODO_tMin[3][iside][ipmt] << fixed << endl; 
	    }
	    if(lim==1){
	      out_hhodo << setprecision(2) << HMSHODO_tMax[0][iside][ipmt] << ", " << setw(15) << HMSHODO_tMax[1][iside][ipmt] << ", " << setw(15) << HMSHODO_tMax[2][iside][ipmt] << ", " << setw(15) << HMSHODO_tMax[3][iside][ipmt] << fixed << endl; 
	    }
	  }
	  else{
	    if(lim==0){
	      out_hhodo << setw(32) << setprecision(2) << HMSHODO_tMin[0][iside][ipmt] << ", " << setw(15) << HMSHODO_tMin[1][iside][ipmt] << ", " << setw(15) << HMSHODO_tMin[2][iside][ipmt] << ", " << setw(15) << HMSHODO_tMin[3][iside][ipmt] << fixed << endl; 
	    }
	    if(lim==1){
	      out_hhodo << setw(32) << setprecision(2) << HMSHODO_tMax[0][iside][ipmt] << ", " << setw(15) << HMSHODO_tMax[1][iside][ipmt] << ", " << setw(15) << HMSHODO_tMax[2][iside][ipmt] << ", " << setw(15) << HMSHODO_tMax[3][iside][ipmt] << fixed << endl; 
	    }   
	  }
	}//end HMS Hodo PMT Loop          
      }
      //-----Write out HMS Calorimeter-------
      for(Int_t layer = 0; layer < 4; layer++){	            
	if(layer < 2 ){
	  if(lim==0){
	    out_hcal << setprecision(2) << HMSCAL_tMin[layer][iside][0]<<","
		     << HMSCAL_tMin[layer][iside][1]<<","
		     << HMSCAL_tMin[layer][iside][2]<<","
		     << HMSCAL_tMin[layer][iside][3]<<","
		     << HMSCAL_tMin[layer][iside][4]<<","
		     << HMSCAL_tMin[layer][iside][5]<<","
		     << HMSCAL_tMin[layer][iside][6]<<","
		     << HMSCAL_tMin[layer][iside][7]<<","
		     << HMSCAL_tMin[layer][iside][8]<<","
		     << HMSCAL_tMin[layer][iside][9]<<","
		     << HMSCAL_tMin[layer][iside][10]<<","
		     << HMSCAL_tMin[layer][iside][11]<<","
		     << HMSCAL_tMin[layer][iside][12]<< fixed << endl;
	  } // end Min Limit
	  if(lim==1){
	    out_hcal << setprecision(2) << HMSCAL_tMax[layer][iside][0]<<","
		     << HMSCAL_tMax[layer][iside][1]<<","
		     << HMSCAL_tMax[layer][iside][2]<<","
		     << HMSCAL_tMax[layer][iside][3]<<","
		     << HMSCAL_tMax[layer][iside][4]<<","
		     << HMSCAL_tMax[layer][iside][5]<<","
		     << HMSCAL_tMax[layer][iside][6]<<","
		     << HMSCAL_tMax[layer][iside][7]<<","
		     << HMSCAL_tMax[layer][iside][8]<<","
		     << HMSCAL_tMax[layer][iside][9]<<","
		     << HMSCAL_tMax[layer][iside][10]<<","
		     << HMSCAL_tMax[layer][iside][11]<<","
		     << HMSCAL_tMax[layer][iside][12]<< fixed << endl;
	  } //end Max Limit
	} //end layer<2 requirement
	else if (layer > 1){
	  if(iside == 0){ // Only do +ve side
	    if(lim==0){
	      out_hcal << setprecision(2) << HMSCAL_tMin[layer][iside][0]<<","
		       << HMSCAL_tMin[layer][iside][1]<<","
		       << HMSCAL_tMin[layer][iside][2]<<","
		       << HMSCAL_tMin[layer][iside][3]<<","
		       << HMSCAL_tMin[layer][iside][4]<<","
		       << HMSCAL_tMin[layer][iside][5]<<","
		       << HMSCAL_tMin[layer][iside][6]<<","
		       << HMSCAL_tMin[layer][iside][7]<<","
		       << HMSCAL_tMin[layer][iside][8]<<","
		       << HMSCAL_tMin[layer][iside][9]<<","
		       << HMSCAL_tMin[layer][iside][10]<<","
		       << HMSCAL_tMin[layer][iside][11]<<","
		       << HMSCAL_tMin[layer][iside][12]<< fixed << endl;
	    } // end Min Limit
	    if(lim==1){
	      out_hcal << setprecision(2) << HMSCAL_tMax[layer][iside][0]<<","
		       << HMSCAL_tMax[layer][iside][1]<<","
		       << HMSCAL_tMax[layer][iside][2]<<","
		       << HMSCAL_tMax[layer][iside][3]<<","
		       << HMSCAL_tMax[layer][iside][4]<<","
		       << HMSCAL_tMax[layer][iside][5]<<","
		       << HMSCAL_tMax[layer][iside][6]<<","
		       << HMSCAL_tMax[layer][iside][7]<<","
		       << HMSCAL_tMax[layer][iside][8]<<","
		       << HMSCAL_tMax[layer][iside][9]<<","
		       << HMSCAL_tMax[layer][iside][10]<<","
		       << HMSCAL_tMax[layer][iside][11]<<","
		       << HMSCAL_tMax[layer][iside][12]<< fixed << endl;
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
	  
      if(iside==0){
	//Loop over DC planes
	for(Int_t i = 0; i < 12; i++){
	  //Lower Limit Time Window Cut
	  if(lim==0){
	    out_hdc << setw(2) << setprecision(2) << HMSDC_tMin[i] << ", " << fixed;
	  }
	  //Upper Limit Time Window Cut
	  if(lim==1){
	    out_hdc << setw(2) << setprecision(2) << HMSDC_tMax[i] << ", " << fixed;
	  }
	} //End loop over DC Planes
		
	  //---------Write HMS/SHMS CER Param-------------  
	  //Loop over PMTs
	for (int ipmt = 0; ipmt<4; ipmt++){
	  //Lower Limit Time Window Cut
	  if(lim==0){
	    //HMS Cer
	    if(ipmt<2){
	      out_hcer << setprecision(2) << HMSCER_tMin[ipmt] << ", " << fixed;
	    }
	  }
	 
	  //Upper Limit Time Window Cut
	  if(lim==1){
	    //HMS Cer
	    if(ipmt<2){
	      out_hcer << setprecision(2) << HMSCER_tMax[ipmt] << ", " << fixed;
	    }
	  }
	}
      } // End loop over min/max limits
    } // End loop over sides
  }
}

