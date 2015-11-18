/*
 * NumberToken.cpp
 *
 *  Created on: Jun 13, 2014
 *      Author: johndi
 */

#include "NumberToken.h"

NumberToken::NumberToken(const string value) : Token(TT_NUMBER, value) {
	string str_temp = value;
	if (str_temp.find_first_of('E') != str_temp.npos || str_temp.find_first_of('e') != str_temp.npos) {

		//scientific notation as requested in EXP-17
		std::transform(str_temp.begin(), str_temp.end(), str_temp.begin(), ::tolower);
		int pos = str_temp.find_first_of('e');
		str_temp.substr(0, pos);
		double mantissa = atof(str_temp.substr(0, pos).c_str());
		double exponent = atof(str_temp.substr(pos + 1).c_str());
		m_doubleValue = mantissa * pow(10, exponent);
	}
	else
		m_doubleValue = atof(str_temp.c_str());
}

