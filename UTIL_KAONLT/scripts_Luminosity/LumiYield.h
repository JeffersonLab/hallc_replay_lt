//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Mar 29 11:25:48 2018 by ROOT version 6.10/02
// from TTree T/Hall A Analyzer Output DST
// found on file: /home/rambrose/hallc_replay/ROOTfiles/hms_replay_production_all_1415_-1.root
//////////////////////////////////////////////////////////

#ifndef LumiYield_h
#define LumiYield_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>
#include <TH1.h>
#include <TH2.h>
#include <TCanvas.h>

// Headers needed by this particular selector


class LumiYield : public TSelector {
 public :
  TTreeReader     fReader;  //!the tree reader
  TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

  Bool_t          fFullShow = kFALSE;

  Double_t        PS1;
  Double_t        PS3;

  TH1F           *h_ecut_before;
  TH1F           *h_ecut_after;
  TH1F           *h_ecut_eff;
  TH1F           *h_dp_before;
  TH1F           *h_dp_after;
  TH1F           *h_th_before;
  TH1F           *h_th_after;
  TH1F           *h_ph_before;
  TH1F           *h_ph_after;
  TH1F           *h_show_before;
  TH1F           *h_show_after;
  TH1F           *h_track_before;
  TH1F           *h_track_after;
  TH1F           *h_etrack_before;
  TH1F           *h_etrack_after;

  TH1F           *p_ecut_before;
  TH1F           *p_ecut_after;
  TH1F           *p_ecut_eff;
  TH1F           *p_dp_before;
  TH1F           *p_dp_after;
  TH1F           *p_th_before;
  TH1F           *p_th_after;
  TH1F           *p_ph_before;
  TH1F           *p_ph_after;
  TH1F           *p_show_before;
  TH1F           *p_show_after;
  TH1F           *p_track_before;
  TH1F           *p_track_after;
  TH1F           *p_hadtrack_before;
  TH1F           *p_hadtrack_after;
  TH1F           *p_pitrack_before;
  TH1F           *p_pitrack_after;
  TH1F           *p_Ktrack_before;
  TH1F           *p_Ktrack_after;
  TH1F           *p_ptrack_before;
  TH1F           *p_ptrack_after;

  TH1F           *EventType;
  TH1F           *bcm_before;
  TH1F           *bcm_after;
  TH1F           *EDTM;
  TH1F           *HMS_EDTM;
  TH1F           *SHMS_EDTM;
  TH1F           *TRIG1;
  TH1F           *TRIG3;
  TH1F           *TRIG5;
  TH1F           *TRIG1_cut;
  TH1F           *TRIG3_cut;
  TH1F           *TRIG5_cut;

  // Readers to access the data (delete the ones you do not need).
  TTreeReaderArray<Double_t> H_cal_etotnorm          = {fReader, "H.cal.etotnorm"};
  TTreeReaderArray<Double_t> H_cer_npeSum            = {fReader, "H.cer.npeSum"};
  TTreeReaderArray<Double_t> H_gtr_dp                = {fReader, "H.gtr.dp"};
  TTreeReaderArray<Double_t> H_tr_tg_th              = {fReader, "H.gtr.th"};
  TTreeReaderArray<Double_t> H_tr_tg_ph              = {fReader, "H.gtr.ph"};
  TTreeReaderArray<Double_t> H_tr_beta               = {fReader, "H.tr.beta"};
  TTreeReaderArray<Double_t> H_tr_chi2               = {fReader, "H.tr.chi2"};
  TTreeReaderArray<Double_t> H_tr_ndof               = {fReader, "H.tr.ndof"};
  TTreeReaderArray<Double_t> H_hod_goodscinhit       = {fReader, "H.hod.goodscinhit"};
  TTreeReaderArray<Double_t> H_hod_betanotrack       = {fReader, "H.hod.betanotrack"};
  TTreeReaderArray<Double_t> H_dc_ntrack             = {fReader, "H.dc.ntrack"};

  TTreeReaderArray<Double_t> H_dc_1x1_nhit           = {fReader, "H.dc.1x1.nhit"};
  TTreeReaderArray<Double_t> H_dc_1u2_nhit           = {fReader, "H.dc.1u2.nhit"};
  TTreeReaderArray<Double_t> H_dc_1u1_nhit           = {fReader, "H.dc.1u1.nhit"};
  TTreeReaderArray<Double_t> H_dc_1v1_nhit           = {fReader, "H.dc.1v1.nhit"};
  TTreeReaderArray<Double_t> H_dc_1x2_nhit           = {fReader, "H.dc.1x2.nhit"};
  TTreeReaderArray<Double_t> H_dc_1v2_nhit           = {fReader, "H.dc.1v2.nhit"};

  TTreeReaderArray<Double_t> H_dc_2x1_nhit           = {fReader, "H.dc.2x1.nhit"};
  TTreeReaderArray<Double_t> H_dc_2u2_nhit           = {fReader, "H.dc.2u2.nhit"};
  TTreeReaderArray<Double_t> H_dc_2u1_nhit           = {fReader, "H.dc.2u1.nhit"};
  TTreeReaderArray<Double_t> H_dc_2v1_nhit           = {fReader, "H.dc.2v1.nhit"};
  TTreeReaderArray<Double_t> H_dc_2x2_nhit           = {fReader, "H.dc.2x2.nhit"};
  TTreeReaderArray<Double_t> H_dc_2v2_nhit           = {fReader, "H.dc.2v2.nhit"};
  
  TTreeReaderArray<Double_t> P_cal_etotnorm          = {fReader, "P.cal.etotnorm"};
  TTreeReaderArray<Double_t> P_hgcer_npeSum          = {fReader, "P.hgcer.npeSum"};
  TTreeReaderArray<Double_t> P_aero_npeSum           = {fReader, "P.aero.npeSum"};
  TTreeReaderArray<Double_t> P_gtr_dp                = {fReader, "P.gtr.dp"};
  TTreeReaderArray<Double_t> P_gtr_th                = {fReader, "P.gtr.th"};
  TTreeReaderArray<Double_t> P_gtr_ph                = {fReader, "P.gtr.ph"};
  TTreeReaderArray<Double_t> P_tr_beta               = {fReader, "P.tr.beta"};
  TTreeReaderArray<Double_t> P_tr_chi2               = {fReader, "P.tr.chi2"};
  TTreeReaderArray<Double_t> P_tr_ndof               = {fReader, "P.tr.ndof"};
  TTreeReaderArray<Double_t> P_hod_goodscinhit       = {fReader, "P.hod.goodscinhit"};
  TTreeReaderArray<Double_t> P_hod_betanotrack       = {fReader, "P.hod.betanotrack"};
  TTreeReaderArray<Double_t> P_dc_ntrack             = {fReader, "P.dc.ntrack"};

  TTreeReaderArray<Double_t> P_dc_1x1_nhit           = {fReader, "P.dc.1x1.nhit"};
  TTreeReaderArray<Double_t> P_dc_1u2_nhit           = {fReader, "P.dc.1u2.nhit"};
  TTreeReaderArray<Double_t> P_dc_1u1_nhit           = {fReader, "P.dc.1u1.nhit"};
  TTreeReaderArray<Double_t> P_dc_1v1_nhit           = {fReader, "P.dc.1v1.nhit"};
  TTreeReaderArray<Double_t> P_dc_1x2_nhit           = {fReader, "P.dc.1x2.nhit"};
  TTreeReaderArray<Double_t> P_dc_1v2_nhit           = {fReader, "P.dc.1v2.nhit"};

  TTreeReaderArray<Double_t> P_dc_2x1_nhit           = {fReader, "P.dc.2x1.nhit"};
  TTreeReaderArray<Double_t> P_dc_2u2_nhit           = {fReader, "P.dc.2u2.nhit"};
  TTreeReaderArray<Double_t> P_dc_2u1_nhit           = {fReader, "P.dc.2u1.nhit"};
  TTreeReaderArray<Double_t> P_dc_2v1_nhit           = {fReader, "P.dc.2v1.nhit"};
  TTreeReaderArray<Double_t> P_dc_2x2_nhit           = {fReader, "P.dc.2x2.nhit"};
  TTreeReaderArray<Double_t> P_dc_2v2_nhit           = {fReader, "P.dc.2v2.nhit"};

  TTreeReaderValue<Double_t> H_bcm_bcm4b_AvgCurrent       = {fReader, "H.bcm.bcm4b.AvgCurrent"};
  TTreeReaderValue<Double_t> T_coin_pTRIG1_ROC1_tdcTime   = {fReader, "T.coin.pTRIG1_ROC1_tdcTime"};
  TTreeReaderValue<Double_t> T_coin_pTRIG3_ROC1_tdcTime   = {fReader, "T.coin.pTRIG3_ROC1_tdcTime"};
  TTreeReaderValue<Double_t> T_coin_pTRIG5_ROC1_tdcTime   = {fReader, "T.coin.pTRIG5_ROC1_tdcTime"};
  TTreeReaderValue<Double_t> T_coin_pTRIG1_ROC2_tdcTime   = {fReader, "T.coin.pTRIG1_ROC2_tdcTime"};
  TTreeReaderValue<Double_t> T_coin_pTRIG3_ROC2_tdcTime   = {fReader, "T.coin.pTRIG3_ROC2_tdcTime"};
  TTreeReaderValue<Double_t> T_coin_pTRIG5_ROC2_tdcTime   = {fReader, "T.coin.pTRIG5_ROC2_tdcTime"};
  TTreeReaderValue<Double_t> T_coin_pEDTM_tdcTime         = {fReader, "T.coin.pEDTM_tdcTime"};
  
  TTreeReaderValue<Int_t> EvtType                    = {fReader, "fEvtHdr.fEvtType"};

  LumiYield(TTree * /*tree*/ =0) {h_ecut_before = 0, h_ecut_after = 0, h_ecut_eff = 0, h_dp_before = 0, h_dp_after = 0, h_th_before = 0, h_th_after = 0, h_ph_before = 0, h_ph_after =0, h_show_before=0, h_show_after=0, h_track_before=0, h_track_after=0, h_etrack_before=0, h_etrack_after=0, p_ecut_before = 0, p_ecut_after = 0, p_ecut_eff = 0, p_dp_before = 0, p_dp_after = 0, p_th_before = 0, p_th_after = 0, p_ph_before = 0, p_ph_after =0, p_show_before=0, p_show_after=0, p_track_before=0, p_track_after=0, p_hadtrack_before=0, p_hadtrack_after=0, p_pitrack_before=0, p_pitrack_after=0, p_Ktrack_before=0, p_Ktrack_after=0, p_ptrack_before=0, p_ptrack_after=0, bcm_before=0, bcm_after=0, EventType=0, EDTM=0, SHMS_EDTM=0, HMS_EDTM=0, TRIG1=0,TRIG3=0,TRIG5=0, TRIG1_cut=0,TRIG3_cut=0,TRIG5_cut=0;}
  virtual ~LumiYield() { }
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

  ClassDef(LumiYield,0);

};

#endif

#ifdef LumiYield_cxx
void LumiYield::Init(TTree *tree)
{
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the reader is initialized.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).

  fReader.SetTree(tree);
}

Bool_t LumiYield::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.

  return kTRUE;
}


#endif // #ifdef LumiYield_cxx
