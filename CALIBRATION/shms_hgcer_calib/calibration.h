// Vijay Kumar, Univerity of Regina - 24/07/20
// vijay36361@gmail.com

#ifndef calibration_h
#define calibration_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>
#include <TH1.h>
#include <TH2.h>
#include <TNtuple.h>

const Int_t        fhgc_pmts = 4;
const Double_t     fhgc_zpos = 156.27;

class calibration : public TSelector {
 public :
  TTreeReader    fReader;
  TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain
  Bool_t          fFullRead;
  Bool_t          fFullShow;
  Bool_t          fTrack;
  Bool_t          fCut;
  Bool_t          fPions;
  Bool_t          frun;

  // Declaration of histograms
  TH1F          **fPulseInt;
  TH1F          **fPulseInt_poiss;
  TH1F         ***fPulseInt_quad;
  TH1F           *fBeta_Cut;
  TH1F           *fBeta_Full;
  TH2F           *fXatYat;
  TH2F           *fXeqYeq;
  TH1F           *fTiming_Full;
  TH1F            *fTim1;
  TH1F            *fTim2;
  TH1F            *fTim3;
  TH1F            *fTim4;
  TH1F            *fTim1_full;  
  TH1F            *fTim2_full;  
  TH1F            *fTim3_full;  
  TH1F            *fTim4_full;  
  
  // Declaration of histograms used in fitting/analysis
  TH1F *scaled_clone;
  TH1F *fscaled[4];
  TH1F *fscaled_nobackground[4];
  TH1F *fscaled_mk2[4];
  TH1F *fscaled_mk2_nobackground[4];
  TH1F *fscaled_temp[4];
  TH1F *fscaled_combined[4];
  TH1F *fscaled_total;
  TH1F *fscaled_temp_mk2[4];
  TH1F *fscaled_combined_mk2[4];
  TH1F *fscaled_total_mk2;
   
  // Declaration of canvases used in fitting/analysis
  TCanvas *t;
  TCanvas *quad_cuts_ipmt;
  TCanvas *quad_cuts[4];
  TCanvas *low_stats_ipmt;
  TCanvas *background_ipmt;
  TCanvas *Full_zoom_fit_ipmt;
  TCanvas *final_spectra_ipmt;
  TCanvas *background_mk2_ipmt;
  TCanvas *final_spectra_mk2_ipmt;
  TCanvas *final_spectra_combined;
  TCanvas *final_spectra_combined_mk2;
  TCanvas *scaled_poisson;
  TCanvas *scaled_total;  
 
  // Declaration of preprocessing quantities
  Double_t  timing_mean[4];
  Double_t  timing_std[4];
  Double_t x;

  // Readers to access the data
  // These leaves MUST all be present in your replay file for this scrip to run!
  //  TTreeReaderValue<Int_t>    Ndata_P_tr_beta            = {fReader, "Ndata.P.tr.beta"};
  TTreeReaderArray<Double_t> P_gtr_beta                  = {fReader, "P.gtr.beta"};
  TTreeReaderArray<Double_t> P_hgcer_goodAdcTdcDiffTime = {fReader, "P.hgcer.goodAdcTdcDiffTime"};
  TTreeReaderArray<Double_t> P_hgcer_goodAdcPulseInt    = {fReader, "P.hgcer.goodAdcPulseInt"};
  TTreeReaderArray<Double_t> P_hgcer_goodAdcPulseAmp    = {fReader, "P.hgcer.goodAdcPulseAmp"};
  TTreeReaderArray<Double_t> P_hgcer_numTracksFired     = {fReader, "P.hgcer.numTracksFired"};
  TTreeReaderValue<Double_t> P_cal_fly_earray           = {fReader, "P.cal.fly.earray"};
  TTreeReaderValue<Double_t> P_cal_pr_eplane            = {fReader, "P.cal.pr.eplane"};
  TTreeReaderValue<Double_t> P_cal_etotnorm             = {fReader, "P.cal.etotnorm"};
  TTreeReaderValue<Double_t> P_gtr_p                    = {fReader, "P.gtr.p"};
  TTreeReaderArray<Double_t> P_gtr_dp                   = {fReader, "P.gtr.dp"};
  TTreeReaderArray<Double_t> P_gtr_x                     = {fReader, "P.gtr.x"};
  TTreeReaderArray<Double_t> P_gtr_ph                    = {fReader, "P.gtr.ph"};
  TTreeReaderArray<Double_t> P_gtr_y                     = {fReader, "P.gtr.y"};
  TTreeReaderArray<Double_t> P_gtr_th                    = {fReader, "P.gtr.th"};
  TTreeReaderArray<Double_t> P_dc_x_fp                     = {fReader, "P.dc.x_fp"};
  TTreeReaderArray<Double_t> P_dc_xp_fp                     = {fReader, "P.dc.xp_fp"};
  TTreeReaderArray<Double_t> P_dc_y_fp                     = {fReader, "P.dc.y_fp"};
  TTreeReaderArray<Double_t> P_dc_yp_fp                     = {fReader, "P.dc.yp_fp"};
  TTreeReaderArray<Double_t> P_hgcer_xAtCer             = {fReader, "P.hgcer.xAtCer"};
  TTreeReaderArray<Double_t> P_hgcer_yAtCer             = {fReader, "P.hgcer.yAtCer"};
  
 calibration(TTree * /*tree*/ =0) : fChain(0) {fPulseInt = 0, fPulseInt_poiss = 0, fPulseInt_quad = 0, fBeta_Cut = 0, fBeta_Full = 0, fXatYat = 0, fXeqYeq = 0, fTiming_Full = 0,fTim1 =0, fTim1_full = 0,fTim2 =0, fTim2_full = 0, fTim3 = 0, fTim3_full = 0, fTim4 = 0, fTim4_full = 0, fFullRead = kFALSE, fFullShow = kFALSE, fTrack = kFALSE, fCut = kFALSE, fPions = kFALSE;}
  virtual ~calibration() { }
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

  ClassDef(calibration,0);
};

#endif

#ifdef calibration_cxx
void calibration::Init(TTree *tree)
{
  fReader.SetTree(tree);  
}

Bool_t calibration::Notify()
{
  return kTRUE;
}

//Poisson distribution is used to remove background from larger values of NPE
Double_t poisson(Double_t *x, Double_t *par)
{
  Double_t PoissFit1 = (par[1]*pow(par[0],x[0])*exp(-par[0]))/(tgamma(x[0]+1));                 
  return PoissFit1;
}

//Gaussian distribution is used to find the mean of the SPE and determine spacing between subsequent NPE
Double_t gauss(Double_t *x, Double_t *par)
{
  Double_t GaussFit1 = par[0]*exp((-0.5)*(pow((x[0] - par[1]),2)/pow((par[2]),2)));
  Double_t GaussFit2 = par[3]*exp((-0.5)*(pow((x[0] - par[4]),2)/pow((par[5]),2)));
  return GaussFit1 + GaussFit2;
}
 
// Function used for quality contron of the calibration
Double_t fun_4gauss_2poisson(Double_t *x, Double_t *par)
{
  Double_t GaussFit1 = par[0]*exp((-0.5)*(pow((x[0] - par[1]),2)/pow((par[2]),2)));
  Double_t GaussFit2 = par[3]*exp((-0.5)*(pow((x[0] - par[4]),2)/pow((par[5]),2)));
  Double_t GaussFit3 = par[6]*exp((-0.5)*(pow((x[0] - par[7]),2)/pow((par[8]),2)));
  Double_t GaussFit4 = par[9]*exp((-0.5)*(pow((x[0] - par[10]),2)/pow((par[11]),2)));
  Double_t PoissFit1 = (par[13]*pow(par[12],x[0])*exp(-par[12]))/(tgamma(x[0]+1)); 
  Double_t PoissFit2 = (par[15]*pow(par[14],x[0])*exp(-par[14]))/(tgamma(x[0]+1)); 
  return GaussFit1 + GaussFit2 + GaussFit3 + GaussFit4 + PoissFit1 + PoissFit2;
}

//A simple linear equation is used to determine how linear the means of the NPE are
Double_t linear(Double_t *x, Double_t *par)
{
  Double_t LinFit1 = par[0]*x[0] + par[1];
  return LinFit1;
}

#endif // #ifdef calibration_cxx
