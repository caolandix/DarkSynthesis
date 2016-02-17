#include "physeqrowdlg.h"
#include "ui_physeqrowdlg.h"

PhysEqRowDlg::PhysEqRowDlg(QWidget *parent) : QDialog(parent), ui(new Ui::PhysEqRowDlg) {
    ui ->setupUi(this);
}

PhysEqRowDlg::~PhysEqRowDlg() {
    delete ui;
}
