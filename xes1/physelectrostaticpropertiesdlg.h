#ifndef PHYSELECTROSTATICPROPERTIESDLG_H
#define PHYSELECTROSTATICPROPERTIESDLG_H

#include <QDialog>

namespace Ui {
class PhysElectrostaticPropertiesDlg;
}

class PhysElectrostaticPropertiesDlg : public QDialog
{
    Q_OBJECT

public:
    explicit PhysElectrostaticPropertiesDlg(QWidget *parent = 0);
    ~PhysElectrostaticPropertiesDlg();

private:
    Ui::PhysElectrostaticPropertiesDlg *ui;
};

#endif // PHYSELECTROSTATICPROPERTIESDLG_H
