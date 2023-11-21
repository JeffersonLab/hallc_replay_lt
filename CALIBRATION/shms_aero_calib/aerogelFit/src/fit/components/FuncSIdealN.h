/*
 * FunctSIdealN.h
 *
 *  Created on: Aug 6, 2020
 *      Author: petrstepanov
 */

#ifndef SRC_FIT_FUNCSIDEALN_H_
#define SRC_FIT_FUNCSIDEALN_H_

#include <RtypesCore.h>
#include "AbsFunc.h"

class FuncSIdealN : public AbsFunc {
public:
	FuncSIdealN(Int_t);
	virtual ~FuncSIdealN();

	Double_t func(Double_t*, Double_t*);
	Double_t getIntegral(Double_t, Double_t, Double_t*);

	Double_t indefiniteIntegral(Double_t, Double_t*);

private:
	Int_t n;
};

#endif /* SRC_FIT_FUNCSIDEALN_H_ */
