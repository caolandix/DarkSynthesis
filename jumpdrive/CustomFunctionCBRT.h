/*
 * CustomFunctionCBRT.h
 *
 *  Created on: Jun 20, 2014
 *      Author: caolan
 */

#ifndef CUSTOMFUNCTIONCBRT_H_
#define CUSTOMFUNCTIONCBRT_H_

#include "CustomFunction.h"

class CustomFunctionCBRT: public CustomFunction {
public:
	CustomFunctionCBRT(const string str) : CustomFunction(str) {};
	virtual ~CustomFunctionCBRT() {};

	virtual double applyFunction(double args[]) const { return cbrt(args[0]); };

};

#endif /* CUSTOMFUNCTIONCBRT_H_ */
