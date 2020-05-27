//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Aug 13 11:12:03 2018 by ROOT version 6.10/02
// from TTree T/Hall A Analyzer Output DST
// found on file: ../../ROOTfiles/coin_replay_production_3423_-1.root
//////////////////////////////////////////////////////////

#ifndef TREFHMS_h
#define TREFHMS_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

// Headers needed by this particular selector


class TREFHMS : public TSelector {
public :
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

   // Declaration of histograms
   TH1F          **h1THMSDCPulseTime;
   TH1F           *h1THMSFADC;
   TH1F          **h1THMSTRIG;


   // Readers to access the data (delete the ones you do not need).
   TTreeReaderValue<Double_t> T_hms_hDCREF1_tdcTime = {fReader, "T.hms.hDCREF1_tdcTimeRaw"};
   TTreeReaderValue<Double_t> T_hms_hDCREF2_tdcTime = {fReader, "T.hms.hDCREF2_tdcTimeRaw"};
   TTreeReaderValue<Double_t> T_hms_hDCREF3_tdcTime = {fReader, "T.hms.hDCREF3_tdcTimeRaw"};
   TTreeReaderValue<Double_t> T_hms_hDCREF4_tdcTime = {fReader, "T.hms.hDCREF4_tdcTimeRaw"};
   TTreeReaderValue<Double_t> T_hms_hDCREF5_tdcTime = {fReader, "T.hms.hDCREF5_tdcTimeRaw"};

   TTreeReaderValue<Double_t> T_hms_hFADC_TREF_ROC1_adcPulseTime = {fReader, "T.hms.hFADC_TREF_ROC1_adcPulseTimeRaw"};

   TTreeReaderValue<Double_t> T_hms_hTRIG1_tdcTimeRaw = {fReader, "T.hms.hT1_tdcTimeRaw"};
   TTreeReaderValue<Double_t> T_hms_hTRIG2_tdcTimeRaw = {fReader, "T.hms.hT2_tdcTimeRaw"};
   TTreeReaderValue<Double_t> T_hms_hTRIG3_tdcTimeRaw = {fReader, "T.hms.hTRIG3_tdcTimeRaw"};
   TTreeReaderValue<Double_t> T_hms_hTRIG4_tdcTimeRaw = {fReader, "T.hms.hTRIG4_tdcTimeRaw"};
   TTreeReaderValue<Double_t> T_hms_hTRIG5_tdcTimeRaw = {fReader, "T.hms.hTRIG5_tdcTimeRaw"};
   TTreeReaderValue<Double_t> T_hms_hTRIG6_tdcTimeRaw = {fReader, "T.hms.hTRIG6_tdcTimeRaw"};
   
   TREFHMS(TTree * /*tree*/ =0) {h1THMSDCPulseTime=0, h1THMSFADC=0, h1THMSTRIG=0;}
   virtual ~TREFHMS() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

   ClassDef(TREFHMS,0);

};

#endif

#ifdef TREFHMS_cxx
void TREFHMS::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the reader is initialized.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   fReader.SetTree(tree);
}

Bool_t TREFHMS::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}


#endif // #ifdef TREFHMS_cxx
