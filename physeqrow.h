#ifndef PHYSEQROW_H
#define PHYSEQROW_H

#include <QtWidgets>

#include "physeqgridcell.h"
#include "physeqrowprops.h"

class PhysEqRow {
public:

    PhysEqRow() {}
    PhysEqRow(PhysEqRowProps *);
    PhysEqRow(const PhysEqRow &);
    PhysEqRow &operator=(const PhysEqRow &);
    ~PhysEqRow();

    PhysEqRowProps *DataObj() const { return m_pRowProps; }

private:
    PhysEqRowProps *m_pRowProps;
};

#endif // PHYSEQROW_H
