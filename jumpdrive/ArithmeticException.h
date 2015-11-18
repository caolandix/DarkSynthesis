/*
 * ArithmeticException.h
 *
 *  Created on: Jun 19, 2014
 *      Author: johndi
 */

#ifndef ARITHMETICEXCEPTION_H_
#define ARITHMETICEXCEPTION_H_

#include <boost/exception/exception.hpp>
#include <iostream>
using namespace std;

class ArithmeticException: public boost::exception {
public:

	ArithmeticException(string message) {
		cout << message <<  endl;
	};
};

#endif /* ARITHMETICEXCEPTION_H_ */
