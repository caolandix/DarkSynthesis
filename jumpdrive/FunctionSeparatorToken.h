/*
 * FunctionSeparatorToken.h
 *
 *  Created on: Jun 13, 2014
 *      Author: johndi
 */

#ifndef FUNCTIONSEPARATORTOKEN_H_
#define FUNCTIONSEPARATORTOKEN_H_

#include "commondefs.h"
#include "Token.h"

class FunctionSeparatorToken : public Token {
public:
    FunctionSeparatorToken() : Token(Token::TT_FUNCTION_SEP, ",") {}
    virtual ~FunctionSeparatorToken() {}

	virtual void mutateStackForInfixTranslation(stack<Token*> &operatorStack, string &output) {
		while ((operatorStack.top() -> tokenType() != Token::TT_PAREN) && operatorStack.top() -> getValue().compare("(") == 0) {
			output += operatorStack.top() -> getValue() + " ";
			operatorStack.pop();
		}
	}
};
#endif /* FUNCTIONSEPARATORTOKEN_H_ */
