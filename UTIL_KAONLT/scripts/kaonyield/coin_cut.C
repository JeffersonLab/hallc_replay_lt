#define coin_cut_cxx
#include "coin_cut.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLine.h>
#include <TMath.h>
#include <TPaveLabel.h>
#include <TProfile.h>
#include <TObjArray.h>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <math.h>
#include <iostream>
#include <fstream>
using namespace std;

void coin_cut::Loop(TString basename,Double_t threshold_cut, Int_t pscal)
{
///*
//   In a ROOT session, you can do:
//.L coin_cut.C+
//coin_cut t("whatever-the-root-file-name.root")
//t.Loop("1446",5.)

//      root> .L coin_cut.C+
//      root> coin_cut t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch

 gStyle->SetPalette(1,0);
 gStyle->SetOptStat(1);
 gStyle->SetOptFit(11);
 gStyle->SetTitleOffset(1.,"Y");
 gStyle->SetTitleOffset(.7,"X");
 gStyle->SetLabelSize(0.04,"XY");
 gStyle->SetTitleSize(0.06,"XY");
 gStyle->SetPadLeftMargin(0.12);
 TString htitle;
   TString outputhist;
   outputhist="hist/"+basename+"_hist.root";
   TObjArray HList(0);
     TString outputpdf;
    outputpdf="plots/"+basename+".pdf";
    Double_t nrun;
    nrun=basename.Atof();
  TH1F *trig[6]; 
  TH1F *trigcut[6];
  for (Int_t n=0;n<6;n++) {
    trig[n] =  new TH1F(Form("ptrig_%d",n+1),Form("Trig %d Time ",n+1),1000,0,1000);
    trigcut[n] =  new TH1F(Form("Htrigcut_%d",n+1),Form("Trig %d ( cut I> %5.2f; Time;Counts",n+1,threshold_cut),1000,0,1000);
  }
    TH1F *pedtm =  new TH1F("pedtm","EDTM; Time; counts",1000,0,1000);
    TH1F *pedtmcut =  new TH1F("pedtmcut",Form("EDTM (cut I> %5.2f; Time; counts",threshold_cut),1000,0,1000);
    
  //
     Int_t nscal_reads=0;
     Int_t nscal_reads_cut=0;
     Double_t prev_read=-1;
     Double_t ave_current=0;
     Double_t ave_current_cut=0;
     Double_t charge_sum=0;
     Double_t charge_sum_cut=0;
     Double_t prev_charge=0;
     Double_t event_flag[10000];
     Double_t scal_event_number[10000];
     Double_t tot_scal_TRIG1=0;
     Double_t prev_TRIG1=0;
     Double_t tot_scal_cut_TRIG1=0;
     Double_t tot_scal_EDTM=0;
     Double_t prev_EDTM=0;
     Double_t tot_scal_cut_EDTM=0;
     Double_t tot_scal_cut_time=0;
     Double_t tot_scal_time=0;
     Double_t prev_time=0;
     Double_t prescal[17] = {1,2,3,5,9,17,33,65,129,257,513,1025,2049,4097,8193,16385,32769};
   //
   if (fChain == 0) return;


   Long64_t nentries = fScalTree->GetEntriesFast();
   Long64_t dentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadScalTree(jentry);
      if (ientry < 0) break;
      nb = fScalTree->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
          event_flag[nscal_reads] = 0;
             scal_event_number[nscal_reads] = Scal_evNumber;
          ave_current+=Scal_BCM4B_current;
	  if (Scal_BCM4B_current > threshold_cut) {
             event_flag[nscal_reads] = 1;
             ave_current_cut+=Scal_BCM4B_current;
 	     tot_scal_cut_time+=(Scal_time-prev_time);
 	     tot_scal_cut_TRIG1+=(Scal_TRIG1-prev_TRIG1);
	     tot_scal_cut_EDTM+=(Scal_EDTM-prev_EDTM);
             charge_sum_cut+=(Scal_BCM4B_charge-prev_charge);
             nscal_reads_cut++;
	  }
	  prev_charge = Scal_BCM4B_charge;
	  prev_time = Scal_time;
	  prev_TRIG1 = Scal_TRIG1;
	  prev_EDTM = Scal_EDTM;
	  //	  cout <<  nscal_reads <<  " " << Scal_BCM4B_current << " " << event_flag[nscal_reads] << " " << scal_event_number[nscal_reads] << endl;
          nscal_reads++;
          charge_sum=Scal_BCM4B_charge;
	  tot_scal_TRIG1=Scal_TRIG1;
	  tot_scal_EDTM=Scal_EDTM;
          tot_scal_time=Scal_time;

   }
// Loop again and do BCm cut
   scal_event_number[nscal_reads-1]= dentries;
   cout << " Finish scaler loop " << nentries << " " << nscal_reads << endl;
   cout << " start data loop entries = " << dentries << endl;
   Int_t nscal_reads_2=0;
   prev_read=-1;
   //   nentries = fChain->GetEntriesFast();
   for (Long64_t jentry=0; jentry<dentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if (jentry%50000==0) cout << " entry = " << jentry << endl;
      if (T_coin_pTRIG1_ROC2_tdcTime!=0) trig[0]->Fill(T_coin_pTRIG1_ROC2_tdcTime);
      pedtm->Fill(T_coin_pEDTM_tdcTime);
      if (event_flag[nscal_reads_2]==1) {
         if (T_coin_pTRIG1_ROC2_tdcTime!=0) trigcut[0]->Fill(T_coin_pTRIG1_ROC2_tdcTime);
         pedtmcut->Fill(T_coin_pEDTM_tdcTime);
      }
      if (fEvtHdr_fEvtNum>scal_event_number[nscal_reads_2]) {
          nscal_reads_2++;
       }
   }
  cout << " number of scaler reads = " << nscal_reads<< " " << nscal_reads_2 << endl;
   cout << " average current (no cut) = " << ave_current/(nscal_reads) <<endl;
   cout << " total charge (no cut) = " << charge_sum/1000 << " mC"  <<endl;
   cout << " Threshold = " << threshold_cut << " uA" << endl;
   cout << " number of scaler reads (cut)= " << nscal_reads_cut << endl;
   cout << " total charge (cut) = " << charge_sum_cut/1000 << " mC"  <<endl;
   cout << " average current (cut) = " << ave_current_cut/(nscal_reads_cut) <<endl;

   //cout << "\n Integral scal EDTM no cut = " << tot_scal_EDTM << endl;
   //cout << " Integral scal EDTM cut = " << tot_scal_cut_EDTM << endl;
   cout << " Integral Data EDTM no cut = " << pedtm->Integral() << endl;
   cout << " ~~~~~Integral Data EDTM cut = " << pedtmcut->Integral(0,1) << endl;

   Double_t edtm_lt= (100-pedtmcut->Integral()/(tot_scal_cut_EDTM*prescal[pscal]))/100;

   cout << "\n EDTM Lifetime = " << edtm_lt << endl;

   //cout << "\n Integral scal TRIG1 no cut = " << tot_scal_TRIG1 << endl;
   //cout << " Integral scal TRIG1 cut = " << tot_scal_cut_TRIG1 << endl;
   //cout << " Integral TRIG1 no cut = " << trig[0]->Integral() << endl;
   //cout << " ~~~Integral TRIG1 cut = " << trig[0]->Integral(0,1) << endl;

   Double_t cpult= (100 - trigcut[0]->Integral()/tot_scal_cut_TRIG1)/100;

   cout << "\n Computer Lifetime = " << cpult << endl;

//*/
// values for controlling format
    const string sep = "	" ;
    const int total_width = 154;
    const string line = sep + string( total_width-1, '-' ) + '|' ;


ofstream myfile1;
  myfile1.open ("kaonyieldVar", fstream::app);
  myfile1 <<
left << nrun << sep << left << charge_sum_cut/1000 << sep << left <<  ave_current_cut/(nscal_reads_cut) << sep;
  myfile1.close();

ofstream myfile2;
  myfile2.open ("efficiencies", fstream::app);	
  myfile2 << 
left << nrun << sep << left << edtm_lt << sep << left << cpult << "\n";
  myfile2.close();

}
