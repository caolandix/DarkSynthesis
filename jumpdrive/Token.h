/*
 * Token.h
 *
 *  Created on: Jun 11, 2014
 *      Author: johndi
 */

#ifndef TOKEN_H_
#define TOKEN_H_

#include "commondefs.h"

class Token {
	public:
		typedef enum { TT_NONE, TT_CALC, TT_FUNCTION, TT_FUNCTION_SEP, TT_NUMBER, TT_OPERATOR, TT_PAREN, TT_VARIABLE, TT_RANGE } TokenType;

		Token() : m_tt(TT_NONE) {};
		Token(TokenType tt) : m_tt(tt) {};
		Token(TokenType tt, const string &str) : m_value(str), m_tt(tt) {};
		Token(TokenType tt, const char c) : m_tt(tt) { m_value.push_back(c); };
		virtual ~Token() {};

		virtual void mutateStackForInfixTranslation(stack<Token*> &operatorStack, string &output) = 0;
		Token *Create(TokenType tt);
		string getValue() const { return m_value; };
		char getTokenChar() const { return (m_value.c_str())[0]; };
		TokenType tokenType() const { return m_tt; };
	private:
		string m_value;
		TokenType m_tt;
};

#endif /* TOKEN_H_ */
