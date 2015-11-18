/*
 * ParenthesisToken.cpp
 *
 *  Created on: Jun 13, 2014
 *      Author: caolan
 */

#include "ParenthesisToken.h"
#include "Token.h"

void ParenthesisToken::mutateStackForInfixTranslation(stack<Token*> &operatorStack, string &output) {
	if (isOpen())
		operatorStack.push(this);
	else {

		// operate only on a non-empty list -- undefined behaviour otherwise
		if (!operatorStack.empty()) {

			Token *pnext = operatorStack.top();
			while (1) {
				if (pnext -> tokenType() == Token::TT_OPERATOR || pnext -> tokenType() == Token::TT_FUNCTION) {
					output += operatorStack.top() -> getValue() + " ";
				}
				else if (pnext -> tokenType() == Token::TT_PAREN && !(((ParenthesisToken *)(pnext)) -> isOpen())) {
					//output += operatorStack.top() -> getValue() + " ";
					;
				}
				else
					break;
				operatorStack.pop();
				pnext = operatorStack.top();
				if (operatorStack.empty())
					return;
			}
			operatorStack.pop();
		}
	}
}
/*
void ParenthesisToken::mutateStackForInfixTranslation(stack<Token*> &operatorStack, string &output) {
	if (isOpen())
		operatorStack.push(this);
	else {
		if (!operatorStack.empty()) {
			Token *ptok = operatorStack.top();
			while (ptok -> tokenType() == Token::TT_OPERATOR ||
					ptok -> tokenType() == Token::TT_FUNCTION ||
					((ptok -> tokenType() == Token::TT_PAREN) && !(((ParenthesisToken *)(ptok)) -> isOpen()))) {

				// NOTE: it adds the open paren to the output here... Is that okay?
				output += operatorStack.top() -> getValue() + " ";
				operatorStack.pop();
				if (operatorStack.empty())
					return;
			}
			operatorStack.pop();
		}
	}
}
*/
