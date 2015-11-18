/*
 * CustomOperatorMod.h
 *
 *  Created on: Jun 19, 2014
 *      Author: johndi
 */

#ifndef CUSTOMOPERATORMOD_H_
#define CUSTOMOPERATORMOD_H_

#include "CustomOperator.h"

class CustomOperatorMod: public CustomOperator {
public:
	virtual ~CustomOperatorMod() {};

	CustomOperatorMod(const string symbol, const bool leftAssociative, const int precedence) :
		CustomOperator(symbol, leftAssociative, precedence) {};
	CustomOperatorMod(const string symbol, const bool leftAssociative, const int precedence, const int operandCount) :
		CustomOperator(symbol, leftAssociative, precedence, operandCount) {};
	CustomOperatorMod(const string symbol, const int precedence) :
		CustomOperator(symbol, precedence) {};
	CustomOperatorMod(const string symbol) :
		CustomOperator(symbol) {};
	virtual double applyOperation(double values[]) { return (int)values[1] % (int)values[0]; };
};

#endif /* CUSTOMOPERATORMOD_H_ */
