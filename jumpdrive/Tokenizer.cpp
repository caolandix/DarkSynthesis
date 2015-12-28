/*
 * Tokenizer.cpp
 *
 *  Created on: Jun 13, 2014
 *      Author: caolan
 */

#include "commondefs.h"
#include "jumpdrivedefs.h"


Tokenizer::Tokenizer(vector<string> variableNames, map<string, CustomFunction *> functions, map<string, CustomOperator *> operators) {
	m_variableNames = variableNames;
	m_functions = functions;
	m_operators = operators;
	setParenTokens();
}

void Tokenizer::setParenTokens() {
	m_parenTokens = "{}()[]";
}

bool Tokenizer::charInTokenSet(const char c, const string &tokenset) const {
    for (unsigned int i = 0; i < tokenset.size(); i++) {
		if (tokenset[i] == c)
			return true;
	}
	return false;
}

bool Tokenizer::isVariable(const string &name) const {
	if (!m_variableNames.empty()) {
		for (vector<string>::const_iterator iter = m_variableNames.begin(); iter != m_variableNames.end(); iter++) {
			string str = *iter;
			if (!name.compare(*iter))
				return true;
		}
	}
	return false;
}

bool Tokenizer::isOperatorCharacter(const char c) const {
	for (map<string, CustomOperator *>::const_iterator iter = m_operators.begin(); iter != m_operators.end(); iter++) {
		string symbol = (*iter).first;
		if (symbol.find_first_of(c) != string::npos)
			return true;
	}
	return false;
}

list<Token*> Tokenizer::getTokens(string &expression) {
	list<Token*> tokens;
	int openBraces = 0;
	int openCurly = 0;
	int openSquare = 0;

#ifdef _DEBUG
	cout << "Tokenizer::getTokens(), input expression: " << expression << endl;
#endif

    // iterate over the chars and fork on different types of input
	for (uint i = 0; i < expression.length(); i++) {
		char c = expression[i];
		if (c == ' ')
			continue;
		if (isdigit(c)) {
			string valueBuilder;

			// handle the numbers of the expression
			valueBuilder.push_back(c);
			int numberLen = 1;
			bool lastCharNotationSeparator = false; // needed to determine if a + or - following an e/E is a unary operation
			bool notationSeparatorOccured = false; // to check if only one notation separator has occured
			while (expression.length() > i + numberLen) {
				if (isDigitOrDecimalSeparator(expression[i + numberLen])) {
					valueBuilder.push_back(expression[i + numberLen]);
					lastCharNotationSeparator = false;
				}
				else if (isNotationSeparator(expression[i + numberLen])) {
					if (notationSeparatorOccured)
						throw new UnparsableExpressionException("Number can have only one notation separator 'e/E'");
					valueBuilder.push_back(expression[i + numberLen]);
					lastCharNotationSeparator = true;
					notationSeparatorOccured = true;
				}
				else if (lastCharNotationSeparator && (expression[i + numberLen] == '-' || expression[i + numberLen] == '+')) {
					valueBuilder.push_back(expression[i + numberLen]);
					lastCharNotationSeparator = false;
				}
				else
					break; // break out of the while loop here, since the number seem finished
				numberLen++;
			}
			i += numberLen - 1;
			tokens.push_back(new NumberToken(valueBuilder));
		}
		else if (isalpha(c) || c == '_') {

			// can be a variable or function
			string nameBuilder;
			nameBuilder.push_back(c);
			int offset = 1;
			while (expression.length() > i + offset && (isalnum(expression[i + offset]) || expression[i + offset] == '_'))
				nameBuilder.push_back(expression[i + offset++]);
			string name(nameBuilder);
			if (isVariable(name)) {
				// a variable
				i += offset - 1;
				tokens.push_back(new VariableToken(name));
			}
			else if (isFunction(name)) {

                // might be a function
				i += offset - 1;
				map<string, CustomFunction *>::const_iterator iter = m_functions.find(name);
				if (iter != m_functions.end())
					tokens.push_back(new FunctionToken(name, (*iter).second));
			}
			else {
				// an unknown symbol was encountered
				; //throw new UnparsableExpressionException(expression, c, i + 1);
			}
		}
		else if (c == ',')
			tokens.push_back(new FunctionSeparatorToken());
		else if (isOperatorCharacter(c)) {
			// might be an operation
			string symbolBuilder;
			symbolBuilder.push_back(c);
			int offset = 1;
			while (expression.length() > i + offset && (isOperatorCharacter(expression[i + offset])) && isOperatorStart(symbolBuilder + expression[i + offset])) {
				symbolBuilder += expression[i + offset];
				offset++;
			}
			string symbol = symbolBuilder;
			map<string, CustomOperator *>::const_iterator iter = m_operators.find(symbol);
			if (iter != m_operators.end()) {
				i += offset - 1;
				tokens.push_back(new OperatorToken(symbol, (*iter).second));
			}
		}
		else if (charInTokenSet(c, m_parenTokens)) {
			if (c == '(')
				openBraces++;
			else if (c == '{')
				openCurly++;
			else if (c == '[')
				openSquare++;
			else if (c == ')')
				openBraces--;
			else if (c == '}')
				openCurly--;
			else if (c == ']')
				openSquare--;
			else {
				// an unknown symbol was encountered
				; //throw new UnparsableExpressionException(expression, c, i + 1);
			}
			tokens.push_back(new ParenthesisToken(c));
		}
	}
	if (openCurly || openBraces || openSquare) {
		string errorBuilder("There are ");
		bool first = true;
		if (openBraces) {
			errorBuilder += abs(openBraces) + " unmatched parentheses ";
			first = false;
		}
		if (openCurly) {
			if (!first)
				errorBuilder += " and ";
			errorBuilder += abs(openCurly) + " unmatched curly brackets ";
			first = false;
		}
		if (openSquare) {
			if (!first)
				errorBuilder += " and ";
			errorBuilder += abs(openSquare) + " unmatched square brackets ";
			first = false;
		}
		errorBuilder += "in expression '" + expression + "'";
		throw new UnparsableExpressionException(errorBuilder);
	}
	return tokens;
}

void Tokenizer::print_tokens(const string &, list<Token*>) {
#ifdef _DEBUG
	cout << str << endl;
	cout << "Token List:" << endl;
	for (list<Token*>::iterator iter = token_list.begin(); iter != token_list.end(); iter++) {
		if ((*iter) -> getTokenChar() == '(' || (*iter) -> getTokenChar() == ')')
			int i = 0;
		cout << "TokenValue: " << (*iter) -> getTokenChar() << endl;
	}
#endif
}

bool Tokenizer::isFunction(const string &name) const {
	map<string, CustomFunction *>::const_iterator iter = m_functions.find(name);
	return (iter != m_functions.end()) ? true : false;
}

bool Tokenizer::isOperatorStart(const string &op) const {
	for (map<string, CustomOperator *>::const_iterator iter = m_operators.begin(); iter != m_operators.end(); iter++) {
		if ((*iter).first.find(op) == 0)
			return true;
	}
	return false;
}
