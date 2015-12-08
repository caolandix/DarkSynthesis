#include <QtWidgets>
#include "physeqsolvertable.h"
#include "physeqsolverdelegate.h"
#include "physeqsolvertableheader.h"

PhysEqSolverTable::PhysEqSolverTable(QWidget *pParent) : QTableWidget(pParent) {
}

PhysEqSolverTable::PhysEqSolverTable(const int rows, const int columns, QWidget *pParent) : QTableWidget(rows, columns, pParent) {
    setSizeAdjustPolicy(QTableWidget::AdjustToContents);
    setItemPrototype(item(rows - 1, columns - 1));
    setHorizontalHeader(m_pHeader = new PhysEqSolverTableHeader(this));
    setHorizontalHeaderLabels(QStringList() << "" << "t0");
    setItemDelegate(new PhysEqSolverDelegate());
    verticalHeader() ->setVisible(false);

    connect(m_pHeader, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(ShowContextMenu(const QPoint &)));
}

PhysEqSolverTable::~PhysEqSolverTable() {
}


void PhysEqSolverTable::ShowContextMenu(const QPoint &pos) {
    QMenu ctxMenu(tr("PhysEqTableheader Menu"));

    m_pActionInsertColumn = new QAction(tr("Insert Column"), this);
    m_pActionInsertColumn -> setStatusTip(tr("Insert a new time column"));
    connect(m_pActionInsertColumn, SIGNAL(triggered()), this, SLOT(insertColumn()));
    m_pActionRemoveColumn = new QAction(tr("Remove Column"), this);
    m_pActionRemoveColumn -> setStatusTip(tr("Removes a time column"));
    connect(m_pActionRemoveColumn, SIGNAL(triggered()), this, SLOT(removeColumn()));

    ctxMenu.addAction(m_pActionInsertColumn);
    ctxMenu.addAction(m_pActionRemoveColumn);

    QAction *pAction = NULL;
    QPoint globalPos = mapToGlobal(pos);
    if (pAction = ctxMenu.exec(globalPos)) {
        bool bVal = true;
    }
}

void PhysEqSolverTable::insertColumn() {
    QStringList headers;
    for (int i = 0; i < model() ->columnCount(); i++)
        headers.append(model() ->headerData(i, Qt::Horizontal).toString());

    // Append a column to the end
    QString lastHeader = headers.back();
    QString lastColumn = lastHeader.right(lastHeader.count() - 1);
    int nextColumn = lastColumn.toInt() + 1;
    QString newColumn(QString::number(nextColumn));
    bool bVal = true;
}

void PhysEqSolverTable::removeColumn() {
    QStringList headers;
    for (int i = 0; i < model() ->columnCount(); i++)
        headers.append(model() ->headerData(i, Qt::Horizontal).toString());
}
