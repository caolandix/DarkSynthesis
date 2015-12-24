#ifndef PHYSEQROWPROPS_H
#define PHYSEQROWPROPS_H

#include <QtWidgets>

#include "physvectordataobj.h"

class PhysEqRowProps {
public:
    PhysEqRowProps(PhysVectorDataObj *pObj = NULL, bool bCalculated = false);
    PhysEqRowProps(const QString &, const QString &);
    PhysEqRowProps(const PhysEqRowProps &);
    PhysEqRowProps &operator=(const PhysEqRowProps &);
    ~PhysEqRowProps() {}

    const QString Equation() const { return m_pDataObj ->Equation(); }
    const QString Variable() const { return m_pDataObj ->Variable(); }
    void Equation(const QString &str) { m_pDataObj ->Equation(str); }
    void Variable(const QString &str) { m_pDataObj ->Variable(str); }
    bool Calculated() const { return m_bCalculated; }
    void Calculated(bool bVal) { m_bCalculated = bVal; }
private:
    PhysVectorDataObj *m_pDataObj;
    bool m_bCalculated;
};

#endif // PHYSEQROWPROPS_H
