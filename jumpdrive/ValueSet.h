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
    ValueSet() : m_pResultSet(NULL) {}
    ValueSet(const VecDbl &);
    ~ValueSet() {}

	// Member methods
    void init() { m_pResultSet = new VecDbl(); }
    int size() const { return (m_pResultSet) ? m_pResultSet -> size() : 0; }
    bool empty() const { return (m_pResultSet) ? m_pResultSet -> empty() : true; }
    VecDblIter begin() const { return m_pResultSet -> begin(); }
    VecDblIter end() const { return m_pResultSet -> end(); }
    void push_back(const double val) { if (!m_pResultSet) m_pResultSet = new VecDbl(); m_pResultSet -> push_back(val); }
    double Value() const { return (m_pResultSet) ? m_pResultSet ->at(0) : -1; }
    void resultSet(std::vector<double> *);
    std::vector<double> *resultSet() const { return m_pResultSet; }

	// Friend methods
	friend ostream &operator<<(ostream &, ValueSet const &);
private:
    VecDbl *m_pResultSet;
};

#endif /* VALUESET_H_ */
