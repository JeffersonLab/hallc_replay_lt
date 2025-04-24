
Double_t pTrig1_Roc1_Raw, pTrig1_Roc1;
Double_t pTrig1_Roc2_Raw, pTrig1_Roc2;
Double_t pTrig4_Roc1_Raw, pTrig4_Roc1;
Double_t pTrig4_Roc2_Raw, pTrig4_Roc2;
Double_t pTref2;
Double_t Cointime_ROC1_RAW, Cointime_ROC2_RAW, Ctime_ePi_Roc1, Ctime_ePi_Roc2;

TH1D *pTRIG1_ROC1_tdcTimeRaw, *pTRIG1_ROC1_tdcTime;
TH1D *pTRIG1_ROC2_tdcTimeRaw, *pTRIG1_ROC2_tdcTime;

TH1D *pTRIG4_ROC1_tdcTimeRaw, *pTRIG4_ROC1_tdcTime;
TH1D *pTRIG4_ROC2_tdcTimeRaw, *pTRIG4_ROC2_tdcTime;

TH1D *pT2_tdcTimeRaw;

TH1D *CoinTime_RAW_ROC1, *CoinTime_RAW_ROC2;
TH1D *ePiCoinTime_ROC1, *ePiCoinTime_ROC1;

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
    
    DataTree->SetBranchAddress("T.coin.pTRIG4_ROC2_tdcTimeRaw", &pTrig1_Roc2_Raw);
    DataTree->SetBranchAddress("T.coin.pTRIG4_ROC2_tdcTime", &pTrig1_Roc2);
    
    DataTree->SetBranchAddress("T.coin.pTRIG4_ROC1_tdcTimeRaw", &pTrig4_Roc1_Raw);
    DataTree->SetBranchAddress("T.coin.pTRIG4_ROC1_tdcTime", &pTrig4_Roc1);
    
    DataTree->SetBranchAddress("T.coin.pT2_tdcTimeRaw", &pTref2);
    
    DataTree->SetBranchAddress("CTime.CoinTime_RAW_ROC1", &Cointime_ROC1_RAW);
    DataTree->SetBranchAddress("CTime.CoinTime_RAW_ROC2", &Cointime_ROC2_RAW);
    DataTree->SetBranchAddress("CTime.ePiCoinTime_ROC1", &Ctime_ePi_Roc1);
    DataTree->SetBranchAddress("CTime.ePiCoinTime_ROC2", &Ctime_ePi_Roc2);
    
    pTRIG1_ROC1_tdcTimeRaw = new TH1D("T.coin.pTRIG1_ROC1_tdcTimeRaw","T.coin.pTRIG1_ROC1_tdcTimeRaw",5000, 0, 10000);
    pTRIG4_ROC1_tdcTimeRaw = new TH1D("T.coin.pTRIG4_ROC1_tdcTimeRaw","T.coin.pTRIG4_ROC1_tdcTimeRaw",5000, 0, 10000);
    pTRIG1_ROC2_tdcTimeRaw = new TH1D("T.coin.pTRIG1_ROC2_tdcTimeRaw","T.coin.pTRIG1_ROC2_tdcTimeRaw",5000, 0, 10000);
    pTRIG4_ROC2_tdcTimeRaw = new TH1D("T.coin.pTRIG4_ROC2_tdcTimeRaw","T.coin.pTRIG4_ROC2_tdcTimeRaw",5000, 0, 10000);
    
    pTRIG1_ROC1_tdcTime = new TH1D("T.coin.pTRIG1_ROC1_tdcTime","T.coin.pTRIG1_ROC1_tdcTime",5000, 0, 10000);
    pTRIG4_ROC1_tdcTime = new TH1D("T.coin.pTRIG4_ROC1_tdcTime","T.coin.pTRIG4_ROC1_tdcTime",5000, 0, 10000);
    pTRIG1_ROC2_tdcTime = new TH1D("T.coin.pTRIG1_ROC2_tdcTime","T.coin.pTRIG1_ROC2_tdcTime",5000, 0, 10000);
    pTRIG4_ROC2_tdcTime = new TH1D("T.coin.pTRIG4_ROC2_tdcTime","T.coin.pTRIG4_ROC2_tdcTime",5000, 0, 10000);
    
    pT2_tdcTimeRaw = new TH1D("T.coin.pT2_tdcTimeRaw","T.coin.pT2_tdcTimeRaw",5000, 0, 10000);
    
    CoinTime_RAW_ROC1 = new TH1D("CTime.CoinTime_RAW_ROC1","CTime.CoinTime_RAW_ROC1",1000,-1000,1000);
    CoinTime_RAW_ROC2 = new TH1D("CTime.CoinTime_RAW_ROC2","CTime.CoinTime_RAW_ROC2",1000,-1000,1000);
    
    ePiCoinTime_ROC1 = new TH1D("CTime.ePiCoinTime_ROC1","CTime.ePiCoinTime_ROC1",1000,-1000,1000);
    ePiCoinTime_ROC2 = new TH1D("CTime.ePiCoinTime_ROC2","CTime.ePiCoinTime_ROC2",1000,-1000,1000);
    
    fillHistos(DataTree);
    
    //write histogrames to pdf
    TCanvas* canvas = new TCanvas("PDFOutput", "PDFOutput", 600, 600);
    gPad->SetLogy();
    
    pTRIG1_ROC1_tdcTimeRaw->Draw();
    canvas->Print(Form("output/CoinRefTimePlots_%d.pdf(",RunNumber),  pTRIG1_ROC1_tdcTimeRaw->GetName());
    pTRIG1_ROC2_tdcTimeRaw->Draw();
    canvas->Print(Form("output/CoinRefTimePlots_%d.pdf",RunNumber),  pTRIG1_ROC2_tdcTimeRaw->GetName());
    pTRIG4_ROC1_tdcTimeRaw->Draw();
    canvas->Print(Form("output/CoinRefTimePlots_%d.pdf",RunNumber),  pTRIG4_ROC1_tdcTimeRaw->GetName());
    pTRIG4_ROC2_tdcTimeRaw->Draw();
    canvas->Print(Form("output/CoinRefTimePlots_%d.pdf",RunNumber),  pTRIG4_ROC2_tdcTimeRaw->GetName());
    
    pTRIG1_ROC1_tdcTime->Draw();
    canvas->Print(Form("output/CoinRefTimePlots_%d.pdf",RunNumber),  pTRIG1_ROC1_tdcTime->GetName());
    pTRIG1_ROC2_tdcTime->Draw();
    canvas->Print(Form("output/CoinRefTimePlots_%d.pdf",RunNumber),  pTRIG1_ROC2_tdcTime->GetName());
    pTRIG4_ROC1_tdcTime->Draw();
    canvas->Print(Form("output/CoinRefTimePlots_%d.pdf",RunNumber),  pTRIG4_ROC1_tdcTime->GetName());
    pTRIG4_ROC2_tdcTime->Draw();
    canvas->Print(Form("output/CoinRefTimePlots_%d.pdf",RunNumber),  pTRIG4_ROC2_tdcTime->GetName());
    
    pT2_tdcTimeRaw->Draw();
    canvas->Print(Form("output/CoinRefTimePlots_%d.pdf",RunNumber),  pT2_tdcTimeRaw->GetName());
    
    CoinTime_RAW_ROC1->Draw();
    canvas->Print(Form("output/CoinRefTimePlots_%d.pdf",RunNumber),  CoinTime_RAW_ROC1->GetName());
    CoinTime_RAW_ROC2->Draw();
    canvas->Print(Form("output/CoinRefTimePlots_%d.pdf",RunNumber),  CoinTime_RAW_ROC2->GetName());
    
    ePiCoinTime_ROC1->Draw();
    canvas->Print(Form("output/CoinRefTimePlots_%d.pdf",RunNumber),  ePiCoinTime_ROC1->GetName());
    ePiCoinTime_ROC2->Draw();
    canvas->Print(Form("output/CoinRefTimePlots_%d.pdf)",RunNumber),  ePiCoinTime_ROC2->GetName());
}

void fillHistos(TTree *DataTree)
{
    Int_t MaxEvents = DataTree->GetEntries();
    cout << "Begining to fill histograms, " << MaxEvents << " events will be processed!\n";
    for(Int_t iEntry = 0; iEntry < MaxEvents; iEntry++)
    {
        DataTree->GetEntry(iEntry);
        
        pTRIG1_ROC1_tdcTimeRaw->Fill(pTrig1_Roc1_Raw);
        pTRIG1_ROC2_tdcTimeRaw->Fill(pTrig1_Roc2_Raw);
        
        pTRIG4_ROC1_tdcTimeRaw->Fill(pTrig4_Roc1_Raw);
        pTRIG4_ROC2_tdcTimeRaw->Fill(pTrig4_Roc2_Raw);
        
        pTRIG1_ROC1_tdcTime->Fill(pTrig1_Roc1);
        pTRIG1_ROC2_tdcTime->Fill(pTrig1_Roc2);
        
        pTRIG4_ROC1_tdcTime->Fill(pTrig4_Roc1);
        pTRIG4_ROC2_tdcTime->Fill(pTrig4_Roc2);
        
        pT2_tdcTimeRaw->Fill(pTref2);
        
        CoinTime_RAW_ROC1->Fill(Cointime_ROC1_RAW);
        CoinTime_RAW_ROC2->Fill(Cointime_ROC2_RAW);
        
        ePiCoinTime_ROC1->Fill(Ctime_ePi_Roc1);
        ePiCoinTime_ROC2->Fill(Ctime_ePi_Roc2);
    }
    
    return;
}
        
        
        
        
        
        
