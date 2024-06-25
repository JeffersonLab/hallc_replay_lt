/*
 * FuncSReal.h
 *
 *  Created on: Aug 2, 2020
 *      Author: petrstepanov
 */

#ifndef SRC_FIT_FUNCSREAL_H_
#define SRC_FIT_FUNCSREAL_H_

#include <Rtypes.h>
#include <TH1.h>
#include <TF1.h>
#include <RooRealVar.h>
#include <iostream>
#include <vector>

#include "AbsComponentFunc.h"

class FuncSReal : public AbsComponentFunc {
public:
	FuncSReal(TH1* h, Int_t nParVal=7);
	virtual ~FuncSReal();

	Double_t func(Double_t*, Double_t*);

private:
	TH1* hist;		// access histogrm for integral and limits
	Int_t nPar;		// number of parameters
};

#endif /* SRC_FIT_FUNCSREAL_H_ */
