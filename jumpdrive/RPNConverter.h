/*
 * RPNConverter.h
 *
 *  Created on: Jun 13, 2014
 *      Author: caolan
 */

#ifndef RPNCONVERTER_H_
#define RPNCONVERTER_H_

#include "commondefs.h"
#include "Token.h"
#include "RPNExpression.h"
#include "CustomFunction.h"
#include "CustomOperator.h"


class RPNConverter {
public:
	RPNConverter() {};
	virtual ~RPNConverter() {};

	 RPNExpression toRPNExpression(const string infix, map<string, double> &variables, map<string, CustomFunction*> &customFunctions, map<string, CustomOperator *> &operators);
	string substituteUnaryOperators(const string expr, map<string, CustomOperator *> &operators);
private:
	void validateRPNExpression(list<Token*> &tokens, map<string, CustomOperator *> &operators);
	bool isOperatorCharacter(const char c, map<string, CustomOperator *> &operators);
};

#endif /* RPNCONVERTER_H_ */
