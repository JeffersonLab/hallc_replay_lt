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
  TDirectory *DHMS = Histogram_file->mkdir("HMS Ref Time Histos"); DHMS->cd();
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

  TDirectory *DSHMS = Histogram_file->mkdir("SHMS Ref Time Histos"); DSHMS->cd();
  h1PHGCRefTime->Write("SHMS HGC RefTime");
  for (Int_t i = 0; i < 12; i++){ 
    TH1F *SHMSDCRT = dynamic_cast<TH1F *>(TProof::GetOutput(Form("PDC%s_RefTime", dc_pl_names[i].c_str()), fOutput));
    SHMSDCRT->Write(Form("SHMS DC %s RefTime", dc_pl_names[i].c_str()));
  }
  for (Int_t i = 0; i < 4; i++){ // Loop over planes
    for (Int_t j = 0; j < 2; j++){ // Loop over ends
      for (Int_t k = 0; k < 2; k++){ // Loop over digitiser
	TH1F *SHMSHODORT = dynamic_cast<TH1F *>(TProof::GetOutput(Form("PHod%s%s%s_RefTime", hod_pl_names[i].c_str(), hod_side[j].c_str(), hod_digi[k].c_str()), fOutput));
	SHMSHODORT->Write(Form("SHMS Hodo %s %s %s RefTime", hod_pl_names[i].c_str(), hod_side[j].c_str(), hod_digi[k].c_str()));
      }
    }
  }

  Histogram_file->Close();

}
