#ifndef CUSTOMFUNCTIONINTEGRATE_H
#define CUSTOMFUNCTIONINTEGRATE_H

#include "CustomFunction.h"

class CustomFunctionIntegrate : public CustomFunction {
public:
    CustomFunctionIntegrate(const string, const int = 0);

    virtual double applyFunction(double args[]) const;
    string applyFunction1(double args[]) const;
private:
    double m_Interval[2];
    bool m_isDefinite;
    string m_fx;        // base equation
};

#endif // CUSTOMFUNCTIONINTEGRATE_H
