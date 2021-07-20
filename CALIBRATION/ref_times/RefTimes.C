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

//***** Branch variables ******/

//ref time variables
Int_t hFADC_TREF_ROC1;
Int_t hTref1, hTref2;
Int_t hDCREF1, hDCREF2, hDCREF3, hDCREF4, hDCREF5; //hDCRef5 not avaiable for runs prior to July 2018

Int_t pFADC_TREF_ROC2;
Int_t pTref1, pTref2;
Int_t pDCREF1, pDCREF2, pDCREF3, pDCREF4, pDCREF5, pDCREF6, pDCREF7, pDCREF8, pDCREF9, pDCREF10;


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



void setBrachAddresses(TTree* DataTree)
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
            DataTree->SetBranchAddress(Form("H.hod.%s.Good%sAdcTdcDiffTime", HodPlanesNames[iPlane], HodSideNames[iSide]), &hHodAdcTdsDiffTime[iPlane][iSide]);
            DataTree->SetBranchAddress(Form("H.hod.%s.Good%sAdcMult", HodPlanesNames[iPlane], HodSideNames[iSide]), &hHodAdcMult[iPlane][iSide]);
            
            DataTree->SetBranchAddress(Form("H.hod.%s.Good%sAdcTdcDiffTime", HodPlanesNames[iPlane], HodSideNames[iSide]), &pHodAdcTdsDiffTime[iPlane][iSide]);
            DataTree->SetBranchAddress(Form("H.hod.%s.Good%sAdcMult", HodPlanesNames[iPlane], HodSideNames[iSide]), &pHodAdcMult[iPlane][iSide]);
        }
    }
    
    //shms gas cherenkov
    
    
    //aerogel
    for(Int_t iSide = 0; iSide < aeroSides; iSide++)
    {
        DataTree->SetBranchAddress(Form("P.aero.good%sAdcTdcDiffTime", aeroSideNames[iSide]), &aeroAdcTdcDiffTime[iSide]);
        DataTree->SetBranchAddress(Form("P.aero.good%sAdcMult", aeroSideNames[iSide]), &aeroAdcMult[iSide]);
    }
}

// input is the path from ref_times directory to rootfile and the run number that your using
void refTimes( TString rootFileName, Int_t RunNumber)
{
    
    //get root file
    TFile* inFile = new TFile(rootFileName, "READ");
    
    //get tree from root file
    TTree *DataTree = dynamic_cast <TTree*> (inFile->Get("T"));
    
    
    
    
}



/*
P.aero.goodPosAdcTdcDiffTime
P.aero.goodPosAdcMult
P.aero.goodNegAdcTdcDiffTime
P.aero.goodNegAdcMult


*/
