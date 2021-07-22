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
static const Int_t dcPlanes                     = 11;
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
static const Int_t aeroSides                    = 2;
static const TString aeroSideNames[aeroSides]   = {"Pos", "Neg"};

//Calorimeter
static const Int_t calSides                     = 2;
static const TString calSideNames[calSides]     = {"Pos", "Neg"};
static const Int_t hcalPlanes                   = 4;
static const TString hcalPlaneNames[hcalPlanes] = {"1pr", "2ta", "3ta", "4ta"};


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
Int_t   hdcnhit[dcPlanes],      pdcnhit[dcPlanes]

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
TH1I hFADC_TREF_ROC1_Hist;
TH1I hTref1_Hist, hTref2_Hist;
TH1I hDCREF1_Hist, hDCREF2_Hist, hDCREF3_Hist, hDCREF4_Hist, hDCREF5_Hist; //hDCRef5 not avaiable for runs prior to July 2018
TH1I hFADC_TREF_ROC1_Mult_Hist;
TH1I hTref1_Mult_Hist, hTref2_Mult_Hist;
TH1I hDCREF1_Mult_Hist, hDCREF2_Mult_Hist, hDCREF3_Mult_Hist, hDCREF4_Mult_Hist, hDCREF5_Mult_Hist;

TH1I pFADC_TREF_ROC2_Hist;
TH1I pTref1_Hist, pTref2_Hist;
TH1I pDCREF1_Hist, pDCREF2_Hist, pDCREF3_Hist, pDCREF4_Hist, pDCREF5_Hist, pDCREF6_Hist, pDCREF7_Hist, pDCREF8_Hist, pDCREF9_Hist, pDCREF10_Hist;
TH1I pFADC_TREF_ROC2_Mult_Hist;
TH1I pTref1_Mult_Hist, pTref2_Mult_Hist;
TH1I pDCREF1_Mult_Hist, pDCREF2_Mult_Hist, pDCREF3_Mult_Hist, pDCREF4_Mult_Hist, pDCREF5_Mult_Hist, pDCREF6_Mult_Hist, pDCREF7_Mult_Hist, pDCREF8_Mult_Hist, pDCREF9_Mult_Hist, pDCREF10_Mult_Hist;

//dc variables
TH1F    hdcrawtdc[dcPlanes]_Hist,    pdcrawtdc[dcPlanes];
TH1I    hdcnhit[dcPlanes]_Hist,      pdcnhit[dcPlanes]

// hodoscope variables
TH1F    hHodAdcTdcDiffTime_Hist[HodPlanes][HodSides];
TH1I    hHodAdcMult_Hist[HodPlanes][HodSides];

TH1F    pHodAdcTdcDiffTime_Hist[HodPlanes][HodSides];
TH1I    pHodAdcMult_Hist[HodPlanes][HodSides];

//Gas cherenkovs
//hms
TH1F    cerAdcTdcDiffTime_Hist;
TH1I    cerAdcMult_Hist;

//shms
TH1F    hgcerAdcTdcDiffTime_Hist, ngcerAdcTdcDiffTime_Hist;
TH1I    hgcerAdcMult_Hist,        ngcerAdcMult_Hist;

//aerogel 
TH1F    aeroAdcTdcDiffTime_Hist[aeroSides];
TH1I    aeroAdcMult_Hist[aeroSides];

//Calorimeters
//hms
TH1F    hcalAdcTdcDiffTime_Hist[hcalPlanes][calSides];
TH1I    hcalAdcMult_Hist[hcalPlanes][calSides];

//shms
TH1F    pcalprAdcTdcDiffTime_Hist[calSides];
TH1I    pcalprAdcMult_Hist[calSides];

TH1F    pcalflyAdcTdcDiffTime_Hist;
TH1I    pcalflyAdcMult_Hist;


void setBranchAddresses(TTree* DataTree)
{
    //assign Branches to ref Time variables
    DataTree->SetBranchAddress(Form("T.%s.hFADC_TREF_ROC1_adcPulseTimeRaw", DaqName), &hFADC_TREF_ROC1);
    DataTree->SetBranchAddress(Form("T.%s.hT1_tdcTimeRaw", DaqName), &hTref1);
    DataTree->SetBranchAddress(Form("T.%s.hT2_tdcTimeRaw", DaqName), &hTref2);
    DataTree->SetBranchAddress(Form("T.%s.hDCREF1_tdcTimeRaw", DaqName), &hDCREF1);
    DataTree->SetBranchAddress(Form("T.%s.hDCREF2_tdcTimeRaw", DaqName), &hDCREF2);
    DataTree->SetBranchAddress(Form("T.%s.hDCREF3_tdcTimeRaw", DaqName), &hDCREF3);
    DataTree->SetBranchAddress(Form("T.%s.hDCREF4_tdcTimeRaw", DaqName), &hDCREF4);
    DataTree->SetBranchAddress(Form("T.%s.hDCREF5_tdcTimeRaw", DaqName), &hDCREF5);
    //multiplicity
    DataTree->SetBranchAddress(Form("T.%s.hFADC_TREF_ROC1_adcMultiplicity", DaqName), &hFADC_TREF_ROC1_Mult);
    DataTree->SetBranchAddress(Form("T.%s.hT1_tdcMultiplicity", DaqName), &hTref1_Mult);
    DataTree->SetBranchAddress(Form("T.%s.hT2_tdcMultiplicity", DaqName), &hTref2_Mult);
    DataTree->SetBranchAddress(Form("T.%s.hDCREF1_tdcMultiplicity", DaqName), &hDCREF1_Mult);
    DataTree->SetBranchAddress(Form("T.%s.hDCREF2_tdcMultiplicity", DaqName), &hDCREF2_Mult);
    DataTree->SetBranchAddress(Form("T.%s.hDCREF3_tdcMultiplicity", DaqName), &hDCREF3_Mult);
    DataTree->SetBranchAddress(Form("T.%s.hDCREF4_tdcMultiplicity", DaqName), &hDCREF4_Mult);
    DataTree->SetBranchAddress(Form("T.%s.hDCREF5_tdcMultiplicity", DaqName), &hDCREF5_Mult);
    
    DataTree->SetBranchAddress(Form("T.%s.pFADC_TREF_ROC2_adcPulseTimeRaw", DaqName), &pFADC_TREF_ROC2);
    DataTree->SetBranchAddress(Form("T.%s.pT1_tdcTimeRaw", DaqName), &pTref1);
    DataTree->SetBranchAddress(Form("T.%s.pT2_tdcTimeRaw", DaqName), &pTref2);
    DataTree->SetBranchAddress(Form("T.%s.pDCREF1_tdcTimeRaw", DaqName), &pDCREF1);
    DataTree->SetBranchAddress(Form("T.%s.pDCREF2_tdcTimeRaw", DaqName), &pDCREF2);
    DataTree->SetBranchAddress(Form("T.%s.pDCREF3_tdcTimeRaw", DaqName), &pDCREF3);
    DataTree->SetBranchAddress(Form("T.%s.pDCREF4_tdcTimeRaw", DaqName), &pDCREF4);
    DataTree->SetBranchAddress(Form("T.%s.pDCREF5_tdcTimeRaw", DaqName), &pDCREF5);
    DataTree->SetBranchAddress(Form("T.%s.pDCREF6_tdcTimeRaw", DaqName), &pDCREF6);
    DataTree->SetBranchAddress(Form("T.%s.pDCREF7_tdcTimeRaw", DaqName), &pDCREF7);
    DataTree->SetBranchAddress(Form("T.%s.pDCREF8_tdcTimeRaw", DaqName), &pDCREF8);
    DataTree->SetBranchAddress(Form("T.%s.pDCREF9_tdcTimeRaw", DaqName), &pDCREF9);
    DataTree->SetBranchAddress(Form("T.%s.pDCREF10_tdcTimeRaw", DaqName), &pDCREF10);
    
    DataTree->SetBranchAddress(Form("T.%s.pFADC_TREF_ROC2_adcMultiplicity", DaqName), &pFADC_TREF_ROC2_Mult);
    DataTree->SetBranchAddress(Form("T.%s.pT1_tdcMultiplicity", DaqName), &pTref1_Mult);
    DataTree->SetBranchAddress(Form("T.%s.pT2_tdcMultiplicity", DaqName), &pTref2_Mult);
    DataTree->SetBranchAddress(Form("T.%s.pDCREF1_tdcMultiplicity", DaqName), &pDCREF1_Mult);
    DataTree->SetBranchAddress(Form("T.%s.pDCREF2_tdcMultiplicity", DaqName), &pDCREF2_Mult);
    DataTree->SetBranchAddress(Form("T.%s.pDCREF3_tdcMultiplicity", DaqName), &pDCREF3_Mult);
    DataTree->SetBranchAddress(Form("T.%s.pDCREF4_tdcMultiplicity", DaqName), &pDCREF4_Mult);
    DataTree->SetBranchAddress(Form("T.%s.pDCREF5_tdcMultiplicity", DaqName), &pDCREF5_Mult);
    DataTree->SetBranchAddress(Form("T.%s.pDCREF6_tdcMultiplicity", DaqName), &pDCREF6_Mult);
    DataTree->SetBranchAddress(Form("T.%s.pDCREF7_tdcMultiplicity", DaqName), &pDCREF7_Mult);
    DataTree->SetBranchAddress(Form("T.%s.pDCREF8_tdcMultiplicity", DaqName), &pDCREF8_Mult);
    DataTree->SetBranchAddress(Form("T.%s.pDCREF9_tdcMultiplicity", DaqName), &pDCREF9_Mult);
    DataTree->SetBranchAddress(Form("T.%s.pDCREF10_tdcMultiplicity", DaqName), &pDCREF10_Mult);
    
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
        DataTree->SetBranchAddress(Form("H.cal.pr.Good%sAdcTdcDiffTime", calSideNames[iSide]), &pcalprAdcMult[iSide]);
        DataTree->SetBranchAddress(Form("H.cal.pr.Good%sAdcMult", calSideNames[iSide]), &pcalprAdcMult[iSide]);
    }
    DataTree->SetBranchAddress(Form("H.cal.fly.GoodAdcTdcDiffTime"), &pcalprAdcMult[iSide]);
    DataTree->SetBranchAddress(Form("H.cal.fly.GoodAdcMult"), &pcalprAdcMult[iSide]);

    return;
}

// input is the path from ref_times directory to rootfile and the run number that your using
void refTimes( TString rootFileName, Int_t RunNumber)
{
    
    //get root file
    TFile* inFile = new TFile(rootFileName, "READ");
    
    //get tree from root file
    TTree *DataTree = dynamic_cast <TTree*> (inFile->Get("T"));
    
    setBranchAddress(DataTree);
    
    
}




