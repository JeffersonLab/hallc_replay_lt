/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   ExpPdf.cpp
 * Author: petrstepanov
 *
 * Created on November 9, 2016, 7:49 PM
 */

#include "ExpPdf.h"
//#include <iostream>

ClassImp(ExpPdf);

ExpPdf::ExpPdf(const char *name, const char *title, RooAbsReal& _x, RooAbsReal& _Q0, RooAbsReal& _a) :
		RooAbsPdf(name, title), x("x", "x", this, _x), Q0("Q0", "Q0", this, _Q0), a("a", "a", this, _a) {
}

ExpPdf::ExpPdf(const ExpPdf& other, const char* name) :
		RooAbsPdf(other, name), x("x", this, other.x), Q0("Q0", this, other.Q0), a("a", this, other.a) {
}

// Doing like rooexponential
Double_t ExpPdf::evaluate() const {
	if (x < Q0) return 0;
	return exp(-a*(x - Q0));
}

Double_t ExpPdf::indefiniteIntegral(Double_t x) const {
	if (x < Q0) return 0;
	return exp(-a*(x - Q0))/-a;
}

// Get analytical integral
Int_t ExpPdf::getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* rangeName) const {
	if (matchArgs(allVars, analVars, x))
		return 1;
	return 0;
}

// Analytical integral
Double_t ExpPdf::analyticalIntegral(Int_t code, const char* rangeName) const {
	assert(code == 1);

	if (code == 1) {
		Double_t x1 = x.min(rangeName);
		Double_t x2 = x.max(rangeName);
		if (x2 <= Q0) return 0;
		x1 = TMath::Max(Q0, x1);
		return indefiniteIntegral(x2) - indefiniteIntegral(x1);
	}
	std::cout << "Error in ExpPdf::analyticalIntegral" << std::endl;
	return 0;
}
