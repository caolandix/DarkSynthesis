#include "physeqgrid.h"

PhysEqGrid::~PhysEqGrid() {
    for (QListIterator<PhysEqRow *> itr(m_rowList); itr.hasNext(); ) {
        PhysEqRow *pRow = itr.next();
        delete pRow;
    }
    m_rowList.clear();
}
