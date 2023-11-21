/*
 * TF1Normalize.h
 *
 *  Created on: Aug 9, 2020
 *      Author: petrstepanov
 */

#ifndef SRC_HELPER_TF1NORMALIZE_H_
#define SRC_HELPER_TF1NORMALIZE_H_

#include <TF1.h>

class TF1Normalize {
public:
	TF1Normalize(TF1*, Double_t);
	virtual ~TF1Normalize();

	Double_t func(Double_t*, Double_t*);

private:
	TF1* originalFunc;
	Double_t norm;
};

#endif /* SRC_HELPER_TF1NORMALIZE_H_ */
