#include <TStyle.h>
#include <TLine.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TF1.h>
#include "THcPShowerCalib.h"

//
// A steering Root script for the SHMS calorimeter calibration.
//

void pcal_calib(string Prefix, int RunNumber, int nstop=-1, int nstart=0) {

  // Initialize the analysis clock
  clock_t t = clock();
   
  cout << "Calibrating file is the following: " << Prefix << "_" << RunNumber << "_" << nstop <<  ".root, events "
       << nstart << " -- " << nstop << endl;

  
  THcPShowerCalib theShowerCalib(Prefix, RunNumber, nstart, nstop);

  theShowerCalib.ReadThresholds();  // Read in threshold param-s and intial gains
  
  theShowerCalib.Init();            // Initialize constants and variables
  theShowerCalib.CalcThresholds();  // Thresholds on the uncalibrated Edep/P
  theShowerCalib.ComposeVMs();      // Compute vectors amd matrices for calib.
  theShowerCalib.SolveAlphas();     // Solve for the calibration constants
  theShowerCalib.SaveAlphas();      // Save the constants
  //theShowerCalib.SaveRawData();   // Save raw data into file for debuging
  theShowerCalib.FillHEcal();       // Fill histograms
  theShowerCalib.fillHits();       // Fill hits
  theShowerCalib.fillCutBranch();       // Fill hits

  // Plot histograms
  
  TCanvas* Canvas =
    new TCanvas("Canvas", "PHMS Shower Counter calibration", 1000, 667);
  Canvas->Divide(3,2);

  Canvas->cd(1);

  // Normalized uncalibrated energy deposition.

  theShowerCalib.hEunc->DrawCopy();
  
  theShowerCalib.hEuncSel->SetFillColor(kGreen);
  theShowerCalib.hEuncSel->DrawCopy("same");

  Canvas->cd(2);
  theShowerCalib.hESHvsEPR->Draw("colz");

  // Normalized energy deposition after calibration.

  Canvas->cd(4);
  gStyle->SetOptFit();

  theShowerCalib.hEcal->Fit("gaus","O","",0.5,1.5);
  TF1 *fit = theShowerCalib.hEcal->GetFunction("gaus");
  Double_t gmean  = fit->GetParameter(1);
  Double_t gsigma = fit->GetParameter(2);
  double gLoThr = gmean - 2.*gsigma;
  double gHiThr = gmean + 2.*gsigma;
  cout << "gLoThr=" << gLoThr << "  gHiThr=" << gHiThr << endl;
  theShowerCalib.hEcal->Fit("gaus","","",gLoThr,gHiThr);

  theShowerCalib.hEcal->GetFunction("gaus")->SetLineColor(2);
  theShowerCalib.hEcal->GetFunction("gaus")->SetLineWidth(1);
  theShowerCalib.hEcal->GetFunction("gaus")->SetLineStyle(1);

  // SHMS delta(P) versus the calibrated energy deposition.

  Canvas->cd(5);
  theShowerCalib.hDPvsEcal->Draw("colz");

  Canvas->cd(6);
 Canvas->cd(6);
 theShowerCalib.hCaloPosNorm->GetZaxis()->SetRangeUser(0.05,1.2);
 theShowerCalib.hCaloPosNorm->SetTitle("Normalized E/p at Calorimeter");
 theShowerCalib.hCaloPosNorm->Draw("COLZ");

  //************wph add plots****************
  TCanvas *Canvas2=new TCanvas("Canvas2", "PHMS Shower Counter calibration", 1000, 667);
  Canvas2->Divide(3,2);

  Canvas2->cd(1);
  theShowerCalib.hpr->Draw("colz TEXT");
  Canvas2->cd(2);
  theShowerCalib.hsh->Draw("colz TEXT");
  Canvas2->cd(3);
  theShowerCalib.hCaloPos->Draw("colz");
  Canvas2->cd(4);
  theShowerCalib.hpra->Draw("colz TEXT");
  Canvas2->cd(5);
  theShowerCalib.hsha->Draw("colz TEXT");
  Canvas2->cd(6);
  theShowerCalib.hExitPos->Draw("colz");

  TCanvas *Canvas3=new TCanvas("Canvas3", "PHMS Shower Counter calibration", 1000, 667);
  Canvas3->Divide(3,2);

  Canvas3->cd(1);
  theShowerCalib.HGCer->Draw();
  gPad->SetLogy();
  Double_t top=theShowerCalib.HGCer->GetMaximum();
  Double_t locx=theShowerCalib.GetCerMin();
  TLine *cerl=new TLine(locx,0,locx,top);
  cerl->SetLineColor(kMagenta);
  cerl->Draw("same");

  Canvas3->cd(2);
  theShowerCalib.pP->Draw();

  // draw 1D Delta 
  Canvas3->cd(3);
  theShowerCalib.pDelta->Draw();
  top=theShowerCalib.pDelta->GetMaximum();
  locx=theShowerCalib.GetDeltaMin();
  TLine *dplmin=new TLine(locx,0,locx,top);
  dplmin->SetLineColor(kMagenta);
  dplmin->Draw("same");
  locx=theShowerCalib.GetDeltaMax();
  TLine *dplmax=new TLine(locx,0,locx,top);
  dplmax->SetLineColor(kMagenta);
  dplmax->Draw("same");

  // draw 1D Beta 
  Canvas3->cd(4);
  theShowerCalib.pBeta->Draw();
  gPad->SetLogy();
  top=theShowerCalib.pBeta->GetMaximum();
  locx=theShowerCalib.GetBetaMin();
  TLine *betalmin=new TLine(locx,0,locx,top);
  betalmin->SetLineColor(kMagenta);
  betalmin->Draw("same");
  locx=theShowerCalib.GetBetaMax();
  TLine *betalmax=new TLine(locx,0,locx,top);
  betalmax->SetLineColor(kMagenta);
  betalmax->Draw("same");
  Canvas3->cd(5);
  theShowerCalib.pClusTrk->Draw("BOX");

  //************wph add plots****************



  // Save canvas in a pdf format.
  TString Outpdf = Form("%s_%d_%d.pdf",Prefix.c_str(),RunNumber,nstop);
  Canvas->Print(Outpdf + '(');
  Canvas2->Print(Outpdf);
  Canvas3->Print(Outpdf + ')');
  // Save histograms in root file.
  //  TFile* froot = new TFile("/volatile/hallc/c-pionlt/jmurphy/ROOTfiles/Calib/HGC/Pion_coin_replay_production_8604_-1.root",
  TFile* froot=new TFile(Form("%s_%d_%d.root",Prefix.c_str(),RunNumber,nstop),
  			 "RECREATE");
  theShowerCalib.hEunc->Write();
  theShowerCalib.hEuncSel->Write();
  theShowerCalib.hESHvsEPR->Write();
  theShowerCalib.hEcal->Write();
  theShowerCalib.hDPvsEcal->Write();
  theShowerCalib.hETOTvsEPR->Write();        ////
  theShowerCalib.hEPRunc->Write();           ////
  theShowerCalib.hETOTvsEPRunc->Write();     ////
  theShowerCalib.hESHvsEPRunc->Write();      ////
  froot->Close();

  TCanvas *Canvas_1=new TCanvas("Canvas_1", "E/p uncalibrated", 800, 600);
//  Canvas_1->cd(1);
  theShowerCalib.hEunc->SetTitle("");
  theShowerCalib.hEunc->GetXaxis()->SetTitle("Normalized Calorimeter Energy (Uncalibrated)");
  theShowerCalib.hEunc->GetYaxis()->SetTitle("Number of Hits");
  theShowerCalib.hEunc->DrawCopy();
  theShowerCalib.hEuncSel->SetFillColor(kGreen);
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);
//  theShowerCalib.hEunc->SetTitle("");
//  theShowerCalib.hEunc->GetXaxis()->SetTitle("Normalized Calorimeter Energy (Uncalibrated)");
//  theShowerCalib.hEunc->GetYaxis()->SetTitle("Number of Hits");
  theShowerCalib.hEuncSel->DrawCopy("same");
  Canvas_1->SaveAs("Uncalibrated_Normalized_Energy.png");

  TCanvas *Canvas_2=new TCanvas("Canvas_2", "E/p calibrated", 800, 600);
//  Canvas_2->cd(1);
  gStyle->SetOptStat(0);
  theShowerCalib.hESHvsEPR->SetTitle("");
  theShowerCalib.hESHvsEPR->GetXaxis()->SetTitle("Preshower Energy");
  theShowerCalib.hESHvsEPR->GetYaxis()->SetTitle("Shower Energy");
  theShowerCalib.hESHvsEPR->Draw("colz");
  Canvas_2->SaveAs("Sh_vs_presh.png");

  TCanvas *Canvas_3=new TCanvas("Canvas_3", "E_sh vs E_pr", 800, 600);
//  Canvas_3->cd(1);
  gStyle->SetOptFit(0);
  theShowerCalib.hEcal->Fit("gaus","O","",0.5,1.5);
  TF1 *fit1 = theShowerCalib.hEcal->GetFunction("gaus");
  Double_t gmean1  = fit1->GetParameter(1);
  Double_t gsigma1 = fit1->GetParameter(2);
  double gLoThr1 = gmean1 - 2.*gsigma1;
  double gHiThr1 = gmean1 + 2.*gsigma1;
  cout << "gLoThr1=" << gLoThr1 << "  gHiThr1=" << gHiThr1 << endl;
  theShowerCalib.hEcal->Fit("gaus","","",gLoThr1,gHiThr1);

  theShowerCalib.hEcal->GetFunction("gaus")->SetLineColor(2);
  theShowerCalib.hEcal->GetFunction("gaus")->SetLineWidth(1);
  theShowerCalib.hEcal->GetFunction("gaus")->SetLineStyle(1);
  gStyle->SetOptStat(0);
  theShowerCalib.hEcal->SetTitle("");
  theShowerCalib.hEcal->GetXaxis()->SetTitle("Normalized Calorimeter Energy (Calibrated)");
  theShowerCalib.hEcal->GetYaxis()->SetTitle("Number of Hits");
  Canvas_3->SaveAs("Calibrated_Normalized_Energy.png");

  TCanvas *Canvas_4=new TCanvas("Canvas_4", "delta vs e_dep", 800, 600);
//  Canvas_4->cd(1);
//  gPad->SetLogz();
  gStyle->SetOptStat(0);
  theShowerCalib.hDPvsEcal->SetTitle("");
  theShowerCalib.hDPvsEcal->GetYaxis()->SetTitle("#delta (%)");
  theShowerCalib.hDPvsEcal->GetXaxis()->SetTitle("Normalized Calorimeter Energy");
  theShowerCalib.hDPvsEcal->Draw("colz");
  Canvas_4->SaveAs("Normalized_Energy_vs_delta.png");

  TCanvas *Canvas_6=new TCanvas("Canvas_6", "track vs hcal", 800, 600);
//  Canvas_6->cd(1);
  gPad->SetLogz();
  gStyle->SetOptStat(0);
  theShowerCalib.hCaloPos->SetTitle("");
  theShowerCalib.hCaloPos->GetXaxis()->SetTitle("X at Calo (cm)");
  theShowerCalib.hCaloPos->GetYaxis()->SetTitle("Y at Calo (cm)");
  theShowerCalib.hCaloPos->Draw("colz");
  Canvas_6->SaveAs("Cal_X_vs_Y.png");


  TString Outpdf1 = Form("NIM_%s_%d_%d.pdf",Prefix.c_str(),RunNumber,nstop);
  Canvas_1->Print(Outpdf1 + '(');
  Canvas_2->Print(Outpdf1);
  Canvas_3->Print(Outpdf1);
  Canvas_4->Print(Outpdf1);
  Canvas_6->Print(Outpdf1 + ')');

  // Calculate the analysis rate
  t = clock() - t;
  printf ("The analysis took %.1f seconds \n", ((float) t) / CLOCKS_PER_SEC);

}
