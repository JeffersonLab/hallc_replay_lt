/*
 * SpectrumReal.cpp
 *
 *  Created on: Aug 2, 2020
 *      Author: petrstepanov
 */

#include "SpectrumReal.h"
#include "../model/Constants.h"
#include "../utils/MathematicaAliases.h"
#include <TMath.h>

SpectrumReal::SpectrumReal(Double_t histIntegralVal, Int_t xMinVal, Int_t xMaxVal, Int_t nMaxVal) :
	nMax(nMaxVal), xMin(xMinVal), xMax(xMaxVal), histIntegral(histIntegralVal), pi(TMath::Pi()), e(TMath::E()) {
	// Initialize parameters as RooRealVars even though we're not using RooFit
	// Convenient because RooRealVar has name, value and limits
	// Parameter values taken from Fig.2, https://doi.org/10.1016/0168-9002(94)90183-X
	RooRealVar* Q0 = new RooRealVar("Q_{0}", "pedestal", 23.26, 10, 40, "e");
	RooRealVar* s0 = new RooRealVar("#sigma_{0}", "standard deviation of the type I background process", 0.192, 0.1, 10, "");
	RooRealVar* Q1 = new RooRealVar("Q_{1}", "average charge at the PM output", 35.04, 0, 100, "e");
	RooRealVar* s1 = new RooRealVar("#sigma_{1}", "corresponding standard deviation of the charge distribution", 11.73, 5, 50, "");
	RooRealVar* w  = new RooRealVar("w", "probability that signal is accompanied by type II background process", 0.4, 0.1, 1, "");
	RooRealVar* a  = new RooRealVar("#alpha", "coefficient of the exponential decrease of the type II background", 0.034, 0, 0.1, "");
	RooRealVar* mu = new RooRealVar("#mu", "number of photo-electrons", 1.68, 0, 20, "");
	parameters->add(*Q0);
	parameters->add(*s0);
	parameters->add(*Q1);
	parameters->add(*s1);
	parameters->add(*w);
	parameters->add(*a);
	parameters->add(*mu);
}

SpectrumReal::~SpectrumReal() {
}

RooArgList* SpectrumReal::parameters = new RooArgList();

// TH1::Fit - fitting function should be normalized
// https://root-forum.cern.ch/t/root-fit-unbindata-example-is-not-working/28462

Double_t SpectrumReal::realDefIntSimpson(Double_t* par){
	// Parameters:
	Double_t Q0 = par[0];		// average charge at the PM output
	Double_t s0 = par[1];		// standard deviation of the type I background process
	Double_t Q1 = par[2];		// average charge at the PM output
	Double_t s1 = par[3];		// corresponding standard deviation of the charge distribution
	Double_t w  = par[4];		// probability that signal is accompanied by type II background process
	Double_t a  = par[5];		// coefficient of the exponential decrease of the type II background
	Double_t mu = par[6];		// number of photo-electrons

	Double_t integral = 0;

	for (Int_t i = xMin; i < xMax; i++){
		Double_t x = i + 0.5;
		integral += // begin mathematica code from "/mathematica/term2.nb"
				((1 - w)/(Power(E,Power(-Q0 + x,2)/(2.*Power(s0,2)))*Sqrt(2*Pi)*s0) +
				     (a*w*UnitStep(-Q0 + x))/Power(E,a*(-Q0 + x)))/Power(E,mu)
		; // end mathematica code

		// Other terms
		for (Int_t n = 1; n <= nMax; n++){
			integral += // begin mathematica code from "/mathematica/term2.nb"
					(Power(mu,n)*((1 - w)/
					        (Power(E,Power(-Q0 - n*Q1 + x,2)/(2.*n*Power(s1,2)))*
					          Sqrt(n)*Sqrt(2*Pi)*s1) +
					       (a*w*(Erf(Abs(-(n*Q1) - a*n*Power(s1,2))/
					              (Sqrt(2)*Sqrt(n)*s1)) +
					            Erf(Abs(-Q0 - n*Q1 - a*n*Power(s1,2) + x)/
					               (Sqrt(2)*Sqrt(n)*s1))*
					             Sign(-Q0 - n*Q1 - a*n*Power(s1,2) + x)))/
					        (2.*Power(E,a*(-Q0 - n*Q1 - a*n*Power(s1,2) + x)))))/
					   (Power(E,mu)*Factorial(n))
			; // end mathematica code
		}
	}
	return integral;
}

Double_t SpectrumReal::func(Double_t* _x, Double_t* par) {
	Double_t x = _x[0];

	// Parameters:
	Double_t Q0 = par[0];		// average charge at the PM output
	Double_t s0 = par[1];		// standard deviation of the type I background process
	Double_t Q1 = par[2];		// average charge at the PM output
	Double_t s1 = par[3];		// corresponding standard deviation of the charge distribution
	Double_t w  = par[4];		// probability that signal is accompanied by type II background process
	Double_t a  = par[5];		// coefficient of the exponential decrease of the type II background
	Double_t mu = par[6];		// number of photo-electrons

	Double_t sum = 0;

	// Zero term
	sum +=  // begin mathematica code from "/mathematica/term2.nb"
			((1 - w)/(Power(E,Power(-Q0 + x,2)/(2.*Power(s0,2)))*Sqrt(2*Pi)*s0) +
			     (a*w*UnitStep(-Q0 + x))/Power(E,a*(-Q0 + x)))/Power(E,mu)
	; // end mathematica code

	// Other terms
	for (Int_t n = 1; n <= nMax; n++){
		sum += // begin mathematica code from "/mathematica/term2.nb"
				(Power(mu,n)*((1 - w)/
				        (Power(E,Power(-Q0 - n*Q1 + x,2)/(2.*n*Power(s1,2)))*
				          Sqrt(n)*Sqrt(2*Pi)*s1) +
				       (a*w*(Erf(Abs(-(n*Q1) - a*n*Power(s1,2))/
				              (Sqrt(2)*Sqrt(n)*s1)) +
				            Erf(Abs(-Q0 - n*Q1 - a*n*Power(s1,2) + x)/
				               (Sqrt(2)*Sqrt(n)*s1))*
				             Sign(-Q0 - n*Q1 - a*n*Power(s1,2) + x)))/
				        (2.*Power(E,a*(-Q0 - n*Q1 - a*n*Power(s1,2) + x)))))/
				   (Power(E,mu)*Factorial(n))
		; // end mathematica code
	}

	Double_t defIntegral = realDefIntSimpson(par); //realDefInt(par);
	return sum/defIntegral*histIntegral;
}

