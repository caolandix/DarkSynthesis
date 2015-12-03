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
    NumberToken() : Token(TokenType::TT_NUMBER), m_doubleValue(0.0) {}
    virtual ~NumberToken() {}

    virtual void mutateStackForInfixTranslation(stack<Token*> &, string &output) { output += getValue() + " "; }
    virtual void mutateStackForCalculation(stack<double> &stack, map<string, double> &) { stack.push(m_doubleValue); }
private:
	double m_doubleValue;
};

#endif /* NUMBERTOKEN_H_ */
