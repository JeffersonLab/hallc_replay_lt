
Double_t pTrig1_Roc1_Raw, pTrig1_Roc1, pTrig1_Roc1_Mult;
Double_t pTrig1_Roc2_Raw, pTrig1_Roc2, pTrig1_Roc2_Mult;
Double_t pTrig3_Roc1_Raw, pTrig3_Roc1, pTrig3_Roc1_Mult;
Double_t pTrig3_Roc2_Raw, pTrig3_Roc2, pTrig3_Roc2_Mult;
Double_t pTrig4_Roc1_Raw, pTrig4_Roc1, pTrig4_Roc1_Mult;
Double_t pTrig4_Roc2_Raw, pTrig4_Roc2, pTrig4_Roc2_Mult;
Double_t pTref2, pTref2_Mult;
Double_t hTref2, hTref2_Mult;
Double_t Cointime_ROC1_RAW, Cointime_ROC2_RAW, Ctime_ePi_Roc1, Ctime_ePi_Roc2;
Double_t MMpi;
Double_t bcm;
Double_t Paero, Hcal, Hcer;
Double_t h_xfp;
Double_t pGtime, hGtime;
Double_t pNtrack, hNtrack;
Double_t pdp, hdp;

TH1D *pTRIG1_ROC1_tdcTimeRaw, *pTRIG1_ROC1_tdcTime;
TH1D *pTRIG1_ROC2_tdcTimeRaw, *pTRIG1_ROC2_tdcTime;

TH1D *pTRIG3_ROC1_tdcTimeRaw, *pTRIG3_ROC1_tdcTime;
TH1D *pTRIG3_ROC2_tdcTimeRaw, *pTRIG3_ROC2_tdcTime;

TH1D *pTRIG4_ROC1_tdcTimeRaw, *pTRIG4_ROC1_tdcTime;
TH1D *pTRIG4_ROC2_tdcTimeRaw, *pTRIG4_ROC2_tdcTime;

// Set with multiplicity cut
TH1D *pTRIG1_ROC1_tdcTimeRawM, *pTRIG1_ROC1_tdcTimeM;
TH1D *pTRIG1_ROC2_tdcTimeRawM, *pTRIG1_ROC2_tdcTimeM;

TH1D *pTRIG3_ROC1_tdcTimeRawM, *pTRIG3_ROC1_tdcTimeM;
TH1D *pTRIG3_ROC2_tdcTimeRawM, *pTRIG3_ROC2_tdcTimeM;

TH1D *pTRIG4_ROC1_tdcTimeRawM, *pTRIG4_ROC1_tdcTimeM;
TH1D *pTRIG4_ROC2_tdcTimeRawM, *pTRIG4_ROC2_tdcTimeM;

TH1D *pT2_tdcTimeRaw, *pT2_tdcTimeRawM;
TH1D *hT2_tdcTimeRaw, *hT2_tdcTimeRawM;

TH1D *CoinTime_RAW_ROC1, *CoinTime_RAW_ROC2;
TH1D *ePiCoinTime_ROC1, *ePiCoinTime_ROC2;

TH1D *CoinTime_RAW_ROC1_cut, *CoinTime_RAW_ROC2_cut;
TH1D *ePiCoinTime_ROC1_cut, *ePiCoinTime_ROC2_cut;

TH1D *MMpi_hist, *MMpi_hist_cut;

void fillHistos(TTree *DataTree)
{
    Int_t MaxEvents = DataTree->GetEntries();
    cout << "Begining to fill histograms, " << MaxEvents << " events will be processed!\n";
    int coinCounter = 0;
    int coinCounter2 = 0;
    int PidCounter = 0;
    for(Int_t iEntry = 0; iEntry < MaxEvents; iEntry++)
    {
        DataTree->GetEntry(iEntry);
        
        if( iEntry % 10000 == 0 ) cout << iEntry << "\n"; //status report
        
        //if(!(h_xfp > 3.5 && h_xfp < 6.5)) continue; // temp focal plain cut
        
        pTRIG1_ROC1_tdcTimeRaw->Fill(pTrig1_Roc1_Raw);
        pTRIG1_ROC2_tdcTimeRaw->Fill(pTrig1_Roc2_Raw);
        
        pTRIG4_ROC1_tdcTimeRaw->Fill(pTrig4_Roc1_Raw);
        pTRIG4_ROC2_tdcTimeRaw->Fill(pTrig4_Roc2_Raw);
        
        pTRIG3_ROC1_tdcTimeRaw->Fill(pTrig3_Roc1_Raw);
        pTRIG3_ROC2_tdcTimeRaw->Fill(pTrig3_Roc2_Raw);

        pTRIG1_ROC1_tdcTime->Fill(pTrig1_Roc1);
        pTRIG1_ROC2_tdcTime->Fill(pTrig1_Roc2);
        
        pTRIG4_ROC1_tdcTime->Fill(pTrig4_Roc1);
        pTRIG4_ROC2_tdcTime->Fill(pTrig4_Roc2);
        
        pTRIG3_ROC1_tdcTime->Fill(pTrig3_Roc1);
        pTRIG3_ROC2_tdcTime->Fill(pTrig3_Roc2);

        pT2_tdcTimeRaw->Fill(pTref2);
        hT2_tdcTimeRaw->Fill(hTref2);
        
        if (pGtime == 1 && hGtime == 1 && pNtrack > 0 && hNtrack > 0 && hdp > -8.0 && hdp < 8.0 && pdp > -10.0 && pdp < 22.0)
        {
            CoinTime_RAW_ROC1_cut->Fill(Cointime_ROC1_RAW);
            CoinTime_RAW_ROC2_cut->Fill(Cointime_ROC2_RAW);
        
            ePiCoinTime_ROC1_cut->Fill(Ctime_ePi_Roc1);
            ePiCoinTime_ROC2_cut->Fill(Ctime_ePi_Roc2);
        }
        

        if (pTrig1_Roc1_Mult == 1)
        {
            pTRIG1_ROC1_tdcTimeRawM->Fill(pTrig1_Roc1_Raw);
            pTRIG1_ROC1_tdcTimeM->Fill(pTrig1_Roc1);
        }
        if (pTrig1_Roc2_Mult == 1)
        {
            pTRIG1_ROC2_tdcTimeRawM->Fill(pTrig1_Roc2_Raw);
            pTRIG1_ROC2_tdcTimeM->Fill(pTrig1_Roc2);
        }
        if (pTrig4_Roc1_Mult == 1)
        {
            pTRIG4_ROC1_tdcTimeRawM->Fill(pTrig4_Roc1_Raw);
            pTRIG4_ROC1_tdcTimeM->Fill(pTrig4_Roc1);
        }
        if (pTrig4_Roc2_Mult == 1)
        {
            pTRIG4_ROC2_tdcTimeRawM->Fill(pTrig4_Roc2_Raw);
            pTRIG4_ROC2_tdcTimeM->Fill(pTrig4_Roc2);
        }
        if (pTrig3_Roc1_Mult == 1)
        {
            pTRIG3_ROC1_tdcTimeRawM->Fill(pTrig3_Roc1_Raw);
            pTRIG3_ROC1_tdcTimeM->Fill(pTrig3_Roc1);
        }
        if (pTrig3_Roc2_Mult == 1)
        {
            pTRIG3_ROC2_tdcTimeRawM->Fill(pTrig3_Roc2_Raw);
            pTRIG3_ROC2_tdcTimeM->Fill(pTrig3_Roc2);
        }
        if (pTref2_Mult == 1)
        {
            pT2_tdcTimeRawM->Fill(pTref2);
        }
        if (hTref2_Mult == 2)
        {
            hT2_tdcTimeRawM->Fill(hTref2);
        }
        
        MMpi_hist->Fill(MMpi);
        if((Ctime_ePi_Roc1 > ((0)-((2.004)/2.0)-(0.25))) & (Ctime_ePi_Roc1 < ((0)+((2.004)/2.0)+(0.25))))
        {
            coinCounter++;
            if (abs(bcm - 70) < 10.0)
            {
                coinCounter2++;
                if ((Paero > 1.5) & (Hcal > 0.7) & (Hcer > 0.3))
                {
                    PidCounter++;
                    MMpi_hist_cut->Fill(MMpi);
                }
            }
        }
        
    }
    cout << "inside Coin Cut: " << coinCounter;
    cout << "\ninside bcm and coin cut: " << coinCounter2<< endl;
    cout << "PID counter: " << PidCounter << endl;
    return;
}

void CoinRefTimes( TString rootFileName, Int_t RunNumber)
{
    gROOT->SetBatch(kTRUE);
    //get root file
    TFile* inFile = new TFile(rootFileName, "READ");
    
    if(!inFile->IsOpen())
    {
        cout << "File did not open properly.\nCheck That: '" << rootFileName << "' exists and is not corrupted.\n --- Ending --- \n";
        return;
    }
    
    
    //get tree from root file
    TTree *DataTree = dynamic_cast <TTree*> (inFile->Get("T"));
    
    DataTree->SetBranchAddress("T.coin.pTRIG1_ROC1_tdcTimeRaw", &pTrig1_Roc1_Raw);
    DataTree->SetBranchAddress("T.coin.pTRIG1_ROC1_tdcTime", &pTrig1_Roc1);
    
    DataTree->SetBranchAddress("T.coin.pTRIG1_ROC2_tdcTimeRaw", &pTrig1_Roc2_Raw);
    DataTree->SetBranchAddress("T.coin.pTRIG1_ROC2_tdcTime", &pTrig1_Roc2);
    
    DataTree->SetBranchAddress("T.coin.pTRIG4_ROC2_tdcTimeRaw", &pTrig4_Roc2_Raw);
    DataTree->SetBranchAddress("T.coin.pTRIG4_ROC2_tdcTime", &pTrig4_Roc2);
    
    DataTree->SetBranchAddress("T.coin.pTRIG4_ROC1_tdcTimeRaw", &pTrig4_Roc1_Raw);
    DataTree->SetBranchAddress("T.coin.pTRIG4_ROC1_tdcTime", &pTrig4_Roc1);

    DataTree->SetBranchAddress("T.coin.pTRIG3_ROC2_tdcTimeRaw", &pTrig3_Roc2_Raw);
    DataTree->SetBranchAddress("T.coin.pTRIG3_ROC2_tdcTime", &pTrig3_Roc2);
    
    DataTree->SetBranchAddress("T.coin.pTRIG3_ROC1_tdcTimeRaw", &pTrig3_Roc1_Raw);
    DataTree->SetBranchAddress("T.coin.pTRIG3_ROC1_tdcTime", &pTrig3_Roc1);


    DataTree->SetBranchAddress("T.coin.pT2_tdcTimeRaw", &pTref2);
    DataTree->SetBranchAddress("T.coin.pT2_tdcMultiplicity", &pTref2_Mult);
    DataTree->SetBranchAddress("T.coin.hT2_tdcTimeRaw", &hTref2);
    DataTree->SetBranchAddress("T.coin.hT2_tdcMultiplicity", &hTref2_Mult);
    
    DataTree->SetBranchAddress("CTime.CoinTime_RAW_ROC1", &Cointime_ROC1_RAW);
    DataTree->SetBranchAddress("CTime.CoinTime_RAW_ROC2", &Cointime_ROC2_RAW);
    DataTree->SetBranchAddress("CTime.ePiCoinTime_ROC1", &Ctime_ePi_Roc1);
    DataTree->SetBranchAddress("CTime.ePiCoinTime_ROC2", &Ctime_ePi_Roc2);
    
    DataTree->SetBranchAddress("T.coin.pTRIG1_ROC1_tdcMultiplicity", &pTrig1_Roc1_Mult);
    DataTree->SetBranchAddress("T.coin.pTRIG4_ROC1_tdcMultiplicity", &pTrig4_Roc1_Mult);
    DataTree->SetBranchAddress("T.coin.pTRIG1_ROC2_tdcMultiplicity", &pTrig1_Roc2_Mult);
    DataTree->SetBranchAddress("T.coin.pTRIG4_ROC2_tdcMultiplicity", &pTrig4_Roc2_Mult);
    DataTree->SetBranchAddress("T.coin.pTRIG3_ROC1_tdcMultiplicity", &pTrig3_Roc1_Mult);
    DataTree->SetBranchAddress("T.coin.pTRIG3_ROC2_tdcMultiplicity", &pTrig3_Roc2_Mult);
    
    DataTree->SetBranchAddress("P.kin.secondary.MMpi", &MMpi);
    
    DataTree->SetBranchAddress("H.bcm.bcm2.AvgCurrent", &bcm);
    DataTree->SetBranchAddress("P.aero.npeSum", &Paero);
    DataTree->SetBranchAddress("H.cal.etottracknorm", &Hcal);
    DataTree->SetBranchAddress("H.cer.npeSum", &Hcer);
    
    DataTree->SetBranchAddress("H.gtr.x", &h_xfp);

    DataTree->SetBranchAddress("P.hod.goodstarttime", &pGtime);
    DataTree->SetBranchAddress("H.hod.goodstarttime", &hGtime);

    DataTree->SetBranchAddress("P.dc.ntrack", &pNtrack);
    DataTree->SetBranchAddress("H.dc.ntrack", &hNtrack);
    
    DataTree->SetBranchAddress("P.gtr.dp", &pdp);
    DataTree->SetBranchAddress("H.gtr.dp", &hdp);

    pTRIG1_ROC1_tdcTimeRaw = new TH1D("T.coin.pTRIG1_ROC1_tdcTimeRaw","T.coin.pTRIG1_ROC1_tdcTimeRaw",5000, 0, 10000);
    pTRIG4_ROC1_tdcTimeRaw = new TH1D("T.coin.pTRIG4_ROC1_tdcTimeRaw","T.coin.pTRIG4_ROC1_tdcTimeRaw",5000, 0, 10000);
    pTRIG1_ROC2_tdcTimeRaw = new TH1D("T.coin.pTRIG1_ROC2_tdcTimeRaw","T.coin.pTRIG1_ROC2_tdcTimeRaw",5000, 0, 10000);
    pTRIG4_ROC2_tdcTimeRaw = new TH1D("T.coin.pTRIG4_ROC2_tdcTimeRaw","T.coin.pTRIG4_ROC2_tdcTimeRaw",5000, 0, 10000);
    pTRIG3_ROC1_tdcTimeRaw = new TH1D("T.coin.pTRIG3_ROC1_tdcTimeRaw","T.coin.pTRIG3_ROC1_tdcTimeRaw",5000, 0, 10000);
    pTRIG3_ROC2_tdcTimeRaw = new TH1D("T.coin.pTRIG3_ROC2_tdcTimeRaw","T.coin.pTRIG3_ROC2_tdcTimeRaw",5000, 0, 10000);
    
    pTRIG1_ROC1_tdcTime = new TH1D("T.coin.pTRIG1_ROC1_tdcTime","T.coin.pTRIG1_ROC1_tdcTime",1000, -1000, 1000);
    pTRIG4_ROC1_tdcTime = new TH1D("T.coin.pTRIG4_ROC1_tdcTime","T.coin.pTRIG4_ROC1_tdcTime",1000, -1000, 1000);
    pTRIG1_ROC2_tdcTime = new TH1D("T.coin.pTRIG1_ROC2_tdcTime","T.coin.pTRIG1_ROC2_tdcTime",1000, -1000, 1000);
    pTRIG4_ROC2_tdcTime = new TH1D("T.coin.pTRIG4_ROC2_tdcTime","T.coin.pTRIG4_ROC2_tdcTime",1000, -1000, 1000);
    pTRIG3_ROC1_tdcTime = new TH1D("T.coin.pTRIG3_ROC1_tdcTime","T.coin.pTRIG3_ROC1_tdcTime",1000, -1000, 1000);
    pTRIG3_ROC2_tdcTime = new TH1D("T.coin.pTRIG3_ROC2_tdcTime","T.coin.pTRIG3_ROC2_tdcTime",1000, -1000, 1000);
    

    pT2_tdcTimeRaw = new TH1D("T.coin.pT2_tdcTimeRaw","T.coin.pT2_tdcTimeRaw",5000, 0, 10000);
    hT2_tdcTimeRaw = new TH1D("T.coin.hT2_tdcTimeRaw","T.coin.hT2_tdcTimeRaw",5000, 0, 10000);
    
    pTRIG1_ROC1_tdcTimeRawM = new TH1D("T.coin.pTRIG1_ROC1_tdcTimeRaw_MultCut","T.coin.pTRIG1_ROC1_tdcTimeRaw_MultCut",5000, 0, 10000);
    pTRIG4_ROC1_tdcTimeRawM = new TH1D("T.coin.pTRIG4_ROC1_tdcTimeRaw_MultCut","T.coin.pTRIG4_ROC1_tdcTimeRaw_MultCut",5000, 0, 10000);
    pTRIG1_ROC2_tdcTimeRawM = new TH1D("T.coin.pTRIG1_ROC2_tdcTimeRaw_MultCut","T.coin.pTRIG1_ROC2_tdcTimeRaw_MultCut",5000, 0, 10000);
    pTRIG4_ROC2_tdcTimeRawM = new TH1D("T.coin.pTRIG4_ROC2_tdcTimeRaw_MultCut","T.coin.pTRIG4_ROC2_tdcTimeRaw_MultCut",5000, 0, 10000);
    pTRIG3_ROC1_tdcTimeRawM = new TH1D("T.coin.pTRIG3_ROC1_tdcTimeRaw_MultCut","T.coin.pTRIG3_ROC1_tdcTimeRaw_MultCut",5000, 0, 10000);
    pTRIG3_ROC2_tdcTimeRawM = new TH1D("T.coin.pTRIG3_ROC2_tdcTimeRaw_MultCut","T.coin.pTRIG3_ROC2_tdcTimeRaw_MultCut",5000, 0, 10000);
    
    pTRIG1_ROC1_tdcTimeM = new TH1D("T.coin.pTRIG1_ROC1_tdcTime_MultCut","T.coin.pTRIG1_ROC1_tdcTime_MultCut",1000, -1000, 1000);
    pTRIG4_ROC1_tdcTimeM = new TH1D("T.coin.pTRIG4_ROC1_tdcTime_MultCut","T.coin.pTRIG4_ROC1_tdcTime_MultCut",1000, -1000, 1000);
    pTRIG1_ROC2_tdcTimeM = new TH1D("T.coin.pTRIG1_ROC2_tdcTime_MultCut","T.coin.pTRIG1_ROC2_tdcTime_MultCut",1000, -1000, 1000);
    pTRIG4_ROC2_tdcTimeM = new TH1D("T.coin.pTRIG4_ROC2_tdcTime_MultCut","T.coin.pTRIG4_ROC2_tdcTime_MultCut",1000, -1000, 1000);
    pTRIG3_ROC1_tdcTimeM = new TH1D("T.coin.pTRIG3_ROC1_tdcTime_MultCut","T.coin.pTRIG3_ROC1_tdcTime_MultCut",1000, -1000, 1000);
    pTRIG3_ROC2_tdcTimeM = new TH1D("T.coin.pTRIG3_ROC2_tdcTime_MultCut","T.coin.pTRIG3_ROC2_tdcTime_MultCut",1000, -1000, 1000);
    
    pT2_tdcTimeRawM = new TH1D("T.coin.pT2_tdcTimeRaw_MultCut","T.coin.pT2_tdcTimeRaw_MultCut",5000, 0, 10000);
    hT2_tdcTimeRawM = new TH1D("T.coin.hT2_tdcTimeRaw_MultCut","T.coin.hT2_tdcTimeRaw_MultCut",5000, 0, 10000);
    
    CoinTime_RAW_ROC1 = new TH1D("CTime.CoinTime_RAW_ROC1","CTime.CoinTime_RAW_ROC1",1000,-1000,1000);
    CoinTime_RAW_ROC2 = new TH1D("CTime.CoinTime_RAW_ROC2","CTime.CoinTime_RAW_ROC2",1000,-1000,1000);
    
    ePiCoinTime_ROC1 = new TH1D("CTime.ePiCoinTime_ROC1","CTime.ePiCoinTime_ROC1",1000,-1000,1000);
    ePiCoinTime_ROC2 = new TH1D("CTime.ePiCoinTime_ROC2","CTime.ePiCoinTime_ROC2",1000,-1000,1000);
    
    CoinTime_RAW_ROC1_cut = new TH1D("CTime.CoinTime_RAW_ROC1_cut","CTime.CoinTime_RAW_ROC1_cut",1000,-1000,1000);
    CoinTime_RAW_ROC2_cut = new TH1D("CTime.CoinTime_RAW_ROC2_cut","CTime.CoinTime_RAW_ROC2_cut",1000,-1000,1000);
    
    ePiCoinTime_ROC1_cut = new TH1D("CTime.ePiCoinTime_ROC1_cut","CTime.ePiCoinTime_ROC1_cut",1000,-1000,1000);
    ePiCoinTime_ROC2_cut = new TH1D("CTime.ePiCoinTime_ROC2_cut","CTime.ePiCoinTime_ROC2_cut",1000,-1000,1000);

    MMpi_hist = new TH1D("MMpi{unCut}", "MMpi{Uncut}", 100,0,1.5);
    MMpi_hist_cut = new TH1D("MMpi{Pid Cut}", "MMpi{Pid Cut}", 100,0,1.5);
    
    
    
    fillHistos(DataTree);
    
    //write histogrames to pdf
    TCanvas* canvas1 = new TCanvas("PDFOutput1", "PDFOutput1", 1200, 2400);
    canvas1->Divide(2,3);
    
    canvas1->cd(1);
    gPad->SetLogy();
    
    pTRIG1_ROC1_tdcTimeRaw->Draw();
    pTRIG1_ROC1_tdcTimeRawM->SetLineColor(kPink+10);
    pTRIG1_ROC1_tdcTimeRawM->Draw("SAME");
    
    canvas1->cd(2);
    gPad->SetLogy();
    
    pTRIG1_ROC2_tdcTimeRaw->Draw();
    pTRIG1_ROC2_tdcTimeRawM->SetLineColor(kPink+10);
    pTRIG1_ROC2_tdcTimeRawM->Draw("SAME");
    
    canvas1->cd(3);
    gPad->SetLogy();
    pTRIG4_ROC1_tdcTimeRaw->Draw();
    pTRIG4_ROC1_tdcTimeRawM->SetLineColor(kPink+10);
    pTRIG4_ROC1_tdcTimeRawM->Draw("SAME");
    
    canvas1->cd(4);
    gPad->SetLogy();
    pTRIG4_ROC2_tdcTimeRaw->Draw();
    pTRIG4_ROC2_tdcTimeRawM->SetLineColor(kPink+10);
    pTRIG4_ROC2_tdcTimeRawM->Draw("SAME");
    
    canvas1->cd(5);
    gPad->SetLogy();
    pTRIG3_ROC1_tdcTimeRaw->Draw();
    pTRIG3_ROC1_tdcTimeRawM->SetLineColor(kPink+10);
    pTRIG3_ROC1_tdcTimeRawM->Draw("SAME");
    
    canvas1->cd(6);
    gPad->SetLogy();
    pTRIG3_ROC2_tdcTimeRaw->Draw();
    pTRIG3_ROC2_tdcTimeRawM->SetLineColor(kPink+10);
    pTRIG3_ROC2_tdcTimeRawM->Draw("SAME");
    canvas1->Print(Form("output/CoinRefTimePlots_%d.pdf(",RunNumber));
    
    TCanvas* canvas2 = new TCanvas("PDFOutput2", "PDFOutput2", 1200, 2400);
    canvas2->Divide(2,3);
    
    canvas2->cd(1);
    gPad->SetLogy();
    pTRIG1_ROC1_tdcTime->Draw();
    pTRIG1_ROC1_tdcTimeM->SetLineColor(kPink+10);
    pTRIG1_ROC1_tdcTimeM->Draw("SAME");
    
    canvas2->cd(2);
    gPad->SetLogy();
    pTRIG1_ROC2_tdcTime->Draw();
    pTRIG1_ROC2_tdcTimeM->SetLineColor(kPink+10);
    pTRIG1_ROC2_tdcTimeM->Draw("SAME");
    
    canvas2->cd(3);
    gPad->SetLogy();
    pTRIG4_ROC1_tdcTime->Draw();
    pTRIG4_ROC1_tdcTimeM->SetLineColor(kPink+10);
    pTRIG4_ROC1_tdcTimeM->Draw("SAME");
    
    canvas2->cd(4);
    gPad->SetLogy();
    pTRIG4_ROC2_tdcTime->Draw();
    pTRIG4_ROC2_tdcTimeM->SetLineColor(kPink+10);
    pTRIG4_ROC2_tdcTimeM->Draw("SAME");
    
    canvas2->cd(5);
    gPad->SetLogy();
    pTRIG3_ROC1_tdcTime->Draw();
    pTRIG3_ROC1_tdcTimeM->SetLineColor(kPink+10);
    pTRIG3_ROC1_tdcTimeM->Draw("SAME");
    
    canvas2->cd(6);
    gPad->SetLogy();
    pTRIG3_ROC2_tdcTime->Draw();
    pTRIG3_ROC2_tdcTimeM->SetLineColor(kPink+10);
    pTRIG3_ROC2_tdcTimeM->Draw("SAME");
    canvas2->Print(Form("output/CoinRefTimePlots_%d.pdf",RunNumber));
    
    TCanvas* canvas3 = new TCanvas("PDFOutput3", "PDFOutput3", 1200, 2400);
    canvas3->Divide(1,2);

    canvas3->cd(1);
    gPad->SetLogy();
    pT2_tdcTimeRaw->Draw();
    pT2_tdcTimeRawM->SetLineColor(kPink+10);
    pT2_tdcTimeRawM->Draw("SAME");
    
    canvas3->cd(2);
    gPad->SetLogy();
    
    hT2_tdcTimeRaw->Draw();
    hT2_tdcTimeRawM->SetLineColor(kPink+10);
    hT2_tdcTimeRawM->Draw("SAME");
    canvas3->Print(Form("output/CoinRefTimePlots_%d.pdf",RunNumber));
    
    TCanvas* canvas4 = new TCanvas("PDFOutput4", "PDFOutput4", 1200, 2400);
    canvas4->Divide(1,2);
    
    canvas4->cd(1);
    gPad->SetLogy();
    CoinTime_RAW_ROC1->Draw();
    CoinTime_RAW_ROC1_cut->SetLineColor(kPink+10);
    CoinTime_RAW_ROC1_cut->Draw("SAME");

    canvas4->cd(2);
    gPad->SetLogy();
    CoinTime_RAW_ROC2->Draw();
    CoinTime_RAW_ROC2_cut->SetLineColor(kPink+10);
    CoinTime_RAW_ROC2_cut->Draw("SAME");
    canvas4->Print(Form("output/CoinRefTimePlots_%d.pdf",RunNumber));
    //canvas4->Print(Form("output/CoinRefTimePlots_%d.png",RunNumber));
    
    TCanvas* canvas5 = new TCanvas("PDFOutput5", "PDFOutput5", 1200, 2400);
    canvas5->Divide(1,2);
    
    canvas5->cd(1);
    gPad->SetLogy();
    ePiCoinTime_ROC1->Draw();
    ePiCoinTime_ROC1_cut->SetLineColor(kPink+10);
    ePiCoinTime_ROC1_cut->Draw("SAME");

    canvas5->cd(2);
    gPad->SetLogy();
    ePiCoinTime_ROC2->Draw();
    ePiCoinTime_ROC2_cut->SetLineColor(kPink+10);
    ePiCoinTime_ROC2_cut->Draw("SAME");
    canvas5->Print(Form("output/CoinRefTimePlots_%d.pdf",RunNumber));
    
    TCanvas* canvas6 = new TCanvas("PDFOutput6", "PDFOutput6", 1200, 2400);
    gPad->SetLogy();
    MMpi_hist->Draw();
    canvas6->Print(Form("output/CoinRefTimePlots_%d.pdf)",RunNumber));
}


        
        
        
        
        
        
