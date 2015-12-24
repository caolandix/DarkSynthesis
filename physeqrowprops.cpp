#include "physeqrowprops.h"


PhysEqRowProps::PhysEqRowProps(PhysVectorDataObj *pObj, bool bCalculated) {
    m_pDataObj = pObj;
    m_bCalculated = bCalculated;
}

PhysEqRowProps::PhysEqRowProps(const QString &equation, const QString &variable) {
    Equation(equation);
    Variable(variable);
}

PhysEqRowProps::PhysEqRowProps(const PhysEqRowProps &obj) {
    Equation(obj.Equation());
    Variable(obj.Variable());
}

PhysEqRowProps &PhysEqRowProps::operator=(const PhysEqRowProps &obj) {
    if (this != &obj) {
        Equation(obj.Equation());
        Variable(obj.Variable());
    }
    return *this;
}

