/*
 * CustomOperatorMult.h
 *
 *  Created on: Jun 19, 2014
 *      Author: johndi
 */

#ifndef CUSTOMOPERATORMULT_H_
#define CUSTOMOPERATORMULT_H_

#include "CustomOperator.h"

class CustomOperatorMult: public CustomOperator {
public:
    virtual ~CustomOperatorMult() {}

	CustomOperatorMult(const string symbol, const bool leftAssociative, const int precedence) :
        CustomOperator(symbol, leftAssociative, precedence) {}
	CustomOperatorMult(const string symbol, const bool leftAssociative, const int precedence, const int operandCount) :
        CustomOperator(symbol, leftAssociative, precedence, operandCount) {}
	CustomOperatorMult(const string symbol, const int precedence) :
        CustomOperator(symbol, precedence) {}
	CustomOperatorMult(const string symbol) :
        CustomOperator(symbol) {}
    virtual double applyOperation(double values[]) { return values[1] * values[0]; }
};

#endif /* CUSTOMOPERATORMULT_H_ */
