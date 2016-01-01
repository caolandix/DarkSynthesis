#ifndef PHYSCELLDATAOBJ_H
#define PHYSCELLDATAOBJ_H

#include <QtWidgets>
#include "physdataobj.h"

class PhysCellDataObj : public PhysDataObj {
public:
    PhysCellDataObj(DataType type, const QString variable, const double val = 0.0, const bool bCalculated = false);

    double Data() const { return m_Data; }
    void Data(const double val) { m_Data = val; }
    bool Calculated() const { return m_bCalculated; }
    void Calculated(const bool bVal) { m_bCalculated = bVal; }
    QString Variable() const { return Name(); }
private:
    double m_Data;
    bool m_bCalculated;
};

#endif // PHYSCELLDATAOBJ_H
