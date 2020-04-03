#define hms_cer_efficiency_cxx
// The class definition in hms_cer_efficiency.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.


// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// root> T->Process("hms_cer_efficiency.C")
// root> T->Process("hms_cer_efficiency.C","some options")
// root> T->Process("hms_cer_efficiency.C+")
//


#include "hms_cer_efficiency.h"
#include <TStyle.h>
#include <TCanvas.h>
#include <TLine.h>
#include <TMath.h>
#include <TPaveText.h>

void hms_cer_efficiency::Begin(TTree * /*tree*/)
{
  // The Begin() function is called at the start of the query.
  // When running with PROOF Begin() is only called on the client.
  // The tree argument is deprecated (on PROOF 0 is passed).

  TString option = GetOption();

  Info("Begin", "Starting Good particle Selection");

  
}

void hms_cer_efficiency::SlaveBegin(TTree * /*tree*/)
{
  // The SlaveBegin() function is called after the Begin() function.
  // When running with PROOF SlaveBegin() is called on each slave server.
  // The tree argument is deprecated (on PROOF 0 is passed).

  TString option = GetOption();

  h1missKcut_CT   = new TH2F("h1missKcut_CT","Kaon Missing mass vs Coincidence Time;Time (ns);Mass (GeV/c^{2})^{2}",400,-10,10,100,0.8,1.4);

  /**
     electron cuts for PID efficiencies
   **/

  /////////////////////////////////////
  h2ROC1_Coin_Beta_noID_electron = new TH2F("ROC1_Coin_Beta_noCut_electron","Electron Coincident Time vs Mass (GeV/c^{2}) for ROC1 (w/out Cherenkov cuts);Time (ns);Mass (GeV/c^{2})",800,-5,5,200,0.0,2.0);
  h2ROC1_Coin_Beta_electron = new TH2F("ROC1_Coin_Beta_electron","Electron Coincident Time vs Mass (GeV/c^{2}) for ROC1 (w/ Cherenkov cuts);Time (ns);Mass (GeV/c^{2})",800,-5,5,200,0.0,2.0);

  h1massElec_noID              = new TH1F("massElec_noID","Electron Missing mass w/out cer;Mass (GeV/c^{2});Counts",200,0.0,2.0);
  h1massElec_noID->Sumw2();
  h1massElec_ID                = new TH1F("massElec_ID","Electron Missing mass w/ cer;Mass (GeV/c^{2});Counts",200,0.0,2.0);
  h1massElec_ID->Sumw2();
  ////////////////////////////////////
  
  h2ROC1_Coin_Beta_noID_kaon = new TH2F("ROC1_Coin_Beta_noCut_kaon","Kaon Coincident Time vs #beta for ROC1 (w/ particle ID);Time (ns);#beta",800,-40,40,200,0.0,2.0);
  h2ROC1_Coin_Beta_kaon = new TH2F("ROC1_Coin_Beta_kaon","Kaon Coincident Time vs #beta for ROC1;Time (ns);#beta",800,-40,40,200,0.0,2.0);
  h2ROC1_Coin_Beta_noID_pion = new TH2F("ROC1_Coin_Beta_noCut_pion","Pion Coincident Time vs #beta for ROC1 (w/ particle ID);Time (ns);#beta",800,-40,40,200,0.0,2.0);
  h2ROC1_Coin_Beta_pion = new TH2F("ROC1_Coin_Beta_pion","Pion Coincident Time vs #beta for ROC1;Time (ns);#beta",800,-40,40,200,0.0,2.0);
  h2ROC1_Coin_Beta_noID_proton = new TH2F("ROC1_Coin_Beta_noCut_proton","Proton Coincident Time vs #beta for ROC1 (w/ particle ID);Time (ns);#beta",800,-40,40,200,0.0,2.0);
  h2ROC1_Coin_Beta_proton = new TH2F("ROC1_Coin_Beta_proton","Proton Coincident Time vs #beta for ROC1;Time (ns);#beta",800,-40,40,200,0.0,2.0);

  h2HMS_electron        = new TH2F("HMS_electron","Normalized HMS Calorimeter Energy vs Cherenkov;Normalized Energy;CER NPE",200,0.01,1.5,60,0.1,30);
  h2HMS_electron_cut    = new TH2F("HMS_electron_cut","Normalized HMS Calorimeter Energy vs Cherenkov, Electrons Selected;Normalized Energy;CER NPE",200,0.01,1.5,60,0.0,30);

  h1SHMS_electron        = new TH1F("SHMS_electron","Normalized SHMS Calorimeter Energy;Normalized Energy;Counts",200,0.01,1.5);
  h1SHMS_electron_cut    = new TH1F("SHMS_electron_cut","Normalized SHMS Calorimeter Energy, Electrons Removed;Normalized Energy;Counts",200,0.01,1.5);

  h2SHMSK_kaon            = new TH2F("SHMSK_kaon","NPE in SHMS Aerogel and Heavy Gas;Aerogel NPE;HGC NPE",50,0.1,25,50,0.1,10);
  h2SHMSK_kaon_cut        = new TH2F("SHMSK_kaon_cut","NPE in SHMS Aerogel and Heavy Gas, Kaons Selected;Aerogel NPE;HGC NPE",50,0.0,25,50,0.0,10);
  h2SHMSK_pion            = new TH2F("SHMSK_pion","Normalized SHMS Calorimeter Energy and NPE in Heavy Gas;Normalized Energy;HGC NPE",50,0.1,2.0,50,0.1,30);
  h2SHMSK_pion_cut        = new TH2F("SHMSK_pion_cut","Normalized SHMS Calorimeter Energy and NPE in Heavy Gas, Pions Selected;Normalized Energy;HGC NPE",50,0.0,2.0,50,0.0,30);

  h2SHMSpi_kaon            = new TH2F("SHMSpi_kaon","NPE in SHMS Aerogel and Heavy Gas;Aerogel NPE;HGC NPE",50,0.1,25,150,0.1,30);
  h2SHMSpi_kaon_cut        = new TH2F("SHMSpi_kaon_cut","NPE in SHMS Aerogel and Heavy Gas, Kaons Selected;Aerogel NPE;HGC NPE",50,0.0,25,150,0.0,30);
  h2SHMSpi_pion            = new TH2F("SHMSpi_pion","Normalized SHMS Calorimeter Energy and NPE in Heavy Gas;Normalized Energy;HGC NPE",50,0.1,2.0,50,0.1,30);
  h2SHMSpi_pion_cut        = new TH2F("SHMSpi_pion_cut","Normalized SHMS Calorimeter Energy and NPE in Heavy Gas, Pions Selected;Normalized Energy;HGC NPE",50,0.0,2.0,50,0.0,30);

  h2SHMSp_kaon            = new TH2F("SHMSp_kaon","NPE in SHMS Aerogel and Heavy Gas;Aerogel NPE;HGC NPE",50,0.1,25,50,0.1,10);
  h2SHMSp_kaon_cut        = new TH2F("SHMSp_kaon_cut","NPE in SHMS Aerogel and Heavy Gas, Kaons Selected;Aerogel NPE;HGC NPE",50,0.0,25,50,0.0,10);
  h2SHMSp_pion            = new TH2F("SHMSp_pion","Normalized SHMS Calorimeter Energy and NPE in Heavy Gas;Normalized Energy;HGC NPE",50,0.1,2.0,50,0.1,30);
  h2SHMSp_pion_cut        = new TH2F("SHMSp_pion_cut","Normalized SHMS Calorimeter Energy and NPE in Heavy Gas, Pions Selected;Normalized Energy;HGC NPE",50,0.0,2.0,50,0.0,30);

  h1SHMS_delta           = new TH1F("SHMS_delta","SHMS #delta;#delta;Counts",100,-50,50);
  h1SHMS_delta_cut       = new TH1F("SHMS_delta_cut","SHMS #delta Cut;#delta;Counts",100,-50,50);
  h1HMS_delta            = new TH1F("HMS_delta","HMS #delta;#delta;Counts",100,-50,50);
  h1HMS_delta_cut        = new TH1F("HMS_delta_cut","HMS #delta Cut;#delta;Counts",100,-50,50);

  h1SHMS_th              = new TH1F("SHMS_th","SHMS Theta Acceptance;#theta;Counts",100,-0.1,0.1);
  h1SHMS_th_cut          = new TH1F("SHMS_th_cut","SHMS Theta Acceptance with Cut;#theta;Counts",100,-0.1,0.1);
  h1SHMS_ph              = new TH1F("SHMS_ph","SHMS Theta Acceptance;#phi;Counts",100,-0.1,0.1);
  h1SHMS_ph_cut          = new TH1F("SHMS_ph_cut","SHMS Theta Acceptance with Cut;#phi;Counts",100,-0.1,0.1);

  h1HMS_th              = new TH1F("HMS_th","HMS Theta Acceptance;#theta;Counts",100,-0.1,0.1);
  h1HMS_th_cut          = new TH1F("HMS_th_cut","HMS Theta Acceptance with Cut;#theta;Counts",100,-0.1,0.1);
  h1HMS_ph              = new TH1F("HMS_ph","HMS Theta Acceptance;#phi;Counts",100,-0.1,0.1);
  h1HMS_ph_cut          = new TH1F("HMS_ph_cut","HMS Theta Acceptance with Cut;#phi;Counts",100,-0.1,0.1);

  h1mmissK                = new TH1F("mmissK","Kaon Missing mass;Mass (GeV/c^{2});Counts",200,0.0,2.0);
  h1mmissK->Sumw2();
  h1mmissK_rand           = new TH1F("mmissK_rand","Kaon Missing mass from Random Coincidence;Mass (GeV/c^{2});Counts",200,0.8,1.4);
  // h1mmissK_rand           = new TH1F("mmissK_rand","Kaon Missing mass from Random Coincidence;Mass (GeV/c^{2});Counts",200,0.,10);
  h1mmissK_rand->Sumw2();
  h1mmissK_cut            = new TH1F("mmissK_cut","Kaon Missing mass with Cuts;Mass (GeV/c^{2});Counts",200,0.8,1.4);
  // h1mmissK_cut            = new TH1F("mmissK_cut","Kaon Missing mass with Cuts;Mass (GeV/c^{2});Counts",200,0.,10);
  h1mmissK_cut->Sumw2();
  h1mmissK_remove         = new TH1F("mmissK_remove","Kaon Missing mass with Cuts (Random Subtracted);Mass (GeV/c^{2});Counts",200,0.8,1.4);
  // h1mmissK_remove         = new TH1F("mmissK_remove","Kaon Missing mass with Cuts (Random Subtracted);Mass (GeV/c^{2});Counts",200,0.,10);
  h1mmissK_remove->Sumw2();

  ///////////////////////////////////////////////
  h2ROC1_Coin_pion_kaon = new TH2F("ROC1_Coin_pion_kaon","pi/Kaon Coincident Time vs #beta for ROC1 (w/ particle ID);Time (ns);#beta",800,-40,40,200,0.0,2.0);
  h2ROC1_Coin_pion_kaon_noID = new TH2F("ROC1_Coin_pion_kaon_noID","pi/Kaon Coincident Time vs #beta for ROC1 (w/ particle ID);Time (ns);#beta",800,-40,40,200,0.0,2.0);
  h1mmisspiK               = new TH1F("mmisspiK","Pi/k Missing mass squared;Mass^{2} (GeV/c^{2})^{2};Counts",200,0.8,1.4);
  h1mmisspiK->Sumw2();
  h1mmisspiK_rand          = new TH1F("mmisspiK_rand","Pi/k Missing mass squared from Random Coincidence;Mass^{2} (GeV/c^{2})^{2};Counts",200,0.8,1.4);
  h1mmisspiK_rand->Sumw2();
  h1mmisspiK_cut           = new TH1F("mmisspiK_cut","Pi/k Missing mass squared with Cuts;Mass^{2} (GeV/c^{2})^{2};Counts",200,0.8,1.4);
  h1mmisspiK_cut->Sumw2();
  h1mmisspiK_remove        = new TH1F("mmisspiK_remove","Pi/k Missing mass squared with Cuts (Random Subtracted);Mass^{2} (GeV/c^{2})^{2};Counts",200,0.8,1.4);
  h1mmisspiK_remove->Sumw2();
  ///////////////////////////////////////////////


  h1mmisspi               = new TH1F("mmisspi","Pion Missing mass squared;Mass^{2} (GeV/c^{2})^{2};Counts",200,0.8,1.4);
  h1mmisspi_rand          = new TH1F("mmisspi_rand","Pion Missing mass squared from Random Coincidence;Mass^{2} (GeV/c^{2})^{2};Counts",200,0.8,1.4);
  h1mmisspi_cut           = new TH1F("mmisspi_cut","Pion Missing mass squared with Cuts;Mass^{2} (GeV/c^{2})^{2};Counts",200,0.8,1.4);
  h1mmisspi_remove        = new TH1F("mmisspi_remove","Pion Missing mass squared with Cuts (Random Subtracted);Mass^{2} (GeV/c^{2})^{2};Counts",200,0.8,1.4);

  h1mmissp                = new TH1F("mmissp","Proton Missing mass squared;Mass^{2} (GeV/c^{2})^{2};Counts",200,-0.5,2.0);
  h1mmissp_rand           = new TH1F("mmissp_rand","Proton Missing mass squared from Random Coincidence;Mass^{2} (GeV/c^{2})^{2};Counts",200,-0.5,2.0);
  h1mmissp_cut            = new TH1F("mmissp_cut","Proton Missing mass squared with Cuts;Mass^{2} (GeV/c^{2})^{2};Counts",200,-0.5,2.0);
  h1mmissp_remove         = new TH1F("mmissp_remove","Proton Missing mass squared with Cuts (Random Subtracted);Mass^{2} (GeV/c^{2})^{2};Counts",200,-0.5,2.0);

  h2WvsQ2                 = new TH2F("WvsQ2","Q2 vs W;Q2;W",480,0.0,7.0,90,0.0,4.0);
  // h2WvsQ2                 = new TH2F("WvsQ2","Q2 vs W;Q2;W",480,1.5,3,90,2.5,3.5);
  // h2tvsph_q               = new TH2F("tvsph_q",";#phi;t",12,-3.14,3.14,16,0.0,0.3);
  h2tvsph_q               = new TH2F("tvsph_q",";#phi;t",12,-3.14,3.14,16,0.0,1.0);
  h1epsilon               = new TH1F("epsilon","Plot of Epsilon;#epsilon;Counts",100,0.0,1.0);

  h1EDTM                  = new TH1F("EDTM","EDTM Time;EDTM TDC Time;Counts",10000,-5000,5000);
  h1TRIG5                 = new TH1F("TRIG5","TRIG5 Time;TRIG5 TDC Time;Counts",10000,-5000,5000);

  h3SHMS_HGC              = new TH3F("SHMS_HGC","SHMS HGC Distribution of NPE in X-Y Mirror Plane;X Position (cm);Y Position (cm);NPE",100,-50,50,100,-50,50,100,0.1,35);

  GetOutputList()->Add(h1missKcut_CT);

  /**
     electron cuts for PID efficiencies
   **/

  /////////////////////////////////////
  GetOutputList()->Add(h2ROC1_Coin_Beta_noID_electron);
  GetOutputList()->Add(h2ROC1_Coin_Beta_electron);

  GetOutputList()->Add(h1massElec_noID);
  GetOutputList()->Add(h1massElec_ID);
  ////////////////////////////////////


  
  GetOutputList()->Add(h2ROC1_Coin_Beta_noID_kaon);
  GetOutputList()->Add(h2ROC1_Coin_Beta_kaon);
  GetOutputList()->Add(h2ROC1_Coin_Beta_noID_pion);
  GetOutputList()->Add(h2ROC1_Coin_Beta_pion);
  GetOutputList()->Add(h2ROC1_Coin_Beta_noID_proton);
  GetOutputList()->Add(h2ROC1_Coin_Beta_proton);
  GetOutputList()->Add(h2HMS_electron);
  GetOutputList()->Add(h2HMS_electron_cut);
  GetOutputList()->Add(h1SHMS_electron);
  GetOutputList()->Add(h1SHMS_electron_cut);
  GetOutputList()->Add(h2SHMSK_kaon);
  GetOutputList()->Add(h2SHMSK_kaon_cut);
  GetOutputList()->Add(h2SHMSK_pion);
  GetOutputList()->Add(h2SHMSK_pion_cut);
  GetOutputList()->Add(h2SHMSpi_kaon);
  GetOutputList()->Add(h2SHMSpi_kaon_cut);
  GetOutputList()->Add(h2SHMSpi_pion);
  GetOutputList()->Add(h2SHMSpi_pion_cut);
  GetOutputList()->Add(h2SHMSp_kaon);
  GetOutputList()->Add(h2SHMSp_kaon_cut);
  GetOutputList()->Add(h2SHMSp_pion);
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
  ///////////////////////////////////////////////
  GetOutputList()->Add(h2ROC1_Coin_pion_kaon);
  GetOutputList()->Add(h2ROC1_Coin_pion_kaon_noID);
  GetOutputList()->Add(h1mmisspiK);
  GetOutputList()->Add(h1mmisspiK_rand);
  GetOutputList()->Add(h1mmisspiK_cut);
  GetOutputList()->Add(h1mmisspiK_remove);
  ///////////////////////////////////////////////
  GetOutputList()->Add(h1mmisspi);
  GetOutputList()->Add(h1mmisspi_rand);
  GetOutputList()->Add(h1mmisspi_cut);
  GetOutputList()->Add(h1mmisspi_remove);
  GetOutputList()->Add(h1mmissp);
  GetOutputList()->Add(h1mmissp_rand);
  GetOutputList()->Add(h1mmissp_cut);
  GetOutputList()->Add(h1mmissp_remove);
  GetOutputList()->Add(h2WvsQ2);
  GetOutputList()->Add(h2tvsph_q);
  GetOutputList()->Add(h1epsilon);
  GetOutputList()->Add(h1EDTM);
  GetOutputList()->Add(h1TRIG5);
  GetOutputList()->Add(h3SHMS_HGC);
}

Bool_t hms_cer_efficiency::Process(Long64_t entry)
{
  // The Process() function is called for each entry in the tree (or possibly
  // keyed object in the case of PROOF) to be processed. The entry argument
  // specifies which entry in the currently loaded tree is to be processed.
  // When processing keyed objects with PROOF, the object is already loaded
  // and is available via the fObject pointer.
  //
  // This function should contain the \"body\" of the analysis. It can contain
  // simple or elaborate selection criteria, run algorithms on the data
  // of the event and typically fill histograms.
  //
  // The processing can be stopped by calling Abort().
  //
  // Use fStatus to set the return value of TTree::Process().
  //
  // The return value is currently not used.

  fReader.SetEntry(entry);

  //if (*fEvtType != 4) return kTRUE;

  h1EDTM->Fill(*pEDTM);
  //h1TRIG5->Fill(*pTRIG5);
  
  h2HMS_electron->Fill(H_cal_etotnorm[0],H_cer_npeSum[0]);
  h1SHMS_electron->Fill(P_cal_etotnorm[0]);

  h2SHMSK_kaon->Fill(P_aero_npeSum[0],P_hgcer_npeSum[0]);
  h2SHMSK_pion->Fill(P_cal_etotnorm[0],P_hgcer_npeSum[0]);
  h2SHMSpi_kaon->Fill(P_aero_npeSum[0],P_hgcer_npeSum[0]);
  h2SHMSpi_pion->Fill(P_cal_etotnorm[0],P_hgcer_npeSum[0]);
  h2SHMSp_kaon->Fill(P_aero_npeSum[0],P_hgcer_npeSum[0]);
  h2SHMSp_pion->Fill(P_cal_etotnorm[0],P_hgcer_npeSum[0]);
  
  h1SHMS_delta->Fill(P_gtr_dp[0]);
  h1HMS_delta->Fill(H_gtr_dp[0]);

  h1SHMS_th->Fill(P_gtr_th[0]);
  h1SHMS_ph->Fill(P_gtr_ph[0]);
  h1HMS_th->Fill(H_gtr_th[0]);
  h1HMS_ph->Fill(H_gtr_ph[0]);

  h1mmissK->Fill(sqrt(pow(emiss[0],2)-pow(pmiss[0],2)));
  // h1mmisspiK->Fill(sqrt(pow(emiss[0],2)-pow(pmiss[0],2)));//
  h1mmisspi->Fill(pow(emiss[0] + sqrt(pow(0.493677,2) + pow(P_gtr_p[0],2)) - sqrt(pow(0.13957018,2) + pow(P_gtr_p[0],2)),2)-pow(pmiss[0],2));
  h1mmissp->Fill(pow(emiss[0] + sqrt(pow(0.493677,2) + pow(P_gtr_p[0],2)) - sqrt(pow(0.93828,2) + pow(P_gtr_p[0],2)),2)-pow(pmiss[0],2));
  
  if (TMath::Abs(H_gtr_dp[0]) > 10.0) return kTRUE; // was 10.0
  if (P_gtr_dp[0] > 20.0 || P_gtr_dp[0] < -10.0) return kTRUE;

  if (P_cal_etotnorm[0] > 0.6) return kTRUE;
  if (abs(P_gtr_beta[0]-1.00) > 0.1) return kTRUE;

  if ( (CTime_eKCoinTime_ROC1[0] - 47.5) > -0.5 && (CTime_eKCoinTime_ROC1[0] - 47.5) < 0.5) {
    if(H_cal_etotnorm[0] > 0.995 && H_cal_etotnorm[0] < 1.015){
      h2ROC1_Coin_Beta_noID_electron->Fill((CTime_eKCoinTime_ROC1[0] - 47.5),sqrt(pow(emiss[0],2)-pow(pmiss[0],2)));
      h1massElec_noID->Fill(sqrt(pow(emiss[0],2)-pow(pmiss[0],2)));
      
      if(H_cer_npeSum[0] > 3.0){
	h2ROC1_Coin_Beta_electron->Fill((CTime_eKCoinTime_ROC1[0] - 47.5),sqrt(pow(emiss[0],2)-pow(pmiss[0],2)));
	h1massElec_ID->Fill(sqrt(pow(emiss[0],2)-pow(pmiss[0],2)));
      }
    }
  }
  
  if (TMath::Abs(P_gtr_th[0]) > 0.040) return kTRUE;
  if (TMath::Abs(P_gtr_ph[0]) > 0.024) return kTRUE;
  if (TMath::Abs(H_gtr_th[0]) > 0.080) return kTRUE;
  if (TMath::Abs(H_gtr_ph[0]) > 0.035) return kTRUE;
  
  h2HMS_electron_cut->Fill(H_cal_etotnorm[0],H_cer_npeSum[0]);
  h1SHMS_electron_cut->Fill(P_cal_etotnorm[0]);
  
  h1SHMS_delta_cut->Fill(P_gtr_dp[0]);
  h1HMS_delta_cut->Fill(H_gtr_dp[0]);

  h1SHMS_th_cut->Fill(P_gtr_th[0]);
  h1SHMS_ph_cut->Fill(P_gtr_ph[0]);
  h1HMS_th_cut->Fill(H_gtr_th[0]);
  h1HMS_ph_cut->Fill(H_gtr_ph[0]);

  ///////////////////////////////////////////////////////////////////////////////////////////////////////
  if (P_aero_npeSum[0] > 1.5 && P_hgcer_npeSum[0] < 1.5) { //Event identified as Kaon
    h2ROC1_Coin_Beta_noID_kaon->Fill((CTime_eKCoinTime_ROC1[0] - 43),P_gtr_beta[0]); 

    if (abs(P_gtr_beta[0]-1.00) > 0.1) return kTRUE;

    h1missKcut_CT->Fill( CTime_eKCoinTime_ROC1[0] - 43, sqrt(pow(emiss[0],2)-pow(pmiss[0],2)));

    if ( (CTime_eKCoinTime_ROC1[0] - 43) > -1. && (CTime_eKCoinTime_ROC1[0] - 43) < 1.) {
      h2ROC1_Coin_Beta_kaon->Fill((CTime_eKCoinTime_ROC1[0] - 43),P_gtr_beta[0]);
      h2SHMSK_kaon_cut->Fill(P_aero_npeSum[0],P_hgcer_npeSum[0]);
      h2SHMSK_pion_cut->Fill(P_cal_etotnorm[0],P_hgcer_npeSum[0]);
      h1mmissK_cut->Fill(sqrt(pow(emiss[0],2)-pow(pmiss[0],2)));

      h2WvsQ2->Fill(Q2[0],W[0]);
      h2tvsph_q->Fill(ph_q[0],-MandelT[0]);
      h1epsilon->Fill(epsilon[0]);
    }

    if ((((CTime_eKCoinTime_ROC1[0] - 43) > -21.0 && (CTime_eKCoinTime_ROC1[0] - 43) < -9.0))) {
      h1mmissK_rand->Fill(sqrt(pow(emiss[0],2)-pow(pmiss[0],2)));
      h1mmissK_remove->Fill(sqrt(pow(emiss[0],2)-pow(pmiss[0],2)));
    }

  }
  
  return kTRUE;
}

void hms_cer_efficiency::SlaveTerminate()
{
  // The SlaveTerminate() function is called after all entries or objects
  // have been processed. When running with PROOF SlaveTerminate() is called
  // on each slave server.

}

void hms_cer_efficiency::Terminate()
{

  Info("Terminate", "Outputting Good Kaon Selection");

  TString option = GetOption();

  TString foutname = Form("OUTPUTS/numEvts_PID_Run%i",option.Atoi());

  TString outputpdf = foutname + ".pdf";
  
  TCanvas *cID = new TCanvas("ID","Summary of Electron Particle PID Cuts");
  cID->Divide(2,2);
  cID->cd(1); h2ROC1_Coin_Beta_noID_electron->Draw("Colz");
  cID->cd(2); h2ROC1_Coin_Beta_electron->Draw("Colz");
  cID->Update();
  cID->cd(3); h1massElec_noID->Draw("hist");
  Int_t numEvts_noID = h1massElec_noID->GetEntries();
  cID->cd(4); h1massElec_ID->Draw("hist");
  Int_t numEvts_ID = h1massElec_ID->GetEntries();
  cID->Print(outputpdf);

  cout << numEvts_noID << endl;
  cout << numEvts_ID << endl;

  ofstream myfile;
  myfile.open ("numEvts_PID", fstream::app);
  myfile << Form("%i     %i     %i\n",
		 option.Atoi(), numEvts_noID, numEvts_ID);
  myfile.close();
  
}
