/*
	HodoParam1Compair.C
	Author: Nathan Heinrich
	
	This script is for graphing the Param1eters from shms Hodoscope Time Walk Calibration.
	It takes in a file with run numbers, and then spits out some graphs of Param1eter vrs run #
	requires you to have run the timeWalkCalib.C script first!!!

	This only works for HMS, a similar script works for SHMS 
*/

#include <TSystem.h>
#include <TString.h>
#include "TFile.h"
#include "TTree.h"
#include <TNtuple.h>
#include "TCanvas.h"
#include <iostream>
#include <fstream>
#include "TMath.h"
#include "TH1F.h"
#include <TH2.h>
#include <TStyle.h>
#include <TGraph.h>
#include <TROOT.h>
#include <TMath.h>
#include <TLegend.h>
#include <TPaveLabel.h>
#include <TPaveText.h>
#include <TProfile.h>
#include <TPolyLine.h>
#include <TObjArray.h>
#include <TMultiGraph.h>
#include <TF1.h>

// Declare constants
static const UInt_t nPlanes     = 4;
static const UInt_t nSides      = 2;
static const UInt_t nBarsMax    = 16;
static const UInt_t nTwFitPars = 2;
static const TString sideNames[nSides] = {"Positive", "Negative"};

const Int_t INILENGTH = 64;

//makes a divided canvas
TCanvas *makeCan(UInt_t numColumns, UInt_t numRows, UInt_t winWidth, UInt_t winHeight, TCanvas *can, TString name, TString title) {
  can = new TCanvas(name, title, winWidth, winHeight);  
  can->Divide(numColumns, numRows);
  return can;
}

//gets run #s from file
bool getRuns ( Double_t *runs, ifstream& runFile, Int_t& Length)
{	
    Int_t Iteration = 1;
	while (!runFile.eof())
	{
		// for if there are greater than INILENGTH runs that need to be read in.
		if (Length >= Iteration*INILENGTH)
		{
			Iteration++;
			// copy current list into one that has INILENGTH more spots
			Double_t *temp = new Double_t [Iteration*INILENGTH];
			for (Int_t i = 0; i < Length; i++)
			{
				temp[i] = runs[i];
			}
			//return memory
			delete[] runs;
			//copy pionter into new list location
			runs = temp;
		}
		runFile >> runs[Length];
		//for some reason the run list has not ended properly (Prob. caused by an extra line at the end of the runlist file)
		//   So end early
		if(runs[Length] == 0)
		{
		    cout << "ending file read in early as zero found in runlist file.\nMight be caused by an extra line at the end of the runlist file\n";
		    // if we managed to read in anything then just use that.
		    if (Length > 0)
		    {
		        return true;
		    }else{
		        return false;
		    }
		}
		Length++;
	}
	Length--; // having issue where the length is to long by one for some reason.
	return true;
}

//gets the data from runfile
void getData ( Double_t *Param1[nPlanes][nBarsMax][nSides], Double_t *Param1Err[nPlanes][nBarsMax][nSides], Double_t *Param2[nPlanes][nBarsMax][nSides], Double_t *Param2Err[nPlanes][nBarsMax][nSides], UInt_t irun, ifstream &runFile)
{
	//loop over sides
	for (UInt_t iside = 0; iside < nSides; iside++)
	{
		//loop over planes
		for(UInt_t iplanes = 0; iplanes < nPlanes; iplanes++)
		{
			//loop over Bars
			for(UInt_t ibar = 0; ibar < nBarsMax; ibar++)
			{
				//get Param1s
				runFile >> Param1[iplanes][ibar][iside][irun];
			}
			
			for(UInt_t ibar = 0; ibar < nBarsMax; ibar++)
			{
				//get Param1 errors
				runFile >> Param1Err[iplanes][ibar][iside][irun];
			}
			
		}
	}
	
	//loop over sides
	for (UInt_t iside = 0; iside < nSides; iside++)
	{
		//loop over planes
		for(UInt_t iplanes = 0; iplanes < nPlanes; iplanes++)
		{
			//loop over Bars
			for(UInt_t ibar = 0; ibar < nBarsMax; ibar++)
			{
				//get Param1s
				runFile >> Param2[iplanes][ibar][iside][irun];
			}
			
			for(UInt_t ibar = 0; ibar < nBarsMax; ibar++)
			{
				//get Param1 errors
				runFile >> Param2Err[iplanes][ibar][iside][irun];
			}
			
		}
	}
	return;
}


//removes points that the fitting proccess failed
void RemoveBad ( TGraphErrors *g1, Double_t *Param, Double_t *ParamErr, UInt_t numRuns)
{
	for (UInt_t irun = 0; irun < numRuns; irun++)
	{
		if ( Param[irun] >= 1 || ParamErr[irun] == 0 || Param[irun] < 0 || (ParamErr[irun]/Param1[irun]) > 0.5)
		{
			g1->RemovePoint(irun);
		}
	}

}

void HodoParamCompair ( TString runNums_name ) //input path to run # file
{
	//open file with run numbers
	ifstream runFile;
	runFile.open(runNums_name);
	
	if (!runFile)
	{
        cout << "File not Found!!!!\n";
		return;
	}
	
	//Make array for the run numbers
	Double_t *runs = new Double_t[INILENGTH];
	Int_t numRuns = 0;
	
	//fill the array with run numbers
	if ( !getRuns(runs, runFile, numRuns) )
	{
		cout << "Bad file given!!\n";
		return;
	}
	
	//output requested runs to terminal
	cout << "Processing Runs:" << endl;
	for (int i = 0; i < numRuns; i++)
		cout << runs[i] << endl;
	
	runFile.close();
	
	
	//********************************//
	//read in values one run at a time
	//********************************//
	
	
	//okay before you get super mad this was the only way, I promise
	//make place to store Param1eter arrays
	Double_t *Param1[nPlanes][nBarsMax][nSides];
	Double_t *Param1Err[nPlanes][nBarsMax][nSides];
	
	Double_t *Param2[nPlanes][nBarsMax][nSides];
	Double_t *Param2Err[nPlanes][nBarsMax][nSides];
	
	// make the Param1eter arrays
	for (UInt_t i = 0; i < nPlanes; i++)
	{
		
		for (UInt_t j = 0; j < nBarsMax; j++)
		{
			
			for (UInt_t k = 0; k < nSides; k++)
			{
				Param1[i][j][k] = new Double_t[numRuns];
				Param1Err[i][j][k] = new Double_t[numRuns];
				Param2[i][j][k] = new Double_t[numRuns];
				Param2Err[i][j][k] = new Double_t[numRuns];
			}
		}
	}
	
	
	TString fileName;
	
	//get from each run
	for(UInt_t irun = 0; irun < numRuns; irun++)
	{
		
		//get file
		fileName = Form("hhodo_TWcalib_Err_%.0f.Param1", runs[irun]); // may need to change this path though
		runFile.open(fileName);
		
		//output error if can't find file
		if ( !runFile )
		{
			cout << "could not find file: \"" << fileName << "\"!!!" << endl;  
			//if this file is not found its either that you did not run that run number or didn't fix the hms to also output this file!
			cout << "Stopping!!" << endl;
			return;
		}
		
		// get data from this file
		getData(Param1, Param1Err, Param2, Param2Err, irun, runFile);
		
		//prep for next file
		runFile.close();
	}
	
	//normalizeData(Param1, Param1Err, numRuns);
	
	//***************//
	//  make plots   //
	//***************//
	
	gROOT->SetBatch(kTRUE); //don't display plots
	
	//make file to store output
	/*
	TFile *Outfile = new TFile("./Hodo_Param1_Comp.root", "RECREATE");
	if ( !Outfile->IsOpen() )
	{
		cout << "Output File Failed To Create!!!\nShuting down!!!\n";
		return;
	}
	*/
	
	/*
	TCanvas *Temp = new TCanvas(Form("c_s%i_p%i", 0, 1), Form("TW_c2_Comp_"+sideNames[0]+"_side_plane_%i", 1), 1600, 1600); // name, title, width, height
	Temp->SetGrid();
	TGraphErrors *tp = new TGraphErrors (numRuns, runs, Param1[0][1][1], nullptr, Param1Err[0][1][1]);
	tp->SetTitle("TW_c2_Copm_Positive_side_plane_x1_Bar_2");
	tp->SetMarkerStyle(1);
	tp->SetMarkerColor(kBlue);
	tp->SetLineColor(kBlue);
	tp->GetXaxis()->SetTitle("Run Number");
	tp->GetYaxis()->SetTitle("TW Fit Param1eter Value");
	tp->SetMarkerStyle(35);
   	tp->Draw("AP");
	Temp->Write( "TW_example" );
	*/
	
	//make canvases and graphs
	TCanvas *CompCanC2[nSides][nPlanes], *CompCanC1[nSides][nPlanes];
	TGraphErrors *CompGra[nSides][nPlanes][nBarsMax], *CompGraC1[nSides][nPlanes][nBarsMax];
	TF1 *Lin2021[nSides][nPlanes][nBarsMax], *Lin2022[nSides][nPlanes][nBarsMax]; 
	
	//loop over sides
	for (UInt_t iside = 0; iside < nSides; iside++)
	{
		
		for (UInt_t iplane = 0; iplane < nPlanes; iplane++)
		{
			CompCanC2[iside][iplane] = new TCanvas(Form("c2_s%i_p%i", iside, iplane+1), Form("hHodo_TW_c2_Comp_"+sideNames[iside]+"_side_plane_%i", iplane+1), 3200, 3200); // name, title, width, height
			CompCanC1[iside][iplane] = new TCanvas(Form("c1_s%i_p%i", iside, iplane+1), Form("hHodo_TW_c1_Comp_"+sideNames[iside]+"_side_plane_%i", iplane+1), 3200, 3200); // name, title, width, height
			
			//save space on the non-quartz planes
			if ( iplane == 3)
			{
				CompCanC2[iside][iplane]->Divide(5,5);
				CompCanC1[iside][iplane]->Divide(5,5);
			}else {
				CompCanC2[iside][iplane]->Divide(4,4);
				CompCanC1[iside][iplane]->Divide(4,4);
			}
			
			//for planes only run as much as is neccessary (13 in first two, 14 in 3rd one and 21 times in quartz
			for (UInt_t ibar = 0;((ibar < 13) || (ibar < 14 && iplane == 2)) || (ibar < nBarsMax && iplane == 3) ; ibar++)
			{
				// make canvas
				CompCanC1[iside][iplane]->cd(ibar+1);
				CompCanC1[iside][iplane]->SetGrid();
				
				// fill then draw graph
				//CompGra[iside][iplane][ibar] = new TGraphErrors (numRuns, runs, Param1[iplane][ibar][iside], nullptr, Param1Err[iplane][ibar][iside]);
				CompGra[iside][iplane][ibar] = new TGraphErrors();
				CompGraC1[iside][iplane][ibar] = new TGraphErrors();
				
				Lin2021[iside][iplane][ibar] = new TF1 ("Const Fit 2021", "[0]", 11700, 14777);
				Lin2022[iside][iplane][ibar] = new TF1 ("Const Fit 2022", "[0]", 14777, 17200);
				
				int *toRemove = new int[numRuns];
				int ipoint = 0;
				for (UInt_t irun = 0; irun < numRuns; irun++)
				{
					//C2 fill, yes I know retrofitting is hard okay
					if (( Param1[iplane][ibar][iside][irun] >= 1 || Param1Err[iplane][ibar][iside][irun] == 0 || Param1[iplane][ibar][iside][irun] < 0 || (TMath::Abs(Param1Err[iplane][ibar][iside][irun]/Param1[iplane][ibar][iside][irun]) > 0.5) ) && !( Param1[iplane][ibar][iside][irun] == 0 && Param1Err[iplane][ibar][iside][irun] == 0 ))
					{
						cout << "Removing C2 Point From plane " << iplane+1 << ", side " << sideNames[iside] << ", bar " << ibar+1 << ", run " << CompGra[iside][iplane][ibar]->GetPointX(irun) << "\n";
						cout << "Values: x = " << runs[irun] << ", y = " << CompGra[iside][iplane][ibar]->GetPointY(irun) << ", yerr = " << CompGra[iside][iplane][ibar]->GetErrorY(irun) << '\n';
						//if (!CompGra[iside][iplane][ibar]->RemovePoint(irun)) cout << "failed!!!\n";
						toRemove[irun] = irun;
					}else{
						toRemove[irun] = 0;
						CompGra[iside][iplane][ibar]->AddPoint(runs[irun],Param1[iplane][ibar][iside][irun]);
						CompGra[iside][iplane][ibar]->SetPointError(ipoint,0, Param1Err[iplane][ibar][iside][irun]);
						ipoint++;
					}
					//C1 fill, yes I know retrofitting is hard okay
					if (( Param2Err[iplane][ibar][iside][irun] == 0 || Param2[iplane][ibar][iside][irun] < 0 || (TMath::Abs(Param2Err[iplane][ibar][iside][irun]/Param2[iplane][ibar][iside][irun]) > 0.5) ) && !( Param2[iplane][ibar][iside][irun] == 0 && Param2Err[iplane][ibar][iside][irun] == 0 ))
					{
						cout << "Removing C1 Point From plane " << iplane+1 << ", side " << sideNames[iside] << ", bar " << ibar+1 << ", run " << CompGra[iside][iplane][ibar]->GetPointX(irun) << "\n";
						cout << "Values: x = " << runs[irun] << ", y = " << CompGra[iside][iplane][ibar]->GetPointY(irun) << ", yerr = " << CompGra[iside][iplane][ibar]->GetErrorY(irun) << '\n';
						//if (!CompGra[iside][iplane][ibar]->RemovePoint(irun)) cout << "failed!!!\n";
						toRemove[irun] = irun;
					}else{
						toRemove[irun] = 0;
						CompGraC1[iside][iplane][ibar]->AddPoint(runs[irun],Param2[iplane][ibar][iside][irun]);
						CompGraC1[iside][iplane][ibar]->SetPointError(ipoint,0, Param2Err[iplane][ibar][iside][irun]);
						ipoint++;
					}
				}
				//for(UInt_t irun = numRuns; irun < 0; irun++){
				//	if (!CompGra[iside][iplane][ibar]->RemovePoint(irun)) cout << "failed to remove run " << runs[irun] << "!!!\n";
				//}
				
				
				//RemoveBad(CompGra[iside][iplane][ibar], Param1[iplane][ibar][iside], Param1Err[iplane][ibar][iside], numRuns);
				
				//setting a bunch of stuff
				CompGra[iside][iplane][ibar]->SetTitle(Form("TW_c2_Comp_"+sideNames[iside]+"_side_plane_%i_Bar%i", iplane+1, ibar+1));
				CompGra[iside][iplane][ibar]->SetMarkerStyle(1);
				CompGra[iside][iplane][ibar]->SetMarkerColor(kBlue);
				CompGra[iside][iplane][ibar]->SetLineColor(kBlue);
				CompGra[iside][iplane][ibar]->GetXaxis()->SetTitle("Run Number");
				CompGra[iside][iplane][ibar]->GetYaxis()->SetTitle("TW C2 Value");
				CompGra[iside][iplane][ibar]->SetMarkerStyle(35);
   				CompGra[iside][iplane][ibar]->Draw("AP");
				
				CompGra[iside][iplane][ibar]->Fit(Lin2021[iside][iplane][ibar], "QR+", "SAME");
				CompGra[iside][iplane][ibar]->Fit(Lin2022[iside][iplane][ibar], "QR+", "SAME");
				
				//Lin2021[iside][iplane][ibar]->Draw("SAME");
				//Lin2022[iside][iplane][ibar]->Draw("SAME");
				//write to file
				// make C2 canvas
				CompCanC2[iside][iplane]->cd(ibar+1);
				CompCanC2[iside][iplane]->SetGrid();
				
				//setting a bunch of stuff
				CompGraC1[iside][iplane][ibar]->SetTitle(Form("TW_c1_Comp_"+sideNames[iside]+"_side_plane_%i_Bar%i", iplane+1, ibar+1));
				CompGraC1[iside][iplane][ibar]->SetMarkerStyle(1);
				CompGraC1[iside][iplane][ibar]->SetMarkerColor(kBlue);
				CompGraC1[iside][iplane][ibar]->SetLineColor(kBlue);
				CompGraC1[iside][iplane][ibar]->GetXaxis()->SetTitle("Run Number");
				CompGraC1[iside][iplane][ibar]->GetYaxis()->SetTitle("TW C1 Value");
				CompGraC1[iside][iplane][ibar]->SetMarkerStyle(35);
   				CompGraC1[iside][iplane][ibar]->Draw("AP");
				
				CompGraC1[iside][iplane][ibar]->Fit(Lin2021[iside][iplane][ibar], "QR+", "SAME");
				CompGraC1[iside][iplane][ibar]->Fit(Lin2022[iside][iplane][ibar], "QR+", "SAME");
				
				//CompGra[iside][iplane]->Write( Form("TW_c2_Comp_"+sideNames[iside]+"_side_plane%i_Bar%i", iplane+1, ibar+1) );
			}
			//CompCanC2[iside][iplane]->Write( Form("TW_c2_Comp_"+sideNames[iside]+"_side_plane%i", iplane+1) );
			if(iside == 0 && iplane == 0) {
				CompCanC2[iside][iplane]->Print("hHodo_TW_Comp_All.pdf(");
				CompCanC1[iside][iplane]->Print("hHodo_TW_Comp_All.pdf");
			}else if (iside == (nSides - 1)  && iplane == (nPlanes - 1) ) {
				CompCanC2[iside][iplane]->Print("hHodo_TW_Comp_All.pdf");
				CompCanC1[iside][iplane]->Print("hHodo_TW_Comp_All.pdf)");
			}else{
				CompCanC2[iside][iplane]->Print("hHodo_TW_Comp_All.pdf");
				CompCanC1[iside][iplane]->Print("hHodo_TW_Comp_All.pdf");
			}
		}
	}
	
	/*
	//move to directory that will contain individual histograms
	TDirectory* CompHistos = dynamic_cast <TDirectory*> (Outfile->Get("CompHistos;1"));
	if (!CompHistos) 
	{
	  CompHistos = Outfile->mkdir("CompHistos");
	  //CompHistos = dynamic_cast <TDirectory*> (Outfile->Get("CompHistos;1"));
	}
	// loop again in order to save histogrames into another directory
	for (UInt_t iside = 0; iside < nSides; iside++)
	{
		for (UInt_t iplane = 0; iplane < nPlanes; iplane++)
		{
			//for planes only run as much as is neccessary (13 in first two, 14 in 3rd one and 21 times in quartz
			for (UInt_t ibar = 0;((ibar < 13) || (ibar < 14 && iplane == 2)) || (ibar < nBarsMax && iplane == 3) ; ibar++)
			{
				CompHistos->WriteObject(CompGra[iside][iplane][ibar], Form("TW_c2_Comp_"+sideNames[iside]+"_side_plane_%i_Bar%i", iplane+1, ibar+1));
			}
		}
	}
	*/
	//Outfile->Close();
	return;
}






