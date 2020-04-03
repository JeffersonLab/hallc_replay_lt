#define SHMSADCGates_cxx
// The class definition in SHMSADCGates.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.


// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// root> T->Process("SHMSADCGates.C")
// root> T->Process("SHMSADCGates.C","some options")
// root> T->Process("SHMSADCGates.C+")
//


#include "SHMSADCGates.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TSpectrum.h>
#include <TPolyMarker.h>
#include <TMath.h>
#include <TSystem.h>

void SHMSADCGates::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();
}

void SHMSADCGates::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

   h1PHGCERPulseTime              = new TH1F*[4];
   h1PHGCERPulseTimeStarttimeDiff = new TH1F*[4];
   for (Int_t ipmt=0; ipmt<4; ipmt++) {
     h1PHGCERPulseTime[ipmt] = new TH1F(Form("PHGCERPulseTime%d",ipmt+1),Form("Pulse Time Information for SHMS HGC PMT%d;Time (ns);Counts",ipmt+1),700,-600,100);
     h1PHGCERPulseTimeStarttimeDiff[ipmt] = new TH1F(Form("PHGCERPulseTimeStarttimeDiff%d",ipmt+1),Form("Pulse Time Information for SHMS HGC  PMT%d Start Time Subtracted;Time (ns);Counts",ipmt+1),1000,-100,100);

     GetOutputList()->Add(h1PHGCERPulseTime[ipmt]);
     GetOutputList()->Add(h1PHGCERPulseTimeStarttimeDiff[ipmt]);
   }

   /*h1PNGCERPulseTime              = new TH1F*[4];
   h1PNGCERPulseTimeStarttimeDiff = new TH1F*[4];
   for (Int_t ipmt=0; ipmt<4; ipmt++) {
     h1PNGCERPulseTime[ipmt] = new TH1F(Form("PNGCERPulseTime%d",ipmt+1),Form("Pulse Time Information for SHMS NGC PMT%d;Time (ns);Counts",ipmt+1),700,-600,100);
     h1PNGCERPulseTimeStarttimeDiff[ipmt] = new TH1F(Form("PNGCERPulseTimeStarttimeDiff%d",ipmt+1),Form("Pulse Time Information for SHMS NGC  PMT%d Start Time Subtracted;Time (ns);Counts",ipmt+1),1000,-100,100);

     GetOutputList()->Add(h1PNGCERPulseTime[ipmt]);
     GetOutputList()->Add(h1PNGCERPulseTimeStarttimeDiff[ipmt]);
     }*/

   h1PAERONegPulseTime              = new TH1F*[7];
   h1PAERONegPulseTimeStarttimeDiff = new TH1F*[7];
   h1PAEROPosPulseTime              = new TH1F*[7];
   h1PAEROPosPulseTimeStarttimeDiff = new TH1F*[7];
   for (Int_t ipmt=0; ipmt<7; ipmt++) {
     h1PAERONegPulseTime[ipmt] = new TH1F(Form("PAERONegPulseTime%d",ipmt+1),Form("Pulse Time Information for SHMS AERO Neg PMT%d;Time (ns);Counts",ipmt+1),700,-600,100);
     h1PAERONegPulseTimeStarttimeDiff[ipmt] = new TH1F(Form("PAERONegPulseTimeStarttimeDiff%d",ipmt+1),Form("Pulse Time Information for SHMS AERO Neg PMT%d Start Time Subtracted;Time (ns);Counts",ipmt+1),1000,100,300);
     h1PAEROPosPulseTime[ipmt] = new TH1F(Form("PAEROPosPulseTime%d",ipmt+1),Form("Pulse Time Information for SHMS AERO Pos PMT%d;Time (ns);Counts",ipmt+1),700,-600,100);
     h1PAEROPosPulseTimeStarttimeDiff[ipmt] = new TH1F(Form("PAEROPosPulseTimeStarttimeDiff%d",ipmt+1),Form("Pulse Time Information for SHMS AERO Pos PMT%d Start Time Subtracted;Time (ns);Counts",ipmt+1),1000,-100,100);

     GetOutputList()->Add(h1PAERONegPulseTime[ipmt]);
     GetOutputList()->Add(h1PAERONegPulseTimeStarttimeDiff[ipmt]);
     GetOutputList()->Add(h1PAEROPosPulseTime[ipmt]);
     GetOutputList()->Add(h1PAEROPosPulseTimeStarttimeDiff[ipmt]);
   }

   h1PPRECALNegPulseTime              = new TH1F*[14];
   h1PPRECALNegPulseTimeStarttimeDiff = new TH1F*[14];
   h1PPRECALPosPulseTime              = new TH1F*[14];
   h1PPRECALPosPulseTimeStarttimeDiff = new TH1F*[14];
   for (Int_t ipmt=0; ipmt<14; ipmt++) {
     h1PPRECALNegPulseTime[ipmt] = new TH1F(Form("PPRECALNegPulseTime%d",ipmt+1),Form("Pulse Time Information for SHMS PRECAL Neg PMT%d;Time (ns);Counts",ipmt+1),700,-600,100);
     h1PPRECALNegPulseTimeStarttimeDiff[ipmt] = new TH1F(Form("PPRECALNegPulseTimeStarttimeDiff%d",ipmt+1),Form("Pulse Time Information for SHMS PRECAL Neg PMT%d Start Time Subtracted;Time (ns);Counts",ipmt+1),2000,-100,100);
     h1PPRECALPosPulseTime[ipmt] = new TH1F(Form("PPRECALPosPulseTime%d",ipmt+1),Form("Pulse Time Information for SHMS PRECAL Pos PMT%d;Time (ns);Counts",ipmt+1),700,-600,100);
     h1PPRECALPosPulseTimeStarttimeDiff[ipmt] = new TH1F(Form("PPRECALPosPulseTimeStarttimeDiff%d",ipmt+1),Form("Pulse Time Information for SHMS PRECAL Pos PMT%d Start Time Subtracted;Time (ns);Counts",ipmt+1),2000,-100,100);

     GetOutputList()->Add(h1PPRECALNegPulseTime[ipmt]);
     GetOutputList()->Add(h1PPRECALNegPulseTimeStarttimeDiff[ipmt]);
     GetOutputList()->Add(h1PPRECALPosPulseTime[ipmt]);
     GetOutputList()->Add(h1PPRECALPosPulseTimeStarttimeDiff[ipmt]);
   }
   
   h1PCALPulseTimeStarttimeDiff = new TH1F*[224];
   for (Int_t ipmt=0; ipmt<224; ipmt++) {
     h1PCALPulseTimeStarttimeDiff[ipmt] = new TH1F(Form("PCALPulseTimeStarttimeDiff%d",ipmt+1),Form("Pulse Time Information for SHMS CAL Neg PMT%d Start Time Subtracted;Time (ns);Counts",ipmt+1),2000,-100,100);

     GetOutputList()->Add(h1PCALPulseTimeStarttimeDiff[ipmt]);
   }

   h1PDCRawTdc = new TH1F*[12];
   for (Int_t ipmt=0; ipmt<12; ipmt++) {
     h1PDCRawTdc[ipmt] = new TH1F(Form("PDCRawTdc%d",ipmt+1),"Pulse Time Information for SHMS DC Start Time Subtracted;Time (ns);Counts",250,-15000,-10000);

     GetOutputList()->Add(h1PDCRawTdc[ipmt]);
   }

   h1PHODO1xNegPulseTimeStarttimeDiff = new TH1F*[18];
   h1PHODO1xPosPulseTimeStarttimeDiff = new TH1F*[18];
   h1PHODO1yNegPulseTimeStarttimeDiff = new TH1F*[18];
   h1PHODO1yPosPulseTimeStarttimeDiff = new TH1F*[18];
   h1PHODO2xNegPulseTimeStarttimeDiff = new TH1F*[18];
   h1PHODO2xPosPulseTimeStarttimeDiff = new TH1F*[18];
   h1PHODO2yNegPulseTimeStarttimeDiff = new TH1F*[18];
   h1PHODO2yPosPulseTimeStarttimeDiff = new TH1F*[18];
   for (Int_t ipmt=0; ipmt<18; ipmt++) {
     h1PHODO1xNegPulseTimeStarttimeDiff[ipmt] = new TH1F(Form("PHODO1xNegPulseTimeStarttimeDiff%d",ipmt+1),Form("Pulse Time Information for SHMS HODO 1x Neg PMT%d Start Time Subtracted;Time (ns);Counts",ipmt+1),1000,-50,50);
     h1PHODO1xPosPulseTimeStarttimeDiff[ipmt] = new TH1F(Form("PHODO1xPosPulseTimeStarttimeDiff%d",ipmt+1),Form("Pulse Time Information for SHMS HODO 1x Pos PMT%d Start Time Subtracted;Time (ns);Counts",ipmt+1),1000,-50,50);
     h1PHODO1yNegPulseTimeStarttimeDiff[ipmt] = new TH1F(Form("PHODO1yNegPulseTimeStarttimeDiff%d",ipmt+1),Form("Pulse Time Information for SHMS HODO 1y Neg PMT%d Start Time Subtracted;Time (ns);Counts",ipmt+1),1000,-50,50);
     h1PHODO1yPosPulseTimeStarttimeDiff[ipmt] = new TH1F(Form("PHODO1yPosPulseTimeStarttimeDiff%d",ipmt+1),Form("Pulse Time Information for SHMS HODO 1y Pos PMT%d Start Time Subtracted;Time (ns);Counts",ipmt+1),1000,-50,50);
     h1PHODO2xNegPulseTimeStarttimeDiff[ipmt] = new TH1F(Form("PHODO2xNegPulseTimeStarttimeDiff%d",ipmt+1),Form("Pulse Time Information for SHMS HODO 2x Neg PMT%d Start Time Subtracted;Time (ns);Counts",ipmt+1),1000,-50,50);
     h1PHODO2xPosPulseTimeStarttimeDiff[ipmt] = new TH1F(Form("PHODO2xPosPulseTimeStarttimeDiff%d",ipmt+1),Form("Pulse Time Information for SHMS HODO 2x Pos PMT%d Start Time Subtracted;Time (ns);Counts",ipmt+1),1000,-50,50);
     h1PHODO2yNegPulseTimeStarttimeDiff[ipmt] = new TH1F(Form("PHODO2yNegPulseTimeStarttimeDiff%d",ipmt+1),Form("Pulse Time Information for SHMS HODO 2y Neg PMT%d Start Time Subtracted;Time (ns);Counts",ipmt+1),1000,-50,50);
     h1PHODO2yPosPulseTimeStarttimeDiff[ipmt] = new TH1F(Form("PHODO2yPosPulseTimeStarttimeDiff%d",ipmt+1),Form("Pulse Time Information for SHMS HODO 2y Pos PMT%d Start Time Subtracted;Time (ns);Counts",ipmt+1),1000,-50,50);

     GetOutputList()->Add(h1PHODO1xNegPulseTimeStarttimeDiff[ipmt]);
     GetOutputList()->Add(h1PHODO1xPosPulseTimeStarttimeDiff[ipmt]);
     GetOutputList()->Add(h1PHODO1yNegPulseTimeStarttimeDiff[ipmt]);
     GetOutputList()->Add(h1PHODO1yPosPulseTimeStarttimeDiff[ipmt]);
     GetOutputList()->Add(h1PHODO2xNegPulseTimeStarttimeDiff[ipmt]);
     GetOutputList()->Add(h1PHODO2xPosPulseTimeStarttimeDiff[ipmt]);
     GetOutputList()->Add(h1PHODO2yNegPulseTimeStarttimeDiff[ipmt]);
     GetOutputList()->Add(h1PHODO2yPosPulseTimeStarttimeDiff[ipmt]);
   }
}

Bool_t SHMSADCGates::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // When processing keyed objects with PROOF, the object is already loaded
   // and is available via the fObject pointer.
   //
   // This function should contain the \"body\" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.

   fReader.SetEntry(entry);
   
   for (Int_t i = 0; i < *Ndata_P_hgcer_adcPulseTime; i++) {
     if (P_hgcer_adcErrorFlag[i] == 1) continue;
     Int_t current_pmt = P_hgcer_adcCounter[i] - 1;
     h1PHGCERPulseTime[current_pmt]->Fill(-P_hgcer_adcPulseTime[i]);
     h1PHGCERPulseTimeStarttimeDiff[current_pmt]->Fill(-P_hgcer_adcPulseTime[i] + *P_hod_starttime);   
   }

   /*for (Int_t i = 0; i <= *Ndata_P_ngcer_adcPulseTime; i++) {
     if (P_ngcer_adcErrorFlag[i] == 1) continue;
     if (P_ngcer_adcCounter[i] < 1 || P_ngcer_adcCounter[i] > 4) continue;
     Int_t current_pmt = P_ngcer_adcCounter[i] - 1;
     h1PNGCERPulseTime[current_pmt]->Fill(-P_ngcer_adcPulseTime[i]);
     h1PNGCERPulseTimeStarttimeDiff[current_pmt]->Fill(-P_ngcer_adcPulseTime[i] + *P_hod_starttime); 
     }*/
   
   for (Int_t i = 0; i < *Ndata_P_aero_negAdcPulseTime; i++) {
     if (P_aero_negAdcErrorFlag[i] == 1) continue;
     Int_t current_pmt = P_aero_negAdcCounter[i] - 1;
     h1PAERONegPulseTime[current_pmt]->Fill(-P_aero_negAdcPulseTime[i]);
     h1PAERONegPulseTimeStarttimeDiff[current_pmt]->Fill(-P_aero_negAdcPulseTime[i] + *P_hod_starttime); 
   }
   
   for (Int_t i = 0; i < *Ndata_P_aero_posAdcPulseTime; i++) {
     if (P_aero_posAdcErrorFlag[i] == 1) continue;
     Int_t current_pmt = P_aero_posAdcCounter[i] - 1;
     h1PAEROPosPulseTime[current_pmt]->Fill(-P_aero_posAdcPulseTime[i]);
     h1PAEROPosPulseTimeStarttimeDiff[current_pmt]->Fill(-P_aero_posAdcPulseTime[i] + *P_hod_starttime); 
   }
   
   for (Int_t i = 0; i < *Ndata_P_precal_negAdcPulseTime; i++) {
     if (P_precal_negAdcErrorFlag[i] == 1) continue;
     Int_t current_pmt = P_precal_negAdcCounter[i] - 1;
     h1PPRECALNegPulseTime[current_pmt]->Fill(-P_precal_negAdcPulseTime[i]);
     h1PPRECALNegPulseTimeStarttimeDiff[current_pmt]->Fill(-P_precal_negAdcPulseTime[i] + *P_hod_starttime); 
   }
   
   for (Int_t i = 0; i < *Ndata_P_precal_posAdcPulseTime; i++) {
     if (P_precal_posAdcErrorFlag[i] == 1) continue;
     Int_t current_pmt = P_precal_posAdcCounter[i] - 1;
     h1PPRECALPosPulseTime[current_pmt]->Fill(-P_precal_posAdcPulseTime[i]);
     h1PPRECALPosPulseTimeStarttimeDiff[current_pmt]->Fill(-P_precal_posAdcPulseTime[i] + *P_hod_starttime); 
   }
   
   for (Int_t i = 0; i < *Ndata_P_cal_adcPulseTime; i++) {
     if (P_cal_adcErrorFlag[i] == 1) continue;
     Int_t current_pmt = P_cal_adcCounter[i] - 1;
     h1PCALPulseTimeStarttimeDiff[current_pmt]->Fill(-P_cal_adcPulseTime[i] + *P_hod_starttime); 
   }
   
   for (Int_t i = 0; i < *Ndata_P_dc_1u1_rawtdc; i++) {
     h1PDCRawTdc[0]->Fill(P_dc_1u1_rawtdc[i]); 
     h1PDCRawTdc[1]->Fill(P_dc_1u2_rawtdc[i]);
     h1PDCRawTdc[2]->Fill(P_dc_1v1_rawtdc[i]); 
     h1PDCRawTdc[3]->Fill(P_dc_1v2_rawtdc[i]);
     h1PDCRawTdc[4]->Fill(P_dc_1x1_rawtdc[i]); 
     h1PDCRawTdc[5]->Fill(P_dc_1x2_rawtdc[i]);
     h1PDCRawTdc[6]->Fill(P_dc_2u1_rawtdc[i]); 
     h1PDCRawTdc[7]->Fill(P_dc_2u2_rawtdc[i]);
     h1PDCRawTdc[8]->Fill(P_dc_2v1_rawtdc[i]); 
     h1PDCRawTdc[9]->Fill(P_dc_2v2_rawtdc[i]);
     h1PDCRawTdc[10]->Fill(P_dc_2x1_rawtdc[i]); 
     h1PDCRawTdc[11]->Fill(P_dc_2x2_rawtdc[i]);
   }
   
   for (Int_t i = 0; i < *Ndata_P_hod_1x_negAdcPulseTime; i++) {
     if (P_hod_1x_negAdcErrorFlag[i] == 1) continue;
     Int_t current_pmt = P_hod_1x_negAdcCounter[i] - 1;
     //h1PHODO1xNegPulseTimeStarttimeDiff[current_pmt]->Fill(P_hod_1x_negTdcTimeCorr[current_pmt] - P_hod_1x_negAdcPulseTime[i]);
     for (Int_t j = 0; j < *Ndata_P_hod_1x_negTdcTime; j++) {
       cout << (P_hod_1x_negTdcTime[j])*0.1 + 200.0 - P_hod_1x_negAdcPulseTime[i] << endl;
       h1PHODO1xNegPulseTimeStarttimeDiff[current_pmt]->Fill((P_hod_1x_negTdcTime[j])*0.1 + 200.0 - P_hod_1x_negAdcPulseTime[i]); 
     }
   }
   
   for (Int_t i = 0; i < *Ndata_P_hod_1x_posAdcPulseTime; i++) {
     if (P_hod_1x_posAdcErrorFlag[i] == 1) continue;
     Int_t current_pmt = P_hod_1x_posAdcCounter[i] - 1;
     //h1PHODO1xPosPulseTimeStarttimeDiff[current_pmt]->Fill(P_hod_1x_posTdcTimeCorr[current_pmt]  - P_hod_1x_posAdcPulseTime[i]);
     for (Int_t j = 0; j < *Ndata_P_hod_1x_posTdcTime; j++) {
       h1PHODO1xPosPulseTimeStarttimeDiff[current_pmt]->Fill(P_hod_1x_posTdcTime[j])*0.1 + 200.0 - P_hod_1x_posAdcPulseTime[i]); 
     }
   }

   for (Int_t i = 0; i < *Ndata_P_hod_1y_negAdcPulseTime; i++) {
     if (P_hod_1y_negAdcErrorFlag[i] == 1) continue;
     Int_t current_pmt = P_hod_1y_negAdcCounter[i] - 1;
     //h1PHODO1yNegPulseTimeStarttimeDiff[current_pmt]->Fill(P_hod_1y_negTdcTimeCorr[current_pmt] - P_hod_1y_negAdcPulseTime[i]); 
     for (Int_t j = 0; j < *Ndata_P_hod_1y_negTdcTime; j++) {
       h1PHODO1yNegPulseTimeStarttimeDiff[current_pmt]->Fill(P_hod_1y_negTdcTime[j])*0.1 + 200.0 - P_hod_1y_negAdcPulseTime[i]); 
     }
   }

   for (Int_t i = 0; i < *Ndata_P_hod_1y_posAdcPulseTime; i++) {
     if (P_hod_1y_posAdcErrorFlag[i] == 1) continue;
     Int_t current_pmt = P_hod_1y_posAdcCounter[i] - 1;
     //h1PHODO1yPosPulseTimeStarttimeDiff[current_pmt]->Fill(P_hod_1y_posTdcTimeCorr[current_pmt] - P_hod_1y_posAdcPulseTime[i]); 
     for (Int_t j = 0; j < *Ndata_P_hod_1y_posTdcTime; j++) {
       h1PHODO1yPosPulseTimeStarttimeDiff[current_pmt]->Fill(P_hod_1y_posTdcTime[j])*0.1 + 200.0 - P_hod_1y_posAdcPulseTime[i]); 
     }
   }

   for (Int_t i = 0; i < *Ndata_P_hod_2x_negAdcPulseTime; i++) {
     if (P_hod_2x_negAdcErrorFlag[i] == 1) continue;
     Int_t current_pmt = P_hod_2x_negAdcCounter[i] - 1;
     //h1PHODO2xNegPulseTimeStarttimeDiff[current_pmt]->Fill(P_hod_2x_negTdcTimeCorr[current_pmt] - P_hod_2x_negAdcPulseTime[i]); 
     for (Int_t j = 0; j < *Ndata_P_hod_2x_negTdcTime; j++) {
       h1PHODO2xNegPulseTimeStarttimeDiff[current_pmt]->Fill(P_hod_2x_negTdcTime[j])*0.1 + 200.0 - P_hod_2x_negAdcPulseTime[i]); 
     }
   }

   for (Int_t i = 0; i < *Ndata_P_hod_2x_posAdcPulseTime; i++) {
     if (P_hod_2x_posAdcErrorFlag[i] == 1) continue;
     Int_t current_pmt = P_hod_2x_posAdcCounter[i] - 1;
     //h1PHODO2xPosPulseTimeStarttimeDiff[current_pmt]->Fill(P_hod_2x_posTdcTimeCorr[current_pmt] - P_hod_2x_posAdcPulseTime[i]); 
     for (Int_t j = 0; j < *Ndata_P_hod_2x_posTdcTime; j++) {
       h1PHODO2xPosPulseTimeStarttimeDiff[current_pmt]->Fill(P_hod_2x_posTdcTime[j])*0.1 + 200.0 - P_hod_2x_posAdcPulseTime[i]); 
     }
   }

   for (Int_t i = 0; i < *Ndata_P_hod_2y_negAdcPulseTime; i++) {
     if (P_hod_2y_negAdcErrorFlag[i] == 1) continue;
     Int_t current_pmt = P_hod_2y_negAdcCounter[i] - 1;
     //h1PHODO2yNegPulseTimeStarttimeDiff[current_pmt]->Fill(P_hod_2y_negTdcTimeCorr[current_pmt] - P_hod_2y_negAdcPulseTime[i]); 
     for (Int_t j = 0; j < *Ndata_P_hod_2y_negTdcTime; j++) {
       h1PHODO2yNegPulseTimeStarttimeDiff[current_pmt]->Fill(P_hod_2y_negTdcTime[j])*0.1 + 200.0 - P_hod_2y_negAdcPulseTime[i]); 
     }
   }

   for (Int_t i = 0; i < *Ndata_P_hod_2y_posAdcPulseTime; i++) {
     if (P_hod_2y_posAdcErrorFlag[i] == 1) continue;
     Int_t current_pmt = P_hod_2y_posAdcCounter[i] - 1;
     //h1PHODO2yPosPulseTimeStarttimeDiff[current_pmt]->Fill(P_hod_2y_posTdcTimeCorr[current_pmt] - P_hod_2y_posAdcPulseTime[i]); 
     for (Int_t j = 0; j < *Ndata_P_hod_2y_posTdcTime; j++) {
       h1PHODO2yPosPulseTimeStarttimeDiff[current_pmt]->Fill(P_hod_2y_posTdcTime[j])*0.1 + 200.0 - P_hod_2y_posAdcPulseTime[i]); 
     }
   }
   
   return kTRUE;
}

void SHMSADCGates::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void SHMSADCGates::Terminate()
{
  // The Terminate() function is the last function to be called during
  // a query. It always runs on the client, it can be used to present
  // the results graphically or save the results to file.

  Info("Terminate", "Branches Sorted, Now Calculating Windows");
  //return;
  TH1F* PHGCPULSETIME[4];
  TH1F* PHGCPULSETIMEDIFF[4];
  for (Int_t ipmt = 0; ipmt < 4; ipmt++) {
    PHGCPULSETIME[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("PHGCERPulseTime%d",ipmt+1)));
    PHGCPULSETIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("PHGCERPulseTimeStarttimeDiff%d",ipmt+1)));
  }

  /*TH1F* PNGCPULSETIME[4];
  TH1F* PNGCPULSETIMEDIFF[4];
  for (Int_t ipmt = 0; ipmt < 4; ipmt++) {
    PNGCPULSETIME[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("PNGCERPulseTime%d",ipmt+1)));
    PNGCPULSETIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("PNGCERPulseTimeStarttimeDiff%d",ipmt+1)));
    }*/
  
  TH1F* PAERONEGPULSETIME[7];
  TH1F* PAERONEGPULSETIMEDIFF[7];
  TH1F* PAEROPOSPULSETIME[7];
  TH1F* PAEROPOSPULSETIMEDIFF[7];
  for (Int_t ipmt = 0; ipmt < 7; ipmt++) {
    PAERONEGPULSETIME[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("PAERONegPulseTime%d",ipmt+1)));
    PAERONEGPULSETIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("PAERONegPulseTimeStarttimeDiff%d",ipmt+1)));
    PAEROPOSPULSETIME[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("PAEROPosPulseTime%d",ipmt+1)));
    PAEROPOSPULSETIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("PAEROPosPulseTimeStarttimeDiff%d",ipmt+1)));
    }

  TH1F* PPRECALNEGPULSETIME[14];
  TH1F* PPRECALNEGPULSETIMEDIFF[14];
  TH1F* PPRECALPOSPULSETIME[14];
  TH1F* PPRECALPOSPULSETIMEDIFF[14];
  for (Int_t ipmt = 0; ipmt < 14; ipmt++) {
    PPRECALNEGPULSETIME[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("PPRECALNegPulseTime%d",ipmt+1)));
    PPRECALNEGPULSETIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("PPRECALNegPulseTimeStarttimeDiff%d",ipmt+1)));
    PPRECALPOSPULSETIME[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("PPRECALPosPulseTime%d",ipmt+1)));
    PPRECALPOSPULSETIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("PPRECALPosPulseTimeStarttimeDiff%d",ipmt+1)));
    }
  
  TH1F* PCALPULSETIMEDIFF[224];
  for (Int_t ipmt = 0; ipmt < 224; ipmt++) {
    PCALPULSETIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("PCALPulseTimeStarttimeDiff%d",ipmt+1)));
    }

  TH1F* PDCRAWTDC[12];
  for (Int_t ipmt = 0; ipmt < 12; ipmt++) {
    PDCRAWTDC[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("PDCRawTdc%d",ipmt+1)));
    }

  TH1F* PHODO1xNEGPULSETIMEDIFF[18];
  TH1F* PHODO1xPOSPULSETIMEDIFF[18];
  TH1F* PHODO1yNEGPULSETIMEDIFF[18];
  TH1F* PHODO1yPOSPULSETIMEDIFF[18];
  TH1F* PHODO2xNEGPULSETIMEDIFF[18];
  TH1F* PHODO2xPOSPULSETIMEDIFF[18];
  TH1F* PHODO2yNEGPULSETIMEDIFF[18];
  TH1F* PHODO2yPOSPULSETIMEDIFF[18];
  for (Int_t ipmt = 0; ipmt < 18; ipmt++) {
    PHODO1xNEGPULSETIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("PHODO1xNegPulseTimeStarttimeDiff%d",ipmt+1)));
    PHODO1xPOSPULSETIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("PHODO1xPosPulseTimeStarttimeDiff%d",ipmt+1)));
    PHODO1yNEGPULSETIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("PHODO1yNegPulseTimeStarttimeDiff%d",ipmt+1)));
    PHODO1yPOSPULSETIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("PHODO1yPosPulseTimeStarttimeDiff%d",ipmt+1)));
    PHODO2xNEGPULSETIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("PHODO2xNegPulseTimeStarttimeDiff%d",ipmt+1)));
    PHODO2xPOSPULSETIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("PHODO2xPosPulseTimeStarttimeDiff%d",ipmt+1)));
    PHODO2yNEGPULSETIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("PHODO2yNegPulseTimeStarttimeDiff%d",ipmt+1)));
    PHODO2yPOSPULSETIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("PHODO2yPosPulseTimeStarttimeDiff%d",ipmt+1)));
    }
  

  //Begin peak Finding
  //gSystem->RedirectOutput("/dev/null","a");
  Double_t HGC_Window[4];
  for (Int_t ipmt = 0; ipmt < 4; ipmt++) {
    if (PHGCPULSETIMEDIFF[ipmt]->GetEntries() != 0) {
      TSpectrum *s = new TSpectrum(1);
      s->Search(PHGCPULSETIMEDIFF[ipmt], 1.0, "nobackground&&nodraw", 0.001);
      TList *functions = PHGCPULSETIMEDIFF[ipmt]->GetListOfFunctions();
      TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
      HGC_Window[ipmt] = *pm->GetX();
    }
    else {
      HGC_Window[ipmt] = 1e+38;
    }
  }

  /*Double_t NGC_Window[4];
  for (Int_t ipmt = 0; ipmt < 4; ipmt++) {
    TSpectrum *s = new TSpectrum(1);
    s->Search(PNGCPULSETIMEDIFF[ipmt], 1.0, "nobackground&&nodraw", 0.001);
    TList *functions = PNGCPULSETIMEDIFF[ipmt]->GetListOfFunctions();
    TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
    NGC_Window[ipmt] = *pm->GetX();
    }*/
  
  Double_t AERONEG_Window[7];
  for (Int_t ipmt = 0; ipmt < 7; ipmt++) {
    if (PAERONEGPULSETIMEDIFF[ipmt]->GetEntries() != 0) {
      TSpectrum *s = new TSpectrum(1);
      s->Search(PAERONEGPULSETIMEDIFF[ipmt], 1.0, "nobackground&&nodraw", 0.001);
      TList *functions = PAERONEGPULSETIMEDIFF[ipmt]->GetListOfFunctions();
      TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
      AERONEG_Window[ipmt] = *pm->GetX();
    }
    else {
      AERONEG_Window[ipmt] = 1e+38;
    }
  }

  Double_t AEROPOS_Window[7];
  for (Int_t ipmt = 0; ipmt < 7; ipmt++) {
    if (PAEROPOSPULSETIMEDIFF[ipmt]->GetEntries() != 0) {
      TSpectrum *s = new TSpectrum(1);
      s->Search(PAEROPOSPULSETIMEDIFF[ipmt], 1.0, "nobackground&&nodraw", 0.001);
      TList *functions = PAEROPOSPULSETIMEDIFF[ipmt]->GetListOfFunctions();
      TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
      AEROPOS_Window[ipmt] = *pm->GetX();
    }
    else {
      AEROPOS_Window[ipmt] = 1e+38;
    }
  }

  Double_t PRECALNEG_Window[14];
  for (Int_t ipmt = 0; ipmt < 14; ipmt++) {
    if (PPRECALNEGPULSETIMEDIFF[ipmt]->GetEntries() !=0) {
      TSpectrum *s = new TSpectrum(1);
      s->Search(PPRECALNEGPULSETIMEDIFF[ipmt], 1.0, "nobackground&&nodraw", 0.001);
      TList *functions = PPRECALNEGPULSETIMEDIFF[ipmt]->GetListOfFunctions();
      TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
      PRECALNEG_Window[ipmt] = *pm->GetX();
    }
    else {
      PRECALNEG_Window[ipmt] = 1e+38;
    }
  }

  Double_t PRECALPOS_Window[14];
  for (Int_t ipmt = 0; ipmt < 14; ipmt++) {
    if (PPRECALPOSPULSETIMEDIFF[ipmt]->GetEntries() !=0) {
      TSpectrum *s = new TSpectrum(1);
      s->Search(PPRECALPOSPULSETIMEDIFF[ipmt], 1.0, "nobackground&&nodraw", 0.001);
      TList *functions = PPRECALPOSPULSETIMEDIFF[ipmt]->GetListOfFunctions();
      TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
      PRECALPOS_Window[ipmt] = *pm->GetX();
    }
    else {
      PRECALPOS_Window[ipmt] = 1e+38;
    }
  }

  Double_t CAL_Window[224];
  for (Int_t ipmt = 0; ipmt < 224; ipmt++) {
    if (PCALPULSETIMEDIFF[ipmt]->GetEntries() < 50) {
      TSpectrum *s = new TSpectrum(1);
      s->Search(PCALPULSETIMEDIFF[ipmt], 1.0, "nobackground&&nodraw", 0.001);
      TList *functions = PCALPULSETIMEDIFF[ipmt]->GetListOfFunctions();
      TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
      if (pm) {
	CAL_Window[ipmt] = *pm->GetX();
      }
      else CAL_Window[ipmt] = 1e+38;
    }
    else {
      CAL_Window[ipmt] = 1e+38;
    }
  }
  
  Double_t DC_Window[12];
  for (Int_t ipmt = 0; ipmt < 12; ipmt++) {
    if (PDCRAWTDC[ipmt]->GetEntries() != 0) {
      TSpectrum *s = new TSpectrum(1);
      s->Search(PDCRAWTDC[ipmt], 1.0, "nobackground&&nodraw", 0.001);
      TList *functions = PDCRAWTDC[ipmt]->GetListOfFunctions();
      TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
      DC_Window[ipmt] = *pm->GetX();
    }
    else {
      DC_Window[ipmt] = 1e+38;
    }
  }
  cout << "I AM HERE" << endl;
  Double_t HODO1xNeg_Window[18];
  for (Int_t ipmt = 0; ipmt < 18; ipmt++) {
    if (ipmt < 13 || PHODO1xNEGPULSETIMEDIFF[ipmt]->GetEntries() != 0) {
      cout << ipmt << "   ";
      TSpectrum *s = new TSpectrum(1);
      s->Search(PHODO1xNEGPULSETIMEDIFF[ipmt], 1.0, "nobackground&&nodraw", 0.001);
      TList *functions = PHODO1xNEGPULSETIMEDIFF[ipmt]->GetListOfFunctions();
      TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
      HODO1xNeg_Window[ipmt] = *pm->GetX();
    } else {
      HODO1xNeg_Window[ipmt] = 1e+38;
    }
  }
  cout << "I AM HERE TOO" << endl;
  Double_t HODO1xPos_Window[18];
  for (Int_t ipmt = 0; ipmt < 18; ipmt++) {
    if (ipmt < 13 || PHODO1xPOSPULSETIMEDIFF[ipmt]->GetEntries() != 0) {
      TSpectrum *s = new TSpectrum(1);
      s->Search(PHODO1xPOSPULSETIMEDIFF[ipmt], 1.0, "nobackground&&nodraw", 0.001);
      TList *functions = PHODO1xPOSPULSETIMEDIFF[ipmt]->GetListOfFunctions();
      TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
      HODO1xPos_Window[ipmt] = *pm->GetX();
    } else {
      HODO1xPos_Window[ipmt] = 1e+38;
    }
  }
  
  Double_t HODO1yNeg_Window[18];
  for (Int_t ipmt = 0; ipmt < 18; ipmt++) {
    if (ipmt < 13 || PHODO1yNEGPULSETIMEDIFF[ipmt]->GetEntries() != 0) {
      TSpectrum *s = new TSpectrum(1);
      s->Search(PHODO1yNEGPULSETIMEDIFF[ipmt], 1.0, "nobackground&&nodraw", 0.001);
      TList *functions = PHODO1yNEGPULSETIMEDIFF[ipmt]->GetListOfFunctions();
      TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
      HODO1yNeg_Window[ipmt] = *pm->GetX();
    } else {
      HODO1yNeg_Window[ipmt] = 1e+38;
    }
  }
  
  Double_t HODO1yPos_Window[18];
  for (Int_t ipmt = 0; ipmt < 18; ipmt++) {
    if (ipmt < 13 || PHODO1yPOSPULSETIMEDIFF[ipmt]->GetEntries() != 0) {
      TSpectrum *s = new TSpectrum(1);
      s->Search(PHODO1yPOSPULSETIMEDIFF[ipmt], 1.0, "nobackground&&nodraw", 0.001);
      TList *functions = PHODO1yPOSPULSETIMEDIFF[ipmt]->GetListOfFunctions();
      TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
      HODO1yPos_Window[ipmt] = *pm->GetX();
    } else {
      HODO1yPos_Window[ipmt] = 1e+38;
    }
  }
  
  Double_t HODO2xNeg_Window[18];
  for (Int_t ipmt = 0; ipmt < 18; ipmt++) {
    if (ipmt < 14 || PHODO2xNEGPULSETIMEDIFF[ipmt]->GetEntries() != 0) {
      TSpectrum *s = new TSpectrum(1);
      s->Search(PHODO2xNEGPULSETIMEDIFF[ipmt], 1.0, "nobackground&&nodraw", 0.001);
      TList *functions = PHODO2xNEGPULSETIMEDIFF[ipmt]->GetListOfFunctions();
      TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
      HODO2xNeg_Window[ipmt] = *pm->GetX();
    }    
    else {
      HODO2xNeg_Window[ipmt] = 1e+38;
    }
  }
  
  Double_t HODO2xPos_Window[18];
  for (Int_t ipmt = 0; ipmt < 18; ipmt++) {
    if (ipmt < 14 || PHODO2xPOSPULSETIMEDIFF[ipmt]->GetEntries() != 0) {
      TSpectrum *s = new TSpectrum(1);
      s->Search(PHODO2xPOSPULSETIMEDIFF[ipmt], 1.0, "nobackground&&nodraw", 0.001);
      TList *functions = PHODO2xPOSPULSETIMEDIFF[ipmt]->GetListOfFunctions();
      TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
      HODO2xPos_Window[ipmt] = *pm->GetX();
    }
    else {
      HODO2xPos_Window[ipmt] = 1e+38;
    }
  }

  Double_t HODO2yNeg_Window[18];
  for (Int_t ipmt = 0; ipmt < 18; ipmt++) {
    if (PHODO2yNEGPULSETIMEDIFF[ipmt]->GetEntries() != 0) {
      TSpectrum *s = new TSpectrum(1);
      s->Search(PHODO2yNEGPULSETIMEDIFF[ipmt], 1.0, "nobackground&&nodraw", 0.001);
      TList *functions = PHODO2yNEGPULSETIMEDIFF[ipmt]->GetListOfFunctions();
      TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
      HODO2yNeg_Window[ipmt] = *pm->GetX();
    }
    else {
      HODO2yNeg_Window[ipmt] = 1e+38;
    }
  }

  Double_t HODO2yPos_Window[18];
  for (Int_t ipmt = 0; ipmt < 18; ipmt++) {
    if (PHODO2yPOSPULSETIMEDIFF[ipmt]->GetEntries() != 0) {
      TSpectrum *s = new TSpectrum(1);
      s->Search(PHODO2yPOSPULSETIMEDIFF[ipmt], 1.0, "nobackground&&nodraw", 0.001);
      TList *functions = PHODO2yPOSPULSETIMEDIFF[ipmt]->GetListOfFunctions();
      TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
      HODO2yPos_Window[ipmt] = *pm->GetX();
    }
    else {
      HODO2yPos_Window[ipmt] = 1e+38;
    }
  }
  //gSystem->RedirectOutput(0);

  

  //Begin Calculation of Window Values
  Int_t AeroPosMin = TMath::Mean(7,AEROPOS_Window) - 35;
  Int_t AeroPosMax = TMath::Mean(7,AEROPOS_Window) + 20;
  Int_t AeroNegMin = TMath::Mean(7,AERONEG_Window) - 35;
  Int_t AeroNegMax = TMath::Mean(7,AERONEG_Window) + 20;

  Int_t HGCMinPMT1 = HGC_Window[0] - 10; Int_t HGCMaxPMT1 = HGC_Window[0] + 10;
  Int_t HGCMinPMT2 = HGC_Window[1] - 10; Int_t HGCMaxPMT2 = HGC_Window[1] + 10;
  Int_t HGCMinPMT3 = HGC_Window[2] - 10; Int_t HGCMaxPMT3 = HGC_Window[2] + 10;
  Int_t HGCMinPMT4 = HGC_Window[3] - 10; Int_t HGCMaxPMT4 = HGC_Window[3] + 10;

  /*Int_t NGCMinPMT1 = NGC_Window[0] - 10; Int_t NGCMaxPMT1 = NGC_Window[0] + 10;
  Int_t NGCMinPMT2 = NGC_Window[1] - 10; Int_t NGCMaxPMT2 = NGC_Window[1] + 10;
  Int_t NGCMinPMT3 = NGC_Window[2] - 10; Int_t NGCMaxPMT3 = NGC_Window[2] + 10;
  Int_t NGCMinPMT4 = NGC_Window[3] - 10; Int_t NGCMaxPMT4 = NGC_Window[3] + 10;*/
  
  Int_t HODOPosMin[72]; Int_t HODOPosMax[72];
  Int_t HODONegMin[72]; Int_t HODONegMax[72];
  for (Int_t ipmt = 0; ipmt < 18; ipmt++) {  
    (HODO1xPos_Window[ipmt] == 1e+38) ? HODOPosMin[4*ipmt]    = -200 : HODOPosMin[4*ipmt]    = HODO1xPos_Window[ipmt] - 10;
    (HODO1yPos_Window[ipmt] == 1e+38) ? HODOPosMin[4*ipmt+1]  = -200 : HODOPosMin[4*ipmt+1]  = HODO1yPos_Window[ipmt] - 20;
    (HODO2xPos_Window[ipmt] == 1e+38) ? HODOPosMin[4*ipmt+2]  = -200 : HODOPosMin[4*ipmt+2]  = HODO2xPos_Window[ipmt] - 10;
    (HODO2yPos_Window[ipmt] == 1e+38) ? HODOPosMin[4*ipmt+3]  = -200 : HODOPosMin[4*ipmt+3]  = HODO2yPos_Window[ipmt] - 20;
    (HODO1xNeg_Window[ipmt] == 1e+38) ? HODONegMin[4*ipmt]    = -200 : HODONegMin[4*ipmt]    = HODO1xNeg_Window[ipmt] - 10;
    (HODO1yNeg_Window[ipmt] == 1e+38) ? HODONegMin[4*ipmt+1]  = -200 : HODONegMin[4*ipmt+1]  = HODO1yNeg_Window[ipmt] - 20;
    (HODO2xNeg_Window[ipmt] == 1e+38) ? HODONegMin[4*ipmt+2]  = -200 : HODONegMin[4*ipmt+2]  = HODO2xNeg_Window[ipmt] - 10;
    (HODO2yNeg_Window[ipmt] == 1e+38) ? HODONegMin[4*ipmt+3]  = -200 : HODONegMin[4*ipmt+3]  = HODO2yNeg_Window[ipmt] - 20;
    (HODO1xPos_Window[ipmt] == 1e+38) ? HODOPosMax[4*ipmt]    = 200 : HODOPosMax[4*ipmt]    = HODO1xPos_Window[ipmt] + 10;
    (HODO1yPos_Window[ipmt] == 1e+38) ? HODOPosMax[4*ipmt+1]  = 200 : HODOPosMax[4*ipmt+1]  = HODO1yPos_Window[ipmt] + 20;
    (HODO2xPos_Window[ipmt] == 1e+38) ? HODOPosMax[4*ipmt+2]  = 200 : HODOPosMax[4*ipmt+2]  = HODO2xPos_Window[ipmt] + 10;
    (HODO2yPos_Window[ipmt] == 1e+38) ? HODOPosMax[4*ipmt+3]  = 200 : HODOPosMax[4*ipmt+3]  = HODO2yPos_Window[ipmt] + 20;
    (HODO1xNeg_Window[ipmt] == 1e+38) ? HODONegMax[4*ipmt]    = 200 : HODONegMax[4*ipmt]    = HODO1xNeg_Window[ipmt] + 10;
    (HODO1yNeg_Window[ipmt] == 1e+38) ? HODONegMax[4*ipmt+1]  = 200 : HODONegMax[4*ipmt+1]  = HODO1yNeg_Window[ipmt] + 20;
    (HODO2xNeg_Window[ipmt] == 1e+38) ? HODONegMax[4*ipmt+2]  = 200 : HODONegMax[4*ipmt+2]  = HODO2xNeg_Window[ipmt] + 10;
    (HODO2yNeg_Window[ipmt] == 1e+38) ? HODONegMax[4*ipmt+3]  = 200 : HODONegMax[4*ipmt+3]  = HODO2yNeg_Window[ipmt] + 20;
  }

  Int_t PRECALPosMin[14]; Int_t PRECALPosMax[14];
  Int_t PRECALNegMin[14]; Int_t PRECALNegMax[14];
  for (Int_t ipmt = 0; ipmt < 14; ipmt++) {  
    (PRECALPOS_Window[ipmt] == 1e+38) ? PRECALPosMin[ipmt] = -200 : PRECALPosMin[ipmt] = PRECALPOS_Window[ipmt] - 10;
    (PRECALNEG_Window[ipmt] == 1e+38) ? PRECALNegMin[ipmt] = -200 : PRECALNegMin[ipmt] = PRECALNEG_Window[ipmt] - 10;
    (PRECALPOS_Window[ipmt] == 1e+38) ? PRECALPosMax[ipmt] = 200 : PRECALPosMax[ipmt] = PRECALPOS_Window[ipmt] + 10;
    (PRECALNEG_Window[ipmt] == 1e+38) ? PRECALNegMax[ipmt] = 200 : PRECALNegMax[ipmt] = PRECALNEG_Window[ipmt] + 10;
  }

  Int_t CALMin[224]; Int_t CALMax[224];
  for (Int_t ipmt = 0; ipmt < 224; ipmt++) {
    (CAL_Window[ipmt] == 1e+38) ? CALMin[ipmt] = -200 : CALMin[ipmt] = CAL_Window[ipmt] - 10;
    (CAL_Window[ipmt] == 1e+38) ? CALMax[ipmt] = 200 : CALMax[ipmt] = CAL_Window[ipmt] + 10;
  }

  Int_t DCMin[12]; Int_t DCMax[12];
  for (Int_t ipmt = 0; ipmt < 12; ipmt++) {
    (DC_Window[ipmt] == 1e+38) ? DCMin[ipmt] = -13000 : DCMin[ipmt] = DC_Window[ipmt] - 2000;
    (DC_Window[ipmt] == 1e+38) ? DCMax[ipmt] = -10000 : DCMax[ipmt] = DC_Window[ipmt] + 2000;
  }
  
  //Begin Plotting Results 
  /*
  TCanvas *HGC = new TCanvas("HGC","ADC Timing Window for SHMS HGC");
  HGC->Divide(2,2); 
  for (Int_t ipmt = 0; ipmt < 4; ipmt++) {
    HGC->cd(ipmt); PHGCPULSETIMEDIFF[ipmt]->Draw(); PHGCPULSETIMEDIFF[ipmt]->GetXaxis()->SetLabelSize(0.1); PHGCPULSETIMEDIFF[ipmt]->GetXaxis()->SetTitleOffset(-1.0); PHGCPULSETIMEDIFF[ipmt]->GetXaxis()->SetTitleSize(0.1);
  }

  TCanvas *AERO = new TCanvas("AERO","ADC Timing Window for SHMS AERO");
  AERO->Divide(2,7);
  for (Int_t ipmt = 0; ipmt < 7; ipmt++) {
    AERO->cd(2*ipmt+1); PAERONEGPULSETIMEDIFF[ipmt]->Draw(); PAERONEGPULSETIMEDIFF[ipmt]->GetXaxis()->SetLabelSize(0.12); PAERONEGPULSETIMEDIFF[ipmt]->GetXaxis()->SetTitleOffset(-1.0); PAERONEGPULSETIMEDIFF[ipmt]->GetXaxis()->SetTitleSize(0.1);
    AERO->cd(2*ipmt+2); PAEROPOSPULSETIMEDIFF[ipmt]->Draw(); PAEROPOSPULSETIMEDIFF[ipmt]->GetXaxis()->SetLabelSize(0.12); PAEROPOSPULSETIMEDIFF[ipmt]->GetXaxis()->SetTitleOffset(-1.0); PAEROPOSPULSETIMEDIFF[ipmt]->GetXaxis()->SetTitleSize(0.1);
  }

  TCanvas *PRECAL = new TCanvas("PRECAL","ADC Timing Window for SHMS PRECAL");
  PRECAL->Divide(2,14);
  for (Int_t ipmt = 0; ipmt < 14; ipmt++) {
    PRECAL->cd(2*ipmt+1); PPRECALNEGPULSETIMEDIFF[ipmt]->Draw(); PPRECALNEGPULSETIMEDIFF[ipmt]->GetXaxis()->SetLabelSize(0.12); PPRECALNEGPULSETIMEDIFF[ipmt]->GetXaxis()->SetTitleOffset(-1.0); PPRECALNEGPULSETIMEDIFF[ipmt]->GetXaxis()->SetTitleSize(0.1);
    PRECAL->cd(2*ipmt+2); PPRECALPOSPULSETIMEDIFF[ipmt]->Draw(); PPRECALPOSPULSETIMEDIFF[ipmt]->GetXaxis()->SetLabelSize(0.12); PPRECALPOSPULSETIMEDIFF[ipmt]->GetXaxis()->SetTitleOffset(-1.0); PPRECALPOSPULSETIMEDIFF[ipmt]->GetXaxis()->SetTitleSize(0.1);
  }

  TCanvas *CAL = new TCanvas("CAL","ADC Timing Window for SHMS CAL");
  CAL->Divide(14,16);
  for (Int_t ipmt = 0; ipmt < 224; ipmt++) {
    CAL->cd(ipmt+1); PCALPULSETIMEDIFF[ipmt]->Draw();
  }
  
  TCanvas *DC = new TCanvas("DC","ADC Timing Window for SHMS DC");
  DC->Divide(2,6);
  for (Int_t ipmt = 0; ipmt < 6; ipmt++) {
    DC->cd(2*ipmt+1); PDCRAWTDC[2*ipmt]->Draw();
    DC->cd(2*ipmt+2); PDCRAWTDC[2*ipmt+1]->Draw();
  }

  TCanvas *HODONEG = new TCanvas("HODONEG","ADC Timing Window for SHMS NEG HODO");
  HODONEG->Divide(4,18);
  for (Int_t ipmt = 0; ipmt < 18; ipmt++) {
    HODONEG->cd(4*ipmt+1); PHODO1xNEGPULSETIMEDIFF[ipmt]->Draw(); PHODO1xNEGPULSETIMEDIFF[ipmt]->GetXaxis()->SetLabelSize(0.12); PHODO1xNEGPULSETIMEDIFF[ipmt]->GetXaxis()->SetTitleOffset(-1.0); PHODO1xNEGPULSETIMEDIFF[ipmt]->GetXaxis()->SetTitleSize(0.1);
    HODONEG->cd(4*ipmt+2); PHODO1yNEGPULSETIMEDIFF[ipmt]->Draw(); PHODO1yNEGPULSETIMEDIFF[ipmt]->GetXaxis()->SetLabelSize(0.12); PHODO1yNEGPULSETIMEDIFF[ipmt]->GetXaxis()->SetTitleOffset(-1.0); PHODO1yNEGPULSETIMEDIFF[ipmt]->GetXaxis()->SetTitleSize(0.1);
    HODONEG->cd(4*ipmt+3); PHODO2xNEGPULSETIMEDIFF[ipmt]->Draw(); PHODO2xNEGPULSETIMEDIFF[ipmt]->GetXaxis()->SetLabelSize(0.12); PHODO2xNEGPULSETIMEDIFF[ipmt]->GetXaxis()->SetTitleOffset(-1.0); PHODO2xNEGPULSETIMEDIFF[ipmt]->GetXaxis()->SetTitleSize(0.1);
    HODONEG->cd(4*ipmt+4); PHODO2yNEGPULSETIMEDIFF[ipmt]->Draw();PHODO2yNEGPULSETIMEDIFF[ipmt]->GetXaxis()->SetLabelSize(0.12); PHODO2yNEGPULSETIMEDIFF[ipmt]->GetXaxis()->SetTitleOffset(-1.0); PHODO2yNEGPULSETIMEDIFF[ipmt]->GetXaxis()->SetTitleSize(0.1);
  }

  TCanvas *HODOPOS = new TCanvas("HODOPOS","ADC Timing Window for SHMS POS HODO");
  HODOPOS->Divide(4,18);
  for (Int_t ipmt = 0; ipmt < 18; ipmt++) {
    HODOPOS->cd(4*ipmt+1); PHODO1xPOSPULSETIMEDIFF[ipmt]->Draw(); PHODO1xPOSPULSETIMEDIFF[ipmt]->Draw(); PHODO1xPOSPULSETIMEDIFF[ipmt]->GetXaxis()->SetLabelSize(0.12); PHODO1xPOSPULSETIMEDIFF[ipmt]->GetXaxis()->SetTitleOffset(-1.0); PHODO1xPOSPULSETIMEDIFF[ipmt]->GetXaxis()->SetTitleSize(0.1);
    HODOPOS->cd(4*ipmt+2); PHODO1yPOSPULSETIMEDIFF[ipmt]->Draw(); PHODO1yPOSPULSETIMEDIFF[ipmt]->Draw(); PHODO1yPOSPULSETIMEDIFF[ipmt]->GetXaxis()->SetLabelSize(0.12); PHODO1yPOSPULSETIMEDIFF[ipmt]->GetXaxis()->SetTitleOffset(-1.0); PHODO1yPOSPULSETIMEDIFF[ipmt]->GetXaxis()->SetTitleSize(0.1);
    HODOPOS->cd(4*ipmt+3); PHODO2xPOSPULSETIMEDIFF[ipmt]->Draw(); PHODO2xPOSPULSETIMEDIFF[ipmt]->Draw(); PHODO2xPOSPULSETIMEDIFF[ipmt]->GetXaxis()->SetLabelSize(0.12); PHODO2xPOSPULSETIMEDIFF[ipmt]->GetXaxis()->SetTitleOffset(-1.0); PHODO2xPOSPULSETIMEDIFF[ipmt]->GetXaxis()->SetTitleSize(0.1);
    HODOPOS->cd(4*ipmt+4); PHODO2yPOSPULSETIMEDIFF[ipmt]->Draw(); PHODO2yPOSPULSETIMEDIFF[ipmt]->Draw();PHODO2yPOSPULSETIMEDIFF[ipmt]->GetXaxis()->SetLabelSize(0.12); PHODO2yPOSPULSETIMEDIFF[ipmt]->GetXaxis()->SetTitleOffset(-1.0); PHODO2yPOSPULSETIMEDIFF[ipmt]->GetXaxis()->SetTitleSize(0.1);
  }
  */
  //Output Adc Time Window Values into an ascii file
  TString option = GetOption();
  ofstream SHMSWindows;
  SHMSWindows.open("SHMSADCTimingWindows.dat", fstream::trunc);
  SHMSWindows << Form(";Values obtained from Run %s",option.Data()) << endl;
  SHMSWindows << Form("paero_adcPosTimeWindowMin = %d\npaero_adcPosTimeWindowMax = %d\npaero_adcNegTimeWindowMin = %d\npaero_adcNegTimeWindowMax = %d\n",AeroPosMin,AeroPosMax,AeroNegMin,AeroNegMax) <<  endl;
  SHMSWindows << Form(";Values obtained from Run %s",option.Data()) << endl;
  SHMSWindows << Form("phgcer_adcTimeWindowMin = %d, %d, %d, %d\nphgcer_adcTimeWindowMax = %d, %d, %d, %d\n",HGCMinPMT1,HGCMinPMT2,HGCMinPMT3,HGCMinPMT4,HGCMaxPMT1,HGCMaxPMT2,HGCMaxPMT3,HGCMaxPMT4) << endl;
  SHMSWindows << Form(";Values obtained from Run %s",option.Data()) << endl;
  //SHMSWindows << Form("pngcer_adcTimeWindowMin = %d, %d, %d, %d\npngcer_adcTimeWindowMax = %d, %d, %d, %d\n",NGCMinPMT1,NGCMinPMT2,NGCMinPMT3,NGCMinPMT4,NGCMaxPMT1,NGCMaxPMT2,NGCMaxPMT3,NGCMaxPMT4) << endl;
  SHMSWindows << Form(";Values obtained from Run %s\nphodo_PosAdcTimeWindowMin =",option.Data());
  for (Int_t ipmt = 0; ipmt < 18; ipmt++) {
    SHMSWindows << Form(" %d, %d, %d, %d\n",HODOPosMin[4*ipmt],HODOPosMin[4*ipmt+1],HODOPosMin[4*ipmt+2],HODOPosMin[4*ipmt+3]);
  }
  SHMSWindows << "\nphodo_PosAdcTimeWindowMax =";
  for (Int_t ipmt = 0; ipmt < 18; ipmt++) {
    SHMSWindows << Form(" %d, %d, %d, %d\n",HODOPosMax[4*ipmt],HODOPosMax[4*ipmt+1],HODOPosMax[4*ipmt+2],HODOPosMax[4*ipmt+3]);
  }
  SHMSWindows << "\nphodo_NegAdcTimeWindowMin =";
  for (Int_t ipmt = 0; ipmt < 18; ipmt++) {
    SHMSWindows << Form(" %d, %d, %d, %d\n",HODONegMin[4*ipmt],HODONegMin[4*ipmt+1],HODONegMin[4*ipmt+2],HODONegMin[4*ipmt+3]);
  }
  SHMSWindows << "\nphodo_NegAdcTimeWindowMax =";
  for (Int_t ipmt = 0; ipmt < 18; ipmt++) {
    SHMSWindows << Form(" %d, %d, %d, %d\n",HODONegMax[4*ipmt],HODONegMax[4*ipmt+1],HODONegMax[4*ipmt+2],HODONegMax[4*ipmt+3]);
  }
  SHMSWindows << Form("\n;Values obtained from Run %s",option.Data()) << endl;
  SHMSWindows << Form("pcal_pos_AdcTimeWindowMin = %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d",PRECALPosMin[0],PRECALPosMin[1],PRECALPosMin[2],PRECALPosMin[3],PRECALPosMin[4],PRECALPosMin[5],PRECALPosMin[6],PRECALPosMin[7],PRECALPosMin[8],PRECALPosMin[9],PRECALPosMin[10],PRECALPosMin[11],PRECALPosMin[12],PRECALPosMin[13]) << endl;
  SHMSWindows << Form("\npcal_neg_AdcTimeWindowMin = %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d",PRECALNegMin[0],PRECALNegMin[1],PRECALNegMin[2],PRECALNegMin[3],PRECALNegMin[4],PRECALNegMin[5],PRECALNegMin[6],PRECALNegMin[7],PRECALNegMin[8],PRECALNegMin[9],PRECALNegMin[10],PRECALNegMin[11],PRECALNegMin[12],PRECALNegMin[13]) << endl;
  SHMSWindows << Form("\npcal_pos_AdcTimeWindowMax = %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d",PRECALPosMax[0],PRECALPosMax[1],PRECALPosMax[2],PRECALPosMax[3],PRECALPosMax[4],PRECALPosMax[5],PRECALPosMax[6],PRECALPosMax[7],PRECALPosMax[8],PRECALPosMax[9],PRECALPosMax[10],PRECALPosMax[11],PRECALPosMax[12],PRECALPosMax[13]) << endl;
  SHMSWindows << Form("\npcal_neg_AdcTimeWindowMax = %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d",PRECALNegMax[0],PRECALNegMax[1],PRECALNegMax[2],PRECALNegMax[3],PRECALNegMax[4],PRECALNegMax[5],PRECALNegMax[6],PRECALNegMax[7],PRECALNegMax[8],PRECALNegMax[9],PRECALNegMax[10],PRECALNegMax[11],PRECALNegMax[12],PRECALNegMax[13]) << endl;
  SHMSWindows << Form("\n;Values obtained from Run %s",option.Data()) << endl;
  SHMSWindows << "pcal_arr_AdcTimeWindowMin = ";
  for (Int_t ipmt = 0; ipmt < 16; ipmt++) {
  SHMSWindows << Form("%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d",CALMin[14*ipmt],CALMin[14*ipmt],CALMin[14*ipmt],CALMin[14*ipmt],CALMin[14*ipmt],CALMin[14*ipmt],CALMin[14*ipmt],CALMin[14*ipmt],CALMin[14*ipmt],CALMin[14*ipmt],CALMin[14*ipmt],CALMin[14*ipmt],CALMin[14*ipmt],CALMin[14*ipmt]) << endl;
  }
  SHMSWindows << "\npcal_arr_AdcTimeWindowMax = ";
  for (Int_t ipmt = 0; ipmt < 16; ipmt++) {
  SHMSWindows << Form("%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d",CALMax[14*ipmt],CALMax[14*ipmt],CALMax[14*ipmt],CALMax[14*ipmt],CALMax[14*ipmt],CALMax[14*ipmt],CALMax[14*ipmt],CALMax[14*ipmt],CALMax[14*ipmt],CALMax[14*ipmt],CALMax[14*ipmt],CALMax[14*ipmt],CALMax[14*ipmt],CALMax[14*ipmt]) << endl;
  }

  SHMSWindows << Form("\n;Values obtained from Run %s\nptdc_win_min =  ",option.Data());
  for (Int_t iplane = 0; iplane < 2; iplane++) {
    SHMSWindows << Form("%d, %d, %d, %d, %d, %d\n",DCMin[6*iplane],DCMin[6*iplane+1],DCMin[6*iplane+2],DCMin[6*iplane+3],DCMin[6*iplane+4],DCMin[6*iplane+5]);
  }
  SHMSWindows << "ptdc_win_max =  ";
  for (Int_t iplane = 0; iplane < 2; iplane++) {
    SHMSWindows << Form("%d, %d, %d, %d, %d, %d\n",DCMax[6*iplane],DCMax[6*iplane+1],DCMax[6*iplane+2],DCMax[6*iplane+3],DCMax[6*iplane+4],DCMax[6*iplane+5]);
  }
  SHMSWindows.close();

  //Start output of .root file with all histograms
  TFile *Histogram_file = new TFile(Form("../HISTOGRAMS/SHMSADCGates_Run%i.root",option.Atoi()),"RECREATE");
  TDirectory *DHGC = Histogram_file->mkdir("Heavy Gas Cherenkov ADC Timing Spectra"); DHGC->cd();
  for (Int_t ipmt=0; ipmt < 4; ipmt++) {
    PHGCPULSETIMEDIFF[ipmt]->Write(Form("HGC PMT %i",ipmt+1));
    }

  /*TDirectory *DNGC = Histogram_file->mkdir("Noble Gas Cherenkov ADC Timing Spectra"); DNGC->cd();
  for (Int_t ipmt=0; ipmt < 4; ipmt++) {
    PNGCPULSETIMEDIFF[ipmt]->Write(Form("NGC PMT %i",ipmt+1));
    }*/
  
  TDirectory *DAERO = Histogram_file->mkdir("Aerogel Cherenkov ADC Timing Spectra"); DAERO->cd();
  for (Int_t ipmt=0; ipmt < 7; ipmt++) {
    PAERONEGPULSETIMEDIFF[ipmt]->Write(Form("AERO NEG PMT %i",ipmt+1));
    PAEROPOSPULSETIMEDIFF[ipmt]->Write(Form("AERO POS PMT %i",ipmt+1));
    }

  TDirectory *DPRECAL = Histogram_file->mkdir("Pre-Shower ADC Timing Spectra"); DPRECAL->cd();
  for (Int_t ipmt=0; ipmt < 14; ipmt++) {
    PPRECALNEGPULSETIMEDIFF[ipmt]->Write(Form("PRECAL NEG PMT %i",ipmt+1));
    PPRECALPOSPULSETIMEDIFF[ipmt]->Write(Form("PRECAL POS PMT %i",ipmt+1));
    }

  TDirectory *DCAL = Histogram_file->mkdir("Calorimeter ADC Timing Spectra"); DCAL->cd();
  for (Int_t ipmt=0; ipmt < 224; ipmt++) {
    PCALPULSETIMEDIFF[ipmt]->Write(Form("CAL PMT %i",ipmt+1));
    }

  TDirectory *DHODO = Histogram_file->mkdir("Hodoscope ADC Timing Spectra"); DHODO->cd();
  for (Int_t ipmt=0; ipmt < 18; ipmt++) {
    PHODO1xNEGPULSETIMEDIFF[ipmt]->Write(Form("HODO 1x NEG PMT %i",ipmt+1));
    PHODO1yNEGPULSETIMEDIFF[ipmt]->Write(Form("HODO 1y NEG PMT %i",ipmt+1));
    PHODO2xNEGPULSETIMEDIFF[ipmt]->Write(Form("HODO 2x NEG PMT %i",ipmt+1));
    PHODO2yNEGPULSETIMEDIFF[ipmt]->Write(Form("HODO 2y NEG PMT %i",ipmt+1));
    PHODO1xPOSPULSETIMEDIFF[ipmt]->Write(Form("HODO 1x POS PMT %i",ipmt+1));
    PHODO1yPOSPULSETIMEDIFF[ipmt]->Write(Form("HODO 1y POS PMT %i",ipmt+1));
    PHODO2xPOSPULSETIMEDIFF[ipmt]->Write(Form("HODO 2x POS PMT %i",ipmt+1));
    PHODO2yPOSPULSETIMEDIFF[ipmt]->Write(Form("HODO 2y POS PMT %i",ipmt+1));
    }

  TDirectory *DDC = Histogram_file->mkdir("Drift Chamber ADC Timing Spectra"); DDC->cd();
  for (Int_t iplane = 0; iplane < 2; iplane++) {
    PDCRAWTDC[6*iplane]->Write(Form("DC %du1 Plane",iplane+1));
    PDCRAWTDC[6*iplane+1]->Write(Form("DC %dv1 Plane",iplane+1));
    PDCRAWTDC[6*iplane+2]->Write(Form("DC %dx1 Plane",iplane+1));
    PDCRAWTDC[6*iplane+3]->Write(Form("DC %du2 Plane",iplane+1));
    PDCRAWTDC[6*iplane+4]->Write(Form("DC %dv2 Plane",iplane+1));
    PDCRAWTDC[6*iplane+5]->Write(Form("DC %dx2 Plane",iplane+1));
  }

  Histogram_file->Close();
}                  
