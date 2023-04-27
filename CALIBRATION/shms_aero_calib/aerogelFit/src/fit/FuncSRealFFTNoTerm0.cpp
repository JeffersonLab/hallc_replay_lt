/*
 * FuncSRealFFTNoTerm0.cpp
 *
 *  Created on: Aug 2, 2020
 *      Author: petrstepanov
 */

#include "FuncSRealFFTNoTerm0.h"
#include "../model/Constants.h"
#include "../utils/MathematicaAliases.h"
#include <TF1Convolution.h>
#include <TMath.h>
#include <TDatime.h>
#include "./components/FuncB.h"
#include "./components/FuncSIdealN.h"
#include "./components/FuncTerm0.h"

FuncSRealFFTNoTerm0::FuncSRealFFTNoTerm0(TH1* h, Int_t nParVal) : AbsComponentFunc(), hist(h), nPar(nParVal) {
	// Init TF1 finctions used to cunstruct the final fitting function
	Double_t xMin = hist->GetXaxis()->GetXmin();
	Double_t xMax = hist->GetXaxis()->GetXmax();
	// Instantiate TF1 from a member function of a general C++ class
	// https://root.cern.ch/doc/master/classTF1.html#F6
	// Since fitting functions are defined in the same class, we are passing this pointer
	// TODO: is this ok that we are passing more variables than needed for bg and termN?
	TDatime* timestamp = new TDatime();
	Int_t nPx = Constants::N_PX;

	// Terms 1..N are background function covoluted wit the Ideal FuncSRealFFTNoTerm0 function
	FuncB* funcB = new FuncB();
	TString bName = TString::Format("b_%d", timestamp->Get());
	TF1* b = new TF1(bName.Data(), funcB, &FuncB::func, xMin, xMax, nPar, "FuncB", "func");
	b->SetNpx(nPx);

	Int_t nMax = Constants::getInstance()->parameters.termsNumber;
	for (UInt_t n=1; n < nMax; n++){
		FuncSIdealN* funcSIdealN = new FuncSIdealN(n);
		TString sIdealNName = TString::Format("sIdeal%d_%d", n, timestamp->Get());
		TF1* sIdealN = new TF1(sIdealNName.Data(), funcSIdealN, &FuncSIdealN::func, xMin, xMax, nPar, "FuncSIdealN", "func");
		sIdealN->SetNpx(nPx);

		TF1Convolution* conv = new TF1Convolution(sIdealN, b, xMin, xMax);
		conv->SetNofPointsFFT(Constants::getInstance()->parameters.convolutionBins);
		TString termNName = TString::Format("term%d_%d", n, timestamp->Get());
		TF1 *termN = new TF1(termNName.Data(),*conv, xMin, xMax, conv->GetNpar());
		termN->SetNpx(nPx);

		components->Add(termN);
	}

	// Initialize coeficient formula
	TString formulaName = TString::Format("formula_%d", timestamp->Get());
 	coefficientN = new TFormula(formulaName.Data(), "TMath::Power([mu],[n]+1)*TMath::Exp(-[mu])/TMath::Factorial([n]+1)/(1-TMath::Exp(-[mu]))");
}

FuncSRealFFTNoTerm0::~FuncSRealFFTNoTerm0() {
}

Double_t FuncSRealFFTNoTerm0::func(Double_t* _x, Double_t* par) {
	// Parameters
	Double_t Q0 = par[0];		// average charge at the PM output
	Double_t s0 = par[1];		// standard deviation of the type I background process
	Double_t Q1 = par[2];		// average charge at the PM output
	Double_t s1 = par[3];		// corresponding standard deviation of the charge distribution
	Double_t w  = par[4];		// probability that signal is accompanied by type II background process
	Double_t a  = par[5];		// coefficient of the exponential decrease of the type II background
	Double_t mu = par[6];		// number of photo-electrons

	Double_t parForConvolution[] = {Q0, s0, Q1, s1, w, a, mu, Q0, s0, Q1, s1, w, a, mu};

	// Loop over components
	Double_t value = 0;
	Int_t xMin = hist->GetXaxis()->GetXmin();
	Int_t xMax = hist->GetXaxis()->GetXmax();

	for (UInt_t n = 0; n <= components->LastIndex(); n++){
		TF1* component = (TF1*)(components->At(n));
		if (component){
			// Set parameters
		    component->SetParameters(parForConvolution);

		    // Calculate term coefficient
		    Double_t coeffParams[2] = {mu, (Double_t)n};
		    Double_t coefficient = coefficientN->EvalPar(nullptr, coeffParams);

		    // Add component contribution
			value += coefficient*component->EvalPar(_x, parForConvolution);

		} else {
			std::cout << "Error getting the component" << std::endl;
		}
	}

	return value*(hist->Integral())*(hist->GetXaxis()->GetBinWidth(1));
}
