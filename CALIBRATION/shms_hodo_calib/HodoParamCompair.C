/*
	HodoParamCompair.C
	Author: Nathan Heinrich
	
	This script is for graphing the Parameters from shms Hodoscope Time Walk Calibration.
	It takes in a file with run numbers, and then spits out some graphs of parameter vrs run #
	requires you to have run the timeWalkCalib.C script first!!!

	This only works for SHMS, a similar script works for HMS 
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
static const UInt_t nPlanes    = 4;
static const UInt_t nSides     = 2;
static const UInt_t nBarsMax   = 21;
static const UInt_t nTwFitPars = 2;
static const TString sideNames[nSides] = {"Positive", "Negative"};

//makes a divided canvas
TCanvas *makeCan(UInt_t numColumns, UInt_t numRows, UInt_t winWidth, UInt_t winHeight, TCanvas *can, TString name, TString title) {
  can = new TCanvas(name, title, winWidth, winHeight);  
  can->Divide(numColumns, numRows);
  return can;
}

//gets run #s from file
bool getRuns ( Double_t *runs, ifstream& runFile, UInt_t numRuns)
{
	for(UInt_t i = 0; i < numRuns; i++)
	{
		if ( runFile.eof())
			return false;
		runFile >> runs[i];
	}
	return true;
}

//gets the data from runfile
void getData ( Double_t *Param[nPlanes][nBarsMax][nSides], Double_t *ParamErr[nPlanes][nBarsMax][nSides], UInt_t irun, ifstream &runFile)
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
				//get Params
				runFile >> Param[iplanes][ibar][iside][irun];
			}
			
			for(UInt_t ibar = 0; ibar < nBarsMax; ibar++)
			{
				//get Param errors
				runFile >> ParamErr[iplanes][ibar][iside][irun];
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
		if ( Param[irun] == 1 &&  ParamErr[irun] == 0)
		{
			g1->RemovePoint(irun);
		}
	}

}

void HodoParamCompair ( TString runNums_name, UInt_t numRuns) //input path to run # file, and the number of runs to look at.
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
	Double_t *runs = new Double_t[numRuns];
	
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
	//make place to store parameter arrays
	Double_t *Param[nPlanes][nBarsMax][nSides];
	Double_t *ParamErr[nPlanes][nBarsMax][nSides];
	
	// make the parameter arrays
	for (UInt_t i = 0; i < nPlanes; i++)
	{
		
		for (UInt_t j = 0; j < nBarsMax; j++)
		{
			
			for (UInt_t k = 0; k < nSides; k++)
			{
				Param[i][j][k] = new Double_t[numRuns];
				ParamErr[i][j][k] = new Double_t[numRuns];
			}
		}
	}
	
	
	TString fileName;
	
	//get from each run
	for(UInt_t irun = 0; irun < numRuns; irun++)
	{
		
		//get file
		fileName = Form("Calibration_Plots/phodo_TWcalib_Err_%.0f.param", runs[irun]); // may need to change this path though
		runFile.open(fileName);
		
		//output error if can't find file
		if ( !runFile )
		{
			cout << "could not find file: \"" << fileName << "\"!!!" << endl;  
			//if this file is not found its either that you did not run that run number or didn't fix the hms to also output this file!
			cout << "Stoping!!" << endl;
			return;
		}
		
		// get data from this file
		getData(Param, ParamErr, irun, runFile);
		
		//prep for next file
		runFile.close();
	}
	
	//normalizeData(Param, ParamErr, numRuns);
	
	//***************//
	//  make plots   //
	//***************//
	
	gROOT->SetBatch(kTRUE); //don't display plots
	
	//make file to store output
	TFile *File = new TFile("./Calibration_Plots/Hodo_Param_Comp.root", "RECREATE");
	if ( !File->IsOpen() )
	{
		cout << "Output File Failed To Create!!!\nShuting down!!!\n";
		return;
	}
	
	TCanvas *Temp = new TCanvas(Form("c_s%i_p%i", 0, 1), Form("TW_c2_Comp_"+sideNames[0]+"_side_plane_%i", 1), 1600, 1600); // name, title, width, height
	Temp->SetGrid();
	TGraphErrors *tp = new TGraphErrors (numRuns, runs, Param[0][1][1], nullptr, ParamErr[0][1][1]);
	tp->SetTitle("TW_c2_Copm_Positive_side_plane_x1_Bar_2");
	tp->SetMarkerStyle(1);
	tp->SetMarkerColor(kBlue);
	tp->SetLineColor(kBlue);
	tp->GetXaxis()->SetTitle("Run Number");
	tp->GetYaxis()->SetTitle("TW Fit Parameter Value");
	tp->SetMarkerStyle(35);
   	tp->Draw("AP");
	Temp->Write( "TW_example" );
	
	
	//make canvases and graphs
	TCanvas *CompCan[nSides][nPlanes];
	TGraphErrors *CompGra[nSides][nPlanes][nBarsMax];
	
	//loop over sides
	for (UInt_t iside = 0; iside < nSides; iside++)
	{
		
		for (UInt_t iplane = 0; iplane < nPlanes; iplane++)
		{
			CompCan[iside][iplane] = new TCanvas(Form("c_s%i_p%i", iside, iplane+1), Form("TW_c2_Comp_"+sideNames[iside]+"_side_plane_%i", iplane+1), 1600, 1600); // name, title, width, height
			
			//save space on the non-quartz planes
			if ( iplane == 3)
			{
				CompCan[iside][iplane]->Divide(5,5);
			}else {
				CompCan[iside][iplane]->Divide(4,4);
			}
			
			//for planes only run as much as is neccessary (13 in first two, 14 in 3rd one and 21 times in quartz
			for (UInt_t ibar = 0;((ibar < 13) || (ibar < 14 && iplane == 2)) || (ibar < nBarsMax && iplane == 3) ; ibar++)
			{
				// make canvas
				CompCan[iside][iplane]->cd(ibar+1);
				CompCan[iside][iplane]->SetGrid();
				
				// fill then draw graph
				CompGra[iside][iplane][ibar] = new TGraphErrors (numRuns, runs, Param[iplane][ibar][iside], nullptr, ParamErr[iplane][ibar][iside]);
				RemoveBad(CompGra[iside][iplane][ibar], Param[iplane][ibar][iside], ParamErr[iplane][ibar][iside], numRuns);
				
				//setting a bunch of stuff
				CompGra[iside][iplane][ibar]->SetTitle(Form("TW_c2_Comp_"+sideNames[iside]+"_side_plane_%i_Bar%i", iplane+1, ibar+1));
				CompGra[iside][iplane][ibar]->SetMarkerStyle(1);
				CompGra[iside][iplane][ibar]->SetMarkerColor(kBlue);
				CompGra[iside][iplane][ibar]->SetLineColor(kBlue);
				CompGra[iside][iplane][ibar]->GetXaxis()->SetTitle("Run Number");
				CompGra[iside][iplane][ibar]->GetYaxis()->SetTitle("TW Fit Parameter Value");
				CompGra[iside][iplane][ibar]->SetMarkerStyle(35);
   				CompGra[iside][iplane][ibar]->Draw("AP");
				
				//write to file
				//CompGra[iside][iplane]->Write( Form("TW_c2_Comp_"+sideNames[iside]+"_side_plane%i_Bar%i", iplane+1, ibar+1) );
			}
			CompCan[iside][iplane]->Write( Form("TW_c2_Comp_"+sideNames[iside]+"_side_plane%i", iplane+1) );
		}
	}
	
	
	File->Close();
	return;
}






