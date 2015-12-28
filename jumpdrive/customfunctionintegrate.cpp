#include "CustomFunction.h"
#include "customfunctionintegrate.h"

// Args in an Integration include:
//  - Function in string form
//  -
CustomFunctionIntegrate::CustomFunctionIntegrate(const string Name, const int argCount) : CustomFunction(Name, argCount) {
}

string CustomFunctionIntegrate::applyFunction(double args[]) const {
    std::string Fx;
    if (m_isDefinite) {
        double val = applyFunction(args);
        Fx = boost::lexical_cast<std::string>(val);
    }
    else {
    }
    return Fx;
}

double CustomFunctionIntegrate::applyFunction(double args[]) const {

}
