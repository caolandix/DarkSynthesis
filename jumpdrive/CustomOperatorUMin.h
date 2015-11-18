/*
 * CustomOperatorUMin.h
 *
 *  Created on: Jun 19, 2014
 *      Author: johndi
 */

#ifndef CUSTOMOPERATORUMIN_H_
#define CUSTOMOPERATORUMIN_H_

#include "CustomOperator.h"

class CustomOperatorUMin: public CustomOperator {
public:
	virtual ~CustomOperatorUMin() {};

	CustomOperatorUMin(const string symbol, const bool leftAssociative, const int precedence) :
		CustomOperator(symbol, leftAssociative, precedence) {};
	CustomOperatorUMin(const string symbol, const bool leftAssociative, const int precedence, const int operandCount) :
		CustomOperator(symbol, leftAssociative, precedence, operandCount) {};
	CustomOperatorUMin(const string symbol, const int precedence) :
		CustomOperator(symbol, precedence) {};
	CustomOperatorUMin(const string symbol) :
		CustomOperator(symbol) {};
	virtual double applyOperation(double values[]) { return -values[0]; };
};

#endif /* CUSTOMOPERATORUMIN_H_ */
