//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Aug 13 11:12:03 2018 by ROOT version 6.10/02
// from TTree T/Hall A Analyzer Output DST
// found on file: ../../ROOTfiles/coin_replay_production_3423_-1.root
//////////////////////////////////////////////////////////

#ifndef TREF_h
#define TREF_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

// Headers needed by this particular selector


class TREF : public TSelector {
public :
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

   // Declaration of histograms
   TH1F          **h1TSHMSDCPulseTime;
   TH1F           *h1TSHMSFADC;
   TH1F          **h1TSHMSTRIG;


   // Readers to access the data (delete the ones you do not need).
   TTreeReaderValue<Double_t> T_shms_pDCREF1_tdcTime = {fReader, "T.shms.pDCREF1_tdcTimeRaw"};
   TTreeReaderValue<Double_t> T_shms_pDCREF2_tdcTime = {fReader, "T.shms.pDCREF2_tdcTimeRaw"};
   TTreeReaderValue<Double_t> T_shms_pDCREF3_tdcTime = {fReader, "T.shms.pDCREF3_tdcTimeRaw"};
   TTreeReaderValue<Double_t> T_shms_pDCREF4_tdcTime = {fReader, "T.shms.pDCREF4_tdcTimeRaw"};
   TTreeReaderValue<Double_t> T_shms_pDCREF5_tdcTime = {fReader, "T.shms.pDCREF5_tdcTimeRaw"};
   TTreeReaderValue<Double_t> T_shms_pDCREF6_tdcTime = {fReader, "T.shms.pDCREF6_tdcTimeRaw"};
   TTreeReaderValue<Double_t> T_shms_pDCREF7_tdcTime = {fReader, "T.shms.pDCREF7_tdcTimeRaw"};
   TTreeReaderValue<Double_t> T_shms_pDCREF8_tdcTime = {fReader, "T.shms.pDCREF8_tdcTimeRaw"};
   TTreeReaderValue<Double_t> T_shms_pDCREF9_tdcTime = {fReader, "T.shms.pDCREF9_tdcTimeRaw"};
   TTreeReaderValue<Double_t> T_shms_pDCREF10_tdcTime = {fReader, "T.shms.pDCREF10_tdcTimeRaw"};
   
   TTreeReaderValue<Double_t> T_shms_pFADC_TREF_ROC2_adcPulseTime = {fReader, "T.shms.pFADC_TREF_ROC2_adcPulseTimeRaw"};
   
   TTreeReaderValue<Double_t> T_shms_pTRIG1_tdcTimeRaw = {fReader, "T.shms.pT1_tdcTimeRaw"};
   TTreeReaderValue<Double_t> T_shms_pTRIG2_tdcTimeRaw = {fReader, "T.shms.pT2_tdcTimeRaw"};
   TTreeReaderValue<Double_t> T_shms_pTRIG3_tdcTimeRaw = {fReader, "T.shms.pTRIG3_tdcTimeRaw"};
   TTreeReaderValue<Double_t> T_shms_pTRIG4_tdcTimeRaw = {fReader, "T.shms.pTRIG4_tdcTimeRaw"};
   TTreeReaderValue<Double_t> T_shms_pTRIG5_tdcTimeRaw = {fReader, "T.shms.pTRIG5_tdcTimeRaw"};
   TTreeReaderValue<Double_t> T_shms_pTRIG6_tdcTimeRaw = {fReader, "T.shms.pTRIG6_tdcTimeRaw"};
   
   TREF(TTree * /*tree*/ =0) {h1TSHMSDCPulseTime=0, h1TSHMSFADC=0, h1TSHMSTRIG=0;}
   virtual ~TREF() { }
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

   ClassDef(TREF,0);

};

#endif

#ifdef TREF_cxx
void TREF::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the reader is initialized.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   fReader.SetTree(tree);
}

Bool_t TREF::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}


#endif // #ifdef TREF_cxx
