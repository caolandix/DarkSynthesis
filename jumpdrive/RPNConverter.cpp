/*
 * RPNConverter.cpp
 *
 *  Created on: Jun 13, 2014
 *      Author: caolan
 */

#include "commondefs.h"
#include "jumpdrivedefs.h"

string RPNConverter::substituteUnaryOperators(const string expr, map<string, CustomOperator *> &operators) {
	string resultBuilder;
	uint whitespaceCount = 0;

	for (uint i = 0; i < expr.length(); i++) {
		bool afterOperator = false;
		bool afterParantheses = false;
		bool expressionStart = false;
		char c = expr[i];
		if (isspace(c)) {
			whitespaceCount++;
			resultBuilder += c;
			continue;
		}
		if (resultBuilder.length() == whitespaceCount)
			expressionStart = true;

		// check if last char in the result is an operator
		if (resultBuilder.length() > whitespaceCount) {
			uint idx = resultBuilder.length() - 1 - whitespaceCount;
			if (isOperatorCharacter(resultBuilder[idx], operators))
				afterOperator = true;
			else {
				if (resultBuilder[idx] == '(')
					afterParantheses = true;
			}
		}
		switch (c) {
			case '+':
				if (resultBuilder.length() > 0 && !afterOperator && !afterParantheses && !expressionStart) {
					// not an unary plus so append the char
					resultBuilder += c;
				}
				break;
			case '-':
				if (resultBuilder.length() > 0 && !afterOperator && !afterParantheses && !expressionStart)
					resultBuilder += c;
				else
					resultBuilder += '\'';
				break;
			default:
				resultBuilder += c;
		}
		whitespaceCount = 0;
	}
	return resultBuilder;
}

RPNExpression RPNConverter::toRPNExpression(const string infix, map<string, double> &variables, map<string, CustomFunction *> &customFunctions, map<string, CustomOperator *> &operators) {
	vector<string> variableKeySet;
	string output;
	stack<Token*> operatorStack;

	cout << "RPNConverter::toRPNExpression(), infix string passed in: " << infix << endl;

	for (map<string, double>::iterator iter = variables.begin(); iter != variables.end(); iter++)
		variableKeySet.push_back((*iter).first);
	Tokenizer tokenizer(variableKeySet, customFunctions, operators);
	list<Token*> tokens = tokenizer.getTokens(substituteUnaryOperators(infix, operators));
	validateRPNExpression(tokens, operators);
	for (list<Token*>::iterator iter = tokens.begin(); iter != tokens.end(); iter++) {
		switch ((*iter) -> tokenType()) {
			case Token::TT_NUMBER: {
				NumberToken *ptok = (NumberToken *)(*iter);
				ptok -> mutateStackForInfixTranslation(operatorStack, output);
			}
			break;
			case Token::TT_OPERATOR: {
				OperatorToken *ptok = (OperatorToken *)(*iter);
				ptok -> mutateStackForInfixTranslation(operatorStack, output);
			}
			break;
			case Token::TT_FUNCTION: {
				FunctionToken *ptok = (FunctionToken *)(*iter);
				ptok -> mutateStackForInfixTranslation(operatorStack, output);
			}
			break;
			case Token::TT_PAREN: {
				ParenthesisToken *ptok = (ParenthesisToken *)(*iter);
				ptok -> mutateStackForInfixTranslation(operatorStack, output);
			}
			break;
			case Token::TT_VARIABLE: {
				VariableToken *ptok = (VariableToken *)(*iter);
				ptok -> mutateStackForInfixTranslation(operatorStack, output);
			}
			break;
		}
	}
	// all tokens read, put the rest of the operations on the output;
	while (!operatorStack.empty()) {
		output += operatorStack.top() -> getValue() + " ";
		cout << "Stack operator: " << operatorStack.top() -> getValue() << endl;
		operatorStack.pop();
	}
	cout << "RPNConverter::toRPNExpression(), output after mutating stack for all tokens: " << output << endl;
	string postfix = ::trim(output);
	tokens = tokenizer.getTokens(postfix);
	RPNExpression rpnExpression(tokens, postfix, variables);
	return rpnExpression;
}

void RPNConverter::validateRPNExpression(list<Token*> &tokens, map<string, CustomOperator *> &operators) {
	list<Token*>::iterator iter = tokens.begin();
	list<Token*>::iterator prevIter = tokens.begin();
	vector<Token*> vecTokens;

	for (list<Token*>::iterator iter = tokens.begin(); iter != tokens.end(); iter++)
		vecTokens.push_back(*iter);
	for (int i = 1; i < vecTokens.size(); i++) {
		if (vecTokens[i - 1] -> tokenType() == Token::TT_NUMBER) {
			if (vecTokens[i] -> tokenType() == Token::TT_VARIABLE ||
				(vecTokens[i] -> tokenType() == Token::TT_PAREN && ((ParenthesisToken *)vecTokens[i]) -> isOpen()) ||
				vecTokens[i] -> tokenType() == Token::TT_FUNCTION) {
				; // thrown error here
			}
		}
	}
}

bool RPNConverter::isOperatorCharacter(const char c, map<string, CustomOperator *> &operators) {
	for (map<string, CustomOperator *>::iterator iter = operators.begin(); iter != operators.end(); iter++) {
		string symbol = (*iter).first;
		if (symbol.find_first_of(c) != string::npos)
			return true;
	}
	return false;
}
