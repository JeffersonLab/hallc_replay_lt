/*
 * FunctSIdealN.h
 *
 *  Created on: Aug 6, 2020
 *      Author: petrstepanov
 */

#ifndef SRC_FIT_FuncSIdealNShiftedQ0_H_
#define SRC_FIT_FuncSIdealNShiftedQ0_H_

#include <RtypesCore.h>
#include "AbsFunc.h"

class FuncSIdealNShiftedQ0 : public AbsFunc {
public:
	FuncSIdealNShiftedQ0(Int_t);
	virtual ~FuncSIdealNShiftedQ0();

	Double_t func(Double_t*, Double_t*);
	Double_t getIntegral(Double_t, Double_t, Double_t*);

	Double_t indefiniteIntegral(Double_t, Double_t*);

private:
	Int_t n;
};

#endif /* SRC_FIT_FuncSIdealNShiftedQ0_H_ */
