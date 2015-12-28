#include "CustomFunction.h"
#include "customfunctiondifferentiate.h"

CustomFunctionDifferentiate::CustomFunctionDifferentiate(const string Name, const int argCount) : CustomFunction(Name, argCount) {

}

double CustomFunctionDifferentiate::applyFunction(double args[]) const {
    return 0.0;
}
