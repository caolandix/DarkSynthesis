#ifndef PHYSEQROWPROPS_H
#define PHYSEQROWPROPS_H

#include <QtWidgets>

class PhysEqRowProps {
public:
    PhysEqRowProps() {}
    PhysEqRowProps(const QString &, const QString &);
    PhysEqRowProps(const PhysEqRowProps &);
    PhysEqRowProps &operator=(const PhysEqRowProps &);
    ~PhysEqRowProps() {}

    const QString Equation() const { return m_equation; }
    const QString VariableName() const { return m_variableName; }
    void Equation(const QString &str) { m_equation = str; }
    void VariableName(const QString &str) { m_variableName = str; }
private:
    QString m_variableName;
    QString m_equation;
};

#endif // PHYSEQROWPROPS_H
