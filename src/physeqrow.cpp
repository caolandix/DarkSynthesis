#include <QtWidgets>
#include "physeqrow.h"

PhysEqRow &PhysEqRow::operator=(const PhysEqRow &obj) {
    if (this != &obj) {
    }
    return *this;
}

PhysEqRow::~PhysEqRow() {
    foreach(PhysEqGridCell *pItem, m_lstCells)
        delete pItem;
    m_lstCells.clear();
}

void PhysEqRow::addCell(PhysEqGridCell *pCell) {
    m_lstCells.push_back(pCell);
}


