/*
 * FuncSIdealNShiftedQ0.cpp
 *
 *  Created on: Aug 6, 2020
 *      Author: petrstepanov
 */

#include "FuncSIdealNShiftedQ0.h"
#include "../../utils/MathematicaAliases.h"

FuncSIdealNShiftedQ0::FuncSIdealNShiftedQ0(Int_t nVal) : n(nVal) {
}

FuncSIdealNShiftedQ0::~FuncSIdealNShiftedQ0() {
}

Double_t FuncSIdealNShiftedQ0::func(Double_t* _x, Double_t* par) {
	Double_t x = _x[0];

	// Parameters:
	Double_t Q0 = par[0];		// average charge at the PM output
	Double_t s0 = par[1];		// standard deviation of the type I background process
	Double_t Q1 = par[2];		// average charge at the PM output
	Double_t s1 = par[3];		// corresponding standard deviation of the charge distribution
	Double_t w  = par[4];		// probability that signal is accompanied by type II background process
	Double_t a  = par[5];		// coefficient of the exponential decrease of the type II background
	Double_t mu = par[6];		// number of photo-electrons

	// Calculate function value
	Double_t value = // begin mathematica code from "/mathematica/sIdealN.nb"
// Without normalization
//			(Power(E,-mu - Power(-Q0 - n*Q1 + x,2)/(2.*n*Power(s1,2)))*Power(mu,n))/(Sqrt(n)*Sqrt(2*Pi)*s1*Factorial(n))
// With normalization
			(Sqrt(n)*Sqrt(2*Pi)*s1)/Power(E,Power(-Q0 - n*Q1 + x,2)/(2.*n*Power(s1,2)))
	; // end mathematica code

	return value;
}

Double_t FuncSIdealNShiftedQ0::getIntegral(Double_t xMin, Double_t xMax, Double_t* par){
	// Newton-Leibniz formula
	return indefiniteIntegral(xMax, par) - indefiniteIntegral(xMin, par);
}

Double_t FuncSIdealNShiftedQ0::indefiniteIntegral(Double_t x, Double_t* par) {
	// Parameters
	Double_t Q0 = par[0];		// average charge at the PM output
	Double_t s0 = par[1];		// standard deviation of the type I background process
	Double_t Q1 = par[2];		// average charge at the PM output
	Double_t s1 = par[3];		// corresponding standard deviation of the charge distribution
	Double_t w  = par[4];		// probability that signal is accompanied by type II background process
	Double_t a  = par[5];		// coefficient of the exponential decrease of the type II background
	Double_t mu = par[6];		// number of photo-electrons

	Double_t value =  // begin mathematica code from "/mathematica/sIdealN.nb"
// Without normalization
//			-(Power(mu,n)*Erf((Q0 + n*Q1 - x)/(Sqrt(2)*Sqrt(n)*s1)))/(2.*Power(E,mu)*Factorial(n))
// With normalization
			-(n*Pi*Power(s1,2)*Erf((Q0 + n*Q1 - x)/(Sqrt(2)*Sqrt(n)*s1)))
	; // end mathematica code

	return value;
}
