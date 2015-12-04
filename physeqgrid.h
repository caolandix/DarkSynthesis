#ifndef PHYSEQGRID_H
#define PHYSEQGRID_H

#include "physeqrow.h"

class PhysEqGrid {
public:
    typedef QList<PhysEqRow *> RowList;
    PhysEqGrid() {}
    ~PhysEqGrid();

private:
    RowList m_rowList;
};

#endif // PHYSEQGRID_H
