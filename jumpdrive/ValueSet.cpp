/*
 * ResultSet.cpp
 *
 *  Created on: Jun 11, 2015
 *      Author: caolan
 */

#include "ValueSet.h"

ValueSet::ValueSet(const VecDbl &results) {
    m_presultSet = new VecDbl();
    for (VecDblIter iter = results.begin(); iter != results.end(); iter++)
		m_presultSet -> push_back(*iter);
}

std::ostream &operator<<(std::ostream &os, ValueSet const &obj) {
	if (obj.m_presultSet) {
        for (VecDblIter iter = obj.m_presultSet -> begin(); iter != obj.m_presultSet ->end(); iter++) {
			os << *iter;
			if (iter + 1 != obj.m_presultSet -> end())
				os << ", ";
		}
	}
    return os;
}
