/*
 * ExpressionBuilder.h
 *
 *  Created on: Jun 13, 2014
 *      Author: johndi
 */

#ifndef EXPRESSIONBUILDER_H_
#define EXPRESSIONBUILDER_H_

#include "commondefs.h"
#include "jumpdrivedefs.h"
#include "RPNExpression.h"

string &ltrim(string &s);
string &rtrim(string &s);
string &trim(string &s);

class ExpressionBuilder {
public:

	static inline string &trim(string &s);

	typedef pair<string, CustomOperator *> CustomOperatorPair;
	typedef pair<string, CustomFunction *> CustomFunctionPair;
	ExpressionBuilder();
	ExpressionBuilder(const string expression);
	virtual ~ExpressionBuilder();

	RPNExpression build();
	ValueSet calculate();
	void withCustomFunctions(const vector<CustomFunction *> &functions);
	void withVariableNames(const vector<string> &variableNames);
	void withVariables(const map<string, double> &variableMap);
	void withOperations(vector<CustomOperator *> &operations);

    void withOperation(CustomOperator *poperation) { m_customOperators.insert(pair<string, CustomOperator *>(poperation -> symbol(), poperation)); }
    void withExpression(const string expression) { m_expression = expression; }
    void withVariable(const string &variableName, const double value) { m_variables.insert(pair<string, double>(variableName, value)); }
    void withCustomFunction(CustomFunction *pfunction) { m_customFunctions.insert(pair<string, CustomFunction *>(pfunction -> get_name(), pfunction)); }
	static const string PROPERTY_UNARY_HIGH_PRECEDENCE;
	/**
	 * Property name for unary precedence choice. You can set System.getProperty(PROPERTY_UNARY_HIGH_PRECEDENCE,"false")
	 * in order to change evaluation from an expression like "-3^2" from "(-3)^2" to "-(3^2)"
	 */
private:
	map<string, double> m_variables;
	map<string, CustomFunction *> m_customFunctions;
	map<string, CustomOperator *> m_builtInOperators;
	map<string, CustomOperator *> m_customOperators;
	ValueSet m_eq_vals;
	list<char> m_validOperatorSymbols;
	bool m_highUnaryPrecedence;
	string m_expression;

	void getBuiltinOperators();
	void getBuiltinFunctions();
	void getValidOperators();
	void checkVariableName(string varName) const;
};

#endif /* EXPRESSIONBUILDER_H_ */
