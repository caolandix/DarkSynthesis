#include "physeqgrid.h"

PhysEqGrid::PhysEqGrid() {
    m_rowCount = 0;
    m_colCount = 0;
}

PhysEqGrid::~PhysEqGrid() {
    foreach (PhysEqRow *item, m_rowList)
        delete item;
    m_rowList.clear();
}

void PhysEqGrid::insertRow() {

}
