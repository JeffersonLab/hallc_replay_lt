#ifndef DC_Calib_Check_HMS_h
#define DC_Calib_Check_HMS_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>
#include <TMath.h>
#include <TProfile2D.h>
#include <TH3.h>
#include <TH2.h>
#include <TF1.h>
#include <TArc.h>

// Headers needed by this particular selector

class DC_Calib_Check_HMS : public TSelector {
 public :
  TTreeReader     fReader;  //!the tree reader
  TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

  //Declare Histograms
  // Could do these as arrays of histos but there's only 12 so won't bother, also more annoying in terms of how they're filled
  TH1F           *h1_1u1_DriftDistance;
  TH1F           *h1_1u2_DriftDistance;
  TH1F           *h1_1x1_DriftDistance;
  TH1F           *h1_1x2_DriftDistance;
  TH1F           *h1_1v1_DriftDistance;
  TH1F           *h1_1v2_DriftDistance;
  TH1F           *h1_2u1_DriftDistance;
  TH1F           *h1_2u2_DriftDistance;
  TH1F           *h1_2x1_DriftDistance;
  TH1F           *h1_2x2_DriftDistance;
  TH1F           *h1_2v1_DriftDistance;
  TH1F           *h1_2v2_DriftDistance;

  // Residual is the distance betwen the final track position and the hit location obtained from an individual plane
  TH1F           **h1_Residual;
  // Residual "unbiased" by the plane you're looking at, need to find a better description somewhere...
  TH1F           **h1_ResidualExclPlane;

  // Readers to access the data (delete the ones you do not need).
  TTreeReaderArray<Double_t> H_dc_1u1_time      = {fReader, "H.dc.1u1.time"};
  TTreeReaderArray<Double_t> H_dc_1u2_time      = {fReader, "H.dc.1u2.time"};
  TTreeReaderArray<Double_t> H_dc_1v1_time      = {fReader, "H.dc.1v1.time"};
  TTreeReaderArray<Double_t> H_dc_1v2_time      = {fReader, "H.dc.1v2.time"};
  TTreeReaderArray<Double_t> H_dc_1x1_time      = {fReader, "H.dc.1x1.time"};
  TTreeReaderArray<Double_t> H_dc_1x2_time      = {fReader, "H.dc.1x2.time"};
  TTreeReaderArray<Double_t> H_dc_2u1_time      = {fReader, "H.dc.2u1.time"};
  TTreeReaderArray<Double_t> H_dc_2u2_time      = {fReader, "H.dc.2u2.time"};
  TTreeReaderArray<Double_t> H_dc_2v1_time      = {fReader, "H.dc.2v1.time"};
  TTreeReaderArray<Double_t> H_dc_2v2_time      = {fReader, "H.dc.2v2.time"};
  TTreeReaderArray<Double_t> H_dc_2x1_time      = {fReader, "H.dc.2x1.time"};
  TTreeReaderArray<Double_t> H_dc_2x2_time      = {fReader, "H.dc.2x2.time"};
 
  TTreeReaderArray<Double_t> H_dc_1u1_dist      = {fReader, "H.dc.1u1.dist"};
  TTreeReaderArray<Double_t> H_dc_1u2_dist      = {fReader, "H.dc.1u2.dist"};
  TTreeReaderArray<Double_t> H_dc_1v1_dist      = {fReader, "H.dc.1v1.dist"};
  TTreeReaderArray<Double_t> H_dc_1v2_dist      = {fReader, "H.dc.1v2.dist"};
  TTreeReaderArray<Double_t> H_dc_1x1_dist      = {fReader, "H.dc.1x1.dist"};
  TTreeReaderArray<Double_t> H_dc_1x2_dist      = {fReader, "H.dc.1x2.dist"};
  TTreeReaderArray<Double_t> H_dc_2u1_dist      = {fReader, "H.dc.2u1.dist"};
  TTreeReaderArray<Double_t> H_dc_2u2_dist      = {fReader, "H.dc.2u2.dist"};
  TTreeReaderArray<Double_t> H_dc_2v1_dist      = {fReader, "H.dc.2v1.dist"};
  TTreeReaderArray<Double_t> H_dc_2v2_dist      = {fReader, "H.dc.2v2.dist"};
  TTreeReaderArray<Double_t> H_dc_2x1_dist      = {fReader, "H.dc.2x1.dist"};
  TTreeReaderArray<Double_t> H_dc_2x2_dist      = {fReader, "H.dc.2x2.dist"};

  TTreeReaderArray<Double_t> H_dc_1u1_wirenum   = {fReader, "H.dc.1u1.wirenum"};
  TTreeReaderArray<Double_t> H_dc_1u2_wirenum   = {fReader, "H.dc.1u2.wirenum"};
  TTreeReaderArray<Double_t> H_dc_1v1_wirenum   = {fReader, "H.dc.1v1.wirenum"};
  TTreeReaderArray<Double_t> H_dc_1v2_wirenum   = {fReader, "H.dc.1v2.wirenum"};
  TTreeReaderArray<Double_t> H_dc_1x1_wirenum   = {fReader, "H.dc.1x1.wirenum"};
  TTreeReaderArray<Double_t> H_dc_1x2_wirenum   = {fReader, "H.dc.1x2.wirenum"};
  TTreeReaderArray<Double_t> H_dc_2u1_wirenum   = {fReader, "H.dc.2u1.wirenum"};
  TTreeReaderArray<Double_t> H_dc_2u2_wirenum   = {fReader, "H.dc.2u2.wirenum"};
  TTreeReaderArray<Double_t> H_dc_2v1_wirenum   = {fReader, "H.dc.2v1.wirenum"};
  TTreeReaderArray<Double_t> H_dc_2v2_wirenum   = {fReader, "H.dc.2v2.wirenum"};
  TTreeReaderArray<Double_t> H_dc_2x1_wirenum   = {fReader, "H.dc.2x1.wirenum"};
  TTreeReaderArray<Double_t> H_dc_2x2_wirenum   = {fReader, "H.dc.2x2.wirenum"};

  TTreeReaderArray<Double_t> H_dc_residual      = {fReader, "H.dc.residual"};
  TTreeReaderArray<Double_t> H_dc_residualExclPlane  = {fReader, "H.dc.residualExclPlane"};

  TTreeReaderArray<Double_t> H_cer_npeSum       = {fReader, "H.cer.npeSum"};

  DC_Calib_Check_HMS(TTree * /*tree*/ =0) {h1_1u1_DriftDistance = 0, h1_1u2_DriftDistance = 0, h1_1v1_DriftDistance = 0, h1_1v2_DriftDistance = 0, h1_1x1_DriftDistance = 0, h1_1x2_DriftDistance = 0, h1_2u1_DriftDistance = 0, h1_2u2_DriftDistance = 0, h1_2v1_DriftDistance = 0, h1_2v2_DriftDistance = 0, h1_2x1_DriftDistance = 0, h1_2x2_DriftDistance = 0;}
  virtual ~DC_Calib_Check_HMS() { }
  virtual Int_t   Version() const { return 2; }
  virtual void    Begin(TTree *tree);
  virtual void    SlaveBegin(TTree *tree);
  virtual void    Init(TTree *tree);
  virtual Bool_t  Notify();
  virtual Bool_t  Process(Long64_t entry);
  virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
  virtual void    SetOption(const char *option) { fOption = option; }
  virtual void    SetObject(TObject *obj) { fObject = obj; }
  virtual void    SetInputList(TList *input) { fInput = input; }
  virtual TList  *GetOutputList() const { return fOutput; }
  virtual void    SlaveTerminate();
  virtual void    Terminate();

  ClassDef(DC_Calib_Check_HMS,0);
};

#endif

#ifdef DC_Calib_Check_HMS_cxx
void DC_Calib_Check_HMS::Init(TTree *tree)
{
  fReader.SetTree(tree);
}

Bool_t DC_Calib_Check_HMS::Notify()
{
  return kTRUE;
}

#endif // #ifdef DC_Calib_Check_cxx
