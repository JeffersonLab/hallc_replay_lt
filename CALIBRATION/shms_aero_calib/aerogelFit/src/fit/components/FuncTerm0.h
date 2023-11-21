/*
 * FuncTerm0.h
 *
 *  Created on: Aug 6, 2020
 *      Author: petrstepanov
 */

#ifndef SRC_FIT_FuncTerm0_H_
#define SRC_FIT_FuncTerm0_H_

#include "AbsFunc.h"

class FuncTerm0 : public AbsFunc {
public:
	FuncTerm0();
	virtual ~FuncTerm0();

	Double_t func(Double_t*, Double_t*);
	Double_t getIntegral(Double_t, Double_t, Double_t*);

	// Because function is non-integratable (contains StepFunction)
	Double_t indefiniteIntegralBeforeQ0(Double_t, Double_t*);
	Double_t indefiniteIntegralAfterQ0(Double_t, Double_t*);
};

#endif /* SRC_FIT_FuncTerm0_H_ */
