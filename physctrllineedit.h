#ifndef PHYSCTRLLINEEDIT_H
#define PHYSCTRLLINEEDIT_H

#include <QLineEdit>

#include "cartesiangraph.h"


class PhysCtrlLineEdit : public QLineEdit {
    Q_OBJECT
public:
    PhysCtrlLineEdit(QWidget *pParent = NULL) : QLineEdit(pParent) {}
    PhysCtrlLineEdit(QGraphicsItem *, QWidget * = NULL);

signals:
    void updateGraphicsItem(const QString &);
public slots:

private:
    QGraphicsItem *m_pObj;
};

#endif // PHYSCTRLLINEEDIT_H
