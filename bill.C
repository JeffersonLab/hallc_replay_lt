{
//void bill(int run=11826){

// TFile *f1=new TFile("ROOTFiles/Analysis/50k/hms_coin_replay_production_11826_50000.root");
// TTree *T=(TTree*)f1->Get("T");

  gROOT->ProcessLine("  TCanvas *c1=new TCanvas();");
  gROOT->ProcessLine("  c1->Divide(2,2);");
  gROOT->ProcessLine("  c1->cd(1);");
  gROOT->ProcessLine("gPad->SetLogz()");
  gROOT->ProcessLine("  T->Draw(\"H.cal.etottracknorm>>h1(100,0,1.2)\");");
  gROOT->ProcessLine("  T->Draw(\"H.cal.etottracknorm>>h2\",\"H.cer.npeSum>5\",\"same\");");
  gROOT->ProcessLine("  T->Draw(\"H.cal.etottracknorm>>h3\",\"H.cer.npeSum>5 && abs(H.gtr.dp)<8\",\"same\");");
  gROOT->ProcessLine("  h1->SetLineColor(kBlack);");
  gROOT->ProcessLine("  h2->SetLineColor(kRed);");
  gROOT->ProcessLine("  h3->SetLineColor(kBlue);");
  gROOT->ProcessLine("  h2->Draw(\"same\");");
  gROOT->ProcessLine("  h3->Draw(\"same\");");

  gROOT->ProcessLine("  c1->cd(2);");
  gROOT->ProcessLine("gPad->SetLogz()");
  gROOT->ProcessLine("  T->Draw(\"H.cer.npeSum>>h5(100,0,30)\");");
  gROOT->ProcessLine("  T->Draw(\"H.cer.npeSum>>h6\",\"H.cal.etottracknorm > 0.6\",\"same\");");
  gROOT->ProcessLine("  T->Draw(\"H.cer.npeSum>>h7\",\"H.cer.etotracknorm> 0.6 && abs(H.gtr.dp)<8\",\"same\");");
  gROOT->ProcessLine("  h5->SetLineColor(kBlack);");
  gROOT->ProcessLine("  h6->SetLineColor(kRed);");
  gROOT->ProcessLine("  h7->SetLineColor(kBlue);");
  gROOT->ProcessLine("  h6->Draw(\"same\");");
  gROOT->ProcessLine("  h7->Draw(\"same\");");
  
  gROOT->ProcessLine("  c1->cd(3);");
  gROOT->ProcessLine("gPad->SetLogz()");
  gROOT->ProcessLine("  T->Draw(\"H.cal.etottracknorm>>h3(100,0,1.2)\",\"H.cer.npeSum>5 && abs(H.gtr.dp)<8 && H.cal.etottracknorm > 0.6\");");
  gROOT->ProcessLine("  c1->cd(4);");
  gROOT->ProcessLine("gPad->SetLogz()");
  gROOT->ProcessLine("  T->Draw(\"H.cer.npeSum>>h8(100,0,30)\",\"H.cer.npeSum>5 && abs(H.gtr.dp)<8 && H.cal.etottracknorm > 0.6\");");
  

//  return;

//}
}
