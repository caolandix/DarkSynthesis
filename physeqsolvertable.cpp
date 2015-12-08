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
    QStringList headers;
    for (int i = 0; i < model() ->columnCount(); i++)
        headers.append(model() ->headerData(i, Qt::Horizontal).toString());

    // Append a column to the end
    QString lastHeader = headers.back();
    QString lastColumn = lastHeader.right(lastHeader.count() - 1);
    int nextColumn = lastColumn.toInt() + 1;
    QString str("t");
    str += QString::number(nextColumn);
    QString newColumn(QString("t") + QString::number(nextColumn));

    model() ->insertColumn(lastHeader.count());
    //horizontalHeaderItem(lastHeader.count() - 1)->setText(newColumn);

    //model() ->insertColumn(lastHeader.count());
    //model() ->setHeaderData(lastHeader.count() - 1, Qt::Horizontal, QVariant(newColumn));

    resizeRowsToContents();
    resizeColumnsToContents();
}

void PhysEqSolverTable::removeColumn() {
    QStringList headers;
    for (int i = 0; i < model() ->columnCount(); i++)
        headers.append(model() ->headerData(i, Qt::Horizontal).toString());
}
