/*
 * StringUtils.cpp
 *
 *  Created on: Jul 30, 2020
 *      Author: petrstepanov
 */

#include "../utils/StringUtils.h"

#include "TPRegexp.h"
#include "TObjString.h"
#include "TObjArray.h"

StringUtils::StringUtils() {
	// TODO Auto-generated constructor stub

}

StringUtils::~StringUtils() {
	// TODO Auto-generated destructor stub
}

std::pair<TString, TString> StringUtils::parseParameter(const char* parameter){
	TString s4(parameter);
	// Test regex here: https://regex101.com/r/7H6We8/1 and remember c++ double escapes!
	// Check if parameter is a variable
	TObjArray *subStr1 = TPRegexp("^--(.+)=(.+)$").MatchS(s4);
	const Int_t nrSubStr1 = subStr1->GetLast()+1;
	if (nrSubStr1 == 3) {
		const TString name = ((TObjString *)subStr1->At(1))->GetString();
		const TString value  = ((TObjString *)subStr1->At(2))->GetString();
		return std::make_pair(name, value);
	}

	// Check if parameter is a ROOT file
	// TObjArray *subStr2 = TPRegexp("^(.+)\\.root$").MatchS(s4);
	// const Int_t nrSubStr2 = subStr2->GetLast()+1;
	// if (nrSubStr2 == 2) {
	// 	return std::make_pair(TString("file-name"), TString(parameter));
	// }

	// Otherwise return "unknown" in pair
	return std::make_pair(TString("file-name"), TString(parameter));
}

//std::pair<TString, TString> StringUtils::extractFilenameAndExtension(const char* fileNamePath){
//	TString s = TString(fileNamePath);
//	TObjArray *objArray = TPRegexp(".*(?:\/|\\)(.*)\.(.*)").MatchS(s);
//	if (objArray->GetLast()+1 != 3){
//		return NULL;
//	}
//	const TString filename = ((TObjString *)objArray->At(1))->GetString();
//	const TString extension  = ((TObjString *)objArray->At(2))->GetString();
//	return std::make_pair(filename, extension);
//}

TString* StringUtils::extractFilenameNoExtension(const char* fileNamePath){
	TString* s = new TString(fileNamePath);

	// If file path has no slashes or backslashes
	if (!s->Contains("\\") && !s->Contains("/")){
		TObjArray *objArray = TPRegexp("(.*)\\.(?:.*)").MatchS(*s);
		if (objArray->GetLast()+1 != 2){
			return NULL;
		}
		const TString str = ((TObjString *)objArray->At(1))->GetString();
		return new TString(str.Data());
	}

	// If file path contains slashes or back slashes
	TObjArray *objArray = TPRegexp(".*(?:\\/|\\\\)(.*)\\.(?:.*)").MatchS(*s); // .*(?:\/|\\)(.*)\.(?:.*)
	objArray->Print();
	if (objArray->GetLast()+1 != 2){
		return NULL;
	}
	return new TString(((TObjString *)objArray->At(1))->GetString().Data());
}

TString* StringUtils::extractFilenameWithExtension(const char* fileNamePath){
	TString* s = new TString(fileNamePath);

	// If file path has no slashes or backslashes
	if (!s->Contains("\\") && !s->Contains("/")){
		return s;
	}

	// If file path contains slashes or back slashes https://regex101.com/r/7H6We8/1
	TObjArray *objArray = TPRegexp(".*(?:\\/|\\\\)(.*)").MatchS(*s); // .*(?:\/|\\)(.*)
	if (objArray->GetLast()+1 != 2){
		return NULL;
	}
	return new TString(((TObjString *)objArray->At(1))->GetString().Data());
}

Int_t StringUtils::extractFileIndex(const char* fileNamePath){
	TString* s = new TString(fileNamePath);

	// If file path contains slashes or back slashes https://regex101.com/r/7H6We8/1
	TObjArray *objArray = TPRegexp("_(\\d+).root").MatchS(*s); // _(\d*)
	if (objArray->GetLast()+1 != 2){
		return 0;
	}
	const char* index = ((TObjString *)objArray->At(1))->GetString().Data();
	return atoi(index);
}
const char* StringUtils::toString(FitType fitType){
	if (fitType == FitType::test) return "test";
	if (fitType == FitType::root) return "root-analytical";
	if (fitType == FitType::rooFit) return "roofit";
	return "none";
}

void StringUtils::extractChiNPars(const char* string, Double_t &chi2, Double_t &nPars){
	TString* s = new TString(string);
	TObjArray *objArray = TPRegexp("=(.+)\\/(.+)").MatchS(*s); // =(.+)\/(.+)
	const char* chi2Str = ((TObjString *)objArray->At(1))->GetString().Data();
	chi2 = atof(chi2Str);
	const char* nParsStr = ((TObjString *)objArray->At(2))->GetString().Data();
	nPars = atoi(nParsStr);
}
