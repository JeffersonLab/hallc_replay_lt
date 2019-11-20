// Stephen Kay - University of Regina - 2019 // 

#ifndef DetTCuts_Coin_h
#define DetTCuts_Coin_h

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
const string cal_pl_names[cal_planes] = {"1pr", "2ta", "3ta", "4ta"};

const string dc_pl_names[dc_planes] = {"1u1", "1u2", "1x1", "1x2", "1v1", "1v2", "2u1", "2u2", "2x1", "2x2", "2v1", "2v2"};

const string side_names[sides] = {"GoodPos", "GoodNeg"};
const string cal_side_names[sides] = {"goodPos", "goodNeg"};

const string nsign[sides] = {"+", "-"};

const Int_t hmaxPMT[hod_planes] = {16, 10, 16, 10};
const Int_t pmaxPMT[hod_planes] = {13, 13, 14, 21};

TString HMSDC_Name;
TString HMSCal_Name;
TString HMSHodo_Name;

// Double arrays to store time window values once determined
Double_t HMSCER_tMin[2];
Double_t HMSCER_tMax[2];
Double_t HMSDC_tMin[12];
Double_t HMSDC_tMax[12];
Double_t HMSCAL_tMin[4][2][13];
Double_t HMSCAL_tMax[4][2][13];
Double_t HMSHODO_tMin[4][2][16];
Double_t HMSHODO_tMax[4][2][16];

Double_t SHMSHGC_tMin[4];
Double_t SHMSHGC_tMax[4];
Double_t SHMSAERO_tMin[2][7];
Double_t SHMSAERO_tMax[2][7];
Double_t SHMSDC_tMin[12];
Double_t SHMSDC_tMax[12];
Double_t SHMSHODO_tMin[4][2][21];
Double_t SHMSHODO_tMax[4][2][21];
Double_t SHMSPRSH_tMin[2][14];
Double_t SHMSPRSH_tMax[2][14];
Double_t SHMSCAL_tMin[14][16];
Double_t SHMSCAL_tMax[14][16];

// Arrays of lines to store time window values once determined
TLine *LHMSCER_tMin[2];
TLine *LHMSCER_tMax[2];
TLine *LHMSDC_tMin[12];
TLine *LHMSDC_tMax[12];
TLine *LHMSCAL_tMin[4][2][13];
TLine *LHMSCAL_tMax[4][2][13];
TLine *LHMSHODO_tMin[4][2][16];
TLine *LHMSHODO_tMax[4][2][16];

TLine *LSHMSHGC_tMin[4];
TLine *LSHMSHGC_tMax[4];
TLine *LSHMSAERO_tMin[2][7];
TLine *LSHMSAERO_tMax[2][7];
TLine *LSHMSDC_tMin[12];
TLine *LSHMSDC_tMax[12];
TLine *LSHMSHODO_tMin[4][2][21];
TLine *LSHMSHODO_tMax[4][2][21];
TLine *LSHMSPRSH_tMin[2][14];
TLine *LSHMSPRSH_tMax[2][14];
TLine *LSHMSCAL_tMin[14][16];
TLine *LSHMSCAL_tMax[14][16];

TLine *LCerADCCut;
TLine *LPrShADCCut;

class DetTCuts_Coin : public TSelector {
public :
   TTreeReader    fReader;
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

   // Declaration of histograms
   TH1F           *h1hCerAdcTdcTDiff[2][2]; // Uncut/cut and by PMT
   TH2F           *h2hCerTDiffADCAmp[2];
   TH1F           *h1hdcTdcT[12]; // Array of 12 histograms
   TH1F           *h1hCalAdcTdcTDiff[4][2][13]; // 3D array of 4/2/13 (4 planes, 2 sides, 13 PMTs per side)
   TH1F           *h1hHodoAdcTdcTDiff[4][2][16]; // 3D array of 4/2/16 (4 planes, 2 sides, UP TO 16 PMTs per side)
   TH2F           *h2hHodoTDiffADCAmp[4][2][16];

   TH1F           *h1pHGCAdcTdcTDiff[3][4]; // Uncut/cut/Aerogel Test and by PMT
   TH2F           *h2pHGCTDiffADCAmp[4];
   TH1F           *h1pAeroAdcTdcTDiff[2][7]; // 2D array of 2/7 (2 sides, 7 PMTs per side)
   TH1F           *h1pdcTdcT[12]; // Array of 12 histograms
   TH1F           *h1pHodoAdcTdcTDiff[4][2][21]; // 3D array of 4/2/21 (4 planes, 2 sides, UP TO 21 PMTs per side)
   TH2F           *h2pHodoTDiffADCAmp[4][2][21];
   TH1F           *h1pPrShAdcTdcTDiff[2][2][14]; // 3D array, 2/2/14 (uncut/cut, 2 sides, 14 PMTs per side)
   TH2F           *h2pPrShTDiffADCAmp[2][14];
   TH1F           *h1pCalAdcTdcTDiff[224]; // Array of 224 histograms, 224 PMTs
   TH2F           *h2pCalTDiffADCAmp[224];
   //TH2F           *h2HGCxyDist[4][4];
   TH2F           *h2HGCxyDist[4];

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

   TTreeReaderArray<Double_t> H_hod_1x_GoodPosAdcTdcDiffTime = {fReader, "H.hod.1x.GoodPosAdcTdcDiffTime"};
   TTreeReaderArray<Double_t> H_hod_1x_GoodNegAdcTdcDiffTime = {fReader, "H.hod.1x.GoodNegAdcTdcDiffTime"};
   TTreeReaderArray<Double_t> H_hod_1y_GoodPosAdcTdcDiffTime = {fReader, "H.hod.1y.GoodPosAdcTdcDiffTime"};
   TTreeReaderArray<Double_t> H_hod_1y_GoodNegAdcTdcDiffTime = {fReader, "H.hod.1y.GoodNegAdcTdcDiffTime"};
   TTreeReaderArray<Double_t> H_hod_2x_GoodPosAdcTdcDiffTime = {fReader, "H.hod.2x.GoodPosAdcTdcDiffTime"};
   TTreeReaderArray<Double_t> H_hod_2x_GoodNegAdcTdcDiffTime = {fReader, "H.hod.2x.GoodNegAdcTdcDiffTime"};
   TTreeReaderArray<Double_t> H_hod_2y_GoodPosAdcTdcDiffTime = {fReader, "H.hod.2y.GoodPosAdcTdcDiffTime"};
   TTreeReaderArray<Double_t> H_hod_2y_GoodNegAdcTdcDiffTime = {fReader, "H.hod.2y.GoodNegAdcTdcDiffTime"};
   TTreeReaderArray<Double_t> H_hod_1x_GoodPosAdcPulseAmp    = {fReader, "H.hod.1x.GoodPosAdcPulseAmp"};   
   TTreeReaderArray<Double_t> H_hod_1x_GoodNegAdcPulseAmp    = {fReader, "H.hod.1x.GoodNegAdcPulseAmp"};   
   TTreeReaderArray<Double_t> H_hod_1y_GoodPosAdcPulseAmp    = {fReader, "H.hod.1y.GoodPosAdcPulseAmp"};   
   TTreeReaderArray<Double_t> H_hod_1y_GoodNegAdcPulseAmp    = {fReader, "H.hod.1y.GoodNegAdcPulseAmp"};   
   TTreeReaderArray<Double_t> H_hod_2x_GoodPosAdcPulseAmp    = {fReader, "H.hod.2x.GoodPosAdcPulseAmp"};   
   TTreeReaderArray<Double_t> H_hod_2x_GoodNegAdcPulseAmp    = {fReader, "H.hod.2x.GoodNegAdcPulseAmp"};   
   TTreeReaderArray<Double_t> H_hod_2y_GoodPosAdcPulseAmp    = {fReader, "H.hod.2y.GoodPosAdcPulseAmp"};   
   TTreeReaderArray<Double_t> H_hod_2y_GoodNegAdcPulseAmp    = {fReader, "H.hod.2y.GoodNegAdcPulseAmp"};   
   TTreeReaderArray<Double_t> H_hod_1x_GoodPosAdcMult        = {fReader, "H.hod.1x.GoodPosAdcMult"};
   TTreeReaderArray<Double_t> H_hod_1x_GoodNegAdcMult        = {fReader, "H.hod.1x.GoodNegAdcMult"};
   TTreeReaderArray<Double_t> H_hod_1y_GoodPosAdcMult        = {fReader, "H.hod.1y.GoodPosAdcMult"};
   TTreeReaderArray<Double_t> H_hod_1y_GoodNegAdcMult        = {fReader, "H.hod.1y.GoodNegAdcMult"};
   TTreeReaderArray<Double_t> H_hod_2x_GoodPosAdcMult        = {fReader, "H.hod.2x.GoodPosAdcMult"};
   TTreeReaderArray<Double_t> H_hod_2x_GoodNegAdcMult        = {fReader, "H.hod.2x.GoodNegAdcMult"};
   TTreeReaderArray<Double_t> H_hod_2y_GoodPosAdcMult        = {fReader, "H.hod.2y.GoodPosAdcMult"};
   TTreeReaderArray<Double_t> H_hod_2y_GoodNegAdcMult        = {fReader, "H.hod.2y.GoodNegAdcMult"};

   TTreeReaderArray<Double_t> H_dc_1u1_rawtdc                = {fReader, "H.dc.1u1.rawtdc"};   
   TTreeReaderArray<Double_t> H_dc_1u2_rawtdc                = {fReader, "H.dc.1u2.rawtdc"};   
   TTreeReaderArray<Double_t> H_dc_1x1_rawtdc                = {fReader, "H.dc.1x1.rawtdc"};   
   TTreeReaderArray<Double_t> H_dc_1x2_rawtdc                = {fReader, "H.dc.1x2.rawtdc"};   
   TTreeReaderArray<Double_t> H_dc_1v1_rawtdc                = {fReader, "H.dc.1v1.rawtdc"};   
   TTreeReaderArray<Double_t> H_dc_1v2_rawtdc                = {fReader, "H.dc.1v2.rawtdc"};   
   TTreeReaderArray<Double_t> H_dc_2u1_rawtdc                = {fReader, "H.dc.2u1.rawtdc"};   
   TTreeReaderArray<Double_t> H_dc_2u2_rawtdc                = {fReader, "H.dc.2u2.rawtdc"};   
   TTreeReaderArray<Double_t> H_dc_2x1_rawtdc                = {fReader, "H.dc.2x1.rawtdc"};   
   TTreeReaderArray<Double_t> H_dc_2x2_rawtdc                = {fReader, "H.dc.2x2.rawtdc"};   
   TTreeReaderArray<Double_t> H_dc_2v1_rawtdc                = {fReader, "H.dc.2v1.rawtdc"};   
   TTreeReaderArray<Double_t> H_dc_2v2_rawtdc                = {fReader, "H.dc.2v2.rawtdc"};   
   TTreeReaderArray<Double_t> H_dc_1u1_nhit                  = {fReader, "H.dc.1u1.nhit"};   
   TTreeReaderArray<Double_t> H_dc_1u2_nhit                  = {fReader, "H.dc.1u2.nhit"};   
   TTreeReaderArray<Double_t> H_dc_1x1_nhit                  = {fReader, "H.dc.1x1.nhit"};   
   TTreeReaderArray<Double_t> H_dc_1x2_nhit                  = {fReader, "H.dc.1x2.nhit"};   
   TTreeReaderArray<Double_t> H_dc_1v1_nhit                  = {fReader, "H.dc.1v1.nhit"};   
   TTreeReaderArray<Double_t> H_dc_1v2_nhit                  = {fReader, "H.dc.1v2.nhit"};   
   TTreeReaderArray<Double_t> H_dc_2u1_nhit                  = {fReader, "H.dc.2u1.nhit"};   
   TTreeReaderArray<Double_t> H_dc_2u2_nhit                  = {fReader, "H.dc.2u2.nhit"};   
   TTreeReaderArray<Double_t> H_dc_2x1_nhit                  = {fReader, "H.dc.2x1.nhit"};   
   TTreeReaderArray<Double_t> H_dc_2x2_nhit                  = {fReader, "H.dc.2x2.nhit"};   
   TTreeReaderArray<Double_t> H_dc_2v1_nhit                  = {fReader, "H.dc.2v1.nhit"};   
   TTreeReaderArray<Double_t> H_dc_2v2_nhit                  = {fReader, "H.dc.2v2.nhit"};   

   TTreeReaderArray<Double_t> H_cer_goodAdcTdcDiffTime        = {fReader, "H.cer.goodAdcTdcDiffTime"};
   TTreeReaderArray<Double_t> H_cer_goodAdcPulseAmp           = {fReader, "H.cer.goodAdcPulseAmp"};
   TTreeReaderArray<Double_t> H_cer_goodAdcMult               = {fReader, "H.cer.goodAdcMult"};   

   TTreeReaderArray<Double_t> H_cal_1pr_goodPosAdcTdcDiffTime = {fReader, "H.cal.1pr.goodPosAdcTdcDiffTime"};   
   TTreeReaderArray<Double_t> H_cal_1pr_goodNegAdcTdcDiffTime = {fReader, "H.cal.1pr.goodNegAdcTdcDiffTime"};   
   TTreeReaderArray<Double_t> H_cal_2ta_goodPosAdcTdcDiffTime = {fReader, "H.cal.2ta.goodPosAdcTdcDiffTime"};   
   TTreeReaderArray<Double_t> H_cal_2ta_goodNegAdcTdcDiffTime = {fReader, "H.cal.2ta.goodNegAdcTdcDiffTime"};   
   TTreeReaderArray<Double_t> H_cal_3ta_goodPosAdcTdcDiffTime = {fReader, "H.cal.3ta.goodPosAdcTdcDiffTime"};   
   TTreeReaderArray<Double_t> H_cal_3ta_goodNegAdcTdcDiffTime = {fReader, "H.cal.3ta.goodNegAdcTdcDiffTime"};   
   TTreeReaderArray<Double_t> H_cal_4ta_goodPosAdcTdcDiffTime = {fReader, "H.cal.4ta.goodPosAdcTdcDiffTime"};   
   TTreeReaderArray<Double_t> H_cal_4ta_goodNegAdcTdcDiffTime = {fReader, "H.cal.4ta.goodNegAdcTdcDiffTime"};   
   TTreeReaderArray<Double_t> H_cal_1pr_goodPosAdcMult        = {fReader, "H.cal.1pr.goodPosAdcMult"};   
   TTreeReaderArray<Double_t> H_cal_1pr_goodNegAdcMult        = {fReader, "H.cal.1pr.goodNegAdcMult"};   
   TTreeReaderArray<Double_t> H_cal_2ta_goodPosAdcMult        = {fReader, "H.cal.2ta.goodPosAdcMult"};   
   TTreeReaderArray<Double_t> H_cal_2ta_goodNegAdcMult        = {fReader, "H.cal.2ta.goodNegAdcMult"};   
   TTreeReaderArray<Double_t> H_cal_3ta_goodPosAdcMult        = {fReader, "H.cal.3ta.goodPosAdcMult"};   
   TTreeReaderArray<Double_t> H_cal_3ta_goodNegAdcMult        = {fReader, "H.cal.3ta.goodNegAdcMult"};   
   TTreeReaderArray<Double_t> H_cal_4ta_goodPosAdcMult        = {fReader, "H.cal.4ta.goodPosAdcMult"};   
   TTreeReaderArray<Double_t> H_cal_4ta_goodNegAdcMult        = {fReader, "H.cal.4ta.goodNegAdcMult"};   

   TTreeReaderArray<Double_t> P_hod_1x_GoodPosAdcTdcDiffTime = {fReader, "P.hod.1x.GoodPosAdcTdcDiffTime"};   
   TTreeReaderArray<Double_t> P_hod_1x_GoodNegAdcTdcDiffTime = {fReader, "P.hod.1x.GoodNegAdcTdcDiffTime"};   
   TTreeReaderArray<Double_t> P_hod_1y_GoodPosAdcTdcDiffTime = {fReader, "P.hod.1y.GoodPosAdcTdcDiffTime"};   
   TTreeReaderArray<Double_t> P_hod_1y_GoodNegAdcTdcDiffTime = {fReader, "P.hod.1y.GoodNegAdcTdcDiffTime"};   
   TTreeReaderArray<Double_t> P_hod_2x_GoodPosAdcTdcDiffTime = {fReader, "P.hod.2x.GoodPosAdcTdcDiffTime"};   
   TTreeReaderArray<Double_t> P_hod_2x_GoodNegAdcTdcDiffTime = {fReader, "P.hod.2x.GoodNegAdcTdcDiffTime"};   
   TTreeReaderArray<Double_t> P_hod_2y_GoodPosAdcTdcDiffTime = {fReader, "P.hod.2y.GoodPosAdcTdcDiffTime"};   
   TTreeReaderArray<Double_t> P_hod_2y_GoodNegAdcTdcDiffTime = {fReader, "P.hod.2y.GoodNegAdcTdcDiffTime"};   
   TTreeReaderArray<Double_t> P_hod_1x_GoodPosAdcPulseAmp    = {fReader, "P.hod.1x.GoodPosAdcPulseAmp"};   
   TTreeReaderArray<Double_t> P_hod_1x_GoodNegAdcPulseAmp    = {fReader, "P.hod.1x.GoodNegAdcPulseAmp"};   
   TTreeReaderArray<Double_t> P_hod_1y_GoodPosAdcPulseAmp    = {fReader, "P.hod.1y.GoodPosAdcPulseAmp"};   
   TTreeReaderArray<Double_t> P_hod_1y_GoodNegAdcPulseAmp    = {fReader, "P.hod.1y.GoodNegAdcPulseAmp"};   
   TTreeReaderArray<Double_t> P_hod_2x_GoodPosAdcPulseAmp    = {fReader, "P.hod.2x.GoodPosAdcPulseAmp"};   
   TTreeReaderArray<Double_t> P_hod_2x_GoodNegAdcPulseAmp    = {fReader, "P.hod.2x.GoodNegAdcPulseAmp"};   
   TTreeReaderArray<Double_t> P_hod_2y_GoodPosAdcPulseAmp    = {fReader, "P.hod.2y.GoodPosAdcPulseAmp"};   
   TTreeReaderArray<Double_t> P_hod_2y_GoodNegAdcPulseAmp    = {fReader, "P.hod.2y.GoodNegAdcPulseAmp"};   
   TTreeReaderArray<Double_t> P_hod_1x_GoodPosAdcMult        = {fReader, "P.hod.1x.GoodPosAdcMult"};   
   TTreeReaderArray<Double_t> P_hod_1x_GoodNegAdcMult        = {fReader, "P.hod.1x.GoodNegAdcMult"};   
   TTreeReaderArray<Double_t> P_hod_1y_GoodPosAdcMult        = {fReader, "P.hod.1y.GoodPosAdcMult"};   
   TTreeReaderArray<Double_t> P_hod_1y_GoodNegAdcMult        = {fReader, "P.hod.1y.GoodNegAdcMult"};   
   TTreeReaderArray<Double_t> P_hod_2x_GoodPosAdcMult        = {fReader, "P.hod.2x.GoodPosAdcMult"};   
   TTreeReaderArray<Double_t> P_hod_2x_GoodNegAdcMult        = {fReader, "P.hod.2x.GoodNegAdcMult"};   
   TTreeReaderArray<Double_t> P_hod_2y_GoodPosAdcMult        = {fReader, "P.hod.2y.GoodPosAdcMult"};   
   TTreeReaderArray<Double_t> P_hod_2y_GoodNegAdcMult        = {fReader, "P.hod.2y.GoodNegAdcMult"};   

   TTreeReaderArray<Double_t> P_dc_1u1_rawtdc                = {fReader, "P.dc.1u1.rawtdc"};   
   TTreeReaderArray<Double_t> P_dc_1u2_rawtdc                = {fReader, "P.dc.1u2.rawtdc"};   
   TTreeReaderArray<Double_t> P_dc_1x1_rawtdc                = {fReader, "P.dc.1x1.rawtdc"};   
   TTreeReaderArray<Double_t> P_dc_1x2_rawtdc                = {fReader, "P.dc.1x2.rawtdc"};   
   TTreeReaderArray<Double_t> P_dc_1v1_rawtdc                = {fReader, "P.dc.1v1.rawtdc"};   
   TTreeReaderArray<Double_t> P_dc_1v2_rawtdc                = {fReader, "P.dc.1v2.rawtdc"};   
   TTreeReaderArray<Double_t> P_dc_2u1_rawtdc                = {fReader, "P.dc.2u1.rawtdc"};   
   TTreeReaderArray<Double_t> P_dc_2u2_rawtdc                = {fReader, "P.dc.2u2.rawtdc"};   
   TTreeReaderArray<Double_t> P_dc_2x1_rawtdc                = {fReader, "P.dc.2x1.rawtdc"};   
   TTreeReaderArray<Double_t> P_dc_2x2_rawtdc                = {fReader, "P.dc.2x2.rawtdc"};   
   TTreeReaderArray<Double_t> P_dc_2v1_rawtdc                = {fReader, "P.dc.2v1.rawtdc"};   
   TTreeReaderArray<Double_t> P_dc_2v2_rawtdc                = {fReader, "P.dc.2v2.rawtdc"};   
   TTreeReaderArray<Double_t> P_dc_1u1_nhit                  = {fReader, "P.dc.1u1.nhit"};   
   TTreeReaderArray<Double_t> P_dc_1u2_nhit                  = {fReader, "P.dc.1u2.nhit"};   
   TTreeReaderArray<Double_t> P_dc_1x1_nhit                  = {fReader, "P.dc.1x1.nhit"};   
   TTreeReaderArray<Double_t> P_dc_1x2_nhit                  = {fReader, "P.dc.1x2.nhit"};   
   TTreeReaderArray<Double_t> P_dc_1v1_nhit                  = {fReader, "P.dc.1v1.nhit"};   
   TTreeReaderArray<Double_t> P_dc_1v2_nhit                  = {fReader, "P.dc.1v2.nhit"};   
   TTreeReaderArray<Double_t> P_dc_2u1_nhit                  = {fReader, "P.dc.2u1.nhit"};   
   TTreeReaderArray<Double_t> P_dc_2u2_nhit                  = {fReader, "P.dc.2u2.nhit"};   
   TTreeReaderArray<Double_t> P_dc_2x1_nhit                  = {fReader, "P.dc.2x1.nhit"};   
   TTreeReaderArray<Double_t> P_dc_2x2_nhit                  = {fReader, "P.dc.2x2.nhit"};   
   TTreeReaderArray<Double_t> P_dc_2v1_nhit                  = {fReader, "P.dc.2v1.nhit"};   
   TTreeReaderArray<Double_t> P_dc_2v2_nhit                  = {fReader, "P.dc.2v2.nhit"};   

   TTreeReaderArray<Double_t> P_hgcer_goodAdcTdcDiffTime     = {fReader, "P.hgcer.goodAdcTdcDiffTime"};
   TTreeReaderArray<Double_t> P_hgcer_goodAdcMult            = {fReader, "P.hgcer.goodAdcMult"};
   TTreeReaderArray<Double_t> P_hgcer_goodAdcPulseAmp        = {fReader, "P.hgcer.goodAdcPulseAmp"};

   TTreeReaderArray<Double_t> P_aero_goodPosAdcTdcDiffTime      = {fReader, "P.aero.goodPosAdcTdcDiffTime"};
   TTreeReaderArray<Double_t> P_aero_goodPosAdcMult             = {fReader, "P.aero.goodPosAdcMult"};
   TTreeReaderArray<Double_t> P_aero_goodNegAdcTdcDiffTime      = {fReader, "P.aero.goodNegAdcTdcDiffTime"};
   TTreeReaderArray<Double_t> P_aero_goodNegAdcMult             = {fReader, "P.aero.goodNegAdcMult"};
            
   TTreeReaderArray<Double_t> P_cal_pr_goodPosAdcTdcDiffTime = {fReader, "P.cal.pr.goodPosAdcTdcDiffTime"};   
   TTreeReaderArray<Double_t> P_cal_pr_goodNegAdcTdcDiffTime = {fReader, "P.cal.pr.goodNegAdcTdcDiffTime"};   
   TTreeReaderArray<Double_t> P_cal_pr_goodPosAdcPulseAmp    = {fReader, "P.cal.pr.goodPosAdcPulseAmp"};   
   TTreeReaderArray<Double_t> P_cal_pr_goodNegAdcPulseAmp    = {fReader, "P.cal.pr.goodNegAdcPulseAmp"};   
   TTreeReaderArray<Double_t> P_cal_pr_goodPosAdcMult        = {fReader, "P.cal.pr.goodPosAdcMult"};   
   TTreeReaderArray<Double_t> P_cal_pr_goodNegAdcMult        = {fReader, "P.cal.pr.goodNegAdcMult"};   
   TTreeReaderArray<Double_t> P_cal_fly_goodAdcTdcDiffTime   = {fReader, "P.cal.fly.goodAdcTdcDiffTime"};
   TTreeReaderArray<Double_t> P_cal_fly_goodAdcMult          = {fReader, "P.cal.fly.goodAdcMult"};
   TTreeReaderArray<Double_t> P_cal_fly_goodAdcPulseAmp      = {fReader, "P.cal.fly.goodAdcPulseAmp"};

 DetTCuts_Coin(TTree * /*tree*/ =0) : fChain(0) {}
   virtual ~DetTCuts_Coin() { }
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

   ClassDef(DetTCuts_Coin,0);
};

#endif

#ifdef DetTCuts_Coin_cxx
void DetTCuts_Coin::Init(TTree *tree)
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

Bool_t DetTCuts_Coin::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef DetTCuts_Coin_cxx
