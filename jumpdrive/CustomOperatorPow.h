/*
 * CustomOperatorPow.h
 *
 *  Created on: Jun 19, 2014
 *      Author: johndi
 */

#ifndef CUSTOMOPERATORPOW_H_
#define CUSTOMOPERATORPOW_H_

#include "CustomOperator.h"

class CustomOperatorPow : public CustomOperator {
public:
	virtual ~CustomOperatorPow() {};

	CustomOperatorPow(const string symbol, const bool leftAssociative, const int precedence) :
		CustomOperator(symbol, leftAssociative, precedence) {};
	CustomOperatorPow(const string symbol, const bool leftAssociative, const int precedence, const int operandCount) :
		CustomOperator(symbol, leftAssociative, precedence, operandCount) {};
	CustomOperatorPow(const string symbol, const int precedence) :
		CustomOperator(symbol, precedence) {};
	CustomOperatorPow(const string symbol) :
		CustomOperator(symbol) {};
	virtual double applyOperation(double values[]) { return pow(values[1], values[0]); };
};

#endif /* CUSTOMOPERATORPOW_H_ */
