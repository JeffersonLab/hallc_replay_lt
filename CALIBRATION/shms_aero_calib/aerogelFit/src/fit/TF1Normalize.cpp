/*
 * TF1Normalize.cpp
 *
 *  Created on: Aug 9, 2020
 *      Author: petrstepanov
 */

#include "TF1Normalize.h"

TF1Normalize::TF1Normalize(TF1* func, Double_t normVal) : originalFunc(func), norm(normVal) {
}

TF1Normalize::~TF1Normalize() {
	// TODO Auto-generated destructor stub
}

Double_t TF1Normalize::func(Double_t* _x, Double_t* par) {
	Double_t x = _x[0];

	Double_t value = originalFunc->EvalPar(_x, par);
	return value*norm;
}
