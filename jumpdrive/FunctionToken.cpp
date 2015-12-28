/*
 * FunctionToken.cpp
 *
 *  Created on: Jun 13, 2014
 *      Author: johndi
 */

#include "CustomFunction.h"
#include "FunctionToken.h"

FunctionToken::FunctionToken(string value, CustomFunction *pFunc) : Token(TokenType::TT_FUNCTION, value) {
    m_functionName = pFunc -> Name();
    m_pFunc = pFunc;
}

void FunctionToken::mutateStackForCalculation(stack<double> &valstack, const map<string, double> &) {
    vector<double> vecArgs;
    for (int i = 0; i < m_pFunc -> argc(); i++) {
        vecArgs.push_back(valstack.top());
		valstack.pop();
	}
    double rev_args[vecArgs.size()];
    int i = 0;
    for (vector<double>::reverse_iterator iter = vecArgs.rbegin(); iter != vecArgs.rend(); iter++, i++)
		rev_args[i] = *iter;
    valstack.push(m_pFunc -> applyFunction(rev_args));
}
