/*
 * CustomOperatorDiv.h
 *
 *  Created on: Jun 19, 2014
 *      Author: johndi
 */

#ifndef CUSTOMOPERATORDIV_H_
#define CUSTOMOPERATORDIV_H_

#include "CustomOperator.h"
#include "ArithmeticException.h"

class CustomOperatorDiv: public CustomOperator {
public:
	virtual ~CustomOperatorDiv() {};

	CustomOperatorDiv(const string symbol, const bool leftAssociative, const int precedence) :
		CustomOperator(symbol, leftAssociative, precedence) {};
	CustomOperatorDiv(const string symbol, const bool leftAssociative, const int precedence, const int operandCount) :
		CustomOperator(symbol, leftAssociative, precedence, operandCount) {};
	CustomOperatorDiv(const string symbol, const int precedence) :
		CustomOperator(symbol, precedence) {};
	CustomOperatorDiv(const string symbol) :
		CustomOperator(symbol) {};
	virtual double applyOperation(double values[]) {
		if (values[0] == 0.0)
			throw new ArithmeticException("Division by zero!");
		return values[1] / values[0];
	};
};

#endif /* CUSTOMOPERATORDIV_H_ */
