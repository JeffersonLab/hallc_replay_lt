/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Term0Pdf.h
 * Author: petrstepanov
 *
 * Created on November 9, 2016, 7:49 PM
 */

#ifndef MY_Term0Pdf
#define MY_Term0Pdf

#include "RooAbsReal.h"
#include "RooAbsPdf.h"
#include "TObject.h"
#include "RooRealProxy.h"

class Term0Pdf : public RooAbsPdf {
public:
	Term0Pdf() {};
	Term0Pdf(const char *name, const char *title,
		RooAbsReal& _x,
		RooAbsReal& _Q0,
		RooAbsReal& _s0,
		RooAbsReal& _w,
		RooAbsReal& _a);
	Term0Pdf(const Term0Pdf& other, const char* name = 0);
	virtual TObject* clone(const char* newname) const { return new Term0Pdf(*this, newname); }
	inline virtual ~Term0Pdf() { }

//    Int_t getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* rangeName=0) const ;
//    Double_t analyticalIntegral(Int_t code, const char* rangeName=0) const ;

protected:
    RooRealProxy x;
    RooRealProxy Q0;
    RooRealProxy s0;
    RooRealProxy w;
    RooRealProxy a;

    Double_t evaluate() const;
//    Double_t indefiniteIntegralBeforeQ0(Double_t x) const;
//    Double_t indefiniteIntegralAfterQ0(Double_t x) const;
private:

	ClassDef(Term0Pdf, 1)
};

#endif /* MY_Term0Pdf */

