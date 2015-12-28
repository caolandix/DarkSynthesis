/*
 * ExpressionBuilder.cpp
 *
 *  Created on: Jun 13, 2014
 *      Author: johndi
 */

#include "commondefs.h"
#include "jumpdrivedefs.h"
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function name: ltrim()
// Purpose: trim whitespace from the start of the string
// Inputs:
//		- szBuffer: string to trim
// Output: reference to the newly trimmed string
// Notes:
//
string &ltrim(string &szBuffer) {
	szBuffer.erase(szBuffer.begin(), find_if(szBuffer.begin(), szBuffer.end(), not1(ptr_fun<int, int>(isspace))));
    return szBuffer;
}
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// trim from end
string &rtrim(string &s) {
	s.erase(find_if(s.rbegin(), s.rend(), not1(std::ptr_fun<int, int>(isspace))).base(), s.end());
	return s;
}
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// trim from both ends
string &trim(string &s) {
	return ltrim(rtrim(s));
}
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function Name:
// Purpose:
// Inputs:
// Output:
// Notes:
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
ExpressionBuilder::ExpressionBuilder() {
	m_highUnaryPrecedence = false;
}
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function Name:
// Purpose:
// Inputs:
// Output:
// Notes:
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
ExpressionBuilder::ExpressionBuilder(string strEquation) {
	string var;
    VecStr fields;

	split(fields, strEquation, is_any_of(","));
    for (VecStr::iterator iter = fields.begin() + 1; iter != fields.end(); iter++) {
		double val = 0.0;
        VecStr tmp;

		// Split the variable from it's value
		split(tmp, ::trim(*iter), is_any_of("="));
		withVariable(::trim(tmp[0]), val = atof(::trim(tmp[1]).c_str()));
		m_eq_vals.push_back(val);
	}

	string expression = ::trim(fields[0]);
	if (expression.length() == 0)
		throw new IllegalArgumentException("Expression can not be empty!.");
	m_expression = expression;

    if (getenv("PROPERTY_UNARY_HIGH_PRECEDENCE"))
    	var = getenv("PROPERTY_UNARY_HIGH_PRECEDENCE");
	m_highUnaryPrecedence = (var.length() == 0 || var != "false");
	getBuiltinFunctions();
	getBuiltinOperators();
	getValidOperators();
}

ValueSet ExpressionBuilder::calculate() {
	return build().calculate(m_eq_vals);
}
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function Name: dtor
// Purpose:
// Inputs:
// Output:
// Notes:
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
ExpressionBuilder::~ExpressionBuilder() {
	if (m_builtInOperators.size() > 0) {
		for (map<string, CustomOperator *>::iterator iter = m_builtInOperators.begin(); iter != m_builtInOperators.end(); iter++)
			delete (*iter).second;
		for (map<string, CustomOperator *>::iterator iter = m_customOperators.begin(); iter != m_customOperators.end(); iter++)
			delete (*iter).second;
		for (map<string, CustomFunction *>::iterator iter = m_customFunctions.begin(); iter != m_customFunctions.end(); iter++)
			delete (*iter).second;
	}
}
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function Name: getValidOperators
// Purpose: Creates a list of valid operators for custom usage
// Inputs:
// Output:
// Notes:
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
void ExpressionBuilder::getValidOperators() {
	string arr("!#§$&;:~<>|=");
	for (uint i = 0; i < arr.length(); i++)
		m_validOperatorSymbols.push_back(arr[i]);
}
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function Name: getBuiltinOperators
// Purpose: Creates the list of standard mathematics operators
// Inputs:
// Output:
// Notes:
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
void ExpressionBuilder::getBuiltinOperators() {
	m_builtInOperators.insert(CustomOperatorPair("+", new CustomOperatorAdd("+")));
	m_builtInOperators.insert(CustomOperatorPair("-", new CustomOperatorSub("-")));
	m_builtInOperators.insert(CustomOperatorPair("/", new CustomOperatorDiv("/", 3)));
	m_builtInOperators.insert(CustomOperatorPair("*", new CustomOperatorMult("*", 3)));
	m_builtInOperators.insert(CustomOperatorPair("\'", new CustomOperatorUMin("\'", false, m_highUnaryPrecedence ? 7 : 5, 1)));
	m_builtInOperators.insert(CustomOperatorPair("^", new CustomOperatorPow("^", false, 5, 2)));
	m_builtInOperators.insert(CustomOperatorPair("%", new CustomOperatorMod("%", true, 3)));
}
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function Name: getBuiltinFunctions
// Purpose: built in mathematical functions
// Inputs:
// Output:
// Notes:
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
void ExpressionBuilder::getBuiltinFunctions() {
	try {
		m_customFunctions.insert(CustomFunctionPair("abs", new CustomFunctionABS("abs")));
		m_customFunctions.insert(CustomFunctionPair("acos", new CustomFunctionACOS("acos")));
		m_customFunctions.insert(CustomFunctionPair("asin", new CustomFunctionASIN("asin")));
		m_customFunctions.insert(CustomFunctionPair("atan", new CustomFunctionATAN("atan")));
		m_customFunctions.insert(CustomFunctionPair("cbrt", new CustomFunctionCBRT("cbrt")));
		m_customFunctions.insert(CustomFunctionPair("ceil", new CustomFunctionCEILING("ceil")));
		m_customFunctions.insert(CustomFunctionPair("cos", new CustomFunctionCOS("cos")));
		m_customFunctions.insert(CustomFunctionPair("cosh", new CustomFunctionCOSH("cosh")));
		m_customFunctions.insert(CustomFunctionPair("exp", new CustomFunctionEXP("exp")));
		m_customFunctions.insert(CustomFunctionPair("expm1", new CustomFunctionEXPM1("expm1")));
		m_customFunctions.insert(CustomFunctionPair("floor", new CustomFunctionFLOOR("floor")));
		m_customFunctions.insert(CustomFunctionPair("log", new CustomFunctionLOG("log")));
		m_customFunctions.insert(CustomFunctionPair("sin", new CustomFunctionSIN("sin")));
		m_customFunctions.insert(CustomFunctionPair("sinh", new CustomFunctionSINH("sinh")));
		m_customFunctions.insert(CustomFunctionPair("sqrt", new CustomFunctionSQRT("sqrt")));
		m_customFunctions.insert(CustomFunctionPair("tan", new CustomFunctionTAN("tan")));
		m_customFunctions.insert(CustomFunctionPair("tanh", new CustomFunctionTANH("tanh")));
        m_customFunctions.insert(CustomFunctionPair("diff", new CustomFunctionDifferentiate("diff")));
        m_customFunctions.insert(CustomFunctionPair("integ", new CustomFunctionIntegrate("integ")));
    }
	catch (InvalidCustomFunctionException &e) {

		// this should not happen...
		;//throw new exception(e);
	}
}
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function Name: build
// Purpose:
// Inputs:
// Output:
// Notes:
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
RPNExpression ExpressionBuilder::build() {
	for (map<string, CustomOperator *>::iterator iter = m_customOperators.begin(); iter != m_customOperators.end(); ++iter) {
		CustomOperator *pop = (*iter).second;
		for (int i = 0; i < (int)(pop -> symbol().length()); i++) {
			list<char>::iterator iter = find(m_validOperatorSymbols.begin(), m_validOperatorSymbols.end(), pop -> symbol()[i]);
			if (iter == m_validOperatorSymbols.end())
				throw new UnparsableExpressionException("" + pop -> symbol() + " is not a valid symbol for an operator please choose from: !,#,§,$,&,;,:,~,<,>,|,=");
		}
		m_builtInOperators.insert(*iter);
	}

	for (map<string, double>::iterator iter = m_variables.begin(); iter != m_variables.end(); ++iter) {
		string varName = (*iter).first;
		checkVariableName(varName);
		if (m_customFunctions.find(varName) != m_customFunctions.end())
			throw new UnparsableExpressionException("Variable '" + varName + "' cannot have the same name as a function");
	}
	RPNConverter rpnConverter;
	RPNExpression rpnExpr = rpnConverter.toRPNExpression(m_expression, m_variables, m_customFunctions, m_builtInOperators);
	return rpnExpr;
}
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function Name: checkVariableName
// Purpose: Lexical parser for variable names
// Inputs:
// Output:
// Notes:
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
void ExpressionBuilder::checkVariableName(const string varName) const {
	if (!isalpha(varName[0]) && varName[0] != '_')
		throw new UnparsableExpressionException(varName + " is not a valid variable name: character '" + varName[0] + " at " + boost::lexical_cast<std::string>(0));
	for (int i = 1; i < (int)(varName.length()); i++) {
		if (!isalnum(varName[i]) && varName[i] != '_')
			throw new UnparsableExpressionException(varName + " is not a valid variable name: character '" + varName[i] + " at " +  boost::lexical_cast<std::string>(i));
	}
}
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function Name:
// Purpose:
// Inputs:
// Output:
// Notes:
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
void ExpressionBuilder::withCustomFunctions(const vector<CustomFunction *> &functions) {
	for (vector<CustomFunction *>::const_iterator iter = functions.begin(); iter != functions.end(); iter++)
		withCustomFunction(*iter);
}
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function Name:
// Purpose:
// Inputs:
// Output:
// Notes:
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
void ExpressionBuilder::withVariableNames(const VecStr &variableNames) {
    for (VecStrIter iter = variableNames.begin(); iter != variableNames.end(); iter++)
		m_variables.insert(pair<string, double>(*iter, NULL));
}
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function Name:
// Purpose:
// Inputs:
// Output:
// Notes:
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
void ExpressionBuilder::withVariables(const map<string, double> &variableMap) {
	for (map<string, double>::const_iterator iter = variableMap.begin(); iter != variableMap.end(); iter++) {
		pair<string, double> obj((*iter).first, (*iter).second);
		m_variables.insert(obj);
	}
}
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function Name: withOperations()
// Purpose: Stores each operation in a vector
// Inputs:
//	- operations: vector referene of the operations
// Output: n/a
// Notes:
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
void ExpressionBuilder::withOperations(vector<CustomOperator *> &operations) {
	for (vector<CustomOperator *>::const_iterator iter = operations.begin(); iter != operations.end(); iter++)
		withOperation(*iter);
}
