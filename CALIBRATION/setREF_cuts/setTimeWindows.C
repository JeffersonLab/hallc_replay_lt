/*
 * Description: Define and Set REF. TIME CUTS 
 * ================================================================
 * Time-stamp: "2019-09-24 13:15:22 trottar"
 * ================================================================
 *
 * Author:  Richard L. Trotta III <trotta@cua.edu>, Carlos Yero <cyero002@fiu.edu>
 *
 * Copyright (c) trottar & Yero1990
 */

//0.0625 ns / Ch., in case it is used

#include "TROOT.h"
#include "TRint.h"
#include "TFile.h"
#include "TH1F.h"
#include "TTree.h"
#include "TLine.h"
#include "TCanvas.h"
#include <sys/stat.h>
#include "ref_time_cuts.h"
#include <iostream>

using namespace std;

//This code currrently works ony for ROOT 6.08
void setTimeWindows(int run = 0, string trg = "")
{

  if(run==0){
  
  	cout << "Please enter run number...\n";
  	cin >> run;
  }

  if(trg==""){
  
  	cout << "Please pick a hms, shms, or coin...\n";
  	cin >> trg;
  }

  
  //user input: trg --> "hms", "shms", "coin" (DAQ Mode) 
  //                                       |--------------------- Time Window Cuts -------------------------------|
  //                          refTime_cuts | Hodoscopes   Calorimeters       Cherenkovs         Drift Chambers    |
  //User input: detector ---> htrig/ptrig, | hhod/pphod,  hcal/pcal/pprsh, hcer/phgcer/pngcer,  hdc/pdc           |
  
  //PREVENT DISPLAY 
  gROOT->SetBatch(kTRUE);
  
  
  //========================================
  //====Create Directories to Save Plots====
  //========================================
  mkdir(Form("Time_cuts_%d", run), S_IRWXU);
  mkdir(Form("Time_cuts_%d/HMS", run), S_IRWXU);
  mkdir(Form("Time_cuts_%d/SHMS", run), S_IRWXU);
  //Create HMS Detectors Dir
  mkdir(Form("Time_cuts_%d/HMS/refTime", run), S_IRWXU);
  mkdir(Form("Time_cuts_%d/HMS/CER", run), S_IRWXU);
  mkdir(Form("Time_cuts_%d/HMS/HODO", run), S_IRWXU);
  mkdir(Form("Time_cuts_%d/HMS/CAL", run), S_IRWXU);
  mkdir(Form("Time_cuts_%d/HMS/DC", run), S_IRWXU);
  
  //Create sHMS Detectors Dir
  mkdir(Form("Time_cuts_%d/SHMS/refTime", run), S_IRWXU);
  mkdir(Form("Time_cuts_%d/SHMS/CER", run), S_IRWXU);
  mkdir(Form("Time_cuts_%d/SHMS/HODO", run), S_IRWXU);
  mkdir(Form("Time_cuts_%d/SHMS/CAL", run), S_IRWXU);
  mkdir(Form("Time_cuts_%d/SHMS/DC", run), S_IRWXU);


  
  //===============================
  //INITIALIZE HISTOGRAM BINNING
  //===============================
  
  //REF Time Histos 
  //HMS                           SHMS
  hhod_tref_nbins = 150,          phod_tref_nbins = 100;
  hhod_tref_xmin = 1000,          phod_tref_xmin = 1500;
  hhod_tref_xmax = 2500,          phod_tref_xmax = 4200;
  
  hdc_tref_nbins = 200,           pdc_tref_nbins = 200;
  hdc_tref_xmin = 10600,          pdc_tref_xmin = 13000;
  hdc_tref_xmax = 16000,          pdc_tref_xmax = 15500;
  
  hadc_tref_nbins = 200,          padc_tref_nbins = 100;
  hadc_tref_xmin = 1000,          padc_tref_xmin = 2000;
  hadc_tref_xmax = 4300,          padc_tref_xmax = 4500;
  
  //TRG
  ptrg1_roc1_nbins=100, ptrg1_roc1_xmin=500, ptrg1_roc1_xmax=3100;
  ptrg1_roc2_nbins=100, ptrg1_roc2_xmin=500, ptrg1_roc2_xmax=3800;
  ptrg4_roc1_nbins=100, ptrg4_roc1_xmin=500, ptrg4_roc1_xmax=3000;
  ptrg4_roc2_nbins=100, ptrg4_roc2_xmin=500, ptrg4_roc2_xmax=3600;
  
  //ADC-TDC Time Diff Histos
  //HMS               SHMS
  hhod_nbins = 100,   phod_nbins = 100;    
  hhod_xmin = -70,    phod_xmin = -80;    
  hhod_xmax = -40,    phod_xmax = 70;  
  
  hhod_tnbins = 100,   phod_tnbins = 100;    
  hhod_txmin = -1000,    phod_txmin = -1000;    
  hhod_txmax = 2000,    phod_txmax = 2000;  
  
  hdc_nbins = 100,    pdc_nbins = 100;                                                      
  hdc_xmin = -16000,  pdc_xmin = -15000;                                                                
  hdc_xmax = -10000,  pdc_xmax = -5000;  
  
  hcer_nbins = 100,   phgcer_nbins = 100,    pngcer_nbins = 100;                                                                                                                                     
  hcer_xmin = 0,      phgcer_xmin = -500,    pngcer_xmin = -500;                                                                                                                                   
  hcer_xmax = 200,    phgcer_xmax = 300,     pngcer_xmax = 300;                                                                                                                 
  
  hcal_nbins = 200,   pPrsh_nbins = 100,      pcal_nbins = 75;                                                           
  hcal_xmin = -140,   pPrsh_xmin = -300,      pcal_xmin = -100;                                                                                                                    
  hcal_xmax = -60,    pPrsh_xmax = 210,       pcal_xmax = 50; 
  
  pPrshAdc_nbins = 200,         pcalAdc_nbins = 200;
  pPrshAdc_xmin = -300.,        pcalAdc_xmin = -300.;
  pPrshAdc_xmax = 500.,         pcalAdc_xmax = 500.;

  //=====================================
  

  
  //=========================
  //====OPEN ROOT FILE=======
  //=========================
  
  string rtype = "coin";  //"coin" or "hms", "shms"  (singles in coin mode)
  // string rtype = trg;
                                
  // TString filename = Form("../../../ROOTfiles/kaon-coin/%s_reftime_%d_-1.root", rtype.c_str(), run);
  TString filename = Form("../../../ROOTfiles/kaon-coin/%s_reftime_%d_50000.root", rtype.c_str(), run);
   
  //read ROOTfile and Get TTree
  TFile *data_file = new TFile(filename, "READ"); 
  TTree *T = (TTree*)data_file->Get("T");
  
  //Create output root file where histograms will be stored
  TFile *outROOT = new TFile(Form("./Time_cuts_%d/%s_histos_run%d.root", run, rtype.c_str(), run), "recreate");
        




  //===========================
  //===Set Branch Address======
  //===Reference Time Leafs====
  //===========================
  
  
  //HMS REF-TIME LEAFS
  for (int i=0; i<4; i++)
    {
      n_hDC_ref = Form("T.%s.hDCREF%d_tdcTimeRaw", trg.c_str(), i+1);
      n_hDC_tdcMult = Form("T.%s.hDCREF%d_tdcMultiplicity", trg.c_str(), i+1);
      
      T->SetBranchAddress(n_hDC_ref, &hDC_ref[i]);
      T->SetBranchAddress(n_hDC_tdcMult, &hDC_tdcMult[i]);
      
      H_DC_Tref[i] = new TH1F(Form("hDC%d_refTime", i+1), Form("HMS DC Ref %d", i+1), hdc_tref_nbins,  hdc_tref_xmin, hdc_tref_xmax);
      H_DC_Tref_CUT[i] = new TH1F(Form("hDC%d_refTime_CUT", i+1), Form("HMS DC Ref CUT %d", i+1), hdc_tref_nbins,  hdc_tref_xmin, hdc_tref_xmax);
      
    }
  
  H_hodo_Tref = new TH1F("hT1_ref", "HMS Hodo hT1 Ref. Time", hhod_tref_nbins, hhod_tref_xmin, hhod_tref_xmax);
  H_FADC_Tref = new TH1F("hFADC_ref", "HMS fADC Ref. Time", hadc_tref_nbins,  hadc_tref_xmin, hadc_tref_xmax);
  
  H_hodo_Tref_CUT = new TH1F("hT1_ref_CUT", "HMS Hodo hT1 Ref. Time (CUT)", hhod_tref_nbins, hhod_tref_xmin, hhod_tref_xmax);
  H_FADC_Tref_CUT = new TH1F("hFADC_ref_CUT", "HMS fADC Ref. Time (CUT)", hadc_tref_nbins,  hadc_tref_xmin, hadc_tref_xmax);
  
  
  n_hT1_ref = Form("T.%s.hT1_tdcTimeRaw", trg.c_str());
  n_hFADC_ref = Form("T.%s.hFADC_TREF_ROC1_adcPulseTimeRaw", trg.c_str());
  n_hT1_tdcMult = Form("T.%s.hT1_tdcMultiplicity", trg.c_str());
  n_hFADC_adcMult = Form("T.%s.hFADC_TREF_ROC1_adcMultiplicity", trg.c_str());
  
  T->SetBranchAddress(n_hT1_ref, &hT1_ref);     
  T->SetBranchAddress(n_hFADC_ref, &hFADC_ref);
  T->SetBranchAddress(n_hT1_tdcMult, &hT1_tdcMult);
  T->SetBranchAddress(n_hFADC_adcMult, &hFADC_adcMult);
  
  
  //SHMS REF-TIME LEAFS 
  for (int i=0; i<10; i++)
    {
      n_pDC_ref = Form("T.%s.pDCREF%d_tdcTimeRaw",trg.c_str(), i+1);
      n_pDC_tdcMult = Form("T.%s.pDCREF%d_tdcMultiplicity", trg.c_str(), i+1);
      
      T->SetBranchAddress(n_pDC_ref, &pDC_ref[i]);
      T->SetBranchAddress(n_pDC_tdcMult, &pDC_tdcMult[i]);
      
      P_DC_Tref[i] = new TH1F(Form("pDC%d_refTime", i+1), Form("SHMS DC Ref %d", i+1), pdc_tref_nbins,  pdc_tref_xmin, pdc_tref_xmax);
      P_DC_Tref_CUT[i] = new TH1F(Form("pDC%d_refTime_CUT", i+1), Form("SHMS DC Ref %d (CUT)", i+1), pdc_tref_nbins,  pdc_tref_xmin, pdc_tref_xmax);
      
    }
  
  n_pT1_ref = Form("T.%s.pT1_tdcTimeRaw", trg.c_str());
  n_pT1_tdcMult = Form("T.%s.pT1_tdcMultiplicity", trg.c_str());
  n_pT2_ref = Form("T.%s.pT2_tdcTimeRaw", trg.c_str());
  n_pT2_tdcMult = Form("T.%s.pT2_tdcMultiplicity", trg.c_str());
  n_pFADC_ref = Form("T.%s.pFADC_TREF_ROC2_adcPulseTimeRaw", trg.c_str());
  n_pFADC_adcMult = Form("T.%s.pFADC_TREF_ROC2_adcMultiplicity", trg.c_str());
  
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
  
  //======================================
  //=======Set Branch Address============= 
  //=======Detector Time Window Leafs=====
  //======================================

  //TRIGGER DETECTOR (ONLY WHEN LOOKING AT COINCIDENCES)
  n_ptrg1_r1 = "T.coin.pTRIG1_ROC1_tdcTimeRaw";
  n_ptrg1_r2 = "T.coin.pTRIG1_ROC2_tdcTimeRaw";
  n_ptrg4_r1 = "T.coin.pTRIG4_ROC1_tdcTimeRaw";
  n_ptrg4_r2 = "T.coin.pTRIG4_ROC2_tdcTimeRaw";

  T->SetBranchAddress(n_ptrg1_r1, &ptrg1_r1);
  T->SetBranchAddress(n_ptrg1_r2, &ptrg1_r2);
  T->SetBranchAddress(n_ptrg4_r1, &ptrg4_r1);
  T->SetBranchAddress(n_ptrg4_r2, &ptrg4_r2);

  pTrig1_ROC1_rawTdcTime = new TH1F("pTRIG1_ROC1_rawTdcTime", "pTRIG1_ROC1_rawTdcTime", ptrg1_roc1_nbins, ptrg1_roc1_xmin, ptrg1_roc1_xmax);
  pTrig1_ROC2_rawTdcTime = new TH1F("pTRIG1_ROC2_rawTdcTime", "pTRIG1_ROC2_rawTdcTime", ptrg1_roc2_nbins, ptrg1_roc2_xmin, ptrg1_roc2_xmax);
  pTrig4_ROC1_rawTdcTime = new TH1F("pTRIG4_ROC1_rawTdcTime", "pTRIG4_ROC1_rawTdcTime", ptrg4_roc1_nbins, ptrg4_roc1_xmin, ptrg4_roc1_xmax);
  pTrig4_ROC2_rawTdcTime = new TH1F("pTRIG4_ROC2_rawTdcTime", "pTRIG4_ROC2_rawTdcTime", ptrg4_roc2_nbins, ptrg4_roc2_xmin, ptrg4_roc2_xmax);

      
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

      H_dc_rawTDC[npl] = new TH1F(Form("hDC%s_rawTDC", hdc_pl_names[npl].c_str()), Form("HMS DC Plane %s Raw TDC", hdc_pl_names[npl].c_str()), hdc_nbins, hdc_xmin, hdc_xmax);
      H_dc_rawTDC_CUT[npl] = new TH1F(Form("hDC%s_rawTDC_CUT", hdc_pl_names[npl].c_str()), Form("HMS DC Plane %s Raw TDC (CUT)", hdc_pl_names[npl].c_str()), hdc_nbins, hdc_xmin, hdc_xmax);
      
      //SHMS
      base = "P.dc." + pdc_pl_names[npl];
      n_pdc_rawTDC = base + "." + "rawtdc";
      n_pndata_rawTDC = "Ndata." + n_pdc_rawTDC;
      
      T->SetBranchAddress(n_pdc_rawTDC, pdc_rawTDC[npl]);
      T->SetBranchAddress(n_pndata_rawTDC, &pndata_rawTDC[npl]);
      
      P_dc_rawTDC[npl] = new TH1F(Form("pDC%s_rawTDC", pdc_pl_names[npl].c_str()), Form("SHMS DC Plane %s Raw TDC", pdc_pl_names[npl].c_str()), pdc_nbins, pdc_xmin, pdc_xmax);
      P_dc_rawTDC_CUT[npl] = new TH1F(Form("pDC%s_rawTDC_CUT", pdc_pl_names[npl].c_str()), Form("SHMS DC Plane %s Raw TDC (CUT)", pdc_pl_names[npl].c_str()), pdc_nbins, pdc_xmin, pdc_xmax);
      
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
	      	  
	      n_hhod_TdcTimeUnCorr = base + "." + side_names[iside] + "TdcTimeUnCorr";
	      n_hhod_TdcAdcTimeDiff = base + "." + side_names[iside] + "AdcTdcDiffTime";
	      n_hhod_AdcMult = base + "." + side_names[iside] + "AdcMult";
	      	      
	      T->SetBranchAddress(n_hhod_TdcTimeUnCorr, hhod_TdcTimeUnCorr[npl][iside]);
	      T->SetBranchAddress(n_hhod_TdcAdcTimeDiff, hhod_TdcAdcTimeDiff[npl][iside]);
	      T->SetBranchAddress(n_hhod_AdcMult, hhod_AdcMult[npl][iside]);
	      	      
	      H_hod_TdcTimeUnCorr[npl][iside][ipmt] = new TH1F(Form("hHod%s%d%s_TdcTimeUnCorr", hod_pl_names[npl].c_str(),ipmt+1,nsign[iside].c_str() ), Form("HMS Hodo %s%d%s TdcTimeUnCorr", hod_pl_names[npl].c_str(),ipmt+1,nsign[iside].c_str()),hhod_tnbins,hhod_txmin,hhod_txmax);
	      H_hod_TdcAdcTimeDiff[npl][iside][ipmt] = new TH1F(Form("hHod%s%d%s_timeDiff", hod_pl_names[npl].c_str(),ipmt+1,nsign[iside].c_str() ), Form("HMS Hodo %s%d%s AdcTdcTimeDiff", hod_pl_names[npl].c_str(),ipmt+1,nsign[iside].c_str()),hhod_nbins,hhod_xmin,hhod_xmax);
	      H_hod_TdcAdcTimeDiff_CUT[npl][iside][ipmt] = new TH1F(Form("hHod%s%d%s_timeDiff_CUT", hod_pl_names[npl].c_str(),ipmt+1,nsign[iside].c_str() ), Form("HMS Hodo %s%d%s AdcTdcTimeDiff (CUT)", hod_pl_names[npl].c_str(),ipmt+1,nsign[iside].c_str()),hhod_nbins,hhod_xmin,hhod_xmax);
	      
	    }
	  
	  //Loop over HMS Calorimeter PMTs
	  for (Int_t ipmt = 0; ipmt < 13; ipmt++)
	    {
	      base =  "H.cal." + cal_pl_names[npl];
	      
	      n_hcal_TdcAdcTimeDiff = base + "." + cal_side_names[iside] + "AdcTdcDiffTime";
	      n_hcal_AdcMult = base + "." + cal_side_names[iside] + "AdcMult";

	      T->SetBranchAddress(n_hcal_TdcAdcTimeDiff, hcal_TdcAdcTimeDiff[npl][iside]);
	      T->SetBranchAddress(n_hcal_AdcMult, hcal_AdcMult[npl][iside]);
	  
	      H_cal_TdcAdcTimeDiff[npl][iside][ipmt] = new TH1F(Form("hCal%s%d%s_timeDiff", cal_pl_names[npl].c_str(),ipmt+1,nsign[iside].c_str() ), Form("HMS Cal %s%d%s AdcTdcTimeDiff", cal_pl_names[npl].c_str(),ipmt+1,nsign[iside].c_str()),hcal_nbins,hcal_xmin,hcal_xmax) ;
	      H_cal_TdcAdcTimeDiff_CUT[npl][iside][ipmt] = new TH1F(Form("hCal%s%d%s_timeDiff_CUT", cal_pl_names[npl].c_str(),ipmt+1,nsign[iside].c_str() ), Form("HMS Cal %s%d%s AdcTdcTimeDiff (CUT)", cal_pl_names[npl].c_str(),ipmt+1,nsign[iside].c_str()),hcal_nbins,hcal_xmin,hcal_xmax) ;

	    }


	  //Loop over SHMS hodo PMTs
	  for (Int_t ipmt = 0; ipmt < pmaxPMT[npl]; ipmt++)
	    {
	      base = "P.hod." + hod_pl_names[npl];

	      n_phod_TdcTimeUnCorr = base + "." + side_names[iside] + "TdcTimeUnCorr";
	      n_phod_TdcAdcTimeDiff = base + "." + side_names[iside] + "AdcTdcDiffTime";
	      n_phod_AdcMult = base + "." + side_names[iside] + "AdcMult";
	  		  
	      T->SetBranchAddress(n_phod_TdcTimeUnCorr, phod_TdcTimeUnCorr[npl][iside]);
	      T->SetBranchAddress(n_phod_TdcAdcTimeDiff, phod_TdcAdcTimeDiff[npl][iside]);
	      T->SetBranchAddress(n_phod_AdcMult, phod_AdcMult[npl][iside]);
	    	     	      
	      P_hod_TdcTimeUnCorr[npl][iside][ipmt] = new TH1F(Form("pHod%s%d%s_TdcTimeUnCorr", hod_pl_names[npl].c_str(),ipmt+1,nsign[iside].c_str() ), Form("SHMS Hodo %s%d%s TdcTimeUnCorr", hod_pl_names[npl].c_str(),ipmt+1,nsign[iside].c_str()),phod_tnbins,phod_txmin,phod_txmax);
	      P_hod_TdcAdcTimeDiff[npl][iside][ipmt] = new TH1F(Form("pHod%s%d%s_timeDiff", hod_pl_names[npl].c_str(),ipmt+1,nsign[iside].c_str() ), Form("SHMS Hodo %s%d%s AdcTdcTimeDiff", hod_pl_names[npl].c_str(),ipmt+1,nsign[iside].c_str()),phod_nbins,phod_xmin,phod_xmax);
	      P_hod_TdcAdcTimeDiff_CUT[npl][iside][ipmt] = new TH1F(Form("pHod%s%d%s_timeDiff_CUT", hod_pl_names[npl].c_str(),ipmt+1,nsign[iside].c_str() ), Form("SHMS Hodo %s%d%s AdcTdcTimeDiff (CUT)", hod_pl_names[npl].c_str(),ipmt+1,nsign[iside].c_str()),phod_nbins,phod_xmin,phod_xmax);

	    }
	  
	  if(npl==0)
	    {
	      //Loop over SHMS PreSH PMTs
	      for (Int_t ipmt = 0; ipmt < 14; ipmt++)
		{
		  base =  "P.cal.pr";
		  
		  n_pPrSh_TdcAdcTimeDiff = base + "." + cal_side_names[iside] + "AdcTdcDiffTime";
		  n_pPrSh_AdcMult = base + "." + cal_side_names[iside] + "AdcMult";
		  n_pPrSh_AdcTime = base + "." +  cal_side_names[iside] + "AdcPulseTime";

		  T->SetBranchAddress(n_pPrSh_TdcAdcTimeDiff, pPrSh_TdcAdcTimeDiff[npl][iside]);
		  T->SetBranchAddress(n_pPrSh_AdcMult, pPrSh_AdcMult[npl][iside]);
		  T->SetBranchAddress(n_pPrSh_AdcTime, pPrSh_AdcTime[npl][iside]);

		  P_prSh_TdcAdcTimeDiff[iside][ipmt] = new TH1F(Form("pPrSh_pmt%d%s", ipmt+1, nsign[iside].c_str()), Form("SHMS Pre-Shower PMT_%d%s", ipmt+1, nsign[iside].c_str()), pPrsh_nbins, pPrsh_xmin, pPrsh_xmax);
		  P_prSh_TdcAdcTimeDiff_CUT[iside][ipmt] = new TH1F(Form("pPrSh_pmt%d%s_CUT", ipmt+1, nsign[iside].c_str()), Form("SHMS Pre-Shower PMT_%d%s (CUT)", ipmt+1, nsign[iside].c_str()), pPrsh_nbins, pPrsh_xmin, pPrsh_xmax);
		  P_prSh_AdcTime[iside][ipmt] = new TH1F(Form("pPrShAdcTime_pmt%d%s", ipmt+1, nsign[iside].c_str()), Form("SHMS Pre-Shower Adc Time: PMT_%d%s", ipmt+1, nsign[iside].c_str()), pPrshAdc_nbins, pPrshAdc_xmin, pPrshAdc_xmax);

				  
		}
	      if(iside==0)
		{
		  //Loop over SHMS fly's eye Calorimeter PMTs
		  for (Int_t ipmt = 0; ipmt < 224; ipmt++)
		    {
		      base =  "P.cal.fly";
		      n_pcal_TdcAdcTimeDiff = base + "." + "goodAdcTdcDiffTime";
		      n_pcal_AdcMult = base + "." + "goodAdcMult";
		      n_pcal_AdcTime = base + "." + "goodAdcPulseTime";

		      //For multiplicity, see THcSHowerArray.cxx, for totNumGoodAdcHits, 
		      T->SetBranchAddress(n_pcal_TdcAdcTimeDiff, pcal_TdcAdcTimeDiff[iside]);
		      T->SetBranchAddress(n_pcal_AdcMult, pcal_AdcMult[iside]);
		      T->SetBranchAddress(n_pcal_AdcTime, pcal_AdcTime[iside]);

		      P_cal_TdcAdcTimeDiff[ipmt] = new TH1F(Form("pSh_pmt%d", ipmt+1), Form("SHMS Shower PMT_%d", ipmt+1), pcal_nbins, pcal_xmin, pcal_xmax);
		      P_cal_TdcAdcTimeDiff_CUT[ipmt] = new TH1F(Form("pSh_pmt%d_CUT", ipmt+1), Form("SHMS Shower PMT_%d (CUT)", ipmt+1), pcal_nbins, pcal_xmin, pcal_xmax);
		      P_cal_AdcTime[ipmt] = new TH1F(Form("pShAdcTime_pmt%d", ipmt+1), Form("SHMS Shower Adc Time: PMT_%d", ipmt+1), pcalAdc_nbins, pcalAdc_xmin, pcalAdc_xmax);

		    }
		
		} //end side0 requirement for fly's eye
	      
	    } //End plane 0 requirement for Pre-SHower
	  
	  
	} //End Loop over sides
      
    } //End Loop over planes
  
  
  
  //===================================
  //====== E V E N T    L O O P =======
  //===================================

  Long64_t nentries = T->GetEntries();
  
  //Define A Boolean for multiplicity CUTS
  Bool_t good_Mult;
  
  //Loop over all entries
  for(Long64_t i=0; i<nentries; i++)
    {
      
      T->GetEntry(i); 
      
      
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
	  good_Mult =  hDC_tdcMult[iref] == 2;

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
      good_Mult = pT1_tdcMult == 3;
      P_hodo_Tref1->Fill(pT1_ref);
      if(good_Mult) {P_hodo_Tref1_CUT->Fill(pT1_ref);}
 
      good_Mult = pT2_tdcMult == 3;
      P_hodo_Tref2->Fill(pT2_ref);
      if(good_Mult) {P_hodo_Tref2_CUT->Fill(pT2_ref);}
      
      good_Mult = pFADC_adcMult == 2;
      P_FADC_Tref->Fill(pFADC_ref);
      if(good_Mult) {P_FADC_Tref_CUT->Fill(pFADC_ref);} 

      //------------------------------------------------------------------------------

      //Fill TRG Detector Leafs
      pTrig1_ROC1_rawTdcTime->Fill(ptrg1_r1);
      pTrig1_ROC2_rawTdcTime->Fill(ptrg1_r2);
      pTrig4_ROC1_rawTdcTime->Fill(ptrg4_r1);
      pTrig4_ROC2_rawTdcTime->Fill(ptrg4_r2);
      

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
		  
		  H_hod_TdcTimeUnCorr[ip][iside][ipmt]->Fill(hhod_TdcTimeUnCorr[ip][iside][ipmt]/tdc_nsperch);

		  if(abs(hhod_TdcAdcTimeDiff[ip][iside][ipmt])<1000.)
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

		  
		   
		  if(abs(hcal_TdcAdcTimeDiff[ip][iside][ipmt])<1000.)
		    {
		      good_Mult = hcal_AdcMult[ip][iside][ipmt] == 1;    //HMS CALO Multiplicity ==1
		      //cout << "TimeDiff: " << hcal_TdcAdcTimeDiff[ip][iside][ipmt] << endl;
		      H_cal_TdcAdcTimeDiff[ip][iside][ipmt]->Fill(hcal_TdcAdcTimeDiff[ip][iside][ipmt]);
		      if(good_Mult) {H_cal_TdcAdcTimeDiff_CUT[ip][iside][ipmt]->Fill(hcal_TdcAdcTimeDiff[ip][iside][ipmt]);}

		    }
		}
	      
	      
	      //Loop over SHMS Hodoscopes PMTs
	      for (Int_t ipmt = 0; ipmt < pmaxPMT[ip]; ipmt++)
		{
		  
		

		  //------------SHMS Hodoscopes----------------
		
		  //UnCorrected TdcTime
		  P_hod_TdcTimeUnCorr[ip][iside][ipmt]->Fill(phod_TdcTimeUnCorr[ip][iside][ipmt]/tdc_nsperch);
		  
		  if(abs(phod_TdcAdcTimeDiff[ip][iside][ipmt])<1000.)
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
		  
		  P_prSh_AdcTime[iside][ipmt]->Fill(pPrSh_AdcTime[ip][iside][ipmt]);

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
		    P_cal_AdcTime[ipmt]->Fill(pcal_AdcTime[iside][ipmt]);
		  
		  }
		}
	      


	    } // END LOOP OVER SIDES

	} //END LOOP OVER PLANES
      
      
    } //END EVENT LOOP
  
  
  //======================================================
  //D R A W   H I S T O G R A M S    T O    C A N V A S
  //======================================================
  
  
  //-------Reference Time Histograms----------

  //HMS
  hms_REF_Canv = new TCanvas("REF Times", "HMS REF TIMES",  1500, 500);
  hms_REF_Canv->Divide(3,1);
  
  hT1_Line = new TLine(hhod_trefcut, 0,  hhod_trefcut, H_hodo_Tref->GetMaximum());
  hDCREF_Line = new TLine(hdc_trefcut, 0,  hdc_trefcut, H_DC_Tref[0]->GetMaximum());
  hFADC_Line = new TLine(hadc_trefcut, 0,  hadc_trefcut, H_FADC_Tref->GetMaximum());
  
  hms_REF_Canv->cd(1);
  gPad->SetLogy();
  H_hodo_Tref_CUT->SetLineColor(kRed);
  H_hodo_Tref->Draw();
  H_hodo_Tref_CUT->Draw("sames");
  hT1_Line->SetLineColor(kBlack);
  hT1_Line->SetLineStyle(2);
  hT1_Line->SetLineWidth(3);
  hT1_Line->Draw();
  
  hms_REF_Canv->cd(2);
  gPad->SetLogy();
  H_DC_Tref_CUT[0]->SetLineColor(kRed);
  H_DC_Tref[0]->Draw();
  H_DC_Tref_CUT[0]->Draw("sames");
  H_DC_Tref[1]->Draw("sames");
  H_DC_Tref[2]->Draw("sames");
  H_DC_Tref[3]->Draw("sames");
  hDCREF_Line->SetLineColor(kBlack);
  hDCREF_Line->SetLineStyle(2);
  hDCREF_Line->SetLineWidth(3);
  hDCREF_Line->Draw();
  
  hms_REF_Canv->cd(3);
  gPad->SetLogy();
  H_FADC_Tref_CUT->SetLineColor(kRed);
  H_FADC_Tref->Draw();
  H_FADC_Tref_CUT->Draw("sames");
  hFADC_Line->SetLineColor(kBlack);
  hFADC_Line->SetLineStyle(2);
  hFADC_Line->SetLineWidth(3);
  hFADC_Line->Draw();
  
  hms_REF_Canv->SaveAs(Form("Time_cuts_%d/HMS/refTime/hms_REFTime_cuts.pdf", run));
  
  
  //SHMS
  shms_REF_Canv = new TCanvas("REF Times", "SHMS REF TIMES",  1500, 500);
  shms_REF_Canv->Divide(3,1);
  
  pT2_Line = new TLine(phod_trefcut, 0,  phod_trefcut, P_hodo_Tref2->GetMaximum());
  pDCREF_Line = new TLine(pdc_trefcut, 0,  pdc_trefcut, P_DC_Tref[0]->GetMaximum());
  pFADC_Line = new TLine(padc_trefcut, 0,  padc_trefcut, P_FADC_Tref->GetMaximum());
  
  shms_REF_Canv->cd(1);
  gPad->SetLogy();
  P_hodo_Tref1_CUT->SetLineColor(kRed);
  P_hodo_Tref2_CUT->SetLineColor(kRed); 
  P_hodo_Tref1->Draw();
  P_hodo_Tref2->Draw("sames");
  P_hodo_Tref1_CUT->Draw("sames");
  P_hodo_Tref2_CUT->Draw("sames");  
  pT2_Line->SetLineColor(kBlack);
  pT2_Line->SetLineStyle(2);
  pT2_Line->SetLineWidth(3);
  pT2_Line->Draw();
  
  shms_REF_Canv->cd(2);
  gPad->SetLogy();
  for(Int_t iref=0; iref<10; iref++)
    {
      P_DC_Tref_CUT[iref]->SetLineColor(kRed);

      P_DC_Tref[iref]->Draw("sames");
      P_DC_Tref_CUT[iref]->Draw("sames");
    }
  pDCREF_Line->SetLineColor(kBlack);
  pDCREF_Line->SetLineStyle(2);
  pDCREF_Line->SetLineWidth(3);
  pDCREF_Line->Draw();
  
  shms_REF_Canv->cd(3);
  gPad->SetLogy();
  P_FADC_Tref_CUT->SetLineColor(kRed);
  P_FADC_Tref->Draw();
  P_FADC_Tref_CUT->Draw("sames"); 
  pFADC_Line->SetLineColor(kBlack);
  pFADC_Line->SetLineStyle(2);
  pFADC_Line->SetLineWidth(3);
  pFADC_Line->Draw();
  
  shms_REF_Canv->SaveAs(Form("Time_cuts_%d/SHMS/refTime/shms_REFTime_cuts.pdf", run));
  
  
  
  //-----Setting up Detector Time WIndows----
  
  
  //TRG Detector
  pTRG_Canv = new TCanvas("pTRIG_RawTimes", "pTRIG Raw TDC Times", 1500, 1500);
  pTRG_Canv->Divide(2,2);
  

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

  pTRG_Canv->cd(1);
  gPad->SetLogy();
  pTrig1_ROC1_rawTdcTime->Draw();
  ptrg1r1_LineMin->Draw();
  ptrg1r1_LineMax->Draw();
  
  pTRG_Canv->cd(2);
  gPad->SetLogy();
  pTrig1_ROC2_rawTdcTime->Draw();
  ptrg1r2_LineMin->Draw();
  ptrg1r2_LineMax->Draw();

  pTRG_Canv->cd(3);
  gPad->SetLogy();
  pTrig4_ROC1_rawTdcTime->Draw();
  ptrg4r1_LineMin->Draw();
  ptrg4r1_LineMax->Draw();
  
  pTRG_Canv->cd(4);
  gPad->SetLogy();
  pTrig4_ROC2_rawTdcTime->Draw();
  ptrg4r2_LineMin->Draw();
  ptrg4r2_LineMax->Draw();

  pTRG_Canv->SaveAs(Form("Time_cuts_%d/coin_trg_tWin.pdf",run));
  
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
	  
	  //Set Min/Max Line Limits
	  hCER_LineMin[ipmt] = new TLine(hCer_tWinMin[ipmt], 0, hCer_tWinMin[ipmt], H_cer_TdcAdcTimeDiff[ipmt]->GetMaximum());
	  hCER_LineMax[ipmt] = new TLine(hCer_tWinMax[ipmt], 0, hCer_tWinMax[ipmt], H_cer_TdcAdcTimeDiff[ipmt]->GetMaximum());
	  
	  hCER_LineMin[ipmt]->SetLineColor(kBlack);
	  hCER_LineMax[ipmt]->SetLineColor(kBlack);
	  	  
	  hCER_LineMin[ipmt]->SetLineStyle(2);
	  hCER_LineMax[ipmt]->SetLineStyle(2);

	  hCer_Canv->cd(ipmt+1);
	  H_cer_TdcAdcTimeDiff_CUT[ipmt]->SetLineColor(kRed);
	  H_cer_TdcAdcTimeDiff[ipmt]->Draw();
	  H_cer_TdcAdcTimeDiff_CUT[ipmt]->Draw("sames");
	  hCER_LineMin[ipmt]->Draw();
	  hCER_LineMax[ipmt]->Draw();
	}
      
      //======================
      // HEAVY GAS CHERENKOV
      //======================
      
      //Set Min/Max Line Limits
      phgcer_LineMin[ipmt] = new TLine(phgcer_tWinMin[ipmt], 0, phgcer_tWinMin[ipmt], P_hgcer_TdcAdcTimeDiff[ipmt]->GetMaximum());
      phgcer_LineMax[ipmt] = new TLine(phgcer_tWinMax[ipmt], 0, phgcer_tWinMax[ipmt], P_hgcer_TdcAdcTimeDiff[ipmt]->GetMaximum());
      
      phgcer_LineMin[ipmt]->SetLineColor(kBlack);
      phgcer_LineMax[ipmt]->SetLineColor(kBlack);
      
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
      
      //===========================
      //====NOBLE GAS CHERENKOV====
      //===========================
      
      //Set Min/Max Line Limits
      pngcer_LineMin[ipmt] = new TLine(pngcer_tWinMin[ipmt], 0, pngcer_tWinMin[ipmt], P_ngcer_TdcAdcTimeDiff[ipmt]->GetMaximum());
      pngcer_LineMax[ipmt] = new TLine(pngcer_tWinMax[ipmt], 0, pngcer_tWinMax[ipmt], P_ngcer_TdcAdcTimeDiff[ipmt]->GetMaximum());
      
      pngcer_LineMin[ipmt]->SetLineColor(kBlack);
      pngcer_LineMax[ipmt]->SetLineColor(kBlack);
      
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
      
    } //end loop over cer pmts
  

  //Save CHerenkovs to Canvas
  hCer_Canv->SaveAs(Form("Time_cuts_%d/HMS/CER/hCER_timeWindow.pdf",run));
  phgCer_Canv->SaveAs(Form("Time_cuts_%d/SHMS/CER/pHGCER_timeWindow.pdf",run));
  pngCer_Canv->SaveAs(Form("Time_cuts_%d/SHMS/CER/pNGCER_timeWindow.pdf",run));
  
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

      hdc_LineMin[npl] = new TLine(hDC_tWinMin[npl], 0, hDC_tWinMin[npl], H_dc_rawTDC[npl]->GetMaximum());
      hdc_LineMax[npl] = new TLine(hDC_tWinMax[npl], 0, hDC_tWinMax[npl], H_dc_rawTDC[npl]->GetMaximum());

      hdc_LineMin[npl]->SetLineColor(kBlack);
      hdc_LineMax[npl]->SetLineColor(kBlack);
      
      hdc_LineMin[npl]->SetLineStyle(2);
      hdc_LineMax[npl]->SetLineStyle(2);

      hdcCanv->cd(npl+1);
      gPad->SetLogy();
      H_dc_rawTDC_CUT[npl]->SetLineColor(kRed);
      H_dc_rawTDC[npl]->Draw();
      H_dc_rawTDC_CUT[npl]->Draw("sames");
      hdc_LineMin[npl]->Draw();
      hdc_LineMax[npl]->Draw();

      //SHMS  
      pdc_LineMin[npl] = new TLine(pDC_tWinMin[npl], 0, pDC_tWinMin[npl], P_dc_rawTDC[npl]->GetMaximum());
      pdc_LineMax[npl] = new TLine(pDC_tWinMax[npl], 0, pDC_tWinMax[npl], P_dc_rawTDC[npl]->GetMaximum());
      
      pdc_LineMin[npl]->SetLineColor(kBlack);
      pdc_LineMax[npl]->SetLineColor(kBlack);
           
      pdc_LineMin[npl]->SetLineStyle(2);
      pdc_LineMax[npl]->SetLineStyle(2);
      
      pdcCanv->cd(npl+1);
      gPad->SetLogy();
      P_dc_rawTDC_CUT[npl]->SetLineColor(kRed);
      P_dc_rawTDC[npl]->Draw();
      P_dc_rawTDC_CUT[npl]->Draw("sames");
      pdc_LineMin[npl]->Draw();
      pdc_LineMax[npl]->Draw();
      
    } //end dc plane loop
  
  
  //Save DC to Canvas
  hdcCanv->SaveAs(Form("Time_cuts_%d/HMS/DC/hDC_rawTDC_window.pdf",run));
  pdcCanv->SaveAs(Form("Time_cuts_%d/SHMS/DC/pDC_rawTDC_window.pdf",run));
  
  
  //HODOSCOPES / CALORIMETERS
  //Loop over planes
  for (Int_t npl = 0; npl < hod_PLANES; npl++ )
    {      
      
      //Loop over plane side
      for (Int_t iside = 0; iside < SIDES; iside++)
	{  
	  
	  //Define HMS Hodo Canv
	  hhodoCanv[npl][iside] = new TCanvas(Form("hhodo_TDC:ADC Time Diff. Hod Plane %s%s", hod_pl_names[npl].c_str(), side_names[iside].c_str()), Form("HMS Hodo TDC-ADC Time Diff, Plane %s%s", hod_pl_names[npl].c_str(), side_names[iside].c_str()),  1500, 600);
	  hhodo_tdcCanv[npl][iside] = new TCanvas(Form("hhodo_TDC UnCorr Time Hod Plane %s%s", hod_pl_names[npl].c_str(), side_names[iside].c_str()), Form("HMS Hodo TDC Time UnCorr, Plane %s%s", hod_pl_names[npl].c_str(), side_names[iside].c_str()),  1500, 600);

	  
	  //Define SHMS Hodo Canv
	  phodoCanv[npl][iside] = new TCanvas(Form("phodo_TDC:ADC Time Diff. Hod Plane %s%s", hod_pl_names[npl].c_str(), side_names[iside].c_str()), Form("SHMS Hodo TDC-ADC Time Diff, Plane %s%s", hod_pl_names[npl].c_str(), side_names[iside].c_str()),  1500, 600);
	  phodo_tdcCanv[npl][iside] = new TCanvas(Form("phodo_TDC UnCorr Time Hod Plane %s%s", hod_pl_names[npl].c_str(), side_names[iside].c_str()), Form("SHMS Hodo TDC Time UnCorr, Plane %s%s", hod_pl_names[npl].c_str(), side_names[iside].c_str()),  1500, 600);

	  
	  //Define HMS Calorimeter Canvas for all planes
	  if (!(npl==2&&iside==1) && !(npl==3&&iside==1)){
	    hcaloCanv[npl][iside] = new TCanvas(Form("hcalo_TDC:ADC Time Diff. Cal Plane %s%s", cal_pl_names[npl].c_str(), cal_side_names[iside].c_str()), Form("Calo TDC:ADC Time Diff, Plane %s %s", cal_pl_names[npl].c_str(), cal_side_names[iside].c_str()),  1500, 600);
	    hcaloCanv[npl][iside]->Divide(5,3);	     
	  }
	  
	  
	  //Define SHMS PreShower and Calorimeter Canvas
	  if(npl==0)
	    {
	      pPrshCanv[iside] =  new TCanvas(Form("pPrSh_TDC:ADC Time Diff %s", cal_side_names[iside].c_str()), Form("SHMS PreShower TDC:ADC Time Diff %s",  cal_side_names[iside].c_str()),  1500, 600);
	      pPrshAdcCanv[iside] =  new TCanvas(Form("pPrSh_ADC Time %s", cal_side_names[iside].c_str()), Form("SHMS PreShower ADC Time %s",  cal_side_names[iside].c_str()),  1500, 600);

	    }
	  
	  
	  //Divide HMS Hodo Canvas Accordingly
	  if(npl == 0 || npl == 2)
	    {
	      hhodoCanv[npl][iside]->Divide(4,4);
	      hhodo_tdcCanv[npl][iside]->Divide(4,4);

	    }
	  
	  else if (npl==1 || npl==3)
	    {
	      hhodoCanv[npl][iside]->Divide(5,2);
	      hhodo_tdcCanv[npl][iside]->Divide(5,2);
	    }
	  
	  
	  //Divide SHMS Hodo Canvas Accordingly
	  if(npl == 0 || npl == 1 || npl==2)
	    {
	      phodoCanv[npl][iside]->Divide(7,2);
	      phodo_tdcCanv[npl][iside]->Divide(7,2);

	    }
	  
	  else if (npl==3)
	    {
	      phodoCanv[npl][iside]->Divide(7,3);
	      phodo_tdcCanv[npl][iside]->Divide(7,3);

	    }
	  
	  
	  //Divide SHMS PreSh / Calo Canvas Accordingly
	  if(npl==0)
	    {
	      
	      pPrshCanv[iside]->Divide(7,2);
	      pPrshAdcCanv[iside]->Divide(7,2);

	    }
	  
	  
	  
	  //Loop over HMS HODO PMTs
	  for (Int_t ipmt = 0; ipmt < hmaxPMT[npl]; ipmt++)
	    {
	      //Get Mean and Sigma
	      binmax = H_hod_TdcAdcTimeDiff_CUT[npl][iside][ipmt]->GetMaximumBin();

	      mean = H_hod_TdcAdcTimeDiff_CUT[npl][iside][ipmt]->GetXaxis()->GetBinCenter(binmax);
	      sig =  H_hod_TdcAdcTimeDiff_CUT[npl][iside][ipmt]->GetStdDev();
	      
	      //Set Time Window Cuts
	      hhodo_tWinMin[npl][iside][ipmt] = mean - 4.0*sig;
	      hhodo_tWinMax[npl][iside][ipmt] = mean + 5.5*sig;
	      
	      //Exceptions to CUTS
	      if(npl==1&&iside==0){
		if(ipmt==3||ipmt==4){
		hhodo_tWinMin[npl][iside][ipmt] = -61.;
		hhodo_tWinMax[npl][iside][ipmt] = -53.;
		}
	      
	      }
	      if(npl==1&&iside==1){
		if(ipmt==0){
		hhodo_tWinMin[npl][iside][ipmt] = -65.;
		hhodo_tWinMax[npl][iside][ipmt] = -50.;
		}
		if(ipmt==4){
		hhodo_tWinMin[npl][iside][ipmt] = -64.;
		hhodo_tWinMax[npl][iside][ipmt] = -55.;
		}

	      }
	      if(npl==3&&iside==1){
		if(ipmt==0){
		hhodo_tWinMin[npl][iside][ipmt] = -63.;
		hhodo_tWinMax[npl][iside][ipmt] = -52.;
		}
		if(ipmt==1){
		hhodo_tWinMin[npl][iside][ipmt] = -63.;
		hhodo_tWinMax[npl][iside][ipmt] = -52.;
		}
		if(ipmt==9){
		hhodo_tWinMin[npl][iside][ipmt] = -61.;
		hhodo_tWinMax[npl][iside][ipmt] = -50.;
		}
		if(ipmt==8){
		hhodo_tWinMin[npl][iside][ipmt] = -61.;
		hhodo_tWinMax[npl][iside][ipmt] = -51.;
		}
		if(ipmt==7){
		hhodo_tWinMin[npl][iside][ipmt] = -61.;
		hhodo_tWinMax[npl][iside][ipmt] = -51.;
		}
	      }

	            
	      //Set Min/Max Line Limits
	      hhod_LineMin[npl][iside][ipmt] = new TLine(hhodo_tWinMin[npl][iside][ipmt], 0, hhodo_tWinMin[npl][iside][ipmt], H_hod_TdcAdcTimeDiff[npl][iside][ipmt]->GetMaximum());
	      hhod_LineMax[npl][iside][ipmt] = new TLine(hhodo_tWinMax[npl][iside][ipmt], 0, hhodo_tWinMax[npl][iside][ipmt], H_hod_TdcAdcTimeDiff[npl][iside][ipmt]->GetMaximum());

	      hhod_LineMin[npl][iside][ipmt]->SetLineColor(kBlack);
	      hhod_LineMax[npl][iside][ipmt]->SetLineColor(kBlack);
	      
	      hhod_LineMin[npl][iside][ipmt]->SetLineStyle(2);
	      hhod_LineMax[npl][iside][ipmt]->SetLineStyle(2);
	      
	      hhodoCanv[npl][iside]->cd(ipmt+1);
	      gPad->SetLogy();
	      H_hod_TdcAdcTimeDiff_CUT[npl][iside][ipmt]->SetLineColor(kRed);
	      H_hod_TdcAdcTimeDiff[npl][iside][ipmt]->Draw();
	      H_hod_TdcAdcTimeDiff_CUT[npl][iside][ipmt]->Draw("sames");
	      hhod_LineMin[npl][iside][ipmt]->Draw();
	      hhod_LineMax[npl][iside][ipmt]->Draw();
	         
	      hhodo_tdcCanv[npl][iside]->cd(ipmt+1);
	      gPad->SetLogy();
	      H_hod_TdcTimeUnCorr[npl][iside][ipmt]->Draw();

	      

	    } //end hms hodo pmt loop
	  
	  //Loop over SHMS HODO PMTs
	  for (Int_t ipmt = 0; ipmt < pmaxPMT[npl]; ipmt++)
	    {
	      //Get Mean and Sigma
	      binmax = P_hod_TdcAdcTimeDiff_CUT[npl][iside][ipmt]->GetMaximumBin();
	      mean = P_hod_TdcAdcTimeDiff_CUT[npl][iside][ipmt]->GetXaxis()->GetBinCenter(binmax);
	      sig =  P_hod_TdcAdcTimeDiff_CUT[npl][iside][ipmt]->GetStdDev();
	      
	      //Set Time Window Cuts
	      phodo_tWinMin[npl][iside][ipmt] = mean - 6.0*sig;
	      phodo_tWinMax[npl][iside][ipmt] = mean + 7.5*sig;
	      
	            
	      //Set Min/Max Line Limits
	      phod_LineMin[npl][iside][ipmt] = new TLine(phodo_tWinMin[npl][iside][ipmt], 0, phodo_tWinMin[npl][iside][ipmt], P_hod_TdcAdcTimeDiff[npl][iside][ipmt]->GetMaximum());
	      phod_LineMax[npl][iside][ipmt] = new TLine(phodo_tWinMax[npl][iside][ipmt], 0, phodo_tWinMax[npl][iside][ipmt], P_hod_TdcAdcTimeDiff[npl][iside][ipmt]->GetMaximum());

	      phod_LineMin[npl][iside][ipmt]->SetLineColor(kBlack);
	      phod_LineMax[npl][iside][ipmt]->SetLineColor(kBlack);
	      
	      phod_LineMin[npl][iside][ipmt]->SetLineStyle(2);
	      phod_LineMax[npl][iside][ipmt]->SetLineStyle(2);

	      phodoCanv[npl][iside]->cd(ipmt+1);
	      gPad->SetLogy();
	      P_hod_TdcAdcTimeDiff_CUT[npl][iside][ipmt]->SetLineColor(kRed);
	      P_hod_TdcAdcTimeDiff[npl][iside][ipmt]->Draw();
	      P_hod_TdcAdcTimeDiff_CUT[npl][iside][ipmt]->Draw("sames");
	      phod_LineMin[npl][iside][ipmt]->Draw();
	      phod_LineMax[npl][iside][ipmt]->Draw();
	      
	      phodo_tdcCanv[npl][iside]->cd(ipmt+1);
	      gPad->SetLogy();
	      P_hod_TdcTimeUnCorr[npl][iside][ipmt]->Draw();


	      } //end shms hodo pmt loop
	  
	  
	  //Loop over HMS Calorimeter pmts
	  for (Int_t ipmt = 0; ipmt < 13; ipmt++)
	    {
	      //Get Mean and Sigma
	      binmax = H_cal_TdcAdcTimeDiff_CUT[npl][iside][ipmt]->GetMaximumBin();
	      mean = H_cal_TdcAdcTimeDiff_CUT[npl][iside][ipmt]->GetXaxis()->GetBinCenter(binmax);
	      sig =  H_cal_TdcAdcTimeDiff_CUT[npl][iside][ipmt]->GetStdDev();
	      
	      //Set Time Window Cuts
	      hCal_tWinMin[npl][iside][ipmt] = mean - 3.2*sig;
	      hCal_tWinMax[npl][iside][ipmt] = mean + 4.5*sig;                                                                                                          
	      
	      //Set Min/Max Line Limits
	      hcal_LineMin[npl][iside][ipmt] = new TLine(hCal_tWinMin[npl][iside][ipmt], 0, hCal_tWinMin[npl][iside][ipmt], H_cal_TdcAdcTimeDiff[npl][iside][ipmt]->GetMaximum());
	      hcal_LineMax[npl][iside][ipmt] = new TLine(hCal_tWinMax[npl][iside][ipmt], 0, hCal_tWinMax[npl][iside][ipmt], H_cal_TdcAdcTimeDiff[npl][iside][ipmt]->GetMaximum());

	      hcal_LineMin[npl][iside][ipmt]->SetLineColor(kBlack);
	      hcal_LineMax[npl][iside][ipmt]->SetLineColor(kBlack);
	      
	      hcal_LineMin[npl][iside][ipmt]->SetLineStyle(2);
	      hcal_LineMax[npl][iside][ipmt]->SetLineStyle(2);

	      if (!(npl==2&&iside==1) && !(npl==3&&iside==1)){
	      hcaloCanv[npl][iside]->cd(ipmt+1);
	      gPad->SetLogy();
	      H_cal_TdcAdcTimeDiff_CUT[npl][iside][ipmt]->SetLineColor(kRed);
	      H_cal_TdcAdcTimeDiff[npl][iside][ipmt]->Draw();
	      H_cal_TdcAdcTimeDiff_CUT[npl][iside][ipmt]->Draw("sames");
	      hcal_LineMin[npl][iside][ipmt]->Draw();
	      hcal_LineMax[npl][iside][ipmt]->Draw();
	      
	      }
	    } //end pmt loop
	  
	    //Loop over SHMS PreSh PMTs
	  for(int ipmt=0; ipmt<14; ipmt++)
	    {
	      if (npl!=0) continue;

	      //Set Min/Max Line Limits
	      pPrsh_LineMin[iside][ipmt] = new TLine(pPrsh_tWinMin[iside][ipmt], 0, pPrsh_tWinMin[iside][ipmt], P_prSh_TdcAdcTimeDiff[iside][ipmt]->GetMaximum());
	      pPrsh_LineMax[iside][ipmt] = new TLine(pPrsh_tWinMax[iside][ipmt], 0, pPrsh_tWinMax[iside][ipmt], P_prSh_TdcAdcTimeDiff[iside][ipmt]->GetMaximum());
	      
	      pPrsh_LineMin[iside][ipmt]->SetLineColor(kBlack);
	      pPrsh_LineMax[iside][ipmt]->SetLineColor(kBlack);
	       
	      pPrsh_LineMin[iside][ipmt]->SetLineStyle(2);
	      pPrsh_LineMax[iside][ipmt]->SetLineStyle(2);
	      
	      pPrshCanv[iside]->cd(ipmt+1);
	      gPad->SetLogy();
	      P_prSh_TdcAdcTimeDiff_CUT[iside][ipmt]->SetLineColor(kRed);
	      P_prSh_TdcAdcTimeDiff[iside][ipmt]->Draw();
	      P_prSh_TdcAdcTimeDiff_CUT[iside][ipmt]->Draw("sames");
	      pPrsh_LineMin[iside][ipmt]->Draw();
	      pPrsh_LineMax[iside][ipmt]->Draw();
	      	      
	      pPrshAdcCanv[iside]->cd(ipmt+1);
	      gPad->SetLogy();
	      P_prSh_AdcTime[iside][ipmt]->Draw();



	    } //end pmt loop
	  	  
	  if(iside==0)
	    {
	      //Loop over SHMS FLy's Eye PMTs
	      for(int ipmt=0; ipmt<224; ipmt++)
		{
		  //Get Mean and Sigma
		  binmax =  P_cal_TdcAdcTimeDiff_CUT[ipmt]->GetMaximumBin();
		  mean = P_cal_TdcAdcTimeDiff_CUT[ipmt]->GetXaxis()->GetBinCenter(binmax);
		  sig =  P_cal_TdcAdcTimeDiff_CUT[ipmt]->GetStdDev();
		  
		  //Set Time Window Cuts
		  pCal_tWinMin[ipmt] = mean - pcal_nSig*sig;
		  pCal_tWinMax[ipmt] = mean + pcal_nSig*sig;                                                                                                          
		  
		  //Set Min/Max Line Limits
		  pcal_LineMin[ipmt] = new TLine(pCal_tWinMin[ipmt], 0, pCal_tWinMin[ipmt], P_cal_TdcAdcTimeDiff[ipmt]->GetMaximum());
		  pcal_LineMax[ipmt] = new TLine(pCal_tWinMax[ipmt], 0, pCal_tWinMax[ipmt], P_cal_TdcAdcTimeDiff[ipmt]->GetMaximum());
		  
		  pcal_LineMin[ipmt]->SetLineColor(kBlack);
		  pcal_LineMax[ipmt]->SetLineColor(kBlack);
		  
		  pcal_LineMin[ipmt]->SetLineStyle(2);
		  pcal_LineMax[ipmt]->SetLineStyle(2);

		} // End FLys Eye PMT loop
	      
	     

	    } //ennd single side requirement
	
	  
	  
	  hhodoCanv[npl][iside]->SaveAs(Form("Time_cuts_%d/HMS/HODO/hHodo_%s%s.pdf",run, hod_pl_names[npl].c_str(), side_names[iside].c_str()));
	  phodoCanv[npl][iside]->SaveAs(Form("Time_cuts_%d/SHMS/HODO/pHodo_%s%s.pdf",run, hod_pl_names[npl].c_str(), side_names[iside].c_str()));
	  	  
	  hhodo_tdcCanv[npl][iside]->SaveAs(Form("Time_cuts_%d/HMS/HODO/hHodo_TdcUnCorr%s%s.pdf",run, hod_pl_names[npl].c_str(), side_names[iside].c_str()));
	  phodo_tdcCanv[npl][iside]->SaveAs(Form("Time_cuts_%d/SHMS/HODO/pHodo_TdcUnCorr%s%s.pdf",run, hod_pl_names[npl].c_str(), side_names[iside].c_str()));

	  if (!(npl==2&&iside==1) && !(npl==3&&iside==1)){
	    hcaloCanv[npl][iside]->SaveAs(Form("Time_cuts_%d/HMS/CAL/hCalo_%s%s.pdf", run,cal_pl_names[npl].c_str(), side_names[iside].c_str()));
	  }
	  
	  if(npl==0){
	    pPrshCanv[iside]->SaveAs(Form("Time_cuts_%d/SHMS/CAL/pPrsh_%s.pdf",run, side_names[iside].c_str()));
	    pPrshAdcCanv[iside]->SaveAs(Form("Time_cuts_%d/SHMS/CAL/pPrshAdc_%s.pdf",run, side_names[iside].c_str()));

	  }
	  
	  
	} //end side loop


    } //end plane loop

  //------------------------x


 int ipmt = 0; //initialize pmt counter
 
 //Alternative Cal Plot
 for(int row=0; row < 16; row++)
   {

     pcalCanv[row] =  new TCanvas(Form("pCal_row_%d", row+1), Form("SHMS Calo TDC:ADC Time Diff, Row %d", row+1),  1500, 600);
     pcalCanv[row]->Divide(7,2);

     pcalAdcCanv[row] =  new TCanvas(Form("pCalAdc_row_%d", row+1), Form("SHMS Calo ADC Time, Row %d", row+1),  1500, 600);
     pcalAdcCanv[row]->Divide(7,2);

     for(int col=0; col<14; col++)
       {
	 	 
	 //Get Mean and Sigma
	 binmax =  P_cal_TdcAdcTimeDiff_CUT[ipmt]->GetMaximumBin();
	 mean = P_cal_TdcAdcTimeDiff_CUT[ipmt]->GetXaxis()->GetBinCenter(binmax);
	 sig =  P_cal_TdcAdcTimeDiff_CUT[ipmt]->GetStdDev();
	 
	 //Set Time Window Cuts
	 pCal_tWinMin[ipmt] = mean - pcal_nSig*sig;
	 pCal_tWinMax[ipmt] = mean + pcal_nSig*sig;                                                                                                          
	 
	 //Set Min/Max Line Limits
	 pcal_LineMin[ipmt] = new TLine(pCal_tWinMin[ipmt], 0, pCal_tWinMin[ipmt], P_cal_TdcAdcTimeDiff[ipmt]->GetMaximum());
	 pcal_LineMax[ipmt] = new TLine(pCal_tWinMax[ipmt], 0, pCal_tWinMax[ipmt], P_cal_TdcAdcTimeDiff[ipmt]->GetMaximum());
	 
	 pcal_LineMin[ipmt]->SetLineColor(kBlack);
	 pcal_LineMax[ipmt]->SetLineColor(kBlack);
	 
	 pcal_LineMin[ipmt]->SetLineStyle(2);
	 pcal_LineMax[ipmt]->SetLineStyle(2);
	 
	 
	 //cd to row pads / column
	 pcalCanv[row]->cd(col+1);
	 gPad->SetLogy();
	 P_cal_TdcAdcTimeDiff_CUT[ipmt]->SetLineColor(kRed);
	 P_cal_TdcAdcTimeDiff[ipmt]->Draw();
	 P_cal_TdcAdcTimeDiff_CUT[ipmt]->Draw("sames");
	 pcal_LineMin[ipmt]->Draw();
	 pcal_LineMax[ipmt]->Draw();

	 pcalAdcCanv[row]->cd(col+1);
	 gPad->SetLogy();
	 P_cal_AdcTime[ipmt]->Draw();


	 //increment pmt counter
	 ipmt++;



       }//end loop over rows
     
     //Save Each Cal. Column
     pcalCanv[row]->SaveAs(Form("Time_cuts_%d/SHMS/CAL/pCal_row%d.pdf",run, row+1));
     pcalAdcCanv[row]->SaveAs(Form("Time_cuts_%d/SHMS/CAL/pCalAdc_row%d.pdf",run, row+1));

   }//end loop over columns
 

 


 
 //Write Histograms to ROOT file
 outROOT->Write();
 outROOT->Close();
  
 
  
 
  //------------Write Time Window Min/Max Limits to Parameter File---------------

 string n_side[2] = {"Pos", "Neg"};
 string n_side_cal[2] = {"pos", "neg"};
 string n_lim[2] = {"Min", "Max"};
 
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
 out_hhodo.open(Form("../../PARAM/HMS/HODO/hhodo_tWin_%d.param", run));
 out_hhodo << "; HMS Hodoscope Parameter File Containing TimeWindow Min/Max Cuts " << endl;
 out_hhodo << " " << endl;
 out_hhodo << " " << endl;
 out_hhodo << " " << endl;
 //SHMS Hodo
 out_phodo.open(Form("../../PARAM/SHMS/HODO/phodo_tWin_%d.param", run));
 out_phodo << "; SHMS Hodoscope Parameter File Containing TimeWindow Min/Max Cuts " << endl;
 out_phodo << " " << endl;
 out_phodo << " " << endl;
 out_phodo << " " << endl;
 //HMS Cal
 out_hcal.open(Form("../../PARAM/HMS/CAL/hcal_tWin_%d.param", run));
 out_hcal << "; HMS Calorimeter Parameter File Containing TimeWindow Min/Max Cuts " << endl;
 out_hcal << " " << endl;
 out_hcal << " " << endl;
 out_hcal << " " << endl;
 //SHMS PreSh
 out_pprsh.open(Form("../../PARAM/SHMS/CAL/pprsh_tWin_%d.param", run));
 out_pprsh << "; SHMS Pre-Shower Parameter File Containing TimeWindow Min/Max Cuts " << endl;
 out_pprsh << " " << endl;
 out_pprsh << " " << endl;
 out_pprsh << " " << endl;
 //SHMS Fly's Eye Cal
 out_pcal.open(Form("../../PARAM/SHMS/CAL/pcal_tWin_%d.param", run));
 out_pcal << "; SHMS Fly's Eye Calorimeter  Parameter File Containing TimeWindow Min/Max Cuts " << endl;
 out_pcal << " " << endl;
 out_pcal << " " << endl;
 out_pcal << " " << endl;
 //HMS DC
 out_hdc.open(Form("../../PARAM/HMS/DC/hdc_tWin_%d.param", run));
 out_hdc << "; HMS DC  Parameter File Containing TimeWindow Min/Max Cuts " << endl;
 out_hdc << " " << endl;
 out_hdc << " " << endl;
 out_hdc << " " << endl;
 //SHMS DC
 out_pdc.open(Form("../../PARAM/SHMS/DC/pdc_tWin_%d.param", run));
 out_pdc << "; SHMS DC  Parameter File Containing TimeWindow Min/Max Cuts " << endl;
 out_pdc << " " << endl;
 out_pdc << " " << endl;
 out_pdc << " " << endl;
 //HMS Cer
 out_hcer.open(Form("../../PARAM/HMS/CER/hcer_tWin_%d.param", run));
 out_hcer << "; HMS Cer  Parameter File Containing TimeWindow Min/Max Cuts " << endl;
 out_hcer << " " << endl;
 out_hcer << " " << endl;
 out_hcer << " " << endl;
//SHMS HGCER
 out_phgcer.open(Form("../../PARAM/SHMS/HGCER/phgcer_tWin_%d.param", run));
 out_phgcer << "; SHMS Heavy Gas Cer  Parameter File Containing TimeWindow Min/Max Cuts " << endl;
 out_phgcer << " " << endl;
 out_phgcer << " " << endl;
 out_phgcer << " " << endl;
//SHMS NGCER
 out_pngcer.open(Form("../../PARAM/SHMS/NGCER/pngcer_tWin_%d.param", run));
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
	    out_hhodo << Form("hhodo_%sAdcTimeWindow%s = ", n_side[iside].c_str(), n_lim[lim].c_str());

	    
	    //SHMS Hodo
	    out_phodo << "" << endl;
	    out_phodo << "; " << setw(32) << "1x " << setw(19) << "1y " << setw(16) << "2x " << setw(16) << "2y " << endl;
	    out_phodo << Form("phodo_%sAdcTimeWindow%s = ", n_side[iside].c_str(), n_lim[lim].c_str());

	    //HMS Calorimeter
	    out_hcal << "" << endl;
	    out_hcal << Form("hcal_%s_AdcTimeWindow%s = ", n_side_cal[iside].c_str(), n_lim[lim].c_str());
	    
	    //SHMS PreSHower
	    out_pprsh << "" << endl;
	    out_pprsh << Form("pcal_%s_AdcTimeWindow%s = ", n_side_cal[iside].c_str(), n_lim[lim].c_str());
	 
	    if(iside==0){
	    //SHMS Fly's Eye
	    out_pcal << "" << endl;
	    out_pcal << Form("pcal_arr_AdcTimeWindow%s = ", n_lim[lim].c_str());
	   
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
	    out_hhodo << Form("hhodo_%sAdcTimeWindow%s = ", n_side[iside].c_str(), n_lim[lim].c_str());

	    //SHMS Hodo
	    out_phodo << "" << endl;
	    out_phodo << "; " << setw(32) << "1x " << setw(19) << "1y " << setw(16) << "2x " << setw(16) << "2y " << endl;
	    out_phodo << Form("phodo_%sAdcTimeWindow%s = ", n_side[iside].c_str(), n_lim[lim].c_str());

	    //HMS Calorimeter
	    out_hcal << "" << endl;
	    out_hcal << Form("hcal_%s_AdcTimeWindow%s = ", n_side_cal[iside].c_str(), n_lim[lim].c_str());
	    
	    //SHMS PreSHower
	    out_pprsh << "" << endl;
	    out_pprsh << Form("pcal_%s_AdcTimeWindow%s = ", n_side_cal[iside].c_str(), n_lim[lim].c_str());
	    
	    if(iside==0){
	    //SHMS Fly's Eye
	    out_pcal << "" << endl;
	    out_pcal << Form("pcal_arr_AdcTimeWindow%s = ", n_lim[lim].c_str());
	    
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



  /*
  //------------------Write CHerenkov Time Window Cuts to Param File------------------------
 
  outPARAM.open(Form("../PARAM/HMS/CER/hCer_tWin_%d.param", run));
  //outPARAM.open(Form("./hCer_tWin_%d.param", run));
  
  outPARAM << "; HMS Cherenkov Parameter File Containing TimeWindow Min/Max Cuts " << endl;
  outPARAM << " " << endl;
  outPARAM << " " << endl;
  outPARAM << "hcer_adcTimeWindowMin =" << hCer_tWinMin[0] << "," << hCer_tWinMin[1] << endl;
  outPARAM << "hcer_adcTimeWindowMax =" << hCer_tWinMax[0] << "," << hCer_tWinMax[1] << endl;
  outPARAM.close();
  //--------------Write DC Time Window Cuts to Parameter File--------------------------------
  
  outPARAM.open(Form("../PARAM/HMS/DC/hDC_tWin_%d.param", run));
  //outPARAM.open(Form("./hDC_tWin_%d.param", run));
  
  outPARAM << "; HMS DC Parameter File Containing TimeWindow Min/Max Cuts " << endl;
  outPARAM << " " << endl;
  outPARAM << " " << endl;
  outPARAM << "hdc_tdc_min_win = " << setprecision(2) << hDC_tWinMin[0] << ", " << hDC_tWinMin[1] << ", " << hDC_tWinMin[2] << ", " << hDC_tWinMin[3] << ", " << hDC_tWinMin[4] << ", " << hDC_tWinMin[5] <<endl;
  outPARAM << setw(27) << setprecision(2) << hDC_tWinMin[6] << ", " << hDC_tWinMin[7] << ", " << hDC_tWinMin[8] << ", " << hDC_tWinMin[9] << ", " << hDC_tWinMin[10] << ", " << hDC_tWinMin[11] <<endl;
  outPARAM << "hdc_tdc_max_win = " << setprecision(2) << hDC_tWinMax[0] << ", " << hDC_tWinMax[1] << ", " << hDC_tWinMax[2] << ", " << hDC_tWinMax[3] << ", " << hDC_tWinMax[4] << ", " << hDC_tWinMax[5] <<endl;
  outPARAM << setw(27) << setprecision(2) << hDC_tWinMax[6] << ", " << hDC_tWinMax[7] << ", " << hDC_tWinMax[8] << ", " << hDC_tWinMax[9] << ", " << hDC_tWinMax[10] << ", " << hDC_tWinMax[11] <<endl;
  outPARAM.close();
  */
} //end program
