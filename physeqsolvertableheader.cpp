#include "physeqsolvertable.h"
#include "physeqsolvertableheader.h"

PhysEqSolverTableHeader::PhysEqSolverTableHeader(QWidget *pParent) : QHeaderView(Qt::Horizontal, pParent) {
    m_pActionInsertColumn = NULL;
    m_pActionRemoveColumn = NULL;
    m_pTable = static_cast<PhysEqSolverTable *>(pParent);
    setSectionsClickable(true);
    setContextMenuPolicy(Qt::CustomContextMenu);

    connect(this, SIGNAL(sectionClicked(int)), this, SLOT(onSectionClicked(int)));
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(onShowContextMenu(const QPoint &)));
}

void PhysEqSolverTableHeader::onSectionClicked(int index) {
    QMessageBox::about(this, "Hi! Header Click Detected!" ,"Index: " + QString::number(index));
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

void PhysEqSolverTableHeader::insertColumn() {
    m_pTable ->insertColumn();
}

void PhysEqSolverTableHeader::removeColumn() {
    m_pTable ->removeColumn(m_hdrIdx);
}

