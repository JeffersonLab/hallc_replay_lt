/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   SIdealNPdf.h
 * Author: petrstepanov
 *
 * Created on November 9, 2016, 7:49 PM
 */

#ifndef MY_SIdealNPdf
#define MY_SIdealNPdf

#include "RooAbsReal.h"
#include "RooAbsPdf.h"
#include "TObject.h"
#include "RooRealProxy.h"

class SIdealNPdf : public RooAbsPdf {
public:
	SIdealNPdf() {};
	SIdealNPdf(const char *name, const char *title,
		RooAbsReal& _x,
		RooAbsReal& _Q1,
		RooAbsReal& _s1,
		RooAbsReal& _n);
	SIdealNPdf(const SIdealNPdf& other, const char* name = 0);
	virtual TObject* clone(const char* newname) const { return new SIdealNPdf(*this, newname); }
	inline virtual ~SIdealNPdf() { }

    Int_t getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* rangeName=0) const ;
    Double_t analyticalIntegral(Int_t code, const char* rangeName=0) const ;

protected:
    RooRealProxy x;
    RooRealProxy Q1;
    RooRealProxy s1;
    RooRealProxy n;

    Double_t evaluate() const;
    Double_t indefiniteIntegral(Double_t x) const;
private:

	ClassDef(SIdealNPdf, 1)
};

#endif /* MY_SIdealNPdf */

