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
    ValueSet() { m_pResultSet = new VecDbl(); }
    ValueSet(const VecDbl &);
    ~ValueSet();

	// Member methods
    int size() const { return m_pResultSet -> size(); }
    bool empty() const { return m_pResultSet -> empty(); }
    VecDblIter begin() const { return m_pResultSet -> begin(); }
    VecDblIter end() const { return m_pResultSet -> end(); }
    void push_back(const double val) { m_pResultSet -> push_back(val); }
    double Value() const { return m_pResultSet ->at(0); }
    void resultSet(std::vector<double> *);
    std::vector<double> *resultSet() const { return m_pResultSet; }

	// Friend methods
	friend ostream &operator<<(ostream &, ValueSet const &);
private:
    VecDbl *m_pResultSet;
};

#endif /* VALUESET_H_ */
