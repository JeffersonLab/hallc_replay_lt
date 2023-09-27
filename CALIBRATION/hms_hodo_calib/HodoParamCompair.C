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
static const bool DEBUGMODE = false;

//C.Y. Dec 09, 2021 | use tdcThresh parameter for scints and quartz independenly
static const Double_t tdcThresh  = 1200.0;

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
		if ( Param[irun] >= 1 || ParamErr[irun] == 0 || Param[irun] < 0 || (ParamErr[irun]/Param[irun]) > 0.5)
		{
			g1->RemovePoint(irun);
		}
	}

}

//Add a method to Get Fit Parameters
void WriteFitParam(double c1[nPlanes][nBarsMax][nSides],double c2[nPlanes][nBarsMax][nSides], bool year)
{
  ofstream outParam;
  TString outPar_Name;
  if(year) {
  	outPar_Name = "hhodo_TWcalib_2021.param";
  }else{
  	outPar_Name = "hhodo_TWcalib_2022.param";  	
  }
  outParam.open(outPar_Name);
  outParam << ";HMS Hodoscopes Time Walk Output Parameter File: taken from average of many runs" << endl;
  outParam << " " << endl;
  outParam << "hTDC_threshold =" << tdcThresh << " ;units of mV" <<endl;          
  //outParam << "pTDC_threshold_scint  =" << tdcThresh_scint  << " ;units of mV" <<endl;
  //outParam << "pTDC_threshold_quartz =" << tdcThresh_quartz  << " ;units of mV" <<endl;
  outParam << " " << endl;

  /*
  //Fill 3D Par array
  for (UInt_t iplane=0; iplane < nPlanes; iplane++)
    {
      
      for (UInt_t iside=0; iside < nSides; iside++) {
	      

	for(UInt_t ipaddle = 0; ipaddle < nbars[iplane]; ipaddle++) {
	 
	  //c1[iplane][iside][ipaddle] = twFit[iplane][iside][ipaddle]->GetParameter("c_{1}");
	  //c2[iplane][iside][ipaddle] = twFit[iplane][iside][ipaddle]->GetParameter("c_{2}");
	  //chi2ndf[iplane][iside][ipaddle] =  twFit[iplane][iside][ipaddle]->GetChisquare()/twFit[iplane][iside][ipaddle]->GetNDF();

	} //end paddle loop

      } //end side loop
    
    } //end plane loop
	*/
  //Wrtie to Param FIle
   
  outParam << ";Param c1-Pos" << endl;
  outParam << "; " << setw(12) << "1x " << setw(15) << "1y " << setw(15) << "2x " << setw(15) << "2y " << endl;
  outParam << "hc1_Pos = ";
  //Loop over all paddles
  for(UInt_t ipaddle = 0; ipaddle < nBarsMax; ipaddle++) {
    //Write c1-Pos values
    if(ipaddle==0){
      outParam << c1[0][ipaddle][0] << ", " << setw(15) << c1[1][ipaddle][0] << ", "  << setw(15) << c1[2][ipaddle][0] << ", " << setw(15) << c1[3][ipaddle][0] << fixed << endl; 
    }
    else {
      outParam << setw(17) << c1[0][ipaddle][0] << ", " << setw(15) << c1[1][ipaddle][0] << ", "  << setw(15) << c1[2][ipaddle][0] << ", " << setw(15) << c1[3][ipaddle][0] << fixed << endl;    
    }
  } //end loop over paddles
  
  outParam << " " << endl;
  outParam << ";Param c1-Neg" << endl;
  outParam << "; " << setw(12) << "1x " << setw(15) << "1y " << setw(15) << "2x " << setw(15) << "2y " << endl;
  outParam << "hc1_Neg = ";                                                                                                                                                                            
  //Loop over all paddles
  for(UInt_t ipaddle = 0; ipaddle < nBarsMax; ipaddle++) { 
    //Write c1-Neg values
    if(ipaddle==0){
      outParam << c1[0][ipaddle][1] << ", " << setw(15) << c1[1][ipaddle][1] << ", "  << setw(15) << c1[2][ipaddle][1] << ", " << setw(15) << c1[3][ipaddle][1] << fixed << endl; 
    }
    else {
      outParam << setw(17) << c1[0][ipaddle][1] << ", " << setw(15) << c1[1][ipaddle][1] << ", "  << setw(15) << c1[2][ipaddle][1] << ", " << setw(15) << c1[3][ipaddle][1] << fixed << endl;
    }
} //end loop over paddles
  
  outParam << " " << endl;
  outParam << ";Param c2-Pos" << endl;
  outParam << "; " << setw(12) << "1x " << setw(15) << "1y " << setw(15) << "2x " << setw(15) << "2y " << endl;
  outParam << "hc2_Pos = ";                                                                                                                                                                            
  //Loop over all paddles
  for(UInt_t ipaddle = 0; ipaddle < nBarsMax; ipaddle++) { 
    //Write c2-Pos values
    if(ipaddle==0)
      {
	outParam << c2[0][ipaddle][0] << ", " << setw(15) << c2[1][ipaddle][0] << ", "  << setw(15) << c2[2][ipaddle][0] << ", " << setw(15) << c2[3][ipaddle][0] << fixed << endl; 
      }
    else {
      outParam << setw(17) << c2[0][ipaddle][0] << ", " << setw(15) << c2[1][ipaddle][0] << ", "  << setw(15) << c2[2][ipaddle][0] << ", " << setw(15) << c2[3][ipaddle][0] << fixed << endl;                                            
    }
  } //end loop over paddles
  
  outParam << " " << endl;
  outParam << ";Param c2-Neg" << endl;
  outParam << "; " << setw(12) << "1x " << setw(15) << "1y " << setw(15) << "2x " << setw(15) << "2y " << endl;
  outParam << "hc2_Neg = ";                                                                                                                                                                            
  //Loop over all paddles
  for(UInt_t ipaddle = 0; ipaddle < nBarsMax; ipaddle++) { 
    //Write c2-Neg values
    if (ipaddle==0){
      outParam << c2[0][ipaddle][1] << ", " << setw(15) << c2[1][ipaddle][1] << ", "  << setw(15) << c2[2][ipaddle][1] << ", " << setw(15) << c2[3][ipaddle][1] << fixed << endl; 
    }
    else{
      outParam << setw(17) << c2[0][ipaddle][1] << ", " << setw(15) << c2[1][ipaddle][1] << ", "  << setw(15) << c2[2][ipaddle][1] << ", " << setw(15) << c2[3][ipaddle][1] << fixed << endl;
    }
  } //end loop over paddles
  
  outParam.close();


} //end method

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
	
	Double_t Param1Out[2][nPlanes][nBarsMax][nSides]; // I've added 2 of these to store both 2021 and 2022
	Double_t Param1ErrOut[2][nPlanes][nBarsMax][nSides];
	
	Double_t Param2Out[2][nPlanes][nBarsMax][nSides]; 
	Double_t Param2ErrOut[2][nPlanes][nBarsMax][nSides];
	
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
				Param1Out[0][i][k][j] = 0.;
				Param1Out[1][i][k][j] = 0.;
				Param2Out[0][i][k][j] = 0.;
				Param2Out[1][i][k][j] = 0.;
			}
		}
	}
	
	
	TString fileName;
	
	//get from each run
	for(UInt_t irun = 0; irun < numRuns; irun++)
	{
		
		//get file
		fileName = Form("hhodo_TWcalib_Err_%.0f.param", runs[irun]); // may need to change this path though
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
	TF1	*Lin2021b[nSides][nPlanes][nBarsMax], *Lin2022b[nSides][nPlanes][nBarsMax]; 
	double mean1[2][nSides][nPlanes][nBarsMax], weight1[2][nSides][nPlanes][nBarsMax], mean2[2][nSides][nPlanes][nBarsMax], weight2[2][nSides][nPlanes][nBarsMax]; // for getting the weighted mean
	bool y1, y2, y3, y4;
	
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
				CompCanC2[iside][iplane]->Divide(4,4);
				CompCanC1[iside][iplane]->Divide(4,4);
			}else {
				CompCanC2[iside][iplane]->Divide(4,4);
				CompCanC1[iside][iplane]->Divide(4,4);
			}
			
			//for planes only run as much as is neccessary (13 in first two, 14 in 3rd one and 21 times in quartz
			for (UInt_t ibar = 0;(ibar < nBarsMax && !(iplane == 1 || iplane == 3)) || (ibar < 10) ; ibar++)
			{
				
				// make canvas
				CompCanC1[iside][iplane]->cd(ibar+1);
				CompCanC1[iside][iplane]->SetGrid();
				
				// fill then draw graph
				//CompGra[iside][iplane][ibar] = new TGraphErrors (numRuns, runs, Param1[iplane][ibar][iside], nullptr, Param1Err[iplane][ibar][iside]);
				CompGra[iside][iplane][ibar] = new TGraphErrors();
				CompGraC1[iside][iplane][ibar] = new TGraphErrors();
				
				Lin2021[iside][iplane][ibar] = new TF1 ("Const Fit 2021", "[0]", 11700, 14777);
				Lin2021[iside][iplane][ibar]->SetParLimits(0,0,0.6);
				Lin2021[iside][iplane][ibar]->SetParameter(0,0.3);
				Lin2022[iside][iplane][ibar] = new TF1 ("Const Fit 2022", "[0]", 14777, 17200);
				Lin2022[iside][iplane][ibar]->SetParLimits(0,0,0.6);
				Lin2022[iside][iplane][ibar]->SetParameter(0,0.3);
				
				Lin2021b[iside][iplane][ibar] = new TF1 ("Const Fit 2021", "[0]", 11700, 14777);
				Lin2021b[iside][iplane][ibar]->SetParLimits(0,12,27);
				Lin2021b[iside][iplane][ibar]->SetParameter(0,15);
				Lin2022b[iside][iplane][ibar] = new TF1 ("Const Fit 2022", "[0]", 14777, 17200);
				Lin2022b[iside][iplane][ibar]->SetParLimits(0,12,27);
				Lin2022b[iside][iplane][ibar]->SetParameter(0,15);
				
				mean1[0][iside][iplane][ibar] = 0.;
				mean1[1][iside][iplane][ibar] = 0.;
				mean2[0][iside][iplane][ibar] = 0.;
				mean2[1][iside][iplane][ibar] = 0.;
				weight1[0][iside][iplane][ibar] = 0.;
				weight1[1][iside][iplane][ibar] = 0.;
				weight2[0][iside][iplane][ibar] = 0.;
				weight2[1][iside][iplane][ibar] = 0.;
				
				//int *toRemove = new int[numRuns];
				int ipoint = 0;
				y1 = false; // markers for average
				y2 = false;
				y3 = false;
				y4 = false;
				for (UInt_t irun = 0; irun < numRuns; irun++)
				{
					//C2 fill, yes I know retrofitting is hard okay
					if ((( Param1[iplane][ibar][iside][irun] >= 1 || Param1Err[iplane][ibar][iside][irun] == 0 || Param1[iplane][ibar][iside][irun] < 0 || (TMath::Abs(Param1Err[iplane][ibar][iside][irun]/Param1[iplane][ibar][iside][irun]) > 0.3) ) && !( Param1[iplane][ibar][iside][irun] == 0 && Param1Err[iplane][ibar][iside][irun] == 0 )) || runs[irun] == 0 || TMath::IsNaN(Param1Err[iplane][ibar][iside][irun]) || TMath::IsNaN(Param1[iplane][ibar][iside][irun]))
					{
						if(DEBUGMODE){
							cout << "Removing C2 Point From plane " << iplane+1 << ", side " << sideNames[iside] << ", bar " << ibar+1 << ", run " << runs[irun] << "\n";
							cout << "Values: x = " << runs[irun] << ", y = " << Param1[iplane][ibar][iside][irun] << ", yerr = " << Param1Err[iplane][ibar][iside][irun] << '\n';
						}
						//if (!CompGra[iside][iplane][ibar]->RemovePoint(irun)) cout << "failed!!!\n";
						//toRemove[irun] = irun;
					}else{
						//toRemove[irun] = 0;
						CompGra[iside][iplane][ibar]->AddPoint(runs[irun],Param1[iplane][ibar][iside][irun]);
						CompGra[iside][iplane][ibar]->SetPointError(ipoint,0, Param1Err[iplane][ibar][iside][irun]);
						if(runs[irun] < 14777){
							if(y1){
								mean1[0][iside][iplane][ibar] = mean1[0][iside][iplane][ibar] + Param1[iplane][ibar][iside][irun]*Param1Err[iplane][ibar][iside][irun];
								weight1[0][iside][iplane][ibar] = weight1[0][iside][iplane][ibar] + Param1Err[iplane][ibar][iside][irun];
							}else{
								mean1[0][iside][iplane][ibar] = Param1[iplane][ibar][iside][irun]*Param1Err[iplane][ibar][iside][irun];
								weight1[0][iside][iplane][ibar] = Param1Err[iplane][ibar][iside][irun];
								y1 = true;
							}
						}else{
							if(y2){
								mean1[1][iside][iplane][ibar] = mean1[1][iside][iplane][ibar] + Param1[iplane][ibar][iside][irun]*Param1Err[iplane][ibar][iside][irun];
								weight1[1][iside][iplane][ibar] = weight1[1][iside][iplane][ibar] + Param1Err[iplane][ibar][iside][irun];
							}else{
								mean1[1][iside][iplane][ibar] = Param1[iplane][ibar][iside][irun]*Param1Err[iplane][ibar][iside][irun];
								weight1[1][iside][iplane][ibar] = Param1Err[iplane][ibar][iside][irun];
								y2 = true;
							}
						}
						ipoint++;
					}
				}
				ipoint = 0;
				for(UInt_t irun = 0; irun < numRuns; irun++)
				{
					//C1 fill, yes I know retrofitting is hard okay
					if ( (( Param2Err[iplane][ibar][iside][irun] == 0 || Param2[iplane][ibar][iside][irun] < 10 || Param2[iplane][ibar][iside][irun] > 30 || (TMath::Abs(Param2Err[iplane][ibar][iside][irun]/Param2[iplane][ibar][iside][irun]) > 0.4) ) && !(Param2[iplane][ibar][iside][irun] == 0 && Param2Err[iplane][ibar][iside][irun] == 0 && (Param2[iplane][ibar][iside][irun+1] == 0 || Param2[iplane][ibar][iside][irun-1] == 0)) ) || runs[irun] == 0 || TMath::IsNaN(Param2Err[iplane][ibar][iside][irun]) || TMath::IsNaN(Param2[iplane][ibar][iside][irun]))
					{
						if(DEBUGMODE){
							cout << "Removing C1 Point From plane " << iplane+1 << ", side " << sideNames[iside] << ", bar " << ibar+1 << ", run " << runs[irun] << "\n";
							cout << "Values: x = " << runs[irun] << ", y = " << Param2[iplane][ibar][iside][irun] << ", yerr = " << Param2Err[iplane][ibar][iside][irun] << '\n';
						}
						//if (!CompGra[iside][iplane][ibar]->RemovePoint(irun)) cout << "failed!!!\n";
						//toRemove[irun] = irun;
					}else{
						//toRemove[irun] = 0;
						CompGraC1[iside][iplane][ibar]->AddPoint(runs[irun],Param2[iplane][ibar][iside][irun]);
						CompGraC1[iside][iplane][ibar]->SetPointError(ipoint,0, Param2Err[iplane][ibar][iside][irun]);
						if(runs[irun] < 14777){
							if(y3){
								mean2[0][iside][iplane][ibar] = mean2[0][iside][iplane][ibar] + Param2[iplane][ibar][iside][irun]*Param2Err[iplane][ibar][iside][irun];
								weight2[0][iside][iplane][ibar] = weight2[0][iside][iplane][ibar] + Param2Err[iplane][ibar][iside][irun];
							}else{
								mean2[0][iside][iplane][ibar] = Param2[iplane][ibar][iside][irun]*Param2Err[iplane][ibar][iside][irun];
								weight2[0][iside][iplane][ibar] = Param2Err[iplane][ibar][iside][irun];
								y3 = true;
							}
						}else{
							if(y4){
								mean2[1][iside][iplane][ibar] = mean2[1][iside][iplane][ibar] + Param2[iplane][ibar][iside][irun]*Param2Err[iplane][ibar][iside][irun];
								weight2[1][iside][iplane][ibar] = weight2[1][iside][iplane][ibar] + Param2Err[iplane][ibar][iside][irun];
							}else{
								mean2[1][iside][iplane][ibar] = Param2[iplane][ibar][iside][irun]*Param2Err[iplane][ibar][iside][irun];
								weight2[1][iside][iplane][ibar] = Param2Err[iplane][ibar][iside][irun];
								y4 = true;
							}
						}
						ipoint++;
					}
				}
				//for(UInt_t irun = numRuns; irun < 0; irun++){
				//	if (!CompGra[iside][iplane][ibar]->RemovePoint(irun)) cout << "failed to remove run " << runs[irun] << "!!!\n";
				//}
				
				// calculate weighted average of the functions
				mean1[0][iside][iplane][ibar] = mean1[0][iside][iplane][ibar]/weight1[0][iside][iplane][ibar];
				mean1[1][iside][iplane][ibar] = mean1[1][iside][iplane][ibar]/weight1[1][iside][iplane][ibar];
				mean2[0][iside][iplane][ibar] = mean2[0][iside][iplane][ibar]/weight2[0][iside][iplane][ibar];
				mean2[1][iside][iplane][ibar] = mean2[1][iside][iplane][ibar]/weight2[1][iside][iplane][ibar];
				//cout << weight2[0][iside][iplane][ibar] << "\n";
				
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
				
				//cout << "********************************************************\nFitting From plane " << iplane+1 << ", side " << sideNames[iside] << ", bar " << ibar+1 << "\n:";
				CompGra[iside][iplane][ibar]->Fit(Lin2021[iside][iplane][ibar], "R+", "SAME");
				CompGra[iside][iplane][ibar]->Fit(Lin2022[iside][iplane][ibar], "R+", "SAME");
				//Lin2021[iside][iplane][ibar]->SetParameter(0, mean1[0][iside][iplane][ibar]);
				//Lin2022[iside][iplane][ibar]->SetParameter(0, mean1[1][iside][iplane][ibar]);
				
				Param2Out[0][iplane][ibar][iside] = Lin2021[iside][iplane][ibar]->GetParameter(0);
				Param2Out[1][iplane][ibar][iside] = Lin2022[iside][iplane][ibar]->GetParameter(0);
				
				if( Param2Out[0][iplane][ibar][iside] < 0.05 || Param2Out[0][iplane][ibar][iside] > 1) Param2Out[0][iplane][ibar][iside] = 0;
				if( Param2Out[1][iplane][ibar][iside] < 0.05 || Param2Out[1][iplane][ibar][iside] > 1) Param2Out[1][iplane][ibar][iside] = 0;
				
				Lin2021[iside][iplane][ibar]->Draw("SAME");
				Lin2022[iside][iplane][ibar]->Draw("SAME");
				
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
				
				CompGraC1[iside][iplane][ibar]->Fit(Lin2021b[iside][iplane][ibar], "R+", "SAME");
				CompGraC1[iside][iplane][ibar]->Fit(Lin2022b[iside][iplane][ibar], "R+", "SAME");
				//Lin2021b[iside][iplane][ibar]->SetParameter(0, mean2[0][iside][iplane][ibar]);
				//Lin2022b[iside][iplane][ibar]->SetParameter(0, mean2[1][iside][iplane][ibar]);
				
				Param1Out[0][iplane][ibar][iside] = Lin2021b[iside][iplane][ibar]->GetParameter(0);
				Param1Out[1][iplane][ibar][iside] = Lin2022b[iside][iplane][ibar]->GetParameter(0);
				
				if( Param1Out[0][iplane][ibar][iside] < 1 || Param1Out[0][iplane][ibar][iside] > 30) Param1Out[0][iplane][ibar][iside] = 0.;
				if( Param1Out[1][iplane][ibar][iside] < 1 || Param1Out[1][iplane][ibar][iside] > 30) Param1Out[1][iplane][ibar][iside] = 0.;
				
				Lin2021b[iside][iplane][ibar]->Draw("SAME");
				Lin2022b[iside][iplane][ibar]->Draw("SAME");
				
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
	
	// check for nonsense in the pmts that don't exist 
	for(int iplane = 10; iplane < nPlanes; iplane++){
		for(int ibar = 1; ibar < nBarsMax; ibar = ibar + 2){ 
			for(int iside = 0; iside < nSides; iside++){
				if( Param2Out[0][iplane][ibar][iside] < 0.05 || Param2Out[0][iplane][ibar][iside] > 1) Param2Out[0][iplane][ibar][iside] = 0.0;
				if( Param2Out[1][iplane][ibar][iside] < 0.05 || Param2Out[1][iplane][ibar][iside] > 1) Param2Out[1][iplane][ibar][iside] = 0.;
				if( Param1Out[0][iplane][ibar][iside] < 1 || Param1Out[0][iplane][ibar][iside] > 30) Param1Out[0][iplane][ibar][iside] = 0.;
				if( Param1Out[1][iplane][ibar][iside] < 1 || Param1Out[1][iplane][ibar][iside] > 30) Param1Out[1][iplane][ibar][iside] = 0.;
			}
		}
	}
	WriteFitParam(Param1Out[0], Param2Out[0], 0);
	WriteFitParam(Param1Out[1], Param2Out[1], 1);
	
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






