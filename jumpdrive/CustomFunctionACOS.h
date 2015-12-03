/*
 * CustomFunctionACOS.h
 *
 *  Created on: Jun 19, 2014
 *      Author: johndi
 */

#ifndef CUSTOMFUNCTIONACOS_H_
#define CUSTOMFUNCTIONACOS_H_

#include "CustomFunction.h"

class CustomFunctionACOS: public CustomFunction {
public:
    CustomFunctionACOS(const string str) : CustomFunction(str) {}
    virtual ~CustomFunctionACOS() {}

    virtual double applyFunction(double args[]) const { return acos(args[0]); }
};

#endif /* CUSTOMFUNCTIONACOS_H_ */
