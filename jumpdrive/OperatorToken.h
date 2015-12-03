/*
 * OperatorToken.h
 *
 *  Created on: Jun 13, 2014
 *      Author: johndi
 */

#ifndef OPERATORTOKEN_H_
#define OPERATORTOKEN_H_

#include "commondefs.h"
#include "Token.h"
#include "CustomOperator.h"

class OperatorToken : public Token {
public:
    OperatorToken() : Token(Token::TT_OPERATOR), m_poperation(NULL) {}
    OperatorToken(const string &value, CustomOperator *poperation) : Token(Token::TT_OPERATOR, value) { m_poperation = poperation; }
    virtual ~OperatorToken() {}

    double applyOperation(double values[]) { return m_poperation -> applyOperation(values); }

	virtual void mutateStackForInfixTranslation(stack<Token*> &operatorStack, string &output);
	virtual void mutateStackForCalculation(stack<double> &stack, const map<string, double> &variableValues);

	bool operator==(const OperatorToken &);

private:
    bool isLeftAssociative() const { return m_poperation -> leftassociative(); }
    int getPrecedence() const {	return m_poperation -> precedence(); }
	CustomOperator *m_poperation;
};

#endif /* OPERATORTOKEN_H_ */
