/*
 * CustomFunctionLOG.h
 *
 *  Created on: Jun 20, 2014
 *      Author: caolan
 */

#ifndef CUSTOMFUNCTIONLOG_H_
#define CUSTOMFUNCTIONLOG_H_

#include "CustomFunction.h"

class CustomFunctionLOG: public CustomFunction {
public:
    CustomFunctionLOG(const string str) : CustomFunction(str) {}
    virtual ~CustomFunctionLOG() {}

    virtual double applyFunction(double args[]) const { return log(args[0]); }
};

#endif /* CUSTOMFUNCTIONLOG_H_ */
