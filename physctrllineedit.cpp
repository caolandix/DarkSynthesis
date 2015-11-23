#include <QGraphicsItem>
#include "physctrllineedit.h"

PhysCtrlLineEdit::PhysCtrlLineEdit(QGraphicsItem *pObj, QWidget *pParent) : QLineEdit(pParent) {
    m_pObj = pObj;
}

