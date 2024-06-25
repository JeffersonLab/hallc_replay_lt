/*
 * BeamOutputHelper.h
 *
 *  Created on: Jul 30, 2020
 *      Author: petrstepanov
 */

#ifndef SRC_HELPER_BeamOutputHelper_H_
#define SRC_HELPER_BeamOutputHelper_H_

#include <cstdio>
#include <TFile.h>
#include "../model/FitParameters.h"

class BeamOutputHelper {
public:
	static BeamOutputHelper* getInstance();
	virtual ~BeamOutputHelper();

	int init();
	int finalize();
	void setRunName(const char* name);
	void addRunValue(Double_t value);
	void writeToAscii(const char* string);
	void writeToAsciiNoIndent(const char* string);
	void writeToAscii(Double_t *pars, Double_t* parsErr);
	void writeToAscii(FitParameters* parameters);
	void writeToAscii(Double_t value);
	void writeToAscii(Int_t value);
	void writeObjectToRootFile(TObject* object);

private:
	BeamOutputHelper();
	static BeamOutputHelper* instance;

	void createAsciiHeader();

	FILE* asciiFile;
	TFile* rootFile;

};

#endif /* SRC_HELPER_BeamOutputHelper_H_ */
