#ifndef PHYSEQROW_H
#define PHYSEQROW_H

#include <QtWidgets>

#include "physeqgridcell.h"
#include "physeqrowprops.h"

class PhysEqRow {
public:

    typedef enum { RT_CARTGRAPH = 0, RT_PARTICLE, RT_VECTOR, RT_PROPERTY, RT_TIMESLICE } RowType;
    PhysEqRow(RowType type) : m_Type(type) {}
    PhysEqRow(PhysEqRowProps *pObj) : m_pRowProps(pObj) {}
    PhysEqRow(const PhysEqRow &);
    PhysEqRow &operator=(const PhysEqRow &);
    ~PhysEqRow();

    PhysEqRowProps *DataObj() const { return m_pRowProps; }
    RowType Type() const { return m_Type; }

    void Addy(const QString addy) { m_Addy = addy; }
    QString Addy() const { return m_Addy; }

    void addCell(PhysEqGridCell *pCell);
private:
    PhysEqRowProps *m_pRowProps;
    QList<PhysEqGridCell *> m_lstCells;
    RowType m_Type;
    QString m_Addy;         // The letter address of the row
};

#endif // PHYSEQROW_H
