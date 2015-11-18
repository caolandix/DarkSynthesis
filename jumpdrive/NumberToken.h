/*
 * NumberToken.h
 *
 *  Created on: Jun 13, 2014
 *      Author: johndi
 */

#ifndef NUMBERTOKEN_H_
#define NUMBERTOKEN_H_

#include "commondefs.h"
#include "Token.h"

class NumberToken : public Token {
public:
	NumberToken(const string value);
	NumberToken() : m_doubleValue(0.0), Token(TokenType::TT_NUMBER) {};
	virtual ~NumberToken() {};

	virtual void mutateStackForInfixTranslation(stack<Token*> &operatorStack, string &output) { output += getValue() + " "; };
	virtual void mutateStackForCalculation(stack<double> &stack, map<string, double> &variableValues) { stack.push(m_doubleValue); };
private:
	double m_doubleValue;
};

#endif /* NUMBERTOKEN_H_ */
