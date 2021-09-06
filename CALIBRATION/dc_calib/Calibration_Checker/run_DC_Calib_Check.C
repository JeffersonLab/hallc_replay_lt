#include <TProof.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <TSystem.h>
#include <TLegend.h>

// Stephen Kay - University of Regina - 30/03/21 - This script needs to be adjusted to be a little more resilient, need to check paths exists and so on

void run_DC_Calib_Check(Int_t RunNumber = 0, Int_t MaxEvent = 0, string Detector = "")
{
  TString Hostname = gSystem->HostName();
  TString rootFileNameString1;
  TString rootFileNameString2;
  TString Outpath;
  TString Histopath;
  // Get RunNumber, MaxEvent, and current threshold if not provided.
  if(RunNumber == 0) {
    cout << "Enter a Run Number (-1 to exit): ";
    cin >> RunNumber;
    if( RunNumber<=0 ) return;
  }
  if(MaxEvent == 0) {
    cout << "\nNumber of Events to analyze: ";
    cin >> MaxEvent;
    if(MaxEvent == 0) {
      cerr << "...Invalid entry\n";
      exit;
    }
  }
  if(Detector == "") {
    cout << "Enter a Detector (HMS or SHMS): ";
    cin >> Detector;
  }
  // Need to convert string to char* for use in form command, do via .c_str()
  if(Hostname.Contains("farm")){
    rootFileNameString1 = Form("/group/c-pionlt/USERS/${USER}/hallc_replay_lt/ROOTfiles/Calib/DC/%s_DC_Calib_Pt1_%i_%i.root", Detector.c_str(), RunNumber, MaxEvent);
    rootFileNameString2 = Form("/group/c-pionlt/USERS/${USER}/hallc_replay_lt/ROOTfiles/Calib/DC/%s_DC_Calib_Pt2_%i_%i.root", Detector.c_str(), RunNumber, MaxEvent);
    Outpath = "/group/c-pionlt/USERS/${USER}/hallc_replay_lt/OUTPUT/Calib/DC";
    Histopath = "/group/c-pionlt/USERS/${USER}/hallc_replay_lt/HISTOGRAMS/Calib/DC";
  }
  else if(Hostname.Contains("qcd")){
    rootFileNameString1 = Form("/group/c-pionlt/USERS/${USER}/hallc_replay_lt/ROOTfiles/Calib/DC/%s_DC_Calib_Pt1_%i_%i.root", Detector.c_str(), RunNumber, MaxEvent);
    rootFileNameString2 = Form("/group/c-pionlt/USERS/${USER}/hallc_replay_lt/ROOTfiles/Calib/DC/%s_DC_Calib_Pt2_%i_%i.root", Detector.c_str(), RunNumber, MaxEvent);
    Outpath = "/group/c-pionlt/USERS/${USER}/hallc_replay_lt/OUTPUT/Calib/DC";
    Histopath = "/group/c-pionlt/USERS/${USER}/hallc_replay_lt/HISTOGRAMS/Calib/DC";
  }
  else if (Hostname.Contains("phys.uregina.ca")){
    rootFileNameString1 = Form("/dsk3/${USER}/JLab/ROOTfiles/DC_Calib/%s_DC_Calib_Pt1_%i_%i.root", Detector.c_str(), RunNumber, MaxEvent);
    rootFileNameString2 = Form("/dsk3/${USER}/JLab/ROOTfiles/DC_Calib/%s_DC_Calib_Pt2_%i_%i.root", Detector.c_str(), RunNumber, MaxEvent);
    Outpath = "/dsk3/${USER}/JLab/OUTPUT/DC_Calib";
    Histopath = "/dsk3/${USER}/JLab/HISTOGRAMS/DC_Calib" ;
}
  else if (Hostname.Contains("cdaq")){
    rootFileNameString1 = Form("/home/cdaq/pionLT-2021/hallc_replay_lt/ROOTfiles/Calib/DC/%s_DC_Calib_Pt1_%i_%i.root", Detector.c_str(), RunNumber, MaxEvent);
    rootFileNameString2 = Form("/home/cdaq/pionLT-2021/hallc_replay_lt/ROOTfiles/Calib/DC/%s_DC_Calib_Pt2_%i_%i.root", Detector.c_str(), RunNumber, MaxEvent);
    Outpath = "/home/cdaq/pionLT-2021/hallc_replay_lt/OUTPUT/Calib/DC";
    Histopath = "/home/cdaq/pionLT-2021/hallc_replay_lt/HISTOGRAMS/Calib/DC";
    }

  TChain ch1("T");
  ch1.Add(rootFileNameString1);
  TChain ch2("T");
  ch2.Add(rootFileNameString2);
  TString option2 = Form("%i.%i",RunNumber, 2);
  TString option1 = Form("%i.%i",RunNumber, 1); 
  TProof *proof = TProof::Open("workers=4");  
  ch1.SetProof();
  ch2.SetProof();
  if (Detector == "HMS"){
    ch1.Process("DC_Calib_Check_HMS.C+",option1);  
    ch2.Process("DC_Calib_Check_HMS.C+",option2);
  }
  else if (Detector == "SHMS"){ 
    ch1.Process("DC_Calib_Check_SHMS.C+",option1);
    ch2.Process("DC_Calib_Check_SHMS.C+",option2);
  }
  else{
    proof->Close();
    cerr << "Error, enter HMS or SHMS as detector \n";
    exit;
  }
  proof->Close();
  
  TFile *f1 = new TFile(Histopath + Form("/%s_DCCalib_Check_Run%i_Pt1.root",Detector.c_str(), RunNumber));
  TFile *f2 = new TFile(Histopath + Form("/%s_DCCalib_Check_Run%i_Pt2.root",Detector.c_str(), RunNumber));  
  TString foutname = Outpath+Form("/%s_DC_Calib_Check_Run%i", Detector.c_str(), RunNumber);
  TString outputpdf = foutname + ".pdf";
  TString Plane[12] = {"1u1", "1u2", "1x1", "1x2", "1v1", "1v2", "2u1", "2u2", "2x1", "2x2", "2v1", "2v2"};
  TString Name;
 
  TCanvas *cDC1 = new TCanvas("DC1","Drift Chamber 1 Planes",100,0,1000,900);
  cDC1->Divide(2,3);
  cDC1->cd(1); ((TH1F*)f2->Get("1u1_DriftDistance"))->Draw();
  ((TH1F*)f1->Get("1u1_DriftDistance"))->SetLineColor(kRed);
  ((TH1F*)f1->Get("1u1_DriftDistance"))->Draw("SAME");
  TLegend *leg2 = new TLegend(0.8, 0.5, 0.95, 0.7);
  leg2->AddEntry(((TH1F*)f2->Get("1u1_DriftDistance")), "Post Calibration", "lepz");
  leg2->AddEntry(((TH1F*)f1->Get("1u1_DriftDistance")), "Pre-Calibration", "lepz");
  leg2->Draw("SAME");
  cDC1->cd(2); ((TH1F*)f2->Get("1u2_DriftDistance"))->Draw();
  ((TH1F*)f1->Get("1u2_DriftDistance"))->SetLineColor(kRed);
  ((TH1F*)f1->Get("1u2_DriftDistance"))->Draw("SAME");
  cDC1->cd(3); ((TH1F*)f2->Get("1x1_DriftDistance"))->Draw();
  ((TH1F*)f1->Get("1x1_DriftDistance"))->SetLineColor(kRed);
  ((TH1F*)f1->Get("1x1_DriftDistance"))->Draw("SAME");
  cDC1->cd(4); ((TH1F*)f2->Get("1x2_DriftDistance"))->Draw();
  ((TH1F*)f1->Get("1x2_DriftDistance"))->SetLineColor(kRed);
  ((TH1F*)f1->Get("1x2_DriftDistance"))->Draw("SAME");
  cDC1->cd(5); ((TH1F*)f2->Get("1v1_DriftDistance"))->Draw();
  ((TH1F*)f1->Get("1v1_DriftDistance"))->SetLineColor(kRed);
  ((TH1F*)f1->Get("1v1_DriftDistance"))->Draw("SAME");
  cDC1->cd(6); ((TH1F*)f2->Get("1v2_DriftDistance"))->Draw();
  ((TH1F*)f1->Get("1v2_DriftDistance"))->SetLineColor(kRed);
  ((TH1F*)f1->Get("1v2_DriftDistance"))->Draw("SAME");

  TCanvas *cDC2 = new TCanvas("DC2","Drift Chamber 2 Planes",100,0,1000,900);
  cDC2->Divide(2,3);
  cDC2->cd(1); ((TH1F*)f2->Get("2u1_DriftDistance"))->Draw();
  ((TH1F*)f1->Get("1u1_DriftDistance"))->SetLineColor(kRed);
  ((TH1F*)f1->Get("1u1_DriftDistance"))->Draw("SAME");
  leg2->Draw("SAME");
  cDC2->cd(2); ((TH1F*)f2->Get("2u2_DriftDistance"))->Draw();
  ((TH1F*)f1->Get("2u2_DriftDistance"))->SetLineColor(kRed);
  ((TH1F*)f1->Get("2u2_DriftDistance"))->Draw("SAME");
  cDC2->cd(3); ((TH1F*)f2->Get("2x1_DriftDistance"))->Draw();
  ((TH1F*)f1->Get("2x1_DriftDistance"))->SetLineColor(kRed);
  ((TH1F*)f1->Get("2x1_DriftDistance"))->Draw("SAME");
  cDC2->cd(4); ((TH1F*)f2->Get("2x2_DriftDistance"))->Draw();
  ((TH1F*)f1->Get("2x2_DriftDistance"))->SetLineColor(kRed);
  ((TH1F*)f1->Get("2x2_DriftDistance"))->Draw("SAME");
  cDC2->cd(5); ((TH1F*)f2->Get("2v1_DriftDistance"))->Draw();
  ((TH1F*)f1->Get("2v1_DriftDistance"))->SetLineColor(kRed);
  ((TH1F*)f1->Get("2v1_DriftDistance"))->Draw("SAME");
  cDC2->cd(6); ((TH1F*)f2->Get("2v2_DriftDistance"))->Draw();
  ((TH1F*)f1->Get("2v2_DriftDistance"))->SetLineColor(kRed);
  ((TH1F*)f1->Get("2v2_DriftDistance"))->Draw("SAME");
  
  TCanvas *cDC1_Res = new TCanvas("DC1_Res","Drift Chamber 1 Residuals",100,0,1000,900);
  cDC1_Res->Divide(2,3);
  for (Int_t i = 0; i < 6; i++){
    Name = "h1_"+Plane[i]+"_Residual"; 
    cDC1_Res->cd(i+1); ((TH1F*)f2->Get(Name))->Draw();
    ((TH1F*)f1->Get(Name))->SetLineColor(kRed); ((TH1F*)f1->Get(Name))->Draw("SAME");
    if(i == 0) leg2->Draw("SAME");
  }

  TCanvas *cDC2_Res = new TCanvas("DC2_Res","Drift Chamber 2 Residuals",100,0,1000,900);
  cDC2_Res->Divide(2,3);
  for (Int_t i = 0; i < 6; i++){
    Name = "h1_"+Plane[i+6]+"_Residual"; 
    cDC2_Res->cd(i+1); ((TH1F*)f2->Get(Name))->Draw();
    ((TH1F*)f1->Get(Name))->SetLineColor(kRed); ((TH1F*)f1->Get(Name))->Draw("SAME");
    if(i == 0) leg2->Draw("SAME");
  }

  TCanvas *cDC1_ResExclPl = new TCanvas("DC1_ResExclPl","Drift Chamber 1 ResidualExclPls",100,0,1000,900);
  cDC1_ResExclPl->Divide(2,3);
  for (Int_t i = 0; i < 6; i++){
    Name = "h1_ResidualExclPlane_"+Plane[i]; 
    cDC1_ResExclPl->cd(i+1); ((TH1F*)f2->Get(Name))->Draw();
    ((TH1F*)f1->Get(Name))->SetLineColor(kRed); ((TH1F*)f1->Get(Name))->Draw("SAME");
    if(i == 0) leg2->Draw("SAME");
  }

  TCanvas *cDC2_ResExclPl = new TCanvas("DC2_ResExclPl","Drift Chamber 2 ResidualExclPls",100,0,1000,900);
  cDC2_ResExclPl->Divide(2,3);
  for (Int_t i = 0; i < 6; i++){
    Name = "h1_ResidualExclPlane_"+Plane[i+6]; 
    cDC2_ResExclPl->cd(i+1); ((TH1F*)f2->Get(Name))->Draw();
    ((TH1F*)f1->Get(Name))->SetLineColor(kRed); ((TH1F*)f1->Get(Name))->Draw("SAME");
    if(i == 0) leg2->Draw("SAME");
  }
  
  cDC1->Print(outputpdf+"["); //Opens file without printing anything
  cDC1->Print(outputpdf);               
  cDC2->Print(outputpdf);               
  cDC1_Res->Print(outputpdf);
  cDC2_Res->Print(outputpdf);
  cDC1_ResExclPl->Print(outputpdf);
  cDC2_ResExclPl->Print(outputpdf);
  cDC1->Print(outputpdf+"]"); //Closes file without printing anything
  
}
