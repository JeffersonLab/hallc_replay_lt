#define HMSADCGates_cxx
// The class definition in HMSADCGates.h has been generated automatically
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
// root> T->Process("HMSADCGates.C")
// root> T->Process("HMSADCGates.C","some options")
// root> T->Process("HMSADCGates.C+")
//


#include "HMSADCGates.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TSpectrum.h>
#include <TPolyMarker.h>
#include <TMath.h>
#include <TSystem.h>

void HMSADCGates::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

   
   Info("Begin", "Starting HMS Detector ADC Timing Window Script");
}

void HMSADCGates::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();


   h1HCERPulseTimeStarttimeDiff = new TH1F*[2];
   for (Int_t ipmt=0; ipmt<2; ipmt++) {
     h1HCERPulseTimeStarttimeDiff[ipmt] = new TH1F(Form("HCERPulseTimeStarttimeDiff%d",ipmt+1),Form("Pulse Time Information for HMS CER PMT%d Start Time Subtracted;Time (ns);Counts",ipmt+1),1000,0,200);

     GetOutputList()->Add(h1HCERPulseTimeStarttimeDiff[ipmt]);
   }

   h1H1prCALNegPulseTimeStarttimeDiff = new TH1F*[13];
   h1H1prCALPosPulseTimeStarttimeDiff = new TH1F*[13];
   h1H2taCALNegPulseTimeStarttimeDiff = new TH1F*[13];
   h1H2taCALPosPulseTimeStarttimeDiff = new TH1F*[13];
   h1H3taCALNegPulseTimeStarttimeDiff = new TH1F*[13];
   h1H3taCALPosPulseTimeStarttimeDiff = new TH1F*[13];
   h1H4taCALNegPulseTimeStarttimeDiff = new TH1F*[13];
   h1H4taCALPosPulseTimeStarttimeDiff = new TH1F*[13];
   for (Int_t ipmt=0; ipmt<13; ipmt++) {
     h1H1prCALNegPulseTimeStarttimeDiff[ipmt] = new TH1F(Form("H1prCALNegPulseTimeStarttimeDiff%d",ipmt+1),Form("Pulse Time Information for HMS 1 pr CAL Neg PMT%d Start Time Subtracted;Time (ns);Counts",ipmt+1),1000,-200,0);
     h1H1prCALPosPulseTimeStarttimeDiff[ipmt] = new TH1F(Form("H1prCALPosPulseTimeStarttimeDiff%d",ipmt+1),Form("Pulse Time Information for HMS 1 pr CAL Pos PMT%d Start Time Subtracted;Time (ns);Counts",ipmt+1),1000,-200,0);
     
     h1H2taCALNegPulseTimeStarttimeDiff[ipmt] = new TH1F(Form("H2taCALNegPulseTimeStarttimeDiff%d",ipmt+1),Form("Pulse Time Information for HMS 1 pr CAL Neg PMT%d Start Time Subtracted;Time (ns);Counts",ipmt+1),1000,-200,0);
     h1H2taCALPosPulseTimeStarttimeDiff[ipmt] = new TH1F(Form("H2taCALPosPulseTimeStarttimeDiff%d",ipmt+1),Form("Pulse Time Information for HMS 1 pr CAL Pos PMT%d Start Time Subtracted;Time (ns);Counts",ipmt+1),1000,-200,0);
     
     h1H3taCALNegPulseTimeStarttimeDiff[ipmt] = new TH1F(Form("H3taCALNegPulseTimeStarttimeDiff%d",ipmt+1),Form("Pulse Time Information for HMS 1 pr CAL Neg PMT%d Start Time Subtracted;Time (ns);Counts",ipmt+1),1000,-200,0);
     h1H3taCALPosPulseTimeStarttimeDiff[ipmt] = new TH1F(Form("H3taCALPosPulseTimeStarttimeDiff%d",ipmt+1),Form("Pulse Time Information for HMS 1 pr CAL Pos PMT%d Start Time Subtracted;Time (ns);Counts",ipmt+1),1000,-200,0);
     
     h1H4taCALNegPulseTimeStarttimeDiff[ipmt] = new TH1F(Form("H4taCALNegPulseTimeStarttimeDiff%d",ipmt+1),Form("Pulse Time Information for HMS 1 pr CAL Neg PMT%d Start Time Subtracted;Time (ns);Counts",ipmt+1),1000,-200,0);
     h1H4taCALPosPulseTimeStarttimeDiff[ipmt] = new TH1F(Form("H4taCALPosPulseTimeStarttimeDiff%d",ipmt+1),Form("Pulse Time Information for HMS 1 pr CAL Pos PMT%d Start Time Subtracted;Time (ns);Counts",ipmt+1),1000,-200,0);

     GetOutputList()->Add(h1H1prCALNegPulseTimeStarttimeDiff[ipmt]);
     GetOutputList()->Add(h1H1prCALPosPulseTimeStarttimeDiff[ipmt]);
     GetOutputList()->Add(h1H2taCALNegPulseTimeStarttimeDiff[ipmt]);
     GetOutputList()->Add(h1H2taCALPosPulseTimeStarttimeDiff[ipmt]);
     GetOutputList()->Add(h1H3taCALNegPulseTimeStarttimeDiff[ipmt]);
     GetOutputList()->Add(h1H3taCALPosPulseTimeStarttimeDiff[ipmt]);
     GetOutputList()->Add(h1H4taCALNegPulseTimeStarttimeDiff[ipmt]);
     GetOutputList()->Add(h1H4taCALPosPulseTimeStarttimeDiff[ipmt]);
   }

   h1HDCRawTdc = new TH1F*[12];
   for (Int_t ipmt=0; ipmt<12; ipmt++) {
     h1HDCRawTdc[ipmt] = new TH1F(Form("PDCRawTdc%d",ipmt+1),"Information for HMS DC Raw TDC;TDC Channel;Counts",250,-15000,-10000);

     GetOutputList()->Add(h1HDCRawTdc[ipmt]);
     }

   h1HHODO1xNegPulseTimeStarttimeDiff = new TH1F*[16];
   h1HHODO1xPosPulseTimeStarttimeDiff = new TH1F*[16];
   h1HHODO1yNegPulseTimeStarttimeDiff = new TH1F*[16];
   h1HHODO1yPosPulseTimeStarttimeDiff = new TH1F*[16];
   h1HHODO2xNegPulseTimeStarttimeDiff = new TH1F*[16];
   h1HHODO2xPosPulseTimeStarttimeDiff = new TH1F*[16];
   h1HHODO2yNegPulseTimeStarttimeDiff = new TH1F*[16];
   h1HHODO2yPosPulseTimeStarttimeDiff = new TH1F*[16];
   for (Int_t ipmt=0; ipmt<16; ipmt++) {
     h1HHODO1xNegPulseTimeStarttimeDiff[ipmt] = new TH1F(Form("HHODO1xNegPulseTimeStarttimeDiff%d",ipmt+1),Form("Pulse Time Information for HMS HODO 1x Neg PMT%d Start Time Subtracted;Time (ns);Counts",ipmt+1),1000,-200,0);
     h1HHODO1xPosPulseTimeStarttimeDiff[ipmt] = new TH1F(Form("HHODO1xPosPulseTimeStarttimeDiff%d",ipmt+1),Form("Pulse Time Information for HMS HODO 1x Pos PMT%d Start Time Subtracted;Time (ns);Counts",ipmt+1),1000,-200,0);
     h1HHODO1yNegPulseTimeStarttimeDiff[ipmt] = new TH1F(Form("HHODO1yNegPulseTimeStarttimeDiff%d",ipmt+1),Form("Pulse Time Information for HMS HODO 1y Neg PMT%d Start Time Subtracted;Time (ns);Counts",ipmt+1),1000,-200,0);
     h1HHODO1yPosPulseTimeStarttimeDiff[ipmt] = new TH1F(Form("HHODO1yPosPulseTimeStarttimeDiff%d",ipmt+1),Form("Pulse Time Information for HMS HODO 1y Pos PMT%d Start Time Subtracted;Time (ns);Counts",ipmt+1),1000,-200,0);
     h1HHODO2xNegPulseTimeStarttimeDiff[ipmt] = new TH1F(Form("HHODO2xNegPulseTimeStarttimeDiff%d",ipmt+1),Form("Pulse Time Information for HMS HODO 2x Neg PMT%d Start Time Subtracted;Time (ns);Counts",ipmt+1),1000,-200,0);
     h1HHODO2xPosPulseTimeStarttimeDiff[ipmt] = new TH1F(Form("HHODO2xPosPulseTimeStarttimeDiff%d",ipmt+1),Form("Pulse Time Information for HMS HODO 2x Pos PMT%d Start Time Subtracted;Time (ns);Counts",ipmt+1),1000,-200,0);
     h1HHODO2yNegPulseTimeStarttimeDiff[ipmt] = new TH1F(Form("HHODO2yNegPulseTimeStarttimeDiff%d",ipmt+1),Form("Pulse Time Information for HMS HODO 2y Neg PMT%d Start Time Subtracted;Time (ns);Counts",ipmt+1),1000,-200,0);
     h1HHODO2yPosPulseTimeStarttimeDiff[ipmt] = new TH1F(Form("HHODO2yPosPulseTimeStarttimeDiff%d",ipmt+1),Form("Pulse Time Information for HMS HODO 2y Pos PMT%d Start Time Subtracted;Time (ns);Counts",ipmt+1),1000,-200,0);

     GetOutputList()->Add(h1HHODO1xNegPulseTimeStarttimeDiff[ipmt]);
     GetOutputList()->Add(h1HHODO1xPosPulseTimeStarttimeDiff[ipmt]);
     GetOutputList()->Add(h1HHODO1yNegPulseTimeStarttimeDiff[ipmt]);
     GetOutputList()->Add(h1HHODO1yPosPulseTimeStarttimeDiff[ipmt]);
     GetOutputList()->Add(h1HHODO2xNegPulseTimeStarttimeDiff[ipmt]);
     GetOutputList()->Add(h1HHODO2xPosPulseTimeStarttimeDiff[ipmt]);
     GetOutputList()->Add(h1HHODO2yNegPulseTimeStarttimeDiff[ipmt]);
     GetOutputList()->Add(h1HHODO2yPosPulseTimeStarttimeDiff[ipmt]);
   }
}

Bool_t HMSADCGates::Process(Long64_t entry)
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

   for (Int_t i = 0; i < *Ndata_H_cer_adcPulseTime; i++) {
     if (H_cer_adcErrorFlag[i] == 1) continue;
     Int_t current_pmt = H_cer_adcCounter[i] - 1;
     h1HCERPulseTimeStarttimeDiff[current_pmt]->Fill(-H_cer_adcPulseTime[i] + *H_hod_starttime);   
   }

   for (Int_t i = 0; i < *Ndata_H_1prcal_negAdcPulseTime; i++) {
     if (H_1prcal_negAdcErrorFlag[i] == 1) continue;
     Int_t current_pmt = H_1prcal_negAdcCounter[i] - 1;
     h1H1prCALNegPulseTimeStarttimeDiff[current_pmt]->Fill(-H_1prcal_negAdcPulseTime[i] + *H_hod_starttime); 
   }

   for (Int_t i = 0; i < *Ndata_H_1prcal_posAdcPulseTime; i++) {
     if (H_1prcal_posAdcErrorFlag[i] == 1) continue;
     Int_t current_pmt = H_1prcal_posAdcCounter[i] - 1;
     h1H1prCALPosPulseTimeStarttimeDiff[current_pmt]->Fill(-H_1prcal_posAdcPulseTime[i] + *H_hod_starttime); 
   }

   for (Int_t i = 0; i < *Ndata_H_2tacal_negAdcPulseTime; i++) {
     if (H_2tacal_negAdcErrorFlag[i] == 1) continue;
     Int_t current_pmt = H_2tacal_negAdcCounter[i] - 1;
     h1H2taCALNegPulseTimeStarttimeDiff[current_pmt]->Fill(-H_2tacal_negAdcPulseTime[i] + *H_hod_starttime); 
   }

   for (Int_t i = 0; i < *Ndata_H_2tacal_posAdcPulseTime; i++) {
     if (H_2tacal_posAdcErrorFlag[i] == 1) continue;
     Int_t current_pmt = H_2tacal_posAdcCounter[i] - 1;
     h1H2taCALPosPulseTimeStarttimeDiff[current_pmt]->Fill(-H_2tacal_posAdcPulseTime[i] + *H_hod_starttime); 
   }

   for (Int_t i = 0; i < *Ndata_H_3tacal_negAdcPulseTime; i++) {
     if (H_3tacal_negAdcErrorFlag[i] == 1) continue;
     Int_t current_pmt = H_3tacal_negAdcCounter[i] - 1;
     h1H3taCALNegPulseTimeStarttimeDiff[current_pmt]->Fill(-H_3tacal_negAdcPulseTime[i] + *H_hod_starttime); 
   }

   for (Int_t i = 0; i < *Ndata_H_3tacal_posAdcPulseTime; i++) {
     if (H_3tacal_posAdcErrorFlag[i] == 1) continue;
     Int_t current_pmt = H_3tacal_posAdcCounter[i] - 1;
     h1H3taCALPosPulseTimeStarttimeDiff[current_pmt]->Fill(-H_3tacal_posAdcPulseTime[i] + *H_hod_starttime); 
   }

   for (Int_t i = 0; i < *Ndata_H_4tacal_negAdcPulseTime; i++) {
     if (H_4tacal_negAdcErrorFlag[i] == 1) continue;
     Int_t current_pmt = H_4tacal_negAdcCounter[i] - 1;
     h1H4taCALNegPulseTimeStarttimeDiff[current_pmt]->Fill(-H_4tacal_negAdcPulseTime[i] + *H_hod_starttime); 
   }

   for (Int_t i = 0; i < *Ndata_H_4tacal_posAdcPulseTime; i++) {
     if (H_4tacal_posAdcErrorFlag[i] == 1) continue;
     Int_t current_pmt = H_4tacal_posAdcCounter[i] - 1;
     h1H4taCALPosPulseTimeStarttimeDiff[current_pmt]->Fill(-H_4tacal_posAdcPulseTime[i] + *H_hod_starttime); 
   }

   for (Int_t i = 0; i < *Ndata_H_dc_1u1_time; i++) {
     h1HDCRawTdc[0]->Fill(H_dc_1u1_rawtdc[i]); 
     h1HDCRawTdc[1]->Fill(H_dc_1u2_rawtdc[i]);
     h1HDCRawTdc[2]->Fill(H_dc_1v1_rawtdc[i]); 
     h1HDCRawTdc[3]->Fill(H_dc_1v2_rawtdc[i]);
     h1HDCRawTdc[4]->Fill(H_dc_1x1_rawtdc[i]); 
     h1HDCRawTdc[5]->Fill(H_dc_1x2_rawtdc[i]);
     h1HDCRawTdc[6]->Fill(H_dc_2u1_rawtdc[i]); 
     h1HDCRawTdc[7]->Fill(H_dc_2u2_rawtdc[i]);
     h1HDCRawTdc[8]->Fill(H_dc_2v1_rawtdc[i]); 
     h1HDCRawTdc[9]->Fill(H_dc_2v2_rawtdc[i]);
     h1HDCRawTdc[10]->Fill(H_dc_2x1_rawtdc[i]); 
     h1HDCRawTdc[11]->Fill(H_dc_2x2_rawtdc[i]);
   }

   for (Int_t i = 0; i < *Ndata_H_hod_1x_negAdcPulseTime; i++) {
     if (H_hod_1x_negAdcErrorFlag[i] == 1) continue;
     Int_t current_pmt = H_hod_1x_negAdcCounter[i] - 1;
     h1HHODO1xNegPulseTimeStarttimeDiff[current_pmt]->Fill(H_hod_1x_negTdcTimeCorr[current_pmt] - H_hod_1x_negAdcPulseTime[i]);
     /*for (Int_t j = 0; j < *Ndata_H_hod_1x_negTdcTime; j++) {
       h1HHODO1xPosPulseTimeStarttimeDiff[current_pmt]->Fill(H_hod_1x_negTdcTime[j] - H_hod_1x_negAdcPulseTime[i]); 
       }*/
   }
   
   for (Int_t i = 0; i < *Ndata_H_hod_1x_posAdcPulseTime; i++) {
     if (H_hod_1x_posAdcErrorFlag[i] == 1) continue;
     Int_t current_pmt = H_hod_1x_posAdcCounter[i] - 1;
     h1HHODO1xPosPulseTimeStarttimeDiff[current_pmt]->Fill(H_hod_1x_posTdcTimeCorr[current_pmt]  - H_hod_1x_posAdcPulseTime[i]);
     /*for (Int_t j = 0; j < *Ndata_H_hod_1x_posTdcTime; j++) {
       h1HHODO1xPosPulseTimeStarttimeDiff[current_pmt]->Fill(H_hod_1x_posTdcTime[j] - H_hod_1x_posAdcPulseTime[i]); 
       }*/
   }

   for (Int_t i = 0; i < *Ndata_H_hod_1y_negAdcPulseTime; i++) {
     if (H_hod_1y_negAdcErrorFlag[i] == 1) continue;
     Int_t current_pmt = H_hod_1y_negAdcCounter[i] - 1;
     h1HHODO1yNegPulseTimeStarttimeDiff[current_pmt]->Fill(H_hod_1y_negTdcTimeCorr[current_pmt] - H_hod_1y_negAdcPulseTime[i]); 
     /*for (Int_t j = 0; j < *Ndata_H_hod_1y_negTdcTime; j++) {
       h1HHODO1yNegPulseTimeStarttimeDiff[current_pmt]->Fill(H_hod_1y_negTdcTime[j] - H_hod_1y_negAdcPulseTime[i]); 
       }*/
   }

   for (Int_t i = 0; i < *Ndata_H_hod_1y_posAdcPulseTime; i++) {
     if (H_hod_1y_posAdcErrorFlag[i] == 1) continue;
     Int_t current_pmt = H_hod_1y_posAdcCounter[i] - 1;
     h1HHODO1yPosPulseTimeStarttimeDiff[current_pmt]->Fill(H_hod_1y_posTdcTimeCorr[current_pmt] - H_hod_1y_posAdcPulseTime[i]); 
     /*for (Int_t j = 0; j < *Ndata_H_hod_1y_posTdcTime; j++) {
       h1HHODO1yPosPulseTimeStarttimeDiff[current_pmt]->Fill(H_hod_1y_posTdcTime[j] - H_hod_1y_posAdcPulseTime[i]); 
       }*/
   }

   for (Int_t i = 0; i < *Ndata_H_hod_2x_negAdcPulseTime; i++) {
     if (H_hod_2x_negAdcErrorFlag[i] == 1) continue;
     Int_t current_pmt = H_hod_2x_negAdcCounter[i] - 1;
     h1HHODO2xNegPulseTimeStarttimeDiff[current_pmt]->Fill(H_hod_2x_negTdcTimeCorr[current_pmt] - H_hod_2x_negAdcPulseTime[i]); 
     /*for (Int_t j = 0; j < *Ndata_H_hod_2x_negTdcTime; j++) {
       h1HHODO2xNegPulseTimeStarttimeDiff[current_pmt]->Fill(H_hod_2x_negTdcTime[j] - H_hod_2x_negAdcPulseTime[i]); 
       }*/
   }

   for (Int_t i = 0; i < *Ndata_H_hod_2x_posAdcPulseTime; i++) {
     if (H_hod_2x_posAdcErrorFlag[i] == 1) continue;
     Int_t current_pmt = H_hod_2x_posAdcCounter[i] - 1;
     h1HHODO2xPosPulseTimeStarttimeDiff[current_pmt]->Fill(H_hod_2x_posTdcTimeCorr[current_pmt] - H_hod_2x_posAdcPulseTime[i]); 
     /*for (Int_t j = 0; j < *Ndata_H_hod_2x_posTdcTime; j++) {
       h1HHODO2xPosPulseTimeStarttimeDiff[current_pmt]->Fill(H_hod_2x_posTdcTime[j] - H_hod_2x_posAdcPulseTime[i]); 
       }*/
   }

   for (Int_t i = 0; i < *Ndata_H_hod_2y_negAdcPulseTime; i++) {
     if (H_hod_2y_negAdcErrorFlag[i] == 1) continue;
     Int_t current_pmt = H_hod_2y_negAdcCounter[i] - 1;
     h1HHODO2yNegPulseTimeStarttimeDiff[current_pmt]->Fill(H_hod_2y_negTdcTimeCorr[current_pmt] - H_hod_2y_negAdcPulseTime[i]); 
     /*for (Int_t j = 0; j < *Ndata_H_hod_2y_negTdcTime; j++) {
       h1HHODO2yNegPulseTimeStarttimeDiff[current_pmt]->Fill(H_hod_2y_negTdcTime[j] - H_hod_2y_negAdcPulseTime[i]); 
       }*/
   }

   for (Int_t i = 0; i < *Ndata_H_hod_2y_posAdcPulseTime; i++) {
     if (H_hod_2y_posAdcErrorFlag[i] == 1) continue;
     Int_t current_pmt = H_hod_2y_posAdcCounter[i] - 1;
     h1HHODO2yPosPulseTimeStarttimeDiff[current_pmt]->Fill(H_hod_2y_posTdcTimeCorr[current_pmt] - H_hod_2y_posAdcPulseTime[i]); 
     /*for (Int_t j = 0; j < *Ndata_H_hod_2y_posTdcTime; j++) {
       h1HHODO2yPosPulseTimeStarttimeDiff[current_pmt]->Fill(H_hod_2y_posTdcTime[j] - H_hod_2y_posAdcPulseTime[i]); 
       }*/
   }

   return kTRUE;
}

void HMSADCGates::SlaveTerminate()
{
  // The SlaveTerminate() function is called after all entries or objects
  // have been processed. When running with PROOF SlaveTerminate() is called
  // on each slave server.

}

void HMSADCGates::Terminate()
{
  // The Terminate() function is the last function to be called during
  // a query. It always runs on the client, it can be used to present
  // the results graphically or save the results to file.

  Info("Terminate", "Branches Sorted, Now Calculating Windows");

  TH1F* HCERPULSETIMEDIFF[2];
  for (Int_t ipmt = 0; ipmt < 2; ipmt++) {
    HCERPULSETIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("HCERPulseTimeStarttimeDiff%d",ipmt+1)));
  }

  TH1F* H1prCALNEGPULSETIMEDIFF[13];
  TH1F* H1prCALPOSPULSETIMEDIFF[13];
  TH1F* H2taCALNEGPULSETIMEDIFF[13];
  TH1F* H2taCALPOSPULSETIMEDIFF[13];
  TH1F* H3taCALNEGPULSETIMEDIFF[13];
  TH1F* H3taCALPOSPULSETIMEDIFF[13];
  TH1F* H4taCALNEGPULSETIMEDIFF[13];
  TH1F* H4taCALPOSPULSETIMEDIFF[13];
  for (Int_t ipmt = 0; ipmt < 13; ipmt++) {
    H1prCALNEGPULSETIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("H1prCALNegPulseTimeStarttimeDiff%d",ipmt+1)));
    H1prCALPOSPULSETIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("H1prCALPosPulseTimeStarttimeDiff%d",ipmt+1)));
    H2taCALNEGPULSETIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("H2taCALNegPulseTimeStarttimeDiff%d",ipmt+1)));
    H2taCALPOSPULSETIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("H2taCALPosPulseTimeStarttimeDiff%d",ipmt+1)));
    H3taCALNEGPULSETIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("H3taCALNegPulseTimeStarttimeDiff%d",ipmt+1)));
    H3taCALPOSPULSETIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("H3taCALPosPulseTimeStarttimeDiff%d",ipmt+1)));
    H4taCALNEGPULSETIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("H4taCALNegPulseTimeStarttimeDiff%d",ipmt+1)));
    H4taCALPOSPULSETIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("H4taCALPosPulseTimeStarttimeDiff%d",ipmt+1)));
    }
  
  TH1F* HDCRAWTDC[12];
  for (Int_t ipmt = 0; ipmt < 12; ipmt++) {
    HDCRAWTDC[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("PDCRawTdc%d",ipmt+1)));
  }

  TH1F* HHODO1xNEGPULSETIMEDIFF[16];
  TH1F* HHODO1xPOSPULSETIMEDIFF[16];
  TH1F* HHODO1yNEGPULSETIMEDIFF[16];
  TH1F* HHODO1yPOSPULSETIMEDIFF[16];
  TH1F* HHODO2xNEGPULSETIMEDIFF[16];
  TH1F* HHODO2xPOSPULSETIMEDIFF[16];
  TH1F* HHODO2yNEGPULSETIMEDIFF[16];
  TH1F* HHODO2yPOSPULSETIMEDIFF[16];
  for (Int_t ipmt = 0; ipmt < 16; ipmt++) {
    HHODO1xNEGPULSETIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("HHODO1xNegPulseTimeStarttimeDiff%d",ipmt+1)));
    HHODO1xPOSPULSETIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("HHODO1xPosPulseTimeStarttimeDiff%d",ipmt+1)));
    HHODO1yNEGPULSETIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("HHODO1yNegPulseTimeStarttimeDiff%d",ipmt+1)));
    HHODO1yPOSPULSETIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("HHODO1yPosPulseTimeStarttimeDiff%d",ipmt+1)));
    HHODO2xNEGPULSETIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("HHODO2xNegPulseTimeStarttimeDiff%d",ipmt+1)));
    HHODO2xPOSPULSETIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("HHODO2xPosPulseTimeStarttimeDiff%d",ipmt+1)));
    HHODO2yNEGPULSETIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("HHODO2yNegPulseTimeStarttimeDiff%d",ipmt+1)));
    HHODO2yPOSPULSETIMEDIFF[ipmt] = dynamic_cast<TH1F*> (GetOutputList()->FindObject(Form("HHODO2yPosPulseTimeStarttimeDiff%d",ipmt+1)));
    }
  
  
  //Begin peak Finding
  gSystem->RedirectOutput("/dev/null","a");
  Double_t CER_Window[2];
  for (Int_t ipmt = 0; ipmt < 2; ipmt++) {
    TSpectrum *s = new TSpectrum(1);
    s->Search(HCERPULSETIMEDIFF[ipmt], 1.0, "nobackground&&nodraw", 0.001);
    TList *functions = HCERPULSETIMEDIFF[ipmt]->GetListOfFunctions();
    TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
    CER_Window[ipmt] = *pm->GetX();
  }
  
  Double_t pr1CALNEG_Window[13];
  for (Int_t ipmt = 0; ipmt < 13; ipmt++) {
    TSpectrum *s = new TSpectrum(1);
    s->Search(H1prCALNEGPULSETIMEDIFF[ipmt], 1.0, "nobackground&&nodraw", 0.001);
    TList *functions = H1prCALNEGPULSETIMEDIFF[ipmt]->GetListOfFunctions();
    TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
    pr1CALNEG_Window[ipmt] = *pm->GetX();
  }
  
  Double_t pr1CALPOS_Window[13];
  for (Int_t ipmt = 0; ipmt < 13; ipmt++) {
    TSpectrum *s = new TSpectrum(1);
    s->Search(H1prCALPOSPULSETIMEDIFF[ipmt], 1.0, "nobackground&&nodraw", 0.001);
    TList *functions = H1prCALPOSPULSETIMEDIFF[ipmt]->GetListOfFunctions();
    TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
    pr1CALPOS_Window[ipmt] = *pm->GetX();
  }
  
  Double_t ta2CALNEG_Window[13];
  for (Int_t ipmt = 0; ipmt < 13; ipmt++) {
    TSpectrum *s = new TSpectrum(1);
    s->Search(H2taCALNEGPULSETIMEDIFF[ipmt], 1.0, "nobackground&&nodraw", 0.001);
    TList *functions = H2taCALNEGPULSETIMEDIFF[ipmt]->GetListOfFunctions();
    TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
    ta2CALNEG_Window[ipmt] = *pm->GetX();
  }

  Double_t ta2CALPOS_Window[13];
  for (Int_t ipmt = 0; ipmt < 13; ipmt++) {
    TSpectrum *s = new TSpectrum(1);
    s->Search(H2taCALPOSPULSETIMEDIFF[ipmt], 1.0, "nobackground&&nodraw", 0.001);
    TList *functions = H2taCALPOSPULSETIMEDIFF[ipmt]->GetListOfFunctions();
    TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
    ta2CALPOS_Window[ipmt] = *pm->GetX();
  }

  Double_t ta3CALNEG_Window[13];
  for (Int_t ipmt = 0; ipmt < 13; ipmt++) {
    //if (ipmt > -1 || H3taCALNEGPULSETIMEDIFF[ipmt]->GetEntries() != 0) {
    //  TSpectrum *s = new TSpectrum(1);
    //  s->Search(H3taCALNEGPULSETIMEDIFF[ipmt], 1.0, "nobackground&&nodraw", 0.001);
    //  TList *functions = H3taCALNEGPULSETIMEDIFF[ipmt]->GetListOfFunctions();
    //  TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
    //  ta3CALNEG_Window[ipmt] = *pm->GetX();
    //  } else {
    //  ta3CALNEG_Window[ipmt] = 1e+38;
    //  }
    ta3CALNEG_Window[ipmt] = 1e+38;
  }


  Double_t ta3CALPOS_Window[13];
  for (Int_t ipmt = 0; ipmt < 13; ipmt++) {
    TSpectrum *s = new TSpectrum(1);
    s->Search(H3taCALPOSPULSETIMEDIFF[ipmt], 1.0, "nobackground&&nodraw", 0.001);
    TList *functions = H3taCALPOSPULSETIMEDIFF[ipmt]->GetListOfFunctions();
    TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
    ta3CALPOS_Window[ipmt] = *pm->GetX();
  }

  Double_t ta4CALNEG_Window[13];
  for (Int_t ipmt = 0; ipmt < 13; ipmt++) {
    //if (ipmt > -1 || H4taCALNEGPULSETIMEDIFF[ipmt]->GetEntries() != 0) {
    //  TSpectrum *s = new TSpectrum(1);
    //  s->Search(H4taCALNEGPULSETIMEDIFF[ipmt], 1.0, "nobackground&&nodraw", 0.001);
    //  TList *functions = H4taCALNEGPULSETIMEDIFF[ipmt]->GetListOfFunctions();
    //  TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
    //  ta4CALNEG_Window[ipmt] = *pm->GetX();
    //} else {
    //  ta4CALNEG_Window[ipmt] = 1e+38;
    //  }
    ta4CALNEG_Window[ipmt] = 1e+38;
  }

  Double_t ta4CALPOS_Window[13];
  for (Int_t ipmt = 0; ipmt < 13; ipmt++) {
    TSpectrum *s = new TSpectrum(1);
    s->Search(H4taCALPOSPULSETIMEDIFF[ipmt], 1.0, "nobackground&&nodraw", 0.001);
    TList *functions = H4taCALPOSPULSETIMEDIFF[ipmt]->GetListOfFunctions();
    TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
    ta4CALPOS_Window[ipmt] = *pm->GetX();
  }
  
  Double_t DC_Window[12];
  for (Int_t ipmt = 0; ipmt < 12; ipmt++) {
    TSpectrum *s = new TSpectrum(1);
    s->Search(HDCRAWTDC[ipmt], 1.0, "nobackground&&nodraw", 0.001);
    TList *functions = HDCRAWTDC[ipmt]->GetListOfFunctions();
    TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
    DC_Window[ipmt] = *pm->GetX();
  }
  
  Double_t HODO1xNeg_Window[16];
  for (Int_t ipmt = 0; ipmt < 16; ipmt++) {
    if (HHODO1xNEGPULSETIMEDIFF[ipmt]->GetEntries() != 0) {
      TSpectrum *s = new TSpectrum(1);
      s->Search(HHODO1xNEGPULSETIMEDIFF[ipmt], 1.0, "nobackground&&nodraw", 0.001);
      TList *functions = HHODO1xNEGPULSETIMEDIFF[ipmt]->GetListOfFunctions();
      TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
      HODO1xNeg_Window[ipmt] = *pm->GetX();
    } else {
      HODO1xNeg_Window[ipmt] = 1e+38;
    }
  }
  
  Double_t HODO1xPos_Window[16];
  for (Int_t ipmt = 0; ipmt < 16; ipmt++) {
    if (HHODO1xPOSPULSETIMEDIFF[ipmt]->GetEntries() != 0) {
      TSpectrum *s = new TSpectrum(1);
      s->Search(HHODO1xPOSPULSETIMEDIFF[ipmt], 1.0, "nobackground&&nodraw", 0.001);
      TList *functions = HHODO1xPOSPULSETIMEDIFF[ipmt]->GetListOfFunctions();
      TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
      HODO1xPos_Window[ipmt] = *pm->GetX();
    } else {
      HODO1xPos_Window[ipmt] = 1e+38;
    }
  }

  Double_t HODO1yNeg_Window[16];
  for (Int_t ipmt = 0; ipmt < 16; ipmt++) {
    if (ipmt < 10 || HHODO1yNEGPULSETIMEDIFF[ipmt]->GetEntries() != 0) {
      TSpectrum *s = new TSpectrum(1);
      s->Search(HHODO1yNEGPULSETIMEDIFF[ipmt], 1.0, "nobackground&&nodraw", 0.001);
      TList *functions = HHODO1yNEGPULSETIMEDIFF[ipmt]->GetListOfFunctions();
      TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
      HODO1yNeg_Window[ipmt] = *pm->GetX();
    } else {
      HODO1yNeg_Window[ipmt] = 1e+38;
    }
  }

  Double_t HODO1yPos_Window[16];
  for (Int_t ipmt = 0; ipmt < 16; ipmt++) {
    if (ipmt < 10 || HHODO1yPOSPULSETIMEDIFF[ipmt]->GetEntries() != 0) {
      TSpectrum *s = new TSpectrum(1);
      s->Search(HHODO1yPOSPULSETIMEDIFF[ipmt], 1.0, "nobackground&&nodraw", 0.001);
      TList *functions = HHODO1yPOSPULSETIMEDIFF[ipmt]->GetListOfFunctions();
      TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
      HODO1yPos_Window[ipmt] = *pm->GetX();
    } else {
      HODO1yPos_Window[ipmt] = 1e+38;
    }
  }

  Double_t HODO2xNeg_Window[16];
  for (Int_t ipmt = 0; ipmt < 16; ipmt++) {
    if (HHODO2xNEGPULSETIMEDIFF[ipmt]->GetEntries() != 0) {
      TSpectrum *s = new TSpectrum(1);
      s->Search(HHODO2xNEGPULSETIMEDIFF[ipmt], 1.0, "nobackground&&nodraw", 0.001);
      TList *functions = HHODO2xNEGPULSETIMEDIFF[ipmt]->GetListOfFunctions();
      TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
      HODO2xNeg_Window[ipmt] = *pm->GetX();
    }    
    else {
      HODO2xNeg_Window[ipmt] = 1e+38;
    }
  }

  Double_t HODO2xPos_Window[16];
  for (Int_t ipmt = 0; ipmt < 16; ipmt++) {
    if (HHODO2xPOSPULSETIMEDIFF[ipmt]->GetEntries() != 0) {
      TSpectrum *s = new TSpectrum(1);
      s->Search(HHODO2xPOSPULSETIMEDIFF[ipmt], 1.0, "nobackground&&nodraw", 0.001);
      TList *functions = HHODO2xPOSPULSETIMEDIFF[ipmt]->GetListOfFunctions();
      TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
      HODO2xPos_Window[ipmt] = *pm->GetX();
    }
    else {
      HODO2xPos_Window[ipmt] = 1e+38;
    }
  }

  Double_t HODO2yNeg_Window[16];
  for (Int_t ipmt = 0; ipmt < 16; ipmt++) {
    if (ipmt < 10 || HHODO2yNEGPULSETIMEDIFF[ipmt]->GetEntries() != 0) {
      TSpectrum *s = new TSpectrum(1);
      s->Search(HHODO2yNEGPULSETIMEDIFF[ipmt], 1.0, "nobackground&&nodraw", 0.001);
      TList *functions = HHODO2yNEGPULSETIMEDIFF[ipmt]->GetListOfFunctions();
      TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
      HODO2yNeg_Window[ipmt] = *pm->GetX();
    }
    else {
      HODO2yNeg_Window[ipmt] = 1e+38;
    }
  }

  Double_t HODO2yPos_Window[16];
  for (Int_t ipmt = 0; ipmt < 16; ipmt++) {
    if (ipmt < 10 || HHODO2yPOSPULSETIMEDIFF[ipmt]->GetEntries() != 0) {
      TSpectrum *s = new TSpectrum(1);
      s->Search(HHODO2yPOSPULSETIMEDIFF[ipmt], 1.0, "nobackground&&nodraw", 0.001);
      TList *functions = HHODO2yPOSPULSETIMEDIFF[ipmt]->GetListOfFunctions();
      TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
      HODO2yPos_Window[ipmt] = *pm->GetX();
    }
    else {
      HODO2yPos_Window[ipmt] = 1e+38;
    }
  }
  gSystem->RedirectOutput(0);

  //Begin Calculation of Window Values
  
  Int_t CERMinPMT1 = CER_Window[0] - 50; Int_t CERMaxPMT1 = CER_Window[0] + 50;
  Int_t CERMinPMT2 = CER_Window[1] - 50; Int_t CERMaxPMT2 = CER_Window[1] + 50;
  
  Int_t HODOPosMin[64]; Int_t HODOPosMax[64];
  Int_t HODONegMin[64]; Int_t HODONegMax[64];
  for (Int_t ipmt = 0; ipmt < 16; ipmt++) {  
    (HHODO1xPOSPULSETIMEDIFF[ipmt]->GetEntries() == 0) ? HODOPosMin[4*ipmt]    = -200 : HODOPosMin[4*ipmt]    = HODO1xPos_Window[ipmt] - 200;
    (HHODO1yPOSPULSETIMEDIFF[ipmt]->GetEntries() == 0) ? HODOPosMin[4*ipmt+1]  = -200 : HODOPosMin[4*ipmt+1]  = HODO1yPos_Window[ipmt] - 200;
    (HHODO2xPOSPULSETIMEDIFF[ipmt]->GetEntries() == 0) ? HODOPosMin[4*ipmt+2]  = -200 : HODOPosMin[4*ipmt+2]  = HODO2xPos_Window[ipmt] - 200;
    (HHODO2yPOSPULSETIMEDIFF[ipmt]->GetEntries() == 0) ? HODOPosMin[4*ipmt+3]  = -200 : HODOPosMin[4*ipmt+3]  = HODO2yPos_Window[ipmt] - 200;
    (HHODO1xNEGPULSETIMEDIFF[ipmt]->GetEntries() == 0) ? HODONegMin[4*ipmt]    = -200 : HODONegMin[4*ipmt]    = HODO1xNeg_Window[ipmt] - 200;
    (HHODO1yNEGPULSETIMEDIFF[ipmt]->GetEntries() == 0) ? HODONegMin[4*ipmt+1]  = -200 : HODONegMin[4*ipmt+1]  = HODO1yNeg_Window[ipmt] - 200;
    (HHODO2xNEGPULSETIMEDIFF[ipmt]->GetEntries() == 0) ? HODONegMin[4*ipmt+2]  = -200 : HODONegMin[4*ipmt+2]  = HODO2xNeg_Window[ipmt] - 200;
    (HHODO2yNEGPULSETIMEDIFF[ipmt]->GetEntries() == 0) ? HODONegMin[4*ipmt+3]  = -200 : HODONegMin[4*ipmt+3]  = HODO2yNeg_Window[ipmt] - 200;
    (HHODO1xPOSPULSETIMEDIFF[ipmt]->GetEntries() == 0) ? HODOPosMax[4*ipmt]    = 200 : HODOPosMax[4*ipmt]    = HODO1xPos_Window[ipmt] + 200;
    (HHODO1yPOSPULSETIMEDIFF[ipmt]->GetEntries() == 0) ? HODOPosMax[4*ipmt+1]  = 200 : HODOPosMax[4*ipmt+1]  = HODO1yPos_Window[ipmt] + 200;
    (HHODO2xPOSPULSETIMEDIFF[ipmt]->GetEntries() == 0) ? HODOPosMax[4*ipmt+2]  = 200 : HODOPosMax[4*ipmt+2]  = HODO2xPos_Window[ipmt] + 200;
    (HHODO2yPOSPULSETIMEDIFF[ipmt]->GetEntries() == 0) ? HODOPosMax[4*ipmt+3]  = 200 : HODOPosMax[4*ipmt+3]  = HODO2yPos_Window[ipmt] + 200;
    (HHODO1xNEGPULSETIMEDIFF[ipmt]->GetEntries() == 0) ? HODONegMax[4*ipmt]    = 200 : HODONegMax[4*ipmt]    = HODO1xNeg_Window[ipmt] + 200;
    (HHODO1yNEGPULSETIMEDIFF[ipmt]->GetEntries() == 0) ? HODONegMax[4*ipmt+1]  = 200 : HODONegMax[4*ipmt+1]  = HODO1yNeg_Window[ipmt] + 200;
    (HHODO2xNEGPULSETIMEDIFF[ipmt]->GetEntries() == 0) ? HODONegMax[4*ipmt+2]  = 200 : HODONegMax[4*ipmt+2]  = HODO2xNeg_Window[ipmt] + 200;
    (HHODO2yNEGPULSETIMEDIFF[ipmt]->GetEntries() == 0) ? HODONegMax[4*ipmt+3]  = 200 : HODONegMax[4*ipmt+3]  = HODO2yNeg_Window[ipmt] + 200;
  }
  
  Int_t CALPosMin[52]; Int_t CALPosMax[52];
  Int_t CALNegMin[52]; Int_t CALNegMax[52];
  for (Int_t ipmt = 0; ipmt < 13; ipmt++) {  
    (pr1CALPOS_Window[ipmt] == 1e+38) ? CALPosMin[ipmt] = -200 : CALPosMin[ipmt] = pr1CALPOS_Window[ipmt] - 50;
    (pr1CALNEG_Window[ipmt] == 1e+38) ? CALNegMin[ipmt] = -200 : CALNegMin[ipmt] = pr1CALNEG_Window[ipmt] - 50;
    (pr1CALPOS_Window[ipmt] == 1e+38) ? CALPosMax[ipmt] = 200 : CALPosMax[ipmt] = pr1CALPOS_Window[ipmt] + 50;
    (pr1CALNEG_Window[ipmt] == 1e+38) ? CALNegMax[ipmt] = 200 : CALNegMax[ipmt] = pr1CALNEG_Window[ipmt] + 50;
  }
  for (Int_t ipmt = 0; ipmt < 13; ipmt++) {  
    (ta2CALPOS_Window[ipmt] == 1e+38) ? CALPosMin[ipmt+13] = -200 : CALPosMin[ipmt+13] = ta2CALPOS_Window[ipmt] - 50;
    (ta2CALNEG_Window[ipmt] == 1e+38) ? CALNegMin[ipmt+13] = -200 : CALNegMin[ipmt+13] = ta2CALNEG_Window[ipmt] - 50;
    (ta2CALPOS_Window[ipmt] == 1e+38) ? CALPosMax[ipmt+13] = 200  : CALPosMax[ipmt+13] = ta2CALPOS_Window[ipmt] + 50;
    (ta2CALNEG_Window[ipmt] == 1e+38) ? CALNegMax[ipmt+13] = 200  : CALNegMax[ipmt+13] = ta2CALNEG_Window[ipmt] + 50;
  }
  for (Int_t ipmt = 0; ipmt < 13; ipmt++) {  
    (ta3CALPOS_Window[ipmt] == 1e+38) ? CALPosMin[ipmt+26] = -200 : CALPosMin[ipmt+26] = ta3CALPOS_Window[ipmt] - 50;
    (ta3CALNEG_Window[ipmt] == 1e+38) ? CALNegMin[ipmt+26] = -200 : CALNegMin[ipmt+26] = ta3CALNEG_Window[ipmt] - 50;
    (ta3CALPOS_Window[ipmt] == 1e+38) ? CALPosMax[ipmt+26] = 200  : CALPosMax[ipmt+26] = ta3CALPOS_Window[ipmt] + 50;
    (ta3CALNEG_Window[ipmt] == 1e+38) ? CALNegMax[ipmt+26] = 200  : CALNegMax[ipmt+26] = ta3CALNEG_Window[ipmt] + 50;
  }
  for (Int_t ipmt = 0; ipmt < 13; ipmt++) {  
    (ta4CALPOS_Window[ipmt] == 1e+38) ? CALPosMin[ipmt+39] = -200 : CALPosMin[ipmt+39] = ta4CALPOS_Window[ipmt] - 50;
    (ta4CALNEG_Window[ipmt] == 1e+38) ? CALNegMin[ipmt+39] = -200 : CALNegMin[ipmt+39] = ta4CALNEG_Window[ipmt] - 50;
    (ta4CALPOS_Window[ipmt] == 1e+38) ? CALPosMax[ipmt+39] = 200  : CALPosMax[ipmt+39] = ta4CALPOS_Window[ipmt] + 50;
    (ta4CALNEG_Window[ipmt] == 1e+38) ? CALNegMax[ipmt+39] = 200  : CALNegMax[ipmt+39] = ta4CALNEG_Window[ipmt] + 50;
  }  
  
  Int_t DCMin[12]; Int_t DCMax[12];
  for (Int_t ipmt = 0; ipmt < 12; ipmt++) {
    (DC_Window[ipmt] == 1e+38) ? DCMin[ipmt] = -30000 : DCMin[ipmt] = DC_Window[ipmt] - 3000;
    (DC_Window[ipmt] == 1e+38) ? DCMax[ipmt] = +30000 : DCMax[ipmt] = DC_Window[ipmt] + 3000;
  }
  //Begin Plotting Results 
  /*
  TCanvas *cCER = new TCanvas("cCER","ADC Timing Window for HMS CER");
  cCER->Divide(2,1); 
  cCER->cd(1); HCERPULSETIMEDIFF[0]->Draw();
  cCER->cd(2); HCERPULSETIMEDIFF[1]->Draw();

  
  TCanvas *cPOSCAL = new TCanvas("cPOSCAL","ADC Timing Window for HMS Positive CAL");
  cPOSCAL->Divide(13,4);
  for (Int_t ipmt = 0; ipmt < 13; ipmt++) {
    cPOSCAL->cd(ipmt+1); H1prCALPOSPULSETIMEDIFF[ipmt]->Draw();
  }
  for (Int_t ipmt = 0; ipmt < 13; ipmt++) {
    cPOSCAL->cd(ipmt+14); H2taCALPOSPULSETIMEDIFF[ipmt]->Draw();
  }
  for (Int_t ipmt = 0; ipmt < 13; ipmt++) {
    cPOSCAL->cd(ipmt+27); H3taCALPOSPULSETIMEDIFF[ipmt]->Draw();
  }
  for (Int_t ipmt = 0; ipmt < 13; ipmt++) {
    cPOSCAL->cd(ipmt+40); H4taCALPOSPULSETIMEDIFF[ipmt]->Draw();
  }

  TCanvas *cNEGCAL = new TCanvas("cNEGCAL","ADC Timing Window for HMS Negative CAL");
  cNEGCAL->Divide(13,4);
  for (Int_t ipmt = 0; ipmt < 13; ipmt++) {
    cNEGCAL->cd(ipmt+1); H1prCALNEGPULSETIMEDIFF[ipmt]->Draw();
  }
  for (Int_t ipmt = 0; ipmt < 13; ipmt++) {
    cNEGCAL->cd(ipmt+14); H2taCALNEGPULSETIMEDIFF[ipmt]->Draw();
  }
  for (Int_t ipmt = 0; ipmt < 13; ipmt++) {
    cNEGCAL->cd(ipmt+27); H3taCALNEGPULSETIMEDIFF[ipmt]->Draw();
  }
  for (Int_t ipmt = 0; ipmt < 13; ipmt++) {
    cNEGCAL->cd(ipmt+40); H4taCALNEGPULSETIMEDIFF[ipmt]->Draw();
  }
  
  TCanvas *DC = new TCanvas("DC","ADC Timing Window for HMS DC");
  DC->Divide(2,6);
  for (Int_t ipmt = 0; ipmt < 6; ipmt++) {
    DC->cd(2*ipmt+1); HDCRAWTDC[2*ipmt]->Draw(); 
    DC->cd(2*ipmt+2); HDCRAWTDC[2*ipmt+1]->Draw(); 
  }
  
  TCanvas *HODONEG = new TCanvas("HODONEG","ADC Timing Window for HMS NEG HODO");
  HODONEG->Divide(4,16);
  for (Int_t ipmt = 0; ipmt < 16; ipmt++) {
    HODONEG->cd(4*ipmt+1); HHODO1xNEGPULSETIMEDIFF[ipmt]->Draw();
    HODONEG->cd(4*ipmt+2); HHODO1yNEGPULSETIMEDIFF[ipmt]->Draw();
    HODONEG->cd(4*ipmt+3); HHODO2xNEGPULSETIMEDIFF[ipmt]->Draw();
    HODONEG->cd(4*ipmt+4); HHODO2yNEGPULSETIMEDIFF[ipmt]->Draw();
  }

  TCanvas *HODOPOS = new TCanvas("HODOPOS","ADC Timing Window for HMS POS HODO");
  HODOPOS->Divide(4,16);
  for (Int_t ipmt = 0; ipmt < 16; ipmt++) {
    HODOPOS->cd(4*ipmt+1); HHODO1xPOSPULSETIMEDIFF[ipmt]->Draw();
    HODOPOS->cd(4*ipmt+2); HHODO1yPOSPULSETIMEDIFF[ipmt]->Draw();
    HODOPOS->cd(4*ipmt+3); HHODO2xPOSPULSETIMEDIFF[ipmt]->Draw();
    HODOPOS->cd(4*ipmt+4); HHODO2yPOSPULSETIMEDIFF[ipmt]->Draw();
  }
  */
  //Output Adc Time Window Values into an ascii file
  TString option = GetOption();
  ofstream HMSWindows;
  HMSWindows.open("HMSADCTimingWindows.dat", fstream::trunc);
  HMSWindows << Form(";Values obtained from Run %s",option.Data()) << endl;
  HMSWindows << Form("hcer_adcTimeWindowMin = %d, %d \nhcer_adcTimeWindowMax = %d, %d\n",CERMinPMT1,CERMinPMT2,CERMaxPMT1,CERMaxPMT2) << endl;
  
  HMSWindows << Form(";Values obtained from Run %s\nhhodo_PosAdcTimeWindowMin =",option.Data());
  for (Int_t ipmt = 0; ipmt < 16; ipmt++) {
    HMSWindows << Form(" %d, %d, %d, %d\n",HODOPosMin[4*ipmt],HODOPosMin[4*ipmt+1],HODOPosMin[4*ipmt+2],HODOPosMin[4*ipmt+3]);
  }
  HMSWindows << "\nhhodo_PosAdcTimeWindowMax =";
  for (Int_t ipmt = 0; ipmt < 16; ipmt++) {
    HMSWindows << Form(" %d, %d, %d, %d\n",HODOPosMax[4*ipmt],HODOPosMax[4*ipmt+1],HODOPosMax[4*ipmt+2],HODOPosMax[4*ipmt+3]);
  }
  HMSWindows << "\nhhodo_NegAdcTimeWindowMin =";
  for (Int_t ipmt = 0; ipmt < 16; ipmt++) {
    HMSWindows << Form(" %d, %d, %d, %d\n",HODONegMin[4*ipmt],HODONegMin[4*ipmt+1],HODONegMin[4*ipmt+2],HODONegMin[4*ipmt+3]);
  }
  HMSWindows << "\nhhodo_NegAdcTimeWindowMax =";
  for (Int_t ipmt = 0; ipmt < 16; ipmt++) {
    HMSWindows << Form(" %d, %d, %d, %d\n",HODONegMax[4*ipmt],HODONegMax[4*ipmt+1],HODONegMax[4*ipmt+2],HODONegMax[4*ipmt+3]);
  }
  
  HMSWindows << Form("\n;Values obtained from Run %s\nhcal_pos_AdcTimeWindowMin =  ",option.Data());
  for (Int_t iplane = 0; iplane < 4; iplane++) {
    HMSWindows << Form("%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d,\n",CALPosMin[13*iplane],CALPosMin[13*iplane+1],CALPosMin[13*iplane+2],CALPosMin[13*iplane+3],CALPosMin[13*iplane+4],CALPosMin[13*iplane+5],CALPosMin[13*iplane+6],CALPosMin[13*iplane+7],CALPosMin[13*iplane+8],CALPosMin[13*iplane+9],CALPosMin[13*iplane+10],CALPosMin[13*iplane+11],CALPosMin[13*iplane+12]);
  }
  HMSWindows << "hcal_neg_AdcTimeWindowMin =  ";
  for (Int_t iplane = 0; iplane < 4; iplane++) {
    HMSWindows << Form("%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d,\n",CALNegMin[13*iplane],CALNegMin[13*iplane+1],CALNegMin[13*iplane+2],CALNegMin[13*iplane+3],CALNegMin[13*iplane+4],CALNegMin[13*iplane+5],CALNegMin[13*iplane+6],CALNegMin[13*iplane+7],CALNegMin[13*iplane+8],CALNegMin[13*iplane+9],CALNegMin[13*iplane+10],CALNegMin[13*iplane+11],CALNegMin[13*iplane+12]);
  }
  HMSWindows << "hcal_pos_AdcTimeWindowMax =  ";
  for (Int_t iplane = 0; iplane < 4; iplane++) {
    HMSWindows << Form("%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d,\n",CALPosMax[13*iplane],CALPosMax[13*iplane+1],CALPosMax[13*iplane+2],CALPosMax[13*iplane+3],CALPosMax[13*iplane+4],CALPosMax[13*iplane+5],CALPosMax[13*iplane+6],CALPosMax[13*iplane+7],CALPosMax[13*iplane+8],CALPosMax[13*iplane+9],CALPosMax[13*iplane+10],CALPosMax[13*iplane+11],CALPosMax[13*iplane+12]);
  }
  HMSWindows << "hcal_neg_AdcTimeWindowMax =  ";
  for (Int_t iplane = 0; iplane < 4; iplane++) {
    HMSWindows << Form("%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d,\n",CALNegMax[13*iplane],CALNegMax[13*iplane+1],CALNegMax[13*iplane+2],CALNegMax[13*iplane+3],CALNegMax[13*iplane+4],CALNegMax[13*iplane+5],CALNegMax[13*iplane+6],CALNegMax[13*iplane+7],CALNegMax[13*iplane+8],CALNegMax[13*iplane+9],CALNegMax[13*iplane+10],CALNegMax[13*iplane+11],CALNegMax[13*iplane+12]);
  }
   
  HMSWindows << Form("\n;Values obtained from Run %s\nhtdc_win_min =  ",option.Data());
  for (Int_t iplane = 0; iplane < 2; iplane++) {
    HMSWindows << Form("%d, %d, %d, %d, %d, %d\n",DCMin[6*iplane],DCMin[6*iplane+1],DCMin[6*iplane+2],DCMin[6*iplane+3],DCMin[6*iplane+4],DCMin[6*iplane+5]);
  }
  HMSWindows << "htdc_win_max =  ";
  for (Int_t iplane = 0; iplane < 2; iplane++) {
    HMSWindows << Form("%d, %d, %d, %d, %d, %d\n",DCMax[6*iplane],DCMax[6*iplane+1],DCMax[6*iplane+2],DCMax[6*iplane+3],DCMax[6*iplane+4],DCMax[6*iplane+5]);
  }
  HMSWindows.close();
  
  //Start output of .root file with all histograms
  TFile *Histogram_file = new TFile(Form("../HISTOGRAMS/HMSADCGates_Run%i.root",option.Atoi()),"RECREATE");
  TDirectory *DCER = Histogram_file->mkdir("Gas Cherenkov ADC Timing Spectra"); DCER->cd();
  for (Int_t ipmt=0; ipmt < 2; ipmt++) {
    HCERPULSETIMEDIFF[ipmt]->Write(Form("CER PMT %i",ipmt+1));
    }
  
   TDirectory *DCAL = Histogram_file->mkdir("Shower ADC Timing Spectra"); DCAL->cd();
  for (Int_t ipmt=0; ipmt < 13; ipmt++) {
    H1prCALNEGPULSETIMEDIFF[ipmt]->Write(Form("1pr CAL NEG PMT %i",ipmt+1));
    H1prCALPOSPULSETIMEDIFF[ipmt]->Write(Form("1pr CAL POS PMT %i",ipmt+1));
    H2taCALNEGPULSETIMEDIFF[ipmt]->Write(Form("2ta CAL NEG PMT %i",ipmt+1));
    H2taCALPOSPULSETIMEDIFF[ipmt]->Write(Form("2ta CAL POS PMT %i",ipmt+1));
    //H3taCALNEGPULSETIMEDIFF[ipmt]->Write(Form("3ta CAL NEG PMT %i",ipmt+1));
    H3taCALPOSPULSETIMEDIFF[ipmt]->Write(Form("3ta CAL POS PMT %i",ipmt+1));
    //H4taCALNEGPULSETIMEDIFF[ipmt]->Write(Form("4ta CAL NEG PMT %i",ipmt+1));
    H4taCALPOSPULSETIMEDIFF[ipmt]->Write(Form("4ta CAL POS PMT %i",ipmt+1));
    }
  
  TDirectory *DHODO = Histogram_file->mkdir("Hodoscope ADC Timing Spectra"); DHODO->cd();
  for (Int_t ipmt=0; ipmt < 16; ipmt++) {
    HHODO1yNEGPULSETIMEDIFF[ipmt]->Write(Form("HODO 1y NEG PMT %i",ipmt+1));
    HHODO2yNEGPULSETIMEDIFF[ipmt]->Write(Form("HODO 2y NEG PMT %i",ipmt+1));
    HHODO1yPOSPULSETIMEDIFF[ipmt]->Write(Form("HODO 1y POS PMT %i",ipmt+1));
    HHODO2yPOSPULSETIMEDIFF[ipmt]->Write(Form("HODO 2y POS PMT %i",ipmt+1));
    HHODO1xNEGPULSETIMEDIFF[ipmt]->Write(Form("HODO 1x NEG PMT %i",ipmt+1));
    HHODO2xNEGPULSETIMEDIFF[ipmt]->Write(Form("HODO 2x NEG PMT %i",ipmt+1));
    HHODO1xPOSPULSETIMEDIFF[ipmt]->Write(Form("HODO 1x POS PMT %i",ipmt+1));
    HHODO2xPOSPULSETIMEDIFF[ipmt]->Write(Form("HODO 2x POS PMT %i",ipmt+1));
  }

  TDirectory *DDC = Histogram_file->mkdir("Drift Chamber ADC Timing Spectra"); DDC->cd();
  for (Int_t iplane = 0; iplane < 2; iplane++) {
    HDCRAWTDC[6*iplane]->Write(Form("DC %du1 Plane",iplane+1));
    HDCRAWTDC[6*iplane+1]->Write(Form("DC %dv1 Plane",iplane+1));
    HDCRAWTDC[6*iplane+2]->Write(Form("DC %dx1 Plane",iplane+1));
    HDCRAWTDC[6*iplane+3]->Write(Form("DC %du2 Plane",iplane+1));
    HDCRAWTDC[6*iplane+4]->Write(Form("DC %dv2 Plane",iplane+1));
    HDCRAWTDC[6*iplane+5]->Write(Form("DC %dx2 Plane",iplane+1));
  }
  
    Histogram_file->Close();
}                  
