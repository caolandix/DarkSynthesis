/*
 * commondefs.h
 *
 *  Created on: Jun 16, 2014
 *      Author: caolan
 */

#ifndef COMMONDEFS_H_
#define COMMONDEFS_H_

#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <exception>
#include <functional>
#include <iostream>
#include <list>
#include <locale>
#include <map>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

#include "IllegalArgumentException.h"
#include "InvalidCustomFunctionException.h"
#include "ArithmeticException.h"

using namespace std;
using namespace boost;
using namespace boost::multi_index;

using boost::multi_index_container;

typedef unsigned int uint;
typedef vector<double> VecDbl;
typedef vector<double>::const_iterator VecDblIter;
typedef vector<string> VecStr;
typedef vector<string>::const_iterator VecStrIter;

#endif /* COMMONDEFS_H_ */
