/*
 * RPNExpression.cpp
 *
 *  Created on: Jun 13, 2014
 *      Author: caolan
 */

#include "commondefs.h"
#include "jumpdrivedefs.h"

RPNExpression::RPNExpression(const list<Token*> &tokens, const string &expression, const map<string, double> &variables) : Calculable() {
	m_tokens = tokens;
	m_expression = expression;
	m_variables = variables;
}

ValueSet RPNExpression::calculate(const ValueSet values) {
	if (m_variables.size() == 0 && values.size() > 0)
		throw new IllegalArgumentException("there are no variables to set values");
    else if ((unsigned int)values.size() != m_variables.size())
		throw new IllegalArgumentException("The are an unequal number of variables and arguments");

	if (m_variables.size() > 0 && !values.empty()) {
		vector<double>::const_iterator valueIter = values.begin();
		for (map<string, double>::iterator entryIter = m_variables.begin(); entryIter != m_variables.end() && valueIter != values.end(); ++valueIter, ++entryIter) {
			pair<string, double> entry = *entryIter;
			entry.second = *valueIter;
		}
	}

	for (list<Token*>::iterator iter = m_tokens.begin(); iter != m_tokens.end(); iter++) {
		Token *ptok = *iter;
		switch (ptok -> tokenType()) {
        case Token::TT_VARIABLE:
            ((VariableToken *)ptok) -> mutateStackForCalculation(m_valstack, m_variables);
            break;
        case Token::TT_FUNCTION:
            ((FunctionToken *)ptok) -> mutateStackForCalculation(m_valstack, m_variables);
            break;
        case Token::TT_NUMBER:
            ((NumberToken *)ptok) -> mutateStackForCalculation(m_valstack, m_variables);
            break;
        case Token::TT_OPERATOR:
            ((OperatorToken *)ptok) -> mutateStackForCalculation(m_valstack, m_variables);
            break;
        case Token::TT_CALC:
            break;
        case Token::TT_FUNCTION_SEP:
            break;
        case Token::TT_PAREN:
            break;
        case Token::TT_RANGE:
        case Token::TT_NONE:
            break;
        }
	}
	vector<double> eq_values;
	if (m_valstack.size() > 0) {
		eq_values.push_back(m_valstack.top());
		m_valstack.pop();
	}
	return eq_values;
}

void RPNExpression::print(const string &) {
#ifdef _DEBUG
	cout << header << endl;
	cout << "Expression: " << m_expression << endl;
	cout << "List of tokens:" << endl;
	for (list<Token *>::iterator iter = m_tokens.begin(); iter != m_tokens.end(); iter++)
		cout << "\tTokenValue: " << (*iter) -> getTokenChar() << endl;
	cout << "List of variables:" << endl;
	for (map<string, double>::iterator iter = m_variables.begin(); iter != m_variables.end(); iter++) {
		cout << "\tVariable: " << iter -> first << endl;
		cout << "\tValue: " << iter -> second << endl;
	}
	if (!m_valstack.empty())
		cout << "Top of Value Stack: " << m_valstack.top() << endl;
#endif
}
