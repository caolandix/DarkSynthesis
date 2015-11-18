/*
 * CustomOperator.h
 *
 *  Created on: Jun 13, 2014
 *      Author: caolan
 */

#ifndef CUSTOMOPERATOR_H_
#define CUSTOMOPERATOR_H_

#include "commondefs.h"

class CustomOperator {
public:
	CustomOperator() : m_symbol(""), m_operandCount(0), m_precedence(0), m_leftAssociative(true) {};
	virtual ~CustomOperator() {};

	const string symbol() const { return m_symbol; };
	const int precedence() const { return m_precedence; };
	const int operandCount() const { return m_operandCount; };
	const bool leftassociative() const { return m_leftAssociative; };
	virtual double applyOperation(double values[]) = 0;
private:
	string m_symbol;
	int m_operandCount;
	int m_precedence;
	bool m_leftAssociative;
protected:
	CustomOperator(const string symbol, const bool leftAssociative, const int precedence);
	CustomOperator(const string symbol, const bool leftAssociative, const int precedence, const int operandCount);
	CustomOperator(const string symbol);
	CustomOperator(const string symbol, const int precedence);
};

#endif /* CUSTOMOPERATOR_H_ */
