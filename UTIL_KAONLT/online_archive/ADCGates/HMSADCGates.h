//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Aug 13 11:12:03 2018 by ROOT version 6.10/02
// from TTree T/Hall A Analyzer Output DST
// found on file: ../../ROOTfiles/coin_replay_production_3423_-1.root
//////////////////////////////////////////////////////////

#ifndef HMSADCGates_h
#define HMSADCGates_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

// Headers needed by this particular selector


class HMSADCGates : public TSelector {
public :
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

   // Declaration of histograms
   TH1F          **h1HCERPulseTimeStarttimeDiff;

   TH1F          **h1HDCRawTdc;

   TH1F          **h1H1prCALNegPulseTimeStarttimeDiff;
   TH1F          **h1H1prCALPosPulseTimeStarttimeDiff;
   TH1F          **h1H2taCALNegPulseTimeStarttimeDiff;
   TH1F          **h1H2taCALPosPulseTimeStarttimeDiff;
   TH1F          **h1H3taCALNegPulseTimeStarttimeDiff;
   TH1F          **h1H3taCALPosPulseTimeStarttimeDiff;
   TH1F          **h1H4taCALNegPulseTimeStarttimeDiff;
   TH1F          **h1H4taCALPosPulseTimeStarttimeDiff;

   TH1F          **h1HHODO1xNegPulseTimeStarttimeDiff;
   TH1F          **h1HHODO1xPosPulseTimeStarttimeDiff;
   TH1F          **h1HHODO1yNegPulseTimeStarttimeDiff;
   TH1F          **h1HHODO1yPosPulseTimeStarttimeDiff;
   TH1F          **h1HHODO2xNegPulseTimeStarttimeDiff;
   TH1F          **h1HHODO2xPosPulseTimeStarttimeDiff;
   TH1F          **h1HHODO2yNegPulseTimeStarttimeDiff;
   TH1F          **h1HHODO2yPosPulseTimeStarttimeDiff;


   // Readers to access the data (delete the ones you do not need).
   TTreeReaderValue<Int_t> Ndata_H_cer_adcPulseTime = {fReader, "Ndata.H.cer.adcPulseTime"};
   TTreeReaderArray<Double_t> H_cer_adcCounter = {fReader, "H.cer.adcCounter"};
   TTreeReaderArray<Double_t> H_cer_adcErrorFlag = {fReader, "H.cer.adcErrorFlag"};
   TTreeReaderArray<Double_t> H_cer_adcPulseTime = {fReader, "H.cer.adcPulseTime"};

   TTreeReaderValue<Int_t> Ndata_H_1prcal_negAdcPulseTime = {fReader, "Ndata.H.cal.1pr.negAdcPulseTime"};
   TTreeReaderArray<Double_t> H_1prcal_negAdcCounter = {fReader, "H.cal.1pr.negAdcCounter"};
   TTreeReaderArray<Double_t> H_1prcal_negAdcErrorFlag = {fReader, "H.cal.1pr.negAdcErrorFlag"};
   TTreeReaderArray<Double_t> H_1prcal_negAdcPulseTime = {fReader, "H.cal.1pr.negAdcPulseTime"};

   TTreeReaderValue<Int_t> Ndata_H_1prcal_posAdcPulseTime = {fReader, "Ndata.H.cal.1pr.posAdcPulseTime"};
   TTreeReaderArray<Double_t> H_1prcal_posAdcCounter = {fReader, "H.cal.1pr.posAdcCounter"};
   TTreeReaderArray<Double_t> H_1prcal_posAdcErrorFlag = {fReader, "H.cal.1pr.posAdcErrorFlag"};
   TTreeReaderArray<Double_t> H_1prcal_posAdcPulseTime = {fReader, "H.cal.1pr.posAdcPulseTime"};
   
   TTreeReaderValue<Int_t> Ndata_H_2tacal_negAdcPulseTime = {fReader, "Ndata.H.cal.2ta.negAdcPulseTime"};
   TTreeReaderArray<Double_t> H_2tacal_negAdcCounter = {fReader, "H.cal.2ta.negAdcCounter"};
   TTreeReaderArray<Double_t> H_2tacal_negAdcErrorFlag = {fReader, "H.cal.2ta.negAdcErrorFlag"};
   TTreeReaderArray<Double_t> H_2tacal_negAdcPulseTime = {fReader, "H.cal.2ta.negAdcPulseTime"};

   TTreeReaderValue<Int_t> Ndata_H_2tacal_posAdcPulseTime = {fReader, "Ndata.H.cal.2ta.posAdcPulseTime"};
   TTreeReaderArray<Double_t> H_2tacal_posAdcCounter = {fReader, "H.cal.2ta.posAdcCounter"};
   TTreeReaderArray<Double_t> H_2tacal_posAdcErrorFlag = {fReader, "H.cal.2ta.posAdcErrorFlag"};
   TTreeReaderArray<Double_t> H_2tacal_posAdcPulseTime = {fReader, "H.cal.2ta.posAdcPulseTime"};

   TTreeReaderValue<Int_t> Ndata_H_3tacal_negAdcPulseTime = {fReader, "Ndata.H.cal.3ta.negAdcPulseTime"};
   TTreeReaderArray<Double_t> H_3tacal_negAdcCounter = {fReader, "H.cal.3ta.negAdcCounter"};
   TTreeReaderArray<Double_t> H_3tacal_negAdcErrorFlag = {fReader, "H.cal.3ta.negAdcErrorFlag"};
   TTreeReaderArray<Double_t> H_3tacal_negAdcPulseTime = {fReader, "H.cal.3ta.negAdcPulseTime"};

   TTreeReaderValue<Int_t> Ndata_H_3tacal_posAdcPulseTime = {fReader, "Ndata.H.cal.3ta.posAdcPulseTime"};
   TTreeReaderArray<Double_t> H_3tacal_posAdcCounter = {fReader, "H.cal.3ta.posAdcCounter"};
   TTreeReaderArray<Double_t> H_3tacal_posAdcErrorFlag = {fReader, "H.cal.3ta.posAdcErrorFlag"};
   TTreeReaderArray<Double_t> H_3tacal_posAdcPulseTime = {fReader, "H.cal.3ta.posAdcPulseTime"};

   TTreeReaderValue<Int_t> Ndata_H_4tacal_negAdcPulseTime = {fReader, "Ndata.H.cal.4ta.negAdcPulseTime"};
   TTreeReaderArray<Double_t> H_4tacal_negAdcCounter = {fReader, "H.cal.4ta.negAdcCounter"};
   TTreeReaderArray<Double_t> H_4tacal_negAdcErrorFlag = {fReader, "H.cal.4ta.negAdcErrorFlag"};
   TTreeReaderArray<Double_t> H_4tacal_negAdcPulseTime = {fReader, "H.cal.4ta.negAdcPulseTime"};

   TTreeReaderValue<Int_t> Ndata_H_4tacal_posAdcPulseTime = {fReader, "Ndata.H.cal.4ta.posAdcPulseTime"};
   TTreeReaderArray<Double_t> H_4tacal_posAdcCounter = {fReader, "H.cal.4ta.posAdcCounter"};
   TTreeReaderArray<Double_t> H_4tacal_posAdcErrorFlag = {fReader, "H.cal.4ta.posAdcErrorFlag"};
   TTreeReaderArray<Double_t> H_4tacal_posAdcPulseTime = {fReader, "H.cal.4ta.posAdcPulseTime"};

   TTreeReaderValue<Int_t> Ndata_H_dc_1u1_time = {fReader, "Ndata.H.dc.1u1.rawtdc"};
   TTreeReaderArray<Double_t> H_dc_1u1_rawtdc = {fReader, "H.dc.1u1.rawtdc"};
   TTreeReaderArray<Double_t> H_dc_1u2_rawtdc = {fReader, "H.dc.1u2.rawtdc"};
   TTreeReaderArray<Double_t> H_dc_1v1_rawtdc = {fReader, "H.dc.1v1.rawtdc"};
   TTreeReaderArray<Double_t> H_dc_1v2_rawtdc = {fReader, "H.dc.1v2.rawtdc"};
   TTreeReaderArray<Double_t> H_dc_1x1_rawtdc = {fReader, "H.dc.1x1.rawtdc"};
   TTreeReaderArray<Double_t> H_dc_1x2_rawtdc = {fReader, "H.dc.1x2.rawtdc"};
   TTreeReaderArray<Double_t> H_dc_2u1_rawtdc = {fReader, "H.dc.2u1.rawtdc"};
   TTreeReaderArray<Double_t> H_dc_2u2_rawtdc = {fReader, "H.dc.2u2.rawtdc"};
   TTreeReaderArray<Double_t> H_dc_2v1_rawtdc = {fReader, "H.dc.2v1.rawtdc"};
   TTreeReaderArray<Double_t> H_dc_2v2_rawtdc = {fReader, "H.dc.2v2.rawtdc"};
   TTreeReaderArray<Double_t> H_dc_2x1_rawtdc = {fReader, "H.dc.2x1.rawtdc"};
   TTreeReaderArray<Double_t> H_dc_2x2_rawtdc = {fReader, "H.dc.2x2.rawtdc"};

   TTreeReaderValue<Int_t> Ndata_H_hod_1x_negAdcPulseTime = {fReader, "Ndata.H.hod.1x.negAdcPulseTime"};
   TTreeReaderValue<Int_t> Ndata_H_hod_1x_negTdcTime      = {fReader, "Ndata.H.hod.1x.negTdcTime"};
   TTreeReaderArray<Double_t> H_hod_1x_negAdcCounter   = {fReader, "H.hod.1x.negAdcCounter"};
   TTreeReaderArray<Double_t> H_hod_1x_negAdcErrorFlag = {fReader, "H.hod.1x.negAdcErrorFlag"};
   TTreeReaderArray<Double_t> H_hod_1x_negAdcPulseTime = {fReader, "H.hod.1x.negAdcPulseTime"};
   TTreeReaderArray<Double_t> H_hod_1x_negTdcTime      = {fReader, "H.hod.1x.negTdcTime"};
   TTreeReaderArray<Double_t> H_hod_1x_negTdcTimeCorr  = {fReader, "H.hod.1x.GoodNegTdcTimeCorr"};

   TTreeReaderValue<Int_t> Ndata_H_hod_1y_negAdcPulseTime = {fReader, "Ndata.H.hod.1y.negAdcPulseTime"};
   TTreeReaderValue<Int_t> Ndata_H_hod_1y_negTdcTime      = {fReader, "Ndata.H.hod.1y.negTdcTime"};
   TTreeReaderArray<Double_t> H_hod_1y_negAdcCounter   = {fReader, "H.hod.1y.negAdcCounter"};
   TTreeReaderArray<Double_t> H_hod_1y_negAdcErrorFlag = {fReader, "H.hod.1y.negAdcErrorFlag"};
   TTreeReaderArray<Double_t> H_hod_1y_negAdcPulseTime = {fReader, "H.hod.1y.negAdcPulseTime"};
   TTreeReaderArray<Double_t> H_hod_1y_negTdcTime      = {fReader, "H.hod.1y.negTdcTime"};
   TTreeReaderArray<Double_t> H_hod_1y_negTdcTimeCorr  = {fReader, "H.hod.1y.GoodNegTdcTimeCorr"};

   TTreeReaderValue<Int_t> Ndata_H_hod_2x_negAdcPulseTime = {fReader, "Ndata.H.hod.2x.negAdcPulseTime"};
   TTreeReaderValue<Int_t> Ndata_H_hod_2x_negTdcTime      = {fReader, "Ndata.H.hod.2x.negTdcTime"};
   TTreeReaderArray<Double_t> H_hod_2x_negAdcCounter   = {fReader, "H.hod.2x.negAdcCounter"};
   TTreeReaderArray<Double_t> H_hod_2x_negAdcErrorFlag = {fReader, "H.hod.2x.negAdcErrorFlag"};
   TTreeReaderArray<Double_t> H_hod_2x_negAdcPulseTime = {fReader, "H.hod.2x.negAdcPulseTime"};
   TTreeReaderArray<Double_t> H_hod_2x_negTdcTime      = {fReader, "H.hod.2x.negTdcTime"};
   TTreeReaderArray<Double_t> H_hod_2x_negTdcTimeCorr  = {fReader, "H.hod.2x.GoodNegTdcTimeCorr"};

   TTreeReaderValue<Int_t> Ndata_H_hod_2y_negAdcPulseTime = {fReader, "Ndata.H.hod.2y.negAdcPulseTime"};
   TTreeReaderValue<Int_t> Ndata_H_hod_2y_negTdcTime      = {fReader, "Ndata.H.hod.2y.negTdcTime"};
   TTreeReaderArray<Double_t> H_hod_2y_negAdcCounter   = {fReader, "H.hod.2y.negAdcCounter"};
   TTreeReaderArray<Double_t> H_hod_2y_negAdcErrorFlag = {fReader, "H.hod.2y.negAdcErrorFlag"};
   TTreeReaderArray<Double_t> H_hod_2y_negAdcPulseTime = {fReader, "H.hod.2y.negAdcPulseTime"};
   TTreeReaderArray<Double_t> H_hod_2y_negTdcTime      = {fReader, "H.hod.2y.negTdcTime"};
   TTreeReaderArray<Double_t> H_hod_2y_negTdcTimeCorr  = {fReader, "H.hod.2y.GoodNegTdcTimeCorr"};

   TTreeReaderValue<Int_t> Ndata_H_hod_1x_posAdcPulseTime = {fReader, "Ndata.H.hod.1x.posAdcPulseTime"};
   TTreeReaderValue<Int_t> Ndata_H_hod_1x_posTdcTime      = {fReader, "Ndata.H.hod.1x.posTdcTime"};
   TTreeReaderArray<Double_t> H_hod_1x_posAdcCounter   = {fReader, "H.hod.1x.posAdcCounter"};
   TTreeReaderArray<Double_t> H_hod_1x_posAdcErrorFlag = {fReader, "H.hod.1x.posAdcErrorFlag"};
   TTreeReaderArray<Double_t> H_hod_1x_posAdcPulseTime = {fReader, "H.hod.1x.posAdcPulseTime"};
   TTreeReaderArray<Double_t> H_hod_1x_posTdcTime      = {fReader, "H.hod.1x.posTdcTime"};
   TTreeReaderArray<Double_t> H_hod_1x_posTdcTimeCorr  = {fReader, "H.hod.1x.GoodPosTdcTimeCorr"};

   TTreeReaderValue<Int_t> Ndata_H_hod_1y_posAdcPulseTime = {fReader, "Ndata.H.hod.1y.posAdcPulseTime"};
   TTreeReaderValue<Int_t> Ndata_H_hod_1y_posTdcTime      = {fReader, "Ndata.H.hod.1y.posTdcTime"};
   TTreeReaderArray<Double_t> H_hod_1y_posAdcCounter   = {fReader, "H.hod.1y.posAdcCounter"};
   TTreeReaderArray<Double_t> H_hod_1y_posAdcErrorFlag = {fReader, "H.hod.1y.posAdcErrorFlag"};
   TTreeReaderArray<Double_t> H_hod_1y_posAdcPulseTime = {fReader, "H.hod.1y.posAdcPulseTime"};
   TTreeReaderArray<Double_t> H_hod_1y_posTdcTime      = {fReader, "H.hod.1y.posTdcTime"};
   TTreeReaderArray<Double_t> H_hod_1y_posTdcTimeCorr  = {fReader, "H.hod.1y.GoodPosTdcTimeCorr"};

   TTreeReaderValue<Int_t> Ndata_H_hod_2x_posAdcPulseTime = {fReader, "Ndata.H.hod.2x.posAdcPulseTime"};
   TTreeReaderValue<Int_t> Ndata_H_hod_2x_posTdcTime      = {fReader, "Ndata.H.hod.2x.posTdcTime"};
   TTreeReaderArray<Double_t> H_hod_2x_posAdcCounter   = {fReader, "H.hod.2x.posAdcCounter"};
   TTreeReaderArray<Double_t> H_hod_2x_posAdcErrorFlag = {fReader, "H.hod.2x.posAdcErrorFlag"};
   TTreeReaderArray<Double_t> H_hod_2x_posAdcPulseTime = {fReader, "H.hod.2x.posAdcPulseTime"};
   TTreeReaderArray<Double_t> H_hod_2x_posTdcTime      = {fReader, "H.hod.2x.posTdcTime"};
   TTreeReaderArray<Double_t> H_hod_2x_posTdcTimeCorr  = {fReader, "H.hod.2x.GoodPosTdcTimeCorr"};

   TTreeReaderValue<Int_t> Ndata_H_hod_2y_posAdcPulseTime = {fReader, "Ndata.H.hod.2y.posAdcPulseTime"};
   TTreeReaderValue<Int_t> Ndata_H_hod_2y_posTdcTime      = {fReader, "Ndata.H.hod.2y.posTdcTime"};
   TTreeReaderArray<Double_t> H_hod_2y_posAdcCounter   = {fReader, "H.hod.2y.posAdcCounter"};
   TTreeReaderArray<Double_t> H_hod_2y_posAdcErrorFlag = {fReader, "H.hod.2y.posAdcErrorFlag"};
   TTreeReaderArray<Double_t> H_hod_2y_posAdcPulseTime = {fReader, "H.hod.2y.posAdcPulseTime"};
   TTreeReaderArray<Double_t> H_hod_2y_posTdcTime      = {fReader, "H.hod.2y.posTdcTime"};
   TTreeReaderArray<Double_t> H_hod_2y_posTdcTimeCorr  = {fReader, "H.hod.2y.GoodPosTdcTimeCorr"};
   
   TTreeReaderValue<Double_t> H_hod_starttime = {fReader, "H.hod.starttime"};

   HMSADCGates(TTree * /*tree*/ =0) {h1HCERPulseTimeStarttimeDiff=0,h1H1prCALNegPulseTimeStarttimeDiff=0,h1H1prCALPosPulseTimeStarttimeDiff=0,h1H2taCALNegPulseTimeStarttimeDiff=0,h1H2taCALPosPulseTimeStarttimeDiff=0,h1H3taCALNegPulseTimeStarttimeDiff=0,h1H3taCALPosPulseTimeStarttimeDiff=0,h1H4taCALNegPulseTimeStarttimeDiff=0,h1H4taCALPosPulseTimeStarttimeDiff=0,h1HDCRawTdc=0,h1HHODO1xNegPulseTimeStarttimeDiff=0,h1HHODO1xPosPulseTimeStarttimeDiff=0,h1HHODO1yNegPulseTimeStarttimeDiff=0,h1HHODO1yPosPulseTimeStarttimeDiff=0,h1HHODO2xNegPulseTimeStarttimeDiff=0,h1HHODO2xPosPulseTimeStarttimeDiff=0,h1HHODO2yNegPulseTimeStarttimeDiff=0,h1HHODO2yPosPulseTimeStarttimeDiff=0;}
   virtual ~HMSADCGates() { }
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

   ClassDef(HMSADCGates,0);

};

#endif

#ifdef HMSADCGates_cxx
void HMSADCGates::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the reader is initialized.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   fReader.SetTree(tree);
}

Bool_t HMSADCGates::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}


#endif // #ifdef HMSADCGates_cxx
