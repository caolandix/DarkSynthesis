/*
 * CustomFunctionTAN.h
 *
 *  Created on: Jun 20, 2014
 *      Author: caolan
 */

#ifndef CUSTOMFUNCTIONTAN_H_
#define CUSTOMFUNCTIONTAN_H_

#include "CustomFunction.h"

class CustomFunctionTAN: public CustomFunction {
public:
    CustomFunctionTAN(const string str) : CustomFunction(str) {}
    virtual ~CustomFunctionTAN() {}

    virtual double applyFunction(double args[]) const { return tan(deg2rad(args[0])); }
};

#endif /* CUSTOMFUNCTIONTAN_H_ */
