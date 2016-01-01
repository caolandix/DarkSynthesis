#ifndef PHYSEQROW_H
#define PHYSEQROW_H

#include <QtWidgets>

#include "physeqgridcell.h"

class PhysEqRow {
public:

    typedef enum { RT_CARTGRAPH = 0, RT_PARTICLE, RT_VECTOR, RT_PROPERTY, RT_TIMESLICE } RowType;
    PhysEqRow(RowType type) : m_Type(type) {}
    PhysEqRow(const PhysEqRow &);
    PhysEqRow &operator=(const PhysEqRow &);
    ~PhysEqRow();

    RowType Type() const { return m_Type; }

    void Addy(const QString addy) { m_Addy = addy; }
    QString Addy() const { return m_Addy; }
    QString Equation() const { return m_Equation; }
    void Equation(QString eq) { m_Equation = eq; }

    void addCell(PhysEqGridCell *pCell);
private:
    // PhysEqRowProps *m_pRowProps;
    QList<PhysEqGridCell *> m_lstCells;
    RowType m_Type;
    QString m_Addy;         // The letter address of the row
    QString m_Equation;
};

#endif // PHYSEQROW_H
