/*
 * CustomFunctionCOS.h
 *
 *  Created on: Jun 20, 2014
 *      Author: caolan
 */

#ifndef CUSTOMFUNCTIONCOS_H_
#define CUSTOMFUNCTIONCOS_H_

#include "CustomFunction.h"

class CustomFunctionCOS: public CustomFunction {
public:
    CustomFunctionCOS(const string str) : CustomFunction(str) {}
    virtual ~CustomFunctionCOS() {}

    virtual double applyFunction(double args[]) const { return cos(deg2rad(args[0])); }
};

#endif /* CUSTOMFUNCTIONCOS_H_ */
