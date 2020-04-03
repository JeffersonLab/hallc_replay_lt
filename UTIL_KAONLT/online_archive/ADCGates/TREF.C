#define TREF_cxx
// The class definition in TREF.h has been generated automatically
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
// root> T->Process("TREF.C")
// root> T->Process("TREF.C","some options")
// root> T->Process("TREF.C+")
//


#include "TREF.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLine.h>
#include <TSpectrum.h>
#include <TPolyMarker.h>
#include <TMath.h>
#include <TSystem.h>

void TREF::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();
}

void TREF::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();
   
   h1TSHMSDCPulseTime = new TH1F*[10];
   for (Int_t idc=0; idc<10; idc++) {
     h1TSHMSDCPulseTime[idc] = new TH1F(Form("SHMSDCPulseTime%d",idc+1),Form("Pulse Time Information for SHMS DC TREF%d;Time (ns);Counts",idc+1),800,0,16000);
     GetOutputList()->Add(h1TSHMSDCPulseTime[idc]);
   }

   h1TSHMSFADC = new TH1F("SHMSFADC","FADC REF Time;Time (ns);Counts",600,0,10000);
   GetOutputList()->Add(h1TSHMSFADC);

   h1TSHMSTRIG = new TH1F*[6];
   for (Int_t iTRIG=0; iTRIG<6; iTRIG++) {
     h1TSHMSTRIG[iTRIG] = new TH1F(Form("SHMSTRIG%d",iTRIG+1),Form("Pulse Time Information for SHMS TRIG%d;Time (ns);Counts",iTRIG+1),200,0,5000);
     GetOutputList()->Add(h1TSHMSTRIG[iTRIG]);
   }
}

Bool_t TREF::Process(Long64_t entry)
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
   
   h1TSHMSDCPulseTime[0]->Fill(*T_shms_pDCREF1_tdcTime);
   h1TSHMSDCPulseTime[1]->Fill(*T_shms_pDCREF2_tdcTime);
   h1TSHMSDCPulseTime[2]->Fill(*T_shms_pDCREF3_tdcTime);
   h1TSHMSDCPulseTime[3]->Fill(*T_shms_pDCREF4_tdcTime);
   h1TSHMSDCPulseTime[4]->Fill(*T_shms_pDCREF5_tdcTime);
   h1TSHMSDCPulseTime[5]->Fill(*T_shms_pDCREF6_tdcTime);
   h1TSHMSDCPulseTime[6]->Fill(*T_shms_pDCREF7_tdcTime);
   h1TSHMSDCPulseTime[7]->Fill(*T_shms_pDCREF8_tdcTime);
   h1TSHMSDCPulseTime[8]->Fill(*T_shms_pDCREF9_tdcTime);
   h1TSHMSDCPulseTime[9]->Fill(*T_shms_pDCREF10_tdcTime);

   h1TSHMSFADC->Fill(*T_shms_pFADC_TREF_ROC2_adcPulseTime);
   
   h1TSHMSTRIG[0]->Fill(*T_shms_pTRIG1_tdcTimeRaw);
   h1TSHMSTRIG[1]->Fill(*T_shms_pTRIG2_tdcTimeRaw);
   h1TSHMSTRIG[2]->Fill(*T_shms_pTRIG3_tdcTimeRaw);
   h1TSHMSTRIG[3]->Fill(*T_shms_pTRIG4_tdcTimeRaw);
   h1TSHMSTRIG[4]->Fill(*T_shms_pTRIG5_tdcTimeRaw);
   
   return kTRUE;
}

void TREF::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void TREF::Terminate()
{
  // The Terminate() function is the last function to be called during
  // a query. It always runs on the client, it can be used to present
  // the results graphically or save the results to file.

  Info("Terminate", "Branches Sorted, Now Calculating Windows");
  
  TH1F* TSHMSDCPulseTime[10];
  for (Int_t idc = 0; idc < 10; idc++) {
    TSHMSDCPulseTime[idc] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("SHMSDCPulseTime%d",idc+1)));
  }  

  TH1F* TSHMSFADC = dynamic_cast<TH1F*> (GetOutputList()->FindObject("SHMSFADC"));

  TH1F* TSHMSTRIG[6];
  for (Int_t iTRIG = 0; iTRIG < 6; iTRIG++) {
    TSHMSTRIG[iTRIG] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("SHMSTRIG%d",iTRIG+1)));
  }  
  
  //Begin peak Finding
  //gSystem->RedirectOutput("/dev/null","a");
  Double_t DCREF_peak[10];
  for (Int_t idc = 0; idc < 10; idc++) {
    if (TSHMSDCPulseTime[idc]->GetEntries() != 0) {
      TSpectrum *s = new TSpectrum(1);
      s->Search(TSHMSDCPulseTime[idc], 1.0, "nobackground&&nodraw", 0.001);
      TList *functions = TSHMSDCPulseTime[idc]->GetListOfFunctions();
      TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
      DCREF_peak[idc] = *pm->GetX();
    }
    else {
      DCREF_peak[idc] = 1e+38;
    }
  }

  Double_t ROC2REF_peak;
  if (TSHMSFADC->GetEntries() != 0) {
    TSpectrum *s = new TSpectrum(1);
    s->Search(TSHMSFADC, 0.01, "nobackground&&nodraw", 0.001);
    TList *functions = TSHMSFADC->GetListOfFunctions();
    TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
    ROC2REF_peak = *pm->GetX();
  }
  else {
    ROC2REF_peak = 1e+38;
  }

  Double_t TRIGREF_peak[6];
  for (Int_t iTRIG = 0; iTRIG < 6; iTRIG++) {
    if (TSHMSTRIG[iTRIG]->GetEntries() != 0) {
      TSpectrum *s = new TSpectrum(1);
      s->Search(TSHMSTRIG[iTRIG], 1.0, "nobackground&&nodraw", 0.001);
      TList *functions = TSHMSTRIG[iTRIG]->GetListOfFunctions();
      TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
      TRIGREF_peak[iTRIG] = *pm->GetX();
    }
    else {
      TRIGREF_peak[iTRIG] = 1e+38;
    }
  }
  //gSystem->RedirectOutput(0);
  
  //Begin Calculation of TREF Cuts
  Double_t DCTREF_Cut = TMath::MinElement(10,DCREF_peak) - 600;

  for (Int_t iTRIG = 0; iTRIG < 6; iTRIG++) {
    TRIGREF_peak[iTRIG] -= 600;
  }
  
  
  //Begin Plotting Results
  TCanvas *cDC = new TCanvas("cDC","SHMS DCREF");
  cDC->Divide(2,5); 
  for (Int_t idc = 0; idc < 10; idc++) {
    cDC->cd(idc+1); TSHMSDCPulseTime[idc]->Draw();
    gPad->Update();
    TLine *Lower_Limit = new TLine(DCTREF_Cut,gPad->GetUymin(),DCTREF_Cut,gPad->GetUymax());
    Lower_Limit->SetLineColor(kRed); Lower_Limit->SetLineWidth(3); Lower_Limit->SetLineStyle(2);
    Lower_Limit->Draw();
  }

  TCanvas *cROC2 = new TCanvas("cROC2","SHMS ROC2 REF");
  TSHMSFADC->Draw();

  TCanvas *cTRIG = new TCanvas("cTRIG","SHMS TRIGREF");
  cTRIG->Divide(2,3); 
  for (Int_t iTRIG = 0; iTRIG < 6; iTRIG++) {
    cTRIG->cd(iTRIG+1); TSHMSTRIG[iTRIG]->Draw();
    gPad->Update();
    TLine *Lower_Limit = new TLine(TRIGREF_peak[iTRIG],gPad->GetUymin(),TRIGREF_peak[iTRIG],gPad->GetUymax());
    Lower_Limit->SetLineColor(kRed); Lower_Limit->SetLineWidth(3); Lower_Limit->SetLineStyle(2);
    Lower_Limit->Draw();
  }
  
  //Output Adc Time Window Values into an ascii file
  TString option = GetOption();
  ofstream TREFFile;
  TREFFile.open("SHMSTREF.dat", fstream::trunc);
  TREFFile << Form(";Values obtained from Run %s",option.Data()) << endl;
  TREFFile << Form("pdc_tdcrefcut= = -%.0f.\n",DCTREF_Cut);
  TREFFile << Form("phodo_tdcrefcut= = -%.0f.\n",TRIGREF_peak[0]);
  TREFFile << Form("phodo_adcrefcut= = -%.0f.\n",ROC2REF_peak);
  TREFFile << Form("pngcer_adcrefcut= = -%.0f.\n",ROC2REF_peak);
  TREFFile << Form("phgcer_adcrefcut= = -%.0f.\n",ROC2REF_peak);
  TREFFile << Form("paero_adcrefcut= = -%.0f.\n",ROC2REF_peak);
  TREFFile << Form("pcal_adcrefcut= = -%.0f.\n",ROC2REF_peak);
  TREFFile.close();

  //Start output of .root file with all histograms
  TFile *Histogram_file = new TFile(Form("../../HISTOGRAMS/SHMSTREF_Run%i.root",option.Atoi()),"RECREATE");
  TDirectory *DDC = Histogram_file->mkdir("Drift Chamber Reference Time"); DDC->cd();
  for (Int_t idc=0; idc < 10; idc++) {
    TSHMSDCPulseTime[idc]->Write(Form("DC REF %i",idc+1));
  }
  TDirectory *DROC2 = Histogram_file->mkdir("FADC ROC2 Reference Time"); DROC2->cd();
  TSHMSFADC->Write("FADC ROC2 REF");

  TDirectory *DTRIG = Histogram_file->mkdir("Trigger Reference Time"); DTRIG->cd();
  for (Int_t itrig=0; itrig < 6; itrig++) {
    TSHMSTRIG[itrig]->Write(Form("TRIG REF %i",itrig+1));
  }
  
  Histogram_file->Close();
}                  
