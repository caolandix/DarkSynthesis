/*
 * CustomFunction.cpp
 *
 *  Created on: Jun 13, 2014
 *      Author: caolan
 */

#include "CustomFunction.h"
#include "InvalidCustomFunctionException.h"

void CustomFunction::init() {
	if (!isalpha(m_name[0]))
		throw new InvalidCustomFunctionException("functions have to start with a lowercase or uppercase character");
}
