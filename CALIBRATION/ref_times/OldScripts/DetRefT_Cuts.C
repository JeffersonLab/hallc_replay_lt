// Stephen Kay - University of Regina - 25/06/20 // 

#define DetRefT_Cuts_cxx

#include "DetRefT_Cuts.h"
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

void DetRefT_Cuts::Begin(TTree * /*tree*/)
{
  printf("\n\n");
  TString option = GetOption();
}

void DetRefT_Cuts::SlaveBegin(TTree * /*tree*/)
{
  printf("\n\n");
  TString option = GetOption();
  
  h1HCerRefTime = new TH1F("HCerRefTime", "HMS Cherenkov RefTime Dist; RefTime/ns", 1000, 0, 20000);
  h1PHGCRefTime = new TH1F("PHGCRefTime", "SHMS HGC RefTime Dist; RefTime/ns", 1000, 0, 20000);
  GetOutputList()->Add(h1HCerRefTime);
  GetOutputList()->Add(h1PHGCRefTime);
  for (Int_t i = 0; i < 12; i++){ 
    h1HDCRefTime[i] = new TH1F(Form("HDC%s_RefTime", dc_pl_names[i].c_str()), Form("HMS DC Plane %s Ref Time; RefTime/ns", dc_pl_names[i].c_str()), 1000, 0, 20000);
    h1PDCRefTime[i] = new TH1F(Form("PDC%s_RefTime", dc_pl_names[i].c_str()), Form("SHMS DC Plane %s Ref Time; RefTime/ns", dc_pl_names[i].c_str()), 1000, 0, 20000);
    GetOutputList()->Add(h1HDCRefTime[i]);
    GetOutputList()->Add(h1PDCRefTime[i]);
  }

  for (Int_t i = 0; i < 4; i++){ // Loop over planes
    for (Int_t j = 0; j < 2; j++){ // Loop over ends
      for (Int_t k = 0; k < 2; k++){ // Loop over digitiser
	h1HHodRefTime[i][j][k] = new TH1F(Form("HHod%s%s%s_RefTime", hod_pl_names[i].c_str(), hod_side[j].c_str(), hod_digi[k].c_str()), Form("HMS Hodo Plane %s %s %s Ref Time; RefTime/ns", hod_pl_names[i].c_str(), hod_side[j].c_str(), hod_digi[k].c_str()), 1000, 0, 20000);
	h1PHodRefTime[i][j][k] = new TH1F(Form("PHod%s%s%s_RefTime", hod_pl_names[i].c_str(), hod_side[j].c_str(), hod_digi[k].c_str()), Form("SHMS Hodo Plane %s %s %s Ref Time; RefTime/ns", hod_pl_names[i].c_str(), hod_side[j].c_str(), hod_digi[k].c_str()), 1000, 0, 20000);
	GetOutputList()->Add(h1HHodRefTime[i][j][k]);
	GetOutputList()->Add(h1PHodRefTime[i][j][k]);
      }
    }
  }

  for (Int_t i = 0; i < 4; i++){ // Loop over planes
    for (Int_t j = 0; j < 2; j++){ // Loop over ends
      h1HHodADCTDCDiffTime[i][j] = new TH1F(Form("HHod_%s_%s_GoodAdcTdcDiffTime", hod_pl_names[i].c_str(),hod_side[j].c_str()), Form("HMS Hodo Plane %s %s AdcTdcDiffTime", hod_pl_names[i].c_str(),hod_side[j].c_str()), 200, -100, 100);
      h1PHodADCTDCDiffTime[i][j] = new TH1F(Form("PHod_%s_%s_GoodAdcTdcDiffTime", hod_pl_names[i].c_str(),hod_side[j].c_str()), Form("SHMS Hodo Plane %s %s AdcTdcDiffTime", hod_pl_names[i].c_str(),hod_side[j].c_str()), 200, -100, 100);
      GetOutputList()->Add(h1HHodADCTDCDiffTime[i][j]);
      GetOutputList()->Add(h1PHodADCTDCDiffTime[i][j]);
    }
  }

}

Bool_t DetRefT_Cuts::Process(Long64_t entry)
{
  fReader.SetEntry(entry);

  h1HCerRefTime->Fill(H_cer_RefTime[0]);
  h1PHGCRefTime->Fill(P_hgcer_RefTime[0]);

  for(Int_t i = 0; i < 12; i++){
    if (i == 0){
      h1HDCRefTime[i]->Fill(H_dc_1u1_RefTime[0]);
      h1PDCRefTime[i]->Fill(P_dc_1u1_RefTime[0]);
    }
    if (i == 1){
      h1HDCRefTime[i]->Fill(H_dc_1u2_RefTime[0]);
      h1PDCRefTime[i]->Fill(P_dc_1u2_RefTime[0]);
    }
    if (i == 2){
      h1HDCRefTime[i]->Fill(H_dc_1x1_RefTime[0]);
      h1PDCRefTime[i]->Fill(P_dc_1x1_RefTime[0]);
    }
    if (i == 3){
      h1HDCRefTime[i]->Fill(H_dc_1x2_RefTime[0]);
      h1PDCRefTime[i]->Fill(P_dc_1x2_RefTime[0]);
    }
    if (i == 4){
      h1HDCRefTime[i]->Fill(H_dc_1v1_RefTime[0]);
      h1PDCRefTime[i]->Fill(P_dc_1v1_RefTime[0]);
    }
    if (i == 5){
      h1HDCRefTime[i]->Fill(H_dc_1v2_RefTime[0]);
      h1PDCRefTime[i]->Fill(P_dc_1v2_RefTime[0]);
    }
    if (i == 6){
      h1HDCRefTime[i]->Fill(H_dc_2u1_RefTime[0]);
      h1PDCRefTime[i]->Fill(P_dc_2u1_RefTime[0]);
    }
    if (i == 7){
      h1HDCRefTime[i]->Fill(H_dc_2u2_RefTime[0]);
      h1PDCRefTime[i]->Fill(P_dc_2u2_RefTime[0]);
    }
    if (i == 8){
      h1HDCRefTime[i]->Fill(H_dc_2x1_RefTime[0]);
      h1PDCRefTime[i]->Fill(P_dc_2x1_RefTime[0]);
    }
    if (i == 9){
      h1HDCRefTime[i]->Fill(H_dc_2x2_RefTime[0]);
      h1PDCRefTime[i]->Fill(P_dc_2x2_RefTime[0]);
    }
    if (i == 10){
      h1HDCRefTime[i]->Fill(H_dc_2v1_RefTime[0]);
      h1PDCRefTime[i]->Fill(P_dc_2v1_RefTime[0]);
    }
    if (i == 11){
      h1HDCRefTime[i]->Fill(H_dc_2v2_RefTime[0]);
      h1PDCRefTime[i]->Fill(P_dc_2v2_RefTime[0]);
    }
  }

  for (Int_t i = 0; i < 4; i++){ // Loop over planes
    for (Int_t j = 0; j < 2; j++){ // Loop over ends
      for (Int_t k = 0; k < 2; k++){ // Loop over digitiser
	if (i == 0 && j == 0){
	  h1HHodADCTDCDiffTime[i][j]->Fill(H_hod_1x_NegAdcTdcDiffTime[0]);
	  h1PHodADCTDCDiffTime[i][j]->Fill(P_hod_1x_NegAdcTdcDiffTime[0]);
	  if (k == 0){
	    h1HHodRefTime[i][j][k]->Fill(H_hod_1x_NegAdcRefTime[0]);
	    h1PHodRefTime[i][j][k]->Fill(P_hod_1x_NegAdcRefTime[0]);
	  }
	  else if (k == 1){
	    h1HHodRefTime[i][j][k]->Fill(H_hod_1x_NegTdcRefTime[0]);
	    h1PHodRefTime[i][j][k]->Fill(P_hod_1x_NegTdcRefTime[0]);
	  }
	}
	else if (i == 0 && j == 1){
	  h1HHodADCTDCDiffTime[i][j]->Fill(H_hod_1x_PosAdcTdcDiffTime[0]);
	  h1PHodADCTDCDiffTime[i][j]->Fill(P_hod_1x_PosAdcTdcDiffTime[0]);
	  if (k == 0){
	    h1HHodRefTime[i][j][k]->Fill(H_hod_1x_PosAdcRefTime[0]);
	    h1PHodRefTime[i][j][k]->Fill(P_hod_1x_PosAdcRefTime[0]);
	  }
	  else if (k == 1){
	    h1HHodRefTime[i][j][k]->Fill(H_hod_1x_PosTdcRefTime[0]);
	    h1PHodRefTime[i][j][k]->Fill(P_hod_1x_PosTdcRefTime[0]);
	  }
	}
      
	else if (i == 1 && j == 0){
	  h1HHodADCTDCDiffTime[i][j]->Fill(H_hod_1y_NegAdcTdcDiffTime[0]);
	  h1PHodADCTDCDiffTime[i][j]->Fill(P_hod_1y_NegAdcTdcDiffTime[0]);
	  if (k == 0){
	    h1HHodRefTime[i][j][k]->Fill(H_hod_1y_NegAdcRefTime[0]);
	    h1PHodRefTime[i][j][k]->Fill(P_hod_1y_NegAdcRefTime[0]);
	  }
	  else if (k == 1){
	    h1HHodRefTime[i][j][k]->Fill(H_hod_1y_NegTdcRefTime[0]);
	    h1PHodRefTime[i][j][k]->Fill(P_hod_1y_NegTdcRefTime[0]);
	  }
	}
	else if (i == 1 && j == 1){
	  h1HHodADCTDCDiffTime[i][j]->Fill(H_hod_1y_PosAdcTdcDiffTime[0]);
	  h1PHodADCTDCDiffTime[i][j]->Fill(P_hod_1y_PosAdcTdcDiffTime[0]);
	  if (k == 0){
	    h1HHodRefTime[i][j][k]->Fill(H_hod_1y_PosAdcRefTime[0]);
	    h1PHodRefTime[i][j][k]->Fill(P_hod_1y_PosAdcRefTime[0]);
	  }
	  else if (k == 1){
	    h1HHodRefTime[i][j][k]->Fill(H_hod_1y_PosTdcRefTime[0]);
	    h1PHodRefTime[i][j][k]->Fill(P_hod_1y_PosTdcRefTime[0]);
	  }
	}
      
	else if (i == 2 && j == 0){
	  h1HHodADCTDCDiffTime[i][j]->Fill(H_hod_2x_NegAdcTdcDiffTime[0]);
	  h1PHodADCTDCDiffTime[i][j]->Fill(P_hod_2x_NegAdcTdcDiffTime[0]);
	   if (k == 0){
	    h1HHodRefTime[i][j][k]->Fill(H_hod_2x_NegAdcRefTime[0]);
	    h1PHodRefTime[i][j][k]->Fill(P_hod_2x_NegAdcRefTime[0]);
	  }
	  else if (k == 1){
	    h1HHodRefTime[i][j][k]->Fill(H_hod_2x_NegTdcRefTime[0]);
	    h1PHodRefTime[i][j][k]->Fill(P_hod_2x_NegTdcRefTime[0]);
	  }
	}
	else if (i == 2 && j == 1){
	  h1HHodADCTDCDiffTime[i][j]->Fill(H_hod_2x_PosAdcTdcDiffTime[0]);
	  h1PHodADCTDCDiffTime[i][j]->Fill(P_hod_2x_PosAdcTdcDiffTime[0]);
	  if (k == 0){
	    h1HHodRefTime[i][j][k]->Fill(H_hod_2x_PosAdcRefTime[0]);
	    h1PHodRefTime[i][j][k]->Fill(P_hod_2x_PosAdcRefTime[0]);
	  }
	  else if (k == 1){
	    h1HHodRefTime[i][j][k]->Fill(H_hod_2x_PosTdcRefTime[0]);
	    h1PHodRefTime[i][j][k]->Fill(P_hod_2x_PosTdcRefTime[0]);
	  }
	}

	else if (i == 3 && j == 0){
	  h1HHodADCTDCDiffTime[i][j]->Fill(H_hod_2y_NegAdcTdcDiffTime[0]);
	  h1PHodADCTDCDiffTime[i][j]->Fill(P_hod_2y_NegAdcTdcDiffTime[2]);
	  if (k == 0){
	    h1HHodRefTime[i][j][k]->Fill(H_hod_2y_NegAdcRefTime[0]);
	    h1PHodRefTime[i][j][k]->Fill(P_hod_2y_NegAdcRefTime[0]);
	  }
	  else if (k == 1){
	    h1HHodRefTime[i][j][k]->Fill(H_hod_2y_NegTdcRefTime[0]);
	    h1PHodRefTime[i][j][k]->Fill(P_hod_2y_NegTdcRefTime[0]);
	  }
	}
	else if (i == 3 && j == 1){
	  h1HHodADCTDCDiffTime[i][j]->Fill(H_hod_2y_PosAdcTdcDiffTime[0]);
	  h1PHodADCTDCDiffTime[i][j]->Fill(P_hod_2y_PosAdcTdcDiffTime[2]);
	  if (k == 0){
	    h1HHodRefTime[i][j][k]->Fill(H_hod_2y_PosAdcRefTime[0]);
	    h1PHodRefTime[i][j][k]->Fill(P_hod_2y_PosAdcRefTime[0]);
	  }
	  else if (k == 1){
	    h1HHodRefTime[i][j][k]->Fill(H_hod_2y_PosTdcRefTime[0]);
	    h1PHodRefTime[i][j][k]->Fill(P_hod_2y_PosTdcRefTime[0]);
	  }
	}

      }
    }
  } // Close of loop over hodoscope filling
  return kTRUE;
}

void DetRefT_Cuts::SlaveTerminate()
{
}

void DetRefT_Cuts::Terminate()
{
  cout << "Finished processing" << endl;
  printf("\n");
  TString option = GetOption();

  TFile *Histogram_file = new TFile(Form("RefTimeHistos_Run%i.root",option.Atoi()),"RECREATE");
  TDirectory *DHMSRT = Histogram_file->mkdir("HMS Ref Time Histos"); DHMSRT->cd();
  h1HCerRefTime->Write("HMS Cherenkov RefTime");
  for (Int_t i = 0; i < 12; i++){ 
    TH1F *HMSDCRT = dynamic_cast<TH1F *>(TProof::GetOutput(Form("HDC%s_RefTime", dc_pl_names[i].c_str()), fOutput));
    HMSDCRT->Write(Form("HMS DC %s RefTime", dc_pl_names[i].c_str()));
  }
  for (Int_t i = 0; i < 4; i++){ // Loop over planes
    for (Int_t j = 0; j < 2; j++){ // Loop over ends
      for (Int_t k = 0; k < 2; k++){ // Loop over digitiser
	TH1F *HMSHODORT = dynamic_cast<TH1F *>(TProof::GetOutput(Form("HHod%s%s%s_RefTime", hod_pl_names[i].c_str(), hod_side[j].c_str(), hod_digi[k].c_str()), fOutput));
	HMSHODORT->Write(Form("HMS Hodo %s %s %s RefTime", hod_pl_names[i].c_str(), hod_side[j].c_str(), hod_digi[k].c_str()));
      }
    }
  }
  TDirectory *DSHMSRT = Histogram_file->mkdir("SHMS Ref Time Histos"); DSHMSRT->cd();
  h1PHGCRefTime->Write("SHMS HGC RefTime");
  for (Int_t i = 0; i < 12; i++){ 
    TH1F *SHMSDCRT = dynamic_cast<TH1F *>(TProof::GetOutput(Form("PDC%s_RefTime", dc_pl_names[i].c_str()), fOutput));
    SHMSDCRT->Write(Form("SHMS DC %s RefTime", dc_pl_names[i].c_str()));
  }
  for (Int_t i = 0; i < 4; i++){ // Loop over planes
    for (Int_t j = 0; j < 2; j++){ // Loop over ends
      TH1F *SHMSHODODIFF = dynamic_cast<TH1F *>(TProof::GetOutput(Form("PHod_%s_%s_GoodAdcTdcDiffTime", hod_pl_names[i].c_str(), hod_side[j].c_str()), fOutput));
      SHMSHODODIFF->Write(Form("SHMS Hodo %s %s ADCTDCDiffTime", hod_pl_names[i].c_str(), hod_side[j].c_str()));
      for (Int_t k = 0; k < 2; k++){ // Loop over digitiser
	TH1F *SHMSHODORT = dynamic_cast<TH1F *>(TProof::GetOutput(Form("PHod%s%s%s_RefTime", hod_pl_names[i].c_str(), hod_side[j].c_str(), hod_digi[k].c_str()), fOutput));
	SHMSHODORT->Write(Form("SHMS Hodo %s %s %s RefTime", hod_pl_names[i].c_str(), hod_side[j].c_str(), hod_digi[k].c_str()));
      }
    }
  }

  TDirectory *DHMSDiff = Histogram_file->mkdir("HMS ADCTDCDiff Histos"); DHMSDiff->cd();
  for (Int_t i = 0; i < 4; i++){ // Loop over planes
    for (Int_t j = 0; j < 2; j++){ // Loop over ends
      TH1F *HMSHODODIFF = dynamic_cast<TH1F *>(TProof::GetOutput(Form("HHod_%s_%s_GoodAdcTdcDiffTime", hod_pl_names[i].c_str(), hod_side[j].c_str()), fOutput));
      HMS_Hodo_Offset_Raw[i][j] = (HMSHODODIFF->GetMean());
      HMS_Hodo_OffsetErr_Raw[i][j] = (HMSHODODIFF->GetMeanError());
      HMSHODODIFF->Write(Form("HMS Hodo %s %s ADCTDCDiffTime", hod_pl_names[i].c_str(), hod_side[j].c_str()));
    }
  }

  TDirectory *DSHMSDiff = Histogram_file->mkdir("SHMS ADCTDCDiff Histos"); DSHMSDiff->cd();
  for (Int_t i = 0; i < 4; i++){ // Loop over planes
    for (Int_t j = 0; j < 2; j++){ // Loop over ends
      TH1F *SHMSHODODIFF = dynamic_cast<TH1F *>(TProof::GetOutput(Form("PHod_%s_%s_GoodAdcTdcDiffTime", hod_pl_names[i].c_str(), hod_side[j].c_str()), fOutput));
      SHMS_Hodo_Offset_Raw[i][j] = (SHMSHODODIFF->GetMean());
      SHMS_Hodo_OffsetErr_Raw[i][j] = (SHMSHODODIFF->GetMeanError());
      SHMSHODODIFF->Write(Form("SHMS Hodo %s %s ADCTDCDiffTime", hod_pl_names[i].c_str(), hod_side[j].c_str()));
    }
  }

  Histogram_file->Close();

  for (Int_t i = 0; i < 4; i++){ // Loop over planes
    // Calculated weighted average of +ve/-ve for each plane to determine offset
    HMSWeightSum1[i]=0;
    HMSWeightSum2[i]=0;
    if(HMS_Hodo_OffsetErr_Raw[i][0] == 0 || HMS_Hodo_OffsetErr_Raw[i][1] == 0) continue;
    for (Int_t j = 0; j < 2; j++){
      HMSWeightSum1[i]+=(HMS_Hodo_Offset_Raw[i][j])/(HMS_Hodo_OffsetErr_Raw[i][j]*HMS_Hodo_OffsetErr_Raw[i][j]);
      HMSWeightSum2[i]+=1/(HMS_Hodo_OffsetErr_Raw[i][j]*HMS_Hodo_OffsetErr_Raw[i][j]);
    }
    if(HMSWeightSum2[i] != 0){
      HMS_Hodo_Offset[i] = 200 + (HMSWeightSum1[i]/HMSWeightSum2[i]);
    }
    else{
      HMS_Hodo_Offset[i] = 200;
    }
  }

  for (Int_t i = 0; i < 4; i++){ // Loop over planes
    // Calculated weighted average of +ve/-ve for each plane to determine offset
    SHMSWeightSum1[i]=0;
    SHMSWeightSum2[i]=0;
    if(SHMS_Hodo_OffsetErr_Raw[i][0] == 0 || SHMS_Hodo_OffsetErr_Raw[i][1] == 0) continue;
    for (Int_t j = 0; j < 2; j++){
      SHMSWeightSum1[i]+=(SHMS_Hodo_Offset_Raw[i][j])/(SHMS_Hodo_OffsetErr_Raw[i][j]*SHMS_Hodo_OffsetErr_Raw[i][j]);
      SHMSWeightSum2[i]+=1/(SHMS_Hodo_OffsetErr_Raw[i][j]*SHMS_Hodo_OffsetErr_Raw[i][j]);
    }
    if(SHMSWeightSum2[i] != 0){
      SHMS_Hodo_Offset[i] = 200 + (SHMSWeightSum1[i]/SHMSWeightSum2[i]);
    }
    else{
      SHMS_Hodo_Offset[i] = 200;
    }
  }

  ofstream out_hhodo;
  ofstream out_phodo;
  // HMS Hodo
  out_hhodo.open(Form("HMS_Hodo_AdcTdc_Offset_%d.param", option.Atoi()));
  out_hhodo << "; HMS Hodoscope AdcTdc Offset times" << endl;
  out_hhodo << "hhodo_adc_tdc_offset = ";
  for (Int_t i = 0; i < 4; i++){ // Loop over planes
    if(i != 3){
      out_hhodo << Form("%.0f", HMS_Hodo_Offset[i]) << "., ";
    }
    else{
      out_hhodo << Form("%.0f", HMS_Hodo_Offset[i]) << "." << endl;
    }
  }
  
  // SHMS Hodo
  out_phodo.open(Form("SHMS_Hodo_AdcTdc_Offset_%d.param", option.Atoi()));
  out_phodo << "; SHMS Hodoscope AdcTdc Offset times" << endl;
  out_phodo << "phodo_adc_tdc_offset = ";
  for (Int_t i = 0; i < 4; i++){ // Loop over planes
    if(i != 3){
      out_phodo << Form("%.0f", SHMS_Hodo_Offset[i]) << "., ";
    }
    else{
      out_phodo << Form("%.0f", SHMS_Hodo_Offset[i]) << "." << endl;
    }
  }

}
