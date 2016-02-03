#ifndef PHYSEQGRIDCELL_H
#define PHYSEQGRIDCELL_H

#include <QtWidgets>
#include "physdataobj.h"

class PhysEqGridCell {
public:
    PhysEqGridCell(PhysDataObj *, const QString);
    ~PhysEqGridCell() { delete m_pObj; m_pObj = NULL; }
    PhysDataObj *Obj() const { return m_pObj; }

private:
    QString m_CellAddress;
    PhysDataObj *m_pObj;
};

#endif // PHYSEQGRIDCELL_H
