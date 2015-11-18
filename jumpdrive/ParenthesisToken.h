/*
 * ParenthesisToken.h
 *
 *  Created on: Jun 13, 2014
 *      Author: caolan
 */

#ifndef PARENTHESISTOKEN_H_
#define PARENTHESISTOKEN_H_

#include "commondefs.h"
#include "Token.h"

class ParenthesisToken : public Token {
public:
	ParenthesisToken() : Token(TT_PAREN) {};
	ParenthesisToken(const string value) : Token(TT_PAREN, value) {};
	ParenthesisToken(const char value) : Token(TT_PAREN, value) {};
	virtual ~ParenthesisToken() {};

	bool operator==(ParenthesisToken &obj) {
		if (obj == *this)
			return true;
		return getValue() == obj.getValue();
	}

	bool isOpen() const { return getValue() == "(" || getValue() == "[" || getValue() == "{"; };
	virtual void mutateStackForInfixTranslation(stack<Token *> &operatorStack, string &output);
};
#endif /* PARENTHESISTOKEN_H_ */
