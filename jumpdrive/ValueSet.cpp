/*
 * ResultSet.cpp
 *
 *  Created on: Jun 11, 2015
 *      Author: caolan
 */

#include "ValueSet.h"

ValueSet::ValueSet(const VecDbl &results) {
    m_pResultSet = new VecDbl();
    for (VecDblIter iter = results.begin(); iter != results.end(); iter++)
        m_pResultSet -> push_back(*iter);
}

ValueSet::~ValueSet() {
    if (m_pResultSet) {
        m_pResultSet ->clear();
        delete m_pResultSet;
    }
    m_pResultSet = NULL;
}


void ValueSet::resultSet(std::vector<double> *pRS) {
    if (m_pResultSet)
        delete m_pResultSet;
    m_pResultSet = new VecDbl();
    for (VecDblIter iter = pRS ->begin(); iter != pRS ->end(); iter++)
        m_pResultSet -> push_back(*iter);
}


std::ostream &operator<<(std::ostream &os, ValueSet const &obj) {
    if (obj.m_pResultSet) {
        for (VecDblIter iter = obj.m_pResultSet -> begin(); iter != obj.m_pResultSet ->end(); iter++) {
			os << *iter;
            if (iter + 1 != obj.m_pResultSet -> end())
				os << ", ";
		}
	}
    return os;
}
