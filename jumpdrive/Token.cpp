/*
 * Token.cpp
 *
 *  Created on: Aug 7, 2014
 *      Author: johndi
 */


#include "commondefs.h"
#include "jumpdrivedefs.h"
#include "Token.h"

// #include "CalculationToken.h"

Token *Token::Create(TokenType tt) {
	switch (tt) {
    case TT_CALC:
        return NULL;// return new CalculationToken();
	case TT_FUNCTION:
		return new FunctionToken();
	case TT_FUNCTION_SEP:
		return new FunctionSeparatorToken();
	case TT_NUMBER:
		return new NumberToken();
	case TT_OPERATOR:
		return new OperatorToken();
	case TT_PAREN:
		return new ParenthesisToken();
	case TT_VARIABLE:
		return new VariableToken();
    case TT_RANGE:
    case TT_NONE:
        return NULL;
    }
	return NULL;
}

