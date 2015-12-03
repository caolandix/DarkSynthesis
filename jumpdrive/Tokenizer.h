/*
 * Tokenizer.h
 *
 *  Created on: Jun 13, 2014
 *      Author: caolan
 */

#ifndef TOKENIZER_H_
#define TOKENIZER_H_

#include "commondefs.h"
#include "jumpdrivedefs.h"

class Tokenizer {
public:
    Tokenizer() { setParenTokens(); }
	Tokenizer(vector<string> variableNames, map<string, CustomFunction *> functions, map<string, CustomOperator *> operators);
    virtual ~Tokenizer() {}

    list<Token*> getTokens(string &);
    bool isDigitOrDecimalSeparator(const char c) const { return isdigit(c) || c == '.'; }
    bool isNotationSeparator(const char c) const { return c == 'e' || c == 'E'; }
    void print_tokens(const string &, list<Token*>);
private:
	vector<string> m_variableNames;
	map<string, CustomFunction *> m_functions;
	map<string, CustomOperator *> m_operators;
	string m_parenTokens;

    bool isVariable(const string &) const;
    bool isFunction(const string &) const;
	bool isOperatorCharacter(const char) const;
    bool isOperatorStart(const string &) const;
	void setParenTokens();
    bool charInTokenSet(const char, const string &) const;
};

#endif /* TOKENIZER_H_ */
