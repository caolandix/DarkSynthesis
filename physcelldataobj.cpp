#include <QtWidgets>
#include "physcelldataobj.h"
#include "physdataobj.h"

PhysCellDataObj::PhysCellDataObj(
        DataType type,
        const QString variable,
        const double val,
        const bool bCalculated) : PhysDataObj(variable, type) {
    m_Data = val;
    m_bCalculated = bCalculated;
}
