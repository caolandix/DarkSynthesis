/*
 * CustomOperatorSub.h
 *
 *  Created on: Jun 19, 2014
 *      Author: johndi
 */

#ifndef CUSTOMOPERATORSUB_H_
#define CUSTOMOPERATORSUB_H_

#include "CustomOperator.h"

class CustomOperatorSub: public CustomOperator {
public:
    virtual ~CustomOperatorSub() {}

	CustomOperatorSub(const string symbol, const bool leftAssociative, const int precedence) :
        CustomOperator(symbol, leftAssociative, precedence) {}
	CustomOperatorSub(const string symbol, const bool leftAssociative, const int precedence, const int operandCount) :
        CustomOperator(symbol, leftAssociative, precedence, operandCount) {}
	CustomOperatorSub(const string symbol, const int precedence) :
        CustomOperator(symbol, precedence) {}
	CustomOperatorSub(const string symbol) :
        CustomOperator(symbol) {}
    virtual double applyOperation(double values[]) { return values[1] - values[0]; }

};

#endif /* CUSTOMOPERATORSUB_H_ */
