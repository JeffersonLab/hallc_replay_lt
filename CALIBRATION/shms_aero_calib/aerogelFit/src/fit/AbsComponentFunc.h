/*
 * AbsComponentFunc.h
 *
 *  Created on: Aug 10, 2020
 *      Author: petrstepanov
 */

#ifndef SRC_FIT_COMPONENTS_ABSCOMPONENTFUNC_H_
#define SRC_FIT_COMPONENTS_ABSCOMPONENTFUNC_H_

#include <TList.h>
#include <TFormula.h>

class AbsComponentFunc {
public:
	AbsComponentFunc();
	virtual ~AbsComponentFunc();

	TList* getComponents();
	TList* components;

	TFormula* coefficientN;

	virtual Double_t func(Double_t*, Double_t*)=0;
};

#endif /* SRC_FIT_COMPONENTS_ABSCOMPONENTFUNC_H_ */
