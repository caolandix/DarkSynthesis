/*
 * CustomFunctionSQRT.h
 *
 *  Created on: Jun 20, 2014
 *      Author: caolan
 */

#ifndef CUSTOMFUNCTIONSQRT_H_
#define CUSTOMFUNCTIONSQRT_H_

#include "CustomFunction.h"

class CustomFunctionSQRT: public CustomFunction {
public:
	CustomFunctionSQRT(const string str) : CustomFunction(str) {};
	virtual ~CustomFunctionSQRT() {};

	virtual double applyFunction(double args[]) const { return sqrt(args[0]); };
};

#endif /* CUSTOMFUNCTIONSQRT_H_ */
