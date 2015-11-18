/*
 * ExpressionUtil.cpp
 *
 *  Created on: Jun 13, 2014
 *      Author: johndi
 */
#include "commondefs.h"
#include "ExpressionUtil.h"

string &ExpressionUtil::normalizeNumber(string &number) {
	number.replace(number.begin(), number.end(), "e|E", "*10^");
	return number;
}
