/*
 * FunctionToken.h
 *
 *  Created on: Jun 13, 2014
 *      Author: johndi
 */

#ifndef FUNCTIONTOKEN_H_
#define FUNCTIONTOKEN_H_

#include "commondefs.h"
#include "CustomFunction.h"
#include "Token.h"

class FunctionToken : public Token {
public:
    FunctionToken() : Token(Token::TT_FUNCTION), m_pFunc(NULL) {}
	FunctionToken(string, CustomFunction *);
    virtual ~FunctionToken() {}

    const string getFunctionName() const { return m_functionName; }
    CustomFunction *getFunction() const { return m_pFunc; }

    bool operator==(const FunctionToken &obj) { return (m_functionName == obj.getFunctionName()) ? true : false; }
    virtual void mutateStackForInfixTranslation(stack<Token*> &operatorStack, string &) { operatorStack.push(this); }
    virtual void mutateStackForCalculation(stack<double> &stack, const map<string, double> &variableValues);
private:
	string m_functionName;
    CustomFunction *m_pFunc;
};


#endif /* FUNCTIONTOKEN_H_ */
