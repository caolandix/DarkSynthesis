/*
 * OperatorToken.cpp
 *
 *  Created on: Jun 13, 2014
 *      Author: johndi
 */

#include "jumpdrivedefs.h"

bool OperatorToken::operator==(const OperatorToken &obj) {
	if (obj.tokenType() == tokenType()) {
		;//return t.getValue().equals(this.getValue());
		return true;
	}
	return false;
}

void OperatorToken::mutateStackForCalculation(stack<double> &valstack, const map<string, double> &) {
	double operands[valstack.size()];
	for (int i = 0; i < m_poperation -> operandCount(); i++) {
		operands[i] = valstack.top();
		valstack.pop();
	}
	double val = m_poperation -> applyOperation(operands);
	valstack.push(val);
}

void OperatorToken::mutateStackForInfixTranslation(stack<Token*> &operatorStack, string &output) {
	Token *pbefore = NULL;

	while (!(operatorStack.empty())) {
		pbefore = operatorStack.top();
		if (pbefore -> tokenType() == TokenType::TT_OPERATOR || pbefore -> tokenType() == TokenType::TT_FUNCTION) {
			if (pbefore -> tokenType() == TokenType::TT_FUNCTION) {
				operatorStack.pop();
				output += pbefore -> getValue() + " ";
			}
			else {
				OperatorToken *popToken = (OperatorToken *)pbefore;
				if (isLeftAssociative() && getPrecedence() <= popToken -> getPrecedence()) {
					output += operatorStack.top() -> getValue() + " ";
					operatorStack.pop();
				}
				else if (!isLeftAssociative() && getPrecedence() < popToken -> getPrecedence()) {
					output += operatorStack.top() -> getValue() + " ";
					operatorStack.pop();
				}
				else
					break;
			}
			if (operatorStack.empty())
				break;
			pbefore = operatorStack.top();
		}
		else
			break;
	}
	operatorStack.push(this);
}
/*
void OperatorToken::mutateStackForInfixTranslation(stack<Token*> &operatorStack, string &output) {
	if (operatorStack.empty())
		return;
	Token *pbefore = operatorStack.top();
	while ((!operatorStack.empty() && pbefore) &&
			(pbefore -> tokenType() == TokenType::TT_OPERATOR ||
			pbefore -> tokenType() == TokenType::TT_FUNCTION)) {

		if (pbefore -> tokenType() == TokenType::TT_FUNCTION) {
			operatorStack.pop();
			output += pbefore -> getValue() + " ";
		}
		else {
			OperatorToken *popToken = (OperatorToken *)pbefore;
			if (isLeftAssociative() && getPrecedence() <= popToken -> getPrecedence()) {
				output += operatorStack.top() -> getValue() + " ";
				operatorStack.pop();
			}
			else if (!isLeftAssociative() && getPrecedence() < popToken -> getPrecedence()) {
				output += operatorStack.top() -> getValue() + " ";
				operatorStack.pop();
			}
			else
				break;
		}
		pbefore = operatorStack.top();
	}
	operatorStack.push(this);
}
*/
