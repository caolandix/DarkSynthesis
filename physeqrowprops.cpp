#include "physeqrowprops.h"


PhysEqRowProps::PhysEqRowProps(const QString &equation, const QString &variableName) {
    m_equation = equation;
    m_variableName = variableName;
}

PhysEqRowProps::PhysEqRowProps(const PhysEqRowProps &obj) {
    m_equation = obj.Equation();
    m_variableName = obj.VariableName();
}

PhysEqRowProps &PhysEqRowProps::operator=(const PhysEqRowProps &obj) {
    if (this != &obj) {
        m_equation = obj.Equation();
        m_variableName = obj.VariableName();
    }
    return *this;
}

