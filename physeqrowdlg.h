#ifndef PHYSEQROWDLG_H
#define PHYSEQROWDLG_H

#include <QDialog>

namespace Ui {
class PhysEqRowDlg;
}

class PhysEqRowDlg : public QDialog {
    Q_OBJECT

public:
    explicit PhysEqRowDlg(QWidget *parent = 0);
    ~PhysEqRowDlg();

private:
    Ui::PhysEqRowDlg *ui;
};

#endif // PHYSEQROWDLG_H
