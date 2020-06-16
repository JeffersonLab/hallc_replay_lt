// 5/5/20 - Stephen Kay, University of Regina

// root .c macro plotting script, reads in desired trees from analysed root file and plots some stuff
// Saves  pdf file with plots and a .root file
#define PlotKaonPhysics_cxx

// Include relevant stuff
#include <TStyle.h>
#include <TCanvas.h>
#include <TLine.h>
#include <TMath.h>
#include <TPaveText.h>
#include <TGaxis.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <TSystem.h>
#include <TTree.h>
#include <TArc.h>

// Input should be the input root file name (including suffix) and an output file name string (without any suffix)
void PlotKaonPhysics(string InFilename = "", string OutFilename = "")
{
  TString Hostname = gSystem->HostName();
  TString User = (gSystem->GetUserInfo())->fUser;
  TString Replaypath;
  TString Outpath;
  TString rootFile;
  Double_t nWindows = 6;
  gStyle->SetPalette(55);

  // Set paths depending on system you're running on
  if(Hostname.Contains("farm")){
    Replaypath = "/group/c-kaonlt/USERS/"+User+"/hallc_replay_lt";
    Outpath = Replaypath+"/UTIL_KAONLT/scripts/kaonyield/OUTPUT";
  }
  else if(Hostname.Contains("qcd")){
    Replaypath = "/group/c-kaonlt/USERS/"+User+"/hallc_replay_lt";
    Outpath = Replaypath+"/UTIL_KAONLT/scripts/kaonyield/OUTPUT";
  }
  else if (Hostname.Contains("phys.uregina.ca")){
    Replaypath = "/home/"+User+"/work/JLab/hallc_replay_lt";
    Outpath = Replaypath+"/UTIL_KAONLT/scripts/kaonyield/OUTPUT";
  }
  // Add more as needed for your own envrionment

  if(InFilename == "") {
    cout << "Enter a Filename to analyse: ";
    cin >> InFilename;
  }  
  if(OutFilename == "") {
    cout << "Enter a Filename to output to: ";
    cin >> OutFilename;
  }
  TString TInFilename = InFilename;
  rootFile = Outpath+"/"+TInFilename;
  // Complain and exit if your file doesn't exist
  if (gSystem->AccessPathName(rootFile) == kTRUE){
    cerr << "!!!!! ERROR !!!!! " << endl << rootFile <<  " not found" << endl <<  "!!!!! ERRROR !!!!!" << endl;
    exit;
  }
  TFile *InFile = new TFile(rootFile, "READ");
  // This assumes a 4 digit run number! Should work for now, saves it as an additional input
  // This ALSO assumes the Filename is XXXX_..... too, which may not be true, edit as needed
  TString TOutFilename = OutFilename;
  // Establish the names of our output files quickly
  TString foutname = Outpath + "/" + TOutFilename + ".root";
  TString foutpdf = Outpath + "/" + TOutFilename + ".pdf";
  
  TTree* Uncut = (TTree*)InFile->Get("Uncut_Kaon_Events"); Long64_t nEntries_Uncut = (Long64_t)Uncut->GetEntries();
  TTree* Cut_All = (TTree*)InFile->Get("Cut_Kaon_Events_All"); Long64_t nEntries_All = (Long64_t)Cut_All->GetEntries();
  TTree* Cut_Pr = (TTree*)InFile->Get("Cut_Kaon_Events_Prompt"); Long64_t nEntries_Pr = (Long64_t)Cut_Pr->GetEntries();
  TTree* Cut_Rn = (TTree*)InFile->Get("Cut_Kaon_Events_Random"); Long64_t nEntries_Rn = (Long64_t)Cut_Rn->GetEntries();
  // Set branch address -> Need this to ensure event info is entangled correctly for 2D plots
  Double_t CT_all; Cut_All->SetBranchAddress("CTime_eKCoinTime_ROC1", &CT_all);
  Double_t CT_pr; Cut_Pr->SetBranchAddress("CTime_eKCoinTime_ROC1", &CT_pr);
  Double_t CT_rn; Cut_Rn->SetBranchAddress("CTime_eKCoinTime_ROC1", &CT_rn);
  Double_t Beta_all; Cut_All->SetBranchAddress("P_gtr_beta", &Beta_all);
  Double_t Beta_pr; Cut_Pr->SetBranchAddress("P_gtr_beta", &Beta_pr);
  Double_t Beta_rn; Cut_Rn->SetBranchAddress("P_gtr_beta", &Beta_rn);
  Double_t MMK_all; Cut_All->SetBranchAddress("MMK", &MMK_all);
  Double_t MMK_pr; Cut_Pr->SetBranchAddress("MMK", &MMK_pr);
  Double_t MMK_rn; Cut_Rn->SetBranchAddress("MMK", &MMK_rn);
  Double_t W_pr; Cut_Pr->SetBranchAddress("W", &W_pr);
  Double_t Q2_pr; Cut_Pr->SetBranchAddress("Q2", &Q2_pr);
  Double_t t_pr; Cut_Pr->SetBranchAddress("MandelT", &t_pr);
  Double_t phi_q_pr; Cut_Pr->SetBranchAddress("ph_q", &phi_q_pr);

  // Define Histograms
  TH1D *h1_MMK_All = new TH1D("h1_MMK_All", "MM_{K} - All events after cuts; Mass (GeV/c^{2})", 220, 0.5, 1.6);
  TH1D *h1_MMK_Prompt = new TH1D("h1_MMK_Prompt", "MM_{K} - Prompt events after cuts; Mass (GeV/c^{2})", 220, 0.5, 1.6);
  TH1D *h1_MMK_Random = new TH1D("h1_MMK_Random", "MM_{K} - Random events after cuts; Mass (GeV/c^{2})", 220, 0.5, 1.6);
  TH1D *h1_MMK_Random_Scaled = new TH1D("h1_MMK_Random_Scaled", "MM_{K} - Random events after cuts; Mass (GeV/c^{2})", 220, 0.5, 1.6);
  TH1D *h1_MMK_BGSub = new TH1D("h1_MMK_BGSub", "MM_{K} - BGSub events after cuts; Mass (GeV/c^{2})", 220, 0.5, 1.6);
  TH1D *h1_CT_All = new TH1D("h1_CT_All", "Kaon CT - All events after cuts; Time (ns)", 240, 10, 70); 
  TH1D *h1_CT_Prompt = new TH1D("h1_CT_Prompt", "Kaon CT - Prompt events after cuts; Time (ns)", 240, 10, 70);
  TH1D *h1_CT_Random = new TH1D("h1_CT_Random", "Kaon CT - Random events after cuts; Time (ns)", 240, 10, 70);
  TH1D *h1_Epsilon = new TH1D("h1_Epsilon", "#epsilon - Prompt events after cuts; #epsilon", 200, 0, 1);

  TH2D *h2_Q2vsW = new TH2D("h2_Q2vsW","Q2 vs W;Q2;W", 200, 3.5, 5.5, 200, 2.2, 3.2);
  TH2D *h2_phiqvst = new TH2D("h2_phiqvst",";#phi;t",12,-3.14,3.14,40,0.0,2.0); 

  TH2D *h2_CT_Beta_All = new TH2D("h2_CT_Beta_All","Kaon CT vs #beta - All events after cuts;Time (ns);#beta",240,10,70,80,0.6,1.4);
  TH2D *h2_CT_Beta_Prompt = new TH2D("h2_CT_Beta_Prompt","Kaon CT vs #beta - Prompt events after cuts;Time (ns);#beta",240,10,70,80,0.6,1.4);
  TH2D *h2_CT_Beta_Random = new TH2D("h2_CT_Beta_Random","Kaon CT vs #beta - Random events after cuts;Time (ns);#beta",240,10,70,80,0.6,1.4);

  TH2D *h2_CT_MMK_All = new TH2D("h2_CT_MMK_All","Kaon CT vs MM_{K} - All events after cuts;Time (ns);Mass (GeV/c^{2})",240,10,70,220,0.5,1.6);
  TH2D *h2_CT_MMK_Prompt = new TH2D("h2_CT_MMK_Prompt","Kaon CT vs MM_{K} - Prompt events after cuts;Time (ns);Mass (GeV/c^{2})",240,10,70,220,0.5,1.6);
  TH2D *h2_CT_MMK_Random = new TH2D("h2_CT_MMK_Random","Kaon CT vs MM_{K} - Random events after cuts;Time (ns);Mass (GeV/c^{2})",240,10,70,220,0.5,1.6);

  // For 1D histos, can easily create directly from the corresponding branch
  Cut_All->Draw("MMK >> h1_MMK_All", "", "goff");
  Cut_Pr->Draw("MMK >> h1_MMK_Prompt", "", "goff");
  Cut_Rn->Draw("MMK >> h1_MMK_Random", "", "goff");
  Cut_Rn->Draw("MMK  >> h1_MMK_Random_Scaled", "", "goff");
  Cut_All->Draw("CTime_eKCoinTime_ROC1 >> h1_CT_All", "", "goff");
  Cut_Pr->Draw("CTime_eKCoinTime_ROC1 >> h1_CT_Prompt", "", "goff");
  Cut_Rn->Draw("CTime_eKCoinTime_ROC1 >> h1_CT_Random", "", "goff");
  Cut_Pr->Draw("epsilon >> h1_Epsilon", "", "goff");
 
  h1_MMK_Random_Scaled->Scale(1.0/nWindows);
  h1_MMK_BGSub->Add(h1_MMK_Prompt, h1_MMK_Random_Scaled, 1, -1);

  // Loop over all events in tree and fill 2D histos event by event, ensures the events correctly correlate
  for(Long64_t i = 0; i < nEntries_All; i++){
    Cut_All->GetEntry(i);
    h2_CT_Beta_All->Fill(CT_all, Beta_all);
    h2_CT_MMK_All->Fill(CT_all, MMK_all);
  } 
  for(Long64_t i = 0; i < nEntries_Pr; i++){
    Cut_Pr->GetEntry(i);
    h2_CT_Beta_Prompt->Fill(CT_pr, Beta_pr);
    h2_CT_MMK_Prompt->Fill(CT_pr, MMK_pr);
    h2_Q2vsW->Fill(Q2_pr, W_pr);
    h2_phiqvst->Fill(phi_q_pr, -t_pr);
  }
  for(Long64_t i = 0; i < nEntries_Rn; i++){
    Cut_Rn->GetEntry(i);
    h2_CT_Beta_Random->Fill(CT_rn, Beta_rn);
    h2_CT_MMK_Random->Fill(CT_rn, MMK_rn);
  } 
 
  TCanvas *c_MM = new TCanvas("c_MM", "Kaon missing mass distributions", 100, 0, 1000, 900);
  c_MM->Divide(2,2);
  c_MM->cd(1);
  h1_MMK_All->Draw();
  c_MM->cd(2);
  h1_MMK_Prompt->Draw();
  c_MM->cd(3);
  h1_MMK_Random->Draw();
  c_MM->cd(4);
  h1_MMK_BGSub->Draw("HIST");
  c_MM->Print(foutpdf + '(');
  
  TCanvas *c_CT = new TCanvas("c_CT", "Kaon CT distributions", 100, 0, 1000, 900);
  c_CT->Divide(3,2);
  c_CT->cd(1);
  h1_CT_All->Draw();
  c_CT->cd(2);
  h1_CT_Prompt->Draw();
  c_CT->cd(3);
  h1_CT_Random->Draw();
  c_CT->cd(4);
  h2_CT_Beta_All->Draw("COLZ");
  c_CT->cd(5);
  h2_CT_Beta_Prompt->Draw("COLZ");
  c_CT->cd(6);
  h2_CT_Beta_Random->Draw("COLZ");
  c_CT->Print(foutpdf);

  TCanvas *c_CT2 = new TCanvas("c_CT2", "Kaon CT vs MM distributions", 100, 0, 1000, 900);
  c_CT2->Divide(1,3);
  c_CT2->cd(1);
  h2_CT_MMK_All->Draw("COLZ");
  c_CT2->cd(2);
  h2_CT_MMK_Prompt->Draw("COLZ");
  c_CT2->cd(3);
  h2_CT_MMK_Random->Draw("COLZ");
  c_CT2->Print(foutpdf);

  TCanvas *c_Kine = new TCanvas("c_Kine", "Kinematics info", 100, 0, 1000, 900);
  c_Kine->Divide(2,2);
  c_Kine->cd(1);
  h2_Q2vsW->Draw("COLZ");
  c_Kine->cd(2);
  h1_Epsilon->Draw();
  c_Kine->cd(3);
  h2_phiqvst->Draw("SURF2 POL"); 
  // Horrible block of stuff for polar plotting
  gPad->SetTheta(90); gPad->SetPhi(180);
  TPaveText *tvsphi_title = new TPaveText(0.0277092,0.89779,0.096428,0.991854,"NDC");
  tvsphi_title->AddText("-t vs #phi"); tvsphi_title->Draw();
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
  TArc *Arc[10];
  for (Int_t k = 0; k < 10; k++){
    Arc[k] = new TArc(); 
    Arc[k]->SetFillStyle(0);
    Arc[k]->SetLineWidth(2);
    Arc[k]->DrawArc(0,0,0.575*(k+1)/(10),0.,360.,"same"); 
  }
  TGaxis *tradius = new TGaxis(0,0,0.575,0,0,2.0,10,"-+"); 
  tradius->SetLineColor(2);tradius->SetLabelColor(2);tradius->Draw();
  TLine *phizero = new TLine(0,0,0.6,0); 
  phizero->SetLineColor(kBlack); phizero->SetLineWidth(2); phizero->Draw();
  c_Kine->cd(4);
  h1_MMK_BGSub->Draw("HIST");
  c_Kine->Print(foutpdf + ')');

  TFile *OutHisto_file = new TFile(foutname,"RECREATE");
  TDirectory *d_KaonAll = OutHisto_file->mkdir("All Kaon events, after cuts");
  TDirectory *d_KaonPr = OutHisto_file->mkdir("Prompt Kaon events, after cuts");
  TDirectory *d_KaonRn = OutHisto_file->mkdir("Random Kaon events, after cuts");
  TDirectory *d_Kine = OutHisto_file->mkdir("Kaon kinematics info");
  
  d_KaonAll->cd();
  h1_MMK_All->Write();
  h1_CT_All->Write();
  h2_CT_Beta_All->Write();
  h2_CT_MMK_All->Write();

  d_KaonPr->cd();
  h1_MMK_Prompt->Write();
  h1_CT_Prompt->Write();
  h2_CT_Beta_Prompt->Write();
  h2_CT_MMK_Prompt->Write();
 
  d_KaonRn->cd();
  h1_MMK_Random->Write();
  h1_CT_Random->Write();
  h2_CT_Beta_Random->Write();
  h2_CT_MMK_Random->Write();

  d_Kine->cd();
  h2_Q2vsW->Write();
  h1_Epsilon->Write();
  h2_phiqvst->Write();
  h1_MMK_BGSub->Write();

  OutHisto_file->Close();

}
