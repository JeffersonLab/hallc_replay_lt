/*
 * TreeHelper.h
 *
 *  Created on: Jul 30, 2020
 *      Author: petrstepanov
 */

#ifndef SRC_HELPER_TREEHELPER_H_
#define SRC_HELPER_TREEHELPER_H_

#include <TString.h>
#include <TFile.h>
#include <TChain.h>
#include <TTree.h>

class TreeHelper {
public:
	static TreeHelper* getInstance();
	virtual ~TreeHelper();

	int init(TList*);
	void plotTreeProfiles();
	void plotTree();
	void fillPmtHists(TH1*, TH1*);
	const char* getFileName();

private:
	TreeHelper();
	static TreeHelper* instance;

	TString* fileName;
//	TFile* myFile;
	TTree* myTree;
};

#endif /* SRC_HELPER_TREEHELPER_H_ */
