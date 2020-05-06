// 5/5/20 - Stephen Kay, University of Regina

// root .c macro plotting script, reads in desired trees from analysed root file and plots some stuff

#define PlotKaonPhysics_cxx

// Include relevant stuff
#include "PlotKaonPhysics.h"
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

void PlotKaonPhysics(string Filename = "")
{
  TString Hostname = gSystem->HostName();
  TString User = (gSystem->GetUserInfo())->fUser;
  TString Replaypath;
  TString Outpath;
  TString rootFile;
  
  // Set paths depending on system you're running on
  if(Hostname.Contains("farm")){
    Replaypath = "/group/c-kaonlt/USERS/"+User+"/hallc_replay_lt";
    Outpath = Replaypath+"/UTIL_PROTON/scripts/protonyield/OUTPUT";
  }
  else if(Hostname.Contains("qcd")){
    Replaypath = "/group/c-kaonlt/USERS/"+User+"/hallc_replay_lt";
    Outpath = Replaypath+"/UTIL_PROTON/scripts/protonyield/OUTPUT";
  }
  else if (Hostname.Contains("phys.uregina.ca")){
    Replaypath = "/home/"+User+"/work/JLab/hallc_replay_lt";
    Outpath = Replaypath+"/UTIL_PROTON/scripts/protonyield/OUTPUT";
  }
  // Add more as needed for your own envrionment

  if(Filename == "") {
    cout << "Enter a Filename to analyse: ";
    cin >> Filename;
  }  
  TString TFilename = Filename;
  rootFile = Outpath+"/"+TFilename;
  // Complain and exit if your file doesn't exist
  if (gSystem->AccessPathName(rootFile) == kTRUE){
    cerr << "!!!!! ERROR !!!!! " << endl << rootFile <<  " not found" << endl <<  "!!!!! ERRROR !!!!!" << endl;
    exit;
  }

  TFile *InFile = new TFile(rootFile, "READ");
  // This assumes a 4 digit run number! Should work for now, saves it as an additional input
  // This ALSO assumes the Filename is XXXX_..... too, which may not be true, edit as needed
  TString runNum = TFilename(0,4);
  // Establish the names of our output files quickly
  TString foutname = Outpath + "/KaonPlots_" +runNum + ".root";
  TString foutpdf =  Outpath + "/KaonPlots_" +runNum + ".pdf";
  
  TTree* Uncut = (TTree*)InFile->Get("Uncut_Kaon_Events");
  TTree* Cut_All = (TTree*)InFile->Get("Cut_Kaon_Events_All");
  TTree* Cut_Pr = (TTree*)InFile->Get("Cut_Kaon_Events_Prompt");
  TTree* Cut_Rn = (TTree*)InFile->Get("Cut_Kaon_Events_Random");

  // Define Histograms
  TH1D *h1_MM_Cut = new TH1D("h1_MM_Cut", "MM_{K} - All events after cuts; Mass (GeV/c^{2})", 300, 0.5, 2.0);
  TH1D *h1_MM_Prompt = new TH1D("h1_MM_Prompt", "MM_{K} - Prompt events after cuts; Mass (GeV/c^{2})", 300, 0.5, 2.0);
  TH1D *h1_MM_Random = new TH1D("h1_MM_Random", "MM_{K} - Random events after cuts; Mass (GeV/c^{2})", 300, 0.5, 2.0);
  TH1D *h1_MM_BGSub = new TH1D("h1_MM_BGSub", "MM_{K} - BGSub events after cuts; Mass (GeV/c^{2})", 300, 0.5, 2.0);
  TH1D *h1_CT_Cut = new TH1D("h1_CT_Cut", "Kaon CT - All events after cuts; Time (ns)", 400, 0, 100); 
  TH1D *h1_CT_Prompt = new TH1D("h1_CT_Prompt", "Kaon CT - Prompt events after cuts; Time (ns)", 400, 0, 100);
  TH1D *h1_CT_Random = new TH1D("h1_CT_Random", "Kaon CT - Random events after cuts; Time (ns)", 400, 0, 100);
  TH1D *h1_Epsilon = new TH1D("h1_Epsilon", "#epsilon - Prompt events after cuts; #epsilon", 200, 0, 1);

  TH2D *h2_WvsQ2 = new TH2D("h2_WvsQ2","Q2 vs W;Q2;W", 200, 5.0, 6.0, 200, 2.8, 3.8);
  TH2D *h2_tvsph_q = new TH2D("h2_tvsph_q",";#phi;t",12,-3.14,3.14,100,0.0,1.5); 

  TH2D *h2_CT_Beta_All = new TH2D("h2_CT_Beta_All","Kaon CT vs #beta - All events after cuts;Time (ns);#beta",400,0,100,200,0.0,2.0);
  TH2D *h2_CT_Beta_Prompt = new TH2D("h2_CT_Beta_Prompt","Kaon CT vs #beta - Prompt events after cuts;Time (ns);#beta",400,0,100,200,0.0,2.0);
  TH2D *h2_CT_Beta_Random = new TH2D("h2_CT_Beta_Random","Kaon CT vs #beta - Random events after cuts;Time (ns);#beta",400,0,100,200,0.0,2.0);

  TH2D *h2_CT_MMK_All = new TH2D("h2_CT_MMK_All","Kaon CT vs MM_{K} - All events after cuts;Time (ns);Mass (GeV/c^{2})",400,0,100,300,0.5,2);
  TH2D *h2_CT_MMK_Prompt = new TH2D("h2_CT_MMK_Prompt","Kaon CT vs MM_{K} - Prompt events after cuts;Time (ns);Mass (GeV/c^{2})",400,0,100,300,0.5,2);
  TH2D *h2_CT_MMK_Random = new TH2D("h2_CT_MMK_Random","Kaon CT vs MM_{K} - Random events after cuts;Time (ns);Mass (GeV/c^{2})",400,0,100,300,0.5,2);

  // For 1D histos, can easily create directly from the corresponding branch

  // Set branch address -> Need this to ensure event info is entangled correctly for 2D plots

  // TH1D *TestHisto = new TH1D("TestHisto", "Test histo please ignore", 400, 0, 10);
  // Cut_All->Draw("Q2 >> TestHisto");

  // TCanvas *c1 = new TCanvas("c1", "c1", 100, 0, 1000, 900);
  // TestHisto->Draw("SAME");
  // c1->Print(foutpdf);
  
}
