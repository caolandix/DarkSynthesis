#include <QGraphicsItem>
#include "physctrllineedit.h"

PhysCtrlLineEdit::PhysCtrlLineEdit(QGraphicsItem *pObj, QWidget *pParent) : QLineEdit(pParent) {
    m_pObj = pObj;

    //connect(m_pObj, SIGNAL(textChanged(const QString &)), this, SLOT(onPropChange(const QString &)));
}

