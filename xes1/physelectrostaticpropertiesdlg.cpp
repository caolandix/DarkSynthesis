#include "physelectrostaticpropertiesdlg.h"
#include "ui_physelectrostaticpropertiesdlg.h"

PhysElectrostaticPropertiesDlg::PhysElectrostaticPropertiesDlg(QWidget *parent) : QDialog(parent),
    ui(new Ui::PhysElectrostaticPropertiesDlg) {
    ui->setupUi(this);
}

PhysElectrostaticPropertiesDlg::~PhysElectrostaticPropertiesDlg() {
    delete ui;
}
