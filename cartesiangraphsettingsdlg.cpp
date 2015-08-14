#include "cartesiangraphsettingsdlg.h"
#include "ui_cartesiangraphsettingsdlg.h"

CartesianGraphSettingsDlg::CartesianGraphSettingsDlg(QWidget *parent) : QDialog(parent),
    ui(new Ui::CartesianGraphSettingsDlg) {
    ui -> setupUi(this);
}

CartesianGraphSettingsDlg::~CartesianGraphSettingsDlg() {
    delete ui;
}
