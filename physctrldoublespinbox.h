#ifndef PHYSCTRLDOUBLESPINBOX_H
#define PHYSCTRLDOUBLESPINBOX_H

#include <QDoubleSpinBox>

class PhysCtrlDoubleSpinBox : public QDoubleSpinBox {
    Q_OBJECT
public:
    PhysCtrlDoubleSpinBox(const int precision = 6, QWidget * = NULL);
private:

signals:
public slots:
};

#endif // PHYSCTRLDOUBLESPINBOX_H