/* getCoinOffset.C
Author: Nathan Heinrich (U Regina)
for getting to cointime offset, feed root file outputs plots and appends offset to csv file

*/
#include <iostream>
#include <fstream>

void getCoinOffset(TString pathToRootFile, int runNum)
{
	gROOT->SetBatch(kTRUE);
    //get root file
    TFile* inFile = new TFile(pathToRootFile, "READ");
    
    if(!inFile->IsOpen())
    {
        cout << "File did not open properly.\nCheck That: '" << pathToRootFile << "' exists and is not corrupted.\n --- Ending --- \n";
        return;
    }
    
    //get tree from root file
    TTree *DataTree = dynamic_cast <TTree*> (inFile->Get("T"));
    Double_t cointime, cointime2, cointime3, cointime4;
    DataTree->SetBranchAddress("CTime.ePiCoinTime_ROC1", &cointime);
//    DataTree->SetBranchAddress("CTime.ePiCoinTime_ROC2", &cointime2);
 //   DataTree->SetBranchAddress("CTime.ePiCoinTime_SHMS", &cointime3);
  //  DataTree->SetBranchAddress("CTime.ePiCoinTime_HMS", &cointime4);
	
	TH1D *coinPlot = new TH1D("CTime.ePiCoinTime_ROC1", "CTime.ePiCoinTime_ROC1", 800, -100, 100);
//	TH1D *coinPlot2 = new TH1D("CTime.ePiCoinTime_ROC2", "CTime.ePiCoinTime_ROC2", 800, -100, 100);
//	TH1D *coinPlot3 = new TH1D("CTime.ePiCoinTime_SHMS", "CTime.ePiCoinTime_SHMS", 800, -100, 100);
//	TH1D *coinPlot4 = new TH1D("CTime.ePiCoinTime_HMS", "CTime.ePiCoinTime_HMS", 800, -100, 100);
	Int_t MaxEvents = DataTree->GetEntries();
    cout << "Begining to fill histogram, " << MaxEvents << " events will be processed!\n";
    for(Int_t iEntry = 0; iEntry < MaxEvents; iEntry++)
    {
        DataTree->GetEntry(iEntry);
    	coinPlot->Fill(cointime);
 //   	coinPlot2->Fill(cointime2);
  //  	coinPlot3->Fill(cointime3);
   // 	coinPlot4->Fill(cointime4);
    }

    TCanvas *can = new TCanvas("PDFOutput", "PDFOutput", 600, 600);
    coinPlot->GetXaxis()->SetTitle("CTime.ePiCoinTime_ROC1 (1/4 ns/bin)");
    Double_t maxbin = coinPlot->GetXaxis()->GetBinCenter(coinPlot->GetMaximumBin());
    cout << maxbin << '\n';
    coinPlot->Draw();
    
    
    //coinPlot2->SetLineColor(kMagenta);
    //coinPlot3->SetLineColor(kMagenta+4);
    //coinPlot4->SetLineColor(kOrange);
    //coinPlot2->Draw("same");    
    //coinPlot3->Draw("same");    
    //coinPlot4->Draw("same");    
    
    TF1 *gaus = new TF1("gaus", "gaus(0)", maxbin-1, maxbin+1);
    gaus->SetParameter(1, maxbin);
    coinPlot->Fit("gaus","","",maxbin-1,maxbin+1);
    gaus->Draw("same");
    
    double mean = gaus->GetParameter(1);
    
    can->Print(Form("Ctime_%d.pdf",runNum));
    cout<<"Cointime mean is: " << mean << '\n';
    
    ofstream out;
    out.open("CoinOffsets.csv",std::ofstream::app);
    out << runNum << ", " << mean << '\n';
    out.close();
    return;
}
