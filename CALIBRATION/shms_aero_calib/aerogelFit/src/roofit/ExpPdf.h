/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   ExpPdf.h
 * Author: petrstepanov
 *
 * Created on November 9, 2016, 7:49 PM
 */

#ifndef MY_EXPPDF
#define MY_EXPPDF

#include "RooAbsReal.h"
#include "RooAbsPdf.h"
#include "TObject.h"
#include "RooRealProxy.h"

class ExpPdf : public RooAbsPdf {
public:
	ExpPdf() {};
	ExpPdf(const char *name, const char *title,
		RooAbsReal& _x,
		RooAbsReal& _Q0,
		RooAbsReal& _a
		);
	ExpPdf(const ExpPdf& other, const char* name = 0);
	virtual TObject* clone(const char* newname) const { return new ExpPdf(*this, newname); }
	inline virtual ~ExpPdf() { }

    Int_t getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* rangeName=0) const ;
    Double_t analyticalIntegral(Int_t code, const char* rangeName=0) const ;

protected:
    RooRealProxy x;
    RooRealProxy Q0;
    RooRealProxy a;

    Double_t evaluate() const;
    Double_t indefiniteIntegral(Double_t y) const;
private:

	ClassDef(ExpPdf, 1)
};

#endif /* MY_EXPPDF */

