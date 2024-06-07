/*
 * FuncSRealFFT.cpp
 *
 *  Created on: Aug 2, 2020
 *      Author: petrstepanov
 */

#include "FuncSRealFFT.h"
#include "../model/Constants.h"
#include "../utils/MathematicaAliases.h"
#include <TF1Convolution.h>
#include <TMath.h>
#include <TDatime.h>
#include "components/FuncB.h"
#include "components/FuncSIdealN.h"
#include "components/FuncTerm0.h"
#include "components/FuncTermN.h"

FuncSRealFFT::FuncSRealFFT(TH1* h, Int_t nParVal) : AbsComponentFunc(), hist(h), nPar(nParVal) {
	// Init TF1 finctions used to cunstruct the final fitting function
	Double_t xMin = hist->GetXaxis()->GetXmin();
	Double_t xMax = hist->GetXaxis()->GetXmax();
	// Instantiate TF1 from a member function of a general C++ class
	// https://root.cern.ch/doc/master/classTF1.html#F6
	// Since fitting functions are defined in the same class, we are passing this pointer
	// TODO: is this ok that we are passing more variables than needed for bg and termN?
	TDatime* timestamp = new TDatime();
	Int_t nPx = Constants::N_PX;

	// Instantiate terms of the real FuncSRealFFT
	// Zero term has an uncertainty. Its approximate value is taken from (10)
	FuncTerm0* funcTerm0 = new FuncTerm0();
	TString term0Name = TString::Format("term0_%d", timestamp->Get());
	TF1* term0 = new TF1(term0Name.Data(), funcTerm0, &FuncTerm0::func, xMin, xMax, nPar, "FuncTerm0", "func");
	// https://root-forum.cern.ch/t/why-is-my-integral-zero/21999/4
	term0->SetNpx(nPx);
	components->Add(term0);

	// Terms 1..N are background function covoluted wit the Ideal FuncSRealFFT function
	FuncB* funcB = new FuncB();
	TString bName = TString::Format("b_%d", timestamp->Get());
	TF1* b = new TF1(bName.Data(), funcB, &FuncB::func, xMin, xMax, nPar, "FuncB", "func");
	// https://root-forum.cern.ch/t/why-is-my-integral-zero/21999/4
	b->SetNpx(nPx);

	Int_t nMax = Constants::getInstance()->parameters.termsNumber;
	for (UInt_t n=1; n < nMax; n++){
		FuncSIdealN* funcSIdealN = new FuncSIdealN(n);
		TString sIdealNName = TString::Format("sIdeal%d_%d", n, timestamp->Get());
		TF1* sIdealN = new TF1(sIdealNName.Data(), funcSIdealN, &FuncSIdealN::func, xMin, xMax, nPar, "FuncSIdealN", "func");
		sIdealN->SetNpx(nPx);

		TF1Convolution* conv = new TF1Convolution(sIdealN, b, xMin, xMax);
		// conv->SetExtraRange(0.5); // Screws up everything
		// conv->SetNumConv(kTRUE);
		// conv->SetRange(xMin, xMax);
		conv->SetNofPointsFFT(Constants::getInstance()->parameters.convolutionBins);
		TString termNName = TString::Format("term%d_%d", n, timestamp->Get());
		TF1 *termN = new TF1(termNName.Data(),*conv, xMin, xMax, conv->GetNpar());
		termN->SetNpx(nPx);

		components->Add(termN);
	}

	// Initialize coeficient formula
	TString formulaName = TString::Format("formula_%d", timestamp->Get());
	coefficientN = new TFormula(formulaName.Data(), "[mu]^[n]*e^(-[mu])/TMath::Factorial([n])");
}

FuncSRealFFT::~FuncSRealFFT() {
}

Double_t FuncSRealFFT::func(Double_t* _x, Double_t* par) {
	// Parameters
	Double_t Q0 = par[0];		// average charge at the PM output
	Double_t s0 = par[1];		// standard deviation of the type I background process
	Double_t Q1 = par[2];		// average charge at the PM output
	Double_t s1 = par[3];		// corresponding standard deviation of the charge distribution
	Double_t w  = par[4];		// probability that signal is accompanied by type II background process
	Double_t a  = par[5];		// coefficient of the exponential decrease of the type II background
	Double_t mu = par[6];		// number of photo-electrons

	Double_t parForConvolution[] = {Q0, s0, Q1, s1, w, a, mu, Q0, s0, Q1, s1, w, a, mu};

	// Set component parameters

	// Loop over components
	Double_t value = 0;
	Double_t integral = 0;
	Int_t xMin = hist->GetXaxis()->GetXmin();
	Int_t xMax = hist->GetXaxis()->GetXmax();

	// Extend the integration range
	// Double_t bufferFraction = 1.5;
	// Double_t delta = (xMax - xMin)*(bufferFraction - 1);
	// xMin = xMin - delta;
	// xMax = xMax + delta;

	// Evaluate sum coeficients for the last term
	for (UInt_t n = 0; n <= components->LastIndex(); n++){
		TF1* component = (TF1*)(components->At(n));
		if (component){
			// Set parameters
		    if (n==0) component->SetParameters(par);
		    else component->SetParameters(parForConvolution);

		    // Calculate term coefficient
		    Double_t coeffParams[2] = {mu, (Double_t)n};
		    Double_t coefficient = coefficientN->EvalPar(nullptr, coeffParams);

		    // Add component contribution
			if (n==0) value += coefficient*component->EvalPar(_x, par);
			else value += coefficient*component->EvalPar(_x, parForConvolution);

			// Sum the total integral
//			if (n==0){
//				// Step function in the Pedestal requires custom analytical integral
//				FuncTerm0* ft0 = new FuncTerm0();
//				Double_t myIntegral = ft0->getIntegral(xMin, xMax, par);
//				// Double_t rootIntegral = component->Integral(xMin, xMax);
//				// std::cout << "n=" << n<< ". myIntegral: " << myIntegral << "\t rootIntegral: " << rootIntegral << std::endl;
//				integral+= myIntegral;
//			}
//			else {
//				// Integral of the real convoluted term is ~ as unconvoluted term shifted to Q0 (analytical)
//				FuncSIdealNShiftedQ0* fSIdealNShiftedQ0 = new FuncSIdealNShiftedQ0(n);
//				Double_t myIntegral = fSIdealNShiftedQ0->getIntegral(xMin, xMax, par);
//				// Double_t rootIntegral = component->Integral(xMin, xMax);
//				// std::cout  << "n=" << n<< ". myIntegral: " << myIntegral << "\t rootIntegral: " << rootIntegral << std::endl;
//				integral+= myIntegral;
//			}
			// Regular integral tekes forever
			// integral += component->Integral(xMin, xMax, 1e-3);
		} else {
			std::cout << "Error getting the component" << std::endl;
		}
	}

	// Return function value
	// return value/integral*(hist->Integral());
	return value*(hist->Integral())*(hist->GetXaxis()->GetBinWidth(1));
}

