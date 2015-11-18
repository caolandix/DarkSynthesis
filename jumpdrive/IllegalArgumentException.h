/*
 * IllegalArgumentException.h
 *
 *  Created on: Jun 17, 2014
 *      Author: johndi
 */

#ifndef ILLEGALARGUMENTEXCEPTION_H_
#define ILLEGALARGUMENTEXCEPTION_H_

#include <boost/exception/exception.hpp>
#include <iostream>
using namespace std;

class IllegalArgumentException : public boost::exception {
public:
	//virtual ~IllegalArgumentException() {};

	IllegalArgumentException(string message) {
		cout << message <<  endl;
	}
};

#endif /* ILLEGALARGUMENTEXCEPTION_H_ */
