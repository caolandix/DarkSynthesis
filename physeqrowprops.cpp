#include "physeqrowprops.h"


PhysEqRowProps::PhysEqRowProps(const QString &equation, const QString &variableName) {
    m_equation = equation;
    m_variableName = variableName;
}

PhysEqRowProps::PhysEqRowProps(const PhysRowProps &obj) {
    m_equation = obj.equation;
    m_variableName = obj.variableName;
}

PhysEqRowProps &PhysEqRowProps::operator=(const PhysRowProps &obj) {
    if (*this != obj) {
        m_equation = obj.equation;
        m_variableName = obj.variableName;
    }
    return *this;
}

