#ifndef CUSTOMFUNCTIONDIFFERENTIATE_H
#define CUSTOMFUNCTIONDIFFERENTIATE_H

#include "CustomFunction.h"

class CustomFunctionDifferentiate : public CustomFunction {
public:
    CustomFunctionDifferentiate(const string, const int = 0);

    virtual double applyFunction(double args[]) const;
};

#endif // CUSTOMFUNCTIONDIFFERENTIATE_H
