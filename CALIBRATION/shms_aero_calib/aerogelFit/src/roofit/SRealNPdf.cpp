/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   SRealNPdf.cpp
 * Author: petrstepanov
 *
 * Created on November 9, 2016, 7:49 PM
 */

#include "SRealNPdf.h"
#include "../utils/MathematicaAliases.h"
//#include <iostream>

ClassImp(SRealNPdf);

SRealNPdf::SRealNPdf(const char *name, const char *title, RooAbsReal& _x, RooAbsReal& _Q0, RooAbsReal& _Q1, RooAbsReal& _s1, RooAbsReal& _w, RooAbsReal& _a, RooAbsReal& _mu, RooAbsReal& _n) :
		RooAbsPdf(name, title), x("x", "x", this, _x), Q0("Q0", "Q0", this, _Q0), Q1("Q1", "Q1", this, _Q1), s1("s1", "s1", this, _s1), w("w", "w", this, _w), a("a", "a", this, _a), mu("mu", "mu", this, _mu), n("n", "n", this, _n) {
}

SRealNPdf::SRealNPdf(const SRealNPdf& other, const char* name) :
		RooAbsPdf(other, name), x("x", this, other.x), Q0("Q0", this, other.Q0), Q1("Q1", this, other.Q1), s1("s1", this, other.s1), w("w", this, other.w), a("a", this, other.a), mu("mu", this, other.mu), n("n", this, other.n) {
}

// Doing like rooexponential
Double_t SRealNPdf::evaluate() const {
	Double_t value = // begin mathematica code from "/mathematica/SidealN.nb"
			(Power(mu,n)*((1 - w)/
			        (Power(E,Power(-Q0 - n*Q1 + x,2)/(2.*n*Power(s1,2)))*
			          Sqrt(n)*Sqrt(2*Pi)*s1) +
			       (a*w*(Erf(Abs(-(n*Q1) - a*n*Power(s1,2))/
			              (Sqrt(2)*Sqrt(n)*s1)) +
			            Erf(Abs(-Q0 - n*Q1 - a*n*Power(s1,2) + x)/
			               (Sqrt(2)*Sqrt(n)*s1))*
			             Sign(-Q0 - n*Q1 - a*n*Power(s1,2) + x)))/
			        (2.*Power(E,a*(-Q0 - n*Q1 - a*n*Power(s1,2) + x)))))/
			   (Power(E,mu)*Factorial(n))	; // end mathematica code
	return value;
}

//Double_t SRealNPdf::indefiniteIntegral(Double_t x) const {
//	Double_t value =  // begin mathematica code from "/mathematica/SidealN.nb"
//			(Power(mu,n)*Erf((-(n*Q1) + x)/(Sqrt(2)*Sqrt(n)*s1)))/
//			   (2.*Power(E,mu)*Factorial(n))
//	; // end mathematica code
//	return value;
//}
//
//// Get analytical integral
//Int_t SRealNPdf::getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* rangeName) const {
//	if (matchArgs(allVars, analVars, x))
//		return 1;
//	return 0;
//}
//
//// Analytical integral
//Double_t SRealNPdf::analyticalIntegral(Int_t code, const char* rangeName) const {
//	assert(code == 1);
//
//	if (code == 1) {
//		Double_t x1 = x.min(rangeName);
//		Double_t x2 = x.max(rangeName);
//		return indefiniteIntegral(x2) - indefiniteIntegral(x1);
//	}
//	std::cout << "Error in SRealNPdf::analyticalIntegral" << std::endl;
//	return 0;
//}
