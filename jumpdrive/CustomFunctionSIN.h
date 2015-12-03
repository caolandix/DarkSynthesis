/*
 * CustomFunctionSIN.h
 *
 *  Created on: Jun 20, 2014
 *      Author: caolan
 */

#ifndef CUSTOMFUNCTIONSIN_H_
#define CUSTOMFUNCTIONSIN_H_

#include "CustomFunction.h"

class CustomFunctionSIN: public CustomFunction {
public:
    CustomFunctionSIN(const string str) : CustomFunction(str) {}
    virtual ~CustomFunctionSIN() {}

    virtual double applyFunction(double args[]) const { return sin(deg2rad(args[0])); }
};

#endif /* CUSTOMFUNCTIONSIN_H_ */
