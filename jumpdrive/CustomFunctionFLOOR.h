/*
 * CustomFunctionFLOOR.h
 *
 *  Created on: Jun 20, 2014
 *      Author: caolan
 */

#ifndef CUSTOMFUNCTIONFLOOR_H_
#define CUSTOMFUNCTIONFLOOR_H_

#include "CustomFunction.h"

class CustomFunctionFLOOR: public CustomFunction {
public:
	CustomFunctionFLOOR(const string str) : CustomFunction(str) {};
	virtual ~CustomFunctionFLOOR() {};

	virtual double applyFunction(double args[]) const { return floor(args[0]); };
};

#endif /* CUSTOMFUNCTIONFLOOR_H_ */
