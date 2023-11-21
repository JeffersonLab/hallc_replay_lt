/*
 * TestSpectrum.h
 *
 *  Created on: Aug 4, 2020
 *      Author: petrstepanov
 */

#ifndef SRC_UTILS_TESTSPECTRUM_H_
#define SRC_UTILS_TESTSPECTRUM_H_

#include <TH1.h>
#include "../model/FitParameters.h"

class TestSpectrum {
public:
//	static TestSpectrum* getInstance();
	TestSpectrum();
	virtual ~TestSpectrum();

	static TH1* getHistogramDigitized();
	static TH1* getHistogramPaper();
	static TH1* getHistogramPaperFix();
	static TH1* getHistogramPaperNoTerm0();
	static TH1* getHistogramGenerated(FitParameters* params);
	static TH1* getHistogramGeneratedNoTerm0(FitParameters* params);
private:
//	static TestSpectrum* instance;
	static Int_t array[];
	static Int_t array2[];
	static Int_t array3[];
};

#endif /* SRC_UTILS_TESTSPECTRUM_H_ */
