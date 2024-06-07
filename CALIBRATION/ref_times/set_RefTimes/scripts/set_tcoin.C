void plot_tcoin_trigs(TString ptrig=""){

  /*
    Description: This script takes as input a histogram object name,
    and reads that histogram from pre-defined ROOTfiles the user chooses.
    These histograms from the different files are then overlayed for a
    direct comparison. The histograms MUST have the same dimensions (bins, range)

   */
  
  gROOT->ForceStyle();
  gStyle->SetOptStat(0);

  
  //black(11799)    --> ps1=9,  ps2=-1, ps3=4,  ps4=-1, ps5=-1, ps6=-1
  //blue(11829)     --> ps1=1,  ps2=-1, ps3=-1, ps4=0,  ps5=0,  ps6=-1
  //green(11847)    --> ps1=2,  ps2=-1, ps3=-1, ps4=0,  ps5=0,  ps6=-1
  //magenta (11883) --> ps1=12, ps2=-1, ps3=-1, ps4=11, ps5=0,  ps6=-1
  //red (11947)     --> ps1=13, ps2=-1, ps3=-1, ps4=10, ps5=0,  ps6=-1
  //------ Additional Kinematics -------

  // 11978  --> ps1=13,ps2=-1,ps3=-1,ps4=9,ps5=0,ps6=-1
  // 12000  --> ps1=13,ps2=-1,ps3=-1,ps4=9,ps5=0,ps6=-1
  // 12050  --> ps1=14,ps2=-1,ps3=-1,ps4=9,ps5=0,ps6=-1

  
  TString s1 = "./ROOTfiles/Pion_coin_replay_tcoin_cyero_11799_100000.root";
  TString s2 = "./ROOTfiles/Pion_coin_replay_tcoin_cyero_11829_100000.root";
  TString s3 = "./ROOTfiles/Pion_coin_replay_tcoin_cyero_11847_100000.root";
  TString s4 = "./ROOTfiles/Pion_coin_replay_tcoin_cyero_11883_100000.root";
  TString s5 = "./ROOTfiles/Pion_coin_replay_tcoin_cyero_11947_100000.root";

  TString s6 = "./ROOTfiles/Pion_coin_replay_tcoin_cyero_11978_100000.root";
  TString s7 = "./ROOTfiles/Pion_coin_replay_tcoin_cyero_12000_100000.root";
  TString s8 = "./ROOTfiles/Pion_coin_replay_tcoin_cyero_12050_100000.root";

  TFile *f1 = new TFile(s1.Data(), "READ");
  TFile *f2 = new TFile(s2.Data(), "READ");
  TFile *f3 = new TFile(s3.Data(), "READ");
  TFile *f4 = new TFile(s4.Data(), "READ");
  TFile *f5 = new TFile(s5.Data(), "READ");

  TFile *f6 = new TFile(s6.Data(), "READ");
  TFile *f7 = new TFile(s7.Data(), "READ");
  TFile *f8 = new TFile(s8.Data(), "READ");

  
  
  TTree *T1 = (TTree*)f1->Get("T");
  TTree *T2 = (TTree*)f2->Get("T");
  TTree *T3 = (TTree*)f3->Get("T");
  TTree *T4 = (TTree*)f4->Get("T");
  TTree *T5 = (TTree*)f5->Get("T");

  TTree *T6 = (TTree*)f6->Get("T");
  TTree *T7 = (TTree*)f7->Get("T");
  TTree *T8 = (TTree*)f8->Get("T");

    
  TCanvas *c1 = new TCanvas();
  c1->cd();
  c1->SetLogy();

  T1->Draw(Form("T.coin.%s_ROC2_tdcTimeRaw>>h1", ptrig.Data()), Form("T.coin.%s_ROC2_tdcMultiplicity==1", ptrig.Data()));
  T2->Draw(Form("T.coin.%s_ROC2_tdcTimeRaw>>h2", ptrig.Data()), Form("T.coin.%s_ROC2_tdcMultiplicity==1", ptrig.Data()), "sames");
  T3->Draw(Form("T.coin.%s_ROC2_tdcTimeRaw>>h3", ptrig.Data()), Form("T.coin.%s_ROC2_tdcMultiplicity==1", ptrig.Data()), "sames");
  T4->Draw(Form("T.coin.%s_ROC2_tdcTimeRaw>>h4", ptrig.Data()), Form("T.coin.%s_ROC2_tdcMultiplicity==1", ptrig.Data()), "sames");
  T5->Draw(Form("T.coin.%s_ROC2_tdcTimeRaw>>h5", ptrig.Data()), Form("T.coin.%s_ROC2_tdcMultiplicity==1", ptrig.Data()), "sames");

  T6->Draw(Form("T.coin.%s_ROC2_tdcTimeRaw>>h6", ptrig.Data()), Form("T.coin.%s_ROC2_tdcMultiplicity==1", ptrig.Data()), "sames");
  T7->Draw(Form("T.coin.%s_ROC2_tdcTimeRaw>>h7", ptrig.Data()), Form("T.coin.%s_ROC2_tdcMultiplicity==1", ptrig.Data()), "sames");
  T8->Draw(Form("T.coin.%s_ROC2_tdcTimeRaw>>h8", ptrig.Data()), Form("T.coin.%s_ROC2_tdcMultiplicity==1", ptrig.Data()), "sames");

  
  //Get Histo Objects
  TH1F *h1 = (TH1F*)gDirectory->Get("h1");
  TH1F *h2 = (TH1F*)gDirectory->Get("h2");
  TH1F *h3 = (TH1F*)gDirectory->Get("h3");
  TH1F *h4 = (TH1F*)gDirectory->Get("h4");
  TH1F *h5 = (TH1F*)gDirectory->Get("h5");

  TH1F *h6 = (TH1F*)gDirectory->Get("h6");
  TH1F *h7 = (TH1F*)gDirectory->Get("h7");
  TH1F *h8 = (TH1F*)gDirectory->Get("h8");


  h1->SetLineColor(kBlack);
  h1->GetYaxis()->SetRangeUser(0.001,1e5);
  h1->SetFillStyle(3004);
  h1->SetLineWidth(3);
  h1->SetFillColorAlpha(kBlack, 0.4);
  h1->Draw();

  h2->SetLineColor(kBlue);
  h2->SetFillStyle(3005);
  h2->SetLineWidth(3);
  h2->SetFillColorAlpha(kBlue, 0.4);
  h2->Draw("same");

  h3->SetLineColor(kGreen);
  h3->SetFillStyle(3004);
  h3->SetLineWidth(3);
  h3->SetFillColorAlpha(kGreen, 0.4);
  h3->Draw("same");

  h4->SetLineColor(kMagenta);
  h4->SetFillStyle(3005);
  h4->SetLineWidth(3);
  h4->SetFillColorAlpha(kMagenta, 0.4);
  h4->Draw("same");

  h5->SetLineColor(kRed);
  h5->SetFillStyle(3004);
  h5->SetLineWidth(3);
  h5->SetFillColorAlpha(kRed, 0.4);
  h5->Draw("same");

  //----- NEW RUNS ----
  h6->SetLineColor(kCyan);
  h6->SetFillStyle(3004);
  h6->SetLineWidth(3);
  h6->SetFillColorAlpha(kCyan, 0.4);
  h6->Draw("same");
  
  h7->SetLineColor(kViolet);
  h7->SetFillStyle(3004);
  h7->SetLineWidth(3);
  h7->SetFillColorAlpha(kViolet, 0.4);
  h7->Draw("same");

  h8->SetLineColor(kOrange);
  h8->SetFillStyle(3004);
  h8->SetLineWidth(3);
  h8->SetFillColorAlpha(kOrange, 0.4);
  h8->Draw("same");
  
}

void set_tcoin(){
  
  plot_tcoin_trigs("pTRIG1");
  plot_tcoin_trigs("pTRIG2");
  plot_tcoin_trigs("pTRIG3");
  plot_tcoin_trigs("pTRIG4");
  plot_tcoin_trigs("pTRIG5");
  plot_tcoin_trigs("pTRIG6");
  

}
