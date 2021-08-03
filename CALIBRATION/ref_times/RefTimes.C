/*
    refTimes.C
    Author: Nathan Heinrich
    
    This is a script for creating referance time time plots, both the overall and detector specific.
    The intent is for an expert to consault the plots while manually setting the referance times.
    This script also automatically applies a multiplicity cut for each variable (where applicable) which is simply be hard coded, this should be fine though.
    Also this script assumes running with coin daq, for use in singles daq some alteration is required. 
    
*/

/*******************************/
//Detector specific Constants

//Drift Chambers
static const Int_t dcPlanes                     = 12;
static const TString dcPlaneNames[dcPlanes]     = {"1u1", "1u2", "1x1", "1x2", "1v1", "1v2", "2u1", "2u2", "2x1", "2x2", "2v1", "2v2"};

//hodoscopes
static const Int_t HodPlanes                    = 4;
static const TString HodPlaneNames[HodPlanes]   = {"1x", "1y", "2x", "2y"};
static const Int_t HodSides                     = 2;
static const TString HodSideNames[HodSides]     = {"pos", "neg"};
static const Int_t MaxHodBars                   = 21;
static const UInt_t hHodbars[HodPlanes]         = {16, 10, 16, 10};
static const UInt_t pHodbars[HodPlanes]         = {13, 13, 14, 21};

//Gas Cherenkovs
static const Int_t cerNpmts                     = 4;

//aerogel
static const Int_t aeroNumPmts                  = 14;
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
static const Int_t hcalNumPmts[hcalPlanes]      = {26, 26, 13, 13};

/******  Cuts n' Stuff   ******/
static const TString DaqName = "coin";
Bool_t IsNgcerIn = false;

//***** Branch variables ******/

//ref time variables
Int_t hFADC_TREF_ROC1;
Int_t hTref1, hTref2;
Int_t hDCREF1, hDCREF2, hDCREF3, hDCREF4, hDCREF5; //hDCRef5 not avaiable for runs prior to July 2018
Int_t hFADC_TREF_ROC1_Mult;
Int_t hTref1_Mult, hTref2_Mult;
Int_t hDCREF1_Mult, hDCREF2_Mult, hDCREF3_Mult, hDCREF4_Mult, hDCREF5_Mult;

Int_t pFADC_TREF_ROC2;
Int_t pTref1, pTref2;
Int_t pDCREF1, pDCREF2, pDCREF3, pDCREF4, pDCREF5, pDCREF6, pDCREF7, pDCREF8, pDCREF9, pDCREF10;
Int_t pFADC_TREF_ROC2_Mult;
Int_t pTref1_Mult, pTref2_Mult;
Int_t pDCREF1_Mult, pDCREF2_Mult, pDCREF3_Mult, pDCREF4_Mult, pDCREF5_Mult, pDCREF6_Mult, pDCREF7_Mult, pDCREF8_Mult, pDCREF9_Mult, pDCREF10_Mult;

//dc variables
Float_t hdcrawtdc[dcPlanes],    pdcrawtdc[dcPlanes];
Int_t   hdcnhit[dcPlanes],      pdcnhit[dcPlanes];

// hodoscope variables, 
Float_t hHodAdcTdcDiffTime[HodPlanes][HodSides];
Int_t   hHodAdcMult[HodPlanes][HodSides];

Float_t pHodAdcTdcDiffTime[HodPlanes][HodSides];
Int_t   pHodAdcMult[HodPlanes][HodSides];

//Gas cherenkovs
//hms
Float_t cerAdcTdcDiffTime;
Int_t   cerAdcMult;

//shms
Float_t hgcerAdcTdcDiffTime, ngcerAdcTdcDiffTime;
Int_t   hgcerAdcMult,        ngcerAdcMult;

//aerogel 
Float_t aeroAdcTdcDiffTime[aeroSides];
Int_t   aeroAdcMult[aeroSides];

//Calorimeters
//hms
Float_t hcalAdcTdcDiffTime[hcalPlanes][calSides]; 
Int_t   hcalAdcMult[hcalPlanes][calSides];

//shms
Float_t pcalprAdcTdcDiffTime[calSides];
Int_t   pcalprAdcMult[calSides];

Float_t pcalflyAdcTdcDiffTime;
Int_t   pcalflyAdcMult;

/*********** Histograms *************/
TH1I    *hFADC_TREF_ROC1_Hist;
TH1I    *hTref1_Hist, *hTref2_Hist;
TH1I    *hDCREF1_Hist, *hDCREF2_Hist, *hDCREF3_Hist, *hDCREF4_Hist, *hDCREF5_Hist; //hDCRef5 not avaiable for runs prior to July 2018
TH1I    *hFADC_TREF_ROC1_Mult_Hist;
TH1I    *hTref1_Mult_Hist, *hTref2_Mult_Hist;
TH1I    *hDCREF1_Mult_Hist, *hDCREF2_Mult_Hist, *hDCREF3_Mult_Hist, *hDCREF4_Mult_Hist, *hDCREF5_Mult_Hist;

TH1I    *pFADC_TREF_ROC2_Hist;
TH1I    *pTref1_Hist, *pTref2_Hist;
TH1I    *pDCREF1_Hist, *pDCREF2_Hist, *pDCREF3_Hist, *pDCREF4_Hist, *pDCREF5_Hist, *pDCREF6_Hist, *pDCREF7_Hist, *pDCREF8_Hist, *pDCREF9_Hist, *pDCREF10_Hist;
TH1I    *pFADC_TREF_ROC2_Mult_Hist;
TH1I    *pTref1_Mult_Hist, *pTref2_Mult_Hist;
TH1I    *pDCREF1_Mult_Hist, *pDCREF2_Mult_Hist, *pDCREF3_Mult_Hist, *pDCREF4_Mult_Hist, *pDCREF5_Mult_Hist, *pDCREF6_Mult_Hist, *pDCREF7_Mult_Hist, *pDCREF8_Mult_Hist, *pDCREF9_Mult_Hist, *pDCREF10_Mult_Hist;

//dc variables
TH1F    *hdcrawtdc_Hist[dcPlanes],    *pdcrawtdc_Hist[dcPlanes];
TH1I    *hdcnhit_Hist[dcPlanes],      *pdcnhit_Hist[dcPlanes]

// hodoscope variables
TH1F    *hHodAdcTdcDiffTime_Hist[HodPlanes][HodSides][MaxHodBars];
TH1I    *hHodAdcMult_Hist[HodPlanes][HodSides][MaxHodBars];

TH1F    *pHodAdcTdcDiffTime_Hist[HodPlanes][HodSides][MaxHodBars];
TH1I    *pHodAdcMult_Hist[HodPlanes][HodSides][MaxHodBars];

//Gas cherenkovs
//hms
TH1F    *cerAdcTdcDiffTime_Hist[cerNpmts];
TH1I    *cerAdcMult_Hist[cerNpmts];

//shms
TH1F    *hgcerAdcTdcDiffTime_Hist[cerNpmts], *ngcerAdcTdcDiffTime_Hist[cerNpmts];
TH1I    *hgcerAdcMult_Hist[cerNpmts],        *ngcerAdcMult_Hist[cerNpmts];

//aerogel 
TH1F    *aeroAdcTdcDiffTime_Hist[aeroSides][aeroNumPmts];
TH1I    *aeroAdcMult_Hist[aeroSides][aeroNumPmts];

//Calorimeters
//hms
TH1F    *hcalAdcTdcDiffTime_Hist[4][calSides][hcalNumPmts[0]]; //do this b/c plane one also has the max # of pmts
TH1I    *hcalAdcMult_Hist[hcalPlanes][calSides][hcalNumPmts[0]];

//shms
TH1F    *pcalprAdcTdcDiffTime_Hist[calSides][pcalPrNumPmts];
TH1I    *pcalprAdcMult_Hist[calSides][pcalPrNumPmts];

TH1F    *pcalflyAdcTdcDiffTime_Hist[pcalFlyNumPmts];
TH1I    *pcalflyAdcMult_Hist[pcalFlyNumPmts];

// sets the addresses of all the variables that are to be used and/or plotted
void setBranchAddresses(TTree* DataTree)
{
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
        DataTree->SetBranchAddress(Form("H.dc.%s.rawtdc", dcPlanesNames[i]), &hdcrawtsc[i]);
        DataTree->SetBranchAddress(Form("H.dc.%s.nhit", dcPlanesNames[i]), &hdcnhit[i]);
        DataTree->SetBranchAddress(Form("P.dc.%s.rawtdc", dcPlanesNames[i]), &pdcrawtsc[i]);
        DataTree->SetBranchAddress(Form("P.dc.%s.nhit", dcPlanesNames[i]), &pdcnhit[i]);
    }
    
    //assign branches to hod variables
    for(Int_t iPlane = 0; iPlane < HodPlanes; iPlane++)
    {
        for(Int_t iSide = 0; iSide < HodSides; iSide++)
        {
            DataTree->SetBranchAddress(Form("H.hod.%s.Good%sAdcTdcDiffTime", HodPlaneNames[iPlane], HodSideNames[iSide]), &hHodAdcTdsDiffTime[iPlane][iSide]);
            DataTree->SetBranchAddress(Form("H.hod.%s.Good%sAdcMult", HodPlaneNames[iPlane], HodSideNames[iSide]), &hHodAdcMult[iPlane][iSide]);
            
            DataTree->SetBranchAddress(Form("H.hod.%s.Good%sAdcTdcDiffTime", HodPlaneNames[iPlane], HodSideNames[iSide]), &pHodAdcTdsDiffTime[iPlane][iSide]);
            DataTree->SetBranchAddress(Form("H.hod.%s.Good%sAdcMult", HodPlaneNames[iPlane], HodSideNames[iSide]), &pHodAdcMult[iPlane][iSide]);
        }
    }
    
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
        DataTree->SetBranchAddress(Form("P.aero.good%sAdcTdcDiffTime", aeroSideNames[iSide]), &aeroAdcTdcDiffTime[iSide]);
        DataTree->SetBranchAddress(Form("P.aero.good%sAdcMult", aeroSideNames[iSide]), &aeroAdcMult[iSide]);
    }
    
    //hms calorimeter
    for(Int_t iPlane = 0; iPlane < hcalPlanes; iPlane++)
    {
        for(Int_t iSide = 0; iSide < calSides; iSide++)
        {
            DataTree->SetBranchAddress(Form("H.cal.%s.Good%sAdcTdcDiffTime", calPlaneNames[iPlane], calSideNames[iSide]), &hcalAdcTdcDiffTime[iPlane][iSide]);
            DataTree->SetBranchAddress(Form("H.cal.%s.Good%sAdcMult", calPlaneNames[iPlane], calSideNames[iSide]), &hcalAdcMult[iPlane][iSide]);
        }
    }
    
    //shms calorimeter
    for(Int_t iSide = 0; iSide < calSides; iSide++)
    {
        DataTree->SetBranchAddress(Form("P.cal.pr.Good%sAdcTdcDiffTime", calSideNames[iSide]), &pcalprAdcMult[iSide]);
        DataTree->SetBranchAddress(Form("P.cal.pr.Good%sAdcMult", calSideNames[iSide]), &pcalprAdcMult[iSide]);
    }
    DataTree->SetBranchAddress("P.cal.fly.GoodAdcTdcDiffTime", &pcalprAdcMult[iSide]);
    DataTree->SetBranchAddress("P.cal.fly.GoodAdcMult", &pcalprAdcMult[iSide]);

    return;
}

//function for declaring all of the Histograms that are to be filed in the proceding script
void makeHistos ()
{
    hFADC_TREF_ROC1_Hist = new TH1I(Form("T.%s.hFADC_TREF_ROC1_adcPulseTimeRaw", DaqName.Data()), Form("T.%s.hFADC_TREF_ROC1_adcPulseTimeRaw", DaqName.Data()), 10000, 1.0);
    hTref1_Hist = new TH1I(Form("T.%s.hT1_tdcTimeRaw", DaqName.Data()), Form("T.%s.hT1_tdcTimeRaw", DaqName.Data()), 10000, 1.0);
    hTref2_Hist = new TH1I(Form("T.%s.hT2_tdcTimeRaw", DaqName.Data()), Form("T.%s.hT2_tdcTimeRaw", DaqName.Data()), 10000, 1.0);
    hDCREF1_Hist = new TH1I(Form("T.%s.hDCREF1_tdcTimeRaw", DaqName.Data()), Form("T.%s.hDCREF1_tdcTimeRaw", DaqName.Data()), 10000, 1.0);
    hDCREF2_Hist = new TH1I(Form("T.%s.hDCREF2_tdcTimeRaw", DaqName.Data()), Form("T.%s.hDCREF2_tdcTimeRaw", DaqName.Data()), 10000, 1.0);
    hDCREF3_Hist = new TH1I(Form("T.%s.hDCREF3_tdcTimeRaw", DaqName.Data()), Form("T.%s.hDCREF3_tdcTimeRaw", DaqName.Data()), 10000, 1.0);
    hDCREF4_Hist = new TH1I(Form("T.%s.hDCREF4_tdcTimeRaw", DaqName.Data()), Form("T.%s.hDCREF4_tdcTimeRaw", DaqName.Data()), 10000, 1.0);
    hDCREF5_Hist = new TH1I(Form("T.%s.hDCREF5_tdcTimeRaw", DaqName.Data()), Form("T.%s.hDCREF5_tdcTimeRaw", DaqName.Data()), 10000, 1.0);
    
    hFADC_TREF_ROC1_Mult_Hist = new TH1I(Form("T.%s.hFADC_TREF_ROC1_adcMultiplicity", DaqName.Data()), Form("T.%s.hFADC_TREF_ROC1_adcMultiplicity", DaqName.Data()), 10, 1.0);
    hTref1_Mult_Hist = new TH1I(Form("T.%s.hT1_tdcMultiplicity", DaqName.Data()), Form("T.%s.hT1_tdcMultiplicity", DaqName.Data()), 10, 1.0);
    hTref2_Mult_Hist = new TH1I(Form("T.%s.hT2_tdcMultiplicity", DaqName.Data()), Form("T.%s.hT2_tdcMultiplicity", DaqName.Data()), 10, 1.0);
    hDCREF1_Mult_Hist = new TH1I(Form("T.%s.hDCREF1_tdcMultiplicity", DaqName.Data()), Form("T.%s.hDCREF1_tdcMultiplicity", DaqName.Data()), 10, 1.0);
    hDCREF2_Mult_Hist = new TH1I(Form("T.%s.hDCREF2_tdcMultiplicity", DaqName.Data()), Form("T.%s.hDCREF2_tdcMultiplicity", DaqName.Data()), 10, 1.0);
    hDCREF3_Mult_Hist = new TH1I(Form("T.%s.hDCREF3_tdcMultiplicity", DaqName.Data()), Form("T.%s.hDCREF3_tdcMultiplicity", DaqName.Data()), 10, 1.0);
    hDCREF4_Mult_Hist = new TH1I(Form("T.%s.hDCREF4_tdcMultiplicity", DaqName.Data()), Form("T.%s.hDCREF4_tdcMultiplicity", DaqName.Data()), 10, 1.0);
    hDCREF5_Mult_Hist = new TH1I(Form("T.%s.hDCREF5_tdcMultiplicity", DaqName.Data()), Form("T.%s.hDCREF5_tdcMultiplicity", DaqName.Data()), 10, 1.0);

    pFADC_TREF_ROC2_Hist = new TH1I(Form("T.%s.pFADC_TREF_ROC2_adcPulseTimeRaw", DaqName.Data()), Form("T.%s.pFADC_TREF_ROC2_adcPulseTimeRaw", DaqName.Data()), 10000, 1.0);
    pTref1_Hist = new TH1I(Form("T.%s.pT1_tdcTimeRaw", DaqName.Data()), Form("T.%s.pT1_tdcTimeRaw", DaqName.Data()), 10000, 1.0);
    pTref2_Hist = new TH1I(Form("T.%s.pT2_tdcTimeRaw", DaqName.Data()), Form("T.%s.pT2_tdcTimeRaw", DaqName.Data()), 10000, 1.0);
    pDCREF1_Hist = new TH1I(Form("T.%s.pDCREF1_tdcTimeRaw", DaqName.Data()), Form("T.%s.pDCREF1_tdcTimeRaw", DaqName.Data()), 10000, 1.0);
    pDCREF2_Hist = new TH1I(Form("T.%s.pDCREF2_tdcTimeRaw", DaqName.Data()), Form("T.%s.pDCREF2_tdcTimeRaw", DaqName.Data()), 10000, 1.0);
    pDCREF3_Hist = new TH1I(Form("T.%s.pDCREF3_tdcTimeRaw", DaqName.Data()), Form("T.%s.pDCREF3_tdcTimeRaw", DaqName.Data()), 10000, 1.0);
    pDCREF4_Hist = new TH1I(Form("T.%s.pDCREF4_tdcTimeRaw", DaqName.Data()), Form("T.%s.pDCREF4_tdcTimeRaw", DaqName.Data()), 10000, 1.0);
    pDCREF5_Hist = new TH1I(Form("T.%s.pDCREF5_tdcTimeRaw", DaqName.Data()), Form("T.%s.pDCREF5_tdcTimeRaw", DaqName.Data()), 10000, 1.0);
    pDCREF6_Hist = new TH1I(Form("T.%s.pDCREF6_tdcTimeRaw", DaqName.Data()), Form("T.%s.pDCREF6_tdcTimeRaw", DaqName.Data()), 10000, 1.0);
    pDCREF7_Hist = new TH1I(Form("T.%s.pDCREF7_tdcTimeRaw", DaqName.Data()), Form("T.%s.pDCREF7_tdcTimeRaw", DaqName.Data()), 10000, 1.0);
    pDCREF8_Hist = new TH1I(Form("T.%s.pDCREF8_tdcTimeRaw", DaqName.Data()), Form("T.%s.pDCREF8_tdcTimeRaw", DaqName.Data()), 10000, 1.0);
    pDCREF9_Hist = new TH1I(Form("T.%s.pDCREF9_tdcTimeRaw", DaqName.Data()), Form("T.%s.pDCREF9_tdcTimeRaw", DaqName.Data()), 10000, 1.0);
    pDCREF10_Hist = new TH1I(Form("T.%s.pDCREF10_tdcTimeRaw", DaqName.Data()), Form("T.%s.pDCREF10_tdcTimeRaw", DaqName.Data()), 10000, 1.0);
    
    pFADC_TREF_ROC2_Mult_Hist = new TH1I(Form("T.%s.pFADC_TREF_ROC2_adcMultiplicity", DaqName.Data()), Form("T.%s.pFADC_TREF_ROC2_adcMultiplicity", DaqName.Data()), 10, 1.0);
    pTref1_Mult_Hist = new TH1I(Form("T.%s.pT1_tdcMultiplicity", DaqName.Data()), Form("T.%s.pT1_tdcMultiplicity", DaqName.Data()), 10, 1.0);
    pTref2_Mult_Hist = new TH1I(Form("T.%s.pT2_tdcMultiplicity", DaqName.Data()), Form("T.%s.pT2_tdcMultiplicity", DaqName.Data()), 10, 1.0);
    pDCREF1_Mult_Hist = new TH1I(Form("T.%s.pDCREF1_tdcMultiplicity", DaqName.Data()), Form("T.%s.pDCREF1_tdcMultiplicity", DaqName.Data()), 10, 1.0);
    pDCREF2_Mult_Hist = new TH1I(Form("T.%s.pDCREF2_tdcMultiplicity", DaqName.Data()), Form("T.%s.pDCREF2_tdcMultiplicity", DaqName.Data()), 10, 1.0);
    pDCREF3_Mult_Hist = new TH1I(Form("T.%s.pDCREF3_tdcMultiplicity", DaqName.Data()), Form("T.%s.pDCREF3_tdcMultiplicity", DaqName.Data()), 10, 1.0);
    pDCREF4_Mult_Hist = new TH1I(Form("T.%s.pDCREF4_tdcMultiplicity", DaqName.Data()), Form("T.%s.pDCREF4_tdcMultiplicity", DaqName.Data()), 10, 1.0);
    pDCREF5_Mult_Hist = new TH1I(Form("T.%s.pDCREF5_tdcMultiplicity", DaqName.Data()), Form("T.%s.pDCREF5_tdcMultiplicity", DaqName.Data()), 10, 1.0);
    pDCREF6_Mult_Hist = new TH1I(Form("T.%s.pDCREF6_tdcMultiplicity", DaqName.Data()), Form("T.%s.pDCREF6_tdcMultiplicity", DaqName.Data()), 10, 1.0);
    pDCREF7_Mult_Hist = new TH1I(Form("T.%s.pDCREF7_tdcMultiplicity", DaqName.Data()), Form("T.%s.pDCREF7_tdcMultiplicity", DaqName.Data()), 10, 1.0);
    pDCREF8_Mult_Hist = new TH1I(Form("T.%s.pDCREF8_tdcMultiplicity", DaqName.Data()), Form("T.%s.pDCREF8_tdcMultiplicity", DaqName.Data()), 10, 1.0);
    pDCREF9_Mult_Hist = new TH1I(Form("T.%s.pDCREF9_tdcMultiplicity", DaqName.Data()), Form("T.%s.pDCREF9_tdcMultiplicity", DaqName.Data()), 10, 1.0);
    pDCREF10_Mult_Hist = new TH1I(Form("T.%s.pDCREF10_tdcMultiplicity", DaqName.Data()), Form("T.%s.pDCREF10_tdcMultiplicity", DaqName.Data()), 10, 1.0);

    //dc variables
    for(Int_t i = 0; i < dcPlanes; i++)
    {
        hdcrawtdc_Hist[i] = new TH1F(Form("H.dc.%s.rawtdc", dcPlanesNames[i]), Form("H.dc.%s.rawtdc", dcPlanesNames[i]), 4000, 1.0);
        pdcrawtdc_Hist[i] = new TH1F(Form("P.dc.%s.rawtdc", dcPlanesNames[i]), Form("P.dc.%s.rawtdc", dcPlanesNames[i]), 4000, 1.0);
        hdcnhit_Hist[i] = new TH1I(Form("H.dc.%s.nhit", dcPlanesNames[i]), Form("H.dc.%s.nhit", dcPlanesNames[i]), 50, 1.0);
        pdcnhit_Hist[i] = new TH1I(Form("P.dc.%s.nhit", dcPlanesNames[i]), Form("P.dc.%s.nhit", dcPlanesNames[i]), 50, 1.0);
    }

    // hodoscope variables
    for(Int_t iPlane = 0; iPlane < HodPlanes; iPlane++)
    {
        for(Int_t iSide = 0; iSide < HodSides; iSide++)
        {
            for(Int_t iPmt = 0; iPmt < hHodBars[iPlane]; iPmt++)
            {
                hHodAdcTdcDiffTime_Hist[iPlane][iSide][iPmt] = new TH1F(Form("H.hod.%s.Good%sAdcTdcDiffTime_pmt%d", HodPlaneNames[iPlane], HodSideNames[iSide], iPmt+1), 10000, 1.0);
                hHodAdcMult_Hist[iPlane][iSide][iPmt] = new TH1I(Form("H.hod.%s.Good%sAdcMult_pmt%d", HodPlaneNames[iPlane], HodSideNames[iSide], iPmt+1), 10, 1.0);
            }
            for(Int_t iPmt = 0; iPmt < pHodBars[iPlane]; iPmt++)
            {
                pHodAdcTdcDiffTime_Hist[iPlane][iSide][iPmt] = new TH1F(Form("P.hod.%s.Good%sAdcTdcDiffTime_pmt%d", HodPlaneNames[iPlane], HodSideNames[iSide], iPmt+1), 10000, 1.0);
                pHodAdcMult_Hist[iPlane][iSide][iPmt] = new TH1I(Form("P.hod.%s.Good%sAdcMult_pmt%d", HodPlaneNames[iPlane], HodSideNames[iSide], iPmt+1), 10, 1.0);
            }
        }
    }
    
    //Gas cherenkovs
    //hms
    for(Int_t iPmt = 0; iPmt < cerNpmts; iPmt++)
    {
        cerAdcTdcDiffTime_Hist[iPmt] = new TH1F(Form("H.cer.goodAdcTdcDiffTime_Pmt%d", iPmt+1), Form("H.cer.goodAdcTdcDiffTime_Pmt%d", iPmt+1), 5000, 1.0);
        cerAdcMult_Hist[iPmt] = new TH1I(Form("H.cer.goodAdcMult_Pmt%d", iPmt+1), Form("H.cer.goodAdcMult_Pmt%d", iPmt+1), 10, 1.0);
    }
    
    //shms
    for(Int_t iPmt = 0; iPmt < cerNpmts; iPmt++)
    {
        hgcerAdcTdcDiffTime_Hist[iPmt] = new TH1F(Form("P.hgcer.goodAdcTdcDiffTime_Pmt%d", iPmt+1), Form("H.cer.goodAdcTdcDiffTime_Pmt%d", iPmt+1), 5000, 1.0);
        ngcerAdcTdcDiffTime_Hist[iPmt] = new TH1F(Form("P.ngcer.goodAdcTdcDiffTime_Pmt%d", iPmt+1), Form("H.cer.goodAdcTdcDiffTime_Pmt%d", iPmt+1), 5000, 1.0);
        hgcerAdcMult_Hist[iPmt] = new TH1I(Form("P.hgcer.goodAdcMult_Pmt%d", iPmt+1), Form("H.cer.goodAdcMult_Pmt%d", iPmt+1), 10, 1.0);
        ngcerAdcMult_Hist[iPmt] = new TH1I(Form("P.ngcer.goodAdcMult_Pmt%d", iPmt+1), Form("H.cer.goodAdcMult_Pmt%d", iPmt+1), 10, 1.0);
    }
    
    //aerogel 
    for(Int_t iSide = 0; iSide < aeroSides; iSide++)
    {
        for(Int_t iPmt = 0; iPmt < aeroNumPmts; iPmt++)
        {
            aeroAdcTdcDiffTime_Hist[iSide][iPmt] = new TH1F(Form("P.aero.good%sAdcTdcDiffTime_Pmt%d", aeroSideNames[iSide], iPmt+1), Form("P.aero.good%sAdcTdcDiffTime_Pmt%d", aeroSideNames[iSide], iPmt+1), 5000, 1.0);
            aeroAdcMult_Hist[iSide][iPmt] = new TH1I(Form("P.aero.good%sAdcMult_Pmt%d", aeroSideNames[iSide], iPmt+1), Form("P.aero.good%sAdcMult_Pmt%d", aeroSideNames[iSide], iPmt+1), 10, 1.0);
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
                hcalAdcTdcDiffTime_Hist[iPlane][iSide][iPmt] = new TH1F(Form("H.cal.%s.Good%sAdcTdcDiffTime_Pmt%d", calPlaneNames[iPlane], calSideNames[iSide], iPmt+1),Form("H.cal.%s.Good%sAdcTdcDiffTime_Pmt%d", calPlaneNames[iPlane], calSideNames[iSide], iPmt+1), 5000, 1.0);
                hcalAdcMult_Hist[iPlane][iSide][iPmt] = new TH1I(Form("H.cal.%s.Good%sAdcMult_Pmt%d", calPlaneNames[iPlane], calSideNames[iSide], iPmt+1),Form("H.cal.%s.Good%sAdcMult_Pmt%d", calPlaneNames[iPlane], calSideNames[iSide], iPmt+1), 10, 1.0);
            }
        }
    }
    
    //shms calorimeter
    for(Int_t iSide = 0; iSide < calSides; iSide++)
    {
        for(Int_t iPmt = 0; iPmt < pcalPrNumPmts; iPmt++)
        {
            pcalprAdcTdcDiffTime_Hist[iSide][iPmt] = new TH1F(Form("P.cal.pr.Good%sAdcTdcDiffTime_pmt%d", calSideNames[iSide], iPmt+1), Form("P.cal.pr.Good%sAdcTdcDiffTime_pmt%d", calSideNames[iSide], iPmt+1), 5000, 1.0);
            pcalprAdcMult_Hist[iSide][iPmt] = new TH1I(Form("P.cal.pr.Good%sAdcMult_pmt%d", calSideNames[iSide], iPmt+1), Form("P.cal.pr.Good%sAdcMult_pmt%d", calSideNames[iSide], iPmt+1), 10, 1.0);
        }
    }    
    
    for(Int_t iPmt = 0; iPmt < pcalFlyNumPmts; iPmt++)
    {
        pcalflyAdcTdcDiffTime_Hist[iPmt] = new TH1F((Form("P.cal.fly.GoodAdcTdcDiffTime_pmt%d", iPmt+1),Form("P.cal.fly.GoodAdcTdcDiffTime_pmt%d", iPmt+1), 5000, 1.0);
        pcalflyAdcMult_Hist[iPmt] = new TH1F((Form("P.cal.fly.GoodAdcMult_pmt%d", iPmt+1),Form("P.cal.fly.GoodAdcMult_pmt%d", iPmt+1), 10, 1.0);
    }
    
    return;
}

// input is the path from ref_times directory to rootfile and the run number that your using
void refTimes( TString rootFileName, Int_t RunNumber)
{
    
    //get root file
    TFile* inFile = new TFile(rootFileName, "READ");
    
    //get tree from root file
    TTree *DataTree = dynamic_cast <TTree*> (inFile->Get("T"));
    
    setBranchAddresses(DataTree);
    
    //make histograms
    makeHistos();
    
    //fill histos and apply cuts
    
    //save plots
    
    return;
}




