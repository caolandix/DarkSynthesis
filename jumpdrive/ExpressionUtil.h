/*
 * ExpressionUtil.h
 *
 *  Created on: Jun 13, 2014
 *      Author: johndi
 */

#ifndef EXPRESSIONUTIL_H_
#define EXPRESSIONUTIL_H_

#include "commondefs.h"

class ExpressionUtil {
public:
	ExpressionUtil() {};
	virtual ~ExpressionUtil() {};

	string &normalizeNumber(string &number);
};
#endif /* EXPRESSIONUTIL_H_ */
