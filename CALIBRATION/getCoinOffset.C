/* getCoinOffset.C
Author: Nathan Heinrich (U Regina)
for getting to cointime offset, feed root file outputs plots and appends offset to csv file

*/
#include <iostream>
#include <fstream>

void getCoinOffset(string pathToRootFile, int runNum)
{
	gROOT->SetBatch(kTRUE);
    //get root file
    TFile* inFile = new TFile(pathToRootFile, "READ");
    
    if(!inFile->IsOpen())
    {
        cout << "File did not open properly.\nCheck That: '" << rootFileName << "' exists and is not corrupted.\n --- Ending --- \n";
        return;
    }
    
    //get tree from root file
    TTree *DataTree = dynamic_cast <TTree*> (inFile->Get("T"));
    Double_t cointime;
    setBranchAddresses(DataTree);
    DataTree->SetBranchAddress("CTime.ePiCoinTime_ROC2", &cointime);
	
	TH1D *coinPlot = new TH1D("CTime.ePiCoinTime_ROC2", "CTime.ePiCoinTime_ROC1", 800, -100, 100);
	Int_t MaxEvents = DataTree->GetEntries();
    cout << "Begining to fill histogram, " << MaxEvents << " events will be processed!\n";
    for(Int_t iEntry = 0; iEntry < MaxEvents; iEntry++)
    {
    	coinPlot->Fill(cointime);
    }

    TCanvas *can = new TCanvas("PDFOutput", "PDFOutput", 600, 600);
    coinPlot->GetXAxis()->SetTitle("CTime.ePiCoinTime_ROC2 (1/4 ns/bin)");
    Double_t maxbin = coinPlot->GetMaximum();
	coinPlot->Draw();    
    
    TF1 gaus = new TF1("gaus", "gaus(0)", maxbin-1, maxbin+1);
    gaus->SetParameter(1, maxbin);
    coinPlot->Fit("gaus");
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
