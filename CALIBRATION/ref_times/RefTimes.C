/*
    refTimes.C
    Author: Nathan Heinrich
    
    This is a script for creating referance time time plots, both the overall and detector specific.
    The intent is for an expert to consault the plots while manually setting the referance times.
    This script also automatically applies a multiplicity cut for each variable (where applicable) which is simply hard coded, this should be fine though.
    Also this script assumes running with coin daq, for use in singles daq some alteration is required. 
    
    for following the proccedure here: https://hallcweb.jlab.org/doc-private/ShowDocument?docid=1032
    
    can save to either PDF or Root File (or both), by changing bools below
*/
/*******************************/
//Save options
static const bool SavePDF = true; 
static const bool SaveRoot = false;
static const int  SaveOption = 1; // choose which set of plots to save in PDF (0 = all, 1 = Ref Times, 2 = detector Times)

/*******************************/
//Detector specific Constants

//Drift Chambers
static const Int_t dcPlanes                     = 12;
static const TString dcPlaneNames[dcPlanes]     = {"1u1", "1u2", "1x1", "1x2", "1v1", "1v2", "2u1", "2u2", "2x1", "2x2", "2v1", "2v2"};

//hodoscopes
static const Int_t HodPlanes                    = 4;
static const TString HodPlaneNames[HodPlanes]   = {"1x", "1y", "2x", "2y"};
static const Int_t HodSides                     = 2;
static const TString HodSideNames[HodSides]     = {"Pos", "Neg"};

static const Int_t HodSides1                    = 2;
static const TString HodSideNames1[HodSides1]   = {"pos", "neg"};

static const Int_t MaxHodBars                   = 21;
static const UInt_t hHodbars[HodPlanes]         = {16, 10, 16, 10};
static const UInt_t pHodbars[HodPlanes]         = {13, 13, 14, 21};

//Gas Cherenkovs
static const Int_t pcerNpmts                     = 4;
static const Int_t hcerNpmts                     = 2;

//aerogel
static const Int_t aeroNumPmts                  = 7;
static const Int_t aeroSides                    = 2;
static const TString aeroSideNames[aeroSides]   = {"Pos", "Neg"};

//SHMS Calorimeter
static const Int_t calSides                     = 2;
static const TString calSideNames[calSides]     = {"Pos", "Neg"};
static const Int_t pcalPrNumPmts                = 14;
static const Int_t pcalFlyNumPmts               = 224;

//HMS Calorimeter
static const Int_t hcalPlanes                   = 4;
static const TString hcalPlaneNames[hcalPlanes] = {"1pr", "2ta", "3ta", "4ta"};
static const Int_t hcalNumPmts[hcalPlanes]      = {13, 13, 13, 13};
static const Int_t hcalNumPmtsMax               = 13;

/******  Cuts n' Stuff   ******/
static const TString DaqName = "coin";
Bool_t IsNgcerIn = false;

//***** Branch variables ******/

//coin Ref times
Double_t pTrig1_Roc1;
Double_t pTrig4_Roc1;
Double_t pTrig1_Roc2;
Double_t pTrig4_Roc2;
Double_t pTrig3_Roc1;
Double_t pTrig3_Roc2;
Double_t pT2;

Double_t pTrig1_Roc1_Mult;
Double_t pTrig4_Roc1_Mult;
Double_t pTrig1_Roc2_Mult;
Double_t pTrig4_Roc2_Mult;
Double_t pTrig3_Roc1_Mult;
Double_t pTrig3_Roc2_Mult;
Double_t pT2_Mult;

//ref time variables
Double_t hFADC_TREF_ROC1;
Double_t hTref1, hTref2;
Double_t hDCREF1, hDCREF2, hDCREF3, hDCREF4, hDCREF5; //hDCRef5 not avaiable for runs prior to July 2018
Double_t hFADC_TREF_ROC1_Mult;
Double_t hTref1_Mult, hTref2_Mult;
Double_t hDCREF1_Mult, hDCREF2_Mult, hDCREF3_Mult, hDCREF4_Mult, hDCREF5_Mult;

Double_t pFADC_TREF_ROC2;
Double_t pTref1, pTref2;
Double_t pDCREF1, pDCREF2, pDCREF3, pDCREF4, pDCREF5, pDCREF6, pDCREF7, pDCREF8, pDCREF9, pDCREF10;
Double_t pFADC_TREF_ROC2_Mult;
Double_t pTref1_Mult, pTref2_Mult;
Double_t pDCREF1_Mult, pDCREF2_Mult, pDCREF3_Mult, pDCREF4_Mult, pDCREF5_Mult, pDCREF6_Mult, pDCREF7_Mult, pDCREF8_Mult, pDCREF9_Mult, pDCREF10_Mult;

//dc variables
Double_t hdcrawtdc[dcPlanes],    pdcrawtdc[dcPlanes];
Double_t   hdcnhit[dcPlanes],      pdcnhit[dcPlanes];

// hodoscope variables, 
Double_t hHodAdcTdcDiffTime[HodPlanes][HodSides][MaxHodBars];
Double_t   hHodAdcMult[HodPlanes][HodSides][MaxHodBars];

Double_t pHodAdcTdcDiffTime[HodPlanes][HodSides][MaxHodBars];
Double_t   pHodAdcMult[HodPlanes][HodSides][MaxHodBars];

Double_t hHodAdcPulseTimeRaw[HodPlanes][HodSides1][MaxHodBars];
Double_t   hHodTdcTimeRaw[HodPlanes][HodSides1][MaxHodBars];

Double_t pHodAdcPulseTimeRaw[HodPlanes][HodSides1][MaxHodBars];
Double_t   pHodTdcTimeRaw[HodPlanes][HodSides1][MaxHodBars];

//Gas cherenkovs
//hms
Double_t cerAdcTdcDiffTime[hcerNpmts];
Double_t   cerAdcMult[hcerNpmts];

//shms
Double_t hgcerAdcTdcDiffTime[pcerNpmts], ngcerAdcTdcDiffTime[pcerNpmts];
Double_t hgcerAdcMult[pcerNpmts],        ngcerAdcMult[pcerNpmts];

//aerogel 
Double_t aeroAdcTdcDiffTime[aeroSides][aeroNumPmts];
Double_t   aeroAdcMult[aeroSides][aeroNumPmts];

//Calorimeters
//hms
Double_t hcalAdcTdcDiffTime[hcalPlanes][calSides][hcalNumPmtsMax]; 
Double_t   hcalAdcMult[hcalPlanes][calSides][hcalNumPmtsMax];

//shms
Double_t pcalprAdcTdcDiffTime[calSides][pcalPrNumPmts];
Double_t   pcalprAdcMult[calSides][pcalPrNumPmts];

Double_t pcalflyAdcTdcDiffTime[pcalFlyNumPmts];
Double_t   pcalflyAdcMult[pcalFlyNumPmts];

/*********** Histograms *************/
TH1D	*pTrig1_Roc1_Hist;
TH1D	*pTrig4_Roc1_Hist;
TH1D	*pTrig1_Roc2_Hist;
TH1D	*pTrig4_Roc2_Hist;
TH1D	*pTrig3_Roc1_Hist;
TH1D	*pTrig3_Roc2_Hist;
TH1D	*pT2_Hist;

TH1D	*pTrig1_Roc1_Hist_cut;
TH1D	*pTrig4_Roc1_Hist_cut;
TH1D	*pTrig1_Roc2_Hist_cut;
TH1D	*pTrig4_Roc2_Hist_cut;
TH1D	*pTrig3_Roc1_Hist_cut;
TH1D	*pTrig3_Roc2_Hist_cut;
TH1D	*pT2_Hist_cut;

TH1D	*pTrig1_Roc1_Mult_Hist;
TH1D	*pTrig4_Roc1_Mult_Hist;
TH1D	*pTrig1_Roc2_Mult_Hist;
TH1D	*pTrig4_Roc2_Mult_Hist;
TH1D	*pTrig3_Roc1_Mult_Hist;
TH1D	*pTrig3_Roc2_Mult_Hist;
TH1D	*pT2_Mult_Hist;

TH1D    *hFADC_TREF_ROC1_Hist;
TH1D    *hTref1_Hist, *hTref2_Hist;
TH1D    *hDCREF1_Hist, *hDCREF2_Hist, *hDCREF3_Hist, *hDCREF4_Hist, *hDCREF5_Hist; //hDCRef5 not avaiable for runs prior to July 2018
TH1D    *hFADC_TREF_ROC1_Mult_Hist;
TH1D    *hTref1_Mult_Hist, *hTref2_Mult_Hist;
TH1D    *hDCREF1_Mult_Hist, *hDCREF2_Mult_Hist, *hDCREF3_Mult_Hist, *hDCREF4_Mult_Hist, *hDCREF5_Mult_Hist;

TH1D    *pFADC_TREF_ROC2_Hist;
TH1D    *pTref1_Hist, *pTref2_Hist;
TH1D    *pDCREF1_Hist, *pDCREF2_Hist, *pDCREF3_Hist, *pDCREF4_Hist, *pDCREF5_Hist, *pDCREF6_Hist, *pDCREF7_Hist, *pDCREF8_Hist, *pDCREF9_Hist, *pDCREF10_Hist;
TH1D    *pFADC_TREF_ROC2_Mult_Hist;
TH1D    *pTref1_Mult_Hist, *pTref2_Mult_Hist;
TH1D    *pDCREF1_Mult_Hist, *pDCREF2_Mult_Hist, *pDCREF3_Mult_Hist, *pDCREF4_Mult_Hist, *pDCREF5_Mult_Hist, *pDCREF6_Mult_Hist, *pDCREF7_Mult_Hist, *pDCREF8_Mult_Hist, *pDCREF9_Mult_Hist, *pDCREF10_Mult_Hist;

//dc variables
TH1D    *hdcrawtdc_Hist[dcPlanes],    *pdcrawtdc_Hist[dcPlanes];
TH1D    *hdcnhit_Hist[dcPlanes],      *pdcnhit_Hist[dcPlanes];

// hodoscope variables
TH1D    *hHodAdcTdcDiffTime_Hist[HodPlanes][HodSides][MaxHodBars];
TH1D    *hHodAdcMult_Hist[HodPlanes][HodSides][MaxHodBars];

TH1D    *pHodAdcTdcDiffTime_Hist[HodPlanes][HodSides][MaxHodBars];
TH1D    *pHodAdcMult_Hist[HodPlanes][HodSides][MaxHodBars];

TH1D    *hHodAdcPulseTimeRaw_Hist[HodPlanes][HodSides1][MaxHodBars];
TH1D    *hHodTdcTimeRaw_Hist[HodPlanes][HodSides1][MaxHodBars];

TH1D    *pHodAdcPulseTimeRaw_Hist[HodPlanes][HodSides1][MaxHodBars];
TH1D    *pHodTdcTimeRaw_Hist[HodPlanes][HodSides1][MaxHodBars];

//Gas cherenkovs
//hms
TH1D    *cerAdcTdcDiffTime_Hist_Sum;
TH1D    *cerAdcTdcDiffTime_Hist[hcerNpmts];
TH1D    *cerAdcMult_Hist[hcerNpmts];

//shms
TH1D    *hgcerAdcTdcDiffTime_Hist_Sum, *ngcerAdcTdcDiffTime_Hist_Sum;
TH1D    *hgcerAdcTdcDiffTime_Hist[pcerNpmts], *ngcerAdcTdcDiffTime_Hist[pcerNpmts];
TH1D    *hgcerAdcMult_Hist[pcerNpmts],        *ngcerAdcMult_Hist[pcerNpmts];

//aerogel 
TH1D    *aeroAdcTdcDiffTime_Hist_Sum[aeroSides];
TH1D    *aeroAdcTdcDiffTime_Hist[aeroSides][aeroNumPmts];
TH1D    *aeroAdcMult_Hist[aeroSides][aeroNumPmts];

//Calorimeters
//hms
TH1D    *hcalAdcTdcDiffTime_Hist_Sum[hcalPlanes][calSides];
TH1D    *hcalAdcTdcDiffTime_Hist[hcalPlanes][calSides][hcalNumPmtsMax]; //do this b/c plane one also has the max # of pmts
TH1D    *hcalAdcMult_Hist[hcalPlanes][calSides][hcalNumPmtsMax];

//shms
TH1D    *pcalprAdcTdcDiffTime_Hist_Sum[calSides];
TH1D    *pcalprAdcTdcDiffTime_Hist[calSides][pcalPrNumPmts];
TH1D    *pcalprAdcMult_Hist[calSides][pcalPrNumPmts];

TH1D    *pcalflyAdcTdcDiffTime_Hist_Sum;
TH1D    *pcalflyAdcTdcDiffTime_Hist[pcalFlyNumPmts];
TH1D    *pcalflyAdcMult_Hist[pcalFlyNumPmts];

//cut Varibles.
//these put lines on the plots, not put any cuts on data
Double_t pdc_tdcrefcut, phodo_tdcrefcut, p_adcrefcut, hdc_tdcrefcut, hhodo_tdcrefcut, h_adcrefcut;
//                              1x, 1y, 2x, 2y 
Double_t phodo_PosAdcTimeWindowMin[4*MaxHodBars]= {-20., -20., -20., 0,
                          -20., -20., -20., 0,
                          -20., -20., -20., 0,
                          -20., -20., -20., 0,
                          -20., -20., -20., 0,
                          -20., -20., -20., 0,
                          -20., -20., -20., 0,
                          -20., -20., -20., 0,
                          -20., -20., -20., 0,
                          -20., -20., -20., 0,
                          -20., -20., -20., 0,
                          -20., -20., -20., 0,
                          -20., -20., -20., 0,
                           0.00, 0.00, -20., 0,
                           0.00, 0.00, 0.00, 0,
                           0.00, 0.00, 0.00, 0,
                           0.00, 0.00, 0.00, 0,
                           0.00, 0.00, 0.00, 0,
                           0.00, 0.00, 0.00, 0,
                           0.00, 0.00, 0.00, 0,
                           0.00, 0.00, 0.00, 0};
Double_t phodo_PosAdcTimeWindowMax[4*MaxHodBars] = {60, 60, 60, 70,
                           60, 60, 60, 70,
                           60, 60, 60, 70,
                           60, 60, 60, 70,
                           60, 60, 60, 70,
                           60, 60, 60, 70,
                           60, 60, 60, 70,
                           60, 60, 60, 70,
                           60, 60, 60, 70,
                           60, 60, 60, 70,
                           60, 60, 60, 70,
                           60, 60, 60, 70,
                           60, 60, 60, 70,
                            0.00,  0.00, 60, 70,
                            0.00,  0.00,  0.00, 70,
                            0.00,  0.00,  0.00, 70,
                            0.00,  0.00,  0.00, 70,
                            0.00,  0.00,  0.00, 70,
                            0.00,  0.00,  0.00, 70,
                            0.00,  0.00,  0.00, 70,
                            0.00,  0.00,  0.00, 70};
Double_t phodo_NegAdcTimeWindowMin[4*MaxHodBars] = {-20., -20., -20., 0,
                          -20., -20., -20., 0,
                          -20., -20., -20., 0,
                          -20., -20., -20., 0,
                          -20., -20., -20., 0,
                          -20., -20., -20., 0,
                          -20., -20., -20., 0,
                          -20., -20., -20., 0,
                          -20., -20., -20., 0,
                          -20., -20., -20., 0,
                          -20., -20., -20., 0,
                          -20., -20., -20., 0,
                          -20., -20., -20., 0,
                           0.00, 0.00, -20., 0,
                           0.00, 0.00, 0.00, 0,
                           0.00, 0.00, 0.00, 0,
                           0.00, 0.00, 0.00, 0,
                           0.00, 0.00, 0.00, 0,
                           0.00, 0.00, 0.00, 0,
                           0.00, 0.00, 0.00, 0,
                           0.00, 0.00, 0.00, 0};
Double_t phodo_NegAdcTimeWindowMax[4*MaxHodBars] {60, 60, 60, 70,
                           60, 60, 60, 70,
                           60, 60, 60, 70,
                           60, 60, 60, 70,
                           60, 60, 60, 70,
                           60, 60, 60, 70,
                           60, 60, 60, 70,
                           60, 60, 60, 70,
                           60, 60, 60, 70,
                           60, 60, 60, 70,
                           60, 60, 60, 70,
                           60, 60, 60, 70,
                           60, 60, 60, 70,
                            0.00,  0.00, 60, 70,
                            0.00,  0.00,  0.00, 70,
                            0.00,  0.00,  0.00, 70,
                            0.00,  0.00,  0.00, 70,
                            0.00,  0.00,  0.00, 70,
                            0.00,  0.00,  0.00, 70,
                            0.00,  0.00,  0.00, 70,
                            0.00,  0.00,  0.00, 70};

Double_t hhodo_PosAdcTimeWindowMin[4*MaxHodBars] = {-75, -75, -75, -75,
                          -75, -75, -75, -75,
                          -75, -75, -75, -75,
                          -75, -75, -75, -75,
                          -75, -75, -75, -75,
                          -75, -75, -75, -75,
                          -75, -75, -75, -75,
                          -75, -75, -75, -75,
                          -75, -75, -75, -75,
                          -75, -75, -75, -75,
                          -75, 0.0, -75, 0.0,
                          -75, 0.0, -75, 0.0,
                          -75, 0.0, -75, 0.0,
                          -75, 0.0, -75, 0.0,
                          -75, 0.0, -75, 0.0,
                          -75, 0.0, -75, 0.0};
Double_t hhodo_PosAdcTimeWindowMax[4*MaxHodBars] = {60, 120, 120, 140,
                           60, 120, 120, 140,
                           60, 120, 120, 140,
                           60, 120, 120, 140,
                           60, 120, 120, 140,
                           60, 120, 120, 140,
                           60, 120, 120, 140,
                           60, 120, 120, 140,
                           60, 120, 120, 140,
                           60, 120, 120, 140,
                           60, 120, 120, 140,
                           60, 120, 120, 140,
                           60, 120, 120, 140,
                           60, 120, 120, 140,
                           60, 120, 120, 140,
                           60, 120, 120, 140};
Double_t hhodo_NegAdcTimeWindowMin[4*MaxHodBars] = {-75, -75, -75, -75,
                          -75, -75, -75, -75,
                          -75, -75, -75, -75,
                          -75, -75, -75, -75,
                          -75, -75, -75, -75,
                          -75, -75, -75, -75,
                          -75, -75, -75, -75,
                          -75, -75, -75, -75,
                          -75, -75, -75, -75,
                          -75, -75, -75, -75,
                          -75, 0.0, -75, 0.0,
                          -75, 0.0, -75, 0.0,
                          -75, 0.0, -75, 0.0,
                          -75, 0.0, -75, 0.0,
                          -75, 0.0, -75, 0.0,
                          -75, 0.0, -75, 0.0};
Double_t hhodo_NegAdcTimeWindowMax[4*MaxHodBars] = {60, 120, 120, 140,
                           60, 120, 120, 140,
                           60, 120, 120, 140,
                           60, 120, 120, 140,
                           60, 120, 120, 140,
                           60, 120, 120, 140,
                           60, 120, 120, 140,
                           60, 120, 120, 140,
                           60, 120, 120, 140,
                           60, 120, 120, 140,
                           60, 120, 120, 140,
                           60, 120, 120, 140,
                           60, 120, 120, 140,
                           60, 120, 120, 140,
                           60, 120, 120, 140,
                           60, 120, 120, 140};

Double_t pcal_pos_AdcTimeWindowMin[pcalPrNumPmts] = {-100., -100., -100., -100., -100., -100., -100., -100., -100., -100., -100., -100., -100., -100.};
Double_t pcal_pos_AdcTimeWindowMax[pcalPrNumPmts] = {100., 100., 100., 100., 100., 100., 100., 100., 100., 100., 100., 100., 100., 100.};
Double_t pcal_neg_AdcTimeWindowMin[pcalPrNumPmts] = {-100., -100., -100., -100., -100., -100., -100., -100., -100., -100., -100., -100., -100., -100.};
Double_t pcal_neg_AdcTimeWindowMax[pcalPrNumPmts] = {100., 100., 100., 100., 100., 100., 100., 100., 100., 100., 100., 100., 100., 100.};

Double_t pcal_arr_AdcTimeWindowMin[pcalFlyNumPmts] = {-42,-41.50,-38.50,-38.50,-41.50,-41.50,-44.50,-41.50,-38.50,-44.50,-44.50,-41.50,-41.50,-41.50,
			    -41.50,-41.50,-41.50,-41.50,-38.50,-41.50,-41.50,-41.50,-41.50,-41.50,-41.50,-41.50,-38.50,-41.50,
			    -41.50,-41.50,-41.50,-44.50,-41.50,-41.50,-41.50,-41.50,-41.50,-41.50,-41.50,-41.50,-41.50,-41.50,
			    -41.50,-41.50,-44.50,-44.50,-41.50,-41.50,-41.50,-41.50,-44.50,-41.50,-41.50,-44.50,-38.50,-41.50,
			    -41.50,-41.50,-38.50,-44.50,-41.50,-41.50,-41.50,-41.50,-44.50,-44.50,-44.50,-44.50,-41.50,-41.50,
			    -41.50,-44.50,-44.50,-41.50,-41.50,-44.50,-41.50,-41.50,-44.50,-44.50,-41.50,-41.50,-44.50,-41.50,
			    -44.50,-44.50,-41.50,-41.50,-41.50,-44.50,-41.50,-41.50,-41.50,-47.50,-44.50,-44.50,-41.50,-44.50,
			    -41.50,-41.50,-44.50,-41.50,-41.50,-41.50,-41.50,-44.50,-44.50,-47.50,-41.50,-44.50,-44.50,-44.50,
			    -44.50,-47.50,-44.50,-47.50,-47.50,-47.50,-47.50,-44.50,-47.50,-47.50,-44.50,-47.50,-44.50,-47.50,
			    -50.50,-44.50,-44.50,-47.50,-47.50,-47.50,-44.50,-44.50,-50.50,-47.50,-44.50,-44.50,-50.50,-44.50,
			    -47.50,-47.50,-47.50,-50.50,-44.50,-44.50,-50.50,-47.50,-47.50,-44.50,-47.50,-44.50,-47.50,-47.50,
			    -47.50,-47.50,-47.50,-47.50,-50.50,-47.50,-41.50,-47.50,-44.50,-44.50,-47.50,-44.50,-47.50,-44.50,
			    -44.50,-44.50,-47.50,-47.50,-47.50,-47.50,-47.50,-47.50,-44.50,-44.50,-44.50,-44.50,-44.50,-47.50,
			    -47.50,-47.50,-44.50,-44.50,-47.50,-47.50,-44.50,-44.50,-44.50,-47.50,-44.50,-44.50,-47.50,-41.50,
			    -44.50,-41.50,-44.50,-44.50,-41.50,-44.50,-44.50,-44.50,-44.50,-44.50,-44.50,-44.50,-44.50,-41.50,
			    -41.50,-47.50,-44.50,-44.50,-44.50,-44.50,-44.50,-44.50,-44.50,-44.50,-44.50,-44.50,-44.50,-44.50};
Double_t pcal_arr_AdcTimeWindowMax[pcalFlyNumPmts] = {38.50,38.50,41.50,41.50,38.50,38.50,35.50,38.50,41.50,35.50,35.50,38.50,38.50,38.50, 38.50,38.50,38.50,38.50,41.50,38.50,38.50,38.50,38.50,38.50,38.50,38.50,41.50,38.50, 38.50,38.50,38.50,35.50,38.50,38.50,38.50,38.50,38.50,38.50,38.50,38.50,38.50,38.50, 38.50,38.50,35.50,35.50,38.50,38.50,38.50,38.50,35.50,38.50,38.50,35.50,41.50,38.50, 38.50,38.50,41.50,35.50,38.50,38.50,38.50,38.50,35.50,35.50,35.50,35.50,38.50,38.50, 38.50,35.50,35.50,38.50,38.50,35.50,38.50,38.50,35.50,35.50,38.50,38.50,35.50,38.50,  35.50,35.50,38.50,38.50,38.50,35.50,38.50,38.50,38.50,32.50,35.50,35.50,38.50,35.50, 38.50,38.50,35.50,38.50,38.50,38.50,38.50,35.50,35.50,32.50,38.50,35.50,35.50,35.50, 35.50,32.50,35.50,32.50,32.50,32.50,32.50,35.50,32.50,32.50,35.50,32.50,35.50,32.50, 29.50,35.50,35.50,32.50,32.50,32.50,35.50,35.50,29.50,32.50,35.50,35.50,29.50,35.50, 32.50,32.50,32.50,29.50,35.50,35.50,29.50,32.50,32.50,35.50,32.50,35.50,32.50,32.50, 32.50,32.50,32.50,32.50,29.50,32.50,38.50,32.50,35.50,35.50,32.50,35.50,32.50,35.50, 35.50,35.50,32.50,32.50,32.50,32.50,32.50,32.50,35.50,35.50,35.50,35.50,35.50,32.50, 32.50,32.50,35.50,35.50,32.50,32.50,35.50,35.50,35.50,32.50,35.50,35.50,32.50,38.50, 35.50,38.50,35.50,35.50,38.50,35.50,35.50,35.50,35.50,35.50,35.50,35.50,35.50,38.50, 38.50,32.50,35.50,35.50,35.50,35.50,35.50,35.50,35.50,35.50,35.50,35.50,35.50,35.50};

Double_t hcal_pos_AdcTimeWindowMin[hcalNumPmtsMax*4] = {-70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,
                                                        -70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,
                                                        -70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,
                                                        -70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.};
Double_t hcal_pos_AdcTimeWindowMax[hcalNumPmtsMax*4] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,
                                                        -10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,
                                                        -10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,
                                                        -10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
Double_t hcal_neg_AdcTimeWindowMin[hcalNumPmtsMax*4] = {-70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,
                                                        -70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,
                                                        -70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,
                                                        -70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.};
Double_t hcal_neg_AdcTimeWindowMax[hcalNumPmtsMax*4] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,
                                                        -10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,
                                                        -10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,
                                                        -10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};

Double_t pdc_tdc_min_win[dcPlanes] = {-12700.00, -12700.00, -12700.00, -12700.00, -12700.00, -12700.00, -12700.00, -12700.00, -12700.00, -12700.00, -12700.00, -12700.00};
Double_t pdc_tdc_max_win[dcPlanes] = {-11000.00, -11000.00, -11000.00, -11000.00, -11000.00, -11000.00, -11000.00, -11000.00, -11000.00, -11000.00, -11000.00, -11000.00};

Double_t hdc_tdc_min_win[dcPlanes] = {-13300.00, -13300.00, -13300.00, -13300.00, -13300.00, -13300.00, -13300.00, -13300.00, -13300.00, -13300.00, -13300.00, -13300.00};
Double_t hdc_tdc_max_win[dcPlanes] = {-11500.00, -11500.00, -11500.00, -11500.00, -11500.00, -11500.00, -11500.00, -11500.00, -11500.00, -11500.00, -11500.00, -11500.00};

Double_t phgcer_adcTimeWindowMin[pcerNpmts] = {-6.0, -6.0, -6.0, -6.0};
Double_t phgcer_adcTimeWindowMax[pcerNpmts] = {20.0,  20.0,  20.0,  20.0};

Double_t pngcer_adcTimeWindowMin[pcerNpmts] = {-5.0, -5.0, -5.0, -5.0};
Double_t pngcer_adcTimeWindowMax[pcerNpmts] = {30.0,  30.0,  30.0,  30.0};

Double_t hcer_adcTimeWindowMin[hcerNpmts] =  {110., 110.};
Double_t hcer_adcTimeWindowMax[hcerNpmts] =  {170., 170.};

Double_t paero_adcPosTimeWindowMin[aeroNumPmts] = {-20., -20., -20., -20., -20., -20., -20.};
Double_t paero_adcNegTimeWindowMin[aeroNumPmts] = {170., 170., 170., 170., 170., 170., 170.};
Double_t paero_adcPosTimeWindowMax[aeroNumPmts] = {40., 40., 40., 40., 40., 40., 40.};
Double_t paero_adcNegTimeWindowMax[aeroNumPmts] = {240., 240., 240., 240., 240., 240., 240.};

// Function that sets the location of illustritive cut values for all the plots,
// I have left this hard coded for now but this could (and maybe should) be read from the respective files.
// Code could be lifted from hcana... probably - NH
void setCutValues(/* Could put the standard.database file here. */)
{   
    // These should be posistive even if they are set negative in the code.
    //shms refTime
    pdc_tdcrefcut    =14400.;
    phodo_tdcrefcut  =4200.;
    p_adcrefcut  =5100.;
    //HMS reftime
    hdc_tdcrefcut   =14500.;
    hhodo_tdcrefcut =2600.;
    h_adcrefcut =3400.;
}

// sets the addresses of all the variables that are to be used and/or plotted
void setBranchAddresses(TTree* DataTree)
{
    //coin Ref times
    DataTree->SetBranchAddress("T.coin.pTRIG1_ROC1_tdcTimeRaw", &pTrig1_Roc1);
    DataTree->SetBranchAddress("T.coin.pTRIG4_ROC1_tdcTimeRaw", &pTrig4_Roc1);
    DataTree->SetBranchAddress("T.coin.pTRIG1_ROC2_tdcTimeRaw", &pTrig1_Roc2);
    DataTree->SetBranchAddress("T.coin.pTRIG4_ROC2_tdcTimeRaw", &pTrig4_Roc2);
    DataTree->SetBranchAddress("T.coin.pTRIG3_ROC1_tdcTimeRaw", &pTrig3_Roc1);
    DataTree->SetBranchAddress("T.coin.pTRIG3_ROC2_tdcTimeRaw", &pTrig3_Roc2);
    //DataTree->SetBranchAddress("T.coin.pT2_tdcTimeRaw", &pT2);
    //DataTree->SetBranchAddress("T.coin.pT2_tdcMultiplicity", &pT2_Mult);
    
    DataTree->SetBranchAddress("T.coin.pTRIG1_ROC1_tdcMultiplicity", &pTrig1_Roc1_Mult);
    DataTree->SetBranchAddress("T.coin.pTRIG4_ROC1_tdcMultiplicity", &pTrig4_Roc1_Mult);
    DataTree->SetBranchAddress("T.coin.pTRIG1_ROC2_tdcMultiplicity", &pTrig1_Roc2_Mult);
    DataTree->SetBranchAddress("T.coin.pTRIG4_ROC2_tdcMultiplicity", &pTrig4_Roc2_Mult);
    DataTree->SetBranchAddress("T.coin.pTRIG3_ROC1_tdcMultiplicity", &pTrig3_Roc1_Mult);
    DataTree->SetBranchAddress("T.coin.pTRIG3_ROC2_tdcMultiplicity", &pTrig3_Roc2_Mult);
    
    //assign Branches to ref Time variables
    DataTree->SetBranchAddress(Form("T.%s.hFADC_TREF_ROC1_adcPulseTimeRaw", DaqName.Data()), &hFADC_TREF_ROC1);
    DataTree->SetBranchAddress(Form("T.%s.hT1_tdcTimeRaw", DaqName.Data()), &hTref1);
    DataTree->SetBranchAddress(Form("T.%s.hT2_tdcTimeRaw", DaqName.Data()), &hTref2);
    DataTree->SetBranchAddress(Form("T.%s.hDCREF1_tdcTimeRaw", DaqName.Data()), &hDCREF1);
    DataTree->SetBranchAddress(Form("T.%s.hDCREF2_tdcTimeRaw", DaqName.Data()), &hDCREF2);
    DataTree->SetBranchAddress(Form("T.%s.hDCREF3_tdcTimeRaw", DaqName.Data()), &hDCREF3);
    DataTree->SetBranchAddress(Form("T.%s.hDCREF4_tdcTimeRaw", DaqName.Data()), &hDCREF4);
    DataTree->SetBranchAddress(Form("T.%s.hDCREF5_tdcTimeRaw", DaqName.Data()), &hDCREF5);
    //multiplicity
    DataTree->SetBranchAddress(Form("T.%s.hFADC_TREF_ROC1_adcMultiplicity", DaqName.Data()), &hFADC_TREF_ROC1_Mult);
    DataTree->SetBranchAddress(Form("T.%s.hT1_tdcMultiplicity", DaqName.Data()), &hTref1_Mult);
    DataTree->SetBranchAddress(Form("T.%s.hT2_tdcMultiplicity", DaqName.Data()), &hTref2_Mult);
    DataTree->SetBranchAddress(Form("T.%s.hDCREF1_tdcMultiplicity", DaqName.Data()), &hDCREF1_Mult);
    DataTree->SetBranchAddress(Form("T.%s.hDCREF2_tdcMultiplicity", DaqName.Data()), &hDCREF2_Mult);
    DataTree->SetBranchAddress(Form("T.%s.hDCREF3_tdcMultiplicity", DaqName.Data()), &hDCREF3_Mult);
    DataTree->SetBranchAddress(Form("T.%s.hDCREF4_tdcMultiplicity", DaqName.Data()), &hDCREF4_Mult);
    DataTree->SetBranchAddress(Form("T.%s.hDCREF5_tdcMultiplicity", DaqName.Data()), &hDCREF5_Mult);
    
    DataTree->SetBranchAddress(Form("T.%s.pFADC_TREF_ROC2_adcPulseTimeRaw", DaqName.Data()), &pFADC_TREF_ROC2);
    DataTree->SetBranchAddress(Form("T.%s.pT1_tdcTimeRaw", DaqName.Data()), &pTref1);
    DataTree->SetBranchAddress(Form("T.%s.pT2_tdcTimeRaw", DaqName.Data()), &pTref2);
    DataTree->SetBranchAddress(Form("T.%s.pDCREF1_tdcTimeRaw", DaqName.Data()), &pDCREF1);
    DataTree->SetBranchAddress(Form("T.%s.pDCREF2_tdcTimeRaw", DaqName.Data()), &pDCREF2);
    DataTree->SetBranchAddress(Form("T.%s.pDCREF3_tdcTimeRaw", DaqName.Data()), &pDCREF3);
    DataTree->SetBranchAddress(Form("T.%s.pDCREF4_tdcTimeRaw", DaqName.Data()), &pDCREF4);
    DataTree->SetBranchAddress(Form("T.%s.pDCREF5_tdcTimeRaw", DaqName.Data()), &pDCREF5);
    DataTree->SetBranchAddress(Form("T.%s.pDCREF6_tdcTimeRaw", DaqName.Data()), &pDCREF6);
    DataTree->SetBranchAddress(Form("T.%s.pDCREF7_tdcTimeRaw", DaqName.Data()), &pDCREF7);
    DataTree->SetBranchAddress(Form("T.%s.pDCREF8_tdcTimeRaw", DaqName.Data()), &pDCREF8);
    DataTree->SetBranchAddress(Form("T.%s.pDCREF9_tdcTimeRaw", DaqName.Data()), &pDCREF9);
    DataTree->SetBranchAddress(Form("T.%s.pDCREF10_tdcTimeRaw", DaqName.Data()), &pDCREF10);
    
    DataTree->SetBranchAddress(Form("T.%s.pFADC_TREF_ROC2_adcMultiplicity", DaqName.Data()), &pFADC_TREF_ROC2_Mult);
    DataTree->SetBranchAddress(Form("T.%s.pT1_tdcMultiplicity", DaqName.Data()), &pTref1_Mult);
    DataTree->SetBranchAddress(Form("T.%s.pT2_tdcMultiplicity", DaqName.Data()), &pTref2_Mult);
    DataTree->SetBranchAddress(Form("T.%s.pDCREF1_tdcMultiplicity", DaqName.Data()), &pDCREF1_Mult);
    DataTree->SetBranchAddress(Form("T.%s.pDCREF2_tdcMultiplicity", DaqName.Data()), &pDCREF2_Mult);
    DataTree->SetBranchAddress(Form("T.%s.pDCREF3_tdcMultiplicity", DaqName.Data()), &pDCREF3_Mult);
    DataTree->SetBranchAddress(Form("T.%s.pDCREF4_tdcMultiplicity", DaqName.Data()), &pDCREF4_Mult);
    DataTree->SetBranchAddress(Form("T.%s.pDCREF5_tdcMultiplicity", DaqName.Data()), &pDCREF5_Mult);
    DataTree->SetBranchAddress(Form("T.%s.pDCREF6_tdcMultiplicity", DaqName.Data()), &pDCREF6_Mult);
    DataTree->SetBranchAddress(Form("T.%s.pDCREF7_tdcMultiplicity", DaqName.Data()), &pDCREF7_Mult);
    DataTree->SetBranchAddress(Form("T.%s.pDCREF8_tdcMultiplicity", DaqName.Data()), &pDCREF8_Mult);
    DataTree->SetBranchAddress(Form("T.%s.pDCREF9_tdcMultiplicity", DaqName.Data()), &pDCREF9_Mult);
    DataTree->SetBranchAddress(Form("T.%s.pDCREF10_tdcMultiplicity", DaqName.Data()), &pDCREF10_Mult);
    
    //assign branches to dc variables.
    for(Int_t i = 0; i < dcPlanes; i++)
    {
        DataTree->SetBranchAddress(Form("H.dc.%s.rawtdc", dcPlaneNames[i].Data()), &hdcrawtdc[i]);
        DataTree->SetBranchAddress(Form("H.dc.%s.nhit", dcPlaneNames[i].Data()), &hdcnhit[i]);
        DataTree->SetBranchAddress(Form("P.dc.%s.rawtdc", dcPlaneNames[i].Data()), &pdcrawtdc[i]);
        DataTree->SetBranchAddress(Form("P.dc.%s.nhit", dcPlaneNames[i].Data()), &pdcnhit[i]);
    }
    
    //assign branches to hod variables
    for(Int_t iPlane = 0; iPlane < HodPlanes; iPlane++)
    {
        for(Int_t iSide = 0; iSide < HodSides; iSide++)
        {
            DataTree->SetBranchAddress(Form("H.hod.%s.Good%sAdcTdcDiffTime", HodPlaneNames[iPlane].Data(), HodSideNames[iSide].Data()), &hHodAdcTdcDiffTime[iPlane][iSide]);
            DataTree->SetBranchAddress(Form("H.hod.%s.Good%sAdcMult", HodPlaneNames[iPlane].Data(), HodSideNames[iSide].Data()), &hHodAdcMult[iPlane][iSide]);

            DataTree->SetBranchAddress(Form("P.hod.%s.Good%sAdcTdcDiffTime", HodPlaneNames[iPlane].Data(), HodSideNames[iSide].Data()), &pHodAdcTdcDiffTime[iPlane][iSide]);
            DataTree->SetBranchAddress(Form("P.hod.%s.Good%sAdcMult", HodPlaneNames[iPlane].Data(), HodSideNames[iSide].Data()), &pHodAdcMult[iPlane][iSide]);
        }
    }

    for(Int_t iPlane = 0; iPlane < HodPlanes; iPlane++)
    {
        for(Int_t iSide = 0; iSide < HodSides1; iSide++)
        {
           DataTree->SetBranchAddress(Form("H.hod.%s.%sAdcPulseTimeRaw", HodPlaneNames[iPlane].Data(), HodSideNames1[iSide].Data()), &hHodAdcPulseTimeRaw[iPlane][iSide]);
           DataTree->SetBranchAddress(Form("H.hod.%s.%sTdcTimeRaw", HodPlaneNames[iPlane].Data(), HodSideNames1[iSide].Data()), &hHodTdcTimeRaw[iPlane][iSide]);

           DataTree->SetBranchAddress(Form("P.hod.%s.%sAdcPulseTimeRaw", HodPlaneNames[iPlane].Data(), HodSideNames1[iSide].Data()), &pHodAdcPulseTimeRaw[iPlane][iSide]);
           DataTree->SetBranchAddress(Form("P.hod.%s.%sTdcTimeRaw", HodPlaneNames[iPlane].Data(), HodSideNames1[iSide].Data()), &pHodTdcTimeRaw[iPlane][iSide]);
        }
    }

    //hms gas cherenkov
    DataTree->SetBranchAddress("H.cer.goodAdcTdcDiffTime", &cerAdcTdcDiffTime);
    DataTree->SetBranchAddress("H.cer.goodAdcMult", &cerAdcMult);

    //shms gas cherenkov
    DataTree->SetBranchAddress("P.hgcer.goodAdcTdcDiffTime", &hgcerAdcTdcDiffTime);
    DataTree->SetBranchAddress("P.hgcer.goodAdcMult", &hgcerAdcMult);
    
    //check if ngcer is in this file before trying to add it
    if( DataTree->GetBranch("P.ngcer.goodAdcTdcDiffTime") != NULL)
    {
        IsNgcerIn = true;
        DataTree->SetBranchAddress("P.ngcer.goodAdcTdcDiffTime", &ngcerAdcTdcDiffTime);
        DataTree->SetBranchAddress("P.ngcer.goodAdcTdcMult", &ngcerAdcMult);
    }
    
    //aerogel
    for(Int_t iSide = 0; iSide < aeroSides; iSide++)
    {
        DataTree->SetBranchAddress(Form("P.aero.good%sAdcTdcDiffTime", aeroSideNames[iSide].Data()), &aeroAdcTdcDiffTime[iSide]);
        DataTree->SetBranchAddress(Form("P.aero.good%sAdcMult", aeroSideNames[iSide].Data()), &aeroAdcMult[iSide]);
    }
    
    //hms calorimeter
    for(Int_t iPlane = 0; iPlane < hcalPlanes; iPlane++)
    {
        for(Int_t iSide = 0; iSide < calSides; iSide++)
        {
            DataTree->SetBranchAddress(Form("H.cal.%s.good%sAdcTdcDiffTime", hcalPlaneNames[iPlane].Data(), calSideNames[iSide].Data()), &hcalAdcTdcDiffTime[iPlane][iSide]);
            DataTree->SetBranchAddress(Form("H.cal.%s.good%sAdcMult", hcalPlaneNames[iPlane].Data(), calSideNames[iSide].Data()), &hcalAdcMult[iPlane][iSide]);
        }
    }
    
    //shms calorimeter
    for(Int_t iSide = 0; iSide < calSides; iSide++)
    {
        DataTree->SetBranchAddress(Form("P.cal.pr.good%sAdcTdcDiffTime", calSideNames[iSide].Data()), &pcalprAdcMult[iSide]);
        DataTree->SetBranchAddress(Form("P.cal.pr.good%sAdcMult", calSideNames[iSide].Data()), &pcalprAdcMult[iSide]);
    }
    DataTree->SetBranchAddress("P.cal.fly.goodAdcTdcDiffTime", &pcalflyAdcMult);
    DataTree->SetBranchAddress("P.cal.fly.goodAdcMult", &pcalflyAdcMult);

    return;
}

//function for declaring all of the Histograms that are to be filed in the proceding script
void makeHistos ()
{
    pTrig1_Roc1_Hist = new TH1D("T.coin.pTRIG1_ROC1_tdcTimeRaw","T.coin.pTRIG1_ROC1_tdcTimeRaw",5000, 0, 10000);
    pTrig4_Roc1_Hist = new TH1D("T.coin.pTRIG4_ROC1_tdcTimeRaw","T.coin.pTRIG4_ROC1_tdcTimeRaw",5000, 0, 10000);
    pTrig1_Roc2_Hist = new TH1D("T.coin.pTRIG1_ROC2_tdcTimeRaw","T.coin.pTRIG1_ROC2_tdcTimeRaw",5000, 0, 10000);
    pTrig4_Roc2_Hist = new TH1D("T.coin.pTRIG4_ROC2_tdcTimeRaw","T.coin.pTRIG4_ROC2_tdcTimeRaw",5000, 0, 10000);
    pTrig3_Roc1_Hist = new TH1D("T.coin.pTRIG3_ROC1_tdcTimeRaw","T.coin.pTRIG3_ROC1_tdcTimeRaw",5000, 0, 10000);
    pTrig3_Roc2_Hist = new TH1D("T.coin.pTRIG3_ROC2_tdcTimeRaw","T.coin.pTRIG3_ROC2_tdcTimeRaw",5000, 0, 10000);
    //pT2_Hist = new TH1D("T.coin.pT2_tdcTimeRaw","T.coin.pT2_tdcTimeRaw",5000, 0, 10000);
    
    pTrig1_Roc1_Hist_cut = new TH1D("T.coin.pTRIG1_ROC1_tdcTimeRaw_cut","T.coin.pTRIG1_ROC1_tdcTimeRaw_cut",5000, 0, 10000);
    pTrig4_Roc1_Hist_cut = new TH1D("T.coin.pTRIG4_ROC1_tdcTimeRaw_cut","T.coin.pTRIG4_ROC1_tdcTimeRaw_cut",5000, 0, 10000);
    pTrig1_Roc2_Hist_cut = new TH1D("T.coin.pTRIG1_ROC2_tdcTimeRaw_cut","T.coin.pTRIG1_ROC2_tdcTimeRaw_cut",5000, 0, 10000);
    pTrig4_Roc2_Hist_cut = new TH1D("T.coin.pTRIG4_ROC2_tdcTimeRaw_cut","T.coin.pTRIG4_ROC2_tdcTimeRaw_cut",5000, 0, 10000);
    pTrig3_Roc1_Hist_cut = new TH1D("T.coin.pTRIG3_ROC1_tdcTimeRaw_cut","T.coin.pTRIG3_ROC1_tdcTimeRaw_cut",5000, 0, 10000);
    pTrig3_Roc2_Hist_cut = new TH1D("T.coin.pTRIG3_ROC2_tdcTimeRaw_cut","T.coin.pTRIG3_ROC2_tdcTimeRaw_cut",5000, 0, 10000);
    //pT2_Hist_cut = new TH1D("T.coin.pT2_tdcTimeRawcut","T.coin.pT2_tdcTimeRawcut",5000, 0, 10000);
    
    pTrig1_Roc1_Mult_Hist = new TH1D("T.coin.pTRIG1_ROC1_tdcMultiplicity","T.coin.pTRIG1_ROC1_tdcMultiplicity",10, -0.5, 9.5);
    pTrig4_Roc1_Mult_Hist = new TH1D("T.coin.pTRIG4_ROC1_tdcMultiplicity","T.coin.pTRIG4_ROC1_tdcMultiplicity",10, -0.5, 9.5);
    pTrig1_Roc2_Mult_Hist = new TH1D("T.coin.pTRIG1_ROC2_tdcMultiplicity","T.coin.pTRIG1_ROC2_tdcMultiplicity",10, -0.5, 9.5);
    pTrig4_Roc2_Mult_Hist = new TH1D("T.coin.pTRIG4_ROC2_tdcMultiplicity","T.coin.pTRIG4_ROC2_tdcMultiplicity",10, -0.5, 9.5);
    pTrig3_Roc1_Mult_Hist = new TH1D("T.coin.pTRIG3_ROC1_tdcMultiplicity","T.coin.pTRIG3_ROC1_tdcMultiplicity",10, -0.5, 9.5);
    pTrig3_Roc2_Mult_Hist = new TH1D("T.coin.pTRIG3_ROC2_tdcMultiplicity","T.coin.pTRIG3_ROC2_tdcMultiplicity",10, -0.5, 9.5);
    //pT2_Mult_Hist = new TH1D("T.coin.pT2_tdcMultiplicity","T.coin.pT2_tdcMultiplicity",10, -0.5, 9.5);
    
    hFADC_TREF_ROC1_Hist = new TH1D(Form("T.%s.hFADC_TREF_ROC1_adcPulseTimeRaw", DaqName.Data()), Form("T.%s.hFADC_TREF_ROC1_adcPulseTimeRaw", DaqName.Data()), 10000, 0, 10000);
    hTref1_Hist = new TH1D(Form("T.%s.hT1_tdcTimeRaw", DaqName.Data()), Form("T.%s.hT1_tdcTimeRaw", DaqName.Data()), 10000, 0, 10000);
    hTref2_Hist = new TH1D(Form("T.%s.hT2_tdcTimeRaw", DaqName.Data()), Form("T.%s.hT2_tdcTimeRaw", DaqName.Data()), 10000, 0, 10000);
    hDCREF1_Hist = new TH1D(Form("T.%s.hDCREF1_tdcTimeRaw", DaqName.Data()), Form("T.%s.hDCREF1_tdcTimeRaw", DaqName.Data()), 23000, 0, 23000);
    hDCREF2_Hist = new TH1D(Form("T.%s.hDCREF2_tdcTimeRaw", DaqName.Data()), Form("T.%s.hDCREF2_tdcTimeRaw", DaqName.Data()), 23000, 0, 23000);
    hDCREF3_Hist = new TH1D(Form("T.%s.hDCREF3_tdcTimeRaw", DaqName.Data()), Form("T.%s.hDCREF3_tdcTimeRaw", DaqName.Data()), 23000, 0, 23000);
    hDCREF4_Hist = new TH1D(Form("T.%s.hDCREF4_tdcTimeRaw", DaqName.Data()), Form("T.%s.hDCREF4_tdcTimeRaw", DaqName.Data()), 23000, 0, 23000);
    hDCREF5_Hist = new TH1D(Form("T.%s.hDCREF5_tdcTimeRaw", DaqName.Data()), Form("T.%s.hDCREF5_tdcTimeRaw", DaqName.Data()), 23000, 0, 23000);
    
    hFADC_TREF_ROC1_Mult_Hist = new TH1D(Form("T.%s.hFADC_TREF_ROC1_adcMultiplicity", DaqName.Data()), Form("T.%s.hFADC_TREF_ROC1_adcMultiplicity", DaqName.Data()), 10, 0, 10);
    hTref1_Mult_Hist = new TH1D(Form("T.%s.hT1_tdcMultiplicity", DaqName.Data()), Form("T.%s.hT1_tdcMultiplicity", DaqName.Data()), 10, 0, 10);
    hTref2_Mult_Hist = new TH1D(Form("T.%s.hT2_tdcMultiplicity", DaqName.Data()), Form("T.%s.hT2_tdcMultiplicity", DaqName.Data()), 10, 0, 10);
    hDCREF1_Mult_Hist = new TH1D(Form("T.%s.hDCREF1_tdcMultiplicity", DaqName.Data()), Form("T.%s.hDCREF1_tdcMultiplicity", DaqName.Data()), 10, 0, 10);
    hDCREF2_Mult_Hist = new TH1D(Form("T.%s.hDCREF2_tdcMultiplicity", DaqName.Data()), Form("T.%s.hDCREF2_tdcMultiplicity", DaqName.Data()), 10, 0, 10);
    hDCREF3_Mult_Hist = new TH1D(Form("T.%s.hDCREF3_tdcMultiplicity", DaqName.Data()), Form("T.%s.hDCREF3_tdcMultiplicity", DaqName.Data()), 10, 0, 10);
    hDCREF4_Mult_Hist = new TH1D(Form("T.%s.hDCREF4_tdcMultiplicity", DaqName.Data()), Form("T.%s.hDCREF4_tdcMultiplicity", DaqName.Data()), 10, 0, 10);
    hDCREF5_Mult_Hist = new TH1D(Form("T.%s.hDCREF5_tdcMultiplicity", DaqName.Data()), Form("T.%s.hDCREF5_tdcMultiplicity", DaqName.Data()), 10, 0, 10);

    pFADC_TREF_ROC2_Hist = new TH1D(Form("T.%s.pFADC_TREF_ROC2_adcPulseTimeRaw", DaqName.Data()), Form("T.%s.pFADC_TREF_ROC2_adcPulseTimeRaw", DaqName.Data()), 10000, 0, 10000);
    pTref1_Hist = new TH1D(Form("T.%s.pT1_tdcTimeRaw", DaqName.Data()), Form("T.%s.pT1_tdcTimeRaw", DaqName.Data()), 10000, 0, 10000);
    pTref2_Hist = new TH1D(Form("T.%s.pT2_tdcTimeRaw", DaqName.Data()), Form("T.%s.pT2_tdcTimeRaw", DaqName.Data()), 10000, 0, 10000);
    pDCREF1_Hist = new TH1D(Form("T.%s.pDCREF1_tdcTimeRaw", DaqName.Data()), Form("T.%s.pDCREF1_tdcTimeRaw", DaqName.Data()), 23000, 0, 23000);
    pDCREF2_Hist = new TH1D(Form("T.%s.pDCREF2_tdcTimeRaw", DaqName.Data()), Form("T.%s.pDCREF2_tdcTimeRaw", DaqName.Data()), 23000, 0, 23000);
    pDCREF3_Hist = new TH1D(Form("T.%s.pDCREF3_tdcTimeRaw", DaqName.Data()), Form("T.%s.pDCREF3_tdcTimeRaw", DaqName.Data()), 23000, 0, 23000);
    pDCREF4_Hist = new TH1D(Form("T.%s.pDCREF4_tdcTimeRaw", DaqName.Data()), Form("T.%s.pDCREF4_tdcTimeRaw", DaqName.Data()), 23000, 0, 23000);
    pDCREF5_Hist = new TH1D(Form("T.%s.pDCREF5_tdcTimeRaw", DaqName.Data()), Form("T.%s.pDCREF5_tdcTimeRaw", DaqName.Data()), 23000, 0, 23000);
    pDCREF6_Hist = new TH1D(Form("T.%s.pDCREF6_tdcTimeRaw", DaqName.Data()), Form("T.%s.pDCREF6_tdcTimeRaw", DaqName.Data()), 23000, 0, 23000);
    pDCREF7_Hist = new TH1D(Form("T.%s.pDCREF7_tdcTimeRaw", DaqName.Data()), Form("T.%s.pDCREF7_tdcTimeRaw", DaqName.Data()), 23000, 0, 23000);
    pDCREF8_Hist = new TH1D(Form("T.%s.pDCREF8_tdcTimeRaw", DaqName.Data()), Form("T.%s.pDCREF8_tdcTimeRaw", DaqName.Data()), 23000, 0, 23000);
    pDCREF9_Hist = new TH1D(Form("T.%s.pDCREF9_tdcTimeRaw", DaqName.Data()), Form("T.%s.pDCREF9_tdcTimeRaw", DaqName.Data()), 23000, 0, 23000);
    pDCREF10_Hist = new TH1D(Form("T.%s.pDCREF10_tdcTimeRaw", DaqName.Data()), Form("T.%s.pDCREF10_tdcTimeRaw", DaqName.Data()), 23000, 0, 23000);
    
    pFADC_TREF_ROC2_Mult_Hist = new TH1D(Form("T.%s.pFADC_TREF_ROC2_adcMultiplicity", DaqName.Data()), Form("T.%s.pFADC_TREF_ROC2_adcMultiplicity", DaqName.Data()), 10, 0, 10);
    pTref1_Mult_Hist = new TH1D(Form("T.%s.pT1_tdcMultiplicity", DaqName.Data()), Form("T.%s.pT1_tdcMultiplicity", DaqName.Data()), 10, 0, 10);
    pTref2_Mult_Hist = new TH1D(Form("T.%s.pT2_tdcMultiplicity", DaqName.Data()), Form("T.%s.pT2_tdcMultiplicity", DaqName.Data()), 10, 0, 10);
    pDCREF1_Mult_Hist = new TH1D(Form("T.%s.pDCREF1_tdcMultiplicity", DaqName.Data()), Form("T.%s.pDCREF1_tdcMultiplicity", DaqName.Data()), 10, 0, 10);
    pDCREF2_Mult_Hist = new TH1D(Form("T.%s.pDCREF2_tdcMultiplicity", DaqName.Data()), Form("T.%s.pDCREF2_tdcMultiplicity", DaqName.Data()), 10, 0, 10);
    pDCREF3_Mult_Hist = new TH1D(Form("T.%s.pDCREF3_tdcMultiplicity", DaqName.Data()), Form("T.%s.pDCREF3_tdcMultiplicity", DaqName.Data()), 10, 0, 10);
    pDCREF4_Mult_Hist = new TH1D(Form("T.%s.pDCREF4_tdcMultiplicity", DaqName.Data()), Form("T.%s.pDCREF4_tdcMultiplicity", DaqName.Data()), 10, 0, 10);
    pDCREF5_Mult_Hist = new TH1D(Form("T.%s.pDCREF5_tdcMultiplicity", DaqName.Data()), Form("T.%s.pDCREF5_tdcMultiplicity", DaqName.Data()), 10, 0, 10);
    pDCREF6_Mult_Hist = new TH1D(Form("T.%s.pDCREF6_tdcMultiplicity", DaqName.Data()), Form("T.%s.pDCREF6_tdcMultiplicity", DaqName.Data()), 10, 0, 10);
    pDCREF7_Mult_Hist = new TH1D(Form("T.%s.pDCREF7_tdcMultiplicity", DaqName.Data()), Form("T.%s.pDCREF7_tdcMultiplicity", DaqName.Data()), 10, 0, 10);
    pDCREF8_Mult_Hist = new TH1D(Form("T.%s.pDCREF8_tdcMultiplicity", DaqName.Data()), Form("T.%s.pDCREF8_tdcMultiplicity", DaqName.Data()), 10, 0, 10);
    pDCREF9_Mult_Hist = new TH1D(Form("T.%s.pDCREF9_tdcMultiplicity", DaqName.Data()), Form("T.%s.pDCREF9_tdcMultiplicity", DaqName.Data()), 10, 0, 10);
    pDCREF10_Mult_Hist = new TH1D(Form("T.%s.pDCREF10_tdcMultiplicity", DaqName.Data()), Form("T.%s.pDCREF10_tdcMultiplicity", DaqName.Data()), 10, 0, 10);

    //dc variables
    for(Int_t i = 0; i < dcPlanes; i++)
    {
        hdcrawtdc_Hist[i] = new TH1D(Form("H.dc.%s.rawtdc", dcPlaneNames[i].Data()), Form("H.dc.%s.rawtdc", dcPlaneNames[i].Data()), 5000, -15000, -10000);
        pdcrawtdc_Hist[i] = new TH1D(Form("P.dc.%s.rawtdc", dcPlaneNames[i].Data()), Form("P.dc.%s.rawtdc", dcPlaneNames[i].Data()), 5000, -15000, -10000);
        hdcnhit_Hist[i] = new TH1D(Form("H.dc.%s.nhit", dcPlaneNames[i].Data()), Form("H.dc.%s.nhit", dcPlaneNames[i].Data()), 50, 0, 50);
        pdcnhit_Hist[i] = new TH1D(Form("P.dc.%s.nhit", dcPlaneNames[i].Data()), Form("P.dc.%s.nhit", dcPlaneNames[i].Data()), 50, 0, 50);
    }

    // hodoscope variables
    for(Int_t iPlane = 0; iPlane < HodPlanes; iPlane++)
    {
        for(Int_t iSide = 0; iSide < HodSides; iSide++)
        {
            for(Int_t iPmt = 0; iPmt < hHodbars[iPlane]; iPmt++)
            {
                hHodAdcTdcDiffTime_Hist[iPlane][iSide][iPmt] = new TH1D(Form("H.hod.%s.%sAdcTdcDiffTimeRaw_pmt%d", HodPlaneNames[iPlane].Data(), HodSideNames[iSide].Data(), iPmt+1), Form("H.hod.%s.%sAdcTdcDiffTimeRaw_pmt%d", HodPlaneNames[iPlane].Data(), HodSideNames[iSide].Data(), iPmt+1), 1500, -1000, 500);
                hHodAdcMult_Hist[iPlane][iSide][iPmt] = new TH1D(Form("H.hod.%s.good%sAdcMult_pmt%d", HodPlaneNames[iPlane].Data(), HodSideNames[iSide].Data(), iPmt+1), Form("H.hod.%s.good%sAdcMult_pmt%d", HodPlaneNames[iPlane].Data(), HodSideNames[iSide].Data(), iPmt+1), 10, 0, 10);
        }
            for(Int_t iPmt = 0; iPmt < pHodbars[iPlane]; iPmt++)
            {
                pHodAdcTdcDiffTime_Hist[iPlane][iSide][iPmt] = new TH1D(Form("P.hod.%s.%sAdcTdcDiffTimeRaw_pmt%d", HodPlaneNames[iPlane].Data(), HodSideNames[iSide].Data(), iPmt+1), Form("P.hod.%s.%sAdcTdcDiffTimeRaw_pmt%d", HodPlaneNames[iPlane].Data(), HodSideNames[iSide].Data(), iPmt+1),1000, -500, 500);
                pHodAdcMult_Hist[iPlane][iSide][iPmt] = new TH1D(Form("P.hod.%s.%sAdcMult_pmt%d", HodPlaneNames[iPlane].Data(), HodSideNames[iSide].Data(), iPmt+1), Form("P.hod.%s.good%sAdcMult_pmt%d", HodPlaneNames[iPlane].Data(), HodSideNames[iSide].Data(), iPmt+1), 10, 0, 10);
        }
        }
    }
 
    for(Int_t iPlane = 0; iPlane < HodPlanes; iPlane++)
    {
        for(Int_t iSide = 0; iSide < HodSides1; iSide++)
        {
            for(Int_t iPmt = 0; iPmt < hHodbars[iPlane]; iPmt++)
        {
                hHodAdcPulseTimeRaw_Hist[iPlane][iSide][iPmt] = new TH1D(Form("H.hod.%s.%sAdcPulseTimeRaw_pmt%d", HodPlaneNames[iPlane].Data(), HodSideNames[iSide].Data(), iPmt+1), Form("H.hod.%s.%sAdcPulseTimeRaw_pmt%d", HodPlaneNames[iPlane].Data(), HodSideNames[iSide].Data(), iPmt+1), 12000, 0, 12000);
                hHodTdcTimeRaw_Hist[iPlane][iSide][iPmt] = new TH1D(Form("H.hod.%s.%sTdcTimeRaw_pmt%d", HodPlaneNames[iPlane].Data(), HodSideNames[iSide].Data(), iPmt+1), Form("H.hod.%s.%sTdcTimeRaw_pmt%d", HodPlaneNames[iPlane].Data(), HodSideNames[iSide].Data(), iPmt+1), 12000, 0, 12000);
            }
        for(Int_t iPmt = 0; iPmt < pHodbars[iPlane]; iPmt++)
        {
                pHodAdcPulseTimeRaw_Hist[iPlane][iSide][iPmt] = new TH1D(Form("P.hod.%s.%sAdcPulseTimeRaw_pmt%d", HodPlaneNames[iPlane].Data(), HodSideNames[iSide].Data(), iPmt+1), Form("P.hod.%s.%sAdcPulseTimeRaw_pmt%d", HodPlaneNames[iPlane].Data(), HodSideNames[iSide].Data(), iPmt+1), 12000, 0, 12000);
                pHodTdcTimeRaw_Hist[iPlane][iSide][iPmt] = new TH1D(Form("P.hod.%s.%sTdcTimeRaw_pmt%d", HodPlaneNames[iPlane].Data(), HodSideNames[iSide].Data(), iPmt+1), Form("P.hod.%s.%sTdcTimeRaw_pmt%d", HodPlaneNames[iPlane].Data(), HodSideNames[iSide].Data(), iPmt+1), 12000, 0, 12000);
            }
        }
    }    

    //Gas cherenkovs
    //hms
    cerAdcTdcDiffTime_Hist_Sum = new TH1D("H.cer.goodAdcTdcDiffTime_Sum", "H.cer.goodAdcTdcDiffTime_Sum", 800, -400, 400);
    for(Int_t iPmt = 0; iPmt < hcerNpmts; iPmt++)
    {
        cerAdcTdcDiffTime_Hist[iPmt] = new TH1D(Form("H.cer.goodAdcTdcDiffTime_Pmt%d", iPmt+1), Form("H.cer.goodAdcTdcDiffTime_Pmt%d", iPmt+1), 800, -400, 400);
        cerAdcMult_Hist[iPmt] = new TH1D(Form("H.cer.goodAdcMult_Pmt%d", iPmt+1), Form("H.cer.goodAdcMult_Pmt%d", iPmt+1), 10, 0, 10);
    }
    
    //shms
    hgcerAdcTdcDiffTime_Hist_Sum = new TH1D("P.hgcer.goodAdcTdcDiffTime_Sum", "P.hgcer.goodAdcTdcDiffTime_Sum", 200, -100, 100);
    ngcerAdcTdcDiffTime_Hist_Sum = new TH1D("P.ngcer.goodAdcTdcDiffTime_Sum", "P.ngcer.goodAdcTdcDiffTime_Sum", 400, -200, 200);
    for(Int_t iPmt = 0; iPmt < pcerNpmts; iPmt++)
    {
        hgcerAdcTdcDiffTime_Hist[iPmt] = new TH1D(Form("P.hgcer.goodAdcTdcDiffTime_Pmt%d", iPmt+1), Form("P.hgcer.goodAdcTdcDiffTime_Pmt%d", iPmt+1), 200, -100, 100);
        ngcerAdcTdcDiffTime_Hist[iPmt] = new TH1D(Form("P.ngcer.goodAdcTdcDiffTime_Pmt%d", iPmt+1), Form("P.ngcer.goodAdcTdcDiffTime_Pmt%d", iPmt+1), 400, -200, 200);
        hgcerAdcMult_Hist[iPmt] = new TH1D(Form("P.hgcer.goodAdcMult_Pmt%d", iPmt+1), Form("P.hgcer.goodAdcMult_Pmt%d", iPmt+1), 10, 0, 10);
        ngcerAdcMult_Hist[iPmt] = new TH1D(Form("P.ngcer.goodAdcMult_Pmt%d", iPmt+1), Form("P.ngcer.goodAdcMult_Pmt%d", iPmt+1), 10, 0, 10);
    }
    
    //aerogel 
    for(Int_t iSide = 0; iSide < aeroSides; iSide++)
    {
        aeroAdcTdcDiffTime_Hist_Sum[iSide] = new TH1D(Form("P.aero.good%sAdcTdcDiffTime_Sum", aeroSideNames[iSide].Data()), Form("P.aero.good%sAdcTdcDiffTime_Sum", aeroSideNames[iSide].Data()), 750, -250, 500);
        for(Int_t iPmt = 0; iPmt < aeroNumPmts; iPmt++)
        {
            aeroAdcTdcDiffTime_Hist[iSide][iPmt] = new TH1D(Form("P.aero.good%sAdcTdcDiffTime_Pmt%d", aeroSideNames[iSide].Data(), iPmt+1), Form("P.aero.good%sAdcTdcDiffTime_Pmt%d", aeroSideNames[iSide].Data(), iPmt+1), 750, -250, 500);
            aeroAdcMult_Hist[iSide][iPmt] = new TH1D(Form("P.aero.good%sAdcMult_Pmt%d", aeroSideNames[iSide].Data(), iPmt+1), Form("P.aero.good%sAdcMult_Pmt%d", aeroSideNames[iSide].Data(), iPmt+1), 10, 0, 10);
        }
    }

    //Calorimeters
    //hms
    for(Int_t iPlane = 0; iPlane < hcalPlanes; iPlane++)
    {
        for(Int_t iSide = 0; iSide < calSides; iSide++)
        {
            hcalAdcTdcDiffTime_Hist_Sum[iPlane][iSide] = new TH1D(Form("H.cal.%s.good%sAdcTdcDiffTime_Sum", hcalPlaneNames[iPlane].Data(), calSideNames[iSide].Data()),Form("H.cal.%s.good%sAdcTdcDiffTime_Sum", hcalPlaneNames[iPlane].Data(), calSideNames[iSide].Data()), 400, -200, 200);
            for(Int_t iPmt = 0; iPmt < hcalNumPmts[iPlane]; iPmt++)
            {
                hcalAdcTdcDiffTime_Hist[iPlane][iSide][iPmt] = new TH1D(Form("H.cal.%s.good%sAdcTdcDiffTime_Pmt%d", hcalPlaneNames[iPlane].Data(), calSideNames[iSide].Data(), iPmt+1),Form("H.cal.%s.good%sAdcTdcDiffTime_Pmt%d", hcalPlaneNames[iPlane].Data(), calSideNames[iSide].Data(), iPmt+1), 400, -200, 200);
                hcalAdcMult_Hist[iPlane][iSide][iPmt] = new TH1D(Form("H.cal.%s.good%sAdcMult_Pmt%d", hcalPlaneNames[iPlane].Data(), calSideNames[iSide].Data(), iPmt+1),Form("H.cal.%s.good%sAdcMult_Pmt%d", hcalPlaneNames[iPlane].Data(), calSideNames[iSide].Data(), iPmt+1), 10, 0, 10);
            }
        }
    }
    
    //shms calorimeter
    for(Int_t iSide = 0; iSide < calSides; iSide++)
    {
        pcalprAdcTdcDiffTime_Hist_Sum[iSide] = new TH1D(Form("P.cal.pr.good%sAdcTdcDiffTime_Sum", calSideNames[iSide].Data()), Form("P.cal.pr.good%sAdcTdcDiffTime_Sum", calSideNames[iSide].Data()), 400, -200, 200);
        for(Int_t iPmt = 0; iPmt < pcalPrNumPmts; iPmt++)
        {
            pcalprAdcTdcDiffTime_Hist[iSide][iPmt] = new TH1D(Form("P.cal.pr.good%sAdcTdcDiffTime_pmt%d", calSideNames[iSide].Data(), iPmt+1), Form("P.cal.pr.good%sAdcTdcDiffTime_pmt%d", calSideNames[iSide].Data(), iPmt+1), 400, -200, 200);
            pcalprAdcMult_Hist[iSide][iPmt] = new TH1D(Form("P.cal.pr.good%sAdcMult_pmt%d", calSideNames[iSide].Data(), iPmt+1), Form("P.cal.pr.good%sAdcMult_pmt%d", calSideNames[iSide].Data(), iPmt+1), 100, 0, 100);
        }
    }    
    
    pcalflyAdcTdcDiffTime_Hist_Sum = new TH1D("P.cal.fly.goodAdcTdcDiffTime_Sum", "P.cal.fly.goodAdcTdcDiffTime_Sum", 400, -200, 200);
    for(Int_t iPmt = 0; iPmt < pcalFlyNumPmts; iPmt++)
    {
        pcalflyAdcTdcDiffTime_Hist[iPmt] = new TH1D(Form("P.cal.fly.goodAdcTdcDiffTime_pmt%d", iPmt+1), Form("P.cal.fly.goodAdcTdcDiffTime_pmt%d", iPmt+1), 400, -200, 200);
        pcalflyAdcMult_Hist[iPmt] = new TH1D(Form("P.cal.fly.goodAdcMult_pmt%d", iPmt+1),Form("P.cal.fly.goodAdcMult_pmt%d", iPmt+1), 100, 0, 100);
    }
    
    return;
}

//function for filling the histograms, this is where any cuts will be implimented
void fillHistos(TTree *DataTree)
{
    int hHodDiffCounter = 0;
    int pHodDiffCounter = 0;
    
    Int_t MaxEvents = DataTree->GetEntries();
    cout << "Begining to fill histograms, " << MaxEvents << " events will be processed!\n";
    for(Int_t iEntry = 0; iEntry < MaxEvents; iEntry++)
    {
        DataTree->GetEntry(iEntry);
        
        if( iEntry % 10000 == 0 ) cout << iEntry << "\n"; //status report
        
        if(SaveOption == 0 || SaveOption == 1)
        {
        	pTrig1_Roc1_Hist->Fill(pTrig1_Roc1);
        	pTrig4_Roc1_Hist->Fill(pTrig4_Roc1);
        	pTrig1_Roc2_Hist->Fill(pTrig1_Roc2);
        	pTrig4_Roc2_Hist->Fill(pTrig4_Roc2);
        	pTrig3_Roc1_Hist->Fill(pTrig3_Roc1);
        	pTrig3_Roc2_Hist->Fill(pTrig3_Roc2);
        	//pT2_Hist->Fill(pT2);
        	
        	pTrig1_Roc1_Mult_Hist->Fill(pTrig1_Roc1_Mult);
        	pTrig4_Roc1_Mult_Hist->Fill(pTrig4_Roc1_Mult);
        	pTrig1_Roc2_Mult_Hist->Fill(pTrig1_Roc2_Mult);
        	pTrig4_Roc2_Mult_Hist->Fill(pTrig4_Roc2_Mult);
        	pTrig3_Roc1_Mult_Hist->Fill(pTrig3_Roc1_Mult);
        	pTrig3_Roc2_Mult_Hist->Fill(pTrig3_Roc2_Mult);
        	//pT2_Mult_Hist->Fill(pT2_Mult);
        	
        	if(pTrig1_Roc1_Mult == 1) pTrig1_Roc1_Hist_cut->Fill(pTrig1_Roc1);
        	if(pTrig4_Roc1_Mult == 1) pTrig4_Roc1_Hist_cut->Fill(pTrig4_Roc1);
        	if(pTrig1_Roc2_Mult == 1) pTrig1_Roc2_Hist_cut->Fill(pTrig1_Roc2);
        	if(pTrig4_Roc2_Mult == 1) pTrig4_Roc2_Hist_cut->Fill(pTrig4_Roc2);
        	if(pTrig3_Roc1_Mult == 1) pTrig3_Roc1_Hist_cut->Fill(pTrig3_Roc1);
        	if(pTrig3_Roc2_Mult == 1) pTrig3_Roc2_Hist_cut->Fill(pTrig3_Roc2);
        	//if(pT2_Mult == 1) pT2_Hist_cut->Fill(pT2);
        	
        	hFADC_TREF_ROC1_Mult_Hist->Fill(hFADC_TREF_ROC1_Mult);
       		hTref1_Mult_Hist->Fill(hTref1_Mult);
        	hTref2_Mult_Hist->Fill(hTref2_Mult);
        	hDCREF1_Mult_Hist->Fill(hDCREF1_Mult);
        	hDCREF2_Mult_Hist->Fill(hDCREF2_Mult); 
        	hDCREF3_Mult_Hist->Fill(hDCREF3_Mult); 
        	hDCREF4_Mult_Hist->Fill(hDCREF4_Mult);  
        	hDCREF5_Mult_Hist->Fill(hDCREF5_Mult); 

        	//apply multiplicity cuts
        	if (hFADC_TREF_ROC1_Mult == 1)  hFADC_TREF_ROC1_Hist->Fill(hFADC_TREF_ROC1); 
        	if (hTref1_Mult == 1)           hTref1_Hist->Fill(hTref1); 
        	if (hTref2_Mult == 1)           hTref2_Hist->Fill(hTref2);
        	if (hDCREF1_Mult == 1)          hDCREF1_Hist->Fill(hDCREF1); 
        	if (hDCREF2_Mult == 1)          hDCREF2_Hist->Fill(hDCREF2); 
        	if (hDCREF3_Mult == 1)          hDCREF3_Hist->Fill(hDCREF3);  
        	if (hDCREF4_Mult == 1)          hDCREF4_Hist->Fill(hDCREF4); 
        	if (hDCREF5_Mult == 1)          hDCREF5_Hist->Fill(hDCREF5);
        
        
        	pFADC_TREF_ROC2_Mult_Hist->Fill(pFADC_TREF_ROC2_Mult); 
        	pTref1_Mult_Hist->Fill(pTref1_Mult); 
        	pTref2_Mult_Hist->Fill(pTref2_Mult);   
        	pDCREF1_Mult_Hist->Fill(pDCREF1_Mult);   
        	pDCREF2_Mult_Hist->Fill(pDCREF2_Mult); 
        	pDCREF3_Mult_Hist->Fill(pDCREF3_Mult);   
        	pDCREF4_Mult_Hist->Fill(pDCREF4_Mult);   
        	pDCREF5_Mult_Hist->Fill(pDCREF5_Mult);   
        	pDCREF6_Mult_Hist->Fill(pDCREF6_Mult);   
        	pDCREF7_Mult_Hist->Fill(pDCREF7_Mult);   
        	pDCREF8_Mult_Hist->Fill(pDCREF8_Mult);   
        	pDCREF9_Mult_Hist->Fill(pDCREF9_Mult); 
        	pDCREF10_Mult_Hist->Fill(pDCREF10_Mult);   
     
        	if (pFADC_TREF_ROC2_Mult > 0)  pFADC_TREF_ROC2_Hist->Fill(pFADC_TREF_ROC2);  
        	if (pTref1_Mult == 1)           pTref1_Hist->Fill(pTref1);
        	if (pTref2_Mult == 1)           pTref2_Hist->Fill(pTref2);  
        	if (pDCREF1_Mult == 1)          pDCREF1_Hist->Fill(pDCREF1); 
        	if (pDCREF2_Mult == 1)          pDCREF2_Hist->Fill(pDCREF2);
        	if (pDCREF3_Mult == 1)          pDCREF3_Hist->Fill(pDCREF3);  
        	if (pDCREF4_Mult == 1)          pDCREF4_Hist->Fill(pDCREF4); 
        	if (pDCREF5_Mult == 1)          pDCREF5_Hist->Fill(pDCREF5); 
        	if (pDCREF6_Mult == 1)          pDCREF6_Hist->Fill(pDCREF6);  
        	if (pDCREF7_Mult == 1)          pDCREF7_Hist->Fill(pDCREF7); 
        	if (pDCREF8_Mult == 1)          pDCREF8_Hist->Fill(pDCREF8);  
        	if (pDCREF9_Mult == 1)          pDCREF9_Hist->Fill(pDCREF9);  
        	if (pDCREF10_Mult == 1)         pDCREF10_Hist->Fill(pDCREF10);    
		} // end Ref Time Fill
		
		if(SaveOption == 0 || SaveOption == 2){
        //dc variables 
        for(Int_t i = 0; i < dcPlanes; i++)
        { 
            hdcnhit_Hist[i]->Fill(hdcnhit[i]);
            pdcnhit_Hist[i]->Fill(pdcnhit[i]);
            if (hdcnhit[i] > 0)    hdcrawtdc_Hist[i]->Fill(hdcrawtdc[i]);
            if (pdcnhit[i] > 0)    pdcrawtdc_Hist[i]->Fill(pdcrawtdc[i]);
            
        } 
        
        // hodoscope variables 
        for(Int_t iPlane = 0; iPlane < HodPlanes; iPlane++)
        { 
            for(Int_t iSide = 0; iSide < HodSides; iSide++)
            { 
                for(Int_t iPmt = 0; iPmt < hHodbars[iPlane]; iPmt++)
                { 
                    hHodAdcMult_Hist[iPlane][iSide][iPmt]->Fill(hHodAdcMult[iPlane][iSide][iPmt]);
                    if ( hHodAdcMult[iPlane][iSide][iPmt] > 0) hHodAdcTdcDiffTime_Hist[iPlane][iSide][iPmt]->Fill(hHodAdcTdcDiffTime[iPlane][iSide][iPmt]);  
                   // if ( hHodAdcTdcDiffTime[iPlane][iSide][iPmt] - (hHodTdcTimeRaw[iPlane][iSide][iPmt] - hHodAdcPulseTimeRaw[iPlane][iSide][iPmt]) > 1 && hHodAdcTdcDiffTime[iPlane][iSide][iPmt] != 0) hHodDiffCounter++;
                } 
                for(Int_t iPmt = 0; iPmt < pHodbars[iPlane]; iPmt++)
                { 
                    pHodAdcMult_Hist[iPlane][iSide][iPmt]->Fill(pHodAdcMult[iPlane][iSide][iPmt]);
                    if ( pHodAdcMult[iPlane][iSide][iPmt] > 0) pHodAdcTdcDiffTime_Hist[iPlane][iSide][iPmt]->Fill(pHodAdcTdcDiffTime[iPlane][iSide][iPmt]); 
                    //if ( pHodAdcTdcDiffTime[iPlane][iSide][iPmt] - (pHodTdcTimeRaw[iPlane][iSide][iPmt] - pHodAdcPulseTimeRaw[iPlane][iSide][iPmt]) > 1 && pHodAdcTdcDiffTime[iPlane][iSide][iPmt] != 0) pHodDiffCounter++;
                } 
            } 
        }

        for(Int_t iPlane = 0; iPlane < HodPlanes; iPlane++)
        {
            for(Int_t iSide = 0; iSide < HodSides1; iSide++)
            {
                for(Int_t iPmt = 0; iPmt < hHodbars[iPlane]; iPmt++)
                {
                    hHodAdcPulseTimeRaw_Hist[iPlane][iSide][iPmt]->Fill(hHodAdcPulseTimeRaw[iPlane][iSide][iPmt]);
                    hHodTdcTimeRaw_Hist[iPlane][iSide][iPmt]->Fill(hHodTdcTimeRaw[iPlane][iSide][iPmt]);
                }
                for(Int_t iPmt = 0; iPmt < pHodbars[iPlane]; iPmt++)
                {            
                    pHodAdcPulseTimeRaw_Hist[iPlane][iSide][iPmt]->Fill(pHodAdcPulseTimeRaw[iPlane][iSide][iPmt]);
                    pHodTdcTimeRaw_Hist[iPlane][iSide][iPmt]->Fill(pHodTdcTimeRaw[iPlane][iSide][iPmt]);
                }
            }
         }


        //Gas cherenkovs 
        //hms 
        for(Int_t iPmt = 0; iPmt < hcerNpmts; iPmt++)
        { 
            cerAdcMult_Hist[iPmt]->Fill(cerAdcMult[iPmt]);
            if(cerAdcMult[iPmt] > -1 ) {
                cerAdcTdcDiffTime_Hist_Sum->Fill(cerAdcTdcDiffTime[iPmt]);
                cerAdcTdcDiffTime_Hist[iPmt]->Fill(cerAdcTdcDiffTime[iPmt]);
            }
        } 
         
        //shms 
        for(Int_t iPmt = 0; iPmt < pcerNpmts; iPmt++)
        { 
            hgcerAdcMult_Hist[iPmt]->Fill(hgcerAdcMult[iPmt]);
            ngcerAdcMult_Hist[iPmt]->Fill(ngcerAdcMult[iPmt]);
            if (hgcerAdcMult[iPmt] > 0) { 
                hgcerAdcTdcDiffTime_Hist[iPmt]->Fill(hgcerAdcTdcDiffTime[iPmt]);
                hgcerAdcTdcDiffTime_Hist_Sum->Fill(hgcerAdcTdcDiffTime[iPmt]);
            }
            if (ngcerAdcMult[iPmt] > -1) {
                ngcerAdcTdcDiffTime_Hist[iPmt]->Fill(ngcerAdcTdcDiffTime[iPmt]);
                ngcerAdcTdcDiffTime_Hist_Sum->Fill(ngcerAdcTdcDiffTime[iPmt]);
            }
        } 
         
        //aerogel  
        for(Int_t iSide = 0; iSide < aeroSides; iSide++)
        { 
            for(Int_t iPmt = 0; iPmt < aeroNumPmts; iPmt++)
            { 
                aeroAdcMult_Hist[iSide][iPmt]->Fill(aeroAdcMult[iSide][iPmt]);
                if (aeroAdcMult[iSide][iPmt] > 0) { 
                    aeroAdcTdcDiffTime_Hist[iSide][iPmt]->Fill(aeroAdcTdcDiffTime[iSide][iPmt]);
                    aeroAdcTdcDiffTime_Hist_Sum[iSide]->Fill(aeroAdcTdcDiffTime[iSide][iPmt]);
                }
            } 
        } 
     
        //Calorimeters 
        //hms 
        for(Int_t iPlane = 0; iPlane < hcalPlanes; iPlane++)
        { 
            for(Int_t iSide = 0; iSide < calSides; iSide++)
            { 
                for(Int_t iPmt = 0; iPmt < hcalNumPmts[iPlane]; iPmt++)
                { 
                    hcalAdcMult_Hist[iPlane][iSide][iPmt]->Fill(hcalAdcMult[iPlane][iSide][iPmt]);
                    if (hcalAdcMult[iPlane][iSide][iPmt] > 0) { 
                        hcalAdcTdcDiffTime_Hist[iPlane][iSide][iPmt]->Fill(hcalAdcTdcDiffTime[iPlane][iSide][iPmt]);
                        hcalAdcTdcDiffTime_Hist_Sum[iPlane][iSide]->Fill(hcalAdcTdcDiffTime[iPlane][iSide][iPmt]);
                    }
                } 
            } 
        } 
         
        //shms calorimeter 
        for(Int_t iSide = 0; iSide < calSides; iSide++)
        { 
            for(Int_t iPmt = 0; iPmt < pcalPrNumPmts; iPmt++)
            { 
                if (pcalprAdcMult[iSide][iPmt] > -1) {
                    pcalprAdcTdcDiffTime_Hist[iSide][iPmt]->Fill(pcalprAdcTdcDiffTime[iSide][iPmt]);  
                    pcalprAdcTdcDiffTime_Hist_Sum[iSide]->Fill(pcalprAdcTdcDiffTime[iSide][iPmt]);  
                }
                pcalprAdcMult_Hist[iSide][iPmt]->Fill(pcalprAdcMult[iSide][iPmt]);
            } 
        }     
         
        for(Int_t iPmt = 0; iPmt < pcalFlyNumPmts; iPmt++)
        { 
            if (pcalflyAdcMult[iPmt] > -1) {
                pcalflyAdcTdcDiffTime_Hist[iPmt]->Fill(pcalflyAdcTdcDiffTime[iPmt]);
                pcalflyAdcTdcDiffTime_Hist_Sum->Fill(pcalflyAdcTdcDiffTime[iPmt]);
            }
            pcalflyAdcMult_Hist[iPmt]->Fill(pcalflyAdcMult[iPmt]);
        }
    }// end Detector Fill 
    }
    cout << "\n\n\n !!!!!!!!!!!!!!!!! \nhHod test: " << hHodDiffCounter << "\npHod Test: " << pHodDiffCounter << "\n\n\n\n !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
    return; 
}

void SaveToPDF(Int_t RunNumber)
{
    //write histogrames to pdf
    TCanvas* canvas = new TCanvas("PDFOutput", "PDFOutput", 600, 600);
    gPad->SetLogy();
    TLine *LeftLine, *RightLine;
    LeftLine = new TLine();
    LeftLine->SetLineWidth(4);
    LeftLine->SetLineStyle(9);

    RightLine = new TLine();
    RightLine->SetLineWidth(4);
    RightLine->SetLineStyle(9);
    
    if(SaveOption == 0 || SaveOption == 1){
    pTrig1_Roc1_Hist->Draw();
    pTrig1_Roc1_Hist_cut->SetLineColor(2);
    pTrig1_Roc1_Hist_cut->Draw("same");
    canvas->Print(Form("output/REF_TimePlots_%d.pdf(",RunNumber),  pTrig1_Roc1_Hist->GetName());
    pTrig4_Roc1_Hist->Draw();
    pTrig4_Roc1_Hist_cut->SetLineColor(2);
    pTrig4_Roc1_Hist_cut->Draw("same");
    canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  pTrig4_Roc1_Hist->GetName());
    pTrig1_Roc2_Hist->Draw();
    pTrig1_Roc2_Hist_cut->SetLineColor(2);
    pTrig1_Roc2_Hist_cut->Draw("same");
    canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  pTrig1_Roc2_Hist->GetName());
    pTrig4_Roc2_Hist->Draw();
    pTrig4_Roc2_Hist_cut->SetLineColor(2);
    pTrig4_Roc2_Hist_cut->Draw("same");
    canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  pTrig4_Roc2_Hist->GetName());
    pTrig3_Roc1_Hist->Draw();
    pTrig3_Roc1_Hist_cut->SetLineColor(2);
    pTrig3_Roc1_Hist_cut->Draw("same");
    canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  pTrig3_Roc1_Hist->GetName());
    pTrig3_Roc2_Hist->Draw();
    pTrig3_Roc2_Hist_cut->SetLineColor(2);
    pTrig3_Roc2_Hist_cut->Draw("same");
    canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  pTrig3_Roc2_Hist->GetName());
    //pT2_Hist->GetYaxis()->SetRangeUser(10,pT2_Hist_cut->GetEntries());
    //pT2_Hist->Draw();
    //pT2_Hist_cut->SetLineColor(2);
    //pT2_Hist_cut->Draw("same");
    //canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  pT2_Hist->GetName());
    
    pTrig1_Roc1_Mult_Hist->Draw();
    canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  pTrig1_Roc1_Mult_Hist->GetName());
    pTrig4_Roc1_Mult_Hist->Draw();
    canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  pTrig4_Roc1_Mult_Hist->GetName());
    pTrig1_Roc2_Mult_Hist->Draw();
    canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  pTrig1_Roc2_Mult_Hist->GetName());
    pTrig4_Roc2_Mult_Hist->Draw();
    canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  pTrig4_Roc2_Mult_Hist->GetName());
    pTrig3_Roc1_Mult_Hist->Draw();
    canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  pTrig3_Roc1_Mult_Hist->GetName());
    pTrig3_Roc2_Mult_Hist->Draw();
    canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  pTrig3_Roc2_Mult_Hist->GetName());
    //pT2_Mult_Hist->Draw();
    //canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  pT2_Mult_Hist->GetName());
    
    hFADC_TREF_ROC1_Hist->Draw();
    //cout << "\n\n\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\nBug fixing Info: \n p_adcrefcut/hFADC_TREF_ROC1_Hist->GetXaxis()->GetXmax() = " << p_adcrefcut/hFADC_TREF_ROC1_Hist->GetXaxis()->GetXmax();
    //cout << "\np_adcrefcut = " << p_adcrefcut << "\nhFADC_TREF_ROC1_Hist->GetXaxis()->GetXmax() = " << hFADC_TREF_ROC1_Hist->GetXaxis()->GetXmax();
    LeftLine->DrawLine(h_adcrefcut, 0, h_adcrefcut, 10);
    canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  hFADC_TREF_ROC1_Hist->GetName());
    hTref1_Hist->Draw();
    LeftLine->DrawLine(hhodo_tdcrefcut, 0, hhodo_tdcrefcut, 10);
    canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  hTref1_Hist->GetName());
    hTref2_Hist->Draw();
    LeftLine->DrawLine(hhodo_tdcrefcut, 0, hhodo_tdcrefcut, 10);
    canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  hTref2_Hist->GetName());
    hDCREF1_Hist->Draw();
    LeftLine->DrawLine(hdc_tdcrefcut, 0, hdc_tdcrefcut, 10);
    canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  hDCREF1_Hist->GetName()); 
    hDCREF2_Hist->Draw();
    LeftLine->DrawLine(hdc_tdcrefcut, 0, hdc_tdcrefcut, 10);
    canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  hDCREF2_Hist->GetName()); 
    hDCREF3_Hist->Draw();
    LeftLine->DrawLine(hdc_tdcrefcut, 0, hdc_tdcrefcut, 10);
    canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  hDCREF3_Hist->GetName());  
    hDCREF4_Hist->Draw();
    LeftLine->DrawLine(hdc_tdcrefcut, 0, hdc_tdcrefcut, 10);
    canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  hDCREF4_Hist->GetName());  
    hDCREF5_Hist->Draw();
    LeftLine->DrawLine(hdc_tdcrefcut, 0, hdc_tdcrefcut, 10);
    canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  hDCREF5_Hist->GetName()); 
    
    /*
    hFADC_TREF_ROC1_Mult_Hist->Draw();
    canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  hFADC_TREF_ROC1_Mult_Hist->GetName());
    hTref1_Mult_Hist->Draw();
    canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  hTref1_Mult_Hist->GetName());
    hTref2_Mult_Hist->Draw();
    canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  hTref2_Mult_Hist->GetName());
    hDCREF1_Mult_Hist->Draw();
    canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  hDCREF1_Mult_Hist->GetName());
    hDCREF2_Mult_Hist->Draw();
    canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  hDCREF2_Mult_Hist->GetName());
    hDCREF3_Mult_Hist->Draw();
    canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  hDCREF3_Mult_Hist->GetName()); 
    hDCREF4_Mult_Hist->Draw();
    canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  hDCREF4_Mult_Hist->GetName()); 
    hDCREF5_Mult_Hist->Draw();
    canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  hDCREF5_Mult_Hist->GetName());
    */

    pFADC_TREF_ROC2_Hist->Draw();
    LeftLine->DrawLine(p_adcrefcut, 0, p_adcrefcut, pFADC_TREF_ROC2_Hist->GetBinContent(pFADC_TREF_ROC2_Hist->GetMaximumBin()));
    canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  pFADC_TREF_ROC2_Hist->GetName());
    pTref1_Hist->Draw();
    LeftLine->DrawLine(phodo_tdcrefcut, 0, phodo_tdcrefcut, pTref1_Hist->GetBinContent(pTref1_Hist->GetMaximumBin()));
    canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  pTref1_Hist->GetName()); 
    pTref2_Hist->Draw();
    LeftLine->DrawLine(phodo_tdcrefcut, 0, phodo_tdcrefcut, pTref2_Hist->GetBinContent(pTref2_Hist->GetMaximumBin()));
    canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  pTref2_Hist->GetName()); 
    pDCREF1_Hist->Draw();
    LeftLine->DrawLine(pdc_tdcrefcut, 0, pdc_tdcrefcut, pDCREF1_Hist->GetBinContent(pDCREF1_Hist->GetMaximumBin()));
    canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  pDCREF1_Hist->GetName());
    pDCREF2_Hist->Draw();
    LeftLine->DrawLine(pdc_tdcrefcut, 0, pdc_tdcrefcut, pDCREF2_Hist->GetBinContent(pDCREF2_Hist->GetMaximumBin()));
    canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  pDCREF2_Hist->GetName());
    pDCREF3_Hist->Draw();
    LeftLine->DrawLine(pdc_tdcrefcut, 0, pdc_tdcrefcut, pDCREF3_Hist->GetBinContent(pDCREF3_Hist->GetMaximumBin()));
    canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  pDCREF3_Hist->GetName()); 
    pDCREF4_Hist->Draw();
    LeftLine->DrawLine(pdc_tdcrefcut, 0, pdc_tdcrefcut, pDCREF4_Hist->GetBinContent(pDCREF4_Hist->GetMaximumBin()));
    canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  pDCREF4_Hist->GetName()); 
    pDCREF5_Hist->Draw();
    LeftLine->DrawLine(pdc_tdcrefcut, 0, pdc_tdcrefcut, pDCREF5_Hist->GetBinContent(pDCREF5_Hist->GetMaximumBin()));
    canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  pDCREF5_Hist->GetName()); 
    pDCREF6_Hist->Draw();
    LeftLine->DrawLine(pdc_tdcrefcut, 0, pdc_tdcrefcut, pDCREF6_Hist->GetBinContent(pDCREF6_Hist->GetMaximumBin()));
    canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  pDCREF6_Hist->GetName()); 
    pDCREF7_Hist->Draw();
    LeftLine->DrawLine(pdc_tdcrefcut, 0, pdc_tdcrefcut, pDCREF7_Hist->GetBinContent(pDCREF7_Hist->GetMaximumBin()));
    canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  pDCREF7_Hist->GetName()); 
    pDCREF8_Hist->Draw();
    LeftLine->DrawLine(pdc_tdcrefcut, 0, pdc_tdcrefcut, pDCREF8_Hist->GetBinContent(pDCREF8_Hist->GetMaximumBin()));
    canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  pDCREF8_Hist->GetName()); 
    pDCREF9_Hist->Draw();
    LeftLine->DrawLine(pdc_tdcrefcut, 0, pdc_tdcrefcut, pDCREF9_Hist->GetBinContent(pDCREF9_Hist->GetMaximumBin()));
    canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  pDCREF9_Hist->GetName()); 
    pDCREF10_Hist->Draw();
    LeftLine->DrawLine(pdc_tdcrefcut, 0, pdc_tdcrefcut, pDCREF10_Hist->GetBinContent(pDCREF10_Hist->GetMaximumBin()));
    
    if(SaveOption == 0 ){ 
    	canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  pDCREF10_Hist->GetName());
    }else{
    	canvas->Print(Form("output/REF_TimePlots_%d.pdf)",RunNumber),  pDCREF10_Hist->GetName());
    }
    
    } // end save ref times
    
    if(SaveOption == 0 || SaveOption == 2) {
    //Sum Plots
    cerAdcTdcDiffTime_Hist_Sum->Draw();
    LeftLine->DrawLine(hcer_adcTimeWindowMin[0], 0, hcer_adcTimeWindowMin[0], cerAdcTdcDiffTime_Hist_Sum->GetBinContent(cerAdcTdcDiffTime_Hist_Sum->GetMaximumBin()));
    RightLine->DrawLine(hcer_adcTimeWindowMax[0], 0, hcer_adcTimeWindowMax[0], cerAdcTdcDiffTime_Hist_Sum->GetBinContent(cerAdcTdcDiffTime_Hist_Sum->GetMaximumBin()));
    if(SaveOption == 0){ 
    	canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  cerAdcTdcDiffTime_Hist_Sum->GetName());
    }else{
    	canvas->Print(Form("output/REF_TimePlots_%d.pdf(",RunNumber),  cerAdcTdcDiffTime_Hist_Sum->GetName());
    }
    hgcerAdcTdcDiffTime_Hist_Sum->Draw();
    LeftLine->DrawLine(phgcer_adcTimeWindowMin[0], 0, phgcer_adcTimeWindowMin[0], hgcerAdcTdcDiffTime_Hist_Sum->GetBinContent(hgcerAdcTdcDiffTime_Hist_Sum->GetMaximumBin()));
    RightLine->DrawLine(phgcer_adcTimeWindowMax[0], 0, phgcer_adcTimeWindowMax[0], hgcerAdcTdcDiffTime_Hist_Sum->GetBinContent(hgcerAdcTdcDiffTime_Hist_Sum->GetMaximumBin()));
    canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  hgcerAdcTdcDiffTime_Hist_Sum->GetName());
    
    ngcerAdcTdcDiffTime_Hist_Sum->Draw();
    LeftLine->DrawLine(pngcer_adcTimeWindowMin[0], 0, pngcer_adcTimeWindowMin[0], ngcerAdcTdcDiffTime_Hist_Sum->GetBinContent(ngcerAdcTdcDiffTime_Hist_Sum->GetMaximumBin()));
    RightLine->DrawLine(pngcer_adcTimeWindowMax[0], 0, pngcer_adcTimeWindowMax[0], ngcerAdcTdcDiffTime_Hist_Sum->GetBinContent(ngcerAdcTdcDiffTime_Hist_Sum->GetMaximumBin()));
    canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  ngcerAdcTdcDiffTime_Hist_Sum->GetName());
    
    aeroAdcTdcDiffTime_Hist_Sum[0]->Draw();
    LeftLine->DrawLine(paero_adcPosTimeWindowMin[0], 0, paero_adcPosTimeWindowMin[0], aeroAdcTdcDiffTime_Hist_Sum[0]->GetBinContent(aeroAdcTdcDiffTime_Hist_Sum[0]->GetMaximumBin()));
    RightLine->DrawLine(paero_adcPosTimeWindowMax[0], 0, paero_adcPosTimeWindowMax[0], aeroAdcTdcDiffTime_Hist_Sum[0]->GetBinContent(aeroAdcTdcDiffTime_Hist_Sum[0]->GetMaximumBin()));
    canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  aeroAdcTdcDiffTime_Hist_Sum[0]->GetName());
    
    aeroAdcTdcDiffTime_Hist_Sum[1]->Draw();
    LeftLine->DrawLine(paero_adcNegTimeWindowMin[0], 0, paero_adcNegTimeWindowMin[0], aeroAdcTdcDiffTime_Hist_Sum[1]->GetBinContent(aeroAdcTdcDiffTime_Hist_Sum[1]->GetMaximumBin()));
    RightLine->DrawLine(paero_adcNegTimeWindowMax[0], 0, paero_adcNegTimeWindowMax[0], aeroAdcTdcDiffTime_Hist_Sum[1]->GetBinContent(aeroAdcTdcDiffTime_Hist_Sum[1]->GetMaximumBin()));
    canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  aeroAdcTdcDiffTime_Hist_Sum[1]->GetName());
    
    for(Int_t iPlane = 0; iPlane < hcalPlanes; iPlane++)
    { 
        for(Int_t iSide = 0; iSide < calSides; iSide++)
        {
            hcalAdcTdcDiffTime_Hist_Sum[iPlane][iSide]->Draw();
            if (iSide == 0) {    
                LeftLine->DrawLine(hcal_pos_AdcTimeWindowMin[ 0], 0, hcal_pos_AdcTimeWindowMin[0], hcalAdcTdcDiffTime_Hist_Sum[iPlane][iSide]->GetBinContent(hcalAdcTdcDiffTime_Hist_Sum[iPlane][iSide]->GetMaximumBin()));
                RightLine->DrawLine(hcal_pos_AdcTimeWindowMax[0], 0, hcal_pos_AdcTimeWindowMax[0], hcalAdcTdcDiffTime_Hist_Sum[iPlane][iSide]->GetBinContent(hcalAdcTdcDiffTime_Hist_Sum[iPlane][iSide]->GetMaximumBin()));
            } else {
                LeftLine->DrawLine(hcal_neg_AdcTimeWindowMin[0], 0, hcal_neg_AdcTimeWindowMin[0], hcalAdcTdcDiffTime_Hist_Sum[iPlane][iSide]->GetBinContent(hcalAdcTdcDiffTime_Hist_Sum[iPlane][iSide]->GetMaximumBin()));
                RightLine->DrawLine(hcal_neg_AdcTimeWindowMax[0], 0, hcal_neg_AdcTimeWindowMax[0], hcalAdcTdcDiffTime_Hist_Sum[iPlane][iSide]->GetBinContent(hcalAdcTdcDiffTime_Hist_Sum[iPlane][iSide]->GetMaximumBin()));
            }
            canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  hcalAdcTdcDiffTime_Hist_Sum[iPlane][iSide]->GetName());
        }
    }
    
    for(Int_t iSide = 0; iSide < calSides; iSide++)
    {
        pcalprAdcTdcDiffTime_Hist_Sum[iSide]->Draw();
        if (iSide == 0) {    
            LeftLine->DrawLine(pcal_pos_AdcTimeWindowMin[0], 0, pcal_pos_AdcTimeWindowMin[0], pcalprAdcTdcDiffTime_Hist_Sum[iSide]->GetBinContent(pcalprAdcTdcDiffTime_Hist_Sum[iSide]->GetMaximumBin()));
            RightLine->DrawLine(pcal_pos_AdcTimeWindowMax[0], 0, pcal_pos_AdcTimeWindowMax[0], pcalprAdcTdcDiffTime_Hist_Sum[iSide]->GetBinContent(pcalprAdcTdcDiffTime_Hist_Sum[iSide]->GetMaximumBin()));
        } else {
            LeftLine->DrawLine(pcal_neg_AdcTimeWindowMin[0], 0, pcal_neg_AdcTimeWindowMin[0], pcalprAdcTdcDiffTime_Hist_Sum[iSide]->GetBinContent(pcalprAdcTdcDiffTime_Hist_Sum[iSide]->GetMaximumBin()));
            RightLine->DrawLine(pcal_neg_AdcTimeWindowMax[0], 0, pcal_neg_AdcTimeWindowMax[0], pcalprAdcTdcDiffTime_Hist_Sum[iSide]->GetBinContent(pcalprAdcTdcDiffTime_Hist_Sum[iSide]->GetMaximumBin()));
        }
        canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  pcalprAdcTdcDiffTime_Hist_Sum[iSide]->GetName());
    }
    
    pcalflyAdcTdcDiffTime_Hist_Sum->Draw();
    LeftLine->DrawLine(pcal_arr_AdcTimeWindowMin[0], 0, pcal_arr_AdcTimeWindowMin[0], pcalflyAdcTdcDiffTime_Hist_Sum->GetBinContent(pcalflyAdcTdcDiffTime_Hist_Sum->GetMaximumBin()));
    RightLine->DrawLine(pcal_arr_AdcTimeWindowMin[0], 0, pcal_arr_AdcTimeWindowMin[0], pcalflyAdcTdcDiffTime_Hist_Sum->GetBinContent(pcalflyAdcTdcDiffTime_Hist_Sum->GetMaximumBin()));
    canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  pcalflyAdcTdcDiffTime_Hist_Sum->GetName());
    
    /*
    pFADC_TREF_ROC2_Mult_Hist->Draw();
    canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  pFADC_TREF_ROC2_Mult_Hist->GetName());
    pTref1_Mult_Hist->Draw();
    canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  pTref1_Mult_Hist->GetName());
    pTref2_Mult_Hist->Draw();
    canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  pTref2_Mult_Hist->GetName());
    pDCREF1_Mult_Hist->Draw();
    canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  pDCREF1_Mult_Hist->GetName());
    pDCREF2_Mult_Hist->Draw();
    canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  pDCREF2_Mult_Hist->GetName());
    pDCREF3_Mult_Hist->Draw();
    canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  pDCREF3_Mult_Hist->GetName()); 
    pDCREF4_Mult_Hist->Draw();
    canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  pDCREF4_Mult_Hist->GetName()); 
    pDCREF5_Mult_Hist->Draw();
    canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  pDCREF5_Mult_Hist->GetName()); 
    pDCREF6_Mult_Hist->Draw();
    canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  pDCREF6_Mult_Hist->GetName()); 
    pDCREF7_Mult_Hist->Draw();
    canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  pDCREF7_Mult_Hist->GetName()); 
    pDCREF8_Mult_Hist->Draw();
    canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  pDCREF8_Mult_Hist->GetName()); 
    pDCREF9_Mult_Hist->Draw();
    canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  pDCREF9_Mult_Hist->GetName()); 
    pDCREF10_Mult_Hist->Draw();
    canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  pDCREF10_Mult_Hist->GetName());
    */

    // hodoscope variables
    for(Int_t iPlane = 0; iPlane < HodPlanes; iPlane++)
    {
        for(Int_t iSide = 0; iSide < HodSides; iSide++)
        {
            for(Int_t iPmt = 0; iPmt < hHodbars[iPlane]; iPmt++)
            {
                hHodAdcTdcDiffTime_Hist[iPlane][iSide][iPmt]->Draw();
                if(iSide == 0) {
                    LeftLine->DrawLine(hhodo_PosAdcTimeWindowMin[iPmt+iPlane*MaxHodBars], 0, hhodo_PosAdcTimeWindowMin[iPmt+iPlane*MaxHodBars], hHodAdcTdcDiffTime_Hist[iPlane][iSide][iPmt]->GetBinContent(hHodAdcTdcDiffTime_Hist[iPlane][iSide][iPmt]->GetMaximumBin())); 
                    RightLine->DrawLine(hhodo_PosAdcTimeWindowMax[iPmt+iPlane*MaxHodBars], 0, hhodo_PosAdcTimeWindowMax[iPmt+iPlane*MaxHodBars], hHodAdcTdcDiffTime_Hist[iPlane][iSide][iPmt]->GetBinContent(hHodAdcTdcDiffTime_Hist[iPlane][iSide][iPmt]->GetMaximumBin()));
                } else {
                    LeftLine->DrawLine(hhodo_NegAdcTimeWindowMin[iPmt+iPlane*MaxHodBars], 0, hhodo_NegAdcTimeWindowMin[iPmt+iPlane*MaxHodBars], hHodAdcTdcDiffTime_Hist[iPlane][iSide][iPmt]->GetBinContent(hHodAdcTdcDiffTime_Hist[iPlane][iSide][iPmt]->GetMaximumBin())); 
                    RightLine->DrawLine(hhodo_NegAdcTimeWindowMax[iPmt+iPlane*MaxHodBars], 0, hhodo_NegAdcTimeWindowMax[iPmt+iPlane*MaxHodBars], hHodAdcTdcDiffTime_Hist[iPlane][iSide][iPmt]->GetBinContent(hHodAdcTdcDiffTime_Hist[iPlane][iSide][iPmt]->GetMaximumBin()));
                }
                canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  hHodAdcTdcDiffTime_Hist[iPlane][iSide][iPmt]->GetName());
                //hHodAdcMult_Hist[iPlane][iSide][iPmt]->Draw();
                //canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  hHodAdcMult_Hist[iPlane][iSide][iPmt]->GetName());
            }
            for(Int_t iPmt = 0; iPmt < pHodbars[iPlane]; iPmt++)
            {
                pHodAdcTdcDiffTime_Hist[iPlane][iSide][iPmt]->Draw();
                if(iSide == 0) {
                    LeftLine->DrawLine(phodo_PosAdcTimeWindowMin[iPmt+iPlane*MaxHodBars], 0, phodo_PosAdcTimeWindowMin[iPmt+iPlane*MaxHodBars], pHodAdcTdcDiffTime_Hist[iPlane][iSide][iPmt]->GetBinContent(pHodAdcTdcDiffTime_Hist[iPlane][iSide][iPmt]->GetMaximumBin())); 
                    RightLine->DrawLine(phodo_PosAdcTimeWindowMax[iPmt+iPlane*MaxHodBars], 0, phodo_PosAdcTimeWindowMax[iPmt+iPlane*MaxHodBars], pHodAdcTdcDiffTime_Hist[iPlane][iSide][iPmt]->GetBinContent(pHodAdcTdcDiffTime_Hist[iPlane][iSide][iPmt]->GetMaximumBin()));
                } else {
                    LeftLine->DrawLine(phodo_NegAdcTimeWindowMin[iPmt+iPlane*MaxHodBars], 0, phodo_NegAdcTimeWindowMin[iPmt+iPlane*MaxHodBars], pHodAdcTdcDiffTime_Hist[iPlane][iSide][iPmt]->GetBinContent(pHodAdcTdcDiffTime_Hist[iPlane][iSide][iPmt]->GetMaximumBin())); 
                    RightLine->DrawLine(phodo_NegAdcTimeWindowMax[iPmt+iPlane*MaxHodBars], 0, phodo_NegAdcTimeWindowMax[iPmt+iPlane*MaxHodBars], pHodAdcTdcDiffTime_Hist[iPlane][iSide][iPmt]->GetBinContent(pHodAdcTdcDiffTime_Hist[iPlane][iSide][iPmt]->GetMaximumBin()));
                }
                canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  pHodAdcTdcDiffTime_Hist[iPlane][iSide][iPmt]->GetName());
                //pHodAdcMult_Hist[iPlane][iSide][iPmt]->Draw();
                //canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  pHodAdcMult_Hist[iPlane][iSide][iPmt]->GetName());
            }
        }
    }
    /* // Not super usfull, removing from pdfs
    for(Int_t iPlane = 0; iPlane < HodPlanes; iPlane++)
    {
        for(Int_t iSide = 0; iSide < HodSides1; iSide++)
        {
            for(Int_t iPmt = 0; iPmt < hHodbars[iPlane]; iPmt++)
            {
                hHodAdcPulseTimeRaw_Hist[iPlane][iSide][iPmt]->Draw();
                canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  hHodAdcPulseTimeRaw_Hist[iPlane][iSide][iPmt]->GetName());
                hHodTdcTimeRaw_Hist[iPlane][iSide][iPmt]->Draw();
                canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  hHodTdcTimeRaw_Hist[iPlane][iSide][iPmt]->GetName());
            }
            for(Int_t iPmt = 0; iPmt < pHodbars[iPlane]; iPmt++)
            {
                pHodAdcPulseTimeRaw_Hist[iPlane][iSide][iPmt]->Draw();
                canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  pHodAdcPulseTimeRaw_Hist[iPlane][iSide][iPmt]->GetName());
                pHodTdcTimeRaw_Hist[iPlane][iSide][iPmt]->Draw();
                canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  pHodTdcTimeRaw_Hist[iPlane][iSide][iPmt]->GetName());

            }
        }
    }
    */
    //dc variables
    for(Int_t i = 0; i < dcPlanes; i++)
    {
        hdcrawtdc_Hist[i]->Draw();
        LeftLine->DrawLine(hdc_tdc_min_win[i], 0, hdc_tdc_min_win[i], hdcrawtdc_Hist[i]->GetBinContent(hdcrawtdc_Hist[i]->GetMaximumBin()));
        RightLine->DrawLine(hdc_tdc_max_win[i], 0, hdc_tdc_max_win[i], hdcrawtdc_Hist[i]->GetBinContent(hdcrawtdc_Hist[i]->GetMaximumBin()));
        canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  hdcrawtdc_Hist[i]->GetName());
        pdcrawtdc_Hist[i]->Draw();
        LeftLine->DrawLine(pdc_tdc_min_win[i], 0, pdc_tdc_min_win[i], pdcrawtdc_Hist[i]->GetBinContent(pdcrawtdc_Hist[i]->GetMaximumBin()));
        RightLine->DrawLine(pdc_tdc_max_win[i], 0, pdc_tdc_max_win[i], pdcrawtdc_Hist[i]->GetBinContent(pdcrawtdc_Hist[i]->GetMaximumBin()));
        canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  pdcrawtdc_Hist[i]->GetName());
        
        //hdcnhit_Hist[i]->Draw();
        //canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  hdcnhit_Hist[i]->GetName());
        //pdcnhit_Hist[i]->Draw();
        //canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  pdcnhit_Hist[i]->GetName());
    }
    
    //Gas cherenkovs
    //hms
    for(Int_t iPmt = 0; iPmt < hcerNpmts; iPmt++)
    {
        cerAdcTdcDiffTime_Hist[iPmt]->Draw();
        LeftLine->DrawLine(hcer_adcTimeWindowMin[iPmt], 0, hcer_adcTimeWindowMin[iPmt], cerAdcTdcDiffTime_Hist[iPmt]->GetBinContent(cerAdcTdcDiffTime_Hist[iPmt]->GetMaximumBin()));
        RightLine->DrawLine(hcer_adcTimeWindowMax[iPmt], 0, hcer_adcTimeWindowMax[iPmt], cerAdcTdcDiffTime_Hist[iPmt]->GetBinContent(cerAdcTdcDiffTime_Hist[iPmt]->GetMaximumBin()));
        canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  cerAdcTdcDiffTime_Hist[iPmt]->GetName());
        //cerAdcMult_Hist[iPmt]->Draw();
        //canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  cerAdcMult_Hist[iPmt]->GetName());
    }
    
    //shms
    for(Int_t iPmt = 0; iPmt < pcerNpmts; iPmt++)
    {
        hgcerAdcTdcDiffTime_Hist[iPmt]->Draw();
        LeftLine->DrawLine(phgcer_adcTimeWindowMin[iPmt], 0, phgcer_adcTimeWindowMin[iPmt], hgcerAdcTdcDiffTime_Hist[iPmt]->GetBinContent(hgcerAdcTdcDiffTime_Hist[iPmt]->GetMaximumBin()));
        RightLine->DrawLine(phgcer_adcTimeWindowMax[iPmt], 0, phgcer_adcTimeWindowMax[iPmt], hgcerAdcTdcDiffTime_Hist[iPmt]->GetBinContent(hgcerAdcTdcDiffTime_Hist[iPmt]->GetMaximumBin()));
        canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  hgcerAdcTdcDiffTime_Hist[iPmt]->GetName());
        ngcerAdcTdcDiffTime_Hist[iPmt]->Draw();
        LeftLine->DrawLine(pngcer_adcTimeWindowMin[iPmt], 0, pngcer_adcTimeWindowMin[iPmt], ngcerAdcTdcDiffTime_Hist[iPmt]->GetBinContent(ngcerAdcTdcDiffTime_Hist[iPmt]->GetMaximumBin()));
        RightLine->DrawLine(pngcer_adcTimeWindowMax[iPmt], 0, pngcer_adcTimeWindowMax[iPmt], ngcerAdcTdcDiffTime_Hist[iPmt]->GetBinContent(ngcerAdcTdcDiffTime_Hist[iPmt]->GetMaximumBin()));
        canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  ngcerAdcTdcDiffTime_Hist[iPmt]->GetName());
        //hgcerAdcMult_Hist[iPmt]->Draw();
        //canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  hgcerAdcMult_Hist[iPmt]->GetName());
        //ngcerAdcMult_Hist[iPmt]->Draw();
        //canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  ngcerAdcMult_Hist[iPmt]->GetName());
    }
    
    //aerogel 
    for(Int_t iSide = 0; iSide < aeroSides; iSide++)
    {
        for(Int_t iPmt = 0; iPmt < aeroNumPmts; iPmt++)
        {
            aeroAdcTdcDiffTime_Hist[iSide][iPmt]->Draw();
            if (iSide == 0) {    
                LeftLine->DrawLine(paero_adcPosTimeWindowMin[iPmt], 0, paero_adcPosTimeWindowMin[iPmt], aeroAdcTdcDiffTime_Hist[iSide][iPmt]->GetBinContent(aeroAdcTdcDiffTime_Hist[iSide][iPmt]->GetMaximumBin()));
                RightLine->DrawLine(paero_adcPosTimeWindowMax[iPmt], 0, paero_adcPosTimeWindowMax[iPmt], aeroAdcTdcDiffTime_Hist[iSide][iPmt]->GetBinContent(aeroAdcTdcDiffTime_Hist[iSide][iPmt]->GetMaximumBin()));
            } else {
                LeftLine->DrawLine(paero_adcNegTimeWindowMin[iPmt], 0, paero_adcNegTimeWindowMin[iPmt], aeroAdcTdcDiffTime_Hist[iSide][iPmt]->GetBinContent(aeroAdcTdcDiffTime_Hist[iSide][iPmt]->GetMaximumBin()));
                RightLine->DrawLine(paero_adcNegTimeWindowMax[iPmt], 0, paero_adcNegTimeWindowMax[iPmt], aeroAdcTdcDiffTime_Hist[iSide][iPmt]->GetBinContent(aeroAdcTdcDiffTime_Hist[iSide][iPmt]->GetMaximumBin()));
            }
            canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  aeroAdcTdcDiffTime_Hist[iSide][iPmt]->GetName());
            //aeroAdcMult_Hist[iSide][iPmt]->Draw();
            //canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  aeroAdcMult_Hist[iSide][iPmt]->GetName());
        }
    }

    //Calorimeters
    //hms
    for(Int_t iPlane = 0; iPlane < hcalPlanes; iPlane++)
    {
        for(Int_t iSide = 0; iSide < calSides; iSide++)
        {
            for(Int_t iPmt = 0; iPmt < hcalNumPmts[iPlane]; iPmt++)
            {
                hcalAdcTdcDiffTime_Hist[iPlane][iSide][iPmt]->Draw();
                if (iSide == 0) {    
                    LeftLine->DrawLine(hcal_pos_AdcTimeWindowMin[iPmt+iPlane*hcalNumPmtsMax], 0, hcal_pos_AdcTimeWindowMin[iPmt+iPlane*hcalNumPmtsMax], hcalAdcTdcDiffTime_Hist[iPlane][iSide][iPmt]->GetBinContent(hcalAdcTdcDiffTime_Hist[iPlane][iSide][iPmt]->GetMaximumBin()));
                    RightLine->DrawLine(hcal_pos_AdcTimeWindowMax[iPmt+iPlane*hcalNumPmtsMax], 0, hcal_pos_AdcTimeWindowMax[iPmt+iPlane*hcalNumPmtsMax], hcalAdcTdcDiffTime_Hist[iPlane][iSide][iPmt]->GetBinContent(hcalAdcTdcDiffTime_Hist[iPlane][iSide][iPmt]->GetMaximumBin()));
                } else {
                    LeftLine->DrawLine(hcal_neg_AdcTimeWindowMin[iPmt+iPlane*hcalNumPmtsMax], 0, hcal_neg_AdcTimeWindowMin[iPmt+iPlane*hcalNumPmtsMax], hcalAdcTdcDiffTime_Hist[iPlane][iSide][iPmt]->GetBinContent(hcalAdcTdcDiffTime_Hist[iPlane][iSide][iPmt]->GetMaximumBin()));
                    RightLine->DrawLine(hcal_neg_AdcTimeWindowMax[iPmt+iPlane*hcalNumPmtsMax], 0, hcal_neg_AdcTimeWindowMax[iPmt+iPlane*hcalNumPmtsMax], hcalAdcTdcDiffTime_Hist[iPlane][iSide][iPmt]->GetBinContent(hcalAdcTdcDiffTime_Hist[iPlane][iSide][iPmt]->GetMaximumBin()));
                }
                canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  hcalAdcTdcDiffTime_Hist[iPlane][iSide][iPmt]->GetName());
                //hcalAdcMult_Hist[iPlane][iSide][iPmt]->Draw();
                //canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  hcalAdcMult_Hist[iPlane][iSide][iPmt]->GetName());
            }
        }
    }
    
    //shms calorimeter
    for(Int_t iSide = 0; iSide < calSides; iSide++)
    {
        for(Int_t iPmt = 0; iPmt < pcalPrNumPmts; iPmt++)
        {
            pcalprAdcTdcDiffTime_Hist[iSide][iPmt]->Draw();
            if (iSide == 0) {    
                LeftLine->DrawLine(pcal_pos_AdcTimeWindowMin[iPmt], 0, pcal_pos_AdcTimeWindowMin[iPmt], pcalprAdcTdcDiffTime_Hist[iSide][iPmt]->GetBinContent(pcalprAdcTdcDiffTime_Hist[iSide][iPmt]->GetMaximumBin()));
                RightLine->DrawLine(pcal_pos_AdcTimeWindowMax[iPmt], 0, hcal_pos_AdcTimeWindowMax[iPmt], pcalprAdcTdcDiffTime_Hist[iSide][iPmt]->GetBinContent(pcalprAdcTdcDiffTime_Hist[iSide][iPmt]->GetMaximumBin()));
            } else {
                LeftLine->DrawLine(pcal_neg_AdcTimeWindowMin[iPmt], 0, pcal_neg_AdcTimeWindowMin[iPmt], pcalprAdcTdcDiffTime_Hist[iSide][iPmt]->GetBinContent(pcalprAdcTdcDiffTime_Hist[iSide][iPmt]->GetMaximumBin()));
                RightLine->DrawLine(pcal_neg_AdcTimeWindowMax[iPmt], 0, pcal_neg_AdcTimeWindowMax[iPmt], pcalprAdcTdcDiffTime_Hist[iSide][iPmt]->GetBinContent(pcalprAdcTdcDiffTime_Hist[iSide][iPmt]->GetMaximumBin()));
            }
            canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  pcalprAdcTdcDiffTime_Hist[iSide][iPmt]->GetName());
            //pcalprAdcMult_Hist[iSide][iPmt]->Draw();
            //canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  pcalprAdcMult_Hist[iSide][iPmt]->GetName());
        } 
    }    
    
    for(Int_t iPmt = 0; iPmt < pcalFlyNumPmts - 1; iPmt++)
    {
        pcalflyAdcTdcDiffTime_Hist[iPmt]->Draw();
        LeftLine->DrawLine(pcal_arr_AdcTimeWindowMin[iPmt], 0, pcal_arr_AdcTimeWindowMin[iPmt], pcalflyAdcTdcDiffTime_Hist[iPmt]->GetBinContent(pcalflyAdcTdcDiffTime_Hist[iPmt]->GetMaximumBin()));
        RightLine->DrawLine(pcal_arr_AdcTimeWindowMax[iPmt], 0, pcal_arr_AdcTimeWindowMax[iPmt], pcalflyAdcTdcDiffTime_Hist[iPmt]->GetBinContent(pcalflyAdcTdcDiffTime_Hist[iPmt]->GetMaximumBin()));
        canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  pcalflyAdcTdcDiffTime_Hist[iPmt]->GetName());
        //pcalflyAdcMult_Hist[iPmt]->Draw();
        //canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  pcalflyAdcMult_Hist[iPmt]->GetName());
    }
    
    // print last one seperate, so that it save properly
    pcalflyAdcTdcDiffTime_Hist[pcalFlyNumPmts-1]->Draw();
    LeftLine->DrawLine(pcal_arr_AdcTimeWindowMin[pcalFlyNumPmts-1], 0, pcal_arr_AdcTimeWindowMin[pcalFlyNumPmts-1], pcalflyAdcTdcDiffTime_Hist[pcalFlyNumPmts-1]->GetBinContent(pcalflyAdcTdcDiffTime_Hist[pcalFlyNumPmts-1]->GetMaximumBin()));
    RightLine->DrawLine(pcal_arr_AdcTimeWindowMax[pcalFlyNumPmts-1], 0, pcal_arr_AdcTimeWindowMax[pcalFlyNumPmts-1], pcalflyAdcTdcDiffTime_Hist[pcalFlyNumPmts-1]->GetBinContent(pcalflyAdcTdcDiffTime_Hist[pcalFlyNumPmts-1]->GetMaximumBin()));
    canvas->Print(Form("output/REF_TimePlots_%d.pdf",RunNumber),  pcalflyAdcTdcDiffTime_Hist[pcalFlyNumPmts-1]->GetName());
    //pcalflyAdcMult_Hist[pcalFlyNumPmts-1]->Draw();
    //canvas->Print(Form("output/REF_TimePlots_%d.pdf)",RunNumber),  pcalflyAdcMult_Hist[pcalFlyNumPmts-1]->GetName());
    }// end save detector times
}

// input is the path from ref_times directory to rootfile and the run number that your using
void RefTimes( TString rootFileName, Int_t RunNumber)
{
    gROOT->SetBatch(kTRUE);
    //get root file
    TFile* inFile = new TFile(rootFileName, "READ");
    
    if(!inFile->IsOpen())
    {
        cout << "File did not open properly.\nCheck That: '" << rootFileName << "' exists and is not corrupted.\n --- Ending --- \n";
        return;
    }
    
    //get tree from root file
    TTree *DataTree = dynamic_cast <TTree*> (inFile->Get("T"));
    
    setBranchAddresses(DataTree);
    
    //make histograms
    makeHistos();
    
    //fill histos and apply cuts
    fillHistos(DataTree);
    
    cout << "Finished filling plots, saving output!\n";
    
    // make sure cut values set
    setCutValues();
    
    //save plots with cuts in
    if(SavePDF){
        SaveToPDF(RunNumber);
    }
    
    //save to root file as histograms, (in case you wanted to fit them or something)
    if(SaveRoot){
        //make output file
        TFile* outFile = new TFile(Form("./output/REF_TimePlots_%d.root", RunNumber), "RECREATE");
        
        //make directories for drawing the files in
        TDirectory *TVar = outFile->mkdir("T");
        
        TDirectory *HMS = outFile->mkdir("HMS");
        
        TDirectory *hDC     = HMS->mkdir("dc");
        TDirectory *hHodo   = HMS->mkdir("hodo");
        TDirectory *hCer    = HMS->mkdir("cer");
        TDirectory *hCal    = HMS->mkdir("cal");
        
        TDirectory *SHMS = outFile->mkdir("SHMS");
        
        TDirectory *pDC     = SHMS->mkdir("dc"); 
        TDirectory *pHodo   = SHMS->mkdir("hodo"); 
        TDirectory *pHgcer  = SHMS->mkdir("hgcer"); 
        TDirectory *pNgcer  = SHMS->mkdir("ngcer"); 
        TDirectory *pAero   = SHMS->mkdir("aero"); 
        TDirectory *pCal    = SHMS->mkdir("cal"); 
        
        
        //write histogrames to file
        TVar->WriteObject(hFADC_TREF_ROC1_Hist, hFADC_TREF_ROC1_Hist->GetName());
        TVar->WriteObject(hTref1_Hist, hTref1_Hist->GetName());
        TVar->WriteObject(hTref2_Hist, hTref2_Hist->GetName());
        TVar->WriteObject(hDCREF1_Hist, hDCREF1_Hist->GetName()); 
        TVar->WriteObject(hDCREF2_Hist, hDCREF2_Hist->GetName()); 
        TVar->WriteObject(hDCREF3_Hist, hDCREF3_Hist->GetName());  
        TVar->WriteObject(hDCREF4_Hist, hDCREF4_Hist->GetName());  
        TVar->WriteObject(hDCREF5_Hist, hDCREF5_Hist->GetName()); 
        
        TVar->WriteObject(hFADC_TREF_ROC1_Mult_Hist, hFADC_TREF_ROC1_Mult_Hist->GetName());
        TVar->WriteObject(hTref1_Mult_Hist, hTref1_Mult_Hist->GetName());
        TVar->WriteObject(hTref2_Mult_Hist, hTref2_Mult_Hist->GetName());
        TVar->WriteObject(hDCREF1_Mult_Hist, hDCREF1_Mult_Hist->GetName());
        TVar->WriteObject(hDCREF2_Mult_Hist, hDCREF2_Mult_Hist->GetName());
        TVar->WriteObject(hDCREF3_Mult_Hist, hDCREF3_Mult_Hist->GetName()); 
        TVar->WriteObject(hDCREF4_Mult_Hist, hDCREF4_Mult_Hist->GetName()); 
        TVar->WriteObject(hDCREF5_Mult_Hist, hDCREF5_Mult_Hist->GetName());

        TVar->WriteObject(pFADC_TREF_ROC2_Hist, pFADC_TREF_ROC2_Hist->GetName());
        TVar->WriteObject(pTref1_Hist, pTref1_Hist->GetName()); 
        TVar->WriteObject(pTref2_Hist, pTref2_Hist->GetName()); 
        TVar->WriteObject(pDCREF1_Hist, pDCREF1_Hist->GetName());
        TVar->WriteObject(pDCREF2_Hist, pDCREF2_Hist->GetName());
        TVar->WriteObject(pDCREF3_Hist, pDCREF3_Hist->GetName()); 
        TVar->WriteObject(pDCREF4_Hist, pDCREF4_Hist->GetName()); 
        TVar->WriteObject(pDCREF5_Hist, pDCREF5_Hist->GetName()); 
        TVar->WriteObject(pDCREF6_Hist, pDCREF6_Hist->GetName()); 
        TVar->WriteObject(pDCREF7_Hist, pDCREF7_Hist->GetName()); 
        TVar->WriteObject(pDCREF8_Hist, pDCREF8_Hist->GetName()); 
        TVar->WriteObject(pDCREF9_Hist, pDCREF9_Hist->GetName()); 
        TVar->WriteObject(pDCREF10_Hist, pDCREF10_Hist->GetName());
        
        TVar->WriteObject(pFADC_TREF_ROC2_Mult_Hist, pFADC_TREF_ROC2_Mult_Hist->GetName());
        TVar->WriteObject(pTref1_Mult_Hist, pTref1_Mult_Hist->GetName());
        TVar->WriteObject(pTref2_Mult_Hist, pTref2_Mult_Hist->GetName());
        TVar->WriteObject(pDCREF1_Mult_Hist, pDCREF1_Mult_Hist->GetName());
        TVar->WriteObject(pDCREF2_Mult_Hist, pDCREF2_Mult_Hist->GetName());
        TVar->WriteObject(pDCREF3_Mult_Hist, pDCREF3_Mult_Hist->GetName()); 
        TVar->WriteObject(pDCREF4_Mult_Hist, pDCREF4_Mult_Hist->GetName()); 
        TVar->WriteObject(pDCREF5_Mult_Hist, pDCREF5_Mult_Hist->GetName()); 
        TVar->WriteObject(pDCREF6_Mult_Hist, pDCREF6_Mult_Hist->GetName()); 
        TVar->WriteObject(pDCREF7_Mult_Hist, pDCREF7_Mult_Hist->GetName()); 
        TVar->WriteObject(pDCREF8_Mult_Hist, pDCREF8_Mult_Hist->GetName()); 
        TVar->WriteObject(pDCREF9_Mult_Hist, pDCREF9_Mult_Hist->GetName()); 
        TVar->WriteObject(pDCREF10_Mult_Hist, pDCREF10_Mult_Hist->GetName());
        

        //dc variables
        for(Int_t i = 0; i < dcPlanes; i++)
        {
                hDC->WriteObject(hdcrawtdc_Hist[i], hdcrawtdc_Hist[i]->GetName());
                pDC->WriteObject(pdcrawtdc_Hist[i], pdcrawtdc_Hist[i]->GetName());
                
                hDC->WriteObject(hdcnhit_Hist[i], hdcnhit_Hist[i]->GetName());
                pDC->WriteObject(pdcnhit_Hist[i], pdcnhit_Hist[i]->GetName());
        }

        // hodoscope variables
        for(Int_t iPlane = 0; iPlane < HodPlanes; iPlane++)
        {
                for(Int_t iSide = 0; iSide < HodSides; iSide++)
                {
                        for(Int_t iPmt = 0; iPmt < hHodbars[iPlane]; iPmt++)
                        {
                                hHodo->WriteObject(hHodAdcTdcDiffTime_Hist[iPlane][iSide][iPmt], hHodAdcTdcDiffTime_Hist[iPlane][iSide][iPmt]->GetName());
                                hHodo->WriteObject(hHodAdcMult_Hist[iPlane][iSide][iPmt], hHodAdcMult_Hist[iPlane][iSide][iPmt]->GetName());
            }
                        for(Int_t iPmt = 0; iPmt < pHodbars[iPlane]; iPmt++)
                        {
                                pHodo->WriteObject(pHodAdcTdcDiffTime_Hist[iPlane][iSide][iPmt], pHodAdcTdcDiffTime_Hist[iPlane][iSide][iPmt]->GetName());
                                pHodo->WriteObject(pHodAdcMult_Hist[iPlane][iSide][iPmt], pHodAdcMult_Hist[iPlane][iSide][iPmt]->GetName());
            }
                }
        }
 
        for(Int_t iPlane = 0; iPlane < HodPlanes; iPlane++)
        {
                for(Int_t iSide = 0; iSide < HodSides1; iSide++)
        {
                        for(Int_t iPmt = 0; iPmt < hHodbars[iPlane]; iPmt++)
                        {
                                hHodo->WriteObject(hHodAdcPulseTimeRaw_Hist[iPlane][iSide][iPmt], hHodAdcPulseTimeRaw_Hist[iPlane][iSide][iPmt]->GetName());
                hHodo->WriteObject(hHodTdcTimeRaw_Hist[iPlane][iSide][iPmt], hHodTdcTimeRaw_Hist[iPlane][iSide][iPmt]->GetName());
                        }
                for(Int_t iPmt = 0; iPmt < pHodbars[iPlane]; iPmt++)
                {
                                pHodo->WriteObject(pHodAdcPulseTimeRaw_Hist[iPlane][iSide][iPmt], pHodAdcPulseTimeRaw_Hist[iPlane][iSide][iPmt]->GetName());
                pHodo->WriteObject(pHodTdcTimeRaw_Hist[iPlane][iSide][iPmt], pHodTdcTimeRaw_Hist[iPlane][iSide][iPmt]->GetName());

                        }
                }
        }

        //Gas cherenkovs
        //hms
        for(Int_t iPmt = 0; iPmt < hcerNpmts; iPmt++)
        {
                hCer->WriteObject(cerAdcTdcDiffTime_Hist[iPmt], cerAdcTdcDiffTime_Hist[iPmt]->GetName());
                hCer->WriteObject(cerAdcMult_Hist[iPmt], cerAdcMult_Hist[iPmt]->GetName());
        }
        
        //shms
        for(Int_t iPmt = 0; iPmt < pcerNpmts; iPmt++)
        {
                pHgcer->WriteObject(hgcerAdcTdcDiffTime_Hist[iPmt], hgcerAdcTdcDiffTime_Hist[iPmt]->GetName());
                pNgcer->WriteObject(ngcerAdcTdcDiffTime_Hist[iPmt], ngcerAdcTdcDiffTime_Hist[iPmt]->GetName());
                pHgcer->WriteObject(hgcerAdcMult_Hist[iPmt], hgcerAdcMult_Hist[iPmt]->GetName());
                pNgcer->WriteObject(ngcerAdcMult_Hist[iPmt], ngcerAdcMult_Hist[iPmt]->GetName());
        }
        
        //aerogel 
        for(Int_t iSide = 0; iSide < aeroSides; iSide++)
        {
                for(Int_t iPmt = 0; iPmt < aeroNumPmts; iPmt++)
                {
                        pAero->WriteObject(aeroAdcTdcDiffTime_Hist[iSide][iPmt], aeroAdcTdcDiffTime_Hist[iSide][iPmt]->GetName());
                        pAero->WriteObject(aeroAdcMult_Hist[iSide][iPmt], aeroAdcMult_Hist[iSide][iPmt]->GetName());
                }
        }

        //Calorimeters
        //hms
        for(Int_t iPlane = 0; iPlane < hcalPlanes; iPlane++)
        {
                for(Int_t iSide = 0; iSide < calSides; iSide++)
                {
                        for(Int_t iPmt = 0; iPmt < hcalNumPmts[iPlane]; iPmt++)
                        {
                                hCal->WriteObject(hcalAdcTdcDiffTime_Hist[iPlane][iSide][iPmt], hcalAdcTdcDiffTime_Hist[iPlane][iSide][iPmt]->GetName());
                                hCal->WriteObject(hcalAdcMult_Hist[iPlane][iSide][iPmt], hcalAdcMult_Hist[iPlane][iSide][iPmt]->GetName());
                        }
                }
        }
        
        //shms calorimeter
        for(Int_t iSide = 0; iSide < calSides; iSide++)
        {
                for(Int_t iPmt = 0; iPmt < pcalPrNumPmts; iPmt++)
                {
                        pCal->WriteObject(pcalprAdcTdcDiffTime_Hist[iSide][iPmt], pcalprAdcTdcDiffTime_Hist[iSide][iPmt]->GetName());
                        pCal->WriteObject(pcalprAdcMult_Hist[iSide][iPmt], pcalprAdcMult_Hist[iSide][iPmt]->GetName());
                } 
        }        
        
        for(Int_t iPmt = 0; iPmt < pcalFlyNumPmts; iPmt++)
        {
                pCal->WriteObject(pcalflyAdcTdcDiffTime_Hist[iPmt], pcalflyAdcTdcDiffTime_Hist[iPmt]->GetName());
                pCal->WriteObject(pcalflyAdcMult_Hist[iPmt], pcalflyAdcMult_Hist[iPmt]->GetName());
        }
        
        outFile->Close();
    }
    cout << "Finished saving output!\n---- End ----\n"; 
    return;
}




