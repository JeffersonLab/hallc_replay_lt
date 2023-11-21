/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   BPdf.cpp
 * Author: petrstepanov
 *
 * Created on November 9, 2016, 7:49 PM
 */

#include "BPdf.h"
#include "../utils/MathematicaAliases.h"
//#include <iostream>

ClassImp(BPdf);

BPdf::BPdf(const char *name, const char *title, RooAbsReal& _x, RooAbsReal& _Q0, RooAbsReal& _s0, RooAbsReal& _w, RooAbsReal& _a) :
		RooAbsPdf(name, title), x("x", "x", this, _x), Q0("Q0", "Q0", this, _Q0), s0("s0", "s0", this, _s0), w("w", "w", this, _w), a("a", "a", this, _a) {
}

BPdf::BPdf(const BPdf& other, const char* name) :
		RooAbsPdf(other, name), x("x", this, other.x), Q0("Q0", this, other.Q0), s0("s0", this, other.s0), w("w", this, other.w), a("a", this, other.a) {
}

// Doing like rooexponential
Double_t BPdf::evaluate() const {
	Double_t value = // begin mathematica code from "/mathematica/B-shifted.nb"
			(1 - w)/(Power(E,Power(-Q0 + x,2)/(2.*Power(s0,2)))*Sqrt(2*Pi)*s0) + (a*w*UnitStep(-Q0 + x))/Power(E,a*(-Q0 + x))
	; // end mathematica code
	return value;
}

Double_t BPdf::indefiniteIntegralBeforeQ0(Double_t x) const {
	Double_t value =  // begin mathematica code from "/mathematica/B-shifted.nb"
			((-1 + w)*Erf((Q0 - x)/(Sqrt(2)*s0)))/2.
	; // end mathematica code
	return value;
}

Double_t BPdf::indefiniteIntegralAfterQ0(Double_t x) const {
	Double_t value =  // begin mathematica code from "/mathematica/B-shifted.nb"
			((-1 + w)*Erf((Q0 - x)/(Sqrt(2)*s0)))/2. + (w - Power(E,a*Q0 - a*x)*w)
	; // end mathematica code
	return value;
}

// Get analytical integral
Int_t BPdf::getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* rangeName) const {
	if (matchArgs(allVars, analVars, x))
		return 1;
	return 0;
}

// Analytical integral
Double_t BPdf::analyticalIntegral(Int_t code, const char* rangeName) const {
	assert(code == 1);

	if (code == 1) {
		Double_t x1 = x.min(rangeName);
		Double_t x2 = x.max(rangeName);

		if (x2 < Q0){
			return indefiniteIntegralBeforeQ0(x2) - indefiniteIntegralBeforeQ0(x1);
		}
		else if (x1 < Q0 && x2 >= Q0){
			// Special case here - function is not monotone
			Double_t integral = 0;
			integral += indefiniteIntegralBeforeQ0(Q0) - indefiniteIntegralBeforeQ0(x1);
			integral += indefiniteIntegralAfterQ0(x2) - indefiniteIntegralAfterQ0(Q0);
			return integral;
		}
		// x1 >= Q0
		return indefiniteIntegralAfterQ0(x2) - indefiniteIntegralAfterQ0(x1);
	}
	std::cout << "Error in BPdf::analyticalIntegral" << std::endl;
	return 0;
}
