#define peepYield_cxx
// The class definition in peepYield.h has been generated automatically
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
// root> T->Process("peepYield.C")
// root> T->Process("peepYield.C","some options")
// root> T->Process("peepYield.C+")
//


#include "peepYield.h"
#include <TStyle.h>
#include <TCanvas.h>
#include <TLine.h>
#include <TMath.h>
#include <TPaveText.h>

void peepYield::Begin(TTree * /*tree*/)
{
  // The Begin() function is called at the start of the query.
  // When running with PROOF Begin() is only called on the client.
  // The tree argument is deprecated (on PROOF 0 is passed).

  TString option = GetOption();

  Info("Begin", "Starting Good particle Selection");

  
}

void peepYield::SlaveBegin(TTree * /*tree*/)
{
  // The SlaveBegin() function is called after the Begin() function.
  // When running with PROOF SlaveBegin() is called on each slave server.
  // The tree argument is deprecated (on PROOF 0 is passed).

  TString option = GetOption();

  h1misspcut_CT   = new TH2F("h1misspcut_CT","Proton Missing mass vs Coincidence Time;Time (ns);Mass (GeV/c^{2})^{2}",400,-5,5,100,0.,2.0);

  h2ROC1_Coin_Beta_noID_proton = new TH2F("ROC1_Coin_Beta_noID_proton","Proton Coincident Time vs #beta for ROC1 (no particle ID);Time (ns);#beta",800,-80,80,200,0.0,2.0);
  h2ROC1_Coin_Beta_proton = new TH2F("ROC1_Coin_Beta_proton","Proton Coincident Time vs #beta for ROC1;Time (ns);#beta",800,-80,80,200,0.0,2.0);

  h2HMS_electron        = new TH2F("HMS_electron","Normalized HMS Calorimeter Energy vs Cherenkov;Normalized Energy;CER NPE",200,0.01,1.5,60,0.1,30);
  h2HMS_electron_cut    = new TH2F("HMS_electron_cut","Normalized HMS Calorimeter Energy vs Cherenkov, Electrons Selected;Normalized Energy;CER NPE",200,0.01,1.5,60,0.0,30);

  h1SHMS_electron        = new TH1F("SHMS_electron","Normalized SHMS Calorimeter Energy;Normalized Energy;Counts",200,0.01,1.5);
  h1SHMS_electron_cut    = new TH1F("SHMS_electron_cut","Normalized SHM Calorimeter Energy, Electrons Removed;Normalized Energy;Counts",200,0.01,1.5);

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
  h1SHMS_ph              = new TH1F("SHMS_ph","SHMS Phi Acceptance;#phi;Counts",100,-0.1,0.1);
  h1SHMS_ph_cut          = new TH1F("SHMS_ph_cut","SHMS Phi Acceptance with Cut;#phi;Counts",100,-0.1,0.1);

  h1HMS_th              = new TH1F("HMS_th","HMS Theta Acceptance;#theta;Counts",100,-0.1,0.1);
  h1HMS_th_cut          = new TH1F("HMS_th_cut","HMS Theta Acceptance with Cut;#theta;Counts",100,-0.1,0.1);
  h1HMS_ph              = new TH1F("HMS_ph","HMS Phi Acceptance;#phi;Counts",100,-0.1,0.1);
  h1HMS_ph_cut          = new TH1F("HMS_ph_cut","HMS Phi Acceptance with Cut;#phi;Counts",100,-0.1,0.1);

  h1mmissp                = new TH1F("mmissp","Proton Missing Mass Squared;Mass (GeV/c^{2})^{2};Counts",200,-0.5,0.5);
  h1mmissp_rand           = new TH1F("mmissp_rand","Proton Missing Mass Squared from Random Coincidence;Mass (GeV/c^{2})^{2};Counts",200,-0.5,0.5);
  h1mmissp_cut            = new TH1F("mmissp_cut","Proton Missing Mass Squared with Cuts;Mass (GeV/c^{2})^{2};Counts",200,-0.5,0.5);
  h1mmissp_remove         = new TH1F("mmissp_remove","Proton Missing Mass Squared with Cuts (inc. Rand);Mass (GeV/c^{2})^{2};Counts",200,-0.5,0.5);

  h2WvsQ2                 = new TH2F("WvsQ2","Q^{2} vs W;Q^{2};W",400,0.0,10.0,100,0.5,2.0);
  h2tvsph_q               = new TH2F("tvsph_q",";#phi;t",25,-1.0,1.0,10,-1.0,1.0);
  h1epsilon               = new TH1F("epsilon","Plot of Epsilon;#epsilon;Counts",100,0.0,1.0);

  h1pmiss                 = new TH1F("pmiss","Plot of P_{miss};P_{miss} GeV/c;Counts",1000,-1.0,1.0);
  h1pxmiss                = new TH1F("pxmiss","Plot of P_{miss,x};P_{miss,x} GeV/c;Counts",1000,-1.0,1.0);
  h1pymiss                = new TH1F("pymiss","Plot of P_{miss,y};P_{miss,y} GeV/c;Counts",1000,-1.0,1.0);
  h1pzmiss                = new TH1F("pzmiss","Plot of P_{miss,z};P_{miss,z} GeV/c;Counts",1000,-1.0,1.0);

  ////////
  h1emiss                 = new TH1F("emiss","Plot of E_{miss};E_{miss} GeV/;Counts",1000,-1.0,1.0);
  ///////

  h1EDTM                  = new TH1F("EDTM","EDTM Time;EDTM TDC Time;Counts",10000,-5000,5000);

  GetOutputList()->Add(h1misspcut_CT);
  GetOutputList()->Add(h2ROC1_Coin_Beta_noID_proton);
  GetOutputList()->Add(h2ROC1_Coin_Beta_proton);
  GetOutputList()->Add(h2HMS_electron);
  GetOutputList()->Add(h2HMS_electron_cut);
  GetOutputList()->Add(h1SHMS_electron);
  GetOutputList()->Add(h1SHMS_electron_cut);
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
  GetOutputList()->Add(h1mmissp);
  GetOutputList()->Add(h1mmissp_rand);
  GetOutputList()->Add(h1mmissp_cut);
  GetOutputList()->Add(h1mmissp_remove);
  GetOutputList()->Add(h2WvsQ2);
  GetOutputList()->Add(h2tvsph_q);
  GetOutputList()->Add(h1epsilon);
  GetOutputList()->Add(h1pmiss);
  GetOutputList()->Add(h1pxmiss);
  GetOutputList()->Add(h1pymiss);
  GetOutputList()->Add(h1pzmiss);
  GetOutputList()->Add(h1EDTM);
  /////
  GetOutputList()->Add(h1emiss);
  /////
}

Bool_t peepYield::Process(Long64_t entry)
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
  
  h2HMS_electron->Fill(H_cal_etotnorm[0],H_cer_npeSum[0]);
  h1SHMS_electron->Fill(P_cal_etotnorm[0]);

  h2SHMSp_kaon->Fill(P_aero_npeSum[0],P_hgcer_npeSum[0]);
  h2SHMSp_pion->Fill(P_cal_etotnorm[0],P_hgcer_npeSum[0]);
  
  h1SHMS_delta->Fill(P_gtr_dp[0]);
  h1HMS_delta->Fill(H_gtr_dp[0]);

  h1SHMS_th->Fill(P_gtr_th[0]);
  h1SHMS_ph->Fill(P_gtr_ph[0]);
  h1HMS_th->Fill(H_gtr_th[0]);
  h1HMS_ph->Fill(H_gtr_ph[0]);

  h1mmissp->Fill(sqrt(pow(emiss[0],2)-pow(pmiss[0],2)));

  if (H_cal_etotnorm[0] < 0.7 || H_cer_npeSum[0] < 1.5) return kTRUE;
  // if (H_cal_etotnorm[0] < 0.9 || H_cer_npeSum[0] < 1.5) return kTRUE;
  if (P_cal_etotnorm[0] > 0.6) return kTRUE;

  if (TMath::Abs(H_gtr_dp[0]) > 10.0) return kTRUE;
  if (P_gtr_dp[0] > 20.0 || P_gtr_dp[0] < -10.0) return kTRUE;
  // if (P_gtr_dp[0] > 10.0 || P_gtr_dp[0] < -22.0) return kTRUE;

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

  if (P_aero_npeSum[0] < 1.5 && P_hgcer_npeSum[0] < 1.5) { //Event identified as Proton
    h2ROC1_Coin_Beta_noID_proton->Fill((CTime_epCoinTime_ROC1[0] - 43.5),P_gtr_beta[0]);
    
    if (abs(P_gtr_beta[0]-1.00) > 0.15) return kTRUE;

    h1misspcut_CT->Fill( CTime_epCoinTime_ROC1[0] - 43.5, sqrt(pow(emiss[0],2)-pow(pmiss[0],2)));

    if (abs((CTime_epCoinTime_ROC1[0] - 43.5)) < 2.0) {
      h2ROC1_Coin_Beta_proton->Fill((CTime_epCoinTime_ROC1[0] - 43.5),P_gtr_beta[0]);
      h2SHMSp_kaon_cut->Fill(P_aero_npeSum[0],P_hgcer_npeSum[0]);
      h2SHMSp_pion_cut->Fill(P_cal_etotnorm[0],P_hgcer_npeSum[0]);
      h1mmissp_cut->Fill(pow(emiss[0],2)-pow(pmiss[0],2));

      h2WvsQ2->Fill(Q2[0],W[0]);
      h2tvsph_q->Fill(ph_q[0],-MandelT[0]);
      h1epsilon->Fill(epsilon[0]);

      h1pmiss->Fill(pmiss[0]);
      h1pxmiss->Fill(pmiss_x[0]);
      h1pymiss->Fill(pmiss_y[0]);
      h1pzmiss->Fill(pmiss_z[0]);
      /////
      h1emiss->Fill(emiss[0]);
      /////
   }

    //if (abs((CTime_epCoinTime_ROC1[0] - 43.5)) > 20.5 && abs((CTime_epCoinTime_ROC1[0] - 43.5)) < 21.5) {
    if (abs((CTime_epCoinTime_ROC1[0] - 43.5)) > 3.0 && abs((CTime_epCoinTime_ROC1[0] - 43.5)) < 25.0) {
      h1mmissp_rand->Fill(pow(emiss[0],2)-pow(pmiss[0],2));
      h1mmissp_remove->Fill(pow(emiss[0],2)-pow(pmiss[0],2));

    }
  }

  return kTRUE;
}

void peepYield::SlaveTerminate()
{
  // The SlaveTerminate() function is called after all entries or objects
  // have been processed. When running with PROOF SlaveTerminate() is called
  // on each slave server.

}

void peepYield::Terminate()
{
  // The Terminate() function is the last function to be called during
  // a query. It always runs on the client, it can be used to present
  // the results graphically or save the results to file.

  Info("Terminate", "Outputting Good Kaon Selection");

  TString option = GetOption();

  TH1F* EDTM = dynamic_cast<TH1F*> (GetOutputList()->FindObject("EDTM"));
  TH2F* HMS_electron = dynamic_cast<TH2F*> (GetOutputList()->FindObject("HMS_electron"));
  TH2F* HMS_electron_cut = dynamic_cast<TH2F*> (GetOutputList()->FindObject("HMS_electron_cut"));

  //Perform Random Subtraction
  h1mmissp_rand->Scale(1/11);
  h1mmissp_remove->Add(h1mmissp_cut,h1mmissp_rand,1,-1);

  //Perform Background Subtraction

  //Fit the Lambda Missing Mass
  
  TF1 *Lambda_Fit = new TF1("Lambda_Fit","[0]*exp(-0.5*((x-[1])/[2])*((x-[1])/[2]))",-0.5,0.5);
  Lambda_Fit->SetParName(0,"Amplitude");
  Lambda_Fit->SetParName(1,"Mean");
  Lambda_Fit->SetParName(2,"Sigma");
  Lambda_Fit->SetParLimits(0,0.0,10000.0);
  Lambda_Fit->SetParLimits(1,-0.5,0.5);
  Lambda_Fit->SetParLimits(2,0.0,0.1);
  Lambda_Fit->SetParameter(0,100);
  Lambda_Fit->SetParameter(1,0.0);
  Lambda_Fit->SetParameter(2,0.011);
  h1mmissp_remove->Fit("Lambda_Fit","RMQN");
  TF1 *Lambda_Fit_Full = new TF1("Lambda_Fit_Full","[0]*exp(-0.5*((x-[1])/[2])*((x-[1])/[2]))",-0.5,0.5);
  Lambda_Fit_Full->SetParName(0,"Amplitude");
  Lambda_Fit_Full->SetParName(1,"Mean");
  Lambda_Fit_Full->SetParName(2,"Sigma");
  Lambda_Fit_Full->SetParameter(0,Lambda_Fit->GetParameter(0));
  Lambda_Fit_Full->SetParameter(1,Lambda_Fit->GetParameter(1));
  Lambda_Fit_Full->SetParameter(2,Lambda_Fit->GetParameter(2));
  

  
  //Start of Canvas Painting
  
  TCanvas *cCuts = new TCanvas("Cuts","Summary of Common Cuts");
  cCuts->Divide(2,4);
  cCuts->cd(1); h1HMS_delta->Draw();
  cCuts->cd(2); h1HMS_delta_cut->Draw();
  cCuts->cd(3); h1SHMS_delta->Draw();
  cCuts->cd(4); h1SHMS_delta_cut->Draw();
  // cCuts->cd(5); h1HMS_electron->Draw();
  // cCuts->cd(6); h1HMS_electron_cut->Draw();
  // cCuts->cd(7); h1SHMS_electron->Draw();
  // cCuts->cd(8); h1SHMS_electron_cut->Draw();

  TCanvas *cCoinTime = new TCanvas("cCoinTime","Summary of Coincidence Time and Random Coincidence");
  cCoinTime->Divide(2,2);
  cCoinTime->cd(1);
  h1mmissp_cut->Draw();
  h1mmissp_rand->Draw("same");
  h1mmissp_rand->SetLineColor(2);
  cCoinTime->cd(2);
  h1mmissp_rand->Draw();
  cCoinTime->cd(3);
  h1mmissp_remove->Draw();
  cCoinTime->cd(4);
  h1misspcut_CT->Draw("COLZ");

  TCanvas *cAngles = new TCanvas("Angles","Summary of Angular Cuts");
  cAngles->Divide(2,4);
  cAngles->cd(1); h1HMS_th->Draw();
  cAngles->cd(2); h1HMS_th_cut->Draw();
  cAngles->cd(3); h1HMS_ph->Draw();
  cAngles->cd(4); h1HMS_ph_cut->Draw();
  cAngles->cd(5); h1SHMS_th->Draw();
  cAngles->cd(6); h1SHMS_th_cut->Draw();
  cAngles->cd(7); h1SHMS_ph->Draw();
  cAngles->cd(8); h1SHMS_ph_cut->Draw();
  
  TCanvas *cRand = new TCanvas("Rand","Summary of Random Correction");
  cRand->Divide(1,3);
  cRand->cd(1); h1mmissp_cut->Draw(); h1mmissp_cut->SetTitleOffset(1.0,"Y");
  cRand->cd(2); h1mmissp_rand->Draw("hist"); h1mmissp_rand->SetTitleOffset(1.0,"Y");
  cRand->cd(3); h1mmissp_remove->Draw("hist");

  //tcanvas *cBack = new TCanvas("Back","Summary of Background Removal");
  //cBack->Divide(2,1);
  //cBack->cd(1); h1mmissK_remove->Draw("hist");
  //Back_Fit->Draw("same");
  //cBack->cd(2); h1mmissK_noback->Draw("hist");

  TCanvas *cpID = new TCanvas("pID","Summary of Proton Particle ID Cuts");
  cpID->Divide(2,4);
  cpID->cd(1); h2SHMSp_kaon->Draw("Colz");
  cpID->cd(2); h2SHMSp_kaon_cut->Draw("Colz");
  cpID->cd(3); h2SHMSp_pion->Draw("Colz");
  cpID->cd(4); h2SHMSp_pion_cut->Draw("Colz");
  cpID->cd(5); h2ROC1_Coin_Beta_noID_proton->Draw("Colz");
  TLine *LowerRand = new TLine(3.0,0.0,3.0,2.0);
  LowerRand->SetLineColor(kRed); LowerRand->SetLineWidth(1); LowerRand->Draw(); 
  TLine *UpperRand = new TLine(15.0,0.0,15.0,2.0);
  UpperRand->SetLineColor(kRed); UpperRand->SetLineWidth(1); UpperRand->Draw();
  cpID->cd(6); h2ROC1_Coin_Beta_proton->Draw("Colz");
  cpID->cd(7); h1mmissp->Draw();
  cpID->cd(8); h1mmissp_remove->Draw("hist");

  TString foutname = Form("../OUTPUT/Kinematics_Run%i",option.Atoi());
  TString outputpdf = foutname + ".pdf";

  TCanvas *cKine = new TCanvas("Kine","Summary of Higher Order Kinemaics");
  cKine->Divide(2,2);
  cKine->cd(1); h2WvsQ2->Draw("Colz"); 
  h2WvsQ2->SetTitleOffset(1.0,"Y");
  cKine->cd(3); h2tvsph_q->Draw("SURF1 POL");
  gPad->SetTheta(90); gPad->SetPhi(180);
  TPaveText *tvsphi_title = new TPaveText(0.0277092,0.89779,0.096428,0.991854,"NDC");
  tvsphi_title->AddText("t vs #phi"); tvsphi_title->Draw();
  TLine *phizero = new TLine(0,0,1,0); 
  phizero->SetLineColor(kBlack); phizero->SetLineWidth(2); phizero->Draw();  
  TPaveText *ptphizero = new TPaveText(0.923951,0.513932,0.993778,0.574551,"NDC");
  ptphizero->AddText("#phi = 0"); ptphizero->Draw();
  TLine *phihalfpi = new TLine(0,0,0,1); 
  phihalfpi->SetLineColor(kBlack); phihalfpi->SetLineWidth(2); phihalfpi->Draw();  
  TPaveText *ptphihalfpi = new TPaveText(0.417855,0.901876,0.486574,0.996358,"NDC");
  ptphihalfpi->AddText("#phi = #frac{#pi}{2}"); ptphihalfpi->Draw();
  TLine *phipi = new TLine(0,0,-1,0); 
  phipi->SetLineColor(kBlack); phipi->SetLineWidth(2); phipi->Draw();  
  TPaveText *ptphipi = new TPaveText(0.0277092,0.514217,0.096428,0.572746,"NDC");
  ptphipi->AddText("#phi = #pi"); ptphipi->Draw();
  TLine *phithreepi = new TLine(0,0,0,-1); 
  phithreepi->SetLineColor(kBlack); phithreepi->SetLineWidth(2); phithreepi->Draw();  
  TPaveText *ptphithreepi = new TPaveText(0.419517,0.00514928,0.487128,0.0996315,"NDC");
  ptphithreepi->AddText("#phi = #frac{3#pi}{2}"); ptphithreepi->Draw();
  cKine->cd(2); h1epsilon->Draw();
  h1epsilon->SetTitleOffset(1.0,"Y");
  cKine->cd(4); h1mmissp_remove->Draw("hist");
  cKine->Update();
  h1mmissp_remove->SetTitleOffset(1.0,"Y"); h1mmissp_remove->SetAxisRange(0.0,gPad->GetUymax(),"Y");
  cKine->Update();
  TLine *MissMass_Full = new TLine(0.0,gPad->GetUymin(),0.0,gPad->GetUymax()); 
  MissMass_Full->SetLineColor(kBlack); MissMass_Full->SetLineWidth(3);
  MissMass_Full->Draw();
  TPaveText *ptProtonEvt = new TPaveText(0.527698,0.652567,0.738421,0.791456,"NDC");
  ptProtonEvt->AddText(Form("# of proton Events: %.0f",h1mmissp_remove->Integral(h1mmissp_remove->GetXaxis()->FindBin(-0.02),h1mmissp_remove->GetXaxis()->FindBin(0.05))));
  ptProtonEvt->Draw();

  cKine->Print(outputpdf + '(');

  TCanvas *cMomentum = new TCanvas("Momentum","Summary of Momentum Quantities");
  cMomentum->Divide(2,2);
  cMomentum->cd(1); h1pmiss->Draw();
  cMomentum->cd(2); h1pxmiss->Draw();
  cMomentum->cd(3); h1pymiss->Draw();
  cMomentum->cd(4); h1pzmiss->Draw();
  
  cMomentum->Print(outputpdf + ')');
  //Start output of .root file with all histograms

  TFile *Histogram_file = new TFile(Form("../../HISTOGRAMS/KaonLT_Run%i.root",option.Atoi()),"RECREATE");
  TDirectory *DCuts = Histogram_file->mkdir("Spectrometer Delta and Calorimeter Cuts"); DCuts->cd();
  h1HMS_delta->Write("HMS Delta Before Cuts"); h1HMS_delta_cut->Write("HMS Delta After Cuts");
  h1SHMS_delta->Write("SHMS Delta Before Cuts"); h1SHMS_delta_cut->Write("SHMS Delta After Cuts");
  HMS_electron->Write("HMS Calorimeter Before Cuts"); HMS_electron_cut->Write("HMS Calorimeter After Cuts");
  h1SHMS_electron->Write("SHMS Calorimeter Before Cuts"); h1SHMS_electron_cut->Write("SHMS Calorimeter After Cuts");

  TDirectory *DAngles = Histogram_file->mkdir("Spectrometer Angular Cuts"); DAngles->cd();
  h1HMS_th->Write("HMS Theta Before Cuts"); h1HMS_th_cut->Write("HMS Theta After Cuts");
  h1SHMS_th->Write("SHMS Theta Before Cuts"); h1SHMS_th_cut->Write("SHMS Theta After Cuts");
  h1HMS_ph->Write("HMS Phi Before Cuts"); h1HMS_ph_cut->Write("HMS Phi After Cuts");
  h1SHMS_ph->Write("SHMS Phi Before Cuts"); h1SHMS_ph_cut->Write("SHMS Phi After Cuts");

  TDirectory *DRand = Histogram_file->mkdir("Random Subtraction Summary"); DRand->cd();
  h1mmissp_cut->Write("Proton Missing Mass, with Randoms");
  h1mmissp_rand->Write("Proton Missing Mass, only Randoms");
  h1mmissp_remove->Write("Proton Missing Mass, Randoms Removed");

  TDirectory *DProton = Histogram_file->mkdir("Proton Identification Summary"); DProton->cd();
  h2SHMSp_kaon->Write("SHMS HGC vs Aerogel, no cuts");
  h2SHMSp_kaon_cut->Write("SHMS HGC vs Aerogel, with cuts");
  h2SHMSp_pion->Write("SHMS HGC vs NGC, no cuts");
  h2SHMSp_pion_cut->Write("SHMS HGC vs NGC, with cuts");
  h2ROC1_Coin_Beta_noID_proton->Write("Proton-Electron Coincidence Time, no cuts");
  h2ROC1_Coin_Beta_proton->Write("Proton-Electron Coincidence Time, with cuts");
  h1mmissp->Write("Proton Missing Mass, no cuts");
  h1mmissp_remove->Write("Proton Missing Mass, with cuts");

  TDirectory *DKine = Histogram_file->mkdir("Higher Order Kinematics Summary"); DKine->cd();
  h2WvsQ2->Write("W vs Q2");
  h2tvsph_q->Write("t vs phi");
  h1epsilon->Write("epsilon");
  h1mmissp_remove->Write("Kaon Missing Mass, with cuts");

  TDirectory *DMomentum = Histogram_file->mkdir("Missing Momentum Summary"); DMomentum->cd();
  h1pmiss->Write("Missing Momentum");
  h1pxmiss->Write("Missing Momentum x");
  h1pymiss->Write("Missing Momentum y");
  h1pzmiss->Write("Missing Momentum z");
  //////
  h1emiss->Write("Missing energy");
  //////
  TDirectory *DEDTM = Histogram_file->mkdir("Accepted EDTM Events"); DEDTM->cd();
  EDTM->Write("EDTM TDC Time");
  Histogram_file->Close();
  
  //cout << Form("Number of good kaon events: %.0f +/- %.0f\n",200*Lambda_Fit_Full->Integral(1.0,1.25),sqrt(200*Lambda_Fit_Full->Integral(1.0,1.25)));

  // values for controlling format
  /*
  const string sep = "	" ;
  const int total_width = 154;
  const string line = sep + string( total_width-1, '-' ) + '|' ;

  ofstream myfile1;
  myfile1.open ("kaonyieldVar", fstream::app);
  myfile1 << Form("%.0f     %.0f     %.0f     ", 200*Lambda_Fit_Full->Integral(1.0,1.25), sqrt(200*Lambda_Fit_Full->Integral(1.0,1.25)), EDTM->GetEntries());
  myfile1.close();*/
}
