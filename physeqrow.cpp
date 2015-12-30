#include <QtWidgets>
#include "physeqrow.h"
#include "physeqrowprops.h"


PhysEqRow::PhysEqRow(const PhysEqRow &obj) {
    m_pRowProps = new PhysEqRowProps(obj.DataObj() ->Equation(), obj.DataObj() ->Variable());
}

PhysEqRow &PhysEqRow::operator=(const PhysEqRow &obj) {
    if (this != &obj) {
        delete m_pRowProps;
        m_pRowProps = new PhysEqRowProps(obj.DataObj() ->Equation(), obj.DataObj() ->Variable());
    }
    return *this;
}

PhysEqRow::~PhysEqRow() {
    delete m_pRowProps; m_pRowProps = NULL;
    foreach(PhysEqGridCell *pItem, m_lstCells)
        delete pItem;
    m_lstCells.clear();
}

void PhysEqRow::addCell(PhysEqGridCell *pCell) {
    m_lstCells.push_back(pCell);
}


