//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Aug 13 11:12:03 2018 by ROOT version 6.10/02
// from TTree T/Hall A Analyzer Output DST
// found on file: ../../ROOTfiles/coin_replay_production_3423_-1.root
//////////////////////////////////////////////////////////

#ifndef SHMSADCGates_h
#define SHMSADCGates_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

// Headers needed by this particular selector


class SHMSADCGates : public TSelector {
public :
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

   // Declaration of histograms
   TH1F          **h1PHGCERPulseTime;
   TH1F          **h1PHGCERPulseTimeStarttimeDiff;

   //TH1F          **h1PNGCERPulseTime;
   //TH1F          **h1PNGCERPulseTimeStarttimeDiff;

   TH1F          **h1PAERONegPulseTime;
   TH1F          **h1PAERONegPulseTimeStarttimeDiff;

   TH1F          **h1PAEROPosPulseTime;
   TH1F          **h1PAEROPosPulseTimeStarttimeDiff;

   TH1F          **h1PPRECALNegPulseTime;
   TH1F          **h1PPRECALNegPulseTimeStarttimeDiff;

   TH1F          **h1PPRECALPosPulseTime;
   TH1F          **h1PPRECALPosPulseTimeStarttimeDiff;

   TH1F          **h1PCALPulseTimeStarttimeDiff;

   TH1F          **h1PDCRawTdc;

   TH1F          **h1PHODO1xNegPulseTimeStarttimeDiff;
   TH1F          **h1PHODO1xPosPulseTimeStarttimeDiff;
   TH1F          **h1PHODO1yNegPulseTimeStarttimeDiff;
   TH1F          **h1PHODO1yPosPulseTimeStarttimeDiff;
   TH1F          **h1PHODO2xNegPulseTimeStarttimeDiff;
   TH1F          **h1PHODO2xPosPulseTimeStarttimeDiff;
   TH1F          **h1PHODO2yNegPulseTimeStarttimeDiff;
   TH1F          **h1PHODO2yPosPulseTimeStarttimeDiff;


   // Readers to access the data (delete the ones you do not need).
   TTreeReaderValue<Int_t> Ndata_P_hgcer_adcPulseTime = {fReader, "Ndata.P.hgcer.adcPulseTime"};
   TTreeReaderArray<Double_t> P_hgcer_adcCounter = {fReader, "P.hgcer.adcCounter"};
   TTreeReaderArray<Double_t> P_hgcer_adcErrorFlag = {fReader, "P.hgcer.adcErrorFlag"};
   TTreeReaderArray<Double_t> P_hgcer_adcPulseTime = {fReader, "P.hgcer.adcPulseTime"};

   //TTreeReaderValue<Int_t> Ndata_P_ngcer_adcPulseTime = {fReader, "Ndata.P.ngcer.adcPulseTime"};
   //TTreeReaderArray<Double_t> P_ngcer_adcCounter = {fReader, "P.ngcer.adcCounter"};
   //TTreeReaderArray<Double_t> P_ngcer_adcErrorFlag = {fReader, "P.ngcer.adcErrorFlag"};
   //TTreeReaderArray<Double_t> P_ngcer_adcPulseTime = {fReader, "P.ngcer.adcPulseTime"};

   TTreeReaderValue<Int_t> Ndata_P_aero_negAdcPulseTime = {fReader, "Ndata.P.aero.negAdcPulseTime"};
   TTreeReaderArray<Double_t> P_aero_negAdcCounter = {fReader, "P.aero.negAdcCounter"};
   TTreeReaderArray<Double_t> P_aero_negAdcErrorFlag = {fReader, "P.aero.negAdcErrorFlag"};
   TTreeReaderArray<Double_t> P_aero_negAdcPulseTime = {fReader, "P.aero.negAdcPulseTime"};

   TTreeReaderValue<Int_t> Ndata_P_aero_posAdcPulseTime = {fReader, "Ndata.P.aero.posAdcPulseTime"};
   TTreeReaderArray<Double_t> P_aero_posAdcCounter = {fReader, "P.aero.posAdcCounter"};
   TTreeReaderArray<Double_t> P_aero_posAdcErrorFlag = {fReader, "P.aero.posAdcErrorFlag"};
   TTreeReaderArray<Double_t> P_aero_posAdcPulseTime = {fReader, "P.aero.posAdcPulseTime"};

   TTreeReaderValue<Int_t> Ndata_P_precal_negAdcPulseTime = {fReader, "Ndata.P.cal.pr.negAdcPulseTime"};
   TTreeReaderArray<Double_t> P_precal_negAdcCounter = {fReader, "P.cal.pr.negAdcCounter"};
   TTreeReaderArray<Double_t> P_precal_negAdcErrorFlag = {fReader, "P.cal.pr.negAdcErrorFlag"};
   TTreeReaderArray<Double_t> P_precal_negAdcPulseTime = {fReader, "P.cal.pr.negAdcPulseTime"};

   TTreeReaderValue<Int_t> Ndata_P_precal_posAdcPulseTime = {fReader, "Ndata.P.cal.pr.posAdcPulseTime"};
   TTreeReaderArray<Double_t> P_precal_posAdcCounter = {fReader, "P.cal.pr.posAdcCounter"};
   TTreeReaderArray<Double_t> P_precal_posAdcErrorFlag = {fReader, "P.cal.pr.posAdcErrorFlag"};
   TTreeReaderArray<Double_t> P_precal_posAdcPulseTime = {fReader, "P.cal.pr.posAdcPulseTime"};
   
   TTreeReaderValue<Int_t> Ndata_P_cal_adcPulseTime = {fReader, "Ndata.P.cal.fly.adcPulseTime"};
   TTreeReaderArray<Double_t> P_cal_adcCounter = {fReader, "P.cal.fly.adcCounter"};
   TTreeReaderArray<Double_t> P_cal_adcErrorFlag = {fReader, "P.cal.fly.adcErrorFlag"};
   TTreeReaderArray<Double_t> P_cal_adcPulseTime = {fReader, "P.cal.fly.adcPulseTime"};

   TTreeReaderValue<Int_t> Ndata_P_dc_1u1_rawtdc = {fReader, "Ndata.P.dc.1u1.rawtdc"};
   TTreeReaderArray<Double_t> P_dc_1u1_rawtdc = {fReader, "P.dc.1u1.rawtdc"};
   TTreeReaderArray<Double_t> P_dc_1u2_rawtdc = {fReader, "P.dc.1u2.rawtdc"};
   TTreeReaderArray<Double_t> P_dc_1v1_rawtdc = {fReader, "P.dc.1v1.rawtdc"};
   TTreeReaderArray<Double_t> P_dc_1v2_rawtdc = {fReader, "P.dc.1v2.rawtdc"};
   TTreeReaderArray<Double_t> P_dc_1x1_rawtdc = {fReader, "P.dc.1x1.rawtdc"};
   TTreeReaderArray<Double_t> P_dc_1x2_rawtdc = {fReader, "P.dc.1x2.rawtdc"};
   TTreeReaderArray<Double_t> P_dc_2u1_rawtdc = {fReader, "P.dc.2u1.rawtdc"};
   TTreeReaderArray<Double_t> P_dc_2u2_rawtdc = {fReader, "P.dc.2u2.rawtdc"};
   TTreeReaderArray<Double_t> P_dc_2v1_rawtdc = {fReader, "P.dc.2v1.rawtdc"};
   TTreeReaderArray<Double_t> P_dc_2v2_rawtdc = {fReader, "P.dc.2v2.rawtdc"};
   TTreeReaderArray<Double_t> P_dc_2x1_rawtdc = {fReader, "P.dc.2x1.rawtdc"};
   TTreeReaderArray<Double_t> P_dc_2x2_rawtdc = {fReader, "P.dc.2x2.rawtdc"};

   TTreeReaderValue<Int_t> Ndata_P_hod_1x_negAdcPulseTime = {fReader, "Ndata.P.hod.1x.negAdcPulseTime"};
   TTreeReaderValue<Int_t> Ndata_P_hod_1x_negTdcTime      = {fReader, "Ndata.P.hod.1x.negTdcTime"};
   TTreeReaderArray<Double_t> P_hod_1x_negAdcCounter   = {fReader, "P.hod.1x.negAdcCounter"};
   TTreeReaderArray<Double_t> P_hod_1x_negAdcErrorFlag = {fReader, "P.hod.1x.negAdcErrorFlag"};
   TTreeReaderArray<Double_t> P_hod_1x_negAdcPulseTime = {fReader, "P.hod.1x.negAdcPulseTime"};
   TTreeReaderArray<Double_t> P_hod_1x_negTdcTime      = {fReader, "P.hod.1x.negTdcTime"};
   TTreeReaderArray<Double_t> P_hod_1x_negTdcTimeCorr  = {fReader, "P.hod.1x.GoodNegTdcTimeCorr"};

   TTreeReaderValue<Int_t> Ndata_P_hod_1y_negAdcPulseTime = {fReader, "Ndata.P.hod.1y.negAdcPulseTime"};
   TTreeReaderValue<Int_t> Ndata_P_hod_1y_negTdcTime      = {fReader, "Ndata.P.hod.1y.negTdcTime"};
   TTreeReaderArray<Double_t> P_hod_1y_negAdcCounter   = {fReader, "P.hod.1y.negAdcCounter"};
   TTreeReaderArray<Double_t> P_hod_1y_negAdcErrorFlag = {fReader, "P.hod.1y.negAdcErrorFlag"};
   TTreeReaderArray<Double_t> P_hod_1y_negAdcPulseTime = {fReader, "P.hod.1y.negAdcPulseTime"};
   TTreeReaderArray<Double_t> P_hod_1y_negTdcTime      = {fReader, "P.hod.1y.negTdcTime"};
   TTreeReaderArray<Double_t> P_hod_1y_negTdcTimeCorr  = {fReader, "P.hod.1y.GoodNegTdcTimeCorr"};

   TTreeReaderValue<Int_t> Ndata_P_hod_2x_negAdcPulseTime = {fReader, "Ndata.P.hod.2x.negAdcPulseTime"};
   TTreeReaderValue<Int_t> Ndata_P_hod_2x_negTdcTime      = {fReader, "Ndata.P.hod.2x.negTdcTime"};
   TTreeReaderArray<Double_t> P_hod_2x_negAdcCounter   = {fReader, "P.hod.2x.negAdcCounter"};
   TTreeReaderArray<Double_t> P_hod_2x_negAdcErrorFlag = {fReader, "P.hod.2x.negAdcErrorFlag"};
   TTreeReaderArray<Double_t> P_hod_2x_negAdcPulseTime = {fReader, "P.hod.2x.negAdcPulseTime"};
   TTreeReaderArray<Double_t> P_hod_2x_negTdcTime      = {fReader, "P.hod.2x.negTdcTime"};
   TTreeReaderArray<Double_t> P_hod_2x_negTdcTimeCorr  = {fReader, "P.hod.2x.GoodNegTdcTimeCorr"};

   TTreeReaderValue<Int_t> Ndata_P_hod_2y_negAdcPulseTime = {fReader, "Ndata.P.hod.2y.negAdcPulseTime"};
   TTreeReaderValue<Int_t> Ndata_P_hod_2y_negTdcTime      = {fReader, "Ndata.P.hod.2y.negTdcTime"};
   TTreeReaderArray<Double_t> P_hod_2y_negAdcCounter   = {fReader, "P.hod.2y.negAdcCounter"};
   TTreeReaderArray<Double_t> P_hod_2y_negAdcErrorFlag = {fReader, "P.hod.2y.negAdcErrorFlag"};
   TTreeReaderArray<Double_t> P_hod_2y_negAdcPulseTime = {fReader, "P.hod.2y.negAdcPulseTime"};
   TTreeReaderArray<Double_t> P_hod_2y_negTdcTime      = {fReader, "P.hod.2y.negTdcTime"};
   TTreeReaderArray<Double_t> P_hod_2y_negTdcTimeCorr  = {fReader, "P.hod.2y.GoodNegTdcTimeCorr"};

   TTreeReaderValue<Int_t> Ndata_P_hod_1x_posAdcPulseTime = {fReader, "Ndata.P.hod.1x.posAdcPulseTime"};
   TTreeReaderValue<Int_t> Ndata_P_hod_1x_posTdcTime      = {fReader, "Ndata.P.hod.1x.posTdcTime"};
   TTreeReaderArray<Double_t> P_hod_1x_posAdcCounter   = {fReader, "P.hod.1x.posAdcCounter"};
   TTreeReaderArray<Double_t> P_hod_1x_posAdcErrorFlag = {fReader, "P.hod.1x.posAdcErrorFlag"};
   TTreeReaderArray<Double_t> P_hod_1x_posAdcPulseTime = {fReader, "P.hod.1x.posAdcPulseTime"};
   TTreeReaderArray<Double_t> P_hod_1x_posTdcTime      = {fReader, "P.hod.1x.posTdcTime"};
   TTreeReaderArray<Double_t> P_hod_1x_posTdcTimeCorr  = {fReader, "P.hod.1x.GoodPosTdcTimeCorr"};

   TTreeReaderValue<Int_t> Ndata_P_hod_1y_posAdcPulseTime = {fReader, "Ndata.P.hod.1y.posAdcPulseTime"};
   TTreeReaderValue<Int_t> Ndata_P_hod_1y_posTdcTime      = {fReader, "Ndata.P.hod.1y.posTdcTime"};
   TTreeReaderArray<Double_t> P_hod_1y_posAdcCounter   = {fReader, "P.hod.1y.posAdcCounter"};
   TTreeReaderArray<Double_t> P_hod_1y_posAdcErrorFlag = {fReader, "P.hod.1y.posAdcErrorFlag"};
   TTreeReaderArray<Double_t> P_hod_1y_posAdcPulseTime = {fReader, "P.hod.1y.posAdcPulseTime"};
   TTreeReaderArray<Double_t> P_hod_1y_posTdcTime      = {fReader, "P.hod.1y.posTdcTime"};
   TTreeReaderArray<Double_t> P_hod_1y_posTdcTimeCorr  = {fReader, "P.hod.1y.GoodPosTdcTimeCorr"};

   TTreeReaderValue<Int_t> Ndata_P_hod_2x_posAdcPulseTime = {fReader, "Ndata.P.hod.2x.posAdcPulseTime"};
   TTreeReaderValue<Int_t> Ndata_P_hod_2x_posTdcTime      = {fReader, "Ndata.P.hod.2x.posTdcTime"};
   TTreeReaderArray<Double_t> P_hod_2x_posAdcCounter   = {fReader, "P.hod.2x.posAdcCounter"};
   TTreeReaderArray<Double_t> P_hod_2x_posAdcErrorFlag = {fReader, "P.hod.2x.posAdcErrorFlag"};
   TTreeReaderArray<Double_t> P_hod_2x_posAdcPulseTime = {fReader, "P.hod.2x.posAdcPulseTime"};
   TTreeReaderArray<Double_t> P_hod_2x_posTdcTime      = {fReader, "P.hod.2x.posTdcTime"};
   TTreeReaderArray<Double_t> P_hod_2x_posTdcTimeCorr  = {fReader, "P.hod.2x.GoodPosTdcTimeCorr"};

   TTreeReaderValue<Int_t> Ndata_P_hod_2y_posAdcPulseTime = {fReader, "Ndata.P.hod.2y.posAdcPulseTime"};
   TTreeReaderValue<Int_t> Ndata_P_hod_2y_posTdcTime      = {fReader, "Ndata.P.hod.2y.posTdcTime"};
   TTreeReaderArray<Double_t> P_hod_2y_posAdcCounter   = {fReader, "P.hod.2y.posAdcCounter"};
   TTreeReaderArray<Double_t> P_hod_2y_posAdcErrorFlag = {fReader, "P.hod.2y.posAdcErrorFlag"};
   TTreeReaderArray<Double_t> P_hod_2y_posAdcPulseTime = {fReader, "P.hod.2y.posAdcPulseTime"};
   TTreeReaderArray<Double_t> P_hod_2y_posTdcTime      = {fReader, "P.hod.2y.posTdcTime"};
   TTreeReaderArray<Double_t> P_hod_2y_posTdcTimeCorr  = {fReader, "P.hod.2y.GoodPosTdcTimeCorr"};
   
   TTreeReaderValue<Double_t> P_hod_starttime = {fReader, "P.hod.starttime"};

   SHMSADCGates(TTree * /*tree*/ =0) {h1PHGCERPulseTime=0,h1PHGCERPulseTimeStarttimeDiff=0,/*h1PNGCERPulseTime=0,h1PNGCERPulseTimeStarttimeDiff=0,*/h1PAERONegPulseTime=0,h1PAERONegPulseTimeStarttimeDiff=0,h1PAEROPosPulseTime=0,h1PAEROPosPulseTimeStarttimeDiff=0,h1PPRECALNegPulseTime=0,h1PPRECALNegPulseTimeStarttimeDiff=0,h1PPRECALPosPulseTime=0,h1PPRECALPosPulseTimeStarttimeDiff=0,h1PCALPulseTimeStarttimeDiff=0,h1PDCRawTdc=0,h1PHODO1xNegPulseTimeStarttimeDiff=0,h1PHODO1xPosPulseTimeStarttimeDiff=0,h1PHODO1yNegPulseTimeStarttimeDiff=0,h1PHODO1yPosPulseTimeStarttimeDiff=0,h1PHODO2xNegPulseTimeStarttimeDiff=0,h1PHODO2xPosPulseTimeStarttimeDiff=0,h1PHODO2yNegPulseTimeStarttimeDiff=0,h1PHODO2yPosPulseTimeStarttimeDiff=0;}
   virtual ~SHMSADCGates() { }
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

   ClassDef(SHMSADCGates,0);

};

#endif

#ifdef SHMSADCGates_cxx
void SHMSADCGates::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the reader is initialized.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   fReader.SetTree(tree);
}

Bool_t SHMSADCGates::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}


#endif // #ifdef SHMSADCGates_cxx
