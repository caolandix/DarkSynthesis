/*
 * CustomFunctionCEILING.h
 *
 *  Created on: Jun 20, 2014
 *      Author: caolan
 */

#ifndef CUSTOMFUNCTIONCEILING_H_
#define CUSTOMFUNCTIONCEILING_H_

#include "CustomFunction.h"

class CustomFunctionCEILING: public CustomFunction {
public:
    CustomFunctionCEILING(const string str) : CustomFunction(str) {}
    virtual ~CustomFunctionCEILING() {}

    virtual double applyFunction(double args[]) const { return ceil(args[0]); }
};

#endif /* CUSTOMFUNCTIONCEILING_H_ */
