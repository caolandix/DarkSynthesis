/*
 * ResultSet.cpp
 *
 *  Created on: Jun 11, 2015
 *      Author: caolan
 */

#include "ValueSet.h"

ValueSet::ValueSet(const vector<double> &results) {
	m_presultSet = new vector<double>();
	for (vector<double>::const_iterator iter = results.begin(); iter != results.end(); iter++)
		m_presultSet -> push_back(*iter);
}

std::ostream &operator<<(std::ostream &os, ValueSet const &obj) {
	if (obj.m_presultSet) {
		for (vector<double>::const_iterator iter = obj.m_presultSet -> begin(); iter != obj.m_presultSet ->end(); iter++) {
			os << *iter;
			if (iter + 1 != obj.m_presultSet -> end())
				os << ", ";
		}
	}
    return os;
}
