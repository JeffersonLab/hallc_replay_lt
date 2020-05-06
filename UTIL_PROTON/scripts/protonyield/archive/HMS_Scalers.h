//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon May  7 10:38:19 2018 by ROOT version 6.10/02
// from TTree TSH/H  Scaler Data
// found on file: /home/rambrose/hallc_replay/ROOTfiles/hms_replay_production_all_1415_-1.root
//////////////////////////////////////////////////////////
 
#ifndef HMS_Scalers_h
#define HMS_Scalers_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

// Headers needed by this particular selector
const int NBCM = 5;
const int NTRIG = 6;
const int NPRE = 4;
const int NRATE = 6;
const int SHMSNRATE = 8;

class HMS_Scalers : public TSelector {
 public :
  TTreeReader     fReader;  //!the tree reader
  TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

  // Variables useful in Process
  //To find total charge
  string          bcm_name[NBCM];
  Double_t        bcm_value[NBCM];
  Double_t        charge_sum[NBCM];
  Double_t        time_sum[NBCM];
  Double_t        time_total;
  Double_t        previous_charge[NBCM];
  Double_t        previous_time;
  Double_t        current_I;
  Double_t        current_time;
  Int_t           Current;

  //To determine computer livetime
  string          trig_name[NTRIG];
  Double_t        trig_sum[NTRIG];
  Double_t        trig_value[NTRIG];
  Double_t        previous_trig[NTRIG];
  Double_t        pretrigger;
  Double_t        previous_pretrigger;
  Double_t        acctrig_sum;
  Double_t        acctrig_value;
  Double_t        previous_acctrig;

  //To determine HMS electronic livetime
  string          PRE_name[NPRE];
  Double_t        PRE_sum[NPRE];
  Double_t        PRE_value[NPRE];
  Double_t        previous_PRE[NPRE];

  //To determine SHMS electronic livetime
  Double_t        SHMS_PRE_sum[NPRE];
  Double_t        SHMS_PRE_value[NPRE];
  Double_t        SHMS_previous_PRE[NPRE];

  //To determine HMS trigger rates
  string          rate_name[NRATE];
  Double_t        rate_sum[NRATE];
  Double_t        rate_value[NRATE];
  Double_t        previous_rate[NRATE];

  //To determine SHMS trigger rates
  string          SHMS_rate_name[SHMSNRATE];
  Double_t        SHMS_rate_sum[SHMSNRATE];
  Double_t        SHMS_rate_value[SHMSNRATE];
  Double_t        SHMS_previous_rate[SHMSNRATE];

  //To determine number of EDTM events
  Double_t        EDTM_sum;
  Double_t        EDTM_value;
  Double_t        EDTM_current;
  Double_t        previous_EDTM;

  // Readers to access the data (delete the ones you do not need).
  TTreeReaderValue<Double_t> H_BCM4A_scalerCharge = {fReader, "H.BCM4A.scalerCharge"};
  TTreeReaderValue<Double_t> H_BCM2_scalerCharge  = {fReader, "H.BCM2.scalerCharge"};
  TTreeReaderValue<Double_t> H_BCM4B_scalerCharge = {fReader, "H.BCM4B.scalerCharge"};
  TTreeReaderValue<Double_t> H_BCM1_scalerCharge  = {fReader, "H.BCM1.scalerCharge"};
  TTreeReaderValue<Double_t> H_1Mhz_scalerTime    = {fReader, "H.1MHz.scalerTime"};
  TTreeReaderValue<Double_t> H_BCM4C_scalerCharge = {fReader, "H.BCM4C.scalerCharge"};

  TTreeReaderValue<Double_t> H_hTRIG1_scaler = {fReader, "H.pTRIG1.scaler"};
  TTreeReaderValue<Double_t> H_hTRIG2_scaler = {fReader, "H.pTRIG2.scaler"};
  TTreeReaderValue<Double_t> H_hTRIG3_scaler = {fReader, "H.pTRIG3.scaler"};
  TTreeReaderValue<Double_t> H_hTRIG4_scaler = {fReader, "H.pTRIG4.scaler"};
  TTreeReaderValue<Double_t> H_hTRIG5_scaler = {fReader, "H.pTRIG5.scaler"};
  TTreeReaderValue<Double_t> H_hTRIG6_scaler = {fReader, "H.pTRIG6.scaler"};

  TTreeReaderValue<Double_t> H_hL1ACCP_scaler = {fReader, "H.hL1ACCP.scaler"};

  TTreeReaderValue<Double_t> H_hPRE40_scaler  = {fReader, "H.hPRE40.scaler"};
  TTreeReaderValue<Double_t> H_hPRE100_scaler = {fReader, "H.hPRE100.scaler"};
  TTreeReaderValue<Double_t> H_hPRE150_scaler = {fReader, "H.hPRE150.scaler"};
  TTreeReaderValue<Double_t> H_hPRE200_scaler = {fReader, "H.hPRE200.scaler"};

  TTreeReaderValue<Double_t> H_pPRE40_scaler  = {fReader, "H.pPRE40.scaler"};
  TTreeReaderValue<Double_t> H_pPRE100_scaler = {fReader, "H.pPRE100.scaler"};
  TTreeReaderValue<Double_t> H_pPRE150_scaler = {fReader, "H.pPRE150.scaler"};
  TTreeReaderValue<Double_t> H_pPRE200_scaler = {fReader, "H.pPRE200.scaler"};
  
  TTreeReaderValue<Double_t> H_hEL_LO_LO_scaler = {fReader, "H.hEL_LO_LO.scaler"};
  TTreeReaderValue<Double_t> H_hEL_LO_scaler    = {fReader, "H.hEL_LO.scaler"};
  TTreeReaderValue<Double_t> H_hEL_HI_scaler    = {fReader, "H.hEL_HI.scaler"};
  TTreeReaderValue<Double_t> H_hEL_REAL_scaler  = {fReader, "H.hEL_REAL.scaler"};
  TTreeReaderValue<Double_t> H_hEL_CLEAN_scaler = {fReader, "H.hEL_CLEAN.scaler"};
  TTreeReaderValue<Double_t> H_hSTOF_scaler     = {fReader, "H.hSTOF.scaler"};

  TTreeReaderValue<Double_t> H_pEL_LO_LO_scaler = {fReader, "H.pEL_LO_LO.scaler"};
  TTreeReaderValue<Double_t> H_pEL_LO_scaler    = {fReader, "H.pEL_LO.scaler"};
  TTreeReaderValue<Double_t> H_pEL_HI_scaler    = {fReader, "H.pEL_HI.scaler"};
  TTreeReaderValue<Double_t> H_pEL_REAL_scaler  = {fReader, "H.pEL_REAL.scaler"};
  TTreeReaderValue<Double_t> H_pEL_CLEAN_scaler = {fReader, "H.pEL_CLEAN.scaler"};
  TTreeReaderValue<Double_t> H_pSTOF_scaler     = {fReader, "H.pSTOF.scaler"};
  TTreeReaderValue<Double_t> H_pPRHI_scaler     = {fReader, "H.PRHI.scaler"};
  TTreeReaderValue<Double_t> H_pPRLO_scaler     = {fReader, "H.PRLO.scaler"};

  TTreeReaderValue<Double_t> H_EDTM_scaler = {fReader, "H.EDTM.scaler"};

  HMS_Scalers(TTree * /*tree*/ =0) { }
  virtual ~HMS_Scalers() { }
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

  ClassDef(HMS_Scalers,0);

};

#endif

#ifdef HMS_Scalers_cxx
void HMS_Scalers::Init(TTree *tree)
{
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the reader is initialized.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).

  fReader.SetTree(tree);
}

Bool_t HMS_Scalers::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.

  return kTRUE;
}


#endif // #ifdef HMS_Scalers_cxx
