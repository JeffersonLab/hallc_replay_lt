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
 
  cout << "Calibrating file " << Prefix << "_" << RunNumber << "_" << nstop <<  ".root, events "
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
  theShowerCalib.hCer->Draw();
  gPad->SetLogy();
  Double_t top=theShowerCalib.hCer->GetMaximum();
  Double_t locx=theShowerCalib.GetCerMin();
  TLine *cerl=new TLine(locx,0,locx,top);
  cerl->SetLineColor(kMagenta);
  cerl->Draw("same");

  Canvas3->cd(2);
  theShowerCalib.hP->Draw();

  // draw 1D Delta 
  Canvas3->cd(3);
  theShowerCalib.hDelta->Draw();
  top=theShowerCalib.hDelta->GetMaximum();
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
  theShowerCalib.hBeta->Draw();
  gPad->SetLogy();
  top=theShowerCalib.hBeta->GetMaximum();
  locx=theShowerCalib.GetBetaMin();
  TLine *betalmin=new TLine(locx,0,locx,top);
  betalmin->SetLineColor(kMagenta);
  betalmin->Draw("same");
  locx=theShowerCalib.GetBetaMax();
  TLine *betalmax=new TLine(locx,0,locx,top);
  betalmax->SetLineColor(kMagenta);
  betalmax->Draw("same");
  Canvas3->cd(5);
  theShowerCalib.hClusTrk->Draw("BOX");

  //************wph add plots****************



  // Save canvas in a pdf format.
  TString Outpdf = Form("%s_%d_%d.pdf",Prefix.c_str(),RunNumber,nstop);
  Canvas->Print(Outpdf + '(');
  Canvas2->Print(Outpdf);
  Canvas3->Print(Outpdf + ')');
  // Save histograms in root file.

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

  // Calculate the analysis rate
  t = clock() - t;
  printf ("The analysis took %.1f seconds \n", ((float) t) / CLOCKS_PER_SEC);
}
