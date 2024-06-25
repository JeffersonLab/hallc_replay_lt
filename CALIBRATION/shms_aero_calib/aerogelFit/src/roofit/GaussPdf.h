/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   GaussPdf.h
 * Author: petrstepanov
 *
 * Created on November 9, 2016, 7:49 PM
 */

#ifndef MY_GaussPdf
#define MY_GaussPdf

#include "RooAbsReal.h"
#include "RooAbsPdf.h"
#include "TObject.h"
#include "RooRealProxy.h"

class GaussPdf : public RooAbsPdf {
public:
	GaussPdf() {};
	GaussPdf(const char *name, const char *title,
		RooAbsReal& _x,
		RooAbsReal& _Q0,
		RooAbsReal& _s0
		);
	GaussPdf(const GaussPdf& other, const char* name = 0);
	virtual TObject* clone(const char* newname) const { return new GaussPdf(*this, newname); }
	inline virtual ~GaussPdf() { }

//    Int_t getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* rangeName=0) const ;
//    Double_t analyticalIntegral(Int_t code, const char* rangeName=0) const ;

protected:
    RooRealProxy x;
    RooRealProxy Q0;
    RooRealProxy s0;

    Double_t evaluate() const;
//    Double_t indefiniteIntegral(Double_t y) const;
private:

	ClassDef(GaussPdf, 1)
};

#endif /* MY_GaussPdf */

