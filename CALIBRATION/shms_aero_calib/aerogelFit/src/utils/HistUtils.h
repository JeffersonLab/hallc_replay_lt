/*
 * HistUtils.h
 *
 *  Created on: Jul 28, 2020
 *      Author: petrstepanov
 */

#ifndef SRC_UTILS_HISTUTILS_H_
#define SRC_UTILS_HISTUTILS_H_

#include <iostream>
#include <TH1F.h>
#include <TList.h>
#include <RooCurve.h>
#include <RooAbsPdf.h>

struct Chi2Struct {
	const Double_t chiSum;
	const Int_t degreesOfFreedom;
	const Double_t chi2;
};

class HistUtils {
public:
	HistUtils();
	virtual ~HistUtils();

	static TH1* trimHistogram(TH1*);
	static TList* trimHistogramList(TList*, Double_t xMin, Double_t xMax);
	static void rebinHistogramList(TList* histograms, Int_t nGroup);
	static TH1* cutHistogram(TH1* hist, Double_t xMin, Double_t xMax);
	static TH1* cloneHistogram(TH1*, const char*, const char* = 0);
	static Int_t getNNonZeroBins(TH1*);
	static void resetHistogram(TH1*);
	static void normalizeHistogram(TH1*);
	static void removeHistogramZeros(TH1*);
	static void increaseBinContent(TH1* hist, Int_t bin);
    static Chi2Struct getChi2(TH1*, RooCurve*, RooAbsPdf*);
	static void increaseCorrespondingBinContent(TH1* hist, Float_t);
};

#endif /* SRC_UTILS_HISTUTILS_H_ */
