/*
 * SpectrumReal.h
 *
 *  Created on: Aug 2, 2020
 *      Author: petrstepanov
 */

#ifndef SRC_FIT_SpectrumReal_H_
#define SRC_FIT_SpectrumReal_H_

#include <Rtypes.h>
#include <RooRealVar.h>

class SpectrumReal {
public:
	SpectrumReal(Double_t histIntegralVal, Int_t xMin, Int_t xMax, Int_t nMaxVal=100);
	virtual ~SpectrumReal();

//	Double_t ideal(Double_t*, Double_t*);
//	Double_t background(Double_t*, Double_t*);

	Double_t realDefIntSimpson(Double_t*);
	Double_t func(Double_t*, Double_t*);
	static RooArgList* parameters;

private:
	Int_t nMax;
	Int_t xMax;
	Int_t xMin;
	Double_t histIntegral;
	Double_t pi;
	Double_t e;
};

#endif /* SRC_FIT_SpectrumReal_H_ */
