/*
 * FuncTermN.h
 *
 *  Created on: Aug 6, 2020
 *      Author: petrstepanov
 */

#ifndef SRC_FIT_FuncTermN_H_
#define SRC_FIT_FuncTermN_H_

#include "AbsFunc.h"

class FuncTermN : public AbsFunc {
public:
	FuncTermN(Int_t);
	virtual ~FuncTermN();

	Double_t func(Double_t*, Double_t*);
	Double_t getIntegral(Double_t, Double_t, Double_t*);

private:
	Int_t n;
};

#endif /* SRC_FIT_FuncTermN_H_ */
