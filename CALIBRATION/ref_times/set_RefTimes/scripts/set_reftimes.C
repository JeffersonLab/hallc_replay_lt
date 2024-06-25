//#include "example.h"
//Define and Set REF. TIME CUTS 
//0.0625 ns / Ch., in case it is used

#include "TROOT.h"
#include "TRint.h"
#include "TFile.h"
#include "TH1F.h"
#include "TTree.h"
#include "TLine.h"
#include "TCanvas.h"
#include <sys/stat.h>
#include <iostream>

// load dedicated header files for this task
#include "set_reftimes.h"
#include "../../../UTILS_CAFE/UTILS/parse_utils.h"
#include "../../../UTILS_CAFE/UTILS/hallc_parse_utils.h"

using namespace std;


void set_param_files(){
  
  // User MUST point to the param files currently being used
  // by their replay script so that the existing cuts may be overlayed with
  // the replayed data, and determine whether to change the limits or not
  // the new limits (for hodoscopes and calorimeter will be determined automatically,
  // given the high channel density

  pref_param_fname = "../../PARAM/SHMS/GEN/fall22/p_reftime_cut_cafe.param";
  href_param_fname = "../../PARAM/HMS/GEN/fall22/h_reftime_cut_cafe.param";

  phodo_param_fname = "../../PARAM/SHMS/HODO/fall22/cuts/phodo_cuts_cafe.param";
  hhodo_param_fname = "../../PARAM/HMS/HODO/fall22/cuts/hhodo_cuts_cafe.param";
  
  pdc_param_fname = "../../PARAM/SHMS/DC/fall22/cuts/pdc_cuts_cafe.param"; //"../../PARAM/SHMS/DC/pdc_cuts.param";
  hdc_param_fname ="../../PARAM/HMS/DC/fall22/cuts/hdc_cuts_cafe.param";  //"../../PARAM/HMS/DC/hdc_cuts.param";

  phgcer_param_fname = "../../PARAM/SHMS/HGCER/fall22/cuts/phgcer_cuts_init.param";
  pngcer_param_fname = "../../PARAM/SHMS/NGCER/fall22/cuts/pngcer_cuts_cafe.param";
  hcer_param_fname = "../../PARAM/HMS/CER/fall22/cuts/hcer_cuts_cafe.param";

  pcal_param_fname = "../../PARAM/SHMS/CAL/fall22/cuts/pcal_cuts_cafe.param";
  hcal_param_fname = "../../PARAM/HMS/CAL/fall22/cuts/hcal_cuts_cafe.param";

}

Double_t read_ref_times(TString spec="", TString det_reftime_name=""){

  /* Brief: read the reference times currently being used
     by hcana (assumes hcana reads them from a specific param file name)
     This is mostly to check whether the current ref. times are set correctly
 
     ------
     input:
     ------
     spec                :  spectrometer name ("HMS" or "SHMS")
     det_reftime_name    :  detector reference time name (as it appears in ref. time param file)
     
     
     "HGCER", "NGCER" only apply if using "SHMS"

     NOTE: the adc ref. cuts are same for all detectors since each received a copy of the same signal

     -------
     output:
     -------
     a Double_t value of the specific ref. times requested
     

   */

  // call function that defines param file paths
  set_param_files();
  
  Double_t  det_reftime;
 
  
  if(spec=="SHMS"){
    //cout << Form("reading reference time parameter '%s' from: %s",  det_reftime_name.Data(), param_fname.Data()) << endl;
    det_reftime = stod(split(FindString(Form("%s", det_reftime_name.Data()),  pref_param_fname.Data())[0], '=')[1]);
  }
  else if (spec=="HMS"){
    //cout << Form("reading reference time parameter '%s' from: %s",  det_reftime_name.Data(), param_fname.Data()) << endl;
    det_reftime = stod(split(FindString(Form("%s", det_reftime_name.Data()),   href_param_fname.Data())[0], '=')[1]);
  }
  
  return det_reftime;

}


void set_reftimes(TString filename="", int run=0, TString daq_mode="coin", Bool_t set_refTimes=true, Bool_t debug=false)
{
  
  /* user input: 
     
     1. run      --> run number
     
     2. daq_mode --> "hms", "shms", "coin" (DAQ Mode)
     
     3. set_refTimes --> true or false (determine whether to set reference time cuts) 
     NOTE: If true, will  plot reference time histos in the corresponding directories (USER must determine which cut to set based on the histos)
     else if false, will assume that ref. times have already been set in the replay, and will determine detector time window cuts (and save the plots)
     
     4. debug  --> true or false | if true, will attempt to plot the hodo and cal ADC/TDC Times separately for debugging purposes, to check individual histos
     that are responsible for making up the ADC-TDC Time differences histos
     
   */

  
  //PREVENT DISPLAY 
  gROOT->SetBatch(kTRUE);
  
  //prevent overcrouded axes
  TGaxis::SetMaxDigits(2);


  // call function that defines param file paths
  set_param_files();

  
  
  //=========================
  //====OPEN ROOT FILE=======
  //=========================
  
    
  // Open Ref Time Windows (used to set ref. times)
  //TString filename = Form("../ROOTfiles/open_ref_times/Pion_coin_replay_timeWin_check_cyero_%d_100000.root", run);
  
  // These ROOTfiles have ther reference times applied
  //TString filename = Form("./ROOTfiles/../Pion_coin_replay_timeWin_check_cyero_%d_100000.root", run);

  //read ROOTfile and Get TTree
  TFile *data_file = new TFile(filename.Data(), "READ"); 
  TTree *T = (TTree*)data_file->Get("T");

  
  TFile *outROOT = NULL;

  //Create HMS/SHMS Ref time Dir
  if(set_refTimes) {
    cout << "============================" << endl;
    cout << "=   DOING REFEFENCE TIMES  =" << endl;
    cout << "============================" << endl;
    
    //========================================
    //====Create Directories to Save Plots====
    //========================================
    mkdir(Form("Time_cuts_refTime%d", run), S_IRWXU);
    
    //mkdir(Form("Time_cuts_refTime%d/param_files", run), S_IRWXU);
    
    mkdir(Form("Time_cuts_refTime%d/HMS", run), S_IRWXU);
    mkdir(Form("Time_cuts_refTime%d/SHMS", run), S_IRWXU); 

    mkdir(Form("Time_cuts_refTime%d/HMS/refTime", run), S_IRWXU);
    mkdir(Form("Time_cuts_refTime%d/SHMS/refTime", run), S_IRWXU);

    //Create output root file where histograms will be stored                                                                  
    outROOT = new TFile(Form("./Time_cuts_refTime%d/refTime_%s_histos_run%d.root", run, daq_mode.Data(), run), "recreate"); 
  }
  
  //Create HMS/SHMS Det time win. Dir
  else{
    cout << "==================================" << endl;
    cout << "=   DOING DETECTOR TIME WINDOWS  =" << endl;
    cout << "==================================" << endl;
    
    //========================================
    //====Create Directories to Save Plots====
    //========================================
    mkdir(Form("Time_cuts_tWinSet%d", run), S_IRWXU);
    mkdir(Form("Time_cuts_tWinSet%d/param_files", run), S_IRWXU);
    mkdir(Form("Time_cuts_tWinSet%d/HMS", run), S_IRWXU);
    mkdir(Form("Time_cuts_tWinSet%d/SHMS", run), S_IRWXU);
    
    mkdir(Form("Time_cuts_tWinSet%d/HMS/CER", run), S_IRWXU);
    mkdir(Form("Time_cuts_tWinSet%d/HMS/HODO", run), S_IRWXU);
    mkdir(Form("Time_cuts_tWinSet%d/HMS/CAL", run), S_IRWXU);
    mkdir(Form("Time_cuts_tWinSet%d/HMS/DC", run), S_IRWXU);
  
    
    mkdir(Form("Time_cuts_tWinSet%d/SHMS/CER", run), S_IRWXU);
    mkdir(Form("Time_cuts_tWinSet%d/SHMS/HODO", run), S_IRWXU);
    mkdir(Form("Time_cuts_tWinSet%d/SHMS/CAL", run), S_IRWXU);
    mkdir(Form("Time_cuts_tWinSet%d/SHMS/DC", run), S_IRWXU);

    //Create output root file where histograms will be stored                                        
    outROOT = new TFile(Form("./Time_cuts_tWinSet%d/detTimeWin_%s_histos_run%d.root", run, daq_mode.Data(), run), "recreate"); 
  }

  
  //===============================
  //INITIALIZE HISTOGRAM BINNING
  //===============================

  if(set_refTimes) {
    
    //-----------------
    //REF Time Histos 
    //-----------------
    
    //HMS                           SHMS
    hhod_tref_nbins = 200,          phod_tref_nbins = 200;
    hhod_tref_xmin = -10000,          phod_tref_xmin = -16000;
    hhod_tref_xmax = 8000,          phod_tref_xmax = 14000;
    
    hdc_tref_nbins = 100,           pdc_tref_nbins = 100;
    hdc_tref_xmin = -1000,            pdc_tref_xmin = -2000;
    hdc_tref_xmax = 20000,          pdc_tref_xmax = 25000;
    
    hadc_tref_nbins = 100,          padc_tref_nbins = 100;
    hadc_tref_xmin = -1000,         padc_tref_xmin = -2000;
    hadc_tref_xmax = 7000,          padc_tref_xmax = 14000;

  }

  else{

    cout << "Init Histos Binning" << endl;
    //TRG (ptrig1,2,3,4), ONLY singles triggers (user may only be interested in triggers that form a coin. for example, pTRIG2, pTRIG3 (SHMS EL-REAL x HMS 3/4)
    ptrg1_roc1_nbins=200, ptrg1_roc1_xmin=0, ptrg1_roc1_xmax=8000;
    ptrg1_roc2_nbins=200, ptrg1_roc2_xmin=0, ptrg1_roc2_xmax=8000;
    
    ptrg2_roc1_nbins=200, ptrg2_roc1_xmin=0, ptrg2_roc1_xmax=8000;
    ptrg2_roc2_nbins=200, ptrg2_roc2_xmin=0, ptrg2_roc2_xmax=8000;

    ptrg3_roc1_nbins=200, ptrg3_roc1_xmin=0, ptrg3_roc1_xmax=8000;
    ptrg3_roc2_nbins=200, ptrg3_roc2_xmin=0, ptrg3_roc2_xmax=8000;

    ptrg4_roc1_nbins=200, ptrg4_roc1_xmin=0, ptrg4_roc1_xmax=8000;
    ptrg4_roc2_nbins=200, ptrg4_roc2_xmin=0, ptrg4_roc2_xmax=8000;
    
    pEDTM_nbins=200, pEDTM_xmin=0, pEDTM_xmax=8000;

    
    //ADC-TDC Time Diff Histos
    //HMS               SHMS
    hhod_nbins = 100,   phod_nbins = 100;    
    hhod_xmin = -500,    phod_xmin = -500;    
    hhod_xmax = 500,     phod_xmax = 500;  
    
    //hodo tdc time bins (debug)
    hhod_tnbins = 100,   phod_tnbins = 100;    
    hhod_txmin = -1000,  phod_txmin = -1000;    
    hhod_txmax = 2000,   phod_txmax = 2000;  
    
    hdc_nbins = 100,    pdc_nbins = 100;                                                      
    hdc_xmin = -20000,  pdc_xmin = -20000;               
    hdc_xmax = 0.,  pdc_xmax = 0;  
    
    hcer_nbins = 100,   phgcer_nbins = 200,    pngcer_nbins = 200;                    
    hcer_xmin = -500,   phgcer_xmin = -500,    pngcer_xmin = -500;       
    hcer_xmax = 500,    phgcer_xmax = 500,     pngcer_xmax = 500;               
    
    hcal_nbins = 100,   pPrsh_nbins = 100,      pcal_nbins = 100;  
    hcal_xmin = -500,   pPrsh_xmin = -500,      pcal_xmin = -500;    
    hcal_xmax = 500,    pPrsh_xmax = 500,       pcal_xmax = 500; 
    
    pPrshAdc_nbins = 500,         pcalAdc_nbins = 500;
    pPrshAdc_xmin = -500.,        pcalAdc_xmin = -500.;
    pPrshAdc_xmax = 500.,         pcalAdc_xmax = 500.;
    
    //=====================================
  }

  

  

  //===========================
  //===Set Branch Address======
  //===Reference Time Leafs====
  //===========================

  
  if(set_refTimes) {
    
    //HMS REF-TIME LEAFS
    for (int i=0; i<4; i++)
      {
	n_hDC_ref = Form("T.%s.hDCREF%d_tdcTimeRaw", daq_mode.Data(), i+1);
	n_hDC_tdcMult = Form("T.%s.hDCREF%d_tdcMultiplicity", daq_mode.Data(), i+1);
	
	T->SetBranchAddress(n_hDC_ref, &hDC_ref[i]);
	T->SetBranchAddress(n_hDC_tdcMult, &hDC_tdcMult[i]);
	
	H_DC_Tref[i] = new TH1F(Form("hDC%d_refTime", i+1), Form("HMS DC Ref %d", i+1), hdc_tref_nbins,  hdc_tref_xmin, hdc_tref_xmax);
	H_DC_Tref_CUT[i] = new TH1F(Form("hDC%d_refTime_CUT", i+1), Form("HMS DC Ref CUT %d", i+1), hdc_tref_nbins,  hdc_tref_xmin, hdc_tref_xmax);
	
      }
    
    H_hodo_Tref = new TH1F("hT1_ref", "HMS Hodo hT1 Ref. Time", hhod_tref_nbins, hhod_tref_xmin, hhod_tref_xmax);
    H_FADC_Tref = new TH1F("hFADC_ref", "HMS fADC Ref. Time", hadc_tref_nbins,  hadc_tref_xmin, hadc_tref_xmax);
    
    H_hodo_Tref_CUT = new TH1F("hT1_ref_CUT", "HMS Hodo hT1 Ref. Time (CUT)", hhod_tref_nbins, hhod_tref_xmin, hhod_tref_xmax);
    H_FADC_Tref_CUT = new TH1F("hFADC_ref_CUT", "HMS fADC Ref. Time (CUT)", hadc_tref_nbins,  hadc_tref_xmin, hadc_tref_xmax);
    
    
    n_hT1_ref = Form("T.%s.hT1_tdcTimeRaw", daq_mode.Data());
    n_hFADC_ref = Form("T.%s.hFADC_TREF_ROC1_adcPulseTimeRaw", daq_mode.Data());
    n_hT1_tdcMult = Form("T.%s.hT1_tdcMultiplicity", daq_mode.Data());
    n_hFADC_adcMult = Form("T.%s.hFADC_TREF_ROC1_adcMultiplicity", daq_mode.Data());
    
    T->SetBranchAddress(n_hT1_ref, &hT1_ref);     
    T->SetBranchAddress(n_hFADC_ref, &hFADC_ref);
    T->SetBranchAddress(n_hT1_tdcMult, &hT1_tdcMult);
    T->SetBranchAddress(n_hFADC_adcMult, &hFADC_adcMult);
    
    
    //SHMS REF-TIME LEAFS 
    for (int i=0; i<10; i++)
      {
	n_pDC_ref = Form("T.%s.pDCREF%d_tdcTimeRaw",daq_mode.Data(), i+1);
	n_pDC_tdcMult = Form("T.%s.pDCREF%d_tdcMultiplicity", daq_mode.Data(), i+1);
	
	T->SetBranchAddress(n_pDC_ref, &pDC_ref[i]);
	T->SetBranchAddress(n_pDC_tdcMult, &pDC_tdcMult[i]);
	
	P_DC_Tref[i] = new TH1F(Form("pDC%d_refTime", i+1), Form("SHMS DC Ref %d", i+1), pdc_tref_nbins,  pdc_tref_xmin, pdc_tref_xmax);
	P_DC_Tref_CUT[i] = new TH1F(Form("pDC%d_refTime_CUT", i+1), Form("SHMS DC Ref %d (CUT)", i+1), pdc_tref_nbins,  pdc_tref_xmin, pdc_tref_xmax);
	
      }
    
    n_pT1_ref = Form("T.%s.pT1_tdcTimeRaw", daq_mode.Data());
    n_pT1_tdcMult = Form("T.%s.pT1_tdcMultiplicity", daq_mode.Data());
    n_pT2_ref = Form("T.%s.pT2_tdcTimeRaw", daq_mode.Data());
    n_pT2_tdcMult = Form("T.%s.pT2_tdcMultiplicity", daq_mode.Data());
    n_pFADC_ref = Form("T.%s.pFADC_TREF_ROC2_adcPulseTimeRaw", daq_mode.Data());
    n_pFADC_adcMult = Form("T.%s.pFADC_TREF_ROC2_adcMultiplicity", daq_mode.Data());
    
    P_hodo_Tref1 = new TH1F("pT1_ref", "SHMS Hodo pT1 Ref. Time", phod_tref_nbins, phod_tref_xmin, phod_tref_xmax);
    P_hodo_Tref2 = new TH1F("pT2_ref", "SHMS Hodo pT2 Ref. Time", phod_tref_nbins, phod_tref_xmin, phod_tref_xmax);
    P_FADC_Tref = new TH1F("pFADC_ref", "SHMS fADC Ref. Time", padc_tref_nbins,  padc_tref_xmin, padc_tref_xmax);
    
    P_hodo_Tref1_CUT = new TH1F("pT1_ref_CUT", "SHMS Hodo pT1 Ref. Time (CUT)", phod_tref_nbins, phod_tref_xmin, phod_tref_xmax);
    P_hodo_Tref2_CUT = new TH1F("pT2_ref_CUT", "SHMS Hodo pT2 Ref. Time (CUT)", phod_tref_nbins, phod_tref_xmin, phod_tref_xmax);
    P_FADC_Tref_CUT = new TH1F("pFADC_ref_CUT", "SHMS fADC Ref. Time (CUT)", padc_tref_nbins,  padc_tref_xmin, padc_tref_xmax);
    
    
    T->SetBranchAddress(n_pT1_ref, &pT1_ref);
    T->SetBranchAddress(n_pT1_tdcMult, &pT1_tdcMult);
    T->SetBranchAddress(n_pT2_ref, &pT2_ref);
    T->SetBranchAddress(n_pT2_tdcMult, &pT2_tdcMult);
    T->SetBranchAddress(n_pFADC_ref, &pFADC_ref);
    T->SetBranchAddress(n_pFADC_adcMult, &pFADC_adcMult);
  }

  else{
    
    //======================================
    //=======Set Branch Address============= 
    //=======Detector Time Window Leafs=====
    //======================================
    
    cout << "Set Branch Address" << endl;
    //TRIGGER DETECTOR (ONLY WHEN LOOKING AT COINCIDENCES)
    n_ptrg1_r1 = "T.coin.pTRIG1_ROC1_tdcTimeRaw";
    n_ptrg1_r2 = "T.coin.pTRIG1_ROC2_tdcTimeRaw";
    
    n_ptrg2_r1 = "T.coin.pTRIG2_ROC1_tdcTimeRaw";
    n_ptrg2_r2 = "T.coin.pTRIG2_ROC2_tdcTimeRaw";
    
    n_ptrg3_r1 = "T.coin.pTRIG3_ROC1_tdcTimeRaw";
    n_ptrg3_r2 = "T.coin.pTRIG3_ROC2_tdcTimeRaw";

    n_ptrg4_r1 = "T.coin.pTRIG4_ROC1_tdcTimeRaw";
    n_ptrg4_r2 = "T.coin.pTRIG4_ROC2_tdcTimeRaw";
    
    n_pEDTM = "T.coin.pEDTM_tdcTimeRaw";

    T->SetBranchAddress(n_ptrg1_r1, &ptrg1_r1);
    T->SetBranchAddress(n_ptrg1_r2, &ptrg1_r2);
    
    T->SetBranchAddress(n_ptrg2_r1, &ptrg2_r1);
    T->SetBranchAddress(n_ptrg2_r2, &ptrg2_r2);
    
    T->SetBranchAddress(n_ptrg3_r1, &ptrg3_r1);
    T->SetBranchAddress(n_ptrg3_r2, &ptrg3_r2);

    T->SetBranchAddress(n_ptrg4_r1, &ptrg4_r1);
    T->SetBranchAddress(n_ptrg4_r2, &ptrg4_r2);
    
    T->SetBranchAddress(n_pEDTM, &pEDTM);

    pTrig1_ROC1_rawTdcTime = new TH1F("pTRIG1_ROC1_rawTdcTime", "pTRIG1_ROC1_rawTdcTime", ptrg1_roc1_nbins, ptrg1_roc1_xmin, ptrg1_roc1_xmax);
    pTrig1_ROC2_rawTdcTime = new TH1F("pTRIG1_ROC2_rawTdcTime", "pTRIG1_ROC2_rawTdcTime", ptrg1_roc2_nbins, ptrg1_roc2_xmin, ptrg1_roc2_xmax);
 
    pTrig2_ROC1_rawTdcTime = new TH1F("pTRIG2_ROC1_rawTdcTime", "pTRIG2_ROC1_rawTdcTime", ptrg2_roc1_nbins, ptrg2_roc1_xmin, ptrg2_roc1_xmax);
    pTrig2_ROC2_rawTdcTime = new TH1F("pTRIG2_ROC2_rawTdcTime", "pTRIG2_ROC2_rawTdcTime", ptrg2_roc2_nbins, ptrg2_roc2_xmin, ptrg2_roc2_xmax);
 
    pTrig3_ROC1_rawTdcTime = new TH1F("pTRIG3_ROC1_rawTdcTime", "pTRIG3_ROC1_rawTdcTime", ptrg3_roc1_nbins, ptrg3_roc1_xmin, ptrg3_roc1_xmax);
    pTrig3_ROC2_rawTdcTime = new TH1F("pTRIG3_ROC2_rawTdcTime", "pTRIG3_ROC2_rawTdcTime", ptrg3_roc2_nbins, ptrg3_roc2_xmin, ptrg3_roc2_xmax);

    pTrig4_ROC1_rawTdcTime = new TH1F("pTRIG4_ROC1_rawTdcTime", "pTRIG4_ROC1_rawTdcTime", ptrg4_roc1_nbins, ptrg4_roc1_xmin, ptrg4_roc1_xmax);
    pTrig4_ROC2_rawTdcTime = new TH1F("pTRIG4_ROC2_rawTdcTime", "pTRIG4_ROC2_rawTdcTime", ptrg4_roc2_nbins, ptrg4_roc2_xmin, ptrg4_roc2_xmax);
    
    pEDTM_rawTdcTime       = new TH1F("pEDTM_rawTdcTime",       "pEDTM_rawTdcTime",       pEDTM_nbins, pEDTM_xmin, pEDTM_xmax);


    
    //Loov over HMS  Cherenkov PMTs
    for (Int_t ipmt = 0; ipmt < 2; ipmt++ )
      {
	n_hcer_TdcAdcTimeDiff =  "H.cer.goodAdcTdcDiffTime";
	n_hcer_AdcMult = "H.cer.goodAdcMult";
	
	T->SetBranchAddress(n_hcer_AdcMult, &hcer_AdcMult);
	T->SetBranchAddress(n_hcer_TdcAdcTimeDiff, &hcer_TdcAdcTimeDiff);
	
	H_cer_TdcAdcTimeDiff[ipmt] = new TH1F(Form("hCER%d_timeDiff", ipmt+1), Form("HMS Cer %d AdcTdcTimeDiff", ipmt+1), hcer_nbins, hcer_xmin, hcer_xmax);
	H_cer_TdcAdcTimeDiff_CUT[ipmt] = new TH1F(Form("hCER%d_timeDiff_CUT", ipmt+1), Form("HMS Cer %d AdcTdcTimeDiff (CUT)", ipmt+1), hcer_nbins, hcer_xmin, hcer_xmax);
	
      }
    
    
    //Loop over SHMS Cherenkov PMTs
    for (Int_t ipmt = 0; ipmt < 4; ipmt++ )
      {  
	
	//SHMS Heavy Gas Cherenkov
	n_phgcer_TdcAdcTimeDiff =  "P.hgcer.goodAdcTdcDiffTime";
	n_phgcer_AdcMult = "P.hgcer.goodAdcMult";
	
	T->SetBranchAddress(n_phgcer_AdcMult, &phgcer_AdcMult);
	T->SetBranchAddress(n_phgcer_TdcAdcTimeDiff, &phgcer_TdcAdcTimeDiff);
	
	P_hgcer_TdcAdcTimeDiff[ipmt] = new TH1F(Form("pHGCER%d_timeDiff", ipmt+1), Form("SHMS Heavy Gas Cer%d AdcTdcTimeDiff", ipmt+1), phgcer_nbins, phgcer_xmin, phgcer_xmax);
	P_hgcer_TdcAdcTimeDiff_CUT[ipmt] = new TH1F(Form("pHGCER%d_timeDiff_CUT", ipmt+1), Form("SHMS Heavy Gas Cer%d AdcTdcTimeDiff (CUT)", ipmt+1), phgcer_nbins, phgcer_xmin, phgcer_xmax);
	
	//SHMS Noble Gas Cherenkov
	n_pngcer_TdcAdcTimeDiff =  "P.ngcer.goodAdcTdcDiffTime";
	n_pngcer_AdcMult = "P.ngcer.goodAdcMult";
	
	T->SetBranchAddress(n_pngcer_AdcMult, &pngcer_AdcMult);
	T->SetBranchAddress(n_pngcer_TdcAdcTimeDiff, &pngcer_TdcAdcTimeDiff);
	
	P_ngcer_TdcAdcTimeDiff[ipmt] = new TH1F(Form("pNGCER%d_timeDiff", ipmt+1), Form("SHMS Noble Gas Cer%d AdcTdcTimeDiff", ipmt+1), pngcer_nbins, pngcer_xmin, pngcer_xmax);
	P_ngcer_TdcAdcTimeDiff_CUT[ipmt] = new TH1F(Form("pNGCER%d_timeDiff_CUT", ipmt+1), Form("SHMS Noble Gas Cer%d AdcTdcTimeDiff (CUT)", ipmt+1), pngcer_nbins, pngcer_xmin, pngcer_xmax);
	
      }
    
    
    //Loop over Drift Chamber Planes
    for (Int_t npl = 0; npl < 12; npl++ )
      {
	//HMS
	base = "H.dc." + hdc_pl_names[npl];
	n_hdc_rawTDC = base + "." + "rawtdc";
	n_hndata_rawTDC = "Ndata." + n_hdc_rawTDC;
	
	T->SetBranchAddress(n_hdc_rawTDC, hdc_rawTDC[npl]);
	T->SetBranchAddress(n_hndata_rawTDC, &hndata_rawTDC[npl]);
	
	H_dc_rawTDC[npl] = new TH1F(Form("hDC%s_rawTDC", hdc_pl_names[npl].Data()), Form("HMS DC Plane %s Raw TDC", hdc_pl_names[npl].Data()), hdc_nbins, hdc_xmin, hdc_xmax);
	H_dc_rawTDC_CUT[npl] = new TH1F(Form("hDC%s_rawTDC_CUT", hdc_pl_names[npl].Data()), Form("HMS DC Plane %s Raw TDC (CUT)", hdc_pl_names[npl].Data()), hdc_nbins, hdc_xmin, hdc_xmax);
	
	//SHMS
	base = "P.dc." + pdc_pl_names[npl];
	n_pdc_rawTDC = base + "." + "rawtdc";
	n_pndata_rawTDC = "Ndata." + n_pdc_rawTDC;
	
	T->SetBranchAddress(n_pdc_rawTDC, pdc_rawTDC[npl]);
	T->SetBranchAddress(n_pndata_rawTDC, &pndata_rawTDC[npl]);
	
	P_dc_rawTDC[npl] = new TH1F(Form("pDC%s_rawTDC", pdc_pl_names[npl].Data()), Form("SHMS DC Plane %s Raw TDC", pdc_pl_names[npl].Data()), pdc_nbins, pdc_xmin, pdc_xmax);
	P_dc_rawTDC_CUT[npl] = new TH1F(Form("pDC%s_rawTDC_CUT", pdc_pl_names[npl].Data()), Form("SHMS DC Plane %s Raw TDC (CUT)", pdc_pl_names[npl].Data()), pdc_nbins, pdc_xmin, pdc_xmax);
	
      }
    
    //Loop over Hodo/Calorimeter Planes
    for (Int_t npl = 0; npl < hod_PLANES; npl++ )
      {
	
	//Loop over Hodo/Calorimeter sides
	for (Int_t iside = 0; iside < SIDES; iside++)
	  {
	    
	    //Loop over HMS hodo PMTs
	    for (Int_t ipmt = 0; ipmt < hmaxPMT[npl]; ipmt++)
	      {
		base = "H.hod." + hod_pl_names[npl];
		
		
		if(debug) n_hhod_TdcTimeUnCorr = base + "." + side_names[iside] + "TdcTimeUnCorr";
	      
		
		n_hhod_TdcAdcTimeDiff = base + "." + side_names[iside] + "AdcTdcDiffTime";
		n_hhod_AdcMult = base + "." + side_names[iside] + "AdcMult";
		
		if(debug) T->SetBranchAddress(n_hhod_TdcTimeUnCorr, hhod_TdcTimeUnCorr[npl][iside]);
		
		T->SetBranchAddress(n_hhod_TdcAdcTimeDiff, hhod_TdcAdcTimeDiff[npl][iside]);
		T->SetBranchAddress(n_hhod_AdcMult, hhod_AdcMult[npl][iside]);
		
		if(debug) H_hod_TdcTimeUnCorr[npl][iside][ipmt] = new TH1F(Form("hHod%s%d%s_TdcTimeUnCorr", hod_pl_names[npl].Data(),ipmt+1,nsign[iside].Data() ), Form("HMS Hodo %s%d%s TdcTimeUnCorr", hod_pl_names[npl].Data(),ipmt+1,nsign[iside].Data()),hhod_tnbins,hhod_txmin,hhod_txmax);
		H_hod_TdcAdcTimeDiff[npl][iside][ipmt] = new TH1F(Form("hHod%s%d%s_timeDiff", hod_pl_names[npl].Data(),ipmt+1,nsign[iside].Data() ), Form("HMS Hodo %s%d%s AdcTdcTimeDiff", hod_pl_names[npl].Data(),ipmt+1,nsign[iside].Data()),hhod_nbins,hhod_xmin,hhod_xmax);
		H_hod_TdcAdcTimeDiff_CUT[npl][iside][ipmt] = new TH1F(Form("hHod%s%d%s_timeDiff_CUT", hod_pl_names[npl].Data(),ipmt+1,nsign[iside].Data() ), Form("HMS Hodo %s%d%s AdcTdcTimeDiff (CUT)", hod_pl_names[npl].Data(),ipmt+1,nsign[iside].Data()),hhod_nbins,hhod_xmin,hhod_xmax);
		
	      }
	    
	    //Loop over HMS Calorimeter PMTs

	    
	    
	    
	    for (Int_t ipmt = 0; ipmt < 13; ipmt++)
	      {
		base =  "H.cal." + cal_pl_names[npl];
		
		n_hcal_TdcAdcTimeDiff = base + "." + cal_side_names[iside] + "AdcTdcDiffTime";
		n_hcal_AdcMult = base + "." + cal_side_names[iside] + "AdcMult";
		
		T->SetBranchAddress(n_hcal_TdcAdcTimeDiff, hcal_TdcAdcTimeDiff[npl][iside]);
		T->SetBranchAddress(n_hcal_AdcMult, hcal_AdcMult[npl][iside]);
	

		H_cal_TdcAdcTimeDiff[npl][iside][ipmt] = new TH1F(Form("hCal%s%d%s_timeDiff", cal_pl_names[npl].Data(),ipmt+1,nsign[iside].Data() ), Form("HMS Cal %s%d%s AdcTdcTimeDiff", cal_pl_names[npl].Data(),ipmt+1,nsign[iside].Data()),hcal_nbins,hcal_xmin,hcal_xmax) ;
		H_cal_TdcAdcTimeDiff_CUT[npl][iside][ipmt] = new TH1F(Form("hCal%s%d%s_timeDiff_CUT", cal_pl_names[npl].Data(),ipmt+1,nsign[iside].Data() ), Form("HMS Cal %s%d%s AdcTdcTimeDiff (CUT)", cal_pl_names[npl].Data(),ipmt+1,nsign[iside].Data()),hcal_nbins,hcal_xmin,hcal_xmax) ;
		
	      }
	    
	    
	    //Loop over SHMS hodo PMTs
	    for (Int_t ipmt = 0; ipmt < pmaxPMT[npl]; ipmt++)
	      {
		base = "P.hod." + hod_pl_names[npl];
		
		if(debug) n_phod_TdcTimeUnCorr = base + "." + side_names[iside] + "TdcTimeUnCorr";
		n_phod_TdcAdcTimeDiff = base + "." + side_names[iside] + "AdcTdcDiffTime";
		n_phod_AdcMult = base + "." + side_names[iside] + "AdcMult";
	  	
		if(debug) T->SetBranchAddress(n_phod_TdcTimeUnCorr, phod_TdcTimeUnCorr[npl][iside]);
		T->SetBranchAddress(n_phod_TdcAdcTimeDiff, phod_TdcAdcTimeDiff[npl][iside]);
		T->SetBranchAddress(n_phod_AdcMult, phod_AdcMult[npl][iside]);
		
		if(debug) P_hod_TdcTimeUnCorr[npl][iside][ipmt] = new TH1F(Form("pHod%s%d%s_TdcTimeUnCorr", hod_pl_names[npl].Data(),ipmt+1,nsign[iside].Data() ), Form("SHMS Hodo %s%d%s TdcTimeUnCorr", hod_pl_names[npl].Data(),ipmt+1,nsign[iside].Data()),phod_tnbins,phod_txmin,phod_txmax);
		P_hod_TdcAdcTimeDiff[npl][iside][ipmt] = new TH1F(Form("pHod%s%d%s_timeDiff", hod_pl_names[npl].Data(),ipmt+1,nsign[iside].Data() ), Form("SHMS Hodo %s%d%s AdcTdcTimeDiff", hod_pl_names[npl].Data(),ipmt+1,nsign[iside].Data()),phod_nbins,phod_xmin,phod_xmax);
		P_hod_TdcAdcTimeDiff_CUT[npl][iside][ipmt] = new TH1F(Form("pHod%s%d%s_timeDiff_CUT", hod_pl_names[npl].Data(),ipmt+1,nsign[iside].Data() ), Form("SHMS Hodo %s%d%s AdcTdcTimeDiff (CUT)", hod_pl_names[npl].Data(),ipmt+1,nsign[iside].Data()),phod_nbins,phod_xmin,phod_xmax);
		
	      }
	    
	    if(npl==0)
	      {
		//Loop over SHMS PreSH PMTs
		for (Int_t ipmt = 0; ipmt < 14; ipmt++)
		  {
		    base =  "P.cal.pr";
		    
		    n_pPrSh_TdcAdcTimeDiff = base + "." + cal_side_names[iside] + "AdcTdcDiffTime";
		    n_pPrSh_AdcMult = base + "." + cal_side_names[iside] + "AdcMult";
		    if(debug) n_pPrSh_AdcTime = base + "." +  cal_side_names[iside] + "AdcPulseTime";
		    
		    T->SetBranchAddress(n_pPrSh_TdcAdcTimeDiff, pPrSh_TdcAdcTimeDiff[npl][iside]);
		    T->SetBranchAddress(n_pPrSh_AdcMult, pPrSh_AdcMult[npl][iside]);
		    if(debug) T->SetBranchAddress(n_pPrSh_AdcTime, pPrSh_AdcTime[npl][iside]);
		    
		    P_prSh_TdcAdcTimeDiff[iside][ipmt] = new TH1F(Form("pPrSh_pmt%d%s", ipmt+1, nsign[iside].Data()), Form("SHMS Pre-Shower PMT_%d%s", ipmt+1, nsign[iside].Data()), pPrsh_nbins, pPrsh_xmin, pPrsh_xmax);
		    P_prSh_TdcAdcTimeDiff_CUT[iside][ipmt] = new TH1F(Form("pPrSh_pmt%d%s_CUT", ipmt+1, nsign[iside].Data()), Form("SHMS Pre-Shower PMT_%d%s (CUT)", ipmt+1, nsign[iside].Data()), pPrsh_nbins, pPrsh_xmin, pPrsh_xmax);
		    if(debug) P_prSh_AdcTime[iside][ipmt] = new TH1F(Form("pPrShAdcTime_pmt%d%s", ipmt+1, nsign[iside].Data()), Form("SHMS Pre-Shower Adc Time: PMT_%d%s", ipmt+1, nsign[iside].Data()), pPrshAdc_nbins, pPrshAdc_xmin, pPrshAdc_xmax);
		    
		    
		  }
		if(iside==0)
		  {
		    //Loop over SHMS fly's eye Calorimeter PMTs
		    for (Int_t ipmt = 0; ipmt < 224; ipmt++)
		      {
			base =  "P.cal.fly";
			n_pcal_TdcAdcTimeDiff = base + "." + "goodAdcTdcDiffTime";
			n_pcal_AdcMult = base + "." + "goodAdcMult";
			if(debug) n_pcal_AdcTime = base + "." + "goodAdcPulseTime";
			
			//For multiplicity, see THcSHowerArray.cxx, for totNumGoodAdcHits, 
			T->SetBranchAddress(n_pcal_TdcAdcTimeDiff, pcal_TdcAdcTimeDiff[iside]);
			T->SetBranchAddress(n_pcal_AdcMult, pcal_AdcMult[iside]);
			if(debug) T->SetBranchAddress(n_pcal_AdcTime, pcal_AdcTime[iside]);
			
			P_cal_TdcAdcTimeDiff[ipmt] = new TH1F(Form("pSh_pmt%d", ipmt+1), Form("SHMS Shower PMT_%d", ipmt+1), pcal_nbins, pcal_xmin, pcal_xmax);
			P_cal_TdcAdcTimeDiff_CUT[ipmt] = new TH1F(Form("pSh_pmt%d_CUT", ipmt+1), Form("SHMS Shower PMT_%d (CUT)", ipmt+1), pcal_nbins, pcal_xmin, pcal_xmax);
			if(debug) P_cal_AdcTime[ipmt] = new TH1F(Form("pShAdcTime_pmt%d", ipmt+1), Form("SHMS Shower Adc Time: PMT_%d", ipmt+1), pcalAdc_nbins, pcalAdc_xmin, pcalAdc_xmax);
			
		      }
		    
		  } //end side0 requirement for fly's eye
		
	      } //End plane 0 requirement for Pre-SHower
	    
	    
	  } //End Loop over sides
	
      } //End Loop over planes
    
  } //end else (if set_RefTime == false)

  
  //===================================
  //====== E V E N T    L O O P =======
  //===================================

  Long64_t nentries = T->GetEntries();
 
  //Define A Boolean for multiplicity CUTS
  Bool_t good_Mult;
  
    
  cout << "Loop over entries" << endl;
  //Loop over all entries
  for(Long64_t i=0; i<nentries; i++)
    {
      
      T->GetEntry(i); 


	
      if(set_refTimes) {
	
	//--------------Loop over HMS/SHMS Ref. TImes-------------------
	
	
	//SHMS DC Ref Times
	for (int iref=0; iref<10; iref++)
	  {
	    good_Mult =  pDC_tdcMult[iref] == 2;
	    
	    P_DC_Tref[iref]->Fill(pDC_ref[iref]);
	    if( good_Mult) { P_DC_Tref_CUT[iref]->Fill(pDC_ref[iref]);}
	    
	  }
	
	for(int iref=0; iref<4; iref++)
	  {
	    good_Mult =  hDC_tdcMult[iref] == 1;
	    
	    //HMS DC Ref. Times
	    H_DC_Tref[iref]->Fill(hDC_ref[iref]);
	    if(good_Mult) {H_DC_Tref_CUT[iref]->Fill(hDC_ref[iref]);}
	    
	  }
	
	//HMS Ref
	good_Mult = hT1_tdcMult==1;
	H_hodo_Tref->Fill(hT1_ref);
	if(good_Mult){H_hodo_Tref_CUT->Fill(hT1_ref);}
	
	good_Mult = hFADC_adcMult==1;
	H_FADC_Tref->Fill(hFADC_ref);
	if(good_Mult){H_FADC_Tref_CUT->Fill(hFADC_ref);}
	
	//SHMS Ref
	good_Mult = pT1_tdcMult == 1;
	P_hodo_Tref1->Fill(pT1_ref);
	if(good_Mult) {P_hodo_Tref1_CUT->Fill(pT1_ref);}
	
	good_Mult = pT2_tdcMult == 1;
	P_hodo_Tref2->Fill(pT2_ref);
	if(good_Mult) {P_hodo_Tref2_CUT->Fill(pT2_ref);}
	
	good_Mult = pFADC_adcMult == 1;
	P_FADC_Tref->Fill(pFADC_ref);
	if(good_Mult) {P_FADC_Tref_CUT->Fill(pFADC_ref);} 
	
	//------------------------------------------------------------------------------
      }

      //------ FILL DETECTOR TIME WINDOW HISTOS --------
      else{
	
	//Fill TRG Detector Leafs
	pTrig1_ROC1_rawTdcTime->Fill(ptrg1_r1);
	pTrig1_ROC2_rawTdcTime->Fill(ptrg1_r2);
	
	pTrig2_ROC1_rawTdcTime->Fill(ptrg2_r1);
	pTrig2_ROC2_rawTdcTime->Fill(ptrg2_r2);
	
	pTrig3_ROC1_rawTdcTime->Fill(ptrg3_r1);
	pTrig3_ROC2_rawTdcTime->Fill(ptrg3_r2);

	pTrig4_ROC1_rawTdcTime->Fill(ptrg4_r1);
	pTrig4_ROC2_rawTdcTime->Fill(ptrg4_r2);
	
	pEDTM_rawTdcTime->Fill(pEDTM);

	//Loop over Cherenkov PMTs
	
	for (Int_t ipmt = 0; ipmt < 2; ipmt++)
	  { 
	    //----HMS Cherenkov----
	    
	    //Define Multiplicity Cuts
	    good_Mult = hcer_AdcMult[ipmt] == 1;
	    if(abs(hcer_TdcAdcTimeDiff[ipmt])<1000.){
	      
	      H_cer_TdcAdcTimeDiff[ipmt]->Fill(hcer_TdcAdcTimeDiff[ipmt]);
	      if(good_Mult){H_cer_TdcAdcTimeDiff_CUT[ipmt]->Fill(hcer_TdcAdcTimeDiff[ipmt]);}
	      
	    }	  
	  }
	
	for (Int_t ipmt = 0; ipmt < 4; ipmt++)
	  {                                                                                                                                             
	    
	    //----SHMS Heavy Gas Cherenkov-----
	    
	    //Define Multiplicity Cuts
	    
	    //Require ADC Multiplicity == 1
	    good_Mult = phgcer_AdcMult[ipmt] == 1;
	    if(abs(phgcer_TdcAdcTimeDiff[ipmt])<1000.){
	      P_hgcer_TdcAdcTimeDiff[ipmt]->Fill(phgcer_TdcAdcTimeDiff[ipmt]);
	      if(good_Mult){P_hgcer_TdcAdcTimeDiff_CUT[ipmt]->Fill(phgcer_TdcAdcTimeDiff[ipmt]);}
	    }
	    
	    //----SHMS Noble Gas Cherenkov-----
	    
	    //Define Multiplicity Cuts
	    
	    //Require ADC Multiplicity == 1
	    good_Mult = pngcer_AdcMult[ipmt] == 1;
	    if(abs(pngcer_TdcAdcTimeDiff[ipmt])<1000.){
	      P_ngcer_TdcAdcTimeDiff[ipmt]->Fill(pngcer_TdcAdcTimeDiff[ipmt]);
	      if(good_Mult){P_ngcer_TdcAdcTimeDiff_CUT[ipmt]->Fill(pngcer_TdcAdcTimeDiff[ipmt]);}
	    }
	    
	  } //End Cherenkov PMT loop
	
	
	//-----------------------------------------------------------------------------
	
	//Loop over Drift Chamber Planes
	for (Int_t npl = 0; npl<dc_PLANES; npl++)
	  {
	    
	    
	    //-------HMS Drift Chambers----------
	    
	    //Add Multiplicity Cuts
	    good_Mult = hndata_rawTDC[npl]==1;  //require total hits in plane to be 1
	    
	    //Loop over all hits per event
	    for(Int_t j = 0; j < hndata_rawTDC[npl]; j++)
	      {
		H_dc_rawTDC[npl]->Fill(hdc_rawTDC[npl][j]);	      
	      }
	    
	    if(good_Mult)
	      {
		H_dc_rawTDC_CUT[npl]->Fill(hdc_rawTDC[npl][0]);
	      }
	    
	    
	    //--------SHMS Drift Chambers--------
	    
	    //Define Cuts Here
	    good_Mult = pndata_rawTDC[npl]==1;  //require total hits in plane to be 1
	    
	    //Loop over all hits per event
	    for(Int_t j = 0; j < pndata_rawTDC[npl]; j++)
	      {
		P_dc_rawTDC[npl]->Fill(pdc_rawTDC[npl][j]);
	      }
	    if(good_Mult)
	      {
		P_dc_rawTDC_CUT[npl]->Fill(pdc_rawTDC[npl][0]);
	      }
	    
	  }
	
	//-------------------------------------------------------------------------------
	
	
	//Loop over Hodoscopes/Calorimeter Planes
	for (Int_t ip =0; ip < hod_PLANES; ip++)
	  {
	    
	    
	    //Loop over hodo/calorimeter side
	    for (Int_t iside = 0; iside < SIDES; iside++)
	      {
		
		//Loop over Hodoscopes PMTs
		for (Int_t ipmt = 0; ipmt < hmaxPMT[ip]; ipmt++)
		  {
		    
		    
		    
		    //-------------HMS Hodoscopoes--------------
		    
		    if (debug) H_hod_TdcTimeUnCorr[ip][iside][ipmt]->Fill(hhod_TdcTimeUnCorr[ip][iside][ipmt]/tdc_nsperch);
		    // cut out overflow bins
		    if(abs(hhod_TdcAdcTimeDiff[ip][iside][ipmt])<1000. && abs(hhod_TdcTimeUnCorr[ip][iside][ipmt]/tdc_nsperch)<10000. )
		      {
			good_Mult = hhod_AdcMult[ip][iside][ipmt] == 1;   //HMS HODO Multiplicity CUT
			H_hod_TdcAdcTimeDiff[ip][iside][ipmt]->Fill(hhod_TdcAdcTimeDiff[ip][iside][ipmt]);
			if(good_Mult) {H_hod_TdcAdcTimeDiff_CUT[ip][iside][ipmt]->Fill(hhod_TdcAdcTimeDiff[ip][iside][ipmt]);}
		      }
		    
		  }
		
		//Loop over Calorimeter PMTs
		for (Int_t ipmt = 0; ipmt < 13; ipmt++)
		  {
		    
		    //------------HMS Calorimeter----------------
		    
		    
		    
		    //if(abs(hcal_TdcAdcTimeDiff[ip][iside][ipmt])<1000.)
		      {
			good_Mult = hcal_AdcMult[ip][iside][ipmt] == 1;    //HMS CALO Multiplicity ==1
        
			
			H_cal_TdcAdcTimeDiff[ip][iside][ipmt]->Fill(hcal_TdcAdcTimeDiff[ip][iside][ipmt]);
			if(good_Mult) {H_cal_TdcAdcTimeDiff_CUT[ip][iside][ipmt]->Fill(hcal_TdcAdcTimeDiff[ip][iside][ipmt]);}
			
		      }
		  }
		
		
		//Loop over SHMS Hodoscopes PMTs
		for (Int_t ipmt = 0; ipmt < pmaxPMT[ip]; ipmt++)
		  {
		    
		    
		    
		    //------------SHMS Hodoscopes----------------
		    
		    //UnCorrected TdcTime
		    if (debug) P_hod_TdcTimeUnCorr[ip][iside][ipmt]->Fill(phod_TdcTimeUnCorr[ip][iside][ipmt]/tdc_nsperch);
		    // cut out overflow
		    if(abs(phod_TdcAdcTimeDiff[ip][iside][ipmt])<1000. && abs(phod_TdcTimeUnCorr[ip][iside][ipmt]/tdc_nsperch)<10000. )
		      {
			good_Mult = phod_AdcMult[ip][iside][ipmt] == 1;   //SHMS HODO Multiplicity CUT
			P_hod_TdcAdcTimeDiff[ip][iside][ipmt]->Fill(phod_TdcAdcTimeDiff[ip][iside][ipmt]);
			if(good_Mult) {P_hod_TdcAdcTimeDiff_CUT[ip][iside][ipmt]->Fill(phod_TdcAdcTimeDiff[ip][iside][ipmt]);}
		      }
		  }
		
		
		
		//------------SHMS PreSHower-------------------
		
		//Loop over SHMS PrSh PMTs
		for (Int_t ipmt=0; ipmt < 14; ipmt++)
		  {
		    
		    if(ip==0&& abs(pPrSh_TdcAdcTimeDiff[ip][iside][ipmt])<1000.){
		      good_Mult = pPrSh_AdcMult[ip][iside][ipmt] == 1;
		      P_prSh_TdcAdcTimeDiff[iside][ipmt]->Fill(pPrSh_TdcAdcTimeDiff[ip][iside][ipmt]);
		      if(good_Mult){P_prSh_TdcAdcTimeDiff_CUT[iside][ipmt]->Fill(pPrSh_TdcAdcTimeDiff[ip][iside][ipmt]);}
		    }
		    
		    if(debug) P_prSh_AdcTime[iside][ipmt]->Fill(pPrSh_AdcTime[ip][iside][ipmt]);
		    
		  } //End loop over SHMS PrSH PMTs
		
		
		//----------SHMS FLy's Eye Calorimeter-------------
		for (Int_t ipmt = 0; ipmt < 224; ipmt++)
		  {
		    if(ip==0&&iside==0&&abs(pcal_TdcAdcTimeDiff[iside][ipmt])<1000.)
		      {
			good_Mult = pcal_AdcMult[iside][ipmt] == 1;
			P_cal_TdcAdcTimeDiff[ipmt]->Fill(pcal_TdcAdcTimeDiff[iside][ipmt]);
			if(good_Mult){P_cal_TdcAdcTimeDiff_CUT[ipmt]->Fill(pcal_TdcAdcTimeDiff[iside][ipmt]);}
		      }
		    
		    if(iside==0){
		      if(debug) P_cal_AdcTime[ipmt]->Fill(pcal_AdcTime[iside][ipmt]);
		      
		    }
		  }
		
		
		
	      } // END LOOP OVER SIDES
	    
	  } //END LOOP OVER PLANES
	
      }
      
      cout << "Completion Percentage: " << std::setprecision(2) << double(i) / nentries * 100. << "  % " << std::flush << "\r";
      
    } //END EVENT LOOP
  
       
  //======================================================
  //D R A W   H I S T O G R A M S    T O    C A N V A S
  //======================================================
  
  // flag to draw new suggested cut line 
  Bool_t new_line_flg = false;

  if(set_refTimes) {
    
    //-------Reference Time Histograms----------
    
    //HMS
    hms_REF_Canv = new TCanvas("REF Times", "HMS REF TIMES",  1500, 500);
    hms_REF_Canv->Divide(3,1);


    hhod_trefcut = read_ref_times("HMS", "hhodo_tdcrefcut");
    hdc_trefcut  = read_ref_times("HMS", "hdc_tdcrefcut");
    hadc_trefcut = read_ref_times("HMS", "hhodo_adcrefcut");
    
    hT1_Line = new TLine(abs(hhod_trefcut), 0,  abs(hhod_trefcut), H_hodo_Tref->GetMaximum());
    hDCREF_Line = new TLine(abs(hdc_trefcut), 0,  abs(hdc_trefcut), H_DC_Tref[0]->GetMaximum());
    hFADC_Line = new TLine(abs(hadc_trefcut), 0,  abs(hadc_trefcut), H_FADC_Tref->GetMaximum());
    
    hms_REF_Canv->cd(1);
    gPad->SetLogy();
    auto href_legend = new TLegend(0.1, 0.7, 0.6, 0.9);
    
    H_hodo_Tref_CUT->SetLineColor(kRed);
    H_hodo_Tref->GetXaxis()->SetTitle("Hodo Ref. Time [Channel]");
    H_hodo_Tref->Draw();
    H_hodo_Tref_CUT->Draw("sames");
    hT1_Line->SetLineColor(kBlue);
    hT1_Line->SetLineStyle(2);
    hT1_Line->SetLineWidth(3);
    hT1_Line->Draw();
    href_legend->AddEntry(hT1_Line, "ref. time cut (existing cut)", "l");
    href_legend->AddEntry(H_hodo_Tref_CUT, "multiplicity=1", "l");

    href_legend->Draw();
    
    hms_REF_Canv->cd(2);
    gPad->SetLogy();
    H_DC_Tref_CUT[0]->SetLineColor(kRed);
    H_DC_Tref[0]->GetXaxis()->SetTitle("DC Ref. Time [Channel]");
    H_DC_Tref[0]->GetXaxis()->SetNdivisions(6);
    H_DC_Tref[0]->Draw();
    H_DC_Tref_CUT[0]->Draw("sames");
    H_DC_Tref[1]->Draw("sames");
    H_DC_Tref[2]->Draw("sames");
    H_DC_Tref[3]->Draw("sames");
    hDCREF_Line->SetLineColor(kBlue);
    hDCREF_Line->SetLineStyle(2);
    hDCREF_Line->SetLineWidth(3);
    hDCREF_Line->Draw();
    
    hms_REF_Canv->cd(3);
    gPad->SetLogy();
    H_FADC_Tref_CUT->SetLineColor(kRed);
    H_FADC_Tref->GetXaxis()->SetTitle("FADC Ref. Time [Channel]");
    H_FADC_Tref->Draw();
    H_FADC_Tref_CUT->Draw("sames");
    hFADC_Line->SetLineColor(kBlue);
    hFADC_Line->SetLineStyle(2);
    hFADC_Line->SetLineWidth(3);
    hFADC_Line->Draw();
    
    hms_REF_Canv->SaveAs(Form("Time_cuts_refTime%d/HMS/refTime/hms_REFTime_cuts.pdf", run));
    
    
    //SHMS
    shms_REF_Canv = new TCanvas("REF Times", "SHMS REF TIMES",  1500, 500);
    shms_REF_Canv->Divide(3,1);

    phod_trefcut = read_ref_times("SHMS", "phodo_tdcrefcut");
    pdc_trefcut  = read_ref_times("SHMS", "pdc_tdcrefcut");
    padc_trefcut = read_ref_times("SHMS", "phodo_adcrefcut");
    
    
    pT2_Line = new TLine(abs(phod_trefcut), 0,    abs(phod_trefcut), P_hodo_Tref2->GetMaximum());
    pDCREF_Line = new TLine(abs(pdc_trefcut), 0,  abs(pdc_trefcut), P_DC_Tref[0]->GetMaximum());
    pFADC_Line = new TLine(abs(padc_trefcut), 0,  abs(padc_trefcut), P_FADC_Tref->GetMaximum());
    
    shms_REF_Canv->cd(1);
    gPad->SetLogy();
    auto pref_legend = new TLegend(0.1, 0.7, 0.6, 0.9);
    P_hodo_Tref1_CUT->SetLineColor(kRed);
    P_hodo_Tref2_CUT->SetLineColor(kRed); 
    P_hodo_Tref1->GetXaxis()->SetTitle("Hodo Ref. Time [Channel]"); 
    P_hodo_Tref1->Draw();
    P_hodo_Tref2->Draw("sames");
    P_hodo_Tref1_CUT->Draw("sames");
    P_hodo_Tref2_CUT->Draw("sames");  
    pT2_Line->SetLineColor(kBlue);
    pT2_Line->SetLineStyle(2);
    pT2_Line->SetLineWidth(3);
    pT2_Line->Draw();
    pref_legend->AddEntry(pT2_Line, "ref. time (existing cut)", "l");
    pref_legend->AddEntry(P_hodo_Tref2_CUT, "multiplicity=1", "l");
    pref_legend->Draw();
    
    shms_REF_Canv->cd(2);
    gPad->SetLogy();
    P_DC_Tref[0]->GetXaxis()->SetTitle("DC Ref. Time [Channel]"); 
    P_DC_Tref[0]->GetXaxis()->SetNdivisions(6); 
    for(Int_t iref=0; iref<10; iref++)
      {
	P_DC_Tref_CUT[iref]->SetLineColor(kRed);
	
	P_DC_Tref[iref]->Draw("sames");
	P_DC_Tref_CUT[iref]->Draw("sames");
      }
    pDCREF_Line->SetLineColor(kBlue);
    pDCREF_Line->SetLineStyle(2);
    pDCREF_Line->SetLineWidth(3);
    pDCREF_Line->Draw();
    
    shms_REF_Canv->cd(3);
    gPad->SetLogy();
    P_FADC_Tref_CUT->SetLineColor(kRed);
    P_FADC_Tref->GetXaxis()->SetTitle("FADC Ref. Time [Channel]"); 
    P_FADC_Tref->Draw();
    P_FADC_Tref_CUT->Draw("sames"); 
    pFADC_Line->SetLineColor(kBlue);
    pFADC_Line->SetLineStyle(2);
    pFADC_Line->SetLineWidth(3);
    pFADC_Line->Draw();
    
    shms_REF_Canv->SaveAs(Form("Time_cuts_refTime%d/SHMS/refTime/shms_REFTime_cuts.pdf", run));

    //Write REF TIME Histograms to ROOT file
    outROOT->Write();
    outROOT->Close();

 
  }

  else{
    
    cout << "Setting Up Canvases" << endl;
    //-----Setting up Detector Time WIndows----
    
    double cw, ch;
    cw = 6000;
    ch = 4000;
    //TRG Detector
    pTRG_Canv = new TCanvas("pTRIG_RawTimes", "pTRIG Raw TDC Times", 1500, 500);
    pTRG_Canv->Divide(2,3);
    
    
    /*
    //Set Min/Max Line Limits
    ptrg1r1_LineMin = new TLine(ptrg1r1_tWinMin, 0, ptrg1r1_tWinMin, pTrig1_ROC1_rawTdcTime->GetMaximum());
    ptrg1r1_LineMax = new TLine(ptrg1r1_tWinMax, 0, ptrg1r1_tWinMax, pTrig1_ROC1_rawTdcTime->GetMaximum());
    
    ptrg1r2_LineMin = new TLine(ptrg1r2_tWinMin, 0, ptrg1r2_tWinMin, pTrig1_ROC2_rawTdcTime->GetMaximum());
    ptrg1r2_LineMax = new TLine(ptrg1r2_tWinMax, 0, ptrg1r2_tWinMax, pTrig1_ROC2_rawTdcTime->GetMaximum());

    ptrg4r1_LineMin = new TLine(ptrg4r1_tWinMin, 0, ptrg4r1_tWinMin, pTrig4_ROC1_rawTdcTime->GetMaximum());
    ptrg4r1_LineMax = new TLine(ptrg4r1_tWinMax, 0, ptrg4r1_tWinMax, pTrig4_ROC1_rawTdcTime->GetMaximum());
  
    ptrg4r2_LineMin = new TLine(ptrg4r2_tWinMin, 0, ptrg4r2_tWinMin, pTrig4_ROC2_rawTdcTime->GetMaximum());
    ptrg4r2_LineMax = new TLine(ptrg4r2_tWinMax, 0, ptrg4r2_tWinMax, pTrig4_ROC2_rawTdcTime->GetMaximum());
  
    ptrg1r1_LineMin->SetLineColor(kBlack);
    ptrg1r1_LineMax->SetLineColor(kBlack);
    ptrg1r2_LineMin->SetLineColor(kBlack);
    ptrg1r2_LineMax->SetLineColor(kBlack);
    ptrg4r1_LineMin->SetLineColor(kBlack);
    ptrg4r1_LineMax->SetLineColor(kBlack);
    ptrg4r2_LineMin->SetLineColor(kBlack);
    ptrg4r2_LineMax->SetLineColor(kBlack);
    
    ptrg1r1_LineMin->SetLineStyle(2);                                                                                                                                      
    ptrg1r1_LineMax->SetLineStyle(2);                                                                                                                                      
    ptrg1r2_LineMin->SetLineStyle(2);                                                                                                                                      
    ptrg1r2_LineMax->SetLineStyle(2);                                                                                                                                        
    ptrg4r1_LineMin->SetLineStyle(2);                                                                                                                                       
    ptrg4r1_LineMax->SetLineStyle(2);                                                                                                                                           
    ptrg4r2_LineMin->SetLineStyle(2);                                                                                                                                            
    ptrg4r2_LineMax->SetLineStyle(2);                                                                                                                                          
    
    
    ptrg1r1_LineMin->SetLineWidth(3);                                                                                                                          
    ptrg1r1_LineMax->SetLineWidth(3);                                                                                                                                           
    ptrg1r2_LineMin->SetLineWidth(3);                                                                                                                                        
    ptrg1r2_LineMax->SetLineWidth(3);                                                                                                                          
    ptrg4r1_LineMin->SetLineWidth(3);                                                                                                                                 
    ptrg4r1_LineMax->SetLineWidth(3);                                                                                                                                          
    ptrg4r2_LineMin->SetLineWidth(3);                                                                                                                                      
    ptrg4r2_LineMax->SetLineWidth(3);  
    */
    
    pTRG_Canv->cd(1);
    gPad->SetLogy();
    pTrig1_ROC1_rawTdcTime->SetLineStyle(1);
    pTrig1_ROC2_rawTdcTime->SetLineStyle(2);
    pTrig1_ROC1_rawTdcTime->Draw();
    pTrig2_ROC1_rawTdcTime->Draw("same");

    
    pTRG_Canv->cd(2);
    gPad->SetLogy();
    pTrig2_ROC1_rawTdcTime->SetLineStyle(1);
    pTrig2_ROC2_rawTdcTime->SetLineStyle(2);
    pTrig2_ROC1_rawTdcTime->Draw();
    pTrig2_ROC2_rawTdcTime->Draw("same");

    
    pTRG_Canv->cd(3);
    gPad->SetLogy();
    pTrig3_ROC1_rawTdcTime->SetLineStyle(1);
    pTrig3_ROC2_rawTdcTime->SetLineStyle(2);
    pTrig3_ROC1_rawTdcTime->Draw();
    pTrig3_ROC2_rawTdcTime->Draw("same");

    
    pTRG_Canv->cd(4);
    gPad->SetLogy();
    pTrig4_ROC1_rawTdcTime->SetLineStyle(1);
    pTrig4_ROC2_rawTdcTime->SetLineStyle(2);
    pTrig4_ROC1_rawTdcTime->Draw();
    pTrig4_ROC2_rawTdcTime->Draw("same");
  
    pTRG_Canv->cd(5);
    gPad->SetLogy();
    pEDTM_rawTdcTime->SetLineStyle(1);
    pEDTM_rawTdcTime->Draw();

    pTRG_Canv->cd(6);
    auto tc_legend = new TLegend(0.1, 0.7, 0.6, 0.9);
    tc_legend->AddEntry(pTrig4_ROC1_rawTdcTime, "ROC1", "l");	 
    tc_legend->AddEntry(pTrig4_ROC2_rawTdcTime, "ROC2", "l");	 
    tc_legend->SetTextSize(0.1);
    tc_legend->Draw();

    pTRG_Canv->SaveAs(Form("Time_cuts_tWinSet%d/tcoin_trg_tWin.pdf",run));
  
  //===========
  //Cherenkovs
  //===========
  
  //HMS
  hCer_Canv = new TCanvas("hCer_ADC:TDC Time Diff", "HMS Cherenkov ADC:TDC Time Diff", 1500, 500);
  hCer_Canv->Divide(2,1);
  
  //SHMS Heavy Gas Cherenkov
  phgCer_Canv = new TCanvas("pHGCer_ADC:TDC Time Diff", "SHMS Heavy Gas Cherenkov ADC:TDC Time Diff", 1500, 1500);
  phgCer_Canv->Divide(2,2);
  
  //SHMS Noble Gas Cherenkov
  pngCer_Canv = new TCanvas("pNGCer_ADC:TDC Time Diff", "SHMS Noble Gas Cherenkov ADC:TDC Time Diff", 1500, 1500);
  pngCer_Canv->Divide(2,2);
  
  
  
  //Loop over Chernkovs PMTs
  for (Int_t ipmt = 0; ipmt < 4; ipmt++ )
    {
      
      //HMS Cherenkov
      if(ipmt < 2)
	{
	  
	  
	  hCer_tWinMin[ipmt] = GetParam(hcer_param_fname.Data(), "hcer_adcTimeWindowMin", ipmt, 0, 2);
	  hCer_tWinMax[ipmt] = GetParam(hcer_param_fname.Data(), "hcer_adcTimeWindowMax", ipmt, 0, 2);
	  

	  //Set Min/Max Line Limits
	  hCER_LineMin[ipmt] = new TLine(hCer_tWinMin[ipmt], 0, hCer_tWinMin[ipmt], H_cer_TdcAdcTimeDiff[ipmt]->GetMaximum());
	  hCER_LineMax[ipmt] = new TLine(hCer_tWinMax[ipmt], 0, hCer_tWinMax[ipmt], H_cer_TdcAdcTimeDiff[ipmt]->GetMaximum());

	  hCER_LineMin[ipmt]->SetLineColor(kBlue);
	  hCER_LineMax[ipmt]->SetLineColor(kBlue);
	  	  
	  hCER_LineMin[ipmt]->SetLineStyle(2);
	  hCER_LineMax[ipmt]->SetLineStyle(2);

	  
	  hCer_Canv->cd(ipmt+1);
	  gPad->SetLogy();
	  H_cer_TdcAdcTimeDiff_CUT[ipmt]->SetLineColor(kRed);
	  H_cer_TdcAdcTimeDiff[ipmt]->Draw();
	  H_cer_TdcAdcTimeDiff_CUT[ipmt]->Draw("sames");
	  hCER_LineMin[ipmt]->Draw();
	  hCER_LineMax[ipmt]->Draw();
	 
	  
	  if(ipmt==0){
	    
	    auto hcer_legend = new TLegend(0.1, 0.8, 0.6, 0.9);
	    hcer_legend->AddEntry(hCER_LineMin[ipmt], "existing cut", "l");	 
	    hcer_legend->SetTextSize(0.05);
	    hcer_legend->Draw();
	  
	  }
	  
       
	}
     
      
      //======================
      // HEAVY GAS CHERENKOV
      //======================
      
      
      phgcer_tWinMin[ipmt] = GetParam(phgcer_param_fname.Data(), "phgcer_adcTimeWindowMin", ipmt, 0, 4);
      phgcer_tWinMax[ipmt] = GetParam(phgcer_param_fname.Data(), "phgcer_adcTimeWindowMax", ipmt, 0, 4);
      
    
      //Set Min/Max Line Limits
      phgcer_LineMin[ipmt] = new TLine(phgcer_tWinMin[ipmt], 0, phgcer_tWinMin[ipmt], P_hgcer_TdcAdcTimeDiff[ipmt]->GetMaximum());
      phgcer_LineMax[ipmt] = new TLine(phgcer_tWinMax[ipmt], 0, phgcer_tWinMax[ipmt], P_hgcer_TdcAdcTimeDiff[ipmt]->GetMaximum());
      
      phgcer_LineMin[ipmt]->SetLineColor(kBlue);
      phgcer_LineMax[ipmt]->SetLineColor(kBlue);
      
      phgcer_LineMin[ipmt]->SetLineStyle(2);
      phgcer_LineMax[ipmt]->SetLineStyle(2);
      
      phgcer_LineMin[ipmt]->SetLineWidth(2);
      phgcer_LineMax[ipmt]->SetLineWidth(2);

      phgCer_Canv->cd(ipmt+1);
      gPad->SetLogy();
      P_hgcer_TdcAdcTimeDiff_CUT[ipmt]->SetLineColor(kRed);
      P_hgcer_TdcAdcTimeDiff[ipmt]->Draw();
      P_hgcer_TdcAdcTimeDiff_CUT[ipmt]->Draw("sames");
      phgcer_LineMin[ipmt]->Draw();
      phgcer_LineMax[ipmt]->Draw();

      if(ipmt==0){
	auto phgcer_legend = new TLegend(0.1, 0.8, 0.6, 0.9);
	phgcer_legend->AddEntry(phgcer_LineMin[ipmt], "existing cut", "l");       
	phgcer_legend->SetTextSize(0.05);
	phgcer_legend->Draw();
      }
      
      
    
      //===========================
      //====NOBLE GAS CHERENKOV====
      //===========================
      
      pngcer_tWinMin[ipmt] = GetParam(pngcer_param_fname.Data(), "pngcer_adcTimeWindowMin", ipmt, 0, 4);
      pngcer_tWinMax[ipmt] = GetParam(pngcer_param_fname.Data(), "pngcer_adcTimeWindowMax", ipmt, 0, 4);
      
      //Set Min/Max Line Limits
      pngcer_LineMin[ipmt] = new TLine(pngcer_tWinMin[ipmt], 0, pngcer_tWinMin[ipmt], P_ngcer_TdcAdcTimeDiff[ipmt]->GetMaximum());
      pngcer_LineMax[ipmt] = new TLine(pngcer_tWinMax[ipmt], 0, pngcer_tWinMax[ipmt], P_ngcer_TdcAdcTimeDiff[ipmt]->GetMaximum());
      
      pngcer_LineMin[ipmt]->SetLineColor(kBlue);
      pngcer_LineMax[ipmt]->SetLineColor(kBlue);
      
      pngcer_LineMin[ipmt]->SetLineStyle(2);
      pngcer_LineMax[ipmt]->SetLineStyle(2);
      
      pngcer_LineMin[ipmt]->SetLineWidth(2);
      pngcer_LineMax[ipmt]->SetLineWidth(2);
      
      pngCer_Canv->cd(ipmt+1);
      gPad->SetLogy();
      P_ngcer_TdcAdcTimeDiff_CUT[ipmt]->SetLineColor(kRed);
      P_ngcer_TdcAdcTimeDiff[ipmt]->Draw();
      P_ngcer_TdcAdcTimeDiff_CUT[ipmt]->Draw("sames");
      pngcer_LineMin[ipmt]->Draw();
      pngcer_LineMax[ipmt]->Draw();

      if(ipmt==0){
	auto pngcer_legend = new TLegend(0.1, 0.8, 0.6, 0.9);
	pngcer_legend->AddEntry(pngcer_LineMin[ipmt], "existing cut", "l");	
	pngcer_legend->SetTextSize(0.05);   
	pngcer_legend->Draw();
      }
	    
      
   

    } //end loop over cer pmts
  
  //Save CHerenkovs to Canvas
  hCer_Canv->SaveAs(Form("Time_cuts_tWinSet%d/HMS/CER/hCER_timeWindow.pdf",run));
  phgCer_Canv->SaveAs(Form("Time_cuts_tWinSet%d/SHMS/CER/pHGCER_timeWindow.pdf",run));
  pngCer_Canv->SaveAs(Form("Time_cuts_tWinSet%d/SHMS/CER/pNGCER_timeWindow.pdf",run));
  
 
  //==================
  //==Drift Chambers==
  //==================
  
  //HMS
  hdcCanv = new TCanvas("HMS DC Raw Times", "HMS DC Raw Times", 1500, 500);
  hdcCanv->Divide(6,2);
  
  //SHMS
  pdcCanv = new TCanvas("SHMS DC Raw Times", "SHMS DC Raw Times", 1500, 500);
  pdcCanv->Divide(6,2);
  
  
  //Loop over DC planes
  for (Int_t npl = 0; npl < 12; npl++ )
    {

      // read dc time window parameters
      if(npl<=5){
	hDC_tWinMin[npl] = GetParam(hdc_param_fname.Data(), "hdc_tdc_min_win", npl, 0, 5);
	hDC_tWinMax[npl] = GetParam(hdc_param_fname.Data(), "hdc_tdc_max_win", npl, 0, 5);

      }
      else{
	hDC_tWinMin[npl] = GetParam(hdc_param_fname.Data(), "hdc_tdc_min_win", npl-6, 1, 5);
	hDC_tWinMax[npl] = GetParam(hdc_param_fname.Data(), "hdc_tdc_max_win", npl-6, 1, 5);
      }
      
      hdc_LineMin[npl] = new TLine(hDC_tWinMin[npl], 0, hDC_tWinMin[npl], H_dc_rawTDC[npl]->GetMaximum());
      hdc_LineMax[npl] = new TLine(hDC_tWinMax[npl], 0, hDC_tWinMax[npl], H_dc_rawTDC[npl]->GetMaximum());

      hdc_LineMin[npl]->SetLineColor(kBlue);
      hdc_LineMax[npl]->SetLineColor(kBlue);
      
      hdc_LineMin[npl]->SetLineStyle(2);
      hdc_LineMax[npl]->SetLineStyle(2);

      hdcCanv->cd(npl+1);
      hdcCanv->SetWindowSize(3000, 1000);    
      
      gPad->SetLogy();
      H_dc_rawTDC_CUT[npl]->SetLineColor(kRed);
      H_dc_rawTDC[npl]->SetNdivisions(5);
      
      H_dc_rawTDC[npl]->GetXaxis()->SetLabelSize(0.05);                                                                                                                          
      H_dc_rawTDC[npl]->GetXaxis()->SetTickSize(0.05);                                                                                                                           
      H_dc_rawTDC[npl]->GetXaxis()->SetTitle("Raw TDC Time [Channel]");                                                                                                          
      H_dc_rawTDC[npl]->GetXaxis()->SetTitleSize(0.05);                                                                                                                          
      H_dc_rawTDC[npl]->GetXaxis()->CenterTitle();                                                                                                                               
      H_dc_rawTDC[npl]->GetYaxis()->SetLabelSize(0.05);                                                                                                                          
      H_dc_rawTDC[npl]->GetYaxis()->SetTitleSize(0.05);                                                                                                                          
      H_dc_rawTDC[npl]->GetYaxis()->SetTickSize(0.05);  

      H_dc_rawTDC[npl]->Draw();
      //H_dc_rawTDC_CUT[npl]->SetNdivisions(5); 
      H_dc_rawTDC_CUT[npl]->Draw("sames");
      hdc_LineMin[npl]->Draw();
      hdc_LineMax[npl]->Draw();

      if(npl==0){
	auto hdc_legend = new TLegend(0.1, 0.7, 0.6, 0.9);
	hdc_legend->AddEntry(hdc_LineMin[npl], "existing cut", "l");	
	hdc_legend->SetTextSize(0.05);
	hdc_legend->Draw();
      }
	    
      //SHMS

      // read dc time window parameters
      if(npl<=5){
	pDC_tWinMin[npl] = GetParam(pdc_param_fname.Data(), "pdc_tdc_min_win", npl, 0, 5);
	pDC_tWinMax[npl] = GetParam(pdc_param_fname.Data(), "pdc_tdc_max_win", npl, 0, 5);

      }
      else{
	pDC_tWinMin[npl] = GetParam(pdc_param_fname.Data(), "pdc_tdc_min_win", npl-6, 1, 5);
	pDC_tWinMax[npl] = GetParam(pdc_param_fname.Data(), "pdc_tdc_max_win", npl-6, 1, 5);
      }
      
      pdc_LineMin[npl] = new TLine(pDC_tWinMin[npl], 0, pDC_tWinMin[npl], P_dc_rawTDC[npl]->GetMaximum());
      pdc_LineMax[npl] = new TLine(pDC_tWinMax[npl], 0, pDC_tWinMax[npl], P_dc_rawTDC[npl]->GetMaximum());
      
      pdc_LineMin[npl]->SetLineColor(kBlue);
      pdc_LineMax[npl]->SetLineColor(kBlue);
           
      pdc_LineMin[npl]->SetLineStyle(2);
      pdc_LineMax[npl]->SetLineStyle(2);
      
      pdcCanv->cd(npl+1);
      pdcCanv->SetWindowSize(3000, 1000); 
      
      gPad->SetLogy();
      P_dc_rawTDC_CUT[npl]->SetLineColor(kRed);
      P_dc_rawTDC[npl]->GetXaxis()->SetNdivisions(5);
      P_dc_rawTDC[npl]->GetXaxis()->SetLabelSize(0.05);                                                                                                                                             
      P_dc_rawTDC[npl]->GetXaxis()->SetTickSize(0.05);                                                                                                                                                 
      P_dc_rawTDC[npl]->GetXaxis()->SetTitle("Raw TDC Time [Channel]");                                                                                                                                
      P_dc_rawTDC[npl]->GetXaxis()->SetTitleSize(0.05);                                                                                                                                                
      P_dc_rawTDC[npl]->GetXaxis()->CenterTitle();                                                                                                                                                      
      P_dc_rawTDC[npl]->GetYaxis()->SetLabelSize(0.05);                                                                                                                                                
      P_dc_rawTDC[npl]->GetYaxis()->SetTitleSize(0.05);                                                                                                                                               
      P_dc_rawTDC[npl]->GetYaxis()->SetTickSize(0.05); 
      
      P_dc_rawTDC[npl]->Draw();
      //P_dc_rawTDC_CUT[npl]->GetXaxis()->SetNdivisions(25); 
      P_dc_rawTDC_CUT[npl]->Draw("sames");
      pdc_LineMin[npl]->Draw();
      pdc_LineMax[npl]->Draw();

      if(npl==0){
	auto pdc_legend = new TLegend(0.1, 0.7, 0.6, 0.9);
	pdc_legend->AddEntry(pdc_LineMin[npl], "existing cut", "l");
	pdc_legend->SetTextSize(0.04);
	pdc_legend->Draw();
      }
      
    } //end dc plane loop
  
  
  //Save DC to Canvas
  hdcCanv->SaveAs(Form("Time_cuts_tWinSet%d/HMS/DC/hDC_rawTDC_window.pdf",run));
  pdcCanv->SaveAs(Form("Time_cuts_tWinSet%d/SHMS/DC/pDC_rawTDC_window.pdf",run));
  
  //===========================
  //HODOSCOPES / CALORIMETERS
  //===========================
  
  //Loop over planes
  for (Int_t npl = 0; npl < hod_PLANES; npl++ )
    {      
      
      //Loop over plane side
      for (Int_t iside = 0; iside < SIDES; iside++)
	{  
	  
	  //Define HMS Hodo Canv
	  hhodoCanv[npl][iside] = new TCanvas(Form("hhodo_TDC:ADC Time Diff. Hod Plane %s%s", hod_pl_names[npl].Data(), side_names[iside].Data()), Form("HMS Hodo TDC-ADC Time Diff, Plane %s%s", hod_pl_names[npl].Data(), side_names[iside].Data()),  cw, ch);
	  if (debug) hhodo_tdcCanv[npl][iside] = new TCanvas(Form("hhodo_TDC UnCorr Time Hod Plane %s%s", hod_pl_names[npl].Data(), side_names[iside].Data()), Form("HMS Hodo TDC Time UnCorr, Plane %s%s", hod_pl_names[npl].Data(), side_names[iside].Data()), cw, ch);

	  
	  //Define SHMS Hodo Canv
	  phodoCanv[npl][iside] = new TCanvas(Form("phodo_TDC:ADC Time Diff. Hod Plane %s%s", hod_pl_names[npl].Data(), side_names[iside].Data()), Form("SHMS Hodo TDC-ADC Time Diff, Plane %s%s", hod_pl_names[npl].Data(), side_names[iside].Data()),  cw, ch);
	  if (debug) phodo_tdcCanv[npl][iside] = new TCanvas(Form("phodo_TDC UnCorr Time Hod Plane %s%s", hod_pl_names[npl].Data(), side_names[iside].Data()), Form("SHMS Hodo TDC Time UnCorr, Plane %s%s", hod_pl_names[npl].Data(), side_names[iside].Data()),  cw, ch);

	  
	  //Define HMS Calorimeter Canvas for all planes
	  if (!(npl==2&&iside==1) && !(npl==3&&iside==1)){
	    hcaloCanv[npl][iside] = new TCanvas(Form("hcalo_TDC:ADC Time Diff. Cal Plane %s%s", cal_pl_names[npl].Data(), cal_side_names[iside].Data()), Form("Calo TDC:ADC Time Diff, Plane %s %s", cal_pl_names[npl].Data(), cal_side_names[iside].Data()),  cw, ch);
	    hcaloCanv[npl][iside]->Divide(5,3);	     
	  }
	  
	  
	  //Define SHMS PreShower and Calorimeter Canvas
	  if(npl==0)
	    {
	      pPrshCanv[iside] =  new TCanvas(Form("pPrSh_TDC:ADC Time Diff %s", cal_side_names[iside].Data()), Form("SHMS PreShower TDC:ADC Time Diff %s",  cal_side_names[iside].Data()),  cw, ch);
	      if(debug) pPrshAdcCanv[iside] =  new TCanvas(Form("pPrSh_ADC Time %s", cal_side_names[iside].Data()), Form("SHMS PreShower ADC Time %s",  cal_side_names[iside].Data()),  cw, ch);

	    }
	  
	  
	  //Divide HMS Hodo Canvas Accordingly
	  if(npl == 0 || npl == 2)
	    {
	      hhodoCanv[npl][iside]->Divide(4,4);
	      if(debug) hhodo_tdcCanv[npl][iside]->Divide(4,4);

	    }
	  
	  else if (npl==1 || npl==3)
	    {
	      hhodoCanv[npl][iside]->Divide(5,2);
	      if(debug) hhodo_tdcCanv[npl][iside]->Divide(5,2);
	    }
	  
	  
	  //Divide SHMS Hodo Canvas Accordingly
	  if(npl == 0 || npl == 1 || npl==2)
	    {
	      phodoCanv[npl][iside]->Divide(7,2);
	      if(debug) phodo_tdcCanv[npl][iside]->Divide(7,2);

	    }
	  
	  else if (npl==3)
	    {
	      phodoCanv[npl][iside]->Divide(7,3);
	      if(debug) phodo_tdcCanv[npl][iside]->Divide(7,3);

	    }
	  
	  
	  //Divide SHMS PreSh / Calo Canvas Accordingly
	  if(npl==0)
	    {
	      
	      pPrshCanv[iside]->Divide(7,2);
	      if(debug) pPrshAdcCanv[iside]->Divide(7,2);

	    }
	  
	  
	  
	  //Loop over HMS HODO PMTs
	  for (Int_t ipmt = 0; ipmt < hmaxPMT[npl]; ipmt++)
	    {

	      // -------- Read the existing min/max parameters HMS Hodo TdcAdcDiffTime (read from existinf hhodo_cuts.param file)	      

	      hhodo_tWinMin_old[npl][iside][ipmt] = GetParam(hhodo_param_fname.Data(), "hhodo_PosAdcTimeWindowMin", npl, ipmt, 16);
	      hhodo_tWinMax_old[npl][iside][ipmt] = GetParam(hhodo_param_fname.Data(), "hhodo_PosAdcTimeWindowMax", npl, ipmt, 16);
	      
	      hhod_LineMin_old[npl][iside][ipmt] = new TLine(hhodo_tWinMin_old[npl][iside][ipmt], 0, hhodo_tWinMin_old[npl][iside][ipmt], H_hod_TdcAdcTimeDiff[npl][iside][ipmt]->GetMaximum());
	      hhod_LineMax_old[npl][iside][ipmt] = new TLine(hhodo_tWinMax_old[npl][iside][ipmt], 0, hhodo_tWinMax_old[npl][iside][ipmt], H_hod_TdcAdcTimeDiff[npl][iside][ipmt]->GetMaximum());

	      hhod_LineMin_old[npl][iside][ipmt]->SetLineColor(kBlue);
	      hhod_LineMax_old[npl][iside][ipmt]->SetLineColor(kBlue);
	      
	      hhod_LineMin_old[npl][iside][ipmt]->SetLineStyle(1);
	      hhod_LineMax_old[npl][iside][ipmt]->SetLineStyle(1);
	      
	      // --------------------
	      
	      //Get Mean and Sigma
	      binmax = H_hod_TdcAdcTimeDiff_CUT[npl][iside][ipmt]->GetMaximumBin();

	      mean = H_hod_TdcAdcTimeDiff_CUT[npl][iside][ipmt]->GetXaxis()->GetBinCenter(binmax);
	      sig =  H_hod_TdcAdcTimeDiff_CUT[npl][iside][ipmt]->GetStdDev();
	      
	      //Set Time Window Cuts 
	      hhodo_tWinMin[npl][iside][ipmt] = mean - hhod_nSig;
	      hhodo_tWinMax[npl][iside][ipmt] = mean + hhod_nSig;
	            
	      
	      //Set Min/Max Line Limits
	      if( new_line_flg ) {
	      hhod_LineMin[npl][iside][ipmt] = new TLine(hhodo_tWinMin[npl][iside][ipmt], 0, hhodo_tWinMin[npl][iside][ipmt], H_hod_TdcAdcTimeDiff[npl][iside][ipmt]->GetMaximum());
	      hhod_LineMax[npl][iside][ipmt] = new TLine(hhodo_tWinMax[npl][iside][ipmt], 0, hhodo_tWinMax[npl][iside][ipmt], H_hod_TdcAdcTimeDiff[npl][iside][ipmt]->GetMaximum());

	      hhod_LineMin[npl][iside][ipmt]->SetLineColor(kGreen+3);
	      hhod_LineMax[npl][iside][ipmt]->SetLineColor(kGreen+3);
	      
	      hhod_LineMin[npl][iside][ipmt]->SetLineStyle(2);
	      hhod_LineMax[npl][iside][ipmt]->SetLineStyle(2);
	      }
	      cout << "pass1" << endl;
	      hhodoCanv[npl][iside]->cd(ipmt+1);
	      hhodoCanv[npl][iside]->SetWindowSize(4500, 3500);
	      
	      gPad->SetLogy();
    
	      H_hod_TdcAdcTimeDiff_CUT[npl][iside][ipmt]->SetLineColor(kRed);
	      // set label/title font size
	      H_hod_TdcAdcTimeDiff[npl][iside][ipmt]->GetXaxis()->SetNdivisions(10);
	      H_hod_TdcAdcTimeDiff[npl][iside][ipmt]->GetXaxis()->SetLabelSize(0.05);
	      H_hod_TdcAdcTimeDiff[npl][iside][ipmt]->GetXaxis()->SetTickSize(0.05);
	      H_hod_TdcAdcTimeDiff[npl][iside][ipmt]->GetXaxis()->SetTitle("Good Tdc-Adc Time [ns]");
	      H_hod_TdcAdcTimeDiff[npl][iside][ipmt]->GetXaxis()->SetTitleSize(0.05); 
	      H_hod_TdcAdcTimeDiff[npl][iside][ipmt]->GetXaxis()->CenterTitle();
	      H_hod_TdcAdcTimeDiff[npl][iside][ipmt]->GetYaxis()->SetLabelSize(0.05);
	      H_hod_TdcAdcTimeDiff[npl][iside][ipmt]->GetYaxis()->SetTitleSize(0.05);
	      H_hod_TdcAdcTimeDiff[npl][iside][ipmt]->GetYaxis()->SetTickSize(0.05);  
	    


	      H_hod_TdcAdcTimeDiff[npl][iside][ipmt]->Draw();
	      H_hod_TdcAdcTimeDiff_CUT[npl][iside][ipmt]->Draw("sames");
	      
	      if(new_line_flg){ 
		hhod_LineMin[npl][iside][ipmt]->Draw();
		hhod_LineMax[npl][iside][ipmt]->Draw();
	      }
	      // draw existing min/max cuts
	      hhod_LineMin_old[npl][iside][ipmt]->Draw();
	      hhod_LineMax_old[npl][iside][ipmt]->Draw();

	      // add legend (only necessary on single side
	      if((iside==0 || iside==1) && ipmt==0){
		auto hhodo_legend = new TLegend(0.1, 0.7, 0.8, 0.9);
		hhodo_legend->AddEntry(hhod_LineMin_old[npl][iside][ipmt], "existing cut", "l");
		if(new_line_flg) hhodo_legend->AddEntry(hhod_LineMin[npl][iside][ipmt], "new cut", "l");
		hhodo_legend->Draw();
	      }
	      
	      if(debug) {
		
		hhodo_tdcCanv[npl][iside]->cd(ipmt+1);
		hhodo_tdcCanv[npl][iside]->SetWindowSize(4500,3500);
	      }
	      gPad->SetLogy();
	      if(debug) {
		
		// set label/title font size
		H_hod_TdcTimeUnCorr[npl][iside][ipmt]->GetXaxis()->SetNdivisions(10);                                                                                                  
		H_hod_TdcTimeUnCorr[npl][iside][ipmt]->GetXaxis()->SetLabelSize(0.05);                                                                                                   
		H_hod_TdcTimeUnCorr[npl][iside][ipmt]->GetXaxis()->SetTickSize(0.05);                                                                                                             
		H_hod_TdcTimeUnCorr[npl][iside][ipmt]->GetXaxis()->SetTitle("Good Tdc Time UnCorr [Channel]");                                                                                   
		H_hod_TdcTimeUnCorr[npl][iside][ipmt]->GetXaxis()->SetTitleSize(0.05);                                                                               
		H_hod_TdcTimeUnCorr[npl][iside][ipmt]->GetYaxis()->SetNdivisions(10);                                                                                                             
		H_hod_TdcTimeUnCorr[npl][iside][ipmt]->GetXaxis()->CenterTitle();                                                                                                            
		H_hod_TdcTimeUnCorr[npl][iside][ipmt]->GetYaxis()->SetLabelSize(0.05);                                                                                                  
		H_hod_TdcTimeUnCorr[npl][iside][ipmt]->GetYaxis()->SetTitleSize(0.05);                                                                 
		H_hod_TdcTimeUnCorr[npl][iside][ipmt]->GetYaxis()->SetTickSize(0.05);  
		
		H_hod_TdcTimeUnCorr[npl][iside][ipmt]->Draw();
	      }
	      

	    } //end hms hodo pmt loop
	  
	  //Loop over SHMS HODO PMTs
	  for (Int_t ipmt = 0; ipmt < pmaxPMT[npl]; ipmt++)
	    {


	      // -------- Read the existing min/max parameters HMS Hodo TdcAdcDiffTime (read from existinf hhodo_cuts.param file)	      

	      phodo_tWinMin_old[npl][iside][ipmt] = GetParam(phodo_param_fname.Data(), "phodo_PosAdcTimeWindowMin", npl, ipmt, 21);
	      phodo_tWinMax_old[npl][iside][ipmt] = GetParam(phodo_param_fname.Data(), "phodo_PosAdcTimeWindowMax", npl, ipmt, 21);
	      
	      phod_LineMin_old[npl][iside][ipmt] = new TLine(phodo_tWinMin_old[npl][iside][ipmt], 0, phodo_tWinMin_old[npl][iside][ipmt], P_hod_TdcAdcTimeDiff[npl][iside][ipmt]->GetMaximum());
	      phod_LineMax_old[npl][iside][ipmt] = new TLine(phodo_tWinMax_old[npl][iside][ipmt], 0, phodo_tWinMax_old[npl][iside][ipmt], P_hod_TdcAdcTimeDiff[npl][iside][ipmt]->GetMaximum());

	      phod_LineMin_old[npl][iside][ipmt]->SetLineColor(kBlue);
	      phod_LineMax_old[npl][iside][ipmt]->SetLineColor(kBlue);
	      
	      phod_LineMin_old[npl][iside][ipmt]->SetLineStyle(1);
	      phod_LineMax_old[npl][iside][ipmt]->SetLineStyle(1);
	      
	      // --------------------
	      
	      //Get Mean and Sigma
	      binmax = P_hod_TdcAdcTimeDiff_CUT[npl][iside][ipmt]->GetMaximumBin();
	      mean = P_hod_TdcAdcTimeDiff_CUT[npl][iside][ipmt]->GetXaxis()->GetBinCenter(binmax);
	      sig =  P_hod_TdcAdcTimeDiff_CUT[npl][iside][ipmt]->GetStdDev();
	      
	      //Set Time Window Cuts
	      phodo_tWinMin[npl][iside][ipmt] = mean - phod_nSig;
	      phodo_tWinMax[npl][iside][ipmt] = mean + phod_nSig;
	      
	            
	      //Set Min/Max Line Limits
	      if(new_line_flg){ 
	      phod_LineMin[npl][iside][ipmt] = new TLine(phodo_tWinMin[npl][iside][ipmt], 0, phodo_tWinMin[npl][iside][ipmt], P_hod_TdcAdcTimeDiff[npl][iside][ipmt]->GetMaximum());
	      phod_LineMax[npl][iside][ipmt] = new TLine(phodo_tWinMax[npl][iside][ipmt], 0, phodo_tWinMax[npl][iside][ipmt], P_hod_TdcAdcTimeDiff[npl][iside][ipmt]->GetMaximum());

	      phod_LineMin[npl][iside][ipmt]->SetLineColor(kGreen+3);
	      phod_LineMax[npl][iside][ipmt]->SetLineColor(kGreen+3);
	      
	      phod_LineMin[npl][iside][ipmt]->SetLineStyle(2);
	      phod_LineMax[npl][iside][ipmt]->SetLineStyle(2);
	      }
	      cout << "pass2" << endl;  
	      phodoCanv[npl][iside]->cd(ipmt+1);
	      phodoCanv[npl][iside]->SetWindowSize(3000, 1000);
	      gPad->SetLogy();

	      
	      P_hod_TdcAdcTimeDiff_CUT[npl][iside][ipmt]->SetLineColor(kRed);

	      // set label/title font size
	      P_hod_TdcAdcTimeDiff[npl][iside][ipmt]->GetXaxis()->SetNdivisions(10);  
	      P_hod_TdcAdcTimeDiff[npl][iside][ipmt]->GetXaxis()->SetLabelSize(0.05); 
	      P_hod_TdcAdcTimeDiff[npl][iside][ipmt]->GetXaxis()->SetTickSize(0.05); 
	      P_hod_TdcAdcTimeDiff[npl][iside][ipmt]->GetXaxis()->SetTitle("Good Tdc-Adc Time [ns]");  
	      P_hod_TdcAdcTimeDiff[npl][iside][ipmt]->GetXaxis()->SetTitleSize(0.05);
	      P_hod_TdcAdcTimeDiff[npl][iside][ipmt]->GetYaxis()->SetNdivisions(10); 
	      P_hod_TdcAdcTimeDiff[npl][iside][ipmt]->GetXaxis()->CenterTitle();
	      P_hod_TdcAdcTimeDiff[npl][iside][ipmt]->GetYaxis()->SetLabelSize(0.05);
	      P_hod_TdcAdcTimeDiff[npl][iside][ipmt]->GetYaxis()->SetTitleSize(0.05);
	      P_hod_TdcAdcTimeDiff[npl][iside][ipmt]->GetYaxis()->SetTickSize(0.05); 


	      P_hod_TdcAdcTimeDiff[npl][iside][ipmt]->Draw();
	      P_hod_TdcAdcTimeDiff_CUT[npl][iside][ipmt]->Draw("sames");
	      if(new_line_flg){ 
	      phod_LineMin[npl][iside][ipmt]->Draw();
	      phod_LineMax[npl][iside][ipmt]->Draw();
	      }
	      // draw existing min/max cuts
	      phod_LineMin_old[npl][iside][ipmt]->Draw();
	      phod_LineMax_old[npl][iside][ipmt]->Draw();
	      
	      // add legend (only necessary on single side
	      if((iside==0 || iside==1) && ipmt==0){
		auto phodo_legend = new TLegend(0.1, 0.7, 0.8, 0.9);
		phodo_legend->AddEntry(phod_LineMin_old[npl][iside][ipmt], "existing cut", "l");
		if(new_line_flg) phodo_legend->AddEntry(phod_LineMin[npl][iside][ipmt],     "new cut", "l");	       
		phodo_legend->SetTextSize(0.08);
		phodo_legend->Draw();
	      }
	      
	      if(debug) {
		
		phodo_tdcCanv[npl][iside]->cd(ipmt+1);
		phodo_tdcCanv[npl][iside]->SetWindowSize(3000, 1000); 
	      }
	      gPad->SetLogy();
	      if(debug) {
		
		// set label/title font size                                                                                   
		P_hod_TdcTimeUnCorr[npl][iside][ipmt]->GetXaxis()->SetNdivisions(10);                                                                                                       
		P_hod_TdcTimeUnCorr[npl][iside][ipmt]->GetXaxis()->SetLabelSize(0.05);                                                                                                                
		P_hod_TdcTimeUnCorr[npl][iside][ipmt]->GetXaxis()->SetTickSize(0.05);                                                                                                           
		P_hod_TdcTimeUnCorr[npl][iside][ipmt]->GetXaxis()->SetTitle("Good Tdc Time [Channel]");                                                                                                
		P_hod_TdcTimeUnCorr[npl][iside][ipmt]->GetXaxis()->SetTitleSize(0.05);                                                                                                          
		P_hod_TdcTimeUnCorr[npl][iside][ipmt]->GetYaxis()->SetNdivisions(10);                                                                                                           
		P_hod_TdcTimeUnCorr[npl][iside][ipmt]->GetXaxis()->CenterTitle();                                                                                                                  
		P_hod_TdcTimeUnCorr[npl][iside][ipmt]->GetYaxis()->SetLabelSize(0.05);                                                                                                           
		P_hod_TdcTimeUnCorr[npl][iside][ipmt]->GetYaxis()->SetTitleSize(0.05);                                                                                                              
		P_hod_TdcTimeUnCorr[npl][iside][ipmt]->GetYaxis()->SetTickSize(0.05); 

		P_hod_TdcTimeUnCorr[npl][iside][ipmt]->Draw();
	      
	      }

	    } //end shms hodo pmt loop
	  
	  
	  //Loop over HMS Calorimeter pmts
	  for (Int_t ipmt = 0; ipmt < 13; ipmt++)
	    {

	      // -------- Read the existing min/max parameters HMS Cal TdcAdcDiffTime (read from existinf hcal_cuts.param file)
	      
	      if(iside==0){
		hCal_tWinMin_old[npl][iside][ipmt] = GetParam(hcal_param_fname.Data(), "hcal_pos_AdcTimeWindowMin", ipmt, npl, 4);
		hCal_tWinMax_old[npl][iside][ipmt] = GetParam(hcal_param_fname.Data(), "hcal_pos_AdcTimeWindowMax", ipmt, npl, 4);
	      }
	      else if(iside==1){
		hCal_tWinMin_old[npl][iside][ipmt] = GetParam(hcal_param_fname.Data(), "hcal_neg_AdcTimeWindowMin", ipmt, npl, 4);
		hCal_tWinMax_old[npl][iside][ipmt] = GetParam(hcal_param_fname.Data(), "hcal_neg_AdcTimeWindowMax", ipmt, npl, 4);
	      }
	      //Set Min/Max Line Limits
	      hcal_LineMin_old[npl][iside][ipmt] = new TLine(hCal_tWinMin_old[npl][iside][ipmt], 0, hCal_tWinMin_old[npl][iside][ipmt], H_cal_TdcAdcTimeDiff[npl][iside][ipmt]->GetMaximum());
	      hcal_LineMax_old[npl][iside][ipmt] = new TLine(hCal_tWinMax_old[npl][iside][ipmt], 0, hCal_tWinMax_old[npl][iside][ipmt], H_cal_TdcAdcTimeDiff[npl][iside][ipmt]->GetMaximum());

	      hcal_LineMin_old[npl][iside][ipmt]->SetLineColor(kBlue);
	      hcal_LineMax_old[npl][iside][ipmt]->SetLineColor(kBlue);
	      
	      hcal_LineMin_old[npl][iside][ipmt]->SetLineStyle(1);
	      hcal_LineMax_old[npl][iside][ipmt]->SetLineStyle(1);
	      
	      //-------------------------
	      
	      
	      //Get Mean and Sigma
	      binmax = H_cal_TdcAdcTimeDiff_CUT[npl][iside][ipmt]->GetMaximumBin();
	      mean = H_cal_TdcAdcTimeDiff_CUT[npl][iside][ipmt]->GetXaxis()->GetBinCenter(binmax);
	      sig =  H_cal_TdcAdcTimeDiff_CUT[npl][iside][ipmt]->GetStdDev();
	      
	      //Set Time Window Cuts
	      hCal_tWinMin[npl][iside][ipmt] = mean - hcal_nSig;
	      hCal_tWinMax[npl][iside][ipmt] = mean + hcal_nSig;                                                                                                          
		
	      //Set Min/Max Line Limits
	      if( new_line_flg ){
	      hcal_LineMin[npl][iside][ipmt] = new TLine(hCal_tWinMin[npl][iside][ipmt], 0, hCal_tWinMin[npl][iside][ipmt], H_cal_TdcAdcTimeDiff[npl][iside][ipmt]->GetMaximum());
	      hcal_LineMax[npl][iside][ipmt] = new TLine(hCal_tWinMax[npl][iside][ipmt], 0, hCal_tWinMax[npl][iside][ipmt], H_cal_TdcAdcTimeDiff[npl][iside][ipmt]->GetMaximum());

	      hcal_LineMin[npl][iside][ipmt]->SetLineColor(kGreen+3);
	      hcal_LineMax[npl][iside][ipmt]->SetLineColor(kGreen+3);
	      
	      hcal_LineMin[npl][iside][ipmt]->SetLineStyle(2);
	      hcal_LineMax[npl][iside][ipmt]->SetLineStyle(2);
	      }
	      cout << "pass3" << endl;  
	      // set label/title font size 
	      H_cal_TdcAdcTimeDiff[npl][iside][ipmt]->GetXaxis()->SetNdivisions(10);
	      H_cal_TdcAdcTimeDiff[npl][iside][ipmt]->GetXaxis()->SetLabelSize(0.05);
	      H_cal_TdcAdcTimeDiff[npl][iside][ipmt]->GetXaxis()->SetTickSize(0.05); 
	      H_cal_TdcAdcTimeDiff[npl][iside][ipmt]->GetXaxis()->SetTitle("Good Tdc-Adc Time [ns]");  
	      H_cal_TdcAdcTimeDiff[npl][iside][ipmt]->GetXaxis()->SetTitleSize(0.04);
	      H_cal_TdcAdcTimeDiff[npl][iside][ipmt]->GetXaxis()->CenterTitle();   
	      H_cal_TdcAdcTimeDiff[npl][iside][ipmt]->GetYaxis()->SetLabelSize(0.05);
	      H_cal_TdcAdcTimeDiff[npl][iside][ipmt]->GetYaxis()->SetTitleSize(0.04);
	      H_cal_TdcAdcTimeDiff[npl][iside][ipmt]->GetYaxis()->SetTickSize(0.05);     

	      if (!(npl==2&&iside==1) && !(npl==3&&iside==1)){
	      hcaloCanv[npl][iside]->cd(ipmt+1);
	      hcaloCanv[npl][iside]->SetWindowSize(4500, 3500);

	      gPad->SetLogy();
	      H_cal_TdcAdcTimeDiff_CUT[npl][iside][ipmt]->SetLineColor(kRed);
	      H_cal_TdcAdcTimeDiff[npl][iside][ipmt]->Draw();
	      H_cal_TdcAdcTimeDiff_CUT[npl][iside][ipmt]->Draw("sames");
	      if( new_line_flg ){ 
	      hcal_LineMin[npl][iside][ipmt]->Draw();
	      hcal_LineMax[npl][iside][ipmt]->Draw();
	      }
	      // draw existing time win. cuts
	      hcal_LineMin_old[npl][iside][ipmt]->Draw();
	      hcal_LineMax_old[npl][iside][ipmt]->Draw();
	      
	      // add legend (only necessary on single side)
	      if((iside==0 || iside==1) && ipmt==0){
		auto hcal_legend = new TLegend(0.1, 0.7, 0.8, 0.9);
		hcal_legend->AddEntry(hcal_LineMin_old[npl][iside][ipmt], "existing cut", "l");
		if(new_line_flg) hcal_legend->AddEntry(hcal_LineMin[npl][iside][ipmt], "new cut", "l");
		hcal_legend->Draw();
	      }
	      
	      }
	    } //end pmt loop
	  
	    //Loop over SHMS PreSh PMTs
	  for(int ipmt=0; ipmt<14; ipmt++)
	    {
	      if (npl!=0) continue;

	      
	      // -------- Read the existing min/max parameters SHMS Cal TdcAdcDiffTime (read from existinf pcal_cuts.param file)
	      

	      if(iside==0){
		pPrsh_tWinMin[iside][ipmt] = GetParam(pcal_param_fname.Data(), "pcal_pos_AdcTimeWindowMin", ipmt, npl, 14);
		pPrsh_tWinMax[iside][ipmt] = GetParam(pcal_param_fname.Data(), "pcal_pos_AdcTimeWindowMax", ipmt, npl, 14);
	      }
	      
	      else if(iside==1){	      
		pPrsh_tWinMin[iside][ipmt] = GetParam(pcal_param_fname.Data(), "pcal_neg_AdcTimeWindowMin", ipmt, npl, 14);
		pPrsh_tWinMax[iside][ipmt] = GetParam(pcal_param_fname.Data(), "pcal_neg_AdcTimeWindowMax", ipmt, npl, 14);
	      }

	      
	      //Set Min/Max Line Limits
	      pPrsh_LineMin[iside][ipmt] = new TLine(pPrsh_tWinMin[iside][ipmt], 0, pPrsh_tWinMin[iside][ipmt], P_prSh_TdcAdcTimeDiff[iside][ipmt]->GetMaximum());
	      pPrsh_LineMax[iside][ipmt] = new TLine(pPrsh_tWinMax[iside][ipmt], 0, pPrsh_tWinMax[iside][ipmt], P_prSh_TdcAdcTimeDiff[iside][ipmt]->GetMaximum());
	      
	      pPrsh_LineMin[iside][ipmt]->SetLineColor(kBlue);
	      pPrsh_LineMax[iside][ipmt]->SetLineColor(kBlue);
	       
	      pPrsh_LineMin[iside][ipmt]->SetLineStyle(2);
	      pPrsh_LineMax[iside][ipmt]->SetLineStyle(2);
	      
	      pPrshCanv[iside]->cd(ipmt+1);
	      pPrshCanv[iside]->SetWindowSize(4500, 1500);    

	      gPad->SetLogy();
	      
	      // set label/title font size
	      P_prSh_TdcAdcTimeDiff[iside][ipmt]->GetXaxis()->SetNdivisions(10); 
	      P_prSh_TdcAdcTimeDiff[iside][ipmt]->GetXaxis()->SetLabelSize(0.05); 
	      P_prSh_TdcAdcTimeDiff[iside][ipmt]->GetXaxis()->SetTickSize(0.05); 
	      P_prSh_TdcAdcTimeDiff[iside][ipmt]->GetXaxis()->SetTitle("Good Tdc-Adc Time [ns]");
	      P_prSh_TdcAdcTimeDiff[iside][ipmt]->GetXaxis()->SetTitleSize(0.05);
	      P_prSh_TdcAdcTimeDiff[iside][ipmt]->GetXaxis()->CenterTitle(); 
	      P_prSh_TdcAdcTimeDiff[iside][ipmt]->GetYaxis()->SetLabelSize(0.05); 
	      P_prSh_TdcAdcTimeDiff[iside][ipmt]->GetYaxis()->SetTitleSize(0.05);
	      P_prSh_TdcAdcTimeDiff[iside][ipmt]->GetYaxis()->SetTickSize(0.05); 

	      P_prSh_TdcAdcTimeDiff_CUT[iside][ipmt]->SetLineColor(kRed);
	      P_prSh_TdcAdcTimeDiff[iside][ipmt]->Draw();
	      P_prSh_TdcAdcTimeDiff_CUT[iside][ipmt]->Draw("sames");
	      pPrsh_LineMin[iside][ipmt]->Draw();
	      pPrsh_LineMax[iside][ipmt]->Draw();

	      // add legend (only necessary on single side)
	      if((iside==0 || iside==1) && ipmt==0){
		auto prsh_legend = new TLegend(0.1, 0.7, 0.8, 0.9);
		prsh_legend->AddEntry(pPrsh_LineMin[iside][ipmt], "existing cut", "l");

		prsh_legend->SetTextSize(0.1);
		prsh_legend->Draw();
	      }
	      
	      if(debug) {pPrshAdcCanv[iside]->cd(ipmt+1);
	      pPrshAdcCanv[iside]->SetWindowSize(4500, 1500);  
	      }
	      gPad->SetLogy();
	      if(debug) {
		// set label/title font size                                                                                                                                                   
		P_prSh_AdcTime[iside][ipmt]->GetXaxis()->SetNdivisions(10);                                                                                                 
		P_prSh_AdcTime[iside][ipmt]->GetXaxis()->SetLabelSize(0.05);                                                                                
		P_prSh_AdcTime[iside][ipmt]->GetXaxis()->SetTickSize(0.05);                                                                      
		P_prSh_AdcTime[iside][ipmt]->GetXaxis()->SetTitle("Good Adc Time [ns]");                                                                                              	
		P_prSh_AdcTime[iside][ipmt]->GetXaxis()->SetTitleSize(0.05);                                                                
		P_prSh_AdcTime[iside][ipmt]->GetXaxis()->CenterTitle();                                                                                                                    
		P_prSh_AdcTime[iside][ipmt]->GetYaxis()->SetLabelSize(0.05);                                                                                                        
		P_prSh_AdcTime[iside][ipmt]->GetYaxis()->SetTitleSize(0.05);                                                                                                         
		P_prSh_AdcTime[iside][ipmt]->GetYaxis()->SetTickSize(0.05); 
		
		P_prSh_AdcTime[iside][ipmt]->Draw();
	      }
	    } //end pmt loop
	  


 




	  
	    /*-----------------------------------------------------------	  
	  if(iside==0)
	    {


	      int row_cnt = 0;
	      int ipmt_min, ipmt_max = 0;
	      
	      //Loop over SHMS FLy's Eye PMTs
	      for(int ipmt=0; ipmt<224; ipmt++)
		{

		  
		  //-----------------------
		  
		  // set initial param
		  if(ipmt==0){
		    
		    ipmt_min = 14 * row_cnt;
		    ipmt_max = ipmt_min + 13;
		  }

		  if(ipmt>=ipmt_min && ipmt<=ipmt_max){

		    pCal_tWinMin_old[ipmt] = GetParam("../../PARAM/SHMS/CAL/pcal_cuts.param",  "pcal_arr_AdcTimeWindowMin", ipmt-ipmt_min, row_cnt, 16 );
		    pCal_tWinMax_old[ipmt] = GetParam("../../PARAM/SHMS/CAL/pcal_cuts.param",  "pcal_arr_AdcTimeWindowMax", ipmt-ipmt_min, row_cnt, 16 );
		    
		    
		  }
      
		  // increment row counter at the end of each row
		  if(ipmt==ipmt_max){
		    
		    cout << "reached end of row" << endl;
		    row_cnt = row_cnt + 1;
		    ipmt_min = 14 * row_cnt;
		    ipmt_max = ipmt_min + 13;
		  }

		  //Set Min/Max Line Limits
		  pcal_LineMin_old[ipmt] = new TLine(pCal_tWinMin_old[ipmt], 0, pCal_tWinMin_old[ipmt], P_cal_TdcAdcTimeDiff[ipmt]->GetMaximum());
		  pcal_LineMax_old[ipmt] = new TLine(pCal_tWinMax_old[ipmt], 0, pCal_tWinMax_old[ipmt], P_cal_TdcAdcTimeDiff[ipmt]->GetMaximum());
		  
		  pcal_LineMin_old[ipmt]->SetLineColor(kBlue);
		  pcal_LineMax_old[ipmt]->SetLineColor(kBlue);
		  
		  pcal_LineMin_old[ipmt]->SetLineStyle(1);
		  pcal_LineMax_old[ipmt]->SetLineStyle(1);
		  
		  //-----------------------

		  
		  //Get Mean and Sigma
		  binmax =  P_cal_TdcAdcTimeDiff_CUT[ipmt]->GetMaximumBin();
		  mean = P_cal_TdcAdcTimeDiff_CUT[ipmt]->GetXaxis()->GetBinCenter(binmax);
		  sig =  P_cal_TdcAdcTimeDiff_CUT[ipmt]->GetStdDev();
		  
		  //Set Time Window Cuts
		  pCal_tWinMin[ipmt] = mean - pcal_nSig;
		  pCal_tWinMax[ipmt] = mean + pcal_nSig;                                                                                                          
		  
		  //Set Min/Max Line Limits
		  pcal_LineMin[ipmt] = new TLine(pCal_tWinMin[ipmt], 0, pCal_tWinMin[ipmt], P_cal_TdcAdcTimeDiff[ipmt]->GetMaximum());
		  pcal_LineMax[ipmt] = new TLine(pCal_tWinMax[ipmt], 0, pCal_tWinMax[ipmt], P_cal_TdcAdcTimeDiff[ipmt]->GetMaximum());
		  
		  pcal_LineMin[ipmt]->SetLineColor(kGreen+3);
		  pcal_LineMax[ipmt]->SetLineColor(kGreen+3);
		  
		  pcal_LineMin[ipmt]->SetLineStyle(2);
		  pcal_LineMax[ipmt]->SetLineStyle(2);

		  
		
		  // add legend (only necessary on single pmt)
		  if(ipmt==0){
		      auto pcal_legend = new TLegend(0.1, 0.7, 0.8, 0.9);
		      pcal_legend->AddEntry(pcal_LineMin_old[ipmt], "existing", "l");
		      pcal_legend->SetTextColor(kBlue);
		      pcal_legend->AddEntry(pcal_LineMin[ipmt], "new cut", "l");
		      pcal_legend->SetTextColor(kGreen+3);
		      pcal_legend->SetTextSize(0.08);
		      pcal_legend->Draw();
		    }

		} // End FLys Eye PMT loop
	      
	     

	    } //ennd single side requirement
	    */ //---------------------------------------------------------/
	  


     






	  
	  
	  hhodoCanv[npl][iside]->SaveAs(Form("Time_cuts_tWinSet%d/HMS/HODO/hHodo_%s%s.pdf",run, hod_pl_names[npl].Data(), side_names[iside].Data()));
	  phodoCanv[npl][iside]->SaveAs(Form("Time_cuts_tWinSet%d/SHMS/HODO/pHodo_%s%s.pdf",run, hod_pl_names[npl].Data(), side_names[iside].Data()));
	  	  
	  if(debug) hhodo_tdcCanv[npl][iside]->SaveAs(Form("Time_cuts_tWinSet%d/HMS/HODO/hHodo_TdcUnCorr%s%s.pdf",run, hod_pl_names[npl].Data(), side_names[iside].Data()));
	  if(debug) phodo_tdcCanv[npl][iside]->SaveAs(Form("Time_cuts_tWinSet%d/SHMS/HODO/pHodo_TdcUnCorr%s%s.pdf",run, hod_pl_names[npl].Data(), side_names[iside].Data()));

	  if (!(npl==2&&iside==1) && !(npl==3&&iside==1)){
	    hcaloCanv[npl][iside]->SaveAs(Form("Time_cuts_tWinSet%d/HMS/CAL/hCalo_%s%s.pdf", run,cal_pl_names[npl].Data(), side_names[iside].Data()));
	  }
	  
	  if(npl==0){
	    pPrshCanv[iside]->SaveAs(Form("Time_cuts_tWinSet%d/SHMS/CAL/pPrsh_%s.pdf",run, side_names[iside].Data()));
	    if(debug) pPrshAdcCanv[iside]->SaveAs(Form("Time_cuts_tWinSet%d/SHMS/CAL/pPrshAdc_%s.pdf",run, side_names[iside].Data()));

	  }
	  
	  
	} //end side loop


    } //end plane loop

  //------------------------
  
  
  int row_cnt = 0; //redundant counter 
  int ipmt = 0; //initialize pmt counter
  int ipmt_min = 0; 
  int ipmt_max = 13;

 //Alternative Cal Plot
 for(int row=0; row < 16; row++)
   {
   
     pcalCanv[row] =  new TCanvas(Form("pCal_row_%d", row+1), Form("SHMS Calo TDC:ADC Time Diff, Row %d", row+1),  cw, ch);
     pcalCanv[row]->Divide(7,2);

     pcalAdcCanv[row] =  new TCanvas(Form("pCalAdc_row_%d", row+1), Form("SHMS Calo ADC Time, Row %d", row+1),  cw, ch);
     pcalAdcCanv[row]->Divide(7,2);

     for(int col=0; col<14; col++)
       {


	 //-----------------------
       
	 
	 if(ipmt>=ipmt_min && ipmt<=ipmt_max){
	   
	   pCal_tWinMin_old[ipmt] = GetParam( pcal_param_fname.Data(),  "pcal_arr_AdcTimeWindowMin", ipmt-ipmt_min, row, 16 );
	   pCal_tWinMax_old[ipmt] = GetParam( pcal_param_fname.Data(),  "pcal_arr_AdcTimeWindowMax", ipmt-ipmt_min, row, 16 );
	   
	   
	 }

	 if(ipmt==ipmt_max){
	   row_cnt = row_cnt + 1;
	   ipmt_min = 14 * row_cnt;
	   ipmt_max = ipmt_min + 13;
	 }

	 //Set Min/Max Line Limits
	 pcal_LineMin_old[ipmt] = new TLine(pCal_tWinMin_old[ipmt], 0, pCal_tWinMin_old[ipmt], P_cal_TdcAdcTimeDiff[ipmt]->GetMaximum());
	 pcal_LineMax_old[ipmt] = new TLine(pCal_tWinMax_old[ipmt], 0, pCal_tWinMax_old[ipmt], P_cal_TdcAdcTimeDiff[ipmt]->GetMaximum());
	 
	 pcal_LineMin_old[ipmt]->SetLineColor(kBlue);
	 pcal_LineMax_old[ipmt]->SetLineColor(kBlue);
	 
	 pcal_LineMin_old[ipmt]->SetLineStyle(1);
	 pcal_LineMax_old[ipmt]->SetLineStyle(1);
	 
	 //-----------------------
	 	 
	 //Get Mean and Sigma
	 binmax =  P_cal_TdcAdcTimeDiff_CUT[ipmt]->GetMaximumBin();
	 mean = P_cal_TdcAdcTimeDiff_CUT[ipmt]->GetXaxis()->GetBinCenter(binmax);
	 sig =  P_cal_TdcAdcTimeDiff_CUT[ipmt]->GetStdDev();
	 
	 //Set Time Window Cuts
	 pCal_tWinMin[ipmt] = mean - pcal_nSig;
	 pCal_tWinMax[ipmt] = mean + pcal_nSig;                                                                                                          
	 
	 //Set Min/Max Line Limits
	 if(new_line_flg){ 
	 pcal_LineMin[ipmt] = new TLine(pCal_tWinMin[ipmt], 0, pCal_tWinMin[ipmt], P_cal_TdcAdcTimeDiff[ipmt]->GetMaximum());
	 pcal_LineMax[ipmt] = new TLine(pCal_tWinMax[ipmt], 0, pCal_tWinMax[ipmt], P_cal_TdcAdcTimeDiff[ipmt]->GetMaximum());
	 
	 pcal_LineMin[ipmt]->SetLineColor(kGreen+3);
	 pcal_LineMax[ipmt]->SetLineColor(kGreen+3);
	 
	 pcal_LineMin[ipmt]->SetLineStyle(2);
	 pcal_LineMax[ipmt]->SetLineStyle(2);
	 }
	 
	 //cd to row pads / column
	 pcalCanv[row]->cd(col+1);
	 
	 pcalCanv[row]->SetWindowSize(4500, 1500);
	 gPad->SetLogy();

	 P_cal_TdcAdcTimeDiff_CUT[ipmt]->SetLineColor(kRed);
	 // set label/title font size                                                                                                                                                                     
	 P_cal_TdcAdcTimeDiff[ipmt]->GetXaxis()->SetNdivisions(10);                                                                                                                           
	 P_cal_TdcAdcTimeDiff[ipmt]->GetXaxis()->SetLabelSize(0.05);                                                                                                                          
	 P_cal_TdcAdcTimeDiff[ipmt]->GetXaxis()->SetTickSize(0.05);                                                                                                                           
	 P_cal_TdcAdcTimeDiff[ipmt]->GetXaxis()->SetTitle("Good Tdc-Adc Time [ns]");                                                                                                          
	 P_cal_TdcAdcTimeDiff[ipmt]->GetXaxis()->SetTitleSize(0.05);                                                                                                                          
	 P_cal_TdcAdcTimeDiff[ipmt]->GetXaxis()->CenterTitle();                                                                                                                               
	 P_cal_TdcAdcTimeDiff[ipmt]->GetYaxis()->SetLabelSize(0.05);                                                                                                                          
	 P_cal_TdcAdcTimeDiff[ipmt]->GetYaxis()->SetTitleSize(0.05);                                                                                                                          
	 P_cal_TdcAdcTimeDiff[ipmt]->GetYaxis()->SetTickSize(0.05); 

	 P_cal_TdcAdcTimeDiff[ipmt]->Draw();
	 P_cal_TdcAdcTimeDiff_CUT[ipmt]->Draw("sames");
	 
	 if( new_line_flg ){
	 pcal_LineMin[ipmt]->Draw();
	 pcal_LineMax[ipmt]->Draw();
	 }
	 pcal_LineMin_old[ipmt]->Draw();  
	 pcal_LineMax_old[ipmt]->Draw(); 

	 
	 // add legend (only necessary on single pmt)
	 if(ipmt==ipmt_min){
	   auto pcal_legend = new TLegend(0.1, 0.7, 0.8, 0.9);
	   pcal_legend->AddEntry(pcal_LineMin_old[ipmt], "existing cut", "l");
	   if(new_line_flg) pcal_legend->AddEntry(pcal_LineMin[ipmt], "new cut", "l");
	   pcal_legend->SetTextSize(0.08);
	   pcal_legend->Draw();
	 }
	   
	 pcalAdcCanv[row]->cd(col+1);
	 pcalAdcCanv[row]->SetWindowSize(4500, 1500);     
	 gPad->SetLogy();
	 
	 if(debug){ 
	   // set label/title font size    
	   P_cal_AdcTime[ipmt]->GetXaxis()->SetNdivisions(10);                                                                                                                           
	   P_cal_AdcTime[ipmt]->GetXaxis()->SetLabelSize(0.05);                                                                                                                          
	   P_cal_AdcTime[ipmt]->GetXaxis()->SetTickSize(0.05);                                                                                                                           
	   P_cal_AdcTime[ipmt]->GetXaxis()->SetTitle("Good Adc Pulse Time [ns]");                                                                                                          
	   P_cal_AdcTime[ipmt]->GetXaxis()->SetTitleSize(0.05);                                                                                                                          
	   P_cal_AdcTime[ipmt]->GetXaxis()->CenterTitle();                                                                                                                               
	   P_cal_AdcTime[ipmt]->GetYaxis()->SetLabelSize(0.05);                                                                                                                          
	   P_cal_AdcTime[ipmt]->GetYaxis()->SetTitleSize(0.05);                                                                                                                          
	   P_cal_AdcTime[ipmt]->GetYaxis()->SetTickSize(0.05);

	   P_cal_AdcTime[ipmt]->Draw();
	 }

	 //increment pmt counter
	 ipmt++;



       }//end loop over rows
     
     //Save Each Cal. Column
     pcalCanv[row]->SaveAs(Form("Time_cuts_tWinSet%d/SHMS/CAL/pCal_row%d.pdf",run, row+1));
     if(debug) pcalAdcCanv[row]->SaveAs(Form("Time_cuts_tWinSet%d/SHMS/CAL/pCalAdc_row%d.pdf",run, row+1));

   }//end loop over columns
 
 //Write Histograms to ROOT file
 outROOT->Write();
 outROOT->Close();
     
  }// end else (i.e.,  set_refTimes==false)
   
 

  //ONLY if set_refTimes is FALSE, will the code assume doing det. time window cuts, and will write the time window cut param file

 if(set_refTimes==false) {
   
   //------------Write Time Window Min/Max Limits to Parameter File---------------
   
 TString n_side[2] = {"Pos", "Neg"};
 TString n_side_cal[2] = {"pos", "neg"};
 TString n_lim[2] = {"Min", "Max"};
 
 ofstream out_hhodo;
 ofstream out_phodo;
 ofstream out_hcal;
 ofstream out_pprsh;  
 ofstream out_pcal;  
 ofstream out_hdc;   
 ofstream out_pdc;   
 ofstream out_hcer; 
 ofstream out_phgcer;
 ofstream out_pngcer; 

 //HMS Hodo
 out_hhodo.open(Form("Time_cuts_tWinSet%d/param_files/hhodo_tWin_%d_new.param", run, run));
 out_hhodo << "; HMS Hodoscope Parameter File Containing TimeWindow Min/Max Cuts " << endl;
 out_hhodo << " " << endl;
 out_hhodo << " " << endl;
 out_hhodo << " " << endl;
 //SHMS Hodo
 out_phodo.open(Form("Time_cuts_tWinSet%d/param_files/phodo_tWin_%d_new.param", run, run));
 out_phodo << "; SHMS Hodoscope Parameter File Containing TimeWindow Min/Max Cuts " << endl;
 out_phodo << " " << endl;
 out_phodo << " " << endl;
 out_phodo << " " << endl;
 //HMS Cal
 out_hcal.open(Form("Time_cuts_tWinSet%d/param_files/hcal_tWin_%d_new.param", run, run));
 out_hcal << "; HMS Calorimeter Parameter File Containing TimeWindow Min/Max Cuts " << endl;
 out_hcal << " " << endl;
 out_hcal << " " << endl;
 out_hcal << " " << endl;
 //SHMS PreSh
 out_pprsh.open(Form("Time_cuts_tWinSet%d/param_files/pprsh_tWin_%d_existing.param", run, run));
 out_pprsh << "; SHMS Pre-Shower Parameter File Containing TimeWindow Min/Max Cuts " << endl;
 out_pprsh << " " << endl;
 out_pprsh << " " << endl;
 out_pprsh << " " << endl;
 //SHMS Fly's Eye Cal
 out_pcal.open(Form("Time_cuts_tWinSet%d/param_files/pcal_tWin_%d_new.param", run, run));
 out_pcal << "; SHMS Fly's Eye Calorimeter  Parameter File Containing TimeWindow Min/Max Cuts " << endl;
 out_pcal << " " << endl;
 out_pcal << " " << endl;
 out_pcal << " " << endl;
 //HMS DC
 out_hdc.open(Form("Time_cuts_tWinSet%d/param_files/hdc_tWin_%d_existing.param", run, run));
 out_hdc << "; HMS DC  Parameter File Containing TimeWindow Min/Max Cuts " << endl;
 out_hdc << " " << endl;
 out_hdc << " " << endl;
 out_hdc << " " << endl;
 //SHMS DC
 out_pdc.open(Form("Time_cuts_tWinSet%d/param_files/pdc_tWin_%d_existing.param", run, run));
 out_pdc << "; SHMS DC  Parameter File Containing TimeWindow Min/Max Cuts " << endl;
 out_pdc << " " << endl;
 out_pdc << " " << endl;
 out_pdc << " " << endl;
 //HMS Cer
 out_hcer.open(Form("Time_cuts_tWinSet%d/param_files/hcer_tWin_%d_existing.param", run, run));
 out_hcer << "; HMS Cer  Parameter File Containing TimeWindow Min/Max Cuts " << endl;
 out_hcer << " " << endl;
 out_hcer << " " << endl;
 out_hcer << " " << endl;
//SHMS HGCER
 out_phgcer.open(Form("Time_cuts_tWinSet%d/param_files/phgcer_tWin_%d_existing.param",run, run));
 out_phgcer << "; SHMS Heavy Gas Cer  Parameter File Containing TimeWindow Min/Max Cuts " << endl;
 out_phgcer << " " << endl;
 out_phgcer << " " << endl;
 out_phgcer << " " << endl;
//SHMS NGCER
 out_pngcer.open(Form("Time_cuts_tWinSet%d/param_files/pngcer_tWin_%d_existing.param", run, run));
 out_pngcer << "; SHMS Noble Gas Cer  Parameter File Containing TimeWindow Min/Max Cuts " << endl;
 out_pngcer << " " << endl;
 out_pngcer << " " << endl;
 out_pngcer << " " << endl;

  //out_hhodo << "; " << setw(32) << "1x " << setw(19) << "1y " << setw(16) << "2x " << setw(16) << "2y " << endl;
  //out_hhodo << "hhodo_PosAdcTimeWindowMin = ";

 //Loop over Hodoscopes Detector Sides, HMS Calorimeter Sides, SHMS PreSHower
  for(int iside = 0; iside<SIDES; iside++)
    {
      //Loop over Min/Max Window Limits
      for (int lim=0; lim<2; lim++)
	{

	  //Minimum Time Window
	  if(lim==0){
	    //HMS Hodo
	    out_hhodo << "" << endl;
	    out_hhodo << "; " << setw(32) << "1x " << setw(19) << "1y " << setw(16) << "2x " << setw(16) << "2y " << endl;
	    out_hhodo << Form("hhodo_%sAdcTimeWindow%s = ", n_side[iside].Data(), n_lim[lim].Data());

	    
	    //SHMS Hodo
	    out_phodo << "" << endl;
	    out_phodo << "; " << setw(32) << "1x " << setw(19) << "1y " << setw(16) << "2x " << setw(16) << "2y " << endl;
	    out_phodo << Form("phodo_%sAdcTimeWindow%s = ", n_side[iside].Data(), n_lim[lim].Data());

	    //HMS Calorimeter
	    out_hcal << "" << endl;
	    out_hcal << Form("hcal_%s_AdcTimeWindow%s = ", n_side_cal[iside].Data(), n_lim[lim].Data());
	    
	    //SHMS PreSHower
	    out_pprsh << "" << endl;
	    out_pprsh << Form("pcal_%s_AdcTimeWindow%s = ", n_side_cal[iside].Data(), n_lim[lim].Data());
	 
	    if(iside==0){
	    //SHMS Fly's Eye
	    out_pcal << "" << endl;
	    out_pcal << Form("pcal_arr_AdcTimeWindow%s = ", n_lim[lim].Data());
	   
	    //HMS DC
	    out_hdc << "" << endl;
	    out_hdc << "hdc_tdc_min_win = ";
	    
	    //SHMS DC
	    out_pdc << "" << endl;
	    out_pdc << "pdc_tdc_min_win = ";
	    
	    //HMS Cer
	    out_hcer << "" << endl;
	    out_hcer << "hcer_adcTimeWindowMin = ";

	    //SHMS HGCER
	    out_phgcer << "" << endl;
	    out_phgcer << "phgcer_adcTimeWindowMin = ";
	    
	    //SHMS NGCER
	    out_pngcer << "" << endl;
	    out_pngcer << "pngcer_adcTimeWindowMin = ";
	    }

	  }
	  //Maximum Time Window
	  if(lim==1){
	    //HMS Hodo
	    out_hhodo << "" << endl;
	    out_hhodo << "; " << setw(32) << "1x " << setw(19) << "1y " << setw(16) << "2x " << setw(16) << "2y " << endl;
	    out_hhodo << Form("hhodo_%sAdcTimeWindow%s = ", n_side[iside].Data(), n_lim[lim].Data());

	    //SHMS Hodo
	    out_phodo << "" << endl;
	    out_phodo << "; " << setw(32) << "1x " << setw(19) << "1y " << setw(16) << "2x " << setw(16) << "2y " << endl;
	    out_phodo << Form("phodo_%sAdcTimeWindow%s = ", n_side[iside].Data(), n_lim[lim].Data());

	    //HMS Calorimeter
	    out_hcal << "" << endl;
	    out_hcal << Form("hcal_%s_AdcTimeWindow%s = ", n_side_cal[iside].Data(), n_lim[lim].Data());
	    
	    //SHMS PreSHower
	    out_pprsh << "" << endl;
	    out_pprsh << Form("pcal_%s_AdcTimeWindow%s = ", n_side_cal[iside].Data(), n_lim[lim].Data());
	    
	    if(iside==0){
	    //SHMS Fly's Eye
	    out_pcal << "" << endl;
	    out_pcal << Form("pcal_arr_AdcTimeWindow%s = ", n_lim[lim].Data());
	    
	    //HMS DC
	    out_hdc << "" << endl;
	    out_hdc << "hdc_tdc_max_win = ";
  
	    //SHMS DC
	    out_pdc << "" << endl;
	    out_pdc << "pdc_tdc_max_win = ";
	    
	    //HMS Cer
	    out_hcer << "" << endl;
	    out_hcer << "hcer_adcTimeWindowMax = ";

	    //SHMS HGCER
	    out_phgcer << "" << endl;
	    out_phgcer << "phgcer_adcTimeWindowMax = ";
	    
	    //SHMS NGCER
	    out_pngcer << "" << endl;
	    out_pngcer << "pngcer_adcTimeWindowMax = ";

	    }
	  }

	  for(int ipmt = 0; ipmt<21; ipmt++)
	    {     

	      //--------Write out HMS Hodo Param---------
	      if(ipmt<16){
		if(ipmt==0){
		  
		  if (lim==0){
		    out_hhodo << setprecision(2) << hhodo_tWinMin[0][iside][ipmt] << ", " << setw(15) << hhodo_tWinMin[1][iside][ipmt] << ", " << setw(15) << hhodo_tWinMin[2][iside][ipmt] << ", " << setw(15) << hhodo_tWinMin[3][iside][ipmt] << fixed << endl; 
		  }
		  if(lim==1){
		    out_hhodo << setprecision(2) << hhodo_tWinMax[0][iside][ipmt] << ", " << setw(15) << hhodo_tWinMax[1][iside][ipmt] << ", " << setw(15) << hhodo_tWinMax[2][iside][ipmt] << ", " << setw(15) << hhodo_tWinMax[3][iside][ipmt] << fixed << endl; 
		  }
		}
		
		else{
		  if(lim==0){
		    out_hhodo << setw(32) << setprecision(2) << hhodo_tWinMin[0][iside][ipmt] << ", " << setw(15) << hhodo_tWinMin[1][iside][ipmt] << ", " << setw(15) << hhodo_tWinMin[2][iside][ipmt] << ", " << setw(15) << hhodo_tWinMin[3][iside][ipmt] << fixed << endl; 		
		  }
		  if(lim==1){
		    out_hhodo << setw(32) << setprecision(2) << hhodo_tWinMax[0][iside][ipmt] << ", " << setw(15) << hhodo_tWinMax[1][iside][ipmt] << ", " << setw(15) << hhodo_tWinMax[2][iside][ipmt] << ", " << setw(15) << hhodo_tWinMax[3][iside][ipmt] << fixed << endl; 
		  }
		  
		}

	      }//end HMS Hodo PMT Loop
	      
	      //------Write out SHMS Hodo Param-------
	      if(ipmt==0){
		
		if (lim==0){
		  out_phodo << setprecision(2) << phodo_tWinMin[0][iside][ipmt] << ", " << setw(15) << phodo_tWinMin[1][iside][ipmt] << ", " << setw(15) << phodo_tWinMin[2][iside][ipmt] << ", " << setw(15) << phodo_tWinMin[3][iside][ipmt] << fixed << endl; 
		}
		if(lim==1){
		  out_phodo << setprecision(2) << phodo_tWinMax[0][iside][ipmt] << ", " << setw(15) << phodo_tWinMax[1][iside][ipmt] << ", " << setw(15) << phodo_tWinMax[2][iside][ipmt] << ", " << setw(15) << phodo_tWinMax[3][iside][ipmt] << fixed << endl; 
		}
	      }
	      
	      else{
		if(lim==0){
		  out_phodo << setw(32) << setprecision(2) << phodo_tWinMin[0][iside][ipmt] << ", " << setw(15) << phodo_tWinMin[1][iside][ipmt] << ", " << setw(15) << phodo_tWinMin[2][iside][ipmt] << ", " << setw(15) << phodo_tWinMin[3][iside][ipmt] << fixed << endl; 		
		}
		if(lim==1){
		  out_phodo << setw(32) << setprecision(2) << phodo_tWinMax[0][iside][ipmt] << ", " << setw(15) << phodo_tWinMax[1][iside][ipmt] << ", " << setw(15) << phodo_tWinMax[2][iside][ipmt] << ", " << setw(15) << phodo_tWinMax[3][iside][ipmt] << fixed << endl; 
		}
		
	      }

	      
	    } //end loop over hms pmts
	  
	  //-----Write out HMS Calorimeter-------
	  for(int layer=0; layer<4; layer++)
	    {
	      
	      if(layer==0)
		{
		  if(lim==0){
		    out_hcal << setprecision(2) << hCal_tWinMin[layer][iside][0]<<","
			     << hCal_tWinMin[layer][iside][1]<<","
			     << hCal_tWinMin[layer][iside][2]<<","
			     << hCal_tWinMin[layer][iside][3]<<","
			     << hCal_tWinMin[layer][iside][4]<<","
			     << hCal_tWinMin[layer][iside][5]<<","
			     << hCal_tWinMin[layer][iside][6]<<","
			     << hCal_tWinMin[layer][iside][7]<<","
			     << hCal_tWinMin[layer][iside][8]<<","
			     << hCal_tWinMin[layer][iside][9]<<","
			     << hCal_tWinMin[layer][iside][10]<<","
			     << hCal_tWinMin[layer][iside][11]<<","
			     << hCal_tWinMin[layer][iside][12]<< fixed << endl;
		    
		  } // end Min Limit
		  
		  if(lim==1){
		    out_hcal << setprecision(2) << hCal_tWinMax[layer][iside][0]<<","
			     << hCal_tWinMax[layer][iside][1]<<","
			     << hCal_tWinMax[layer][iside][2]<<","
			     << hCal_tWinMax[layer][iside][3]<<","
			     << hCal_tWinMax[layer][iside][4]<<","
			     << hCal_tWinMax[layer][iside][5]<<","
			     << hCal_tWinMax[layer][iside][6]<<","
			     << hCal_tWinMax[layer][iside][7]<<","
			     << hCal_tWinMax[layer][iside][8]<<","
			     << hCal_tWinMax[layer][iside][9]<<","
			     << hCal_tWinMax[layer][iside][10]<<","
			     << hCal_tWinMax[layer][iside][11]<<","
			     << hCal_tWinMax[layer][iside][12]<< fixed << endl;
		    
		  } //end Max Limit
		  
		} //end layer==0 requirement
	      
	      else
		{
		  if(lim==0){
		    out_hcal << setw(32) << setprecision(2) << hCal_tWinMin[layer][iside][0]<<","
			     << hCal_tWinMin[layer][iside][1]<<","
			     << hCal_tWinMin[layer][iside][2]<<","
			     << hCal_tWinMin[layer][iside][3]<<","
			     << hCal_tWinMin[layer][iside][4]<<","
			     << hCal_tWinMin[layer][iside][5]<<","
			     << hCal_tWinMin[layer][iside][6]<<","
			     << hCal_tWinMin[layer][iside][7]<<","
			     << hCal_tWinMin[layer][iside][8]<<","
			     << hCal_tWinMin[layer][iside][9]<<","
			     << hCal_tWinMin[layer][iside][10]<<","
			     << hCal_tWinMin[layer][iside][11]<<","
			     << hCal_tWinMin[layer][iside][12]<< fixed << endl;
		    
		  } // end Min Limit
		  
		  if(lim==1){
		    out_hcal << setw(32) << setprecision(2) << hCal_tWinMax[layer][iside][0]<<","
			     << hCal_tWinMax[layer][iside][1]<<","
			     << hCal_tWinMax[layer][iside][2]<<","
			     << hCal_tWinMax[layer][iside][3]<<","
			     << hCal_tWinMax[layer][iside][4]<<","
			     << hCal_tWinMax[layer][iside][5]<<","
			     << hCal_tWinMax[layer][iside][6]<<","
			     << hCal_tWinMax[layer][iside][7]<<","
			     << hCal_tWinMax[layer][iside][8]<<","
			     << hCal_tWinMax[layer][iside][9]<<","
			     << hCal_tWinMax[layer][iside][10]<<","
			     << hCal_tWinMax[layer][iside][11]<<","
			     << hCal_tWinMax[layer][iside][12]<< fixed << endl;
		    
		  } //end Max Limit
		  
		} 

	      
	    } //end loop over layers
	    
	  //------Write SHMS PreShower Param-------
	  //Lower Limit Time Window Cut
	  if(lim==0){
	    out_pprsh << setprecision(2) << pPrsh_tWinMin[iside][0] << ", " << pPrsh_tWinMin[iside][1] << ", " 
		      <<  pPrsh_tWinMin[iside][2] << ", "  <<  pPrsh_tWinMin[iside][3]  << ", " 
		      <<  pPrsh_tWinMin[iside][4] << ", "  <<  pPrsh_tWinMin[iside][5]  << ", " 
		      <<  pPrsh_tWinMin[iside][6] << ", "  <<  pPrsh_tWinMin[iside][7]  << ", "
		      <<  pPrsh_tWinMin[iside][8] << ", "  <<  pPrsh_tWinMin[iside][9]  << ", " 
		      <<  pPrsh_tWinMin[iside][10] << ", " <<  pPrsh_tWinMin[iside][11] << ", " 
		      <<  pPrsh_tWinMin[iside][12] << ", " <<  pPrsh_tWinMin[iside][13] << fixed << endl;
	  }
	  //Upper Limit Time WIndow Cut
	  if(lim==1){
	    out_pprsh << setprecision(2) << pPrsh_tWinMax[iside][0] << ", " << pPrsh_tWinMax[iside][1] << ", " 
		      <<  pPrsh_tWinMax[iside][2] << ", "  <<  pPrsh_tWinMax[iside][3]  << ", " 
		      <<  pPrsh_tWinMax[iside][4] << ", "  <<  pPrsh_tWinMax[iside][5]  << ", " 
		      <<  pPrsh_tWinMax[iside][6] << ", "  <<  pPrsh_tWinMax[iside][7]  << ", "
		      <<  pPrsh_tWinMax[iside][8] << ", "  <<  pPrsh_tWinMax[iside][9]  << ", " 
		      <<  pPrsh_tWinMax[iside][10] << ", " <<  pPrsh_tWinMax[iside][11] << ", " 
		      <<  pPrsh_tWinMax[iside][12] << ", " <<  pPrsh_tWinMax[iside][13] << fixed << endl;
	  }
	  

	  
	  //Write Out Param of Detectors without a SIDE (Fly's Eye, DC, Cher)
	  if(iside==0)
	    {

	      //---------Write SHMS Fly's Eye Calorimeter Param-------------
	      for(int ipmt=0; ipmt<224; ipmt++)
		{
		  //Lower Limit Time Window Cut
		  if(lim==0){
		    //pCal_tWinMin[ipmt];
		    if(ipmt < 224 ){
		      out_pcal << setw(2) << setprecision(2) << pCal_tWinMin[ipmt] << ( (ipmt+1) % 14 ? "," : "\n") << fixed; 
		    }
		    
		  }
		  
		  //Upper Limit Time WIndow Cut
		  if(lim==1){
		    if(ipmt < 224 ){
		      out_pcal << setw(2) << setprecision(2) << pCal_tWinMax[ipmt] << ( (ipmt+1) % 14 ? "," : "\n") << fixed; 
		    }
		  }
		  
		} //End Fly's Eye Cal PMT Loop
	     
	      
	      //---------Write HMS/SHMS DC Param-------------
	      
	      //Loop over DC planes
	      for(int npl=0; npl<dc_PLANES; npl++)
		{
		
		  //Lower Limit Time Window Cut
		  if(lim==0){
		    out_hdc << setw(2) << setprecision(2) << hDC_tWinMin[npl] << ", " << fixed;
		    out_pdc << setw(2) << setprecision(2) << pDC_tWinMin[npl] << ", " << fixed;

		  }
		  


		  //Upper Limit Time Window Cut
		  if(lim==1){
		    out_hdc << setw(2) << setprecision(2) << hDC_tWinMax[npl] << ", " << fixed;
		    out_pdc << setw(2) << setprecision(2) << pDC_tWinMax[npl] << ", " << fixed;

		  }
		
		} //End loop over DC Planes

	      //---------Write HMS/SHMS CER Param-------------
	      
	      //Loop over PMTs
	      for (int ipmt = 0; ipmt<4; ipmt++){
		//Lower Limit Time Window Cut
		if(lim==0){
		  //HMS Cer
		  if(ipmt<2){
		    out_hcer << setprecision(2) << hCer_tWinMin[ipmt] << ", " << fixed;
		  }
		  //SHMS HGCER
		  out_phgcer << setprecision(2) << phgcer_tWinMin[ipmt] << ", " << fixed;
		  //SHMS NGCER
		  out_pngcer << setprecision(2) << pngcer_tWinMin[ipmt] << ", " << fixed;

		  
		}
		 
		//Upper Limit Time Window Cut
		if(lim==1){
		  //HMS Cer
		  if(ipmt<2){
		    out_hcer << setprecision(2) << hCer_tWinMax[ipmt] << ", " << fixed;
		  }
		  //SHMS HGCER
		  out_phgcer << setprecision(2) << phgcer_tWinMax[ipmt] << ", " << fixed;
		  //SHMS NGCER
		  out_pngcer << setprecision(2) << pngcer_tWinMax[ipmt] << ", " << fixed;

		}

		
	      }//end loop over Cher PMTs


	    } //End loop over single side
	  
	}// end loop Min/Max Limits
      
    } // end loop over sides

 }
 
      
} //end program
