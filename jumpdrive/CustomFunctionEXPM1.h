/*
 * CustomFunctionEXPM1.h
 *
 *  Created on: Jun 20, 2014
 *      Author: caolan
 */

#ifndef CUSTOMFUNCTIONEXPM1_H_
#define CUSTOMFUNCTIONEXPM1_H_

#include "CustomFunction.h"

class CustomFunctionEXPM1: public CustomFunction {
public:
	CustomFunctionEXPM1(const string str) : CustomFunction(str) {};
	virtual ~CustomFunctionEXPM1() {};

	virtual double applyFunction(double args[]) const { return expm1(args[0]); };
};

#endif /* CUSTOMFUNCTIONEXPM1_H_ */
