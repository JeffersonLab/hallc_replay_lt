/*
 * FuncSRealNoTerm0.h
 *
 *  Created on: Aug 2, 2020
 *      Author: petrstepanov
 */

#ifndef SRC_FIT_FuncSRealNoTerm0_H_
#define SRC_FIT_FuncSRealNoTerm0_H_

#include <Rtypes.h>
#include <TH1.h>
#include <TF1.h>
#include <RooRealVar.h>
#include <iostream>
#include <vector>

#include "AbsComponentFunc.h"

class FuncSRealNoTerm0 : public AbsComponentFunc {
public:
	FuncSRealNoTerm0(TH1* h, Int_t nParVal=7);
	virtual ~FuncSRealNoTerm0();

	Double_t func(Double_t*, Double_t*);

private:
	TH1* hist;		// access histogrm for integral and limits
	Int_t nPar;		// number of parameters
};

#endif /* SRC_FIT_FuncSRealNoTerm0_H_ */
