/*
 * FuncTerm0.cpp
 *
 *  Created on: Aug 6, 2020
 *      Author: petrstepanov
 */

#include "FuncTerm0.h"
#include "../../utils/MathematicaAliases.h"

FuncTerm0::FuncTerm0() {
	// TODO Auto-generated constructor stub

}

FuncTerm0::~FuncTerm0() {
	// TODO Auto-generated destructor stub
}

Double_t FuncTerm0::func(Double_t* _x, Double_t* par) {
	Double_t x = _x[0];

	// Parameters:
	Double_t Q0 = par[0];		// pedestal position
	Double_t s0 = par[1];		// standard deviation of the type I background process
	Double_t Q1 = par[2];		// average charge at the PM output
	Double_t s1 = par[3];		// corresponding standard deviation of the charge distribution
	Double_t w  = par[4];		// probability that signal is accompanied by type II background process
	Double_t a  = par[5];		// coefficient of the exponential decrease of the type II background
	Double_t mu = par[6];		// number of photo-electrons

	// Calculate function value
	Double_t value = // begin mathematica code from "/mathematica/term0-no-coeff.nb"
	    (Power(E,((Q0 - x)*(-Q0 + x))/(2.*Power(s0,2)))*(1 - w))/(Sqrt(2*Pi)*s0) + (a*w*UnitStep(-Q0 + x))/Power(E,a*(-Q0 + x))
	; // end mathematica code

	return value;
}

Double_t FuncTerm0::getIntegral(Double_t xMin, Double_t xMax, Double_t* par){
	Double_t Q0 = par[0];		// pedestal position

	// Newton-Leibniz formula
	if (xMax < Q0){
		return indefiniteIntegralBeforeQ0(xMax, par) - indefiniteIntegralBeforeQ0(xMin, par);
	}
	else if (xMin < Q0 && xMax >= Q0){
		Double_t integral = indefiniteIntegralBeforeQ0(Q0, par) - indefiniteIntegralBeforeQ0(xMin, par);
		integral+= indefiniteIntegralAfterQ0(xMax, par) - indefiniteIntegralAfterQ0(Q0, par);
	}
	// else if xMin > Q0
	return indefiniteIntegralAfterQ0(xMax, par) - indefiniteIntegralAfterQ0(xMin, par);
}

Double_t FuncTerm0::indefiniteIntegralBeforeQ0(Double_t x, Double_t* par) {
	// Parameters
	Double_t Q0 = par[0];		// average charge at the PM output
	Double_t s0 = par[1];		// standard deviation of the type I background process
	Double_t Q1 = par[2];		// average charge at the PM output
	Double_t s1 = par[3];		// corresponding standard deviation of the charge distribution
	Double_t w  = par[4];		// probability that signal is accompanied by type II background process
	Double_t a  = par[5];		// coefficient of the exponential decrease of the type II background
	Double_t mu = par[6];		// number of photo-electrons

	Double_t value =  // begin mathematica code from "/mathematica/term0.nb" but UnitStep=0
// With coefficient
//			((-1 + w)*Erf((Q0 - x)/(Sqrt(2)*s0)))/(2.*Power(E,mu))
// Without coefficient
			((-1 + w)*Erf((Q0 - x)/(Sqrt(2)*s0)))/2.
	; // end mathematica code

	return value;
}

Double_t FuncTerm0::indefiniteIntegralAfterQ0(Double_t x, Double_t* par) {
	// Parameters
	Double_t Q0 = par[0];		// average charge at the PM output
	Double_t s0 = par[1];		// standard deviation of the type I background process
	Double_t Q1 = par[2];		// average charge at the PM output
	Double_t s1 = par[3];		// corresponding standard deviation of the charge distribution
	Double_t w  = par[4];		// probability that signal is accompanied by type II background process
	Double_t a  = par[5];		// coefficient of the exponential decrease of the type II background
	Double_t mu = par[6];		// number of photo-electrons

	Double_t value =  // begin mathematica code from "/mathematica/term0.nb" but UnitStep=1
// With coefficient
//			(-(Power(E,a*Q0 - a*x)*w) + ((-1 + w)*Erf((Q0 - x)/(Sqrt(2)*s0)))/2.)/Power(E,mu)
// Without coefficient
			-(Power(E,a*Q0 - a*x)*w) + ((-1 + w)*Erf((Q0 - x)/(Sqrt(2)*s0)))/2.
	; // end mathematica code

	return value;
}
