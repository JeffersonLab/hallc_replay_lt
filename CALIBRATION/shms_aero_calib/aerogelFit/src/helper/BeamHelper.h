/*
 * BeamHelper.h
 *
 *  Created on: Jul 30, 2020
 *      Author: petrstepanov
 */

#ifndef SRC_HELPER_BeamHelper_H_
#define SRC_HELPER_BeamHelper_H_

#include <TList.h>
#include <TString.h>
#include <TTree.h>

class BeamHelper {
public:
	BeamHelper(const char* fileNamePath);
	virtual ~BeamHelper();

	TList* getHistogramsPositive();
	TList* getHistogramsNegative();
	const char* getFileName();

private:
	TFile* myFile;
	TList* histogramsPositive;
	TList* histogramsNegative;
};

#endif /* SRC_HELPER_BeamHelper_H_ */
