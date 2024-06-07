/*
 * FitParameters.h
 *
 *  Created on: Aug 16, 2020
 *      Author: petrstepanov
 */

#ifndef SRC_MODEL_FITPARAMETERS_H_
#define SRC_MODEL_FITPARAMETERS_H_

#include <RtypesCore.h>
#include <RooArgList.h>
#include <RooRealVar.h>

enum class ParametersType {
	forBellamyHist,
	forKaonHist
};

class FitParameters {
public:
	FitParameters(ParametersType parType);
	FitParameters(const char* fileName);
	virtual ~FitParameters();

	RooArgList* getList();
	Double_t* getArray();
	Int_t getSize();

	void updateFromArrays(const Double_t* params, const Double_t* errors);

	Int_t readParametersFromFile();

	static const char* parameterNames[];
	static const int parametersNumber;

private:
	const char* filename;
	RooArgList* parameters;
};

#endif /* SRC_MODEL_FITPARAMETERS_H_ */
