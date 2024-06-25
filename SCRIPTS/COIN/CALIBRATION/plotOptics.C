void plotOptics(int nrun){

  //read the input file
  TFile *f = new TFile(Form("/home/cdaq/pionLT-2021/hallc_replay_lt_2022_Run/ROOTfiles/Analysis/50k/hms_coin_replay_production_%i_100000.root",nrun));
  //TFile *f = new TFile(Form("/volatile/hallc/comm2017/holly/ROOTfiles/hms_c_q8.root"));
  TTree *tt = (TTree*)f->Get("T");

  //here's the cut
  //TCut cut = "H.gtr.dp<9&&H.gtr.dp>-9&&H.cal.etracknorm>0.8&&H.cer.npe>2";
  TCut cut = "H.gtr.dp<9&&H.gtr.dp>-9&&H.cer.npe>2";
  TCut cutCentral = "abs(H.gtr.ph)<0.005&&abs(H.gtr.y)<1";
  TCut centerFoil = "abs(H.react.z)<5";

  //make the output file
  TCanvas *canvas = new TCanvas("canvas","plots",800,800);
  canvas->SetFillColor(0);
  canvas->SetBorderMode(0);
  canvas->SetBorderSize(0);
  canvas->SetFrameFillColor(0);
  canvas->SetFrameBorderMode(0);
  std::string pdf_file_name= Form("/home/cdaq/pionLT-2021/hallc_replay_lt_2022_Run/OUTPUT/Calib/Optics/output_plots_%i_sieve.pdf",nrun);
  gROOT->SetBatch(true);
  gStyle->SetOptStat(0);
  canvas->SetGridx();
  canvas->SetGridy();
  TFile *fout = new TFile(Form("/home/cdaq/pionLT-2021/hallc_replay_lt_2022_Run/OUTPUT/Calib/Optics/output_plots_%i_sieve.root",nrun),"RECREATE");


  //make plots
  TH1F *h_z = new TH1F("h_z",";H.react.z [cm]",100,-14,14);
  TH2F *h2_ypVy = new TH2F("h2_ypVy",";yTar [cm];ypTar",100,-5,5,100,-0.05,0.05);
  TH2F *h2_yfpVxfp = new TH2F("h2_yfpVxfp",";xfp [cm];yfp [cm]",100,-5,5,100,-10,10);
  TH2F *h2_dpVz = new TH2F("h2_dpVz",";zVertex [cm];delta",100,-14,14,100,-15,20);
  TH2F *h2_ypVz = new TH2F("h2_ypVz",";zVertex [cm];ypTar",100,-14,14,100,-0.05,0.05);
  TH2F *h2_sieve = new TH2F("h2_sieve",";ySieve [cm];xSieve[cm]",200,-7.0,7.0,200,-12.0,12.0);
  TH2F *h2_xpVd = new TH2F("h2_xpVd",";delta;xpfp",100,-10,20,100,-0.15,0.15);
  
  //plots with central hole only
  TH1F *h_z_c = new TH1F("h_z_c","central sieve hole;H.react.z [cm]",100,-14,14);
  TH2F *h2_ypVy_c = new TH2F("h2_ypVy_c","central sieve hole;yTar [cm];ypTar",100,-5,5,100,-0.05,0.05);
  TH2F *h2_yfpVxfp_c = new TH2F("h2_yfpVxfp_c","central sieve hole;xfp [cm];yfp [cm]",100,-5,5,100,-10,10);
  TH2F *h2_dpVz_c = new TH2F("h2_dpVz_c","central sieve hole;zVertex [cm];delta",100,-14,14,100,-10,20);
  TH2F *h2_ypVz_c = new TH2F("h2_ypVz_c","central sieve hole;zVertex [cm];ypTar",100,-14,14,100,-0.05,0.05);
  TH2F *h2_sieve_c = new TH2F("h2_sieve_c","central sieve hole;ySieve [cm];xSieve[cm]",200,-7.0,7.0,200,-12.0,12.0);
  TH2F *h2_xpVd_c = new TH2F("h2_xpVd_c","central sieve hole;delta;xpfp",100,-15,20,100,-0.15,0.15);

  TH2F *h2_ypVzSlice[8];

  //sieve at 166.032
  //plot this stuff
  tt->Draw("H.gtr.ph:H.react.z>>h2_ypVz",cut);
  tt->Draw("H.dc.y_fp:H.dc.x_fp>>h2_yfpVxfp",cut);
  tt->Draw("H.gtr.ph:H.gtr.y>>h2_ypVy",cut);
  tt->Draw("H.react.z>>h_z",cut );
  tt->Draw("H.gtr.dp:H.react.z>>h2_dpVz",cut);
  tt->Draw("H.gtr.x+H.gtr.th*166.032:H.gtr.y+H.gtr.ph*166.032>>h2_sieve",cut&& centerFoil);
  tt->Draw("H.dc.xp_fp:H.gtr.dp>>h2_xpVd",cut);

  tt->Draw("H.gtr.ph:H.react.z>>h2_ypVz_c",cut && cutCentral);
  tt->Draw("H.dc.y_fp:H.dc.x_fp>>h2_yfpVxfp_c",cut && cutCentral);
  tt->Draw("H.gtr.ph:H.gtr.y>>h2_ypVy_c",cut && cutCentral);
  tt->Draw("H.react.z>>h_z_c",cut && cutCentral);
  tt->Draw("H.gtr.dp:H.react.z>>h2_dpVz_c",cut && cutCentral);
  tt->Draw("H.gtr.x+H.gtr.th*166.032:H.gtr.y+H.gtr.ph*166.032>>h2_sieve_c",cut && cutCentral);
  tt->Draw("H.dc.xp_fp:H.gtr.dp>>h2_xpVd_c",cut && cutCentral);

  for (int ii=0; ii<8; ii++){
    h2_ypVzSlice[ii] = new TH2F(Form("h2_ypVzSlice_%i",ii),Form("xfp=%i cm +/- 0.5cm;zVertex [cm]; ypTar",ii-4),100,-15,15,100,-0.05,0.05);
    TCut slice = Form("abs(H.dc.x_fp - (%i+1))<0.5",ii-4);
    tt->Draw(Form("H.gtr.ph:H.react.z>>h2_ypVzSlice_%i",ii),cut && slice);
  }

  //save plots
  canvas->Update();

  h_z->SetLineWidth(2);
  h_z->Draw();
  canvas->Print((pdf_file_name +"(").c_str());

  h2_ypVz->Draw("colz");
  canvas->Print((pdf_file_name +"(").c_str());

  h2_dpVz->Draw("colz");
  canvas->Print((pdf_file_name +"(").c_str());

  h2_ypVy->Draw("colz");
  canvas->Print((pdf_file_name +"(").c_str());

  h2_yfpVxfp->Draw("colz");  
  canvas->Print((pdf_file_name +"(").c_str());

  h2_sieve->Draw("colz");  
  canvas->Print((pdf_file_name +"(").c_str());

  h2_xpVd->Draw("colz");
  canvas->Print((pdf_file_name +"(").c_str());

  h_z_c->SetLineWidth(2);
  h_z_c->Draw();
  canvas->Print((pdf_file_name +"(").c_str());

  h2_ypVz_c->Draw("colz");
  canvas->Print((pdf_file_name +"(").c_str());

  h2_dpVz_c->Draw("colz");
  canvas->Print((pdf_file_name +"(").c_str());

  h2_ypVy_c->Draw("colz");
  canvas->Print((pdf_file_name +"(").c_str());

  h2_yfpVxfp_c->Draw("colz");  
  canvas->Print((pdf_file_name +"(").c_str());

  h2_sieve_c->Draw("colz");  
  canvas->Print((pdf_file_name +"(").c_str());

  h2_xpVd_c->Draw("colz");
  canvas->Print((pdf_file_name +"(").c_str());

  for (int jj=0;jj<8; jj++){
    h2_ypVzSlice[jj]->Draw("colz");
    canvas->Print((pdf_file_name +"(").c_str());
  }
  h2_xpVd_c->Draw("colz");
  canvas->Print((pdf_file_name +")").c_str());

  fout->Write();
  fout->Close();

}
