#ifndef CUSTOMFUNCTIONDIFFERENTIATE_H
#define CUSTOMFUNCTIONDIFFERENTIATE_H


class CustomFunctionDifferentiate : public CustomFunction {
public:
    CustomFunctionIntegrate(const string, const int = 0);

    virtual double applyFunction(double args[]) const;
};

#endif // CUSTOMFUNCTIONDIFFERENTIATE_H
