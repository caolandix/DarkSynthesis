#include "cartesiangraphsettingsdlg.h"
#include "ui_cartesiangraphsettingsdlg.h"

#include "cartesiangraphdataobj.h"

CartesianGraphSettingsDlg::CartesianGraphSettingsDlg(CartesianGraphDataObj &dataObj, QWidget *parent) : QDialog(parent),
    ui(new Ui::CartesianGraphSettingsDlg) {
    ui -> setupUi(this);
    m_DataObj = DataObj;
}

CartesianGraphSettingsDlg::~CartesianGraphSettingsDlg() {
    delete ui;
}

void CartesianGraphSettingsDlg::done(int r) {

    // check if OK was pressed
    if (QDialog::Accepted == r) {

        // do data validation
        if (1) {
            QDialog::done(r);
            return;
        }

        // error reporting
        else {
            //statusBar -> setText("Invalid data in text edit...try again...");
            return;
        }
    }

    // handle Cancel, Close, etc. ...
    else {
        QDialog::done(r);
        return;
    }
}
