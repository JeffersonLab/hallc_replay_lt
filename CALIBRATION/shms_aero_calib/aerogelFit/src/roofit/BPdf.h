/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   BPdf.h
 * Author: petrstepanov
 *
 * Created on November 9, 2016, 7:49 PM
 */

#ifndef MY_BPdf
#define MY_BPdf

#include "RooAbsReal.h"
#include "RooAbsPdf.h"
#include "TObject.h"
#include "RooRealProxy.h"

class BPdf : public RooAbsPdf {
public:
	BPdf() {};
	BPdf(const char *name, const char *title,
		RooAbsReal& _x,
		RooAbsReal& _Q0,
		RooAbsReal& _s0,
		RooAbsReal& _w,
		RooAbsReal& _a);
	BPdf(const BPdf& other, const char* name = 0);
	virtual TObject* clone(const char* newname) const { return new BPdf(*this, newname); }
	inline virtual ~BPdf() { }

    Int_t getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* rangeName=0) const ;
    Double_t analyticalIntegral(Int_t code, const char* rangeName=0) const ;

protected:
    RooRealProxy x;
    RooRealProxy Q0;
    RooRealProxy s0;
    RooRealProxy w;
    RooRealProxy a;

    Double_t evaluate() const;
    Double_t indefiniteIntegralBeforeQ0(Double_t x) const;
    Double_t indefiniteIntegralAfterQ0(Double_t x) const;
private:

	ClassDef(BPdf, 1)
};

#endif /* MY_BPdf */

