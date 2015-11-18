/*
 * CustomFunctionEXP.h
 *
 *  Created on: Jun 20, 2014
 *      Author: caolan
 */

#ifndef CUSTOMFUNCTIONEXP_H_
#define CUSTOMFUNCTIONEXP_H_

#include "CustomFunction.h"

class CustomFunctionEXP: public CustomFunction {
public:
	CustomFunctionEXP(const string str) : CustomFunction(str) {};
	virtual ~CustomFunctionEXP() {};

	virtual double applyFunction(double args[]) const { return exp(args[0]); };
};

#endif /* CUSTOMFUNCTIONEXP_H_ */
