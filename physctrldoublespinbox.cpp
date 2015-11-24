#include <QWidget>
#include <QDoubleSpinBox>
#include "physctrldoublespinbox.h"

PhysCtrlDoubleSpinBox::PhysCtrlDoubleSpinBox(const int precision, QWidget *pParent) : QDoubleSpinBox(pParent) {
    setDecimals(m_precision = precision);
}

