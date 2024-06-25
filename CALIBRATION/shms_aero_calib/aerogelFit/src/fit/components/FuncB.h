/*
 * FunctB.h
 *
 *  Created on: Aug 6, 2020
 *      Author: petrstepanov
 */

#ifndef SRC_FIT_FUNCB_H_
#define SRC_FIT_FUNCB_H_

#include "AbsFunc.h"

class FuncB : public AbsFunc {
public:
	FuncB();
	virtual ~FuncB();

	Double_t func(Double_t*, Double_t*);
	Double_t getIntegral(Double_t, Double_t, Double_t*);

	Double_t indefiniteIntegral(Double_t, Double_t*);
};

#endif /* SRC_FIT_FUNCB_H_ */
