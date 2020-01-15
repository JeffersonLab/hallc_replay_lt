#define ProtonYield_cxx

#include "ProtonYield.h"
#include <TStyle.h>
#include <TCanvas.h>
#include <TLine.h>
#include <TMath.h>
#include <TPaveText.h>
#include <TGaxis.h>

void ProtonYield::Begin(TTree * /*tree*/)
{  
  TString option = GetOption();
}

void ProtonYield::SlaveBegin(TTree * /*tree*/)
{
  TString option = GetOption();

  h2missKcut_CT   = new TH2F("h1missKcut_CT","Kaon Missing mass vs Coincidence Time;Time (ns);Mass (GeV/c^{2})^{2}",400,-10,10,200,0.8,1.5);
  h2misspicut_CT   = new TH2F("h1misspicut_CT","Pion Missing mass vs Coincidence Time;Time (ns);Mass (GeV/c^{2})^{2}",400,-10,10,200,0.8,1.5);
  h2misspcut_CT   = new TH2F("h1misspcut_CT","Proton Missing mass vs Coincidence Time;Time (ns);Mass (GeV/c^{2})^{2}",400,-10,10,200,0.8,1.5);

  h2HGCXYAll = new TH2F("h2HGCXYAll", "X vs Y Position in HGC; X Dimension (cm);Y Dimension (cm)", 100, -50, 50, 100, -50, 50);
  h2HGCXYPion = new TH2F("h2HGCXYPion", "X vs Y for Pions Position in HGC; X Dimension (cm);Y Dimension (cm)", 100, -50, 50, 100, -50, 50);
  h2HGCXYKaon = new TH2F("h2HGCXYKaon", "X vs Y for Kaons Position in HGC; X Dimension (cm);Y Dimension (cm)", 100, -50, 50, 100, -50, 50);
  h2HGCXYProton = new TH2F("h2HGCXYProton", "X vs Y for Protons Position in HGC; X Dimension (cm);Y Dimension (cm)", 100, -50, 50, 100, -50, 50);

  h3XYNPEAll = new TH3F("h3XYNPEAll","NPE Sum vs X vs Y;X Dimension (cm);Y Dimension (cm);NPE",100,-50,50,100,-50,50,100,0.0,50);
  h3XYNPEPion = new TH3F("h3XYNPEPion","NPE Sum vs X vs Y for Pions;X Dimension (cm);Y Dimension (cm);NPE",100,-50,50,100,-50,50,100,0.0,50);
  h3XYNPEKaon = new TH3F("h3XYNPEKaon","NPE Sum vs X vs Y for Kaons;X Dimension (cm);Y Dimension (cm);NPE",100,-50,50,100,-50,50,100,0.0,50);
  h3XYNPEProton = new TH3F("h3XYNPEProton","NPE Sum vs X vs Y for Protons;X Dimension (cm);Y Dimension (cm);NPE",100,-50,50,100,-50,50,100,0.0,50);
  
  // Timing Windows, may change to be some 2D array
  h2ROC1_Coin_Beta_noID_kaon = new TH2F("ROC1_Coin_Beta_noCut_kaon","Kaon Coincident Time vs #beta for ROC1 (w/ particle ID);Time (ns);#beta",800,-40,40,200,0.0,2.0);
  h2ROC1_Coin_Beta_kaon = new TH2F("ROC1_Coin_Beta_kaon","Kaon Coincident Time vs #beta for ROC1;Time (ns);#beta",800,-40,40,200,0.0,2.0);
  h2ROC1_Coin_Beta_randID_kaon = new TH2F("ROC1_Coin_Beta_randID_kaon","Random Kaon Coincident Time vs #beta for ROC1;Time (ns);#beta",800,-40,40,200,0.0,2.0);
  h2ROC1_Coin_Beta_noID_pion = new TH2F("ROC1_Coin_Beta_noCut_pion","Pion Coincident Time vs #beta for ROC1 (w/ particle ID);Time (ns);#beta",400,-20,20,100,0.0,2.0);
  h2ROC1_Coin_Beta_pion = new TH2F("ROC1_Coin_Beta_pion","Pion Coincident Time vs #beta for ROC1;Time (ns);#beta",400,-20,20,100,0.0,2.0);
  h2ROC1_Coin_Beta_randID_pion = new TH2F("ROC1_Coin_Beta_randID_pion","Random Pion Coincident Time vs #beta for ROC1;Time (ns);#beta",800,-40,40,200,0.0,2.0);
  h2ROC1_Coin_Beta_noID_proton = new TH2F("ROC1_Coin_Beta_noCut_proton","Proton Coincident Time vs #beta for ROC1 (w/ particle ID);Time (ns);#beta",800,-40,40,200,0.0,2.0);
  h2ROC1_Coin_Beta_proton = new TH2F("ROC1_Coin_Beta_proton","Proton Coincident Time vs #beta for ROC1;Time (ns);#beta",800,-40,40,200,0.0,2.0);
  h2ROC1_Coin_Beta_randID_proton = new TH2F("ROC1_Coin_Beta_randID_proton","Random Proton Coincident Time vs #beta for ROC1;Time (ns);#beta",800,-40,40,200,0.0,2.0);
  
  h2HMS_electron        = new TH2F("HMS_electron","Normalized HMS Calorimeter Energy vs Cherenkov;Normalized Energy;CER NPE",200,0.01,1.5,60,0.1,30);
  h2HMS_electron_cut    = new TH2F("HMS_electron_cut","Normalized HMS Calorimeter Energy vs Cherenkov, Electrons Selected;Normalized Energy;CER NPE",200,0.01,1.5,60,0.0,30);

  h1SHMS_electron        = new TH1F("SHMS_electron","Normalized SHMS Calorimeter Energy;Normalized Energy;Counts",200,0.01,1.5);
  h1SHMS_electron_cut    = new TH1F("SHMS_electron_cut","Normalized SHMS Calorimeter Energy, Electrons Removed;Normalized Energy;Counts",200,0.01,1.5);

  h2SHMS_AERO_HGC         = new TH2F("SHMS_AERO_HGC","NPE in SHMS Aerogel and Heavy Gas;Aerogel NPE;HGC NPE",50,0.1,25,50,0.1,30);
  h2SHMS_CAL_HGC         = new TH2F("SHMS_CAL_HGC","Normalized SHMS Calorimeter Energy and NPE in Heavy Gas;Normalized Energy;HGC NPE",50,0.1,2.0,50,-1,30);

  h2SHMSK_kaon_cut        = new TH2F("SHMSK_kaon_cut","NPE in SHMS Aerogel and Heavy Gas, Kaons Selected;Aerogel NPE;HGC NPE",50,0.0,25,50,0.0,10);
  h2SHMSK_pion_cut        = new TH2F("SHMSK_pion_cut","Normalized SHMS Calorimeter Energy and NPE in Heavy Gas, Kaons Selected;Normalized Energy;HGC NPE",50,0.0,2.0,50,-1.0,30);

  h2SHMSpi_kaon_cut        = new TH2F("SHMSpi_kaon_cut","NPE in SHMS Aerogel and Heavy Gas, Pions Selected;Aerogel NPE;HGC NPE",50,0.0,25,150,0.0,30);
  h2SHMSpi_pion_cut        = new TH2F("SHMSpi_pion_cut","Normalized SHMS Calorimeter Energy and NPE in Heavy Gas, Pions Selected;Normalized Energy;HGC NPE",50,0.0,2.0,50,-1.0,30);

  h2SHMSp_kaon_cut        = new TH2F("SHMSp_kaon_cut","NPE in SHMS Aerogel and Heavy Gas, Protons Selected; Aerogel NPE;HGC NPE",50,0.0,25,50,0.0,10);
  h2SHMSp_pion_cut        = new TH2F("SHMSp_pion_cut","Normalized SHMS Calorimeter Energy and NPE in Heavy Gas, Protons Selected;Normalized Energy;HGC NPE",50,0.0,2.0,50,0.0,30);

  h1SHMS_delta           = new TH1F("SHMS_delta","SHMS #delta;#delta;Counts",100,-50,50);
  h1SHMS_delta_cut       = new TH1F("SHMS_delta_cut","SHMS #delta Cut;#delta;Counts",100,-50,50);
  h1HMS_delta            = new TH1F("HMS_delta","HMS #delta;#delta;Counts",100,-50,50);
  h1HMS_delta_cut        = new TH1F("HMS_delta_cut","HMS #delta Cut;#delta;Counts",100,-50,50);

  h1SHMS_th              = new TH1F("SHMS_th","SHMS #theta Acceptance;#theta;Counts",100,-0.1,0.1);
  h1SHMS_th_cut          = new TH1F("SHMS_th_cut","SHMS #theta Acceptance with Cut;#theta;Counts",100,-0.1,0.1);
  h1SHMS_ph              = new TH1F("SHMS_ph","SHMS #phi Acceptance;#phi;Counts",100,-0.1,0.1);
  h1SHMS_ph_cut          = new TH1F("SHMS_ph_cut","SHMS #phi Acceptance with Cut;#phi;Counts",100,-0.1,0.1);

  h1HMS_th              = new TH1F("HMS_th","HMS #theta Acceptance;#theta;Counts",100,-0.1,0.1);
  h1HMS_th_cut          = new TH1F("HMS_th_cut","HMS #theta Acceptance with Cut;#theta;Counts",100,-0.1,0.1);
  h1HMS_ph              = new TH1F("HMS_ph","HMS #phi Acceptance;#phi;Counts",100,-0.1,0.1);
  h1HMS_ph_cut          = new TH1F("HMS_ph_cut","HMS #phi Acceptance with Cut;#phi;Counts",100,-0.1,0.1);

  h1mmissK                = new TH1F("mmissK","Kaon Missing mass;Mass (GeV/c^{2});Counts",200,0.8,2.0);
  h1mmissK_rand           = new TH1F("mmissK_rand","Kaon Missing mass from Random Coincidence;Mass (GeV/c^{2});Counts",200,0.8,1.8);
  h1mmissK_cut            = new TH1F("mmissK_cut","Kaon Missing mass with Cuts;Mass (GeV/c^{2});Counts",200,0.8,1.8);
  h1mmissK_remove         = new TH1F("mmissK_remove","Kaon Missing mass with Cuts (Random Subtracted);Mass (GeV/c^{2});Counts",200,0.8,1.8);

  h1mmisspi               = new TH1F("mmisspi","Pion Missing mass;Mass (GeV/c^{2});Counts",200,0.8,1.2);
  h1mmisspi_rand          = new TH1F("mmisspi_rand","Pion Missing mass from Random Coincidence;Mass (GeV/c^{2});Counts",200,0.8,1.2);
  h1mmisspi_cut           = new TH1F("mmisspi_cut","Pion Missing mass with Cuts;Mass (GeV/c^{2});Counts",200,0.8,1.2);
  h1mmisspi_remove        = new TH1F("mmisspi_remove","Pion Missing mass with Cuts (Random Subtracted);Mass (GeV/c^{2});Counts",200,0.8,1.2);

  h1mmissp                = new TH1F("mmissp","Proton Missing mass;Mass (GeV/c^{2});Counts",200,0.0,2.0);
  h1mmissp_rand           = new TH1F("mmissp_rand","Proton Missing mass from Random Coincidence;Mass (GeV/c^{2});Counts",200,0.0,2.0);
  h1mmissp_cut            = new TH1F("mmissp_cut","Proton Missing mass with Cuts;Mass (GeV/c^{2});Counts",200,0.0,2.0);
  h1mmissp_remove         = new TH1F("mmissp_remove","Proton Missing mass with Cuts (Random Subtracted);Mass (GeV/c^{2});Counts",200,0.0,2.0);

  h2WvsQ2                 = new TH2F("WvsQ2","Q2 vs W;Q2;W", 200, 5.0, 6.0, 200, 2.8, 3.8);
  h2uvsph_q               = new TH2F("uvsph_q",";#phi;u",12,-3.14,3.14,100,0.0,1.5); 
  h1epsilon               = new TH1F("epsilon","Plot of Epsilon;#epsilon;Counts",100,0.0,1.0);

  h1mmpKMissID             = new TH1F("mmpKMissID","MM_{p} - K Wrong PID;Mass (GeV/c^{2});Counts",200,0.0,2.0);
  h1mmKpMissID             = new TH1F("mmKpMissID","MM_{K} - p Wrong PID;Mass (GeV/c^{2});Counts",200,0.0,2.0);
  h2HGCXYKMissID            = new TH2F("h2HGCXYKMissID", "X vs Y for K wrong PID in HGC; X Dimension (cm);Y Dimension (cm)", 100, -50, 50, 100, -50, 50);
  h2HGCXYpMissID           = new TH2F("h2HGCXYpMissID", "X vs Y for p wrong PID in HGC; X Dimension (cm);Y Dimension (cm)", 100, -50, 50, 100, -50, 50);  
  h3XYNPEKMissID           = new TH3F("h3XYNPEKMissID","NPE Sum vs X vs Y for K wrong PID;X Dimension (cm);Y Dimension (cm);NPE",100,-50,50,100,-50,50,100,0.0,50);
  h3XYNPEpMissID           = new TH3F("h3XYNPEpMissID","NPE Sum vs X vs Y for p wrong PID;X Dimension (cm);Y Dimension (cm);NPE",100,-50,50,100,-50,50,100,0.0,50);

  h1EDTM                  = new TH1F("EDTM","EDTM Time;EDTM TDC Time;Counts",10000,-5000,5000);
  h1TRIG5                 = new TH1F("TRIG5","TRIG5 Time;TRIG5 TDC Time;Counts",10000,-5000,5000);

  GetOutputList()->Add(h2missKcut_CT);
  GetOutputList()->Add(h2misspicut_CT);
  GetOutputList()->Add(h2misspcut_CT);
  GetOutputList()->Add(h2HGCXYAll);
  GetOutputList()->Add(h2HGCXYPion);
  GetOutputList()->Add(h2HGCXYKaon);
  GetOutputList()->Add(h2HGCXYProton);
  GetOutputList()->Add(h3XYNPEAll);
  GetOutputList()->Add(h3XYNPEPion);
  GetOutputList()->Add(h3XYNPEKaon);
  GetOutputList()->Add(h3XYNPEProton);
  GetOutputList()->Add(h2ROC1_Coin_Beta_noID_kaon);
  GetOutputList()->Add(h2ROC1_Coin_Beta_kaon);
  GetOutputList()->Add(h2ROC1_Coin_Beta_randID_kaon);
  GetOutputList()->Add(h2ROC1_Coin_Beta_noID_pion);
  GetOutputList()->Add(h2ROC1_Coin_Beta_pion);
  GetOutputList()->Add(h2ROC1_Coin_Beta_randID_pion);
  GetOutputList()->Add(h2ROC1_Coin_Beta_noID_proton);
  GetOutputList()->Add(h2ROC1_Coin_Beta_proton);
  GetOutputList()->Add(h2ROC1_Coin_Beta_randID_proton);
  GetOutputList()->Add(h2HMS_electron);
  GetOutputList()->Add(h2HMS_electron_cut);
  GetOutputList()->Add(h1SHMS_electron);
  GetOutputList()->Add(h1SHMS_electron_cut);
  GetOutputList()->Add(h2SHMS_AERO_HGC);
  GetOutputList()->Add(h2SHMS_CAL_HGC);
  GetOutputList()->Add(h2SHMSK_kaon_cut);
  GetOutputList()->Add(h2SHMSK_pion_cut);
  GetOutputList()->Add(h2SHMSpi_kaon_cut);
  GetOutputList()->Add(h2SHMSpi_pion_cut);
  GetOutputList()->Add(h2SHMSp_kaon_cut);
  GetOutputList()->Add(h2SHMSp_pion_cut);
  GetOutputList()->Add(h1SHMS_delta);
  GetOutputList()->Add(h1SHMS_delta_cut);
  GetOutputList()->Add(h1HMS_delta);
  GetOutputList()->Add(h1HMS_delta_cut);
  GetOutputList()->Add(h1SHMS_th);
  GetOutputList()->Add(h1SHMS_th_cut);
  GetOutputList()->Add(h1SHMS_ph);
  GetOutputList()->Add(h1SHMS_ph_cut);
  GetOutputList()->Add(h1HMS_th);
  GetOutputList()->Add(h1HMS_th_cut);
  GetOutputList()->Add(h1HMS_ph);
  GetOutputList()->Add(h1HMS_ph_cut);
  GetOutputList()->Add(h1mmissK);
  GetOutputList()->Add(h1mmissK_rand);
  GetOutputList()->Add(h1mmissK_cut);
  GetOutputList()->Add(h1mmissK_remove);
  GetOutputList()->Add(h1mmisspi);
  GetOutputList()->Add(h1mmisspi_rand);
  GetOutputList()->Add(h1mmisspi_cut);
  GetOutputList()->Add(h1mmisspi_remove);
  GetOutputList()->Add(h1mmissp);
  GetOutputList()->Add(h1mmissp_rand);
  GetOutputList()->Add(h1mmissp_cut);
  GetOutputList()->Add(h1mmissp_remove);
  GetOutputList()->Add(h2WvsQ2);
  GetOutputList()->Add(h2uvsph_q);
  GetOutputList()->Add(h1epsilon);
  GetOutputList()->Add(h1mmpKMissID);
  GetOutputList()->Add(h1mmKpMissID);
  GetOutputList()->Add(h2HGCXYKMissID);
  GetOutputList()->Add(h2HGCXYpMissID);
  GetOutputList()->Add(h3XYNPEKMissID);
  GetOutputList()->Add(h3XYNPEpMissID);
  GetOutputList()->Add(h1EDTM);
  GetOutputList()->Add(h1TRIG5);
}

Bool_t ProtonYield::Process(Long64_t entry)
{
  fReader.SetEntry(entry);
  // Note, these should be set for ALL entries somewhere else but I had no luck actually getting this to work correctly
  // This a very horrible implementation of this but it works so it's FINE for now. I really hate it though
  Double_t Offset[3] = {43.5, 43.6, 43.4};
  Double_t PromptLow[3] = {-2, -2, -2};
  Double_t PromptHigh[3] = {2, 2, 2};
  Double_t RandomLow[3] = {6.5, 6.5, 6.5};
  Double_t RandomHigh[3] = {18.5, 18.5, 18.5};
  
  // Fill some histograms before applying any cuts
  h1EDTM->Fill(*pEDTM);
  h2HMS_electron->Fill(H_cal_etotnorm[0],H_cer_npeSum[0]);
  h1SHMS_electron->Fill(P_cal_etotnorm[0]);
  h2SHMS_AERO_HGC->Fill(P_aero_npeSum[0],P_hgcer_npeSum[0]);
  h2SHMS_CAL_HGC->Fill(P_cal_etotnorm[0],P_hgcer_npeSum[0]);
  h1SHMS_delta->Fill(P_gtr_dp[0]);
  h1HMS_delta->Fill(H_gtr_dp[0]);
  h1SHMS_th->Fill(P_gtr_th[0]);
  h1SHMS_ph->Fill(P_gtr_ph[0]);
  h1HMS_th->Fill(H_gtr_th[0]);
  h1HMS_ph->Fill(H_gtr_ph[0]);
 
 // This analysis operates on runs that have been analysed as though a kaon is going into the SHMS
  Double_t MMp = sqrt(pow(emiss[0] + sqrt(pow(0.493677,2) + pow(P_gtr_p[0],2)) - sqrt(pow(0.93828,2) + pow(P_gtr_p[0],2)),2)-pow(pmiss[0],2)); // Calculate missing mass under condition that hadron is a proton
  Double_t MMPi = sqrt(pow(emiss[0] + sqrt(pow(0.493677,2) + pow(P_gtr_p[0],2)) - sqrt(pow(0.13957018,2) + pow(P_gtr_p[0],2)),2)-pow(pmiss[0],2)); // Calculate missing mass under condition that hadron is a pion
  Double_t MMK = sqrt(pow(emiss[0],2)-pow(pmiss[0],2)); // Calculate missing mass under condition that hadron is a kaon
  h1mmissK->Fill(MMK);
  h1mmisspi->Fill(MMPi);
  if (MMp > 0) h1mmissp->Fill(MMp);

  // Cuts that all particle species share in common
  // if (P_cal_etotnorm[0] > 0.6) return kTRUE; // Check SHMS doesn't see a positron
  if (H_cal_etotnorm[0] < 0.7 || H_cer_npeSum[0] < 1.5) return kTRUE; // Check HMS sees an electron
  //  if (H_gtr_dp[0] > 17.0 || H_gtr_dp[0] < -13.0) return kTRUE;
  if (H_gtr_dp[0] > 8.0 || H_gtr_dp[0] < -8.0) return kTRUE; // add HMS delta cuts
  if (P_gtr_dp[0] > 20.0 || P_gtr_dp[0] < -10.0) return kTRUE; // Cut on delta
  if (TMath::Abs(P_gtr_th[0]) > 0.060) return kTRUE; // Cut on theta/phi for SHMS/HMS, broadened from 0.4/0.024 to current values
  if (TMath::Abs(P_gtr_ph[0]) > 0.040) return kTRUE; // Without these we see too much crap in the t-phi plot
  if (TMath::Abs(H_gtr_th[0]) > 0.080) return kTRUE; // Keep them in, they will need tweaking in future
  if (TMath::Abs(H_gtr_ph[0]) > 0.045) return kTRUE;

  // Fill histograms with events AFTER doing our common cuts
  h2HMS_electron_cut->Fill(H_cal_etotnorm[0],H_cer_npeSum[0]);
  h1SHMS_electron_cut->Fill(P_cal_etotnorm[0]);
  h1SHMS_delta_cut->Fill(P_gtr_dp[0]);
  h1HMS_delta_cut->Fill(H_gtr_dp[0]);
  h1SHMS_th_cut->Fill(P_gtr_th[0]);
  h1SHMS_ph_cut->Fill(P_gtr_ph[0]);
  h1HMS_th_cut->Fill(H_gtr_th[0]);
  h1HMS_ph_cut->Fill(H_gtr_ph[0]);
  h2HGCXYAll->Fill(P_hgcer_xAtCer[0],P_hgcer_yAtCer[0]);
  h3XYNPEAll->Fill(P_hgcer_xAtCer[0],P_hgcer_yAtCer[0],P_hgcer_npeSum[0]);

  //Event identified as Pion
  if (P_hgcer_npeSum[0] > 1.5 && P_aero_npeSum[0] > 1.5) { // HGC and AERO hit
    h2ROC1_Coin_Beta_noID_pion->Fill((CTime_ePiCoinTime_ROC1[0] - Offset[0]),P_gtr_beta[0]);
    if (abs(P_gtr_beta[0]-1.00) > 0.3) return kTRUE;
    h2misspicut_CT->Fill( CTime_ePiCoinTime_ROC1[0] - Offset[0], MMPi);
    h2HGCXYPion->Fill(P_hgcer_xAtCer[0],P_hgcer_yAtCer[0]);  
    h3XYNPEPion->Fill(P_hgcer_xAtCer[0],P_hgcer_yAtCer[0],P_hgcer_npeSum[0]);
    if ((CTime_ePiCoinTime_ROC1[0] - Offset[0]) > PromptLow[0] && (CTime_ePiCoinTime_ROC1[0] - Offset[0]) < PromptHigh[0]) {
      h2ROC1_Coin_Beta_pion->Fill((CTime_ePiCoinTime_ROC1[0] - Offset[0]),P_gtr_beta[0]);
      h2SHMSpi_kaon_cut->Fill(P_aero_npeSum[0],P_hgcer_npeSum[0]);
      h2SHMSpi_pion_cut->Fill(P_cal_etotnorm[0],P_hgcer_npeSum[0]);
      h1mmisspi_cut->Fill(MMPi);
    }
    if (abs((CTime_ePiCoinTime_ROC1[0] - Offset[0])) > RandomLow[0] && abs((CTime_ePiCoinTime_ROC1[0] - Offset[0])) < PromptHigh[0]) {
      h1mmisspi_rand->Fill(MMPi);
      h1mmisspi_remove->Fill(MMPi);
      h2ROC1_Coin_Beta_randID_pion->Fill((CTime_ePiCoinTime_ROC1[0] - Offset[0]),P_gtr_beta[0]);    
    }
  }

  //Event identified as Kaon
  if (P_aero_npeSum[0] > 1.5 && P_hgcer_npeSum[0] < 1.5) { // AERO but no HGC
    h2ROC1_Coin_Beta_noID_kaon->Fill((CTime_eKCoinTime_ROC1[0] - Offset[1]),P_gtr_beta[0]); 
    if (abs(P_gtr_beta[0]-1.00) > 0.1) return kTRUE;
    h2missKcut_CT->Fill( CTime_eKCoinTime_ROC1[0] - Offset[1], MMK);
    h2HGCXYKaon->Fill(P_hgcer_xAtCer[0],P_hgcer_yAtCer[0]);
    h3XYNPEKaon->Fill(P_hgcer_xAtCer[0],P_hgcer_yAtCer[0],P_hgcer_npeSum[0]);
    if ( (CTime_eKCoinTime_ROC1[0] - Offset[1]) > PromptLow[1] && (CTime_eKCoinTime_ROC1[0] - Offset[1]) < PromptHigh[1]) {
      h2ROC1_Coin_Beta_kaon->Fill((CTime_eKCoinTime_ROC1[0] - Offset[1]),P_gtr_beta[0]);
      h2SHMSK_kaon_cut->Fill(P_aero_npeSum[0],P_hgcer_npeSum[0]);
      h2SHMSK_pion_cut->Fill(P_cal_etotnorm[0],P_hgcer_npeSum[0]);
      h1mmissK_cut->Fill(MMK);
      if (0.7 < MMK && MMK < 0.9){
	h1mmpKMissID->Fill(MMp);
	h2HGCXYKMissID->Fill(P_hgcer_xAtCer[0],P_hgcer_yAtCer[0]);
	h3XYNPEKMissID->Fill(P_hgcer_xAtCer[0],P_hgcer_yAtCer[0],P_hgcer_npeSum[0]);
      }
    }
    if (abs((CTime_eKCoinTime_ROC1[0] - Offset[1])) > RandomLow[1]  && abs((CTime_eKCoinTime_ROC1[0] - Offset[1])) < RandomHigh[1]) {
      h1mmissK_rand->Fill(MMK);
      h1mmissK_remove->Fill(MMK);
      h2ROC1_Coin_Beta_randID_kaon->Fill((CTime_eKCoinTime_ROC1[0] - Offset[1]),P_gtr_beta[0]);
    }
  }

  //Event identified as Proton
  if (P_aero_npeSum[0] < 1.5 && P_hgcer_npeSum[0] < 1.5) { // No HGC or AERO
    h2ROC1_Coin_Beta_noID_proton->Fill((CTime_epCoinTime_ROC1[0] - Offset[2]),P_gtr_beta[0]);
    if (abs(P_gtr_beta[0]-1.00) > 0.1) return kTRUE;
    h2misspcut_CT->Fill( CTime_epCoinTime_ROC1[0] - Offset[2], MMp);
    h2HGCXYProton->Fill(P_hgcer_xAtCer[0],P_hgcer_yAtCer[0]);
    h3XYNPEProton->Fill(P_hgcer_xAtCer[0],P_hgcer_yAtCer[0],P_hgcer_npeSum[0]);
    if ((CTime_epCoinTime_ROC1[0] - Offset[2]) > PromptLow[2] && (CTime_epCoinTime_ROC1[0] - Offset[2]) < PromptHigh[2]) {
      h2ROC1_Coin_Beta_proton->Fill((CTime_epCoinTime_ROC1[0] - Offset[2]),P_gtr_beta[0]);
      h2SHMSp_kaon_cut->Fill(P_aero_npeSum[0],P_hgcer_npeSum[0]);
      h2SHMSp_pion_cut->Fill(P_cal_etotnorm[0],P_hgcer_npeSum[0]);
      h1mmissp_cut->Fill(MMp);
      h2WvsQ2->Fill(Q2[0],W[0]);
      // Due to the way hcana defines T and U, for the proton case mandelstam t is actually mandelstam u and vice versa
      // Slightly stupid/confusing but could be corrected at some point
      h2uvsph_q->Fill(ph_q[0],-MandelT[0]);
      h1epsilon->Fill(epsilon[0]);
      if (0.8 < MMK && MMK < 0.9){
	h1mmKpMissID->Fill(MMK);
	h2HGCXYpMissID->Fill(P_hgcer_xAtCer[0],P_hgcer_yAtCer[0]);
	h3XYNPEpMissID->Fill(P_hgcer_xAtCer[0],P_hgcer_yAtCer[0],P_hgcer_npeSum[0]);
      }
    }
    if (abs((CTime_epCoinTime_ROC1[0] - Offset[2])) > RandomLow[2] && abs((CTime_epCoinTime_ROC1[0] - Offset[2])) < RandomHigh[2]) {
      h1mmissp_rand->Fill(MMp);
      h1mmissp_remove->Fill(MMp);
      h2ROC1_Coin_Beta_randID_proton->Fill((CTime_epCoinTime_ROC1[0] - Offset[2]),P_gtr_beta[0]);
    }
  }
  return kTRUE;
}

void ProtonYield::SlaveTerminate()
{
}

void ProtonYield::Terminate()
{
  TString option = GetOption();
  TH1F* EDTM = dynamic_cast<TH1F*> (GetOutputList()->FindObject("EDTM"));
  TH2F* HMS_electron = dynamic_cast<TH2F*> (GetOutputList()->FindObject("HMS_electron"));
  TH2F* HMS_electron_cut = dynamic_cast<TH2F*> (GetOutputList()->FindObject("HMS_electron_cut"));
  TH3F* XYNPE3DAll;
  TH3F* XYNPE3DPion;
  TH3F* XYNPE3DKaon;
  TH3F* XYNPE3DProton;
  TH3F* XYNPE3DKaonMissID;
  TH3F* XYNPE3DProtonMissID;
  XYNPE3DAll = dynamic_cast<TH3F*> (GetOutputList()->FindObject("h3XYNPEAll"));
  XYNPE3DPion = dynamic_cast<TH3F*> (GetOutputList()->FindObject("h3XYNPEPion"));
  XYNPE3DKaon = dynamic_cast<TH3F*> (GetOutputList()->FindObject("h3XYNPEKaon"));
  XYNPE3DProton = dynamic_cast<TH3F*> (GetOutputList()->FindObject("h3XYNPEProton"));
  XYNPE3DKaonMissID = dynamic_cast<TH3F*> (GetOutputList()->FindObject("h3XYNPEKMissID"));
  XYNPE3DProtonMissID = dynamic_cast<TH3F*> (GetOutputList()->FindObject("h3XYNPEpMissID"));

  TProfile2D *h3XYNPEAll_pxy = new TProfile2D("h3XYNPEAll_pxy","NPE vs X vs Y; Y Dimension (cm);X Dimension (cm)",100,-50,50,100,-50,50,0.0,50);
  XYNPE3DAll->Project3DProfile("xy");
  TProfile2D *h3XYNPEPion_pxy = new TProfile2D("h3XYNPEPion_pxy","NPE vs X vs Y; Y Dimension (cm);X Dimension (cm)",100,-50,50,100,-50,50,0.0,50);
  XYNPE3DPion->Project3DProfile("xy");
  TProfile2D *h3XYNPEKaon_pxy = new TProfile2D("h3XYNPEKaon_pxy","NPE vs X vs Y; Y Dimension (cm);X Dimension (cm)",100,-50,50,100,-50,50,0.0,50);
  XYNPE3DKaon->Project3DProfile("xy");
  TProfile2D *h3XYNPEProton_pxy = new TProfile2D("h3XYNPEProton_pxy","NPE vs X vs Y; Y Dimension (cm);X Dimension (cm)",100,-50,50,100,-50,50,0.0,50);
  XYNPE3DProton->Project3DProfile("xy");
  TProfile2D *h3XYNPEKMissID_pxy = new TProfile2D("h3XYNPEKMissID_pxy","NPE vs X vs Y; Y Dimension (cm);X Dimension (cm)",100,-50,50,100,-50,50,0.0,50);
  XYNPE3DKaonMissID->Project3DProfile("xy");
  TProfile2D *h3XYNPEpMissID_pxy = new TProfile2D("h3XYNPEpMissID_pxy","NPE vs X vs Y; Y Dimension (cm);X Dimension (cm)",100,-50,50,100,-50,50,0.0,50);
  XYNPE3DProtonMissID->Project3DProfile("xy");

  Double_t RandomLow[3] = {6.5, 6.5, 6.5};
  Double_t RandomHigh[3] = {18.5, 18.5, 18.5};
 
  h1mmissK_rand->Scale(1.0/6.0);
  h1mmisspi_rand->Scale(1.0/6.0); 
  h1mmissp_rand->Scale(1.0/6.0);
  h1mmissK_remove->Add(h1mmissK_cut,h1mmissK_rand,1,-1);
  h1mmisspi_remove->Add(h1mmisspi_cut,h1mmisspi_rand,1,-1);
  h1mmissp_remove->Add(h1mmissp_cut,h1mmissp_rand,1,-1);
  
  // Provide a full path?
  TString foutname = Form("../OUTPUT/Proton_Kinematics_Run%i_AllPlots", option.Atoi());
  TString outputpng = foutname + ".png";
  TString outputpng_coin = foutname + "_coin.png";
  TString outputpdf = foutname + ".pdf";
  
  TCanvas *cCuts = new TCanvas("Cuts","Summary of Common Cuts",100,0,1000,900);
  cCuts->Divide(2,4);
  cCuts->cd(1); h1HMS_delta->Draw();
  cCuts->cd(2); h1HMS_delta_cut->Draw();
  cCuts->cd(3); h1SHMS_delta->Draw();
  cCuts->cd(4); h1SHMS_delta_cut->Draw();
  cCuts->cd(5); HMS_electron->Draw("Colz");
  cCuts->cd(6); HMS_electron_cut->Draw("Colz");
  cCuts->cd(7); h1SHMS_electron->Draw();
  cCuts->cd(8); h1SHMS_electron_cut->Draw();
  cCuts->Print(outputpdf + '(');

  TCanvas *cAngles = new TCanvas("Angles","Summary of Angular Cuts",200,50,1000,900);
  cAngles->Divide(2,4);
  cAngles->cd(1); h1HMS_th->Draw();
  cAngles->cd(2); h1HMS_th_cut->Draw();
  cAngles->cd(3); h1HMS_ph->Draw();
  cAngles->cd(4); h1HMS_ph_cut->Draw();
  cAngles->cd(5); h1SHMS_th->Draw();
  cAngles->cd(6); h1SHMS_th_cut->Draw();
  cAngles->cd(7); h1SHMS_ph->Draw();
  cAngles->cd(8); h1SHMS_ph_cut->Draw();
  cAngles->Print(outputpdf);

  TCanvas *cpiID = new TCanvas("piID","Summary of Pion Particle ID Cuts",300,100,1000,900);
  cpiID->Divide(2,4);
  cpiID->cd(1); h2SHMS_AERO_HGC->Draw("Colz");
  cpiID->cd(2); h2SHMSpi_kaon_cut->Draw("Colz");
  cpiID->cd(3); h2SHMS_CAL_HGC->Draw("Colz");
  cpiID->cd(4); h2SHMSpi_pion_cut->Draw("Colz");
  cpiID->cd(5); h2ROC1_Coin_Beta_noID_pion->Draw("Colz");
  cpiID->Update();
  TLine *piLowerRand1 = new TLine(RandomLow[0],gPad->GetUymin(), RandomLow[0],gPad->GetUymax()); 
  piLowerRand1->SetLineColor(kRed); piLowerRand1->SetLineWidth(1); piLowerRand1->Draw();
  TLine *piUpperRand1 = new TLine(RandomHigh[0],gPad->GetUymin(), RandomHigh[0],gPad->GetUymax());  
  piUpperRand1->SetLineColor(kRed); piUpperRand1->SetLineWidth(1); piUpperRand1->Draw();
  TLine *piLowerRand2 = new TLine(-RandomHigh[0],gPad->GetUymin(), -RandomHigh[0],gPad->GetUymax()); 
  piLowerRand2->SetLineColor(kRed); piLowerRand2->SetLineWidth(1); piLowerRand2->Draw();
  TLine *piUpperRand2 = new TLine(-RandomLow[0],gPad->GetUymin(),-RandomLow[0],gPad->GetUymax());  
  piUpperRand2->SetLineColor(kRed); piUpperRand2->SetLineWidth(1); piUpperRand2->Draw();
  cpiID->cd(6); h2ROC1_Coin_Beta_pion->Draw("Colz");
  cpiID->cd(7); h1mmisspi->Draw();
  cpiID->cd(8); h1mmisspi_remove->Draw("hist");
  cpiID->Update();
  cpiID->Print(outputpdf);

  TCanvas *cKID = new TCanvas("KID","Summary of Kaon Particle ID Cuts",300,100,1000,900);
  cKID->Divide(2,4);
  cKID->cd(1); h2SHMS_AERO_HGC->Draw("Colz");
  cKID->cd(2); h2SHMSK_kaon_cut->Draw("Colz");
  cKID->cd(3); h2SHMS_CAL_HGC->Draw("Colz");
  cKID->cd(4); h2SHMSK_pion_cut->Draw("Colz");
  cKID->cd(5); h2ROC1_Coin_Beta_noID_kaon->Draw("Colz");
  cKID->Update();
  TLine *KLowerRand1 = new TLine(RandomLow[1],gPad->GetUymin(),RandomLow[1],gPad->GetUymax()); 
  KLowerRand1->SetLineColor(kRed); KLowerRand1->SetLineWidth(1); KLowerRand1->Draw();
  TLine *KUpperRand1 = new TLine(RandomHigh[1],gPad->GetUymin(),RandomHigh[1],gPad->GetUymax());  
  KUpperRand1->SetLineColor(kRed); KUpperRand1->SetLineWidth(1); KUpperRand1->Draw();
  TLine *KLowerRand2 = new TLine(-RandomHigh[1],gPad->GetUymin(),-RandomHigh[1],gPad->GetUymax()); 
  KLowerRand2->SetLineColor(kRed); KLowerRand2->SetLineWidth(1); KLowerRand2->Draw();
  TLine *KUpperRand2 = new TLine(-RandomLow[1],gPad->GetUymin(),-RandomLow[1],gPad->GetUymax());  
  KUpperRand2->SetLineColor(kRed); KUpperRand2->SetLineWidth(1); KUpperRand2->Draw();
  cKID->cd(6); h2ROC1_Coin_Beta_kaon->Draw("Colz");
  cKID->cd(7); h1mmissK->Draw();
  cKID->cd(8); h1mmissK_remove->Draw("hist");
  cKID->Update();
  cKID->Print(outputpdf);

  TCanvas *cpID = new TCanvas("pID","Summary of Proton Particle ID Cuts",300,100,1000,900);
  cpID->Divide(2,4);
  cpID->cd(1); h2SHMS_AERO_HGC->Draw("Colz");
  cpID->cd(2); h2SHMSp_kaon_cut->Draw("Colz");
  cpID->cd(3); h2SHMS_CAL_HGC->Draw("Colz");
  cpID->cd(4); h2SHMSp_pion_cut->Draw("Colz");
  cpID->cd(5); h2ROC1_Coin_Beta_noID_proton->Draw("Colz");
  cpID->Update();
  TLine *pLowerRand1 = new TLine(RandomLow[2],gPad->GetUymin(),RandomLow[2],gPad->GetUymax()); 
  pLowerRand1->SetLineColor(kRed); pLowerRand1->SetLineWidth(1); pLowerRand1->Draw();
  TLine *pUpperRand1 = new TLine(RandomHigh[2],gPad->GetUymin(),RandomHigh[2],gPad->GetUymax());  
  pUpperRand1->SetLineColor(kRed); pUpperRand1->SetLineWidth(1); pUpperRand1->Draw();
  TLine *pLowerRand2 = new TLine(-RandomHigh[2],gPad->GetUymin(),-RandomHigh[2],gPad->GetUymax()); 
  pLowerRand2->SetLineColor(kRed); pLowerRand2->SetLineWidth(1); pLowerRand2->Draw();
  TLine *pUpperRand2 = new TLine(-RandomLow[2],gPad->GetUymin(),-RandomLow[2],gPad->GetUymax());  
  pUpperRand2->SetLineColor(kRed); pUpperRand2->SetLineWidth(1); pUpperRand2->Draw();  
  cpID->cd(6); h2ROC1_Coin_Beta_proton->Draw("Colz");
  cpID->cd(7); h1mmissp->Draw();
  cpID->cd(8); h1mmissp_remove->Draw("hist");
  cpID->Update();
  cpID->Print(outputpdf);  
  
  TCanvas *picCoinTime = new TCanvas("picCoinTime","Summary of pion coincidence time and random",400,150,1000,900);
  picCoinTime->Divide(2,2);
  picCoinTime->cd(1);
  h1mmisspi_cut->Draw();
  h1mmisspi_rand->Draw("same");
  h1mmisspi_rand->SetLineColor(2);
  picCoinTime->cd(2);
  h1mmisspi_rand->Draw();
  picCoinTime->cd(3);
  h1mmisspi_remove->Draw();
  picCoinTime->cd(4);
  h2misspicut_CT->Draw("Colz");
  picCoinTime->Print(outputpng_coin);
  picCoinTime->Print(outputpdf);
  
  TCanvas *KcCoinTime = new TCanvas("KcCoinTime","Summary of kaon coincidence time and random",400,150,1000,900);
  KcCoinTime->Divide(2,2);
  KcCoinTime->cd(1);
  h1mmissK_cut->Draw();
  h1mmissK_rand->Draw("same");
  h1mmissK_rand->SetLineColor(2);
  KcCoinTime->cd(2);
  h1mmissK_rand->Draw();
  KcCoinTime->cd(3);
  h1mmissK_remove->Draw();
  KcCoinTime->cd(4);
  h2missKcut_CT->Draw("Colz");
  KcCoinTime->Print(outputpng_coin);
  KcCoinTime->Print(outputpdf);
  
  TCanvas *pcCoinTime = new TCanvas("pcCoinTime","Summary of proton coincidence time and random",400,150,1000,900);
  pcCoinTime->Divide(2,2);
  pcCoinTime->cd(1);
  h1mmissp_cut->Draw();
  h1mmissp_rand->Draw("same");
  h1mmissp_rand->SetLineColor(2);
  pcCoinTime->cd(2);
  h1mmissp_rand->Draw();
  pcCoinTime->cd(3);
  h1mmissp_remove->Draw();
  pcCoinTime->cd(4);
  h2misspcut_CT->Draw("Colz");
  pcCoinTime->Print(outputpng_coin);
  pcCoinTime->Print(outputpdf);

  TCanvas *cKine = new TCanvas("Kine","Summary of Higher Order Kinematics",500,200,1000,900);
  cKine->Divide(2,2);
  cKine->cd(1); h2WvsQ2->Draw("Colz"); 
  h2WvsQ2->SetTitleOffset(1.0,"Y");
  cKine->cd(3); 
  h2uvsph_q->Draw("SURF2 POL"); 
  gPad->SetTheta(90); gPad->SetPhi(180);
  TPaveText *uvsphi_title = new TPaveText(0.0277092,0.89779,0.096428,0.991854,"NDC");
  uvsphi_title->AddText("-u vs #phi"); uvsphi_title->Draw();
  TPaveText *ptphizero = new TPaveText(0.923951,0.513932,0.993778,0.574551,"NDC");
  ptphizero->AddText("#phi = 0"); ptphizero->Draw();
  TLine *phihalfpi = new TLine(0,0,0,0.6); 
  phihalfpi->SetLineColor(kBlack); phihalfpi->SetLineWidth(2); phihalfpi->Draw();  
  TPaveText *ptphihalfpi = new TPaveText(0.417855,0.901876,0.486574,0.996358,"NDC");
  ptphihalfpi->AddText("#phi = #frac{#pi}{2}"); ptphihalfpi->Draw();
  TLine *phipi = new TLine(0,0,-0.6,0); 
  phipi->SetLineColor(kBlack); phipi->SetLineWidth(2); phipi->Draw();  
  TPaveText *ptphipi = new TPaveText(0.0277092,0.514217,0.096428,0.572746,"NDC");
  ptphipi->AddText("#phi = #pi"); ptphipi->Draw();
  TLine *phithreepi = new TLine(0,0,0,-0.6); 
  phithreepi->SetLineColor(kBlack); phithreepi->SetLineWidth(2); phithreepi->Draw();  
  TPaveText *ptphithreepi = new TPaveText(0.419517,0.00514928,0.487128,0.0996315,"NDC");
  ptphithreepi->AddText("#phi = #frac{3#pi}{2}"); ptphithreepi->Draw();
  for (Int_t k = 0; k < 10; k++){
    Arc[k] = new TArc(); 
    Arc[k]->SetFillStyle(0);
    Arc[k]->SetLineWidth(2);
    Arc[k]->DrawArc(0,0,0.575*(k+1)/(10),0.,360.,"same"); 
  }
  //make sure that if you change range on the u-phi you change this uradius aswell. The sixth input is the range on the ruler on the t-phi plot. hienricn 2019/06/29
  TGaxis *tradius = new TGaxis(0,0,0.575,0,0,1.5,10,"-+"); 
  tradius->SetLineColor(2);tradius->SetLabelColor(2);tradius->Draw();
  TLine *phizero = new TLine(0,0,0.6,0); 
  phizero->SetLineColor(kBlack); phizero->SetLineWidth(2); phizero->Draw();
  cKine->cd(2); h1epsilon->Draw();
  h1epsilon->SetTitleOffset(1.0,"Y");
  cKine->cd(4); h1mmissp_remove->Draw("hist");
  h1mmissp_remove->SetTitleOffset(1.0,"Y");
  // Save TCanvas
  cKine->Print(outputpng);
  cKine->Print(outputpdf + ')');

  //Start output of .root file with all histograms
  TFile *Histogram_file = new TFile(Form("../HISTOGRAMS/KaonLT_Proton_Run%i.root",option.Atoi()),"RECREATE");
  TDirectory *DCuts = Histogram_file->mkdir("Spectrometer Delta and Calorimeter Cuts"); DCuts->cd();
  h1HMS_delta->Write("HMS Delta Before Cuts"); h1HMS_delta_cut->Write("HMS Delta After Cuts");
  h1SHMS_delta->Write("SHMS Delta Before Cuts"); h1SHMS_delta_cut->Write("SHMS Delta After Cuts");
  HMS_electron->Write("HMS Calorimeter Before Cuts"); HMS_electron_cut->Write("HMS Calorimeter After Cuts");
  h1SHMS_electron->Write("SHMS Calorimeter Before Cuts"); h1SHMS_electron_cut->Write("SHMS Calorimeter After Cuts");
  h2SHMS_AERO_HGC->Write("SHMS Aerogel vs HGC before Cuts"); h2SHMS_CAL_HGC->Write("SHMS Calorimeter vs HGC Before Cuts");

  TDirectory *DAngles = Histogram_file->mkdir("Spectrometer Angular Cuts"); DAngles->cd();
  h1HMS_th->Write("HMS Theta Before Cuts"); h1HMS_th_cut->Write("HMS Theta After Cuts");
  h1SHMS_th->Write("SHMS Theta Before Cuts"); h1SHMS_th_cut->Write("SHMS Theta After Cuts");
  h1HMS_ph->Write("HMS Phi Before Cuts"); h1HMS_ph_cut->Write("HMS Phi After Cuts");
  h1SHMS_ph->Write("SHMS Phi Before Cuts"); h1SHMS_ph_cut->Write("SHMS Phi After Cuts");

  TDirectory *DRand = Histogram_file->mkdir("Random Subtraction Summary"); DRand->cd();
  h1mmissK_cut->Write("Kaon Missing Mass, with Randoms");
  h1mmissK_rand->Write("Kaon Missing Mass, only Randoms");
  h1mmissK_remove->Write("Kaon Missing Mass, Randoms Removed");
  h1mmisspi_cut->Write("Pion Missing Mass, with Randoms");
  h1mmisspi_rand->Write("Pion Missing Mass, only Randoms");
  h1mmisspi_remove->Write("Pion Missing Mass, Randoms Removed");
  h1mmissp_cut->Write("Proton Missing Mass, with Randoms");
  h1mmissp_rand->Write("Proton Missing Mass, only Randoms");
  h1mmissp_remove->Write("Proton Missing Mass, Randoms Removed");

  TDirectory *DPion = Histogram_file->mkdir("Pion Identification Summary"); DPion->cd();
  h2SHMS_AERO_HGC->Write("SHMS HGC vs Aerogel no cuts"); 
  h2SHMSpi_kaon_cut->Write("SHMS HGC vs Aerogel, with cuts");
  h2SHMS_CAL_HGC->Write("SHMS HGC vs CAL, no Cuts");
  h2SHMSpi_pion_cut->Write("SHMS HGC vs CAL, with cuts");
  h2ROC1_Coin_Beta_noID_pion->Write("Pion-Electron Coincidence Time, no cuts");
  h2ROC1_Coin_Beta_pion->Write("Pion-Electron Coincidence Time, with cuts");
  h2ROC1_Coin_Beta_randID_pion->Write("Random Pion-Electron Coincidence Time, with cuts");
  h2misspicut_CT->Write("Pion-Electron Coincidence Time vs Missing Mass");
  h1mmisspi->Write("Pion Missing Mass, no cuts");
  h1mmisspi_remove->Write("Pion Missing Mass, with cuts");

  TDirectory *DKaon = Histogram_file->mkdir("Kaon Identification Summary"); DKaon->cd();
  h2SHMSK_kaon_cut->Write("SHMS HGC vs Aerogel, with cuts");
  h2SHMSK_pion_cut->Write("SHMS HGC vs CAL, with cuts");
  h2ROC1_Coin_Beta_noID_kaon->Write("Kaon-Electron Coincidence Time, no cuts");
  h2ROC1_Coin_Beta_kaon->Write("Kaon-Electron Coincidence Time, with cuts");
  h2ROC1_Coin_Beta_randID_kaon->Write("Random Kaon-Electron Coincidence Time, with cuts");
  h2missKcut_CT->Write("Kaon-Electron Coincidence Time vs Missing Mass");
  h1mmissK->Write("Kaon Missing Mass, no cuts");
  h1mmissK_remove->Write("Kaon Missing Mass, with cuts");

  TDirectory *DProton = Histogram_file->mkdir("Proton Identification Summary"); DProton->cd();
  h2SHMS_AERO_HGC->Write("SHMS HGC vs Aerogel no cuts");
  h2SHMSp_kaon_cut->Write("SHMS HGC vs Aerogel, with cuts");
  h2SHMS_CAL_HGC->Write("SHMS HGC vs CAL no Cuts");
  h2SHMSp_pion_cut->Write("SHMS HGC vs CAL, with cuts");
  h2ROC1_Coin_Beta_noID_proton->Write("Proton-Electron Coincidence Time, no cuts");
  h2ROC1_Coin_Beta_proton->Write("Proton-Electron Coincidence Time, with cuts");
  h2ROC1_Coin_Beta_randID_proton->Write("Random Proton-Electron Coincidence Time, with cuts"); 
  h2misspcut_CT->Write("Proton-Electron Coincidence Time vs Missing Mass");
  h1mmissp->Write("Proton Missing Mass, no cuts");
  h1mmissp_remove->Write("Proton Missing Mass, with cuts");

  TDirectory *DKine = Histogram_file->mkdir("Proton Higher Order Kinematics Summary"); DKine->cd();
  h2WvsQ2->Write("W vs Q2");
  h2uvsph_q->Write("u vs phi");
  h1epsilon->Write("epsilon");
  h1mmissp_remove->Write("Proton Missing Mass, with cuts");

  TDirectory *DEDTM = Histogram_file->mkdir("Accepted EDTM Events"); DEDTM->cd();
  EDTM->Write("EDTM TDC Time");

  TDirectory *DXYHGC = Histogram_file->mkdir("HGC X vs Y Information"); DXYHGC->cd();
  h2HGCXYAll->Write("All Events");
  h2HGCXYPion->Write("Pion Events");
  h2HGCXYKaon->Write("Kaon Events");
  h2HGCXYProton->Write("Proton Events");
  
  TDirectory *DXYNPE = Histogram_file->mkdir("NPE Sum vs X vs Y Information"); DXYNPE->cd();
  XYNPE3DAll->Write("3D All Events");
  h3XYNPEAll_pxy->Write("2D All Events");
  XYNPE3DPion->Write("3D Pion Events");
  h3XYNPEPion_pxy->Write("2D Pion Events");
  XYNPE3DKaon->Write("3D Kaon Events");
  h3XYNPEKaon_pxy->Write("2D Kaon Events");
  XYNPE3DProton->Write("3D Proton Events");
  h3XYNPEProton_pxy->Write("2D Proton Events");

  TDirectory *DMissID = Histogram_file->mkdir("Miss ID'd Events Testing"); DMissID->cd();
  XYNPE3DKaonMissID->Write("3D HGC NPE Miss-ID Kaon");  
  h3XYNPEKMissID_pxy->Write("2D HGC NPE Miss-ID Kaon");
  h2HGCXYKMissID->Write("2D HGC Miss-ID Kaon");
  h1mmpKMissID->Write("Proton Missing Mass for Miss-ID Kaons");
  XYNPE3DProtonMissID->Write("3D HGC NPE Miss-ID Proton");  
  h3XYNPEpMissID_pxy->Write("2D HGC NPE Miss-ID Proton");
  h2HGCXYpMissID->Write("2D HGC Miss-ID Proton");  
  h1mmKpMissID->Write("Kaon Missing Mass for Miss-ID Protons");

  Histogram_file->Close();
}
