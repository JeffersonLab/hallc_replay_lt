/*
 * AbsComponentFunc.cpp
 *
 *  Created on: Aug 10, 2020
 *      Author: petrstepanov
 */

#include "AbsComponentFunc.h"

AbsComponentFunc::AbsComponentFunc() {
	components = new TList();
}

AbsComponentFunc::~AbsComponentFunc() {
}

TList* AbsComponentFunc::getComponents(){
	return components;
}

