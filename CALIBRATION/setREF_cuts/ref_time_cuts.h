/*
 * Description: Define and Set REF. TIME CUTS 
 * ================================================================
 * Time-stamp: "2019-09-24 13:48:18 trottar"
 * ================================================================
 *
 * Author:  Richard L. Trotta III <trotta@cua.edu>, Carlos Yero <cyero002@fiu.edu>
 *
 * Copyright (c) trottar & Yero1990
 */

#ifndef REF_TIME_CUTS
#define REF_TIME_CUTS


//=====================================================
//==============DEFINE SOME CONSTANTS==================
//=====================================================

static const Double_t tdc_nsperch = 0.09766;   //TDC Conv. ns/channel 

//Define some detectors planes and sides
static const Int_t hod_PLANES = 4;
static const Int_t cal_PLANES = 4;
static const Int_t dc_PLANES = 12;
static const Int_t SIDES = 2;

static const string hod_pl_names[hod_PLANES] = {"1x", "1y", "2x", "2y"};
static const string cal_pl_names[cal_PLANES] = {"1pr", "2ta", "3ta", "4ta"};

static const string hdc_pl_names[dc_PLANES] = {"1u1", "1u2", "1x1", "1x2", "1v2", "1v1", "2v1", "2v2", "2x2", "2x1", "2u2", "2u1"};
static const string pdc_pl_names[dc_PLANES] = {"1u1", "1u2", "1x1", "1x2", "1v1", "1v2", "2v2", "2v1", "2x2", "2x1", "2u2", "2u1"};

static const string side_names[SIDES] = {"GoodPos", "GoodNeg"};
static const string cal_side_names[SIDES] = {"goodPos", "goodNeg"};

static const string nsign[SIDES] = {"+", "-"};

static const Int_t hmaxPMT[hod_PLANES] = {16, 10, 16, 10};
static const Int_t pmaxPMT[hod_PLANES] = {13, 13, 14, 21};

//=====================================================


//=====================================================
//=======Set HMS/SHMS/COIN REference Time Cuts=========
//===================================================== 

//NOTE: These Values must be entered with a "minus(-)" sign in the para file

// Carlos values
//(See /PARAM/HMS/GEN/h_reftime_cut.param, units in Channel)
/* static const Double_t hhod_trefcut = 1600.;      //hodo tdc ref cut */
/* static const Double_t hdc_trefcut = 13400.;      //dc tdc ref cut */
/* static const Double_t hadc_trefcut = 2900.;      //hodo/cer/cal adc ref cut */

//(See /PARAM/SHMS/GEN/p_reftime_cut.param, units in Channel)
/* static const Double_t phod_trefcut = 2800.;            //\**NOTE: Use this to set t_coin_trig_tdcrefcut in tcoin.param */
/* static const Double_t pdc_trefcut = 13700.; */
/* static const Double_t padc_trefcut = 2850.;            //\**NOTE: Use this to set t_coin_trig_tdcrefcut in tcoin.param */

//(See /PARAM/HMS/GEN/h_reftime_cut.param, units in Channel)
static const Double_t hhod_trefcut = 3700.;      //hodo tdc ref cut
static const Double_t hdc_trefcut = 16500.;      //dc tdc ref cut
static const Double_t hadc_trefcut = 5150.;      //hodo/cer/cal adc ref cut

//(See /PARAM/SHMS/GEN/p_reftime_cut.param, units in Channel)
static const Double_t phod_trefcut = 4700.;            //**NOTE: Use this to set t_coin_trig_tdcrefcut in tcoin.param
static const Double_t pdc_trefcut = 15500.;
static const Double_t padc_trefcut = 6150.;            //**NOTE: Use this to set t_coin_trig_tdcrefcut in tcoin.param


//=======================================================




//========================================================
//==========SET DETECTOR TIME WINDOW CUTS=================
//========================================================

//**NOTE** : Hodoscopes /Calorimeters are set from the histogram mean/sigma in the code. (They are ONLY initialized here)

//----------------------------
//------ HMS HODOSCOPES ------
//----------------------------
Double_t hhodo_tWinMin[hod_PLANES][SIDES][16] = {0.};
Double_t hhodo_tWinMax[hod_PLANES][SIDES][16] = {0.};


//-----------------------------
//------ HMS CALORIMETER ------
//-----------------------------
Double_t hCal_tWinMin[cal_PLANES][SIDES][13] = {0.};
Double_t hCal_tWinMax[cal_PLANES][SIDES][13] = {0.};

//-----------------------------
//------ HMS CHERENKOV --------
//-----------------------------
Double_t hCer_tWinMin[2] = {80., 90.};
Double_t hCer_tWinMax[2] = {105., 110.};

//----------------------------------
//------ HMS DRIFT CHAMBERS --------
//----------------------------------
// Deuteron H(e,e'p) Elastics
Double_t hDC_tWinMin[dc_PLANES] = {-14e3, -14e3,   -14e3,   -14e3,  -14.e3,  -14e3,     -14e3,   -14e3,   -14e3,   -14e3,   -14e3,   -14e3   };
Double_t hDC_tWinMax[dc_PLANES] = {-11.e3, -11.9e3, -11.8e3, -11.8e3,-10.6e3, -11.8e3, -10.8e3, -11.6e3, -11.8e3, -11.8e3, -10.6e3, -11.8e3 };



//-----------------------------
//------ SHMS HODOSCOPES ------
//-----------------------------
Double_t phodo_tWinMin[hod_PLANES][SIDES][21] = {0.};
Double_t phodo_tWinMax[hod_PLANES][SIDES][21] = {0.};

//----------------------------------------
//------ SHMS Fly's EYE CALORIMETER ------
//----------------------------------------
Double_t pCal_tWinMin[224] = {0.};
Double_t pCal_tWinMax[224] = {0.};

//-----------------------------------------
//------ SHMS Pre-Shower CALORIMETER ------
//-----------------------------------------

//**NOTE** : { {POS SIDE} , {NEG SIDE} }  --> 1st inner curly brackets contain the PMTs 0, 1, . . . 14  "Time Window Min Cut"
Double_t pPrsh_tWinMin[2][14] = { { -100., -100., -100., -100., -100., -100., -100., -80., -100., -100., -100., -100., -100., -100. }, 
				  { -100., -100., -100., -100., -80., -100., -100., -100., -100., -100., -100, -100., -100., -100. } };


Double_t pPrsh_tWinMax[2][14] =  { { 20., 20., 20., 20., 20., 20., 20., 20., 20., 20., 20., 20., 20., 20. }, 
				   { 20., 20., 20., 20., 20., 20., 20., 20., 20., 20., 20., 20., 20., 20. } };

//----------------------------------------
//------ SHMS HEAVY GAS CHERENKOV --------
//----------------------------------------
Double_t phgcer_tWinMin[4] = {-80., -80., -80, -80};
Double_t phgcer_tWinMax[4] = {40., 40., 40., 40.};

//----------------------------------------
//------ SHMS NOBLE GAS CHERENKOV --------
//----------------------------------------
Double_t pngcer_tWinMin[4] = {-60., -60., -60., -60.};
Double_t pngcer_tWinMax[4] = {40., 40., 40., 40.};

//----------------------------------
//------ HMS DRIFT CHAMBERS --------
//----------------------------------

//Deuteron H(e,e'p) Elastics
//Tighter SHMS DC Time Window Lower Limitcuts (Used run3377), to study the W yield
Double_t pDC_tWinMin[dc_PLANES] = {-13.2e3, -13.2e3,  -13.2e3,   -13.2e3,   -13.2e3,   -13.2e3,   -13.2e3,  -13.2e3,   -13.2e3,  -13.2e3,  -13.2e3,  -13.2e3 };        
Double_t pDC_tWinMax[dc_PLANES] = {-10.5e3,  -10.5e3, -10.5e3, -10.5e3,  -10.5e3,  -10.5e3,  -10.5e3,   -10.5e3,  -10.5e3, -10.5e3, -10.5e3, -10.5e3};      

//---------------------------------------
//----Define and set Multiple of Sigma 
//----to place cuts (Mean +/- nSig*sig) 
//----around ADC:TDC Time Diff HERE ! ! !
//----------------------------------------

//HMS
Double_t hhod_nSig = 4.0;
Double_t hcal_nSig = 4.0;

//SHMS
Double_t phod_nSig = 4.5;
Double_t pcal_nSig = 10.0;


//----------------------------------
//Coincidence Trigger Components: 
//----------------------------------

//**NOTE** : These are found in the PARAM/TRIG/tcoin.param file

// Carlos values
/* static const Double_t ptrg1r1_tWinMin = 2200;    //pTRIG1_ROC1 */
/* static const Double_t ptrg1r1_tWinMax = 3050; */

/* static const Double_t ptrg1r2_tWinMin = 2850;    //pTRIG1_ROC2 */
/* static const Double_t ptrg1r2_tWinMax = 3800; */

/* static const Double_t ptrg4r1_tWinMin = 1900; */
/* static const Double_t ptrg4r1_tWinMax = 2900; */

/* static const Double_t ptrg4r2_tWinMin = 2600; */
/* static const Double_t ptrg4r2_tWinMax = 3550; */


static const Double_t ptrg1r1_tWinMin = 4200;    //pTRIG1_ROC1, 28
static const Double_t ptrg1r1_tWinMax = 6200;

static const Double_t ptrg1r2_tWinMin = 0;    //pTRIG1_ROC2, 59
static const Double_t ptrg1r2_tWinMax = 10000;

static const Double_t ptrg4r1_tWinMin = 4200;    //pTRIG4_ROC1, 31
static const Double_t ptrg4r1_tWinMax = 6200;

static const Double_t ptrg4r2_tWinMin = 5500;   //pTRIG4_ROC2, 62
static const Double_t ptrg4r2_tWinMax = 7000;

//==============================================================


//=============================================
//===========DEFINE HISTOGRAMS=================
//=============================================

//------Define REF Time Histogram Binning--------

//HMS
Double_t hhod_tref_nbins, hhod_tref_xmin, hhod_tref_xmax;
Double_t hdc_tref_nbins, hdc_tref_xmin, hdc_tref_xmax;
Double_t hadc_tref_nbins, hadc_tref_xmin, hadc_tref_xmax;

//SHMS
Double_t phod_tref_nbins, phod_tref_xmin, phod_tref_xmax;
Double_t pdc_tref_nbins, pdc_tref_xmin, pdc_tref_xmax;
Double_t padc_tref_nbins, padc_tref_xmin, padc_tref_xmax;

//----------------------------------------------  
  
//-----Define ADC-TDC Time Diff. Histogram Binning-------

//HMS
Double_t hhod_nbins, hhod_xmin, hhod_xmax;
Double_t hhod_tnbins, hhod_txmin, hhod_txmax;
Double_t hdc_nbins, hdc_xmin, hdc_xmax;
Double_t hcer_nbins, hcer_xmin, hcer_xmax;                                                                                              
Double_t hcal_nbins, hcal_xmin, hcal_xmax;                                                                                                                    

//SHMS
Double_t phod_nbins, phod_xmin, phod_xmax;
Double_t phod_tnbins, phod_txmin, phod_txmax;
Double_t pdc_nbins, pdc_xmin, pdc_xmax;
Double_t phgcer_nbins, phgcer_xmin, phgcer_xmax;                                                                                              
Double_t pngcer_nbins, pngcer_xmin, pngcer_xmax;
Double_t pPrsh_nbins, pPrsh_xmin, pPrsh_xmax;                                                                                                                                                                                                   
Double_t pcal_nbins, pcal_xmin, pcal_xmax;                                                                                                                    
Double_t pPrshAdc_nbins, pPrshAdc_xmin, pPrshAdc_xmax;                                                                                                                                                                                                   
Double_t pcalAdc_nbins, pcalAdc_xmin, pcalAdc_xmax;
//TRG DETECTOR Components
Double_t ptrg1_roc1_nbins, ptrg1_roc1_xmin, ptrg1_roc1_xmax;
Double_t ptrg1_roc2_nbins, ptrg1_roc2_xmin, ptrg1_roc2_xmax;
Double_t ptrg4_roc1_nbins, ptrg4_roc1_xmin, ptrg4_roc1_xmax;
Double_t ptrg4_roc2_nbins, ptrg4_roc2_xmin, ptrg4_roc2_xmax;

//-------------------------------------------------------

//--------Define Histograms for reference time Cuts------

//HMS Histograms
TH1F *H_hodo_Tref;
TH1F *H_DC_Tref[4];
TH1F *H_FADC_Tref;

//HMS Multiplicity CUT Histograms (Apply mult == 1 cut for HMS ref. times, as there was only 1 ref. time, 3/4 for protons)
TH1F *H_hodo_Tref_CUT;
TH1F *H_DC_Tref_CUT[4];
TH1F *H_FADC_Tref_CUT;

//SHMS Histograms
TH1F *P_hodo_Tref1;
TH1F *P_hodo_Tref2;
TH1F *P_DC_Tref[10];
TH1F *P_FADC_Tref;

//SHMS Multiplicity CUT Histograms (Applt mult == 3 cut for SHMS ref. time, as there were 3 ref. time, 3/4, pEL_REAL, pEL_CLEAN)
TH1F *P_hodo_Tref1_CUT;
TH1F *P_hodo_Tref2_CUT;
TH1F *P_DC_Tref_CUT[10];
TH1F *P_FADC_Tref_CUT;

//-------Define Histograms for Time Window Cuts--------

//HMS Histograms
TH1F *H_hod_TdcTimeUnCorr[hod_PLANES][SIDES][16];
TH1F *H_hod_TdcAdcTimeDiff[hod_PLANES][SIDES][16];
TH1F *H_cal_TdcAdcTimeDiff[cal_PLANES][SIDES][13];
TH1F *H_dc_rawTDC[dc_PLANES];
TH1F *H_cer_TdcAdcTimeDiff[2];

//HMS Histograms with Multiplicity == 1 CUT
TH1F *H_hod_TdcAdcTimeDiff_CUT[hod_PLANES][SIDES][16];
TH1F *H_cal_TdcAdcTimeDiff_CUT[cal_PLANES][SIDES][13];
TH1F *H_dc_rawTDC_CUT[dc_PLANES];
TH1F *H_cer_TdcAdcTimeDiff_CUT[2];

//SHMS Histograms
TH1F *P_hod_TdcTimeUnCorr[hod_PLANES][SIDES][21];
TH1F *P_hod_TdcAdcTimeDiff[hod_PLANES][SIDES][21];
TH1F *P_cal_TdcAdcTimeDiff[224];  //fly's eye (224 pmt-channels)
TH1F *P_prSh_TdcAdcTimeDiff[SIDES][14];
TH1F *P_cal_AdcTime[224];  //fly's eye (224 pmt-channels)
TH1F *P_prSh_AdcTime[SIDES][14];
TH1F *P_dc_rawTDC[dc_PLANES];
TH1F *P_hgcer_TdcAdcTimeDiff[4];
TH1F *P_ngcer_TdcAdcTimeDiff[4];

//SHMS Histograms with Multiplicity == 3 CUT
TH1F *P_hod_TdcAdcTimeDiff_CUT[hod_PLANES][SIDES][21];
TH1F *P_cal_TdcAdcTimeDiff_CUT[224];  
TH1F *P_prSh_TdcAdcTimeDiff_CUT[SIDES][14];
TH1F *P_dc_rawTDC_CUT[dc_PLANES];
TH1F *P_hgcer_TdcAdcTimeDiff_CUT[4];
TH1F *P_ngcer_TdcAdcTimeDiff_CUT[4];

//TRG DETECTOR Histograms
TH1F *pTrig1_ROC1_rawTdcTime;
TH1F *pTrig1_ROC2_rawTdcTime;
TH1F *pTrig4_ROC1_rawTdcTime;
TH1F *pTrig4_ROC2_rawTdcTime;

//=========================
//====DEFINE CANVAS========
//=========================

//Define Canvas
//HMS
TCanvas *hms_REF_Canv;                      //canvas to save reference time histograms
TCanvas *hhodoCanv[hod_PLANES][SIDES];
TCanvas *hhodo_tdcCanv[hod_PLANES][SIDES];
TCanvas *hcaloCanv[cal_PLANES][SIDES];
TCanvas *hdcCanv;
TCanvas *hCer_Canv;

//SHMS
TCanvas *shms_REF_Canv;                      //canvas to save reference time histograms
TCanvas *phodoCanv[hod_PLANES][SIDES];
TCanvas *phodo_tdcCanv[hod_PLANES][SIDES];
TCanvas *pcalCanv[16];
TCanvas *pPrshCanv[SIDES];

TCanvas *pcalAdcCanv[16];
TCanvas *pPrshAdcCanv[SIDES];


TCanvas *pdcCanv;
TCanvas *pngCer_Canv;
TCanvas *phgCer_Canv;

//TRG
TCanvas *pTRG_Canv;



//Mean and Sigma. Variables to determine TimeWindow Cut Region
Int_t binmax;
Double_t mean; 
Double_t sig;
  
//=========================================
//Define TLines TO DRAW AROUND CUT REGION
//=========================================

//----Reference Time TLines----

//HMS
TLine *hT1_Line;      //hms trigger ref. time
TLine *hDCREF_Line;  //hms DC ref. time
TLine *hFADC_Line;    //flash ADC ref. time
//SHMS
TLine *pT2_Line;      //shms trigger ref. time
TLine *pDCREF_Line;  //shms DC ref. time
TLine *pFADC_Line;    //flash ADC ref. time

  
//-----Detectors Time Window CUts Lines-----

//HMS
TLine *hhod_LineMin[hod_PLANES][SIDES][16];
TLine *hhod_LineMax[hod_PLANES][SIDES][16];

TLine *hcal_LineMin[cal_PLANES][SIDES][13];
TLine *hcal_LineMax[cal_PLANES][SIDES][13];

TLine *hdc_LineMin[dc_PLANES];
TLine *hdc_LineMax[dc_PLANES];

TLine *hCER_LineMin[2];
TLine *hCER_LineMax[2];

//SHMS
TLine *phod_LineMin[hod_PLANES][SIDES][21];
TLine *phod_LineMax[hod_PLANES][SIDES][21];

TLine *pcal_LineMin[224];
TLine *pcal_LineMax[224];

TLine *pPrsh_LineMin[2][14];
TLine *pPrsh_LineMax[2][14];

TLine *pdc_LineMin[dc_PLANES];
TLine *pdc_LineMax[dc_PLANES];

TLine *phgcer_LineMin[4];
TLine *phgcer_LineMax[4];

TLine *pngcer_LineMin[4];
TLine *pngcer_LineMax[4];

//TRG
TLine *ptrg1r1_LineMin;
TLine *ptrg1r1_LineMax;

TLine *ptrg1r2_LineMin;
TLine *ptrg1r2_LineMax;

TLine *ptrg4r1_LineMin;
TLine *ptrg4r1_LineMax;

TLine *ptrg4r2_LineMin;
TLine *ptrg4r2_LineMax;

//===========================================

  
//========================
//Define TTree Leaf Names 
//========================

TString base;
                                                                                                                                  
//HMS Detector Leaf Names                                                                                                                                         
TString n_hhod_TdcTimeUnCorr;                                                                                                                                
TString n_hhod_TdcAdcTimeDiff;                                                                                                                                             
TString n_hhod_AdcMult;                                                                                                                                                   
TString n_hcal_TdcAdcTimeDiff;                                                                                                                                               
TString n_hcal_AdcMult;                                                                                                                                                         
TString n_hcer_TdcAdcTimeDiff;                                                                                                                      
TString n_hcer_AdcMult;                                                                                                                                                                
TString n_hndata_rawTDC;                                                                                                                          
TString n_hdc_rawTDC; 
TString n_hdc_TdcMult;

//HMS Ref. Time Names
TString n_hT1_ref;
TString n_hDC_ref;
TString n_hFADC_ref;
TString n_hT1_tdcMult;
TString n_hDC_tdcMult;
TString n_hFADC_adcMult;

//SHMS Detector Leaf Names    
TString n_phod_TdcTimeUnCorr;                                                                                                                                 
TString n_phod_TdcAdcTimeDiff;                                                                                                                                                         
TString n_phod_AdcMult;                                                                                                                                                              
TString n_pcal_TdcAdcTimeDiff;                                                                                                                                                        
TString n_pcal_AdcMult;                                                                                                                                                               
TString n_pPrSh_TdcAdcTimeDiff;
TString n_pPrSh_AdcMult;
TString n_pcal_AdcTime;                                                                                                                                                        
TString n_pPrSh_AdcTime;
TString n_phgcer_TdcAdcTimeDiff;                                                                                                                                          
TString n_phgcer_AdcMult;
TString n_pngcer_TdcAdcTimeDiff;                                                                                                                                                      
TString n_pngcer_AdcMult;
TString n_pdc_rawTDC;                                                                                                                                                               
TString n_pndata_rawTDC;                                                                                                                                                               
TString n_pdc_TdcMult;

//SHMS Ref. Time Names                                                                                                                                                                      
TString n_pT1_ref;                                                                                                                                                
TString n_pT2_ref;                                                                                                                                                
TString n_pDC_ref;                                                                                                                                                    
TString n_pFADC_ref;        
TString n_pT1_tdcMult;
TString n_pT2_tdcMult;                                                                                                                                                
TString n_pDC_tdcMult;                                                                                                                                                    
TString n_pFADC_adcMult;                                                                                                                                 

//TRG Detector  Leaf Names
TString n_ptrg1_r1;
TString n_ptrg1_r2;
TString n_ptrg4_r1;
TString n_ptrg4_r2;

//========================================
//Define Variables Associated with Leafs
//========================================

//HMS Leaf Variables
Double_t hhod_TdcTimeUnCorr[hod_PLANES][SIDES][16];
Double_t hhod_TdcAdcTimeDiff[hod_PLANES][SIDES][16];
Double_t hhod_AdcMult[hod_PLANES][SIDES][16];
Double_t hcer_TdcAdcTimeDiff[2];
Double_t hcer_AdcMult[2];
Double_t hcal_TdcAdcTimeDiff[cal_PLANES][SIDES][13];
Double_t hcal_AdcMult[cal_PLANES][SIDES][13];

//HMS Ref. Time Varables                                                                                                                                           
Double_t hT1_ref;                                                                                                    
Double_t hDC_ref[4];                                                                                      
Double_t hFADC_ref;
Double_t hT1_tdcMult;
Double_t hDC_tdcMult[4];
Double_t hFADC_adcMult;

//SHMS Leaf Variables
Double_t phod_TdcTimeUnCorr[hod_PLANES][SIDES][21];
Double_t phod_TdcAdcTimeDiff[hod_PLANES][SIDES][21];
Double_t phod_AdcMult[hod_PLANES][SIDES][21];
Double_t pcal_TdcAdcTimeDiff[1][224];
Double_t pcal_AdcMult[1][224];
Double_t pPrSh_TdcAdcTimeDiff[1][SIDES][14]; 
Double_t pPrSh_AdcMult[1][SIDES][14];
Double_t pcal_AdcTime[1][224];
Double_t pPrSh_AdcTime[1][SIDES][14]; 
Double_t phgcer_TdcAdcTimeDiff[4];
Double_t phgcer_AdcMult[4];
Double_t pngcer_TdcAdcTimeDiff[4];
Double_t pngcer_AdcMult[4];

//SHMS Ref. Time Varables                                                                                                                                           
Double_t pT1_ref;
Double_t pT2_ref;                                                                                                    
Double_t pDC_ref[10];                                                                                      
Double_t pFADC_ref;
Double_t pT1_tdcMult;
Double_t pT2_tdcMult;
Double_t pDC_tdcMult[10];
Double_t pFADC_adcMult;

//Drift Chamber rawTDC / Ndata / Multiplicity
Double_t hdc_rawTDC[dc_PLANES][1000];
Double_t pdc_rawTDC[dc_PLANES][1000];

Int_t hndata_rawTDC[dc_PLANES];
Int_t pndata_rawTDC[dc_PLANES];

//TRG Detector Leaf Variables
Double_t ptrg1_r1;
Double_t ptrg1_r2;
Double_t ptrg4_r1;
Double_t ptrg4_r2;

//=========================================================


#endif 
