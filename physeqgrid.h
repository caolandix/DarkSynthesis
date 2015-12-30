#ifndef PHYSEQGRID_H
#define PHYSEQGRID_H

#include "physeqrow.h"

class PhysEqGrid {
public:
    PhysEqGrid();
    ~PhysEqGrid();

    int RowCount() const { return m_rowCount; }
    int ColCount() const { return m_colCount; }

private:
    void insertRow();


private:
    QList<PhysEqRow *> m_rowList;
    int m_rowCount, m_colCount;
};

#endif // PHYSEQGRID_H
