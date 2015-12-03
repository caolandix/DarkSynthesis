#include <QtWidgets>
#include "physeqsolvertable.h"

PhysEqSolverTable::PhysEqSolverTable(QWidget *pParent) : QTableWidget(pParent) {
}

PhysEqSolverTable::PhysEqSolverTable(const int rows, const int columns, QWidget *pParent) : QTableWidget(rows, columns, pParent) {
}

PhysEqSolverTable::~PhysEqSolverTable() {

}
