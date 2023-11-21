/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   SIdealNPdf.cpp
 * Author: petrstepanov
 *
 * Created on November 9, 2016, 7:49 PM
 */

#include "SIdealNPdf.h"
#include "../utils/MathematicaAliases.h"
//#include <iostream>

ClassImp(SIdealNPdf);

SIdealNPdf::SIdealNPdf(const char *name, const char *title, RooAbsReal& _x, RooAbsReal& _Q1, RooAbsReal& _s1, RooAbsReal& _n) :
		RooAbsPdf(name, title), x("x", "x", this, _x), Q1("Q1", "Q1", this, _Q1), s1("s1", "s1", this, _s1), n("n", "n", this, _n) {
}

SIdealNPdf::SIdealNPdf(const SIdealNPdf& other, const char* name) :
		RooAbsPdf(other, name), x("x", this, other.x), Q1("Q1", this, other.Q1), s1("s1", this, other.s1), n("n", this, other.n) {
}

// Doing not normalized!
Double_t SIdealNPdf::evaluate() const {
	Double_t value = // begin mathematica code from "/mathematica/RooFit/SidealN-pdf-not-norm.nb"
			Power(E,-Power(-(n*Q1) + x,2)/(2.*n*Power(s1,2)))
	; // end mathematica code
	return value;
}

Double_t SIdealNPdf::indefiniteIntegral(Double_t x) const {
	Double_t value =  // begin mathematica code from "/mathematica/SidealN.nb"
			Sqrt(n)*Sqrt(Pi/2.)*s1*Erf((-(n*Q1) + x)/(Sqrt(2)*Sqrt(n)*s1))
	; // end mathematica code
	return value;
}

// Get analytical integral
Int_t SIdealNPdf::getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* rangeName) const {
	if (matchArgs(allVars, analVars, x))
		return 1;
	return 0;
}

// Analytical integral
Double_t SIdealNPdf::analyticalIntegral(Int_t code, const char* rangeName) const {
	assert(code == 1);

	if (code == 1) {
		Double_t x1 = x.min(rangeName);
		Double_t x2 = x.max(rangeName);
		return indefiniteIntegral(x2) - indefiniteIntegral(x1);
	}
	std::cout << "Error in SIdealNPdf::analyticalIntegral" << std::endl;
	return 0;
}
