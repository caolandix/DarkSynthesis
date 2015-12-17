#include "physeqsolvertable.h"
#include "physeqsolvertableheader.h"
#include "physobjectpropdelegate.h"


PhysEqSolverTableHeader::PhysEqSolverTableHeader(QWidget *pParent) : QHeaderView(Qt::Horizontal, pParent) {
    m_pActionInsertColumn = NULL;
    m_pActionRemoveColumn = NULL;
    m_pTable = static_cast<PhysEqSolverTable *>(pParent);
    setSectionsClickable(true);
    setContextMenuPolicy(Qt::CustomContextMenu);

    connect(this, SIGNAL(sectionDoubleClicked(int)), this, SLOT(onSectionDoubleClicked(int)));
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(onShowContextMenu(const QPoint &)));
}

void PhysEqSolverTableHeader::onShowContextMenu(const QPoint &pos) {
    QMenu ctxMenu(tr("PhysEqTableheader Menu"));

    m_pActionInsertColumn = new QAction(tr("Insert Column"), this);
    m_pActionInsertColumn -> setStatusTip(tr("Insert a new time column"));
    connect(m_pActionInsertColumn, SIGNAL(triggered()), this, SLOT(insertColumn()));
    m_pActionRemoveColumn = new QAction(tr("Remove Column"), this);
    m_pActionRemoveColumn -> setStatusTip(tr("Removes a time column"));
    connect(m_pActionRemoveColumn, SIGNAL(triggered()), this, SLOT(removeColumn()));

    ctxMenu.addAction(m_pActionInsertColumn);
    ctxMenu.addAction(m_pActionRemoveColumn);

    m_hdrIdx = logicalIndexAt(pos);
    ctxMenu.exec(mapToGlobal(pos));
}

void PhysEqSolverTableHeader::onSectionDoubleClicked(int logicalIndex) {
    qDebug("PhysEqSolverTableHeader::onSectionDoubleClicked");

    QString strTime = QInputDialog::getText(this, tr("Enter a time value"), tr("Enter a value in seconds"), QLineEdit::Normal, "");
    int time = strTime.toInt();
    emit
    //model() ->setHeaderData(logicalIndex, Qt::Horizontal, strTime);

}

void PhysEqSolverTableHeader::insertColumn() {
    m_pTable ->insertColumn();
}

void PhysEqSolverTableHeader::removeColumn() {
    m_pTable ->removeColumn(m_hdrIdx);
}

