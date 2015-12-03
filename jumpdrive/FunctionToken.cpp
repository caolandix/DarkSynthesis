/*
 * FunctionToken.cpp
 *
 *  Created on: Jun 13, 2014
 *      Author: johndi
 */

#include "CustomFunction.h"
#include "FunctionToken.h"

FunctionToken::FunctionToken(string value, CustomFunction *pfunction) : Token(TokenType::TT_FUNCTION, value) {
	m_functionName = pfunction -> get_name();
	m_pfunction = pfunction;
}
void FunctionToken::mutateStackForCalculation(stack<double> &valstack, const map<string, double> &) {
	vector<double> args;
	for (int i = 0; i < m_pfunction -> getArgumentCount(); i++) {
		args.push_back(valstack.top());
		valstack.pop();
	}
	double rev_args[args.size()];
	int i = 0;
	for (vector<double>::reverse_iterator iter = args.rbegin(); iter != args.rend(); iter++, i++)
		rev_args[i] = *iter;
	valstack.push(m_pfunction -> applyFunction(rev_args));
}
