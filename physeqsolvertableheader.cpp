#include "physeqsolvertableheader.h"

PhysEqSolverTableHeader::PhysEqSolverTableHeader(QWidget *pParent) : QHeaderView(Qt::Horizontal, pParent) {
    // m_pActionInsertColumn = NULL;
    setSectionsClickable(true);
    setContextMenuPolicy(Qt::CustomContextMenu);

    connect(this, SIGNAL(sectionClicked(int)), this, SLOT(onSectionClicked(int)));
    //connect(this, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(ShowContextMenu(const QPoint &)));
}

void PhysEqSolverTableHeader::onSectionClicked(int index) {
    QMessageBox::about(this, "Hi! Header Click Detected!" ,"Index: " + QString::number(index));
}

