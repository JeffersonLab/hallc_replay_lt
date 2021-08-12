// Stephen Kay - University of Regina - 25/06/20 // 

#ifndef DetRefT_Cuts_h
#define DetRefT_Cuts_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>
#include <TH1.h>
#include <TH2.h>
#include <TNtuple.h>
#include <TLine.h>

const Double_t tdc_nsperch = 0.09766;   //TDC Conv. ns/channel 
// Note, will modify these in future to be user defined at launch of script, hard coding is not good!
const Double_t CerPulseAmpCut = 50;   // Cut on ADC Pulse amp for cherenkovs (HMS CER/SHMS HGC)
const Double_t PrShPulseAmpCut = 40;   // Cut on ADC Pulse amp for SHMS Pre-shower

//Define some detectors planes and sides
const Int_t hod_planes = 4;
const Int_t cal_planes = 4;
const Int_t dc_planes = 12;
const Int_t sides = 2;

Int_t AeroMultSum;

const string hod_pl_names[hod_planes] = {"1x", "1y", "2x", "2y"};
const string hod_side[2] = {"Neg", "Pos"};
const string hod_digi[2] = {"Adc", "Tdc"};

const string dc_pl_names[dc_planes] = {"1u1", "1u2", "1x1", "1x2", "1v1", "1v2", "2u1", "2u2", "2x1", "2x2", "2v1", "2v2"};

const string nsign[sides] = {"+", "-"};

const Int_t hmaxPMT[hod_planes] = {16, 10, 16, 10};
const Int_t pmaxPMT[hod_planes] = {13, 13, 14, 21};

TString HMSDC_Name;
TString HMSCal_Name;
TString HMSHodo_Name;

// Some double arrays to store offset and other info
Double_t HMS_Hodo_Offset_Raw[4][2];
Double_t SHMS_Hodo_Offset_Raw[4][2];
Double_t HMS_Hodo_OffsetErr_Raw[4][2];
Double_t SHMS_Hodo_OffsetErr_Raw[4][2];
Double_t HMSWeightSum1[4];
Double_t HMSWeightSum2[4];
Double_t SHMSWeightSum1[4];
Double_t SHMSWeightSum2[4];
Double_t HMS_Hodo_Offset[4];
Double_t SHMS_Hodo_Offset[4];

class DetRefT_Cuts : public TSelector {
public :
   TTreeReader    fReader;
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

   // Declaration of histograms
   TH1F           *h1HCerRefTime;
   TH1F           *h1HDCRefTime[12];
   TH1F           *h1HHodRefTime[4][2][2];
   TH1F           *h1PHGCRefTime;
   TH1F           *h1PDCRefTime[12];
   TH1F           *h1PHodRefTime[4][2][2];
   TH1F           *h1HHodADCTDCDiffTime[4][2];
   TH1F           *h1PHodADCTDCDiffTime[4][2];
 
   // Readers to access the data
   // Readers for PID/Delta cuts
   TTreeReaderArray<Double_t> H_gtr_dp           = {fReader, "H.gtr.dp"}; 
   TTreeReaderArray<Double_t> P_gtr_dp           = {fReader, "P.gtr.dp"}; 
   TTreeReaderArray<Double_t> H_cal_etotnorm     = {fReader, "H.cal.etotnorm"};  
   TTreeReaderArray<Double_t> P_cal_etotnorm     = {fReader, "P.cal.etotnorm"};
   TTreeReaderValue<Double_t> P_hgcer_xAtCer     = {fReader, "P.hgcer.xAtCer"}; 
   TTreeReaderValue<Double_t> P_hgcer_yAtCer     = {fReader, "P.hgcer.yAtCer"}; 

   // Reader for ADC pulse amp cut
   TTreeReaderValue<Double_t> T_coin_pFADC_TREF_ROC2_adcPulseAmpRaw = {fReader, "T.coin.pFADC_TREF_ROC2_adcPulseAmpRaw"};

   TTreeReaderArray<Double_t> H_cer_RefTime = {fReader, "H.cer.RefTime"};
   TTreeReaderArray<Double_t> H_dc_1u1_RefTime = {fReader, "H.dc.1u1.RefTime"};
   TTreeReaderArray<Double_t> H_dc_1u2_RefTime = {fReader, "H.dc.1u2.RefTime"};
   TTreeReaderArray<Double_t> H_dc_1x1_RefTime = {fReader, "H.dc.1x1.RefTime"};
   TTreeReaderArray<Double_t> H_dc_1x2_RefTime = {fReader, "H.dc.1x2.RefTime"};
   TTreeReaderArray<Double_t> H_dc_1v1_RefTime = {fReader, "H.dc.1v1.RefTime"};
   TTreeReaderArray<Double_t> H_dc_1v2_RefTime = {fReader, "H.dc.1v2.RefTime"};
   TTreeReaderArray<Double_t> H_dc_2u1_RefTime = {fReader, "H.dc.2u1.RefTime"};
   TTreeReaderArray<Double_t> H_dc_2u2_RefTime = {fReader, "H.dc.2u2.RefTime"};
   TTreeReaderArray<Double_t> H_dc_2x1_RefTime = {fReader, "H.dc.2x1.RefTime"};
   TTreeReaderArray<Double_t> H_dc_2x2_RefTime = {fReader, "H.dc.2x2.RefTime"};
   TTreeReaderArray<Double_t> H_dc_2v1_RefTime = {fReader, "H.dc.2v1.RefTime"};
   TTreeReaderArray<Double_t> H_dc_2v2_RefTime = {fReader, "H.dc.2v2.RefTime"};
   TTreeReaderArray<Double_t> H_hod_1x_NegAdcRefTime = {fReader, "H.hod.1x.NegAdcRefTime"};
   TTreeReaderArray<Double_t> H_hod_1y_NegAdcRefTime = {fReader, "H.hod.1y.NegAdcRefTime"};
   TTreeReaderArray<Double_t> H_hod_2x_NegAdcRefTime = {fReader, "H.hod.2x.NegAdcRefTime"};
   TTreeReaderArray<Double_t> H_hod_2y_NegAdcRefTime = {fReader, "H.hod.2y.NegAdcRefTime"};
   TTreeReaderArray<Double_t> H_hod_1x_PosAdcRefTime = {fReader, "H.hod.1x.PosAdcRefTime"};
   TTreeReaderArray<Double_t> H_hod_1y_PosAdcRefTime = {fReader, "H.hod.1y.PosAdcRefTime"};
   TTreeReaderArray<Double_t> H_hod_2x_PosAdcRefTime = {fReader, "H.hod.2x.PosAdcRefTime"};
   TTreeReaderArray<Double_t> H_hod_2y_PosAdcRefTime = {fReader, "H.hod.2y.PosAdcRefTime"};
   TTreeReaderArray<Double_t> H_hod_1x_NegTdcRefTime = {fReader, "H.hod.1x.NegTdcRefTime"};
   TTreeReaderArray<Double_t> H_hod_1y_NegTdcRefTime = {fReader, "H.hod.1y.NegTdcRefTime"};
   TTreeReaderArray<Double_t> H_hod_2x_NegTdcRefTime = {fReader, "H.hod.2x.NegTdcRefTime"};
   TTreeReaderArray<Double_t> H_hod_2y_NegTdcRefTime = {fReader, "H.hod.2y.NegTdcRefTime"};
   TTreeReaderArray<Double_t> H_hod_1x_PosTdcRefTime = {fReader, "H.hod.1x.PosTdcRefTime"};
   TTreeReaderArray<Double_t> H_hod_1y_PosTdcRefTime = {fReader, "H.hod.1y.PosTdcRefTime"};
   TTreeReaderArray<Double_t> H_hod_2x_PosTdcRefTime = {fReader, "H.hod.2x.PosTdcRefTime"};
   TTreeReaderArray<Double_t> H_hod_2y_PosTdcRefTime = {fReader, "H.hod.2y.PosTdcRefTime"};

   TTreeReaderArray<Double_t> P_hgcer_RefTime = {fReader, "P.hgcer.RefTime"};
   TTreeReaderArray<Double_t> P_dc_1u1_RefTime = {fReader, "P.dc.1u1.RefTime"};
   TTreeReaderArray<Double_t> P_dc_1u2_RefTime = {fReader, "P.dc.1u2.RefTime"};
   TTreeReaderArray<Double_t> P_dc_1x1_RefTime = {fReader, "P.dc.1x1.RefTime"};
   TTreeReaderArray<Double_t> P_dc_1x2_RefTime = {fReader, "P.dc.1x2.RefTime"};
   TTreeReaderArray<Double_t> P_dc_1v1_RefTime = {fReader, "P.dc.1v1.RefTime"};
   TTreeReaderArray<Double_t> P_dc_1v2_RefTime = {fReader, "P.dc.1v2.RefTime"};
   TTreeReaderArray<Double_t> P_dc_2u1_RefTime = {fReader, "P.dc.2u1.RefTime"};
   TTreeReaderArray<Double_t> P_dc_2u2_RefTime = {fReader, "P.dc.2u2.RefTime"};
   TTreeReaderArray<Double_t> P_dc_2x1_RefTime = {fReader, "P.dc.2x1.RefTime"};
   TTreeReaderArray<Double_t> P_dc_2x2_RefTime = {fReader, "P.dc.2x2.RefTime"};
   TTreeReaderArray<Double_t> P_dc_2v1_RefTime = {fReader, "P.dc.2v1.RefTime"};
   TTreeReaderArray<Double_t> P_dc_2v2_RefTime = {fReader, "P.dc.2v2.RefTime"};
   TTreeReaderArray<Double_t> P_hod_1x_NegAdcRefTime = {fReader, "P.hod.1x.NegAdcRefTime"};
   TTreeReaderArray<Double_t> P_hod_1y_NegAdcRefTime = {fReader, "P.hod.1y.NegAdcRefTime"};
   TTreeReaderArray<Double_t> P_hod_2x_NegAdcRefTime = {fReader, "P.hod.2x.NegAdcRefTime"};
   TTreeReaderArray<Double_t> P_hod_2y_NegAdcRefTime = {fReader, "P.hod.2y.NegAdcRefTime"};
   TTreeReaderArray<Double_t> P_hod_1x_PosAdcRefTime = {fReader, "P.hod.1x.PosAdcRefTime"};
   TTreeReaderArray<Double_t> P_hod_1y_PosAdcRefTime = {fReader, "P.hod.1y.PosAdcRefTime"};
   TTreeReaderArray<Double_t> P_hod_2x_PosAdcRefTime = {fReader, "P.hod.2x.PosAdcRefTime"};
   TTreeReaderArray<Double_t> P_hod_2y_PosAdcRefTime = {fReader, "P.hod.2y.PosAdcRefTime"};
   TTreeReaderArray<Double_t> P_hod_1x_NegTdcRefTime = {fReader, "P.hod.1x.NegTdcRefTime"};
   TTreeReaderArray<Double_t> P_hod_1y_NegTdcRefTime = {fReader, "P.hod.1y.NegTdcRefTime"};
   TTreeReaderArray<Double_t> P_hod_2x_NegTdcRefTime = {fReader, "P.hod.2x.NegTdcRefTime"};
   TTreeReaderArray<Double_t> P_hod_2y_NegTdcRefTime = {fReader, "P.hod.2y.NegTdcRefTime"};
   TTreeReaderArray<Double_t> P_hod_1x_PosTdcRefTime = {fReader, "P.hod.1x.PosTdcRefTime"};
   TTreeReaderArray<Double_t> P_hod_1y_PosTdcRefTime = {fReader, "P.hod.1y.PosTdcRefTime"};
   TTreeReaderArray<Double_t> P_hod_2x_PosTdcRefTime = {fReader, "P.hod.2x.PosTdcRefTime"};
   TTreeReaderArray<Double_t> P_hod_2y_PosTdcRefTime = {fReader, "P.hod.2y.PosTdcRefTime"};

   TTreeReaderArray<Double_t> H_hod_1x_NegAdcTdcDiffTime = {fReader, "H.hod.1x.GoodNegAdcTdcDiffTime"};
   TTreeReaderArray<Double_t> H_hod_1y_NegAdcTdcDiffTime = {fReader, "H.hod.1y.GoodNegAdcTdcDiffTime"};
   TTreeReaderArray<Double_t> H_hod_2x_NegAdcTdcDiffTime = {fReader, "H.hod.2x.GoodNegAdcTdcDiffTime"};
   TTreeReaderArray<Double_t> H_hod_2y_NegAdcTdcDiffTime = {fReader, "H.hod.2y.GoodNegAdcTdcDiffTime"};
   TTreeReaderArray<Double_t> H_hod_1x_PosAdcTdcDiffTime = {fReader, "H.hod.1x.GoodPosAdcTdcDiffTime"};
   TTreeReaderArray<Double_t> H_hod_1y_PosAdcTdcDiffTime = {fReader, "H.hod.1y.GoodPosAdcTdcDiffTime"};
   TTreeReaderArray<Double_t> H_hod_2x_PosAdcTdcDiffTime = {fReader, "H.hod.2x.GoodPosAdcTdcDiffTime"};
   TTreeReaderArray<Double_t> H_hod_2y_PosAdcTdcDiffTime = {fReader, "H.hod.2y.GoodPosAdcTdcDiffTime"};

   TTreeReaderArray<Double_t> P_hod_1x_NegAdcTdcDiffTime = {fReader, "P.hod.1x.GoodNegAdcTdcDiffTime"};
   TTreeReaderArray<Double_t> P_hod_1y_NegAdcTdcDiffTime = {fReader, "P.hod.1y.GoodNegAdcTdcDiffTime"};
   TTreeReaderArray<Double_t> P_hod_2x_NegAdcTdcDiffTime = {fReader, "P.hod.2x.GoodNegAdcTdcDiffTime"};
   TTreeReaderArray<Double_t> P_hod_2y_NegAdcTdcDiffTime = {fReader, "P.hod.2y.GoodNegAdcTdcDiffTime"};
   TTreeReaderArray<Double_t> P_hod_1x_PosAdcTdcDiffTime = {fReader, "P.hod.1x.GoodPosAdcTdcDiffTime"};
   TTreeReaderArray<Double_t> P_hod_1y_PosAdcTdcDiffTime = {fReader, "P.hod.1y.GoodPosAdcTdcDiffTime"};
   TTreeReaderArray<Double_t> P_hod_2x_PosAdcTdcDiffTime = {fReader, "P.hod.2x.GoodPosAdcTdcDiffTime"};
   TTreeReaderArray<Double_t> P_hod_2y_PosAdcTdcDiffTime = {fReader, "P.hod.2y.GoodPosAdcTdcDiffTime"};

 DetRefT_Cuts(TTree * /*tree*/ =0) : fChain(0) {h1HCerRefTime=0, h1PHGCRefTime=0;}
   virtual ~DetRefT_Cuts() { } 
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

   ClassDef(DetRefT_Cuts,0);
};

#endif

#ifdef DetRefT_Cuts_cxx
void DetRefT_Cuts::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers

  fReader.SetTree(tree);
   
}

Bool_t DetRefT_Cuts::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef DetRefT_Cuts_cxx
