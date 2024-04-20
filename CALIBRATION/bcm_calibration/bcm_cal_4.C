/**********************
		bcm_cal_4.C
		updated by: Nathan Heinrich (heinricn@jlab.org)
		2024 04 17
		In a twist nobody expected this is getting edited to make it easier to automate, 
		and make it more friendly to use as part of a shell script.
		
		I'm adding code that will also make it easier to do secondary analysis (like in excel)
		make sure ./bcm_data/ exists, otherwise the data will not save
**********************/

////////////////////////
// Four Panel Plot 
// Thsi code is basically a copy of bcm_cal_2.C , but here I will to remove 
// the hard coding as much as possible and automated it.
// This Script is used for BCM Caliobration for the HAll C in 12 GeV era. 
// Author: Debaditya Biswas, biswas@jlab.org 
// Date : March 15, 2018 (Last Update)
//
///////////////////////

#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TF1.h"
#include "TGraph.h"
#include <fstream>
#include <iostream>
#include <TROOT.h>
#include <string>

void bcm_cal_4(string rootFilePath, string beamRangesFile, int runNumber, string BCMName, bool batchMode)
{
    if (batchMode) // typically going to want this to be false
    {
        gROOT->SetBatch(kTRUE);
    }

	gStyle->SetOptStat(0);
	gStyle->SetOptStat(0);
	gStyle->SetTitleFontSize(0.05);
	gStyle->SetNdivisions(505);
	gStyle->SetCanvasColor(10);
	gStyle->SetPadTopMargin(0.10);
	gStyle->SetPadLeftMargin(0.08);
	gStyle->SetPadRightMargin(0.08);
	gStyle->SetPadBottomMargin(.14);
	gStyle->SetTitleYOffset(1.09);
	gStyle->SetTitleXOffset(0.855);
	gStyle->SetTitleYSize(0.03);
	gStyle->SetTitleXSize(0.03);
	gStyle->SetLabelFont(62,"X");
	gStyle->SetLabelFont(62,"Y");
	gStyle->SetTitleFont(62,"X");
	gStyle->SetTitleFont(62,"Y");
	gStyle->SetLabelSize(0.025,"X");
	gStyle->SetLabelSize(0.025,"Y");
	gStyle->SetPaperSize(23,24);
	//	gStyle->SetOptFit(1);
	//djm adding the fit probability
	gStyle->SetOptFit(1111);
	

	// BEGIN USER INPUTS FROM KEYBOARD

	Double_t cl1,cl2;
	string filename_ranges;
	if (beamRangesFile == "")
	{
	    cout << "file name for the ranges :" << endl; 
	    cout << "choose from : " << endl;
	    cin >> filename_ranges;
	}else {
	    cout << "Looking for: " << beamRangesFile << '\n';
	    filename_ranges = beamRangesFile;
	}
	std::vector<Double_t> r1,r2;
	ifstream infile(filename_ranges.c_str());
	if(infile.fail()){
		cout << "Cannot open the file: " << endl;
		cout << "ok" << endl;	 
		exit(1);
		
	}else{
		while(!infile.eof()){
			infile >> cl1 >> cl2;
			r1.push_back(cl1);
			r2.push_back(cl2);
			
		}

	}
	r1.pop_back();
	r2.pop_back();	
	Int_t size_rfile = r1.size();	
	Int_t size_rfile_trim = (size_rfile - 1)/2 ;	

	cout << "size_rfile= " << size_rfile << endl; 
	cout << "size_rfile_trim= " << size_rfile_trim << endl; 
	cout << "		 " << endl; 

	
	//cout << "shms_run_NUM "<< endl;
	cout << "runNumber: ";
	if (runNumber < 1) 
    	cin >> runNumber; 
	else {
	    cout << runNumber << '\n';
	}
    
    if ( rootFilePath == "" )
    {
        cout << "Full path to ROOTfile: ";
        cin >> rootFilePath;
    }else{
        cout << "looking for: " << rootFilePath << '\n';
    }
    
    TFile *f = new TFile(rootFilePath.c_str(),"READ"); // %d : expects integer; %f expects float 
    
    TTree *T = (TTree*)f->Get("TSH"); // TSH : for HMS and TSP : for SHMS
	
	Int_t totev = T->GetEntries();
	
	
	// Read the branch 
	
	Double_t bcm4A;
	Double_t bcm4B;
	Double_t time;
	Double_t Urate; 

	string bcm_name;	 
	cout << "BCM NAME : ";
	if ( !(BCMName == "BCM1" || BCMName == "BCM2" || BCMName == "BCM4A" || BCMName == "BCM4B" || BCMName == "BCM4C") )
	{
    	// djm These bcm's should be appropriate after the Fall17-Spring18 run.
	    cout << "choose from : BCM1, BCM2, BCM4A, BCM4B, BCM4C " << endl; 
	    cin>> bcm_name ;
    }else{
        bcm_name = BCMName;
        cout << bcm_name << '\n';
    }

	// END OF USER KEYBOARD INPUTS

    // Echo the inputs from the ranges*.txt file:
    cout << "ranges File: \n";
    for (Int_t i=0; i <size_rfile ;i++){
		cout <<"i="<< i <<" r1= "<< r1[i] <<" r2= "<< r2[i] << endl;
		//cout << p[i] << endl;
	}


	T->SetBranchAddress(Form("H.%s.scalerRate",bcm_name.c_str()),&bcm4B);	
	// T->SetBranchAddress(Form("P.%s.scalerRate",bcm_name.c_str()),&bcm4B);	
	
	// djm 7/10/19 I changed the old "Mhz" to the new "MHz"	
	T->SetBranchAddress("H.1MHz.scalerTime", &time); //for shms: P.BCM1.scalerRate
	//T->SetBranchAddress("P.1MHz.scalerTime", &time); //for shms: P.BCM1.scalerRate

	T->SetBranchAddress("H.Unser.scalerRate",&Urate);
    //T->SetBranchAddress("P.Unser.scalerRate",&Urate);
    
    cout << "---- Got BCMi, Time and Unser data----" << endl;


	//Draw the unser rate vs scaler time & bcm rate vs scaler time 

	TCanvas *c1 = new TCanvas("c1","scaler rate vs scaler time Hall C", 800, 900);
	c1->Divide(1,2);
	Double_t bcm4A_1[totev], time_1[totev],bcm4B_1[totev],Urate_1[totev] ;
	
	for (Int_t i=0 ; i<totev; i++){
		T->GetEntry(i);
		bcm4B_1[i] = bcm4B ;
		Urate_1[i] = Urate;
		time_1[i] = time ; 
		
	}
	
	cout << "Begin calculating BCMi average rates" <<endl; 

	// Draw bcm rate vs scaler time
	 
	c1->cd(1);
	TGraph *gr2 = new TGraph(totev,time_1,bcm4B_1);
	gr2->SetTitle("Rate vs time ; Scaler time	 ; BCM Rate ");
	gr2->GetXaxis()->CenterTitle();
	gr2->GetYaxis()->CenterTitle();
	gr2->Draw("aple");
		 
 
	Double_t d[size_rfile], p[size_rfile]; // dip and peak values : number of lines in text file
	
	// fitting gr2(bcm vs scaler time) from r1[i] to r2[i] with polynomial 0
	// then get the parameter 0 which is the average of the gr2 in that range
 
	for (Int_t i=0; i <size_rfile ;i++){
		TF1* d1 = new TF1("d1", "pol0", -10, 10);
		gr2->Fit("d1","S","",r1[i],r2[i]);
		d1->Draw("Same");
		p[i] = d1->GetParameter(0);
	cout <<"i="<< i <<" r1= "<< r1[i] <<" r2=	"<< r2[i] <<" bcm ave rate= "<< p[i] << endl;
		//		cout << p[i] << endl;
	}
	
	//	cout << "ok" << endl;
	// For the BCMi averaging, don't subtract the beam off offsets.
	// Later, we will subtract beam off offsets for the Unser rates. 
	// For historical reasons, keep this do-nothing definition of p_r[i] .
	Double_t p_r[size_rfile_trim];
	cout << "	" << endl; 
	cout << "Recap of the beam-on BCMi ave rates:"<< endl;
	for (Int_t i=0; i<size_rfile_trim; i++){
		//	 cout << p[2*i+1] << " " << p[2*i] <<" "<< p[2*i+2] << endl;
		//	cout <<"i="<< i <<"	"<<	p[2*i+1] << " " << p[2*i] <<" "<< p[2*i+2] << endl;		
		cout <<"i="<< i <<"		" <<	p[2*i+1]	<< endl;		
		p_r[i] = p[2*i+1] ;//- ((p[2*i] + p[2*i+2])/2.);
		 //	cout << p_r[i] << " real" << endl; 
		
	}
	
	
		 // draw all the fitted lines //

	for(Int_t i=0; i<size_rfile; i++ ){
		 TLine *l8 = new TLine(r1[i],p[i],r2[i],p[i]);
		 // l8->SetLineColor(9);
		 // I can't see the thin blue lines, so make them red. 
		 l8->SetLineColor(2);
		 l8->Draw("same");
	}
	
	cout << "	" << endl; 
	cout << "Begin calculating Unser average rates" <<endl; 


	c1->cd(2);
	TGraph *gr3 = new TGraph(totev,time_1,Urate_1);
	gr3->SetTitle("Rate vs time ; Scaler time	 ; Unser Rate ");
	// gr1->GetXaxis()->SetLimits(100.0,360.0);
	// gr1->GetYaxis()->SetRangeUser(-0.88,-0.76);
	gr3->GetXaxis()->CenterTitle();
	gr3->GetYaxis()->CenterTitle();
	// gr1->SetMarkerSize(0.20);
	//gr1->SetMarkerStyle(20);
	//gr1->SetMarkerColor(2);
	gr3->Draw("aple");
	
	// Double_t d1[20], 
	Double_t p1[size_rfile]; // parameter values or the average values of the several ranges will be stored here 
	
	for (Int_t i=0; i <size_rfile ;i++){
		TF1* f2 = new TF1("f2", "pol0", -10, 10);
		gr3->Fit("f2","S","",r1[i],r2[i]);
		f2->Draw("Same");
		p1[i] = f2->GetParameter(0);
	    cout <<"i="<< i <<" r1= "<< r1[i] <<" r2=	"<< r2[i] <<" Unser ave rate= "<< p1[i] << endl;
	    //	cout << p1[i] << endl;
	}


// draw all the fitted lines //

	for(Int_t i=0; i<size_rfile; i++ ){
		 TLine *l10 = new TLine(r1[i],p1[i],r2[i],p1[i]);
		 l10->SetLineColor(2);
		 l10->SetLineWidth(2.);
		 //l10->SetLineWidth(.5);
		 l10->Draw("same");
	}

	
	//	cout << "ok" << endl; 
	Double_t p_r1[size_rfile_trim];
	cout << "	 " << endl; 
	cout << "Summary of Unser rates:"<< endl; 
    cout << "			Beam On	 Off_low	 Off_high	On_offset-corrected"<< endl; 
	for (Int_t i=0; i<size_rfile_trim; i++){
		p_r1[i] = p1[2*i+1] - ((p1[2*i] + p1[2*i+2])/2.);
		cout << "i= "<< i << "		" << p1[2*i+1] << "	 " << p1[2*i] <<"	 "<< p1[2*i+2] << "	 "<<p_r1[i] << endl;	
		//		cout << "offset-corrected rate="<< p_r1[i] << endl; 
		//		cout << p_r1[i] << "real" << endl; 
		
	}
	

		Double_t I_U[size_rfile_trim];
		// Double_t Gain_U = 0.0002399 ;
			 Double_t Gain_U = 0.0002493 ;
		//	Double_t Gain_U = 0.0024964 ;
			 // cout << "	 " << endl; 
			 // cout << "Converting offset-corrected Unser rates to current" << endl; 
			 // cout << "based on Sept 2023 wire calibration run 911 https://hallcweb.jlab.org/doc-private/ShowDocument?docid=1235 . " << endl; 
 

	// calculate beam current I_U[i] from the bcm rate	
    for (Int_t i=0 ; i<size_rfile_trim;i++){ 
		I_U[i]= p_r1[i] * Gain_U;
		// cout <<" I_Unser :"<<I_U[i] << "	 " << "BCM_rate :" << p_r[i] << endl;		
		
	}
	
	// calculate unser current uncertaintites for the beam on positions
 // djm Sept 14, 2021 changed Unser noise level to 1 muA/sqrtHz 
 // djm Sept 26, 2023 changed Unser noise level to 2 muA/sqrtHz
		Double_t I_U_err[size_rfile_trim], p_r_err[size_rfile_trim];
		cout << "i	 I_unser	error	 BCMi ave rate	" << endl; 
 
		for (Int_t i=0; i<size_rfile_trim; i++){
			I_U_err[i] = 2.0/ sqrt(r2[2*i+1]- r1[2*i+1]);
		    p_r_err[i] = 0.01;
		    cout << i << "	 "<< I_U[i] << "	 " << I_U_err[i] << "	 " << p_r[i]	<< endl;
			//		 cout << I_U[i] << "	 "<< I_U_err[i] << "	 " << p_r[i] << "	"<< p_r_err[i]	<< endl;
		} 
		
		
		//		cout << "--- understood ---" << endl; 
		c1->Print(Form("bcm_data/%d_frequencyVtime_%s.png",runNumber, bcm_name.c_str()));
		
		TCanvas *c2 = new TCanvas("c2","Unser current vs BCMi frequency", 800, 900);	
		c2->Divide(2,2);
		c2->cd(1);
			 
		TGraphErrors *gr4 = new TGraphErrors(size_rfile_trim,I_U,p_r,I_U_err,p_r_err);
		
		// TGraphErrors *gr4 = new TGraphErrors(9,p_r,I_U,I_U_err,p_r_err);
	 
		TF1 *f4 = new TF1("f4", "pol1");
		f4->SetParameters(250000.,1600.);
		gr4->SetTitle("Frequency vs Unser ; Unser current (#muA) ; BCMi Frequency (HZ)");
		gr4->GetXaxis()->CenterTitle();
		gr4->GetYaxis()->CenterTitle();
		gr4->SetMarkerSize(0.95);
		gr4->SetMarkerStyle(20);
		gr4->SetMarkerColor(2);
 
		cout << "	" << endl; 
		cout << "Begin fitting the slope and offset for BCMi" << endl;	 

		gr4->Fit("f4","Q","");
		gr4->Draw("AP");

		Double_t slope; 
		Double_t intersec;
		slope = gr4->GetFunction("f4")->GetParameter(1);
		intersec = gr4->GetFunction("f4")->GetParameter(0);
		cout << " slope = " << slope << " intercept = " << intersec << endl;
		
		cout << "	" << endl; 
		cout << "Begin residual calculations "<< endl;
		
		// Begin calculating residuals

		Double_t BCM_I[size_rfile_trim], residual[size_rfile_trim], residual_percent[size_rfile_trim], I_U_resi_err[size_rfile_trim],
			residual_abs[size_rfile_trim],resisual_abs_err[size_rfile_trim];
		cout << "BCMi			I_unser	 Residual"<< endl; 
		for (Int_t i=0 ; i<size_rfile_trim;i++){
			// find the BCM curent from BCM frequency and slope and the offset
			BCM_I[i] =	(p_r[i]	- intersec) / slope ;
			//djm			residual[i] = I_U[i] - BCM_I[i];	I don't like this sign convention for the residual. 
			residual[i] = BCM_I[i] - I_U[i] ;
			//djm		 residual_abs[i] = (residual[i]/I_U[i]) ;
			residual_percent[i] = (residual[i]/I_U[i]) * 100.0 ; 
			resisual_abs_err[i] = (I_U_err[i] / I_U[i]) ;
			I_U_resi_err[i] = 100.0 * (I_U_err[i] / I_U[i]) ; 
			cout << BCM_I[i] << "	 " << I_U[i] << "	 "<< residual[i] << endl;
 
		 } 

		c2->cd(2);
		TGraphErrors *gr7 = new TGraphErrors(size_rfile_trim,I_U,residual,p_r_err,I_U_err);
		 gr7->SetTitle("Fit Residual vs Unser Current ; Unser current (#muA); Fit Residual (#muA)");
		 gr7->GetXaxis()->CenterTitle();
		 gr7->GetYaxis()->CenterTitle();
		 gr7 ->SetMarkerSize(0.95);
		 gr7->SetMarkerStyle(20);
		 gr7->SetMarkerColor(2);
		 gr7->Draw("SAP");
		 TLine *l7 = new TLine(0.,0.,70.,0.);
		 l7->SetLineColor(9);
		 l7->Draw();

	 c2->cd(3);
	 TGraphErrors *gr6 = new TGraphErrors(size_rfile_trim,I_U,residual_percent,p_r_err,I_U_resi_err);
		 gr6->SetTitle("Fit Residual in % vs Unser Current ; Unser current (#muA); Fit Residual (%)");
		 gr6->GetXaxis()->CenterTitle();
		 gr6->GetYaxis()->CenterTitle();
		 gr6 ->SetMarkerSize(0.95);
		 gr6->SetMarkerStyle(20);
		 gr6->SetMarkerColor(2);
		 gr6->Draw("SAP");
		 TLine *l6 = new TLine(0.,0.,70.,0.);
		 l6->SetLineColor(9);
		 l6->Draw();

		 
		 // Residual vs time graph Calculation
		 Double_t time_start[size_rfile_trim],time_end[size_rfile_trim], time_ave[size_rfile_trim], time_ave_min[size_rfile_trim]; 
		 for(Int_t i=0; i<size_rfile_trim; i++ ){
				 
				time_start[i] = r1[2*i + 1.];
	 
				time_end[i] = r2[2*i + 1.]; 
				cout << "----------------" << endl; 
				cout <<	time_start[i] << " time start (sec) "<< endl; 
				cout << time_end[i] << " time end (sec)" << endl;
				time_ave[i] = (time_start[i] + time_end[i] )/2 ; 
				time_ave_min[i] = time_ave[i] /60. ;
				cout << time_ave[i] << " time ave (sec)" << endl;
				cout <<" residual=" << residual[i]<< endl;
	//		 	cout <<" residual=" << residual_abs[i]<< endl;
		 }


		 //Drawing the Residual vs Time 

		 c2->cd(4);
		 TGraphErrors *gr8 = new TGraphErrors(size_rfile_trim,time_ave_min,residual,p_r_err,I_U_err);
		 gr8->SetTitle(" Fit Residual vs Time ; Sample Time (minutes); Fit Residual (#muA)");
		 gr8->GetXaxis()->CenterTitle();
		 gr8->GetYaxis()->CenterTitle();
		 gr8 ->SetMarkerSize(0.95);
		 gr8->SetMarkerStyle(20);
		 gr8->SetMarkerColor(2);
		 gr8->Draw("SAP");
		 TLine *l8 = new TLine(0.,0.,360.,0.);
		 l8->SetLineColor(9);
		 l8->Draw();
	 
	    c2->Print(Form("bcm_data/%d_Fit_%s.png",runNumber, bcm_name.c_str()));

	
		 // opeing a new text file //
		 
		 ofstream bcm_text; 
		 bcm_text.open (Form("bcm_data/%d_BCM_points_%s.csv",runNumber, bcm_name.c_str()));
		 bcm_text << "I_unser, I_Unser_error, BCM ave rate, BCM ave rate error, fit Residual, residual error, time (min)\n";
		 for(Int_t i =0; i<size_rfile_trim ; i++){
			 bcm_text << I_U[i]<< "," << I_U_err[i]<<"," << p_r[i] << ","<<p_r_err[i] <<"," <<residual[i] << ","<< residual_percent[i]<<"," << I_U_resi_err[i]<< "," << time_ave_min[i] << endl;	 ;
		 }
		 bcm_text << "Slope, error, Intercept, error\n" << gr4->GetFunction("f4")->GetParameter(1) << "," << gr4->GetFunction("f4")->GetParError(1) << "," << gr4->GetFunction("f4")->GetParameter(0) << "," << gr4->GetFunction("f4")->GetParError(0) << '\n'; 
		 bcm_text.close();
		 

		 /*		 
		 
		 // writting out variables in a file
		 
		 std::ofstream o("result_I_d_bcm1_1181.txt");
		 for(UInt_t j=0; j<size_rfile_trim; j++){ 
			 
			 o << I_U[j] << " "<< p_r[j] << " " <<I_U_err[j]<<" " <<p_r_err[j]<<" " << BCM_I[j] << " " << residual_percent[j] << " " << I_U_resi_err[j]<<" " <<std::endl;
			 
			 cout <<	I_U[j] << " "<< p_r[j] << " " <<I_U_err[j]<<" " <<p_r_err[j]<<" " << BCM_I[j] << " " << residual_percent[j] << " " << I_U_resi_err[j]<<" " <<endl;
			 
		 }
		 */
	//	cout << size_rfile << " :text file lines " << endl; 
		 
}
