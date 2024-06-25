/*
 * SpectrumSimplified.h
 *
 *  Created on: Aug 2, 2020
 *      Author: petrstepanov
 */

#ifndef SRC_FIT_SpectrumSimplified_H_
#define SRC_FIT_SpectrumSimplified_H_

#include <Rtypes.h>
#include <RooRealVar.h>

class SpectrumSimplified {
public:
	SpectrumSimplified(Double_t histIntegralVal, Int_t xMin, Int_t xMax, Int_t nMaxVal=100);
	virtual ~SpectrumSimplified();

	Double_t realIndefInt(Double_t , Double_t*);
	Double_t realDefIntNewton(Double_t*);
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

#endif /* SRC_FIT_SpectrumSimplified_H_ */
