//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jul 31 11:48:46 2018 by ROOT version 6.14/00
// from TTree T/Hall A Analyzer Output DST
// found on file: ../ROOTfiles/coin_replay_production_3420_10000.root
//////////////////////////////////////////////////////////

#ifndef coin_cut_h
#define coin_cut_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>



// Header file for the classes stored in the TTree if any.


class coin_cut{
 public :
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  TTree          *fScalTree;   //!pointer to the analyzed TTree or TChain
  Int_t           fCurrent; //!current Tree number in a TChain
  Int_t           fCurrentScal; //!current Tree number in a TChain

  Double_t        Scal_BCM4B_current;
  Double_t        Scal_BCM4B_charge;
  Double_t        Scal_evNumber;
  Double_t        Scal_TRIG1;
  Double_t        Scal_EDTM;
  Double_t        Scal_cut_TRIG1;
  Double_t        Scal_cut_EDTM;
  Double_t        Scal_time;
  Double_t        T_coin_pTRIG1_ROC2_tdcTime;
  Double_t        T_coin_pEDTM_tdcTime;
  TBranch        *b_Scal_time;
  TBranch        *b_Scal_cut_TRIG1;
  TBranch        *b_Scal_cut_EDTM;
  TBranch        *b_Scal_TRIG1;
  TBranch        *b_Scal_EDTM;
  TBranch        *b_Scal_BCM4B_current;
  TBranch        *b_Scal_BCM4B_charge;
  TBranch        *b_Scal_evNumber;
  TBranch        *b_T_coin_pTRIG1_ROC2_tdcTime;   //!
  TBranch        *b_T_coin_pEDTM_tdcTime;   //!
  //THaEvent        *Event_Branch;
   ULong64_t       fEvtHdr_fEvtTime;
   UInt_t          fEvtHdr_fEvtNum;
   Int_t           fEvtHdr_fEvtType;
   Int_t           fEvtHdr_fEvtLen;
   Int_t           fEvtHdr_fHelicity;
   Int_t           fEvtHdr_fTargetPol;
   Int_t           fEvtHdr_fRun;

  coin_cut(TString ifile,TTree *tree=0);
  virtual ~coin_cut();
  virtual Int_t    Cut(Long64_t entry);
  virtual Int_t   GetEntry(Long64_t entry);
  virtual Int_t   GetScalEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual Long64_t LoadScalTree(Long64_t entry);
  virtual void    Init(TTree *tree);
  virtual void    InitScal(TTree *tree);
  virtual void    Loop(TString basename,Double_t threshold_cut, Int_t pscal);
  virtual Bool_t  Notify();
  virtual void    Show(Long64_t entry = -1);
};

#endif

#ifdef coin_cut_cxx

coin_cut::coin_cut(TString ifile,TTree *tree) : fChain(0)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
      TTree *stree=0;
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(ifile);
      if (!f || !f->IsOpen()) {
         f = new TFile(ifile);
      }
      f->GetObject("T",tree);
      f->GetObject("TSH",stree);

   }
   Init(tree);
   InitScal(stree);
}

coin_cut::~coin_cut()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t coin_cut::GetEntry(Long64_t entry) 
{ 
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}

Int_t coin_cut::GetScalEntry(Long64_t entry)
{ 
// Read contents of entry.
   if (!fScalTree) return 0; 
   return fScalTree->GetEntry(entry); 
}

Long64_t coin_cut::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

Long64_t coin_cut::LoadScalTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fScalTree) return -5;
   Long64_t centry = fScalTree->LoadTree(entry);
   if (centry < 0) return centry;
   if (fScalTree->GetTreeNumber() != fCurrentScal) {
      fCurrentScal = fScalTree->GetTreeNumber();
      Notify();
   }
   return centry;
}

void coin_cut::InitScal(TTree *tree)
{
   if (!tree) return;
   fCurrentScal=-1;
   fScalTree=tree;
   fScalTree->SetMakeClass(1);
   fScalTree->SetBranchAddress("H.BCM4B.scalerCurrent",&Scal_BCM4B_current,&b_Scal_BCM4B_current);
   fScalTree->SetBranchAddress("H.BCM4B.scalerCharge",&Scal_BCM4B_charge,&b_Scal_BCM4B_charge);
   fScalTree->SetBranchAddress("evNumber",&Scal_evNumber,&b_Scal_evNumber);
   fScalTree->SetBranchAddress("H.1Mhz.scalerTime",&Scal_time,&b_Scal_time);
   fScalTree->SetBranchAddress("H.hTRIG1.scaler",&Scal_TRIG1,&b_Scal_TRIG1);
   fScalTree->SetBranchAddress("H.EDTM.scaler",&Scal_EDTM,&b_Scal_EDTM);
   fScalTree->SetBranchAddress("H.hTRIG1.scalerCut",&Scal_cut_TRIG1,&b_Scal_cut_TRIG1);
   fScalTree->SetBranchAddress("H.EDTM.scalerCut",&Scal_cut_EDTM,&b_Scal_cut_EDTM);
}

void coin_cut::Init(TTree *tree)
{
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);
   fChain->SetBranchAddress("T.coin.pTRIG1_ROC2_tdcTime", &T_coin_pTRIG1_ROC2_tdcTime, &b_T_coin_pTRIG1_ROC2_tdcTime);
   fChain->SetBranchAddress("T.coin.pEDTM_tdcTime", &T_coin_pEDTM_tdcTime, &b_T_coin_pEDTM_tdcTime);
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the reader is initialized.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).

}

Bool_t coin_cut::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.

  return kTRUE;
}

void coin_cut::Show(Long64_t entry)
{ 
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return; 
   fChain->Show(entry); 
}

Int_t coin_cut::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}

#endif // #ifdef coin_cut_cxx
