/*
 * FuncSRealFFT.h
 *
 *  Created on: Aug 2, 2020
 *      Author: petrstepanov
 */

#ifndef SRC_FIT_FuncSRealFFT_H_
#define SRC_FIT_FuncSRealFFT_H_

#include <Rtypes.h>
#include <TH1.h>
#include <TF1.h>
#include <RooRealVar.h>
#include <iostream>
#include <vector>

#include "AbsComponentFunc.h"

class FuncSRealFFT : public AbsComponentFunc {
public:
	FuncSRealFFT(TH1* hist, Int_t nParVal=7);
	virtual ~FuncSRealFFT();

	Double_t func(Double_t*, Double_t*);

private:
	TH1* hist;
	Int_t nPar;
};

#endif /* SRC_FIT_FuncSRealFFT_H_ */
