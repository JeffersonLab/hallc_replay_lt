#define TREFHMS_cxx
// The class definition in TREFHMS.h has been generated automatically
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
// root> T->Process("TREFHMS.C")
// root> T->Process("TREFHMS.C","some options")
// root> T->Process("TREFHMS.C+")
//


#include "TREFHMS.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLine.h>
#include <TSpectrum.h>
#include <TPolyMarker.h>
#include <TMath.h>
#include <TSystem.h>

void TREFHMS::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();
}

void TREFHMS::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

   h1THMSDCPulseTime = new TH1F*[10];
   for (Int_t idc=0; idc<5; idc++) {
     h1THMSDCPulseTime[idc] = new TH1F(Form("HMSDCPulseTime%d",idc+1),Form("Pulse Time Information for HMS DC TREF%d;Time (ns);Counts",idc+1),850,0,18000);
     GetOutputList()->Add(h1THMSDCPulseTime[idc]);
   }

   h1THMSFADC = new TH1F("HMSFADC","FADC REF Time;Time (ns);Counts",1000,0,10000);
   GetOutputList()->Add(h1THMSFADC);

   h1THMSTRIG = new TH1F*[6];
   for (Int_t iTRIG=0; iTRIG<6; iTRIG++) {
     h1THMSTRIG[iTRIG] = new TH1F(Form("HMSTRIG%d",iTRIG+1),Form("Pulse Time Information for HMS TRIG%d;Time (ns);Counts",iTRIG+1),200,0,4500);
     GetOutputList()->Add(h1THMSTRIG[iTRIG]);
   }
}

Bool_t TREFHMS::Process(Long64_t entry)
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

   h1THMSDCPulseTime[0]->Fill(*T_hms_hDCREF1_tdcTime);
   h1THMSDCPulseTime[1]->Fill(*T_hms_hDCREF2_tdcTime);
   h1THMSDCPulseTime[2]->Fill(*T_hms_hDCREF3_tdcTime);
   h1THMSDCPulseTime[3]->Fill(*T_hms_hDCREF4_tdcTime);
   h1THMSDCPulseTime[4]->Fill(*T_hms_hDCREF5_tdcTime);

   h1THMSFADC->Fill(*T_hms_hFADC_TREF_ROC1_adcPulseTime);

   h1THMSTRIG[0]->Fill(*T_hms_hTRIG1_tdcTimeRaw);
   h1THMSTRIG[1]->Fill(*T_hms_hTRIG2_tdcTimeRaw);
   h1THMSTRIG[2]->Fill(*T_hms_hTRIG3_tdcTimeRaw);
   h1THMSTRIG[3]->Fill(*T_hms_hTRIG4_tdcTimeRaw);
   h1THMSTRIG[4]->Fill(*T_hms_hTRIG5_tdcTimeRaw);

   return kTRUE;
}

void TREFHMS::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void TREFHMS::Terminate()
{
  // The Terminate() function is the last function to be called during
  // a query. It always runs on the client, it can be used to present
  // the results graphically or save the results to file.

  Info("Terminate", "Branches Sorted, Now Calculating Windows");
  
  TH1F* THMSDCPulseTime[5];
  for (Int_t idc = 0; idc < 5; idc++) {
    THMSDCPulseTime[idc] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("HMSDCPulseTime%d",idc+1)));
  }  

  TH1F* THMSFADC = dynamic_cast<TH1F*> (GetOutputList()->FindObject("HMSFADC"));

  TH1F* THMSTRIG[6];
  for (Int_t iTRIG = 0; iTRIG < 6; iTRIG++) {
    THMSTRIG[iTRIG] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("HMSTRIG%d",iTRIG+1)));
  } 
  
  //Begin peak Finding
  gSystem->RedirectOutput("/dev/null","a");
  Double_t DCREF_peak[5];
  for (Int_t idc = 0; idc < 5; idc++) {
    if (THMSDCPulseTime[idc]->GetEntries() != 0) {
      TSpectrum *s = new TSpectrum(1);
      s->Search(THMSDCPulseTime[idc], 1.0, "nobackground&&nodraw", 0.001);
      TList *functions = THMSDCPulseTime[idc]->GetListOfFunctions();
      TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
      if (pm) DCREF_peak[idc] = *pm->GetX();
    }
    else {
      DCREF_peak[idc] = 1e+38;
    }
  }

  Double_t ROC1REF_peak = 1e+38;
  if (THMSFADC->GetEntries() != 0) {
    TSpectrum *s = new TSpectrum(1);
    s->Search(THMSFADC, 1.0, "nobackground&&nodraw", 0.001);
    TList *functions = THMSFADC->GetListOfFunctions();
    TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
    if (pm) ROC1REF_peak = *pm->GetX();
  }
  else {
    ROC1REF_peak = 1e+38;
  }

  Double_t TRIGREF_peak[6];
  for (Int_t iTRIG = 0; iTRIG < 6; iTRIG++) {
    if (THMSTRIG[iTRIG]->GetEntries() != 0) {
      TSpectrum *s = new TSpectrum(1);
      s->Search(THMSTRIG[iTRIG], 1.0, "nobackground&&nodraw", 0.001);
      TList *functions = THMSTRIG[iTRIG]->GetListOfFunctions();
      TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
      TRIGREF_peak[iTRIG] = *pm->GetX();
    }
    else {
      TRIGREF_peak[iTRIG] = 1e+38;
    }
  }
  gSystem->RedirectOutput(0);
  
  //Begin Calculation of TREF Cuts
  Double_t DCTREF_Cut = TMath::MinElement(5,DCREF_peak) - 600;

  for (Int_t iTRIG = 0; iTRIG < 6; iTRIG++) {
    TRIGREF_peak[iTRIG] -= 600;
  }
  
  
  //Begin Plotting Results
  TCanvas *cDC = new TCanvas("cDC","HMS DCREF");
  cDC->Divide(2,3); 
  for (Int_t idc = 0; idc < 5; idc++) {
    cDC->cd(idc+1); THMSDCPulseTime[idc]->Draw();
    gPad->Update();
    TLine *Lower_Limit = new TLine(DCTREF_Cut,gPad->GetUymin(),DCTREF_Cut,gPad->GetUymax());
    Lower_Limit->SetLineColor(kRed); Lower_Limit->SetLineWidth(3); Lower_Limit->SetLineStyle(2);
    Lower_Limit->Draw();
  }

  TCanvas *cROC1 = new TCanvas("cROC1","HMS ROC1 REF");
  THMSFADC->Draw();

  TCanvas *cTRIG = new TCanvas("cTRIG","HMS TRIGREF");
  cTRIG->Divide(2,3); 
  for (Int_t iTRIG = 0; iTRIG < 6; iTRIG++) {
    cTRIG->cd(iTRIG+1); THMSTRIG[iTRIG]->Draw();
    gPad->Update();
    TLine *Lower_Limit = new TLine(TRIGREF_peak[iTRIG],gPad->GetUymin(),TRIGREF_peak[iTRIG],gPad->GetUymax());
    Lower_Limit->SetLineColor(kRed); Lower_Limit->SetLineWidth(3); Lower_Limit->SetLineStyle(2);
    Lower_Limit->Draw();
  }
  
  //Output Adc Time Window Values into an ascii file
  TString option = GetOption();
  ofstream TREFFile;
  TREFFile.open("HMSTREF.dat", fstream::trunc);
  TREFFile << Form(";Values obtained from Run %s",option.Data()) << endl;
  TREFFile << Form("hdc_tdcrefcut= = -%.0f.\n",DCTREF_Cut);
  TREFFile << Form("hhodo_tdcrefcut= = -%.0f.\n",TRIGREF_peak[0]);
  TREFFile << Form("hhodo_adcrefcut= = -%.0f.\n",ROC1REF_peak);
  TREFFile << Form("hcer_adcrefcut= = -%.0f.\n",ROC1REF_peak);
  TREFFile << Form("hcal_adcrefcut= = -%.0f.\n",ROC1REF_peak);
  TREFFile.close();

  //Start output of .root file with all histograms
  TFile *Histogram_file = new TFile(Form("../../HISTOGRAMS/HMSTREF_Run%i.root",option.Atoi()),"RECREATE");
  TDirectory *DDC = Histogram_file->mkdir("Drift Chamber Reference Time"); DDC->cd();
  for (Int_t idc=0; idc < 5; idc++) {
    THMSDCPulseTime[idc]->Write(Form("DC REF %i",idc+1));
  }
  TDirectory *DROC1 = Histogram_file->mkdir("FADC ROC1 Reference Time"); DROC1->cd();
  THMSFADC->Write("FADC ROC1 REF");

  TDirectory *DTRIG = Histogram_file->mkdir("Trigger Reference Time"); DTRIG->cd();
  for (Int_t itrig=0; itrig < 6; itrig++) {
    THMSTRIG[itrig]->Write(Form("TRIG REF %i",itrig+1));
  }

  Histogram_file->Close();
}                  
