#ifndef CARTESIANGRAPHSETTINGSDLG_H
#define CARTESIANGRAPHSETTINGSDLG_H

#include <QDialog>

class CartesianGraphDataObj;

namespace Ui {
class CartesianGraphSettingsDlg;
}

class CartesianGraphSettingsDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CartesianGraphSettingsDlg(CartesianGraphDataObj &, QWidget *parent = 0);
    ~CartesianGraphSettingsDlg();

    CartesianGraphDataObj &DataObj() const { return m_DataObj; }
    void DataObj(const CartesianGraphDataObj &obj) { m_DataObj = obj; }

protected:
    void done(int);

private:
    Ui::CartesianGraphSettingsDlg *ui;
    CartesianGraphDataObj &m_DataObj;
};

#endif // CARTESIANGRAPHSETTINGSDLG_H
