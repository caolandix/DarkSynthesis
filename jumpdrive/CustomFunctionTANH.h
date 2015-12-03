/*
 * CustomFunctionTANH.h
 *
 *  Created on: Jun 20, 2014
 *      Author: caolan
 */

#ifndef CUSTOMFUNCTIONTANH_H_
#define CUSTOMFUNCTIONTANH_H_

#include "CustomFunction.h"

class CustomFunctionTANH: public CustomFunction {
public:
    CustomFunctionTANH(const string str) : CustomFunction(str) {}
    virtual ~CustomFunctionTANH() {}

    virtual double applyFunction(double args[]) const { return tanh(args[0]); }
};

#endif /* CUSTOMFUNCTIONTANH_H_ */
