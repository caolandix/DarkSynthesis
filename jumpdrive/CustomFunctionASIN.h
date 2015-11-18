/*
 * CustomFunctionASIN.h
 *
 *  Created on: Jun 19, 2014
 *      Author: johndi
 */

#ifndef CUSTOMFUNCTIONASIN_H_
#define CUSTOMFUNCTIONASIN_H_

#include "CustomFunction.h"

class CustomFunctionASIN: public CustomFunction {
public:
	CustomFunctionASIN(const string str) : CustomFunction(str) {};
	virtual ~CustomFunctionASIN() {};

	virtual double applyFunction(double args[]) const { return asin(args[0]); };
};

#endif /* CUSTOMFUNCTIONASIN_H_ */
