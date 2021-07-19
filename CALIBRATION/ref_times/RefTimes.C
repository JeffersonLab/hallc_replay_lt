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
static const UInt_t hHodbars[HodPlanes]         = {16, 10, 16, 10};
static const UInt_t pHodbars[HodPlanes]         = {13, 13, 14, 21};

//Gas Cherenkovs
static const Int_t cerNpmts                     = 4;

//aerogel

//Calorimeter

//...... TO DO ........


//Branch variables
//dc variables
Float_t hdcrawtdc[dcPlanes],    pdcrawtdc[dcPlanes];
Int_t   hdcnhit[dcPlanes],      pdcnhit[dcPlanes]

// hodoscope variables, 
//a mess yes but this is much better than just having about 100 of these
Float_t hHod1xAdcTdcDiffTime[HodSides][hHodbars[1]];
Int_t   hHod1xAdcMult[HodSides][hHodbars[1]];
Float_t hHod1yAdcTdcDiffTime[HodSides][hHodbars[2]];
Int_t   hHod1yAdcMult[HodSides][hHodbars[2]];
Float_t hHod2xAdcTdcDiffTime[HodSides][hHodbars[3]];
Int_t   hHod2xAdcMult[HodSides][hHodbars[3]];
Float_t hHod2yAdcTdcDiffTime[HodSides][hHodbars[4]];
Int_t   hHod2yAdcMult[HodSides][hHodbars[4]];

Float_t pHod1xAdcTdcDiffTime[HodSides][hHodbars[1]];
Int_t   pHod1xAdcMult[HodSides][hHodbars[1]];
Float_t pHod1yAdcTdcDiffTime[HodSides][hHodbars[2]];
Int_t   pHod1yAdcMult[HodSides][hHodbars[2]];
Float_t pHod2xAdcTdcDiffTime[HodSides][hHodbars[3]];
Int_t   pHod2xAdcMult[HodSides][hHodbars[3]];
Float_t pHod2yAdcTdcDiffTime[HodSides][hHodbars[4]];
Int_t   pHod2yAdcMult[HodSides][hHodbars[4]];

//Gas cherenkovs



//Calorimeter

// input is the path from ref_times directory to rootfile and the run number that your using
void refTimes( TString rootFileName, Int_t RunNumber)
{
    TString DaqName = "coin";
    
    //get root file
    TFile* inFile = new TFile(rootFileName, "READ");
    
    //get tree from root file
    TTree *DataTree = dynamic_cast <TTree*> (inFile->Get("T"));
    
    //assign branches to variables.
    for(Int_t i = 0; i < dcPlanes; i++)
    {
        DataTree->SetBranchAddress(Form("H.dc.%s.rawtdc", dcPlanesNames[i]), &hdcrawtsc[i]);
        DataTree->SetBranchAddress(Form("H.dc.%s.nhit", dcPlanesNames[i]), &hdcnhit[i]);
        DataTree->SetBranchAddress(Form("P.dc.%s.rawtdc", dcPlanesNames[i]), &pdcrawtsc[i]);
        DataTree->SetBranchAddress(Form("P.dc.%s.nhit", dcPlanesNames[i]), &pdcnhit[i]);
    }
    for()
    
}



/*
T.coin.pFADC_TREF_ROC2_adcPulseAmpRaw

// HMS branches

// HMS Cer
H.cer.good*
H.cer.RefTime

// HMS DC


// HMS Hodo
H.hod.1x.*
H.hod.1y.*
H.hod.2x.*
H.hod.2y.*


// HMS Cal
H.cal.etotnorm
H.cal.1pr.*
H.cal.2ta.*
H.cal.3ta.*
H.cal.4ta.*

// HMS track info
H.gtr.dp

// HMS kin/rastered beam/react variables
H.kin.*
H.rb.*
H.react.*

// SHMS branches

// SHMS HGC
P.hgcer.good*
P.hgcer.xAtCer
P.hgcer.yAtCer
P.hgcer.RefTime

// SHMS Aero
P.aero.good*

// SHMS Calorimeter
P.cal.etotnorm
P.cal.pr.*
P.cal.fly.*


// SHMS Hodoscope
P.hod.1x.*
P.hod.1y.*
P.hod.2x.*
P.hod.2y.*

// SHMS tracking
P.tr.*
P.gtr.dp
*/
