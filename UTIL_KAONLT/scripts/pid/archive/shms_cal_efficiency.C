#define shms_cal_efficiency_cxx
// The class definition in shms_cal_efficiency.h has been generated automatically
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
// root> T->Process("shms_cal_efficiency.C")
// root> T->Process("shms_cal_efficiency.C","some options")
// root> T->Process("shms_cal_efficiency.C+")
//


#include "shms_cal_efficiency.h"
#include <TStyle.h>
#include <TCanvas.h>
#include <TLine.h>
#include <TMath.h>
#include <TPaveText.h>

void shms_cal_efficiency::Begin(TTree * /*tree*/)
{
  // The Begin() function is called at the start of the query.
  // When running with PROOF Begin() is only called on the client.
  // The tree argument is deprecated (on PROOF 0 is passed).

  TString option = GetOption();

  Info("Begin", "Starting Good particle Selection");

  
}

void shms_cal_efficiency::SlaveBegin(TTree * /*tree*/)
{
  // The SlaveBegin() function is called after the Begin() function.
  // When running with PROOF SlaveBegin() is called on each slave server.
  // The tree argument is deprecated (on PROOF 0 is passed).

  TString option = GetOption();

  h1missKcut_CT   = new TH2F("h1missKcut_CT","Kaon Missing mass vs Coincidence Time;Time (ns);Mass (GeV/c^{2})^{2}",400,-10,10,100,0.8,1.4);

  // h2ROC1_Coin_Beta_noID_electron = new TH2F("ROC1_Coin_Beta_noCut_electron","Electron Coincident Time vs #beta for ROC1 (w/ particle ID);Time (ns);#beta",800,-40,40,200,0.0,2.0);
  // h2ROC1_Coin_Beta_electron = new TH2F("ROC1_Coin_Beta_electron","Electron Coincident Time vs #beta for ROC1;Time (ns);#beta",800,-40,40,200,0.0,2.0);
  h2ROC1_Coin_Beta_noID_electron = new TH2F("ROC1_Coin_Beta_noCut_electron","Electron Coincident Time vs Mass (GeV/c^{2}) for ROC1 (w/out Calorimeter cuts);Time (ns);Mass (GeV/c^{2})",800,-5,5,200,0.0,2.0);
  h2ROC1_Coin_Beta_electron = new TH2F("ROC1_Coin_Beta_electron","Electron Coincident Time vs Mass (GeV/c^{2}) for ROC1 (w/ Calorimeter cuts);Time (ns);Mass (GeV/c^{2})",800,-5,5,200,0.0,2.0);
  
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

  GetOutputList()->Add(h2ROC1_Coin_Beta_noID_electron);
  GetOutputList()->Add(h2ROC1_Coin_Beta_electron);
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

Bool_t shms_cal_efficiency::Process(Long64_t entry)
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

  if (TMath::Abs(H_gtr_dp[0]) > 10.0) return kTRUE;
  if (P_gtr_dp[0] > 20.0 || P_gtr_dp[0] < -10.0) return kTRUE;
  
  if (H_cal_etotnorm[0] < 0.7 || H_cer_npeSum[0] < 1.5) return kTRUE;

  if(P_aero_npeSum[0] > 1.5 || P_hgcer_npeSum[0] > 1.5){
    h2ROC1_Coin_Beta_noID_electron->Fill((CTime_eKCoinTime_ROC1[0] - 47.5),sqrt(pow(emiss[0],2)-pow(pmiss[0],2)));
  }

  if(P_cal_etotnorm[0] > 0.7 || P_hgcer_npeSum[0] > 1.5 || P_aero_npeSum[0] > 1.5){
    h2ROC1_Coin_Beta_electron->Fill((CTime_eKCoinTime_ROC1[0] - 47.5),sqrt(pow(emiss[0],2)-pow(pmiss[0],2)));
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

void shms_cal_efficiency::SlaveTerminate()
{
  // The SlaveTerminate() function is called after all entries or objects
  // have been processed. When running with PROOF SlaveTerminate() is called
  // on each slave server.

}

void shms_cal_efficiency::Terminate()
{

  Info("Terminate", "Outputting Good Kaon Selection");

  TString option = GetOption();

  /*TH3F* SHMS_HGC = dynamic_cast<TH3F*> (GetOutputList()->FindObject("SHMS_HGC"));
  TProfile2D *SHMS_HGC_pyx = new TProfile2D("SHMS_HGC_pyx","Profile of NPE in SHMS HGC;X Position (cm);Y Position (cm)",100,-50,50,100,-50,50,0.1,35);
  SHMS_HGC->Project3DProfile("yx");*/
  TH1F* EDTM = dynamic_cast<TH1F*> (GetOutputList()->FindObject("EDTM"));
  TH2F* HMS_electron = dynamic_cast<TH2F*> (GetOutputList()->FindObject("HMS_electron"));
  TH2F* HMS_electron_cut = dynamic_cast<TH2F*> (GetOutputList()->FindObject("HMS_electron_cut"));


  //Perform Random Subtraction
  //h1mmissK_rand->Scale(0.725/7.0);
  h1mmissK_rand->Scale(1./12);
  // h1mmisspiK_rand->Scale(1./3.);//
  h1mmisspi_rand->Scale(1.25/7.0);
  h1mmissp_rand->Scale(1.25/7.0);
  h1mmissK_remove->Add(h1mmissK_cut,h1mmissK_rand,1,-1);
  // h1mmisspiK_remove->Add(h1mmisspiK_cut,h1mmisspiK_rand,1,-1);//
  h1mmisspi_remove->Add(h1mmisspi_cut,h1mmisspi_rand,1,-1);
  h1mmissp_remove->Add(h1mmissp_cut,h1mmissp_rand,1,-1);

  //Perform Background Subtraction
  /*TF1 *Back_Fit = new TF1("Back_Fit","[0]*exp(-0.5*((x-[1])/[2])*((x-[1])/[2]))",1.3,1.8);
  Back_Fit->SetParName(0,"Amplitude");
  Back_Fit->SetParName(1,"Mean");
  Back_Fit->SetParName(2,"Sigma");
  Back_Fit->SetParLimits(0,0.0,10000.0);
  Back_Fit->SetParLimits(1,1.3,1.8);
  Back_Fit->SetParLimits(2,0.0,1.0);
  Back_Fit->SetParameter(0,20);
  Back_Fit->SetParameter(1,1.44);
  Back_Fit->SetParameter(2,0.16);*/
  
  //TF1 *Back_Fit = new TF1("Back_Fit","[A] + [B]*x + [C]*pow(x,2)",1.07,1.15);
  TF1 *Back_Fit = new TF1("Back_Fit","[A] + [B]*x",1.05,1.18);
  //Back_Fit->FixParameter(1,0);
  h1mmissK_remove->Fit("Back_Fit","RMQN");
  
  //TF1 *GausBack = new TF1("GausBack","[Constant]*exp(-0.5*((x-[Mean])/[Sigma])*((x-[Mean])/[Sigma])) + [A] + [B]*x + [C]*pow(x,2)",1.07,1.15);
  TF1 *GausBack = new TF1("GausBack","[Constant]*exp(-0.5*((x-[Mean])/[Sigma])*((x-[Mean])/[Sigma])) + [A] + [B]*x",1.05,1.18);
  //TF1 *GausBack = new TF1("GausBack","[0]*TMath::Landau(x,[1],[2]) + [A] + [B]*x",1.05,1.18);
  GausBack->FixParameter(0,Back_Fit->GetParameter(0));
  GausBack->FixParameter(1,Back_Fit->GetParameter(1));  
  GausBack->SetParameter(2,500);
  GausBack->SetParameter(3,1.12);
  GausBack->SetParameter(4,0.004);
  GausBack->SetParLimits(2,0,5000);
  GausBack->SetParLimits(3,1.10,1.13);
  GausBack->SetParLimits(4,0.001,0.01);
  h1mmissK_remove->Fit("GausBack","RMQN");

  TF1 *Gauss_Fit = new TF1("Gauss_Fit","[Constant]*exp(-0.5*((x-[Mean])/[Sigma])*((x-[Mean])/[Sigma]))",1.0,1.2);
  //TF1 *Gauss_Fit = new TF1("Gauss_Fit","[0]*TMath::Landau(x,[1],[2])",1.0,1.2);
  Gauss_Fit->FixParameter(0,GausBack->GetParameter(2));
  Gauss_Fit->FixParameter(1,GausBack->GetParameter(3));
  Gauss_Fit->FixParameter(2,GausBack->GetParameter(4));

  TH1F *h1mmissK_noback = (TH1F*) h1mmissK_remove->Clone();
  h1mmissK_noback->Add(Back_Fit,-1);

  //Fit the Lambda Missing Mass
  TF1 *Lambda_Fit = new TF1("Lambda_Fit","[0]*exp(-0.5*((x-[1])/[2])*((x-[1])/[2]))",1.105,1.15);
  // TF1 *Lambda_Fit = new TF1("Lambda_Fit","[0]*TMath::Landau(x,[1],[2])",1.105,1.15);
  Lambda_Fit->SetParName(0,"Amplitude");
  Lambda_Fit->SetParName(1,"Mean");
  Lambda_Fit->SetParName(2,"Sigma");
  Lambda_Fit->SetParLimits(0,0.0,10000.0);
  Lambda_Fit->SetParLimits(1,1.10,1.15);
  Lambda_Fit->SetParLimits(2,0.0,0.1);
  Lambda_Fit->SetParameter(0,100);
  Lambda_Fit->SetParameter(1,1.1075);
  Lambda_Fit->SetParameter(2,0.011);
  h1mmissK_remove->Fit("Lambda_Fit","RMQN");

  TF1 *Lambda_Fit_Full = new TF1("Lambda_Fit_Full","[0]*exp(-0.5*((x-[1])/[2])*((x-[1])/[2]))",1.0,1.25);
  // TF1 *Lambda_Fit_Full = new TF1("Lambda_Fit_Full","[0]*TMath::Landau(x,[1],[2])",1.0,1.25);
  Lambda_Fit_Full->SetParName(0,"Amplitude");
  Lambda_Fit_Full->SetParName(1,"Mean");
  Lambda_Fit_Full->SetParName(2,"Sigma");
  Lambda_Fit_Full->SetParameter(0,Lambda_Fit->GetParameter(0));
  Lambda_Fit_Full->SetParameter(1,Lambda_Fit->GetParameter(1));
  Lambda_Fit_Full->SetParameter(2,Lambda_Fit->GetParameter(2));

  //Int_t current = 35;
  TString foutname = Form("../OUTPUT/Kinematics_Run%i",option.Atoi());
  // TString foutname = "../OUTPUT/Kinematics_1uA_allPlots";

  TString outputpdf = foutname + ".pdf";


  TCanvas *cID = new TCanvas("ID","Summary of Electron Particle ID Cuts");
  cID->Divide(1,2);
  cID->cd(1); h2ROC1_Coin_Beta_noID_electron->Draw("Colz");
  cID->cd(2); h2ROC1_Coin_Beta_electron->Draw("Colz");
  cID->Update();
  cID->Print(outputpdf);
  

}
