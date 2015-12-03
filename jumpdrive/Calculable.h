/*
 * Calculable.h
 *
 *  Created on: Jun 11, 2014
 *      Author: johndi
 */

#ifndef CALCULABLE_H_
#define CALCULABLE_H_

#include "commondefs.h"

class Calculable {
public:
    virtual ~Calculable() {}

    virtual double calculate() const { return 0.0; }
    virtual double calculate(vector<double> ) const { return 0.0; }
    virtual string getExpression() const { return ""; }
    virtual void setVariable(string , double ) {}
};

#endif /* CALCULABLE_H_ */
