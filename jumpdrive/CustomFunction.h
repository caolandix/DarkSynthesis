/*
 * CustomFunction.h
 *
 *  Created on: Jun 11, 2014
 *      Author: johndi
 */

#ifndef CUSTOMFUNCTION_H_
#define CUSTOMFUNCTION_H_

#include "commondefs.h"

class CustomFunction {
public:
	CustomFunction() : m_PI(3.1415926), m_argc(0) {};
	virtual ~CustomFunction() {};


	int getArgumentCount() const { return m_argc; };
	virtual double applyFunction(double args[]) const { return 0.0; };
	string get_name() const { return m_name; };
private:
	int m_argc;
	string m_name;

	// COnvert degrees to radians -- trigonometric functions in the C++ library does everything in radians but inputs are in degrees so need to convert to make sure that
	// we get the proper values returned.
protected:
	CustomFunction(const string name, const int argumentCount = 1) : m_PI(3.1415926) {
		m_argc = argumentCount;
		m_name = name;
	}
	void init();
	double deg2rad(const double val) const { return val * m_PI / 180; };
	const double m_PI;
};


#endif /* CUSTOMFUNCTION_H_ */
