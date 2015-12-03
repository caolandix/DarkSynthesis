/*
 * RPNExpression.h
 *
 *  Created on: Jun 13, 2014
 *      Author: caolan
 */

#ifndef RPNEXPRESSION_H_
#define RPNEXPRESSION_H_

#include "commondefs.h"
#include "jumpdrivedefs.h"
#include "Token.h"
#include "ValueSet.h"

class RPNExpression : public Calculable {
public:
    RPNExpression() {}
	RPNExpression(const list<Token *> &tokens, const string &expression, const map<string, double> &variables);
    virtual ~RPNExpression() {}

	ValueSet calculate(const ValueSet values);
    string getExpression() const { return m_expression; }
    void setVariable(string name, double value) { m_variables.insert(pair<string, double>(name, value)); }
    void print(const string &);
private:
	list<Token *> m_tokens;
	string m_expression;
	map<string, double> m_variables;
	stack<double> m_valstack;
};

#endif /* RPNEXPRESSION_H_ */
