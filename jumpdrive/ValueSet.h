/*
 * ValueSet.h
 *
 *  Created on: Jun 11, 2015
 *      Author: caolan
 */

#ifndef VALUESET_H_
#define VALUESET_H_

#include "commondefs.h"

class ValueSet {
public:
	ValueSet() { m_presultSet = new vector<double>(); };
	ValueSet(const vector<double> &);
	~ValueSet() {};

	// Member methods
	int size() const { return m_presultSet -> size(); };
	bool empty() const { return m_presultSet -> empty(); };
	vector<double>::const_iterator begin() const { return m_presultSet -> begin(); };
	vector<double>::const_iterator end() const { return m_presultSet -> end(); };
	void push_back(const double val) { m_presultSet -> push_back(val); };

	// Friend methods
	friend ostream &operator<<(ostream &, ValueSet const &);
private:
	vector<double> *m_presultSet;
};

#endif /* VALUESET_H_ */
