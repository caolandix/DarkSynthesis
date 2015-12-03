/*
 * CustomFunctionCOSH.h
 *
 *  Created on: Jun 20, 2014
 *      Author: caolan
 */

#ifndef CUSTOMFUNCTIONCOSH_H_
#define CUSTOMFUNCTIONCOSH_H_

#include "CustomFunction.h"

class CustomFunctionCOSH: public CustomFunction {
public:
    CustomFunctionCOSH(const string str) : CustomFunction(str) {}
    virtual ~CustomFunctionCOSH() {}

    virtual double applyFunction(double args[]) const { return cosh(args[0]); }
};

#endif /* CUSTOMFUNCTIONCOSH_H_ */
