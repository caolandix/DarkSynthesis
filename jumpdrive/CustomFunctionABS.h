/*
 * CustomFunctionABS.h
 *
 *  Created on: Jun 19, 2014
 *      Author: johndi
 */

#ifndef CUSTOMFUNCTIONABS_H_
#define CUSTOMFUNCTIONABS_H_

#include "commondefs.h"
#include "CustomFunction.h"

class CustomFunctionABS : public CustomFunction {
public:
    CustomFunctionABS(const string str) : CustomFunction(str) {}
    virtual ~CustomFunctionABS() {}

    virtual double applyFunction(double args[]) const { return abs(args[0]); }
};

#endif /* CUSTOMFUNCTIONABS_H_ */
