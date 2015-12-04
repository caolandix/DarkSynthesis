#ifndef PHYSEQROW_H
#define PHYSEQROW_H

#include <QtWidgets>

#include "physeqgridcell.h"
#include "physeqrowprops.h"

class PhysEqRow {
public:
    typedef QList<PhysEqGridCell *> CellList;

    PhysEqRow() {}
    PhysEqRow(const QString &, const QString &);
    PhysEqRow(const PhysEqRow &);
    PhysEqRow &operator=(const PhysEqRow &);
    ~PhysEqRow();

    PhysEqRowProps *RowProps() const { return m_pRowProps; }
    CellList cellList() const { return m_CellList; }

private:
    CellList m_CellList;
    PhysEqRowProps *m_pRowProps;
};

#endif // PHYSEQROW_H
