#ifndef PHYSCELLDATAOBJ_H
#define PHYSCELLDATAOBJ_H

#include "physdataobj.h"

class PhysCellDataObj : public PhysDataObj {
public:
    PhysCellDataObj(DataType type, const double val = 0.0) : PhysDataObj(QString(""), type), m_Data(val) {}

    double Data() const { return m_Data; }
    void Data(double val) { m_Data = val; }

private:
    double m_Data;
};

#endif // PHYSCELLDATAOBJ_H
