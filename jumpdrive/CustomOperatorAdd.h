/*
 * CustomOperatorAdd.h
 *
 *  Created on: Jun 19, 2014
 *      Author: johndi
 */

#ifndef CUSTOMOPERATORADD_H_
#define CUSTOMOPERATORADD_H_

#include "commondefs.h"
#include "CustomOperator.h"

class CustomOperatorAdd : public CustomOperator {
public:
	virtual ~CustomOperatorAdd() {};

	CustomOperatorAdd(const string symbol, const bool leftAssociative, const int precedence) :
		CustomOperator(symbol, leftAssociative, precedence) {};
	CustomOperatorAdd(const string symbol, const bool leftAssociative, const int precedence, const int operandCount) :
		CustomOperator(symbol, leftAssociative, precedence, operandCount) {};
	CustomOperatorAdd(const string symbol, const int precedence) :
		CustomOperator(symbol, precedence) {};
	CustomOperatorAdd(const string symbol) :
		CustomOperator(symbol) {};
	virtual double applyOperation(double values[]) { return values[1] + values[0]; };
};

#endif /* CUSTOMOPERATORADD_H_ */
