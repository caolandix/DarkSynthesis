/*
 * CustomFunctionSINH.h
 *
 *  Created on: Jun 20, 2014
 *      Author: caolan
 */

#ifndef CUSTOMFUNCTIONSINH_H_
#define CUSTOMFUNCTIONSINH_H_

#include "CustomFunction.h"

class CustomFunctionSINH: public CustomFunction {
public:
    CustomFunctionSINH(const string str) : CustomFunction(str) {}
    virtual ~CustomFunctionSINH() {}

    virtual double applyFunction(double args[]) const { return sinh(args[0]); }
};

#endif /* CUSTOMFUNCTIONSINH_H_ */
