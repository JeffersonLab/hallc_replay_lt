/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   SRealNPdf.h
 * Author: petrstepanov
 *
 * Created on November 9, 2016, 7:49 PM
 */

#ifndef MY_SRealNPdf
#define MY_SRealNPdf

#include "RooAbsReal.h"
#include "RooAbsPdf.h"
#include "TObject.h"
#include "RooRealProxy.h"

class SRealNPdf : public RooAbsPdf {
public:
	SRealNPdf() {};
	SRealNPdf(const char *name, const char *title,
		RooAbsReal& _x,
		RooAbsReal& _Q0,
		RooAbsReal& _Q1,
		RooAbsReal& _s1,
		RooAbsReal& _w,
		RooAbsReal& _a,
		RooAbsReal& _mu,
		RooAbsReal& _n);
	SRealNPdf(const SRealNPdf& other, const char* name = 0);
	virtual TObject* clone(const char* newname) const { return new SRealNPdf(*this, newname); }
	inline virtual ~SRealNPdf() { }

//    Int_t getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* rangeName=0) const ;
//    Double_t analyticalIntegral(Int_t code, const char* rangeName=0) const ;

protected:
    RooRealProxy x;
    RooRealProxy Q0;
    RooRealProxy Q1;
    RooRealProxy s1;
    RooRealProxy w;
    RooRealProxy a;
    RooRealProxy mu;
    RooRealProxy n;

    Double_t evaluate() const;
//    Double_t indefiniteIntegral(Double_t x) const;
private:

	ClassDef(SRealNPdf, 1)
};

#endif /* MY_SRealNPdf */

