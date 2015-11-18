/*
 * VariableToken.h
 *
 *  Created on: Jun 13, 2014
 *      Author: caolan
 */

#ifndef VARIABLETOKEN_H_
#define VARIABLETOKEN_H_

#include "commondefs.h"
#include "jumpdrivedefs.h"

class VariableToken : public Token {
public:
	VariableToken() :Token(TT_VARIABLE) {};
	VariableToken(const string val) : Token(TT_VARIABLE, val) {};
	virtual ~VariableToken() {};

	bool operator==(const VariableToken &obj) const {
		if (obj == *this)
			return true;
		return getValue() == obj.getValue();
	};

	void mutateStackForCalculation(stack<double> &valstack, map<string, double> variableValues) {
		map<string, double>::iterator iter = variableValues.find(getValue());
		if (iter != variableValues.end())
			valstack.push((*iter).second);
	}

	void mutateStackForInfixTranslation(stack<Token *> &operatorStack, string &output) {
		output.append(getValue().append(" "));
	}
};
#endif /* VARIABLETOKEN_H_ */
