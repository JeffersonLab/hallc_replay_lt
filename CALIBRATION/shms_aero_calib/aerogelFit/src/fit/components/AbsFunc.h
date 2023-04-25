/*
 * AbsFunct.h
 *
 *  Created on: Aug 6, 2020
 *      Author: petrstepanov
 */

#ifndef SRC_FIT_ABSFUNC_H_
#define SRC_FIT_ABSFUNC_H_

#include <RtypesCore.h>

class AbsFunc {
public:
	AbsFunc();
	virtual ~AbsFunc();

	// Function
	virtual Double_t func(Double_t*, Double_t*) = 0;
	virtual Double_t getIntegral(Double_t, Double_t, Double_t*) = 0;
};

#endif /* SRC_FIT_ABSFUNC_H_ */
