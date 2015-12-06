#include "physeqsolvertableheader.h"

PhysEqSolverTableHeader::PhysEqSolverTableHeader(QWidget *pParent) : QHeaderView(Qt::Horizontal, pParent) {
   setSectionsClickable(true);
   connect(this, SIGNAL(sectionClicked(int)), this, SLOT(onSectionClicked(int)));
}

void PhysEqSolverTableHeader::onSectionClicked(int index) {
    QMessageBox::about(this, "Hi! Header Click Detected!" ,"Index: " + QString::number(index));
}
