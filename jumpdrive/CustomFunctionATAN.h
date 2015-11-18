/*
 * CustomFunctionATAN.h
 *
 *  Created on: Jun 20, 2014
 *      Author: caolan
 */

#ifndef CUSTOMFUNCTIONATAN_H_
#define CUSTOMFUNCTIONATAN_H_

#include "CustomFunction.h"

class CustomFunctionATAN: public CustomFunction {
public:
	CustomFunctionATAN(const string str) : CustomFunction(str) {};
	virtual ~CustomFunctionATAN() {};

	virtual double applyFunction(double args[]) const { return atan(args[0]); };
};

#endif /* CUSTOMFUNCTIONATAN_H_ */
