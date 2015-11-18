/*
 * InvalidCustomFunctionException.h
 *
 *  Created on: Jun 12, 2014
 *      Author: johndi
 */

#ifndef INVALIDCUSTOMFUNCTIONEXCEPTION_H_
#define INVALIDCUSTOMFUNCTIONEXCEPTION_H_


#include <boost/exception/exception.hpp>
#include <iostream>
using namespace std;

class InvalidCustomFunctionException : public boost::exception {
public:
	InvalidCustomFunctionException(string message) {
		cout << message <<  endl;
	}
};

#endif /* INVALIDCUSTOMFUNCTIONEXCEPTION_H_ */
