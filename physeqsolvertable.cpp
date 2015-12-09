#include <QtWidgets>
#include "physeqsolvertable.h"
#include "physeqsolverdelegate.h"
#include "physeqsolvertableheader.h"

PhysEqSolverTable::PhysEqSolverTable(QWidget *pParent) : QTableWidget(pParent) {
}

PhysEqSolverTable::PhysEqSolverTable(const int rows, const int columns, QWidget *pParent) : QTableWidget(rows, columns, pParent) {
    setHorizontalHeader(m_pHeader = new PhysEqSolverTableHeader(this));
    setHorizontalHeaderLabels(QStringList() << "" << "t0");
    verticalHeader() ->setVisible(false);

    setSizeAdjustPolicy(QTableWidget::AdjustToContents);
    setItemPrototype(item(rows - 1, columns - 1));
    setItemDelegate(new PhysEqSolverDelegate());
}

PhysEqSolverTable::~PhysEqSolverTable() {
}

void PhysEqSolverTable::insertColumn() {
    model() ->insertColumn(model() ->columnCount());
    rebuildColumnHeaders();
    resizeColumnsToContents();
}

void PhysEqSolverTable::removeColumn(const int idx) {
    model() ->removeColumn(idx);
    rebuildColumnHeaders();
}

void PhysEqSolverTable::rebuildColumnHeaders() {
    QStringList headers;

    // rebuild column headers
    headers.push_back(QString(""));
    for (int i = 1; i < model() ->columnCount(); i++)
        headers.push_back(QString("t") + QString::number(i - 1));
    setHorizontalHeaderLabels(headers);
}
