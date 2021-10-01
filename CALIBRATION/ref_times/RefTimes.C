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
static const TString HodSideNames[HodSides]     = {"Pos", "Neg"};

static const Int_t HodSides1                    = 2;
static const TString HodSideNames1[HodSides1]   = {"pos", "neg"};

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
static const Int_t hcalNumPmtsMax               = 26;

/******  Cuts n' Stuff   ******/
static const TString DaqName = "coin";
Bool_t IsNgcerIn = false;

//***** Branch variables ******/

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
Double_t cerAdcTdcDiffTime[cerNpmts];
Double_t   cerAdcMult[cerNpmts];

//shms
Double_t hgcerAdcTdcDiffTime[cerNpmts], ngcerAdcTdcDiffTime[cerNpmts];
Double_t hgcerAdcMult[cerNpmts],        ngcerAdcMult[cerNpmts];

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
TH1D    *cerAdcTdcDiffTime_Hist[cerNpmts];
TH1D    *cerAdcMult_Hist[cerNpmts];

//shms
TH1D    *hgcerAdcTdcDiffTime_Hist[cerNpmts], *ngcerAdcTdcDiffTime_Hist[cerNpmts];
TH1D    *hgcerAdcMult_Hist[cerNpmts],        *ngcerAdcMult_Hist[cerNpmts];

//aerogel 
TH1D    *aeroAdcTdcDiffTime_Hist[aeroSides][aeroNumPmts];
TH1D    *aeroAdcMult_Hist[aeroSides][aeroNumPmts];

//Calorimeters
//hms
TH1D    *hcalAdcTdcDiffTime_Hist[hcalPlanes][calSides][hcalNumPmtsMax]; //do this b/c plane one also has the max # of pmts
TH1D    *hcalAdcMult_Hist[hcalPlanes][calSides][hcalNumPmtsMax];

//shms
TH1D    *pcalprAdcTdcDiffTime_Hist[calSides][pcalPrNumPmts];
TH1D    *pcalprAdcMult_Hist[calSides][pcalPrNumPmts];

TH1D    *pcalflyAdcTdcDiffTime_Hist[pcalFlyNumPmts];
TH1D    *pcalflyAdcMult_Hist[pcalFlyNumPmts];

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
                hHodAdcTdcDiffTime_Hist[iPlane][iSide][iPmt] = new TH1D(Form("H.hod.%s.%sAdcTdcDiffTimeRaw_pmt%d", HodPlaneNames[iPlane].Data(), HodSideNames[iSide].Data(), iPmt+1), Form("H.hod.%s.%sAdcTdcDiffTimeRaw_pmt%d", HodPlaneNames[iPlane].Data(), HodSideNames[iSide].Data(), iPmt+1), 2000, -1000, 1000);
                hHodAdcMult_Hist[iPlane][iSide][iPmt] = new TH1D(Form("H.hod.%s.good%sAdcMult_pmt%d", HodPlaneNames[iPlane].Data(), HodSideNames[iSide].Data(), iPmt+1), Form("H.hod.%s.good%sAdcMult_pmt%d", HodPlaneNames[iPlane].Data(), HodSideNames[iSide].Data(), iPmt+1), 10, 0, 10);
	    }
            for(Int_t iPmt = 0; iPmt < pHodbars[iPlane]; iPmt++)
            {
                pHodAdcTdcDiffTime_Hist[iPlane][iSide][iPmt] = new TH1D(Form("P.hod.%s.%sAdcTdcDiffTimeRaw_pmt%d", HodPlaneNames[iPlane].Data(), HodSideNames[iSide].Data(), iPmt+1), Form("P.hod.%s.%sAdcTdcDiffTimeRaw_pmt%d", HodPlaneNames[iPlane].Data(), HodSideNames[iSide].Data(), iPmt+1),2000, -1000, 1000);
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
                hHodAdcPulseTimeRaw_Hist[iPlane][iSide][iPmt] = new TH1D(Form("H.hod.%s.%sAdcPulseTimeRaw_pmt%d", HodPlaneNames[iPlane].Data(), HodSideNames[iSide].Data(), iPmt+1), Form("H.hod.%s.%sAdcPulseTimeRaw_pmt%d", HodPlaneNames[iPlane].Data(), HodSideNames[iSide].Data(), iPmt+1), 100000, 0, 100000);
                hHodTdcTimeRaw_Hist[iPlane][iSide][iPmt] = new TH1D(Form("H.hod.%s.%sTdcTimeRaw_pmt%d", HodPlaneNames[iPlane].Data(), HodSideNames[iSide].Data(), iPmt+1), Form("H.hod.%s.%sTdcTimeRaw_pmt%d", HodPlaneNames[iPlane].Data(), HodSideNames[iSide].Data(), iPmt+1), 100000, 0, 100000);
            }
	    for(Int_t iPmt = 0; iPmt < pHodbars[iPlane]; iPmt++)
	    {
                pHodAdcPulseTimeRaw_Hist[iPlane][iSide][iPmt] = new TH1D(Form("P.hod.%s.%sAdcPulseTimeRaw_pmt%d", HodPlaneNames[iPlane].Data(), HodSideNames[iSide].Data(), iPmt+1), Form("P.hod.%s.%sAdcPulseTimeRaw_pmt%d", HodPlaneNames[iPlane].Data(), HodSideNames[iSide].Data(), iPmt+1), 100000, 0, 100000);
                pHodTdcTimeRaw_Hist[iPlane][iSide][iPmt] = new TH1D(Form("P.hod.%s.%sTdcTimeRaw_pmt%d", HodPlaneNames[iPlane].Data(), HodSideNames[iSide].Data(), iPmt+1), Form("P.hod.%s.%sTdcTimeRaw_pmt%d", HodPlaneNames[iPlane].Data(), HodSideNames[iSide].Data(), iPmt+1), 100000, 0, 100000);
            }
        }
    }	

    //Gas cherenkovs
    //hms
    for(Int_t iPmt = 0; iPmt < cerNpmts; iPmt++)
    {
        cerAdcTdcDiffTime_Hist[iPmt] = new TH1D(Form("H.cer.goodAdcTdcDiffTime_Pmt%d", iPmt+1), Form("H.cer.goodAdcTdcDiffTime_Pmt%d", iPmt+1), 5000, 0, 5000);
        cerAdcMult_Hist[iPmt] = new TH1D(Form("H.cer.goodAdcMult_Pmt%d", iPmt+1), Form("H.cer.goodAdcMult_Pmt%d", iPmt+1), 10, 0, 10);
    }
    
    //shms
    for(Int_t iPmt = 0; iPmt < cerNpmts; iPmt++)
    {
        hgcerAdcTdcDiffTime_Hist[iPmt] = new TH1D(Form("P.hgcer.goodAdcTdcDiffTime_Pmt%d", iPmt+1), Form("H.cer.goodAdcTdcDiffTime_Pmt%d", iPmt+1), 1500, 0, 1500);
        ngcerAdcTdcDiffTime_Hist[iPmt] = new TH1D(Form("P.ngcer.goodAdcTdcDiffTime_Pmt%d", iPmt+1), Form("H.cer.goodAdcTdcDiffTime_Pmt%d", iPmt+1), 1500, 0, 1500);
        hgcerAdcMult_Hist[iPmt] = new TH1D(Form("P.hgcer.goodAdcMult_Pmt%d", iPmt+1), Form("H.cer.goodAdcMult_Pmt%d", iPmt+1), 10, 0, 10);
        ngcerAdcMult_Hist[iPmt] = new TH1D(Form("P.ngcer.goodAdcMult_Pmt%d", iPmt+1), Form("H.cer.goodAdcMult_Pmt%d", iPmt+1), 10, 0, 10);
    }
    
    //aerogel 
    for(Int_t iSide = 0; iSide < aeroSides; iSide++)
    {
        for(Int_t iPmt = 0; iPmt < aeroNumPmts; iPmt++)
        {
            aeroAdcTdcDiffTime_Hist[iSide][iPmt] = new TH1D(Form("P.aero.good%sAdcTdcDiffTime_Pmt%d", aeroSideNames[iSide].Data(), iPmt+1), Form("P.aero.good%sAdcTdcDiffTime_Pmt%d", aeroSideNames[iSide].Data(), iPmt+1), 100, 0, 100);
            aeroAdcMult_Hist[iSide][iPmt] = new TH1D(Form("P.aero.good%sAdcMult_Pmt%d", aeroSideNames[iSide].Data(), iPmt+1), Form("P.aero.good%sAdcMult_Pmt%d", aeroSideNames[iSide].Data(), iPmt+1), 10, 0, 10);
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
                hcalAdcTdcDiffTime_Hist[iPlane][iSide][iPmt] = new TH1D(Form("H.cal.%s.good%sAdcTdcDiffTime_Pmt%d", hcalPlaneNames[iPlane].Data(), calSideNames[iSide].Data(), iPmt+1),Form("H.cal.%s.good%sAdcTdcDiffTime_Pmt%d", hcalPlaneNames[iPlane].Data(), calSideNames[iSide].Data(), iPmt+1), 100000, 0, 100000);
                hcalAdcMult_Hist[iPlane][iSide][iPmt] = new TH1D(Form("H.cal.%s.good%sAdcMult_Pmt%d", hcalPlaneNames[iPlane].Data(), calSideNames[iSide].Data(), iPmt+1),Form("H.cal.%s.good%sAdcMult_Pmt%d", hcalPlaneNames[iPlane].Data(), calSideNames[iSide].Data(), iPmt+1), 10, 0, 10);
            }
        }
    }
    
    //shms calorimeter
    for(Int_t iSide = 0; iSide < calSides; iSide++)
    {
        for(Int_t iPmt = 0; iPmt < pcalPrNumPmts; iPmt++)
        {
            pcalprAdcTdcDiffTime_Hist[iSide][iPmt] = new TH1D(Form("P.cal.pr.good%sAdcTdcDiffTime_pmt%d", calSideNames[iSide].Data(), iPmt+1), Form("P.cal.pr.good%sAdcTdcDiffTime_pmt%d", calSideNames[iSide].Data(), iPmt+1), 5000, 0, 5000);
            pcalprAdcMult_Hist[iSide][iPmt] = new TH1D(Form("P.cal.pr.good%sAdcMult_pmt%d", calSideNames[iSide].Data(), iPmt+1), Form("P.cal.pr.good%sAdcMult_pmt%d", calSideNames[iSide].Data(), iPmt+1), 1000, 0, 1000);
        }
    }    
    
    for(Int_t iPmt = 0; iPmt < pcalFlyNumPmts; iPmt++)
    {
        pcalflyAdcTdcDiffTime_Hist[iPmt] = new TH1D(Form("P.cal.fly.goodAdcTdcDiffTime_pmt%d", iPmt+1), Form("P.cal.fly.goodAdcTdcDiffTime_pmt%d", iPmt+1), 5000, 0, 5000);
        pcalflyAdcMult_Hist[iPmt] = new TH1D(Form("P.cal.fly.goodAdcMult_pmt%d", iPmt+1),Form("P.cal.fly.goodAdcMult_pmt%d", iPmt+1), 1000, 0, 1000);
    }
    
    return;
}

//function for filling the histograms, this is where any cuts will be implimented
void fillHistos(TTree *DataTree)
{
    Int_t MaxEvents = DataTree->GetEntries();
    cout << "Begining to fill histograms, " << MaxEvents << " events will be processed!\n";
    for(Int_t iEntry = 0; iEntry < MaxEvents; iEntry++)
    {
        DataTree->GetEntry(iEntry);
        
        if( iEntry % 10000 == 0 ) cout << iEntry << "\n"; //status report
        
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
        if (pTref1_Mult > 0)           pTref1_Hist->Fill(pTref1);
        if (pTref2_Mult > 0)           pTref2_Hist->Fill(pTref2);  
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
                    hHodAdcTdcDiffTime_Hist[iPlane][iSide][iPmt]->Fill(hHodTdcTimeRaw[iPlane][iSide][iPmt] - hHodAdcPulseTimeRaw[iPlane][iSide][iPmt]); //changed this to fill raw variables 
                } 
                for(Int_t iPmt = 0; iPmt < pHodbars[iPlane]; iPmt++)
                { 
                    pHodAdcMult_Hist[iPlane][iSide][iPmt]->Fill(pHodAdcMult[iPlane][iSide][iPmt]);
                    pHodAdcTdcDiffTime_Hist[iPlane][iSide][iPmt]->Fill(hHodTdcTimeRaw[iPlane][iSide][iPmt] - hHodAdcPulseTimeRaw[iPlane][iSide][iPmt]); //same here
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
        for(Int_t iPmt = 0; iPmt < cerNpmts; iPmt++)
        { 
            cerAdcMult_Hist[iPmt]->Fill(cerAdcMult[iPmt]);
            //if(cerAdcMult[iPmt] > 0 ) 
	      cerAdcTdcDiffTime_Hist[iPmt]->Fill(cerAdcTdcDiffTime[iPmt]);
        } 
         
        //shms 
        for(Int_t iPmt = 0; iPmt < cerNpmts; iPmt++)
        { 
            hgcerAdcMult_Hist[iPmt]->Fill(hgcerAdcMult[iPmt]);
            ngcerAdcMult_Hist[iPmt]->Fill(ngcerAdcMult[iPmt]);
            //if (hgcerAdcMult[iPmt] > 0) 
	    hgcerAdcTdcDiffTime_Hist[iPmt]->Fill(hgcerAdcTdcDiffTime[iPmt]);
	    //if (ngcerAdcMult[iPmt] > 0) 
	    ngcerAdcTdcDiffTime_Hist[iPmt]->Fill(ngcerAdcTdcDiffTime[iPmt]);
        } 
         
        //aerogel  
        for(Int_t iSide = 0; iSide < aeroSides; iSide++)
        { 
            for(Int_t iPmt = 0; iPmt < aeroNumPmts; iPmt++)
            { 
	      //if (aeroAdcMult[iSide][iPmt] > 0) 
	        aeroAdcTdcDiffTime_Hist[iSide][iPmt]->Fill(aeroAdcTdcDiffTime[iSide][iPmt]);
                aeroAdcMult_Hist[iSide][iPmt]->Fill(aeroAdcMult[iSide][iPmt]);
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
		  //if (hcalAdcMult[iPlane][iSide][iPmt] > 0) 
		    hcalAdcTdcDiffTime_Hist[iPlane][iSide][iPmt]->Fill(hcalAdcTdcDiffTime[iPlane][iSide][iPmt]);
                    hcalAdcMult_Hist[iPlane][iSide][iPmt]->Fill(hcalAdcMult[iPlane][iSide][iPmt]);
                } 
            } 
        } 
         
        //shms calorimeter 
        for(Int_t iSide = 0; iSide < calSides; iSide++)
        { 
            for(Int_t iPmt = 0; iPmt < pcalPrNumPmts; iPmt++)
            { 
                if (pcalprAdcMult[iSide][iPmt] < 1) pcalprAdcTdcDiffTime_Hist[iSide][iPmt]->Fill(pcalprAdcTdcDiffTime[iSide][iPmt]);  
                pcalprAdcMult_Hist[iSide][iPmt]->Fill(pcalprAdcMult[iSide][iPmt]);
            } 
        }     
         
        for(Int_t iPmt = 0; iPmt < pcalFlyNumPmts; iPmt++)
        { 
            if (pcalflyAdcMult[iPmt] < 1) pcalflyAdcTdcDiffTime_Hist[iPmt]->Fill(pcalflyAdcTdcDiffTime[iPmt]);
            pcalflyAdcMult_Hist[iPmt]->Fill(pcalflyAdcMult[iPmt]);
        } 
    }
    return; 
}

// input is the path from ref_times directory to rootfile and the run number that your using
void RefTimes( TString rootFileName, Int_t RunNumber)
{
    
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
    
    //save plots
    
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
    for(Int_t iPmt = 0; iPmt < cerNpmts; iPmt++)
    {
        hCer->WriteObject(cerAdcTdcDiffTime_Hist[iPmt], cerAdcTdcDiffTime_Hist[iPmt]->GetName());
        hCer->WriteObject(cerAdcMult_Hist[iPmt], cerAdcMult_Hist[iPmt]->GetName());
    }
    
    //shms
    for(Int_t iPmt = 0; iPmt < cerNpmts; iPmt++)
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
    cout << "Finished saving output!\n---- End ----\n"; 
    return;
}




