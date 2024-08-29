/*
  RefitBCM.C
  Author: Nathan Heinrich (U of Regina)
  
  Quick root scipt to fit the quadratic term that Hcana uses to the BCM data.
  Take space seperated files with format:
  unser_Current unser_Error BCM_current BCM_error Time
*/
#include <iostream>
#include <fstream>
using namespace std;

Double_t linQuad(Double_t *x, Double_t *par)
{
    Double_t m = par[1];
    Double_t b = par[0];
    
    Double_t I = x[0];
    
    Double_t y = I* m + b;
    if(I > 50.)
    {
        y+=(-1.) * (0.002 * ( I- 50.));
    }
    return y;
}

void RefitBCM ( TString fileName ) // requires the filename as input
{
	// opens data file
    ifstream inData1;
    TString inputFileName1 = fileName;
    inData1.open(inputFileName1);
    if(!(inData1.is_open())) cout << "File Opening Failed" << endl;
	
	
	const int LEN = 100; // hard coded, should change for bigger files
	double unserCur[LEN], unserErr[LEN], BCMcur[LEN], BCMerr[LEN], Time[LEN]; 
	double maxCur = 0, maxTime = 0, minTime = 0;
	int i = 0;
	while(!inData1.eof())
	{
	    inData1 >> unserCur[i];
	    inData1 >> unserErr[i];
	    inData1 >> BCMcur[i];
	    inData1 >> BCMerr[i];
	    inData1 >> Time[i];
	    if (unserCur[i] > maxCur) maxCur = unserCur[i];
	    if (Time[i] > maxTime) maxTime = Time[i];
	    if (Time[i] < minTime) minTime = Time[i];
	    i++;
	}
	i--;
    
    if(minTime-5 < 0) minTime = 5;
    
    for(int j = 0; j<i; j++)
	{
	    cout << unserCur[j] << " " << unserErr[j] << " " << BCMcur[j] << " " << BCMerr[j] << " " << Time[j] << '\n';
	}
	
	TCanvas *c1 = new TCanvas ("c1", "Linear", 1300, 700);
	c1->Divide(2,2);
	c1->cd(1);
	
	TGraphErrors *Data = new TGraphErrors (i, unserCur, BCMcur, unserErr, BCMerr);
	Data->GetXaxis()->SetRangeUser(0, maxCur+5);
	Data->SetMarkerColor(4);
	Data->SetMarkerStyle(21);
	
	Data->SetTitle("Fit");
	Data->GetXaxis()->SetTitle("Unser Current (uA)");
	Data->GetYaxis()->SetTitle("BCM Rate");

    Data->Draw("AP"); //draws plot
	TF1 *f1 = new TF1("f1", linQuad, 0, 80, 2); 
	f1->SetParameter(1, 5579.5);
	f1->SetParameter(0, 249470.);
	
	//Data->Fit(f1, "", "", 0, 100);
	f1->Draw("same");
	
	std::ostringstream sstream, sstream1;
    
	Double_t slope = f1->GetParameter(1);
	Double_t intercept = f1->GetParameter(0);
	Double_t slope_err = f1->GetParError(1);
	Double_t intercept_err = f1->GetParError(0);
	sstream << "Slope: " << slope << " +- " << slope_err; 
	sstream1 <<"Intercept: " << intercept << " +- " << intercept_err << '\n';
    std::string varAsString = sstream.str();
	
    TLegend *legend = new TLegend(0.1,0.7,0.48,0.9);
    legend->SetHeader("fit","C"); // option "C" allows to center the header
    //legend->AddEntry("f1","Slope: "+slope+" +- " +slope);
    legend->AddEntry("f1",varAsString.c_str());
    legend->AddEntry("f1", sstream1.str().c_str());
    cout << slope << " " << slope_err << " " << intercept << " " << intercept_err << '\n';
    legend->Draw();
	
	c1->cd(2);
	Double_t residual[LEN];
	
	for(int j = 0; j<i; j++)
	{
	    residual[j] = ((BCMcur[j] - intercept)/slope) - unserCur[j];
	    if(unserCur[j] > 50){
	        //residual[j] = residual[j] + 0.002*(unserCur[j]-50)*(unserCur[j]-50);
	    }
	}
	
	TGraphErrors *res1 = new TGraphErrors (i, unserCur, residual, BCMerr, unserErr);
	res1->GetXaxis()->SetRangeUser(0, maxCur+5);
	res1->SetMarkerColor(4);
	res1->SetMarkerStyle(21);
	res1->SetTitle("residual");
	res1->GetXaxis()->SetTitle("Unser Current (uA)");
	res1->GetYaxis()->SetTitle("Residual");

    res1->Draw("AP"); //draws plot
	TLine *bar = new TLine(0,0,maxCur+5,0);
	bar->SetLineColor(2);
	bar->Draw("same");
	
	c1->cd(3);
	Double_t residual_percent[LEN];
	Double_t residerr_percent[LEN];
	
	for(int j = 0; j<i; j++)
	{
	    residual_percent[j] = (residual[j]/unserCur[j])*100;
	    residerr_percent[j] = 100*unserErr[j]/(unserCur[j]);
	}
	
	TGraphErrors *res2 = new TGraphErrors (i, unserCur, residual_percent, BCMerr, residerr_percent);
	res2->GetXaxis()->SetRangeUser(0, maxCur+5);
	res2->SetMarkerColor(4);
	res2->SetMarkerStyle(21);
	res2->SetTitle("percent residual");
	res2->GetXaxis()->SetTitle("Unser Current (uA)");
	res2->GetYaxis()->SetTitle("Residual %");

    res2->Draw("AP"); //draws plot
	bar->Draw("same");
	
	c1->cd(4);
	
	TGraphErrors *res3 = new TGraphErrors (i, Time, residual, BCMerr, unserErr);
	
	res3->SetMarkerColor(4);
	res3->SetMarkerStyle(21);
	res3->SetTitle("Residual vrs Time");
	res3->GetXaxis()->SetTitle("Time (min)");
	res3->GetYaxis()->SetTitle("Residual");

    res3->Draw("AP"); //draws plot
    res3->GetXaxis()->SetRangeUser(minTime-5, maxTime+5);
    res3->Draw("AP");
    c1->Update();
	TLine *bar2 = new TLine(minTime,0,maxTime+5,0);
	bar2->SetLineColor(2);
	bar2->Draw("same");
	
	c1->Print("refit.png");
}






