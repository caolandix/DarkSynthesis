#ifndef CARTESIANGRAPHSETTINGSDLG_H
#define CARTESIANGRAPHSETTINGSDLG_H

#include <QDialog>

namespace Ui {
class CartesianGraphSettingsDlg;
}

class CartesianGraphSettingsDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CartesianGraphSettingsDlg(QWidget *parent = 0);
    ~CartesianGraphSettingsDlg();

protected:
    void done(int);

private:
    Ui::CartesianGraphSettingsDlg *ui;
};

#endif // CARTESIANGRAPHSETTINGSDLG_H
