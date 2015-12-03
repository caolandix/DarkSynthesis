/*
 * UnparsableExpressionException.h
 *
 *  Created on: Jun 19, 2014
 *      Author: johndi
 */

#ifndef UNPARSABLEEXPRESSIONEXCEPTION_H_
#define UNPARSABLEEXPRESSIONEXCEPTION_H_

#include <boost/exception/exception.hpp>
#include <iostream>
using namespace std;

class UnparsableExpressionException: public boost::exception {
public:
    UnparsableExpressionException(string message) { cout << message <<  endl; }
};

#endif /* UNPARSABLEEXPRESSIONEXCEPTION_H_ */
