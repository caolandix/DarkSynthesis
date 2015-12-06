#include <QtWidgets>
#include "physeqsolvertable.h"
#include "physeqsolverdelegate.h"
#include "physeqsolvertableheader.h"

PhysEqSolverTable::PhysEqSolverTable(QWidget *pParent) : QTableWidget(pParent) {
}

PhysEqSolverTable::PhysEqSolverTable(const int rows, const int columns, QWidget *pParent) : QTableWidget(rows, columns, pParent) {
    setSizeAdjustPolicy(QTableWidget::AdjustToContents);
    setItemPrototype(item(rows - 1, columns - 1));
    setHorizontalHeader(new PhysEqSolverTableHeader(this));
    setHorizontalHeaderLabels(QStringList() << "" << "t0");
    setItemDelegate(new PhysEqSolverDelegate());
    verticalHeader() ->setVisible(false);
}

PhysEqSolverTable::~PhysEqSolverTable() {
}

void PhysEqSolverTable::appendColumn() {
    QStringList headers;
    for (int i = 0; i < model() ->columnCount(); i++)
        headers.append(model() ->headerData(i, Qt::Horizontal).toString());

}

void PhysEqSolverTable::insertColumn(const QPoint pos) {
    QStringList headers;
}

void PhysEqSolverTable::removeColumn(const QPoint pos) {
    QStringList headers;
}
